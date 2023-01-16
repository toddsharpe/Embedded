#pragma once

#include <cstdint>

namespace Graphics
{
	struct RGB565
	{
		union
		{
			struct
			{
				uint16_t Red : 5;
				uint16_t Green : 6;
				uint16_t Blue : 5;
			};
			uint16_t AsUint16;
		};
	};
	static_assert(sizeof(RGB565) == sizeof(uint16_t), "Invalid color struct");
	typedef RGB565 Color;

	namespace Colors
	{
		//To support 16bit transfers, colors were converted to little endian, bytes reversed.
		static constexpr Color White = {.AsUint16 = 0xFFFF };
		static constexpr Color Black = {.AsUint16 = 0x0000 };
		static constexpr Color Blue = {.AsUint16 = 0x1F00 };
		static constexpr Color Red = {.AsUint16 = 0x00F8 };
		static constexpr Color Magenta = {.AsUint16 = 0x1FF8 };
		static constexpr Color Green = {.AsUint16 = 0xE007 };
		static constexpr Color Cyan = {.AsUint16 = 0xFF7F };
	}
}
