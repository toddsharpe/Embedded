#pragma once

namespace Sys
{
	class GpioPin
	{
	public:
		virtual void Set(bool value) = 0;

		virtual bool Get() = 0;

		virtual bool Read() = 0;
		
		void Toggle()
		{
			Set(!Get());
		}
	};
}
