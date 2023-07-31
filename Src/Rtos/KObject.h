#pragma once

namespace Rtos
{
	enum class KObjectType
	{
		Semaphore,
		Event,
		Sleep
	};

	class KObject
	{
	public:
		KObject(const KObjectType type) :
			m_type(type)
		{

		}

		KObjectType GetType() const
		{
			return m_type;
		}

	private:
		const KObjectType m_type;
	};
}
