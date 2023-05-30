// MAN: Docs\SiFive\fe310-g002-v1p5.pdf

#pragma once

#include "Assert.h"
#include "DataChannel.h"
#include "StringPrinter.h"
#include "RingBuffer.h"

#include <cstdint>
#include <FE310.h>

namespace HiFive
{
	struct UartConfig
	{
		uint32_t BaudRate;
	};

	static constexpr UartConfig const UartDefault = { .BaudRate = 115200 };

	//NOTE(tsharpe): Default values - txctrl: 0x1001, rxctrl: 0x01, div: 0x8A
	class Uart : public DataChannel, public StringPrinter
	{
	public:
		static void OnInterrupt(void* arg);

		Uart(UART0_Type *uart);

		void Init(const uint32_t clkFreq, const UartConfig& config);

		void Write(const std::string &string);
		virtual void Write(const uint8_t *buffer, size_t length) override;

		virtual void Read(uint8_t *buffer, size_t length) override;

		virtual size_t BytesAvailable() override;

		void EnableInterrupt();

		void OnInterrupt();

	private:
		static constexpr size_t BUFFER_SIZE = 1024;

		UART0_Type *m_uart;
		RingBuffer<uint8_t, BUFFER_SIZE> m_buffer;
	};
}
