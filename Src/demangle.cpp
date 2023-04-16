#include <cstdlib>
#include <cstring>

//Define demangle handler to avoid linking against libstdc++. Saves 23k.
extern "C" char *__cxa_demangle(const char *mangled_name, char *output_buffer, size_t *length, int *status)
{
	strcpy((char *)mangled_name, output_buffer);
	return output_buffer;
}