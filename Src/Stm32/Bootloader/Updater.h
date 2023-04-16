#pragma once

#include "Assert.h"
#include "Board.h"
#include "DataChannel.h"
#include "Stm32/System.h"
#include "OTA.h"
#include "Rtos/Kernel.h"
#include "Stm32/Flash.h"

using namespace OTA;
using namespace Rtos;
using namespace Stm32;

class Updater
{
public:
	static void OnDataReceived(void* arg, const size_t bytesAvailable) { ((Updater*)arg)->OnDataReceived(bytesAvailable); };

	Updater(Board& board, Kernel& kernel, DataChannel& channel) : m_board(board), m_kernel(kernel), m_channel(channel), m_state(State::Init), m_event()
	{
		m_channel.DataReceived.Context = this;
		m_channel.DataReceived.Handler = &Updater::OnDataReceived;
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
					Flash::Unlock();
					m_state = State::ErashFlash;
					break;

				case State::ErashFlash:
					Flash::EraseSector(SystemSectors::App1);
					Flash::EraseSector(SystemSectors::App2);
					m_state = State::GetAppData;
					break;

				case State::GetAppData:
					m_state = GetAppData(numberOfBlocks);
					break;

				case State::LockFlash:
					Flash::Lock();
					m_state = State::BootApp;
					break;

				case State::BootApp:
					m_state = BootApp();
					break;

				default:
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
		m_board.Printf("GetAppInfo\r\n");
		
		GetAppMessage request = {};
		request.Length = sizeof(GetAppMessage);
		request.Type = MessageType::GetApp;

		AppInfoMessage response = {};
		if (!SendAndReceive(request, response))
			return State::BootApp;

		AssertEqual(response.Type, MessageType::AppInfo);
		numberOfBlocks = response.NumberOfBlocks;
		m_board.Printf("Blocks: %d\r\n", numberOfBlocks);

		return State::UnlockFlash;
	}

	State GetAppData(uint16_t numberOfBlocks)
	{
		m_board.Printf("GetAppData\r\n");
		
		for (size_t i = 0; i < numberOfBlocks; i++)
		{
			m_board.Printf("  Block: %d ", i);
			
			GetDataBlockMessage request = {};
			request.Length = sizeof(GetDataBlockMessage);
			request.Type = MessageType::GetDataBlock;
			request.BlockNumber = i;

			DataBlockMessage response = {};
			if (!SendAndReceive(request, response))
				return State::Faulted;
			m_board.Printf("Received.\r\n");

			AssertEqual(response.Type, MessageType::DataBlock);

			//Write bytes
			const uintptr_t address = (uintptr_t)SystemMemoryMap::App + (i * sizeof(response.Data));
			const uint32_t* data = (uint32_t*)&response.Data[0];
			m_board.Printf("  Writing at 0x%x\r\n", address);
			for (size_t j = 0; j < sizeof(response.Data) / sizeof(uint32_t); j++)
			{
				Flash::WriteWord(address + j * sizeof(uint32_t), data[j]);
			}
		}

		return State::LockFlash;
	}

	State BootApp()
	{
		m_board.Printf("BootApp\r\n");
		ResetVectorTable* isr_vector = (ResetVectorTable*)SystemMemoryMap::App;
		if (isr_vector->Reset >= SystemMemoryMap::App && isr_vector->Reset < SystemMemoryMap::SysReserved)
		{
			//Stop existing kernel
			m_kernel.Stop();
			
			AppMain main = (AppMain)isr_vector->Reset;
			__set_MSP(isr_vector->InitialSP);
			main();
		}

		//Boot app failed
		m_board.Printf("App launch failed...\r\n");
		return State::Faulted;
	}

	template<class TSend, class TReceive>
	bool SendAndReceive(TSend& send, TReceive& receive)
	{
		m_channel.Write((uint8_t*)&send, send.Length);

		while (m_channel.BytesAvailable() < sizeof(TReceive))
		{
			WaitStatus status = m_kernel.KeWait(m_event, 5*1000);
			if (status == WaitStatus::Timeout)
			{
				m_board.Printf("SendAndReceive timeout\r\n");
				return false;
			}
		}
		m_channel.Read((uint8_t*)&receive, sizeof(TReceive));
		return true;
	}

	void OnDataReceived(const size_t bytesAvailable)
	{
		m_kernel.KeSignal(m_event);
	}

	Board& m_board;
	Kernel& m_kernel;
	DataChannel& m_channel;

	State m_state;
	KEvent m_event;
};
