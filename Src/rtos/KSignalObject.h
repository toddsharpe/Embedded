#pragma once

#include "Rtos/KObject.h"

namespace Rtos
{
	class KSignalObject : public KObject
	{
	public:
		KSignalObject(const KObjectType type) :
			KObject(type)
		{

		}

		virtual bool IsSignalled() const = 0;
	};
}
