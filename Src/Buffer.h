#pragma once

#include <cstdint>
#include <cstddef>
#include <cstring>

struct ReadOnlyBuffer
{
	const void* Data;
	size_t Length;
};

struct Buffer
{
	Buffer() :
		Data(nullptr),
		Count(0),
		Length(0)
	{

	}

	operator ReadOnlyBuffer() const
	{
		return { Data, Count };
	}

	bool CopyFrom(const ReadOnlyBuffer& from)
	{
		if (from.Length > Length)
			return false;

		memcpy(Data, from.Data, from.Length);
		Count = from.Length;
		return true;
	}
	
	void* Data;
	size_t Count;
	size_t Length;
};

template <size_t TSize>
struct StaticBuffer : public Buffer
{
public:
	StaticBuffer() :
		Buffer()
	{
		Data = m_buffer;
		Count = 0;
		Length = TSize;
	}

private:
	uint8_t m_buffer[TSize];
};
