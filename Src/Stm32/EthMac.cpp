#include "Board.h"
#include "Sys/EthPhy.h"
#include "Sys/EthMac.h"
#include "Sys/IsrVector.h"
#include "Sys/Mdio.h"
#include "Rtos/Kernel.h"
#include "Util.h"
#include <stm32f7xx.h>
#include <stm32f746xx.h>

//MAN: rm0385-stm32f75xxx-and-stm32f74xxx-advanced-armbased-32bit-mcus-stmicroelectronics.pdf

#define DMA_ALIGN __attribute__ ((aligned (__SCB_DCACHE_LINE_SIZE)))

namespace
{
	//MAN: Ethernet DMA status register. Page 1634.
	struct DMASR_Reg
	{
		union
		{
			struct
			{
				uint32_t TS : 1;
				uint32_t TPSS : 1;
				uint32_t TBUS : 1;
				uint32_t TJTS : 1;
				uint32_t ROS : 1;
				uint32_t TUS : 1;
				uint32_t RS : 1;
				uint32_t RBUS : 1;
				uint32_t RPSS : 1;
				uint32_t RWTS : 1;
				uint32_t ETS : 1;
				uint32_t : 2;
				uint32_t FBES : 1;
				uint32_t ERS : 1;
				uint32_t AIS : 1;
				uint32_t NIS : 1;
				uint32_t RPS : 3;
				uint32_t TPS : 3;
				uint32_t EBS : 3;
				uint32_t : 1;
				uint32_t MMCS : 1;
				uint32_t PMTS : 1;
				uint32_t TSTS : 1;
				uint32_t : 2;
			};
			uint32_t AsUint32;
		};
	};
	static_assert(sizeof(DMASR_Reg) == sizeof(uint32_t), "Invalid size");

	//MAN: Figure 518. Page 1578.
	struct TxDmaDescriptor
	{
		union
		{
			struct
			{
				uint32_t Status : 17;
				uint32_t TTSS : 1;
				uint32_t : 2;
				uint32_t TCH : 1;
				uint32_t TER : 1;
				uint32_t CIC : 2;
				uint32_t : 1;
				uint32_t TTSE : 1;
				uint32_t DP : 1;
				uint32_t DC : 1;
				uint32_t FS : 1;
				uint32_t LS : 1;
				uint32_t IC : 1;
				uint32_t Own : 1;
			};
			uint32_t AsUint32;
		} TDES0;

		union
		{
			struct
			{
				uint32_t Buffer1Size : 13;
				uint32_t Reserved : 3;
				uint32_t Buffer2Size : 13;
				uint32_t Reserved2 : 3;
			};
			uint32_t AsUint32;
		} TDES1;
		
		//Buffer Address
		uint32_t TDES2;

		//Buffer2/Chain address
		uint32_t TDES3;
	};
	static_assert(sizeof(TxDmaDescriptor) == sizeof(uint32_t) * 4, "Invalid size");

	//MAN: Figure 521. Page 1588.
	struct RxDmaDescriptor
	{
		union
		{
			struct
			{
				uint32_t Status : 16;
				uint32_t FrameLength : 14;
				uint32_t AFM : 1;
				uint32_t Own : 1;
			};
			uint32_t AsUint32;
		} TDES0;

		union
		{
			struct
			{
				uint32_t Buffer1Count : 13;
				uint32_t : 1;
				uint32_t Chain : 1;
				uint32_t Ring : 1;
				uint32_t Buffer2Count : 13;
				uint32_t : 2;
				uint32_t CTRL2 : 1;
			};
			uint32_t AsUint32;
		} TDES1;

		//Buffer Address
		uint32_t TDES2;

		//Buffer2/Chain address
		uint32_t TDES3;
	};
	static_assert(sizeof(RxDmaDescriptor) == sizeof(uint32_t) * 4, "Invalid size");
	
	//Tx DMA
	static size_t m_txIndex;
	static DMA_ALIGN TxDmaDescriptor m_txDescriptors[EthMac::BufferCount];
	static DMA_ALIGN uint8_t m_txBuffers[EthMac::BufferCount][EthMac::BufferSize];

	//Rx DMA
	static DMA_ALIGN RxDmaDescriptor m_rxDescriptors[EthMac::BufferCount];
	static DMA_ALIGN uint8_t m_rxBuffers[EthMac::BufferCount][EthMac::BufferSize];
}

