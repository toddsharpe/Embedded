#pragma once

#include "Channel.h"
#include <Windows.h>
#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers

namespace Windows
{
	class SerialChannel : public Channel
	{
	public:
		SerialChannel();

		virtual void Init() override;

		virtual void Write(const void* buffer, const size_t count) override;
		virtual size_t Read(void* buffer, const size_t count) override;

	private:
		HANDLE m_handle;
	};
}

