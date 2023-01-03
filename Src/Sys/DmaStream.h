#pragma once

#include "Callback.h"

#include <cstddef>

namespace Sys
{
	class DmaStream
	{
	public:
		static void OnInterrupt(void* arg) { ((DmaStream*)arg)->OnInterrupt(); };
		static constexpr size_t MaxTransfer = (1 << 16) - 1;

		DmaStream() : TransferError(), TransferComplete() {};

		virtual void Start(const void* source, const void* destination, const size_t length) = 0;

		Callback TransferError;
		Callback TransferComplete;

	private:
		virtual void OnInterrupt() = 0;
	};
}