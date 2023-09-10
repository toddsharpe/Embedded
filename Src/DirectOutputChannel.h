#pragma once

#include "OutputChannel.h"

class DirectOutputChannel : public OutputChannel
{
public:
	DirectOutputChannel() :
		OutputChannel()
	{
		
	};

	virtual void* GetWriteAddress() = 0;
};
