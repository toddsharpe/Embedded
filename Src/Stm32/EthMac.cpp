#include "Stm32/EthMac.h"
#include "Assert.h"
#include "Sys/EthPhy.h"
#include "Stm32/Mdio.h"
#include "Rtos/Types.h"

#include <stm32f7xx.h>
#include <stm32f746xx.h>
#include <cstring>

extern void DebugPrintf(const char* format, ...);
extern void DebugPrintBytes(const char* buffer, const size_t length);

namespace Stm32
{
	EthMac::EthMac(ETH_TypeDef* eth, uint8_t (&txBuffers)[EthMac::BufferCount][EthMac::BufferSize], uint8_t (&rxBuffers)[EthMac::BufferCount][EthMac::BufferSize]) :
		Sys::EthMac(),
		m_eth(eth),
		m_txIndex(),
		m_txDescriptors(),
		m_txBuffers(txBuffers),
		m_rxDescriptors(),
		m_rxBuffers(rxBuffers)
	{
	}

	//MAN: 38.6.1 Initialization of a transfer using DMA. Page 1571.
	void EthMac::Init()
	{
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

		//Enable clocks
		SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_ETHMACEN);
		SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_ETHMACRXEN);
		SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_ETHMACTXEN);
		__DSB();

		//Reset MAC
		SET_BIT(m_eth->DMABMR, ETH_DMABMR_SR);
		while(READ_BIT(m_eth->DMABMR, ETH_DMABMR_SR) != 0);

		//Initialize MDIO clock
		MODIFY_REG(m_eth->MACMIIAR, ETH_MACMIIAR_CR, ETH_MACMIIAR_CR_Div102);

		//Reset Phy
		Mdio mdio(m_eth);
		Sys::EthPhy phy(0, mdio);
		phy.Init();
		phy.Display();

		//Setup interrupts
		SET_BIT(m_eth->DMAIER, ETH_DMAIER_NISE);
		SET_BIT(m_eth->DMAIER, ETH_DMAIER_RIE);

		//Set descriptors
		m_eth->DMARDLAR = (uint32_t)(uintptr_t)m_rxDescriptors;
		m_eth->DMATDLAR = (uint32_t)(uintptr_t)m_txDescriptors;

		//Enable transmit and receive
		m_eth->MACCR = ETH_MACCR_FES | ETH_MACCR_DM | ETH_MACCR_TE | ETH_MACCR_RE;

		//Start DMA TX
		m_eth->DMAOMR = ETH_DMAOMR_TSF | ETH_DMAOMR_RSF | ETH_DMAOMR_ST | ETH_DMAOMR_SR;

		//TODO: MAC filtering
		//Enable all MAC
		m_eth->MACFFR = ETH_MACFFR_RA;

		//Enable interrupts
		NVIC_EnableIRQ(ETH_IRQn);
	}

	void EthMac::Display()
	{
		DebugPrintf("DMASR 0x%08X\r\n", m_eth->DMASR);
	}

	void EthMac::Send(uint8_t* buffer, const size_t length)
	{
		//Check buffer size
		Assert(length <= EthMac::BufferSize);
		
		//Ensure descriptor is free
		AssertPrintHex32(m_txDescriptors[m_txIndex].TDES0.Own == 0, m_eth->DMASR);

		//Copy data to buffer
		memcpy(m_txBuffers[m_txIndex], buffer, length);
		m_txDescriptors[m_txIndex].TDES1.Buffer1Size = length;
		
		m_txDescriptors[m_txIndex].TDES0.AsUint32 = 0;
		m_txDescriptors[m_txIndex].TDES0.FS = 1;
		m_txDescriptors[m_txIndex].TDES0.LS = 1;
		m_txDescriptors[m_txIndex].TDES0.TCH = 1;
		m_txDescriptors[m_txIndex].TDES0.Own = 1;

		m_txIndex = (m_txIndex + 1) % BufferCount;

		//If suspended, resume
		if (READ_BIT(m_eth->DMASR, ETH_DMASR_TBUS))
		{
			SET_BIT(m_eth->DMASR, ETH_DMASR_TBUS);
			SET_BIT(m_eth->DMATPDR, ETH_DMATPDR_TPD);
		}
	}

	void EthMac::OnInterrupt()
	{
		if (READ_BIT(m_eth->DMASR, ETH_DMASR_RS))
		{
			//Loop through descriptors to find received packets
			for (size_t i = 0; i < EthMac::BufferCount; i++)
			{
				RxDmaDescriptor& desc = m_rxDescriptors[i];
				if (desc.TDES0.Own)
					continue;

				const Buffer buffer = { m_rxBuffers[i], desc.TDES0.FrameLength };
				if (FrameReceived.IsCallable())
					FrameReceived.Invoke(buffer);

				desc.TDES0.Own = 1;
			}

			//Clear
			SET_BIT(m_eth->DMASR, ETH_DMASR_RS);
		}

		//If DMA RX stopped because no buffers were available, restart it
		if (READ_BIT(m_eth->DMASR, ETH_DMASR_RBUS))
		{
			SET_BIT(m_eth->DMASR, ETH_DMASR_RBUS);
			SET_BIT(m_eth->DMARPDR, ETH_DMARPDR_RPD);
		}
	}
}
