#pragma once

#include "Rtos/KSignalObject.h"

namespace Rtos
{
	class KEvent : public KSignalObject
	{
	public:
		KEvent(bool manualReset = false, bool initialState = false) :
			KSignalObject(KObjectType::Event),
			m_manualReset(manualReset),
			m_state(initialState)
		{

		}

		void Set()
		{
			m_state = true;
		}

		void Reset()
		{
			m_state = false;
		}

		bool IsManual()
		{
			return m_manualReset;
		}

		virtual bool IsSignalled() const override
		{
			return m_state;
		}

	private:
		bool m_manualReset;
		//Commonly modified during interrupt, so make it volatile
		volatile bool m_state;
	};
}
