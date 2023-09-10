#pragma once

#include "Sys/EthMac.h"
#include "Net/Net.h"
#include <stm32f746xx.h>
#include <cstddef>

//MAN: rm0385-stm32f75xxx-and-stm32f74xxx-advanced-armbased-32bit-mcus-stmicroelectronics.pdf

namespace Stm32
{
	//MAN: 38.6, Page 1570. Chain implementation.
	//TODO(tsharpe): Convert to ring?
	class EthMac : public Sys::EthMac
	{
	public:
		static constexpr size_t BufferCount = 4;
		static constexpr size_t BufferSize = 1518;
		static void OnInterrupt(void* arg) { ((EthMac*)arg)->OnInterrupt(); };

		EthMac(ETH_TypeDef* eth, uint8_t (&txBuffers)[EthMac::BufferCount][EthMac::BufferSize], uint8_t (&rxBuffers)[EthMac::BufferCount][EthMac::BufferSize]);
		
		void Init();
		virtual void Send(const ReadOnlyBuffer& frame) override;
		virtual void Display() override;

	private:
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
		
		void OnInterrupt();

		ETH_TypeDef* m_eth;

		//Tx DMA
		size_t m_txIndex;
		TxDmaDescriptor m_txDescriptors[BufferCount];
		uint8_t (&m_txBuffers)[EthMac::BufferCount][EthMac::BufferSize];

		//Rx DMA
		RxDmaDescriptor m_rxDescriptors[BufferCount];
		uint8_t (&m_rxBuffers)[EthMac::BufferCount][EthMac::BufferSize];
	};
}
