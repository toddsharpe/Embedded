#pragma once

class Event
{
public:
	Event(bool initialState = false) : m_state(initialState)
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

	bool IsSignalled()
	{
		return m_state;
	}

	void WaitFor()
	{
		while (!IsSignalled())
			__WFI();
	}

private:
	bool m_state;
};