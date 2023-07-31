#pragma once

#include <cstdint>
#include "Rtos/KSignalObject.h"

namespace Rtos
{
	//Count decremented each time thread completes a wait
	//Incremented each time thread releases
	//When coult is 0, threads block
	class KSemaphore : public KSignalObject
	{
	public:
		KSemaphore(const uint32_t initial, const uint32_t maximum) :
			KSignalObject(KObjectType::Semaphore),
			m_value(initial),
			m_limit(maximum)
		{

		}

		//Returns post-decrement value
		size_t Wait(const size_t count)
		{
			//Decrement
			m_value -= count;

			return m_value;
		}

		//Returns pre-increment value
		size_t Signal(const size_t count)
		{
			size_t ret = m_value;
			m_value += count;

			return ret;
		}

		virtual bool IsSignalled() const override
		{
			return m_value > 0;
		}

	private:
		size_t m_value;
		size_t m_limit;
	};
}
