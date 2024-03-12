#pragma once

//TODO(tsharpe): Convert to std::function/bind paradigm
struct Callback
{
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