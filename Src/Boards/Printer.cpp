#include "Assert.h"
#include "Board.h"
#include <string>
#include <cstring>
#include <cstdarg>

namespace Board
{
	void PrintfVA(const char* format, va_list args)
	{
		char buffer[255];

		int retval = vsnprintf(buffer, sizeof(buffer), format, args);
		size_t ret = static_cast<size_t>(retval);
		Assert(ret < sizeof(buffer));
		buffer[retval] = '\0';

		Board::Write({buffer, ret});
	}

	void Printf(const char* format, ...)
	{
		va_list args;
		va_start(args, format);
		PrintfVA(format, args);
		va_end(args);
	}

	void PrintBytes(const char* buffer, const size_t length)
	{
		const uint32_t width = 16;
		
		//Print headers
		Printf("A: 0x%016x S: 0x%016x\r\n", buffer, length);
		Printf("---- ");
		for (size_t i = 0; i < width; i++)
		{
			Printf("%02x ", (unsigned char)i);
		}
		Printf("\r\n");

		char line[width] = { 0 };
		for (size_t i = 0; i < length; i++)
		{
			if (i != 0 && i % width == 0)
			{
				//Print characters
				Printf(" | ");
				for (const auto c : line)
				{
					Printf("%c", isprint(c) ? c : '.');
				}

				memset(line, 0, width);
				Printf("\r\n");
			}

			if (i % width == 0)
				Printf("%02x - ", (i / width) << 4);

			Printf("%02x ", (unsigned char)buffer[i]);
			line[i % width] = (unsigned char)buffer[i];
		}

		//Print the rest of the line
		if ((length % width) != 0)
			for (size_t i = 0; i < width - (length % width); i++)
			{
				Printf("   ");
			}

		//Print characters
		Printf(" | ");
		for (size_t i = 0; i < (length % width); i++)
		{
			char c = line[i];
			Printf("%c", isprint(c) ? c : '.');
		}

		Printf("\r\n");
	}
}
