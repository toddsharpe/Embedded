#pragma once

void Bugcheck(const char* file, const char* line, const char* format, ...);

#define STR_HELPER(x) #x
#define STR(x) STR_HELPER(x)
#define Assert(x) if (!(x)) { Bugcheck("File: " __FILE__, "Line: " STR(__LINE__),  #x); }
#define AssertPrintHex32(x, y) \
	if (!(x)) \
	{ \
		Bugcheck("File: " __FILE__, "Line: " STR(__LINE__), "Assert Failed: %s,\r\n%s=0x%08x\r\n", #x, #y, y); \
	}
#define AssertEqual(x, y) \
	if (!(x == y)) \
	{ \
		Bugcheck("File: " __FILE__, "Line: " STR(__LINE__), #x " (0x%x) != " #y " (0x%x)", x, y); \
	}
#define AssertNotEqual(x, y) \
	if (!(x != y)) \
	{ \
		Bugcheck("File: " __FILE__, "Line: " STR(__LINE__), #x " (0x%x) != " #y " (0x%x)", x, y); \
	}
#define AssertOp(x, op, y) \
	{ \
		const size_t X = (x); \
		const size_t Y = (y); \
		if (!(X op Y)) \
		{ \
			Bugcheck("File: " __FILE__, "Line: " STR(__LINE__), #x " (0x%x) " STR(op) " " #y " (0x%x)", X, Y); \
		} \
	}
#define Fatal(x) Bugcheck("File: " __FILE__, "Line: " STR(__LINE__),  #x); 
#define Trace() Board::Printf(__FILE__ "-" STR(__LINE__));
