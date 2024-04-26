#pragma once

#include "Assert.h"
#include "Board.h"
#include "Arm.h"
#include "Stm32/System.h"
#include "OTA.h"
#include "Rtos/Kernel.h"
#include "Stm32/Flash.h"

using namespace OTA;
using namespace Rtos;
using namespace Stm32;

template<class TChannel>
class Updater
{
public:
	static void OnDataReceived(void* arg) { ((Updater*)arg)->OnDataReceived(); };

	Updater(TChannel& channel) :
		m_channel(channel),
		m_state(State::Init),
		m_event()
	{
		channel.DgramReceived.Context = this;
		channel.DgramReceived.Handler = &Updater::OnDataReceived;
	}

	void Run()
	{
		uint16_t numberOfBlocks = 0;

		while (m_state != State::Faulted)
		{
			switch (m_state)
			{
				case State::Init:
					m_state = State::GetAppInfo;
					break;
				
				case State::GetAppInfo:
					m_state = GetAppInfo(numberOfBlocks);
					break;

				case State::UnlockFlash:
					Board::Printf("UnlockFlash\r\n");
					Flash::Unlock();
					m_state = State::ErashFlash;
					break;

				case State::ErashFlash:
					Board::Printf("ErashFlash\r\n");
					Flash::EraseSector(Sectors::App1);
					m_state = State::GetAppData;
					break;

				case State::GetAppData:
					m_state = GetAppData(numberOfBlocks);
					break;

				case State::LockFlash:
					Board::Printf("LockFlash\r\n");
					Flash::Lock();
					m_state = State::BootApp;
					break;

				case State::BootApp:
					m_state = BootApp();
					break;

				case State::Faulted:
					Board::Printf("Faulted\r\n");
					break;

				default:
					Board::Printf("Updater::Run: Unknown state\r\n");
					break;
			}
		}
	}

private:
	enum class State
	{
		Init,
		GetAppInfo,
		UnlockFlash,
		ErashFlash,
		GetAppData,
		LockFlash,
		BootApp,
		Faulted
	};

	State GetAppInfo(uint16_t& numberOfBlocks)
	{
		Board::Printf("GetAppInfo\r\n");
		GetAppMessage request = {};
		request.Length = sizeof(GetAppMessage);
		request.Type = MessageType::GetApp;

		AppInfoMessage response = {};
		if (!SendAndReceive(request, response))
			return State::BootApp;

		AssertEqual(response.Type, MessageType::AppInfo);
		numberOfBlocks = response.NumberOfBlocks;
		Board::Printf("Blocks: %d\r\n", numberOfBlocks);

		return State::UnlockFlash;
	}

	State GetAppData(uint16_t numberOfBlocks)
	{
		Board::Printf("GetAppData\r\n");
		for (size_t i = 0; i < numberOfBlocks; i++)
		{
			Board::Printf("  Block: %d ", i);
			
			GetDataBlockMessage request = {};
			request.Length = sizeof(GetDataBlockMessage);
			request.Type = MessageType::GetDataBlock;
			request.BlockNumber = i;

			DataBlockMessage response = {};
			if (!SendAndReceive(request, response))
				return State::Faulted;

			AssertEqual(response.Type, MessageType::DataBlock);

			//Write bytes
			const uintptr_t address = (uintptr_t)Addresses::App + (i * sizeof(response.Data));
			const uint32_t* data = (uint32_t*)&response.Data[0];
			Board::Printf("Writing at 0x%x\r\n", address);
			for (size_t j = 0; j < sizeof(response.Data) / sizeof(uint32_t); j++)
			{
				Flash::WriteWord(address + j * sizeof(uint32_t), data[j]);
			}
		}

		return State::LockFlash;
	}

	State BootApp()
	{
		Board::Printf("BootApp\r\n");
		ResetVectorTable* isr_vector = (ResetVectorTable*)Addresses::App;
		if (isr_vector->Reset >= Addresses::App && isr_vector->Reset < FlashEnd)
		{
			//Stop existing kernel
			Rtos::Stop();
			__disable_irq();
			
			AppMain main = (AppMain)isr_vector->Reset;
			__set_MSP(isr_vector->InitialSP);
			main();
		}

		//Boot app failed
		Board::Printf("App launch failed...\r\n");
		return State::Faulted;
	}

	template<class TSend, class TReceive>
	bool SendAndReceive(TSend& send, TReceive& receive)
	{
		m_channel.Write({&send, send.Length});

		//Wait for dgram
		WaitStatus status = Rtos::KeWait(m_event, 5 * 1000);
		if (status == WaitStatus::Timeout)
		{
			Board::Printf("SendAndReceive timeout\r\n");
			return false;
		}

		const ReadOnlyBuffer buffer = m_channel.Read();
		AssertEqual(buffer.Length, sizeof(TReceive));
		memcpy(&receive, buffer.Data, buffer.Length);

		return true;
	}

	void OnDataReceived()
	{
		Rtos::KeSignal(m_event);
	}

	TChannel& m_channel;
	State m_state;
	KEvent m_event;
};
