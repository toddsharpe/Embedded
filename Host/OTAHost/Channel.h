#pragma once
class Channel
{
public:
	virtual void Init() = 0;
	virtual void Write(const void* Buffer, const size_t count) = 0;
	virtual size_t Read(void* Buffer, const size_t count) = 0;
};

