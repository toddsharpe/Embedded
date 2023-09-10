// MAN: Docs\SiFive\fe310-g002-v1p5.pdf

#pragma once

#include "Assert.h"
#include "DgramChannel.h"
#include "StringPrinter.h"

#include <cstdint>
#include <SoC.h>

namespace SoC
{
	class Uart : public DgramChannel
	{
	public:
		static void OnInterrupt(void* arg);

		Uart(uart_block *uart);

		void Init();

		void Write(const std::string &string);
		virtual void Write(const ReadOnlyBuffer& buffer) override;
		virtual ReadOnlyBuffer Read() override;

	private:
		uart_block *m_uart;
	};
}
