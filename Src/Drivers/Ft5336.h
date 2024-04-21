#pragma once

namespace Drivers
{
	template <class TChannel>
	class Ft5336
	{
	public:
		Ft5336(TChannel& channel) : 
			m_channel(channel)
		{
			
		}

		void Init()
		{

		}

	private:
		static constexpr uint8_t Address = 0x70;

		enum Registers
		{
			ChipId = 0xA8
		};

		TChannel& m_channel;
	};
}