namespace EthMac
{
	ParamCallback<const ReadOnlyBuffer&> FrameReceived;

	//MAN: 38.6.1 Initialization of a transfer using DMA. Page 1571.
	void Init()
	{
		//Enable clocks
		__DSB();

		//Force reset
		SET_BIT(RCC->AHB1RSTR, RCC_AHB1RSTR_ETHMACRST);
		CLEAR_BIT(RCC->AHB1RSTR, RCC_AHB1RSTR_ETHMACRST);

		//Initialize TX DMA
		for (size_t i = 0; i < BufferCount; ++i)
		{
			m_txDescriptors[i].TDES0.AsUint32 = 0;
			m_txDescriptors[i].TDES1.AsUint32 = 0;
			m_txDescriptors[i].TDES2 = (uint32_t)(uintptr_t)m_txBuffers[i];
			m_txDescriptors[i].TDES3 = (uint32_t)&m_txDescriptors[(i + 1) % BufferCount];
		}

		//Initialize RX DMA
		for (size_t i = 0; i < BufferCount; ++i)
		{
			m_rxDescriptors[i].TDES0.AsUint32 = 0;
			m_rxDescriptors[i].TDES0.Own = 1;
			m_rxDescriptors[i].TDES1.AsUint32 = 0;
			m_rxDescriptors[i].TDES1.Buffer1Count = EthMac::BufferSize;
			m_rxDescriptors[i].TDES1.Chain = 1;
			m_rxDescriptors[i].TDES2 = (uint32_t)(uintptr_t)m_rxBuffers[i];
			m_rxDescriptors[i].TDES3 = (uint32_t)&m_rxDescriptors[(i + 1) % BufferCount];
		}

		//Initialize MDIO clock
		MODIFY_REG(ETH->MACMIIAR, ETH_MACMIIAR_CR, ETH_MACMIIAR_CR_Div102);

		//Detect phy
		uint16_t phyAddr = 0;
		Assert(EthPhy::Detect(phyAddr));

		//Reset Phy
		EthPhy phy(phyAddr);
		phy.Init();
		phy.Display();

		//Reset MAC
		SET_BIT(ETH->DMABMR, ETH_DMABMR_SR);
		while(READ_BIT(ETH->DMABMR, ETH_DMABMR_SR) != 0);

		//Setup interrupts
		SET_BIT(ETH->DMAIER, ETH_DMAIER_NISE);
		SET_BIT(ETH->DMAIER, ETH_DMAIER_RIE);

		//Set descriptors
		ETH->DMARDLAR = (uint32_t)(uintptr_t)m_rxDescriptors;
		ETH->DMATDLAR = (uint32_t)(uintptr_t)m_txDescriptors;

		//Enable transmit and receive
		ETH->MACCR = ETH_MACCR_FES | ETH_MACCR_DM | ETH_MACCR_TE | ETH_MACCR_RE;

		//Start DMA TX
		ETH->DMAOMR = ETH_DMAOMR_TSF | ETH_DMAOMR_RSF | ETH_DMAOMR_ST | ETH_DMAOMR_SR;

		//TODO: MAC filtering
		//Enable all MAC
		ETH->MACFFR = ETH_MACFFR_RA;

		//Register and enable interrupts
		IsrVector::Register(IRQn_Type::ETH_IRQn, {&EthMac::OnInterrupt, nullptr});
		NVIC_EnableIRQ(ETH_IRQn);

		//TODO(tsharpe): Delay hack, find out why this is needed.
		(void)ETH->DMASR;
	}

