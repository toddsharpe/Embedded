#pragma once

#include "Buffer.h"
#include <cstdint>
#include <array>

template<class T, size_t N>
class RingBuffer
{
public:
	RingBuffer() :
		m_head(),
		m_tail(N - 1),
		m_count(),
		m_buffer()
	{

	}

	constexpr size_t Count()
	{
		return m_count;
	}

	constexpr size_t Size() const
	{
		return m_buffer.size();
	}

	constexpr bool IsFull() const
	{
		return m_buffer.size() == m_count;
	}

	constexpr bool IsEmpty() const
	{
		return m_count == 0;
	}

	bool Read(T& item)
	{
		if (m_count == 0)
			return false;
		
		m_count--;
		item = m_buffer[m_head];
		m_head = (m_head + 1) % m_buffer.size();
		return true;
	}

	bool CopyTo(Buffer& buffer)
	{
		//Check if theres enough room
		buffer.Count = m_count;
		if (m_count > buffer.Length)
			return false;

		//Loop through and read
		//TODO(tsharpe): Replace with 1 or 2 memcpys
		uint8_t* data = (uint8_t*)buffer.Data;
		for (size_t i = 0; i < m_count; i++)
		{
			if (!Read(data[i]))
				return false;
		}

		return true;
	}

	bool Write(const T item)
	{
		if (m_count == m_buffer.size())
			return false;

		m_tail = (m_tail + 1) % m_buffer.size();
		m_buffer[m_tail] = item;
		m_count++;
		return true;
	}

	void* Front()
	{
		return &m_buffer[m_head];
	}

private:
	size_t m_head;//Points to item to read
	size_t m_tail;//Points to last item
	size_t m_count;
	std::array<T, N> m_buffer;
};
