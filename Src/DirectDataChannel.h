#pragma once

#include "DataChannel.h"

class DirectDataChannel : public DataChannel
{
public:
	DirectDataChannel() : DataChannel() {};

	virtual void* GetWriteAddress() = 0;
};