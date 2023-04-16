// MAN: Docs\SiFive\fe310-g002-v1p5.pdf

#pragma once

#include "Assert.h"
#include "DataChannel.h"
#include "StringPrinter.h"

#include <cstdint>
#include <SoC.h>

namespace SoC
{
	class Uart : public DataChannel, public StringPrinter
	{
	public:
		static void OnInterrupt(void* arg);

		Uart(uart_block *uart);

		void Init();

		void Write(const std::string &string);
		virtual void Write(const uint8_t *buffer, size_t length) override;

		virtual void Read(uint8_t *buffer, size_t length) override;

		virtual size_t BytesAvailable() override;

	private:
		uart_block *m_uart;
	};
}
