#include <cstdlib>

void * operator new(size_t n)
{
	void* p = std::malloc(n);

	return p;
}

void operator delete(void * p)
{
	std::free(p);
}
