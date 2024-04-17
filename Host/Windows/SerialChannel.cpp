#include "SerialChannel.h"

#include <Assert.h>

SerialChannel::SerialChannel() :
	m_handle()
{

}

void SerialChannel::Init()
{
	m_handle = CreateFileA("COM4",
		GENERIC_READ | GENERIC_WRITE,
		0,
		NULL,
		OPEN_EXISTING,
		0,
		NULL);

	Assert(m_handle != INVALID_HANDLE_VALUE);
}

void SerialChannel::Write(const void* buffer, const size_t count)
{
	DWORD bytesWritten = 0;
	Assert(WriteFile(m_handle, buffer, count, &bytesWritten, NULL));
	Assert(count == bytesWritten);
}

size_t SerialChannel::Read(void* buffer, const size_t count)
{
	DWORD bytesRead = 0;
	Assert(ReadFile(m_handle, buffer, count, &bytesRead, NULL));
	return bytesRead;
}