	void Send(const ReadOnlyBuffer& frame)
	{
		//Check buffer size
		Assert(frame.Length <= EthMac::BufferSize);
		
		//Ensure descriptor is free
		AssertPrintHex32(m_txDescriptors[m_txIndex].TDES0.Own == 0, ETH->DMASR);

		//Copy data to buffer
		memcpy(m_txBuffers[m_txIndex], frame.Data, frame.Length);
		m_txDescriptors[m_txIndex].TDES1.Buffer1Size = frame.Length;
		
		m_txDescriptors[m_txIndex].TDES0.AsUint32 = 0;
		m_txDescriptors[m_txIndex].TDES0.FS = 1;
		m_txDescriptors[m_txIndex].TDES0.LS = 1;
		m_txDescriptors[m_txIndex].TDES0.TCH = 1;
		m_txDescriptors[m_txIndex].TDES0.Own = 1;
		__DSB();

		m_txIndex = (m_txIndex + 1) % BufferCount;

		//If suspended, resume
		if (READ_BIT(ETH->DMASR, ETH_DMASR_TBUS))
		{
			SET_BIT(ETH->DMASR, ETH_DMASR_TBUS);
			SET_BIT(ETH->DMATPDR, ETH_DMATPDR_TPD);
		}
		if (READ_BIT(ETH->DMASR, ETH_DMASR_TUS))
		{
			SET_BIT(ETH->DMASR, ETH_DMASR_TUS);
			SET_BIT(ETH->DMATPDR, ETH_DMATPDR_TPD);
		}
	}

	void OnInterrupt(void* arg)
	{
		if (READ_BIT(ETH->DMASR, ETH_DMASR_RS))
		{
			//Loop through descriptors to find received packets
			for (size_t i = 0; i < EthMac::BufferCount; i++)
			{
				RxDmaDescriptor& desc = m_rxDescriptors[i];
				if (desc.TDES0.Own)
					continue;

				uint8_t packet[desc.TDES0.FrameLength];
				memcpy(packet, m_rxBuffers[i], desc.TDES0.FrameLength);
				const ReadOnlyBuffer buffer = { packet, desc.TDES0.FrameLength };
				if (FrameReceived.IsCallable())
					FrameReceived.Invoke(buffer);

				desc.TDES0.Own = 1;
			}

			//Clear
			SET_BIT(ETH->DMASR, ETH_DMASR_RS);
		}

		//If DMA RX stopped because no buffers were available, restart it
		if (READ_BIT(ETH->DMASR, ETH_DMASR_RBUS))
		{
			SET_BIT(ETH->DMASR, ETH_DMASR_RBUS);
			SET_BIT(ETH->DMARPDR, ETH_DMARPDR_RPD);
		}

		//If Tx Suspended, restart
		/*
		if (GET_REG_FIELD(ETH->DMASR, ETH_DMASR_TPS_Suspended, ETH_DMASR_TPS_Pos))
		{
			ETH->DMASR |= ETH_DMASR_TPS;
		}
		*/
		ETH->DMASR = ETH->DMASR & ~(ETH_DMASR_TBUS | ETH_DMASR_RBUS);
		SET_BIT(ETH->DMATPDR, ETH_DMATPDR_TPD);
	}

	void Display()
	{
		DMASR_Reg reg;
		reg.AsUint32 = ETH->DMASR;
		Board::Printf("DMASR 0x%08X\r\n", reg.AsUint32);
		Board::Printf("  TS: 0x%x\r\n", reg.TS);
		Board::Printf("  TPSS: 0x%x\r\n", reg.TPSS);
		Board::Printf("  TBUS: 0x%x\r\n", reg.TBUS);
		Board::Printf("  TJTS: 0x%x\r\n", reg.TJTS);
		Board::Printf("  ROS: 0x%x\r\n", reg.ROS);
		Board::Printf("  TUS: 0x%x\r\n", reg.TUS);
		Board::Printf("  RS: 0x%x\r\n", reg.RS);
		Board::Printf("  RBUS: 0x%x\r\n", reg.RBUS);
		Board::Printf("  RPSS: 0x%x\r\n", reg.RPSS);
		Board::Printf("  RWTS: 0x%x\r\n", reg.RWTS);
		Board::Printf("  ETS: 0x%x\r\n", reg.ETS);
		Board::Printf("  FBES: 0x%x\r\n", reg.FBES);
		Board::Printf("  ERS: 0x%x\r\n", reg.ERS);
		Board::Printf("  AIS: 0x%x\r\n", reg.AIS);
		Board::Printf("  NIS: 0x%x\r\n", reg.NIS);
		Board::Printf("  RPS: 0x%x\r\n", reg.RPS);
		Board::Printf("  TPS: 0x%x\r\n", reg.TPS);
		Board::Printf("  EBS: 0x%x\r\n", reg.EBS);
		Board::Printf("  MMCS: 0x%x\r\n", reg.MMCS);
		Board::Printf("  PMTS: 0x%x\r\n", reg.PMTS);
		Board::Printf("  TSTS: 0x%x\r\n", reg.TSTS);
	}
}
