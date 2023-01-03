#pragma once

struct Callback
{
	Callback() : Context(), Handler()
	{

	}

	bool IsCallable()
	{
		return Handler != nullptr;
	}

	void Invoke()
	{
		Handler(Context);
	}

	void* Context;
	void (*Handler)(void* sender);
};

template<class P>
struct ParamCallback
{
	ParamCallback() : Context(), Handler()
	{

	}

	bool IsCallable()
	{
		return Handler != nullptr;
	}

	void Invoke(P param)
	{
		Handler(Context, param);
	}

	void* Context;
	void (*Handler)(void* sender, P param);
};