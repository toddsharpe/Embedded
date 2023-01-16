#pragma once

#include "Rtos/KSignalObject.h"

namespace Rtos
{
	//Object that never signals, for unconditionally sleeping threads
	class KSleep : public KSignalObject
	{
	public:
		KSleep() :
			KSignalObject(KObjectType::Sleep)
		{

		}

		virtual bool IsSignalled() const override
		{
			return false;
		}
	};
}
