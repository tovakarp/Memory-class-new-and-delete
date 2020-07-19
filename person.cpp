#include "person.h"

static const size_t size = 3;

inline void* initFreeList(void *pool)
{
	Person *cur = (Person*)pool;
	
	size_t i = 0;
	
	while (i++ < size - 1)
	{
		*reinterpret_cast<Person**>(cur) = cur + 1;
		++cur;
	}
	
	*reinterpret_cast<Person**>(cur) = NULL;
	
	return pool;
}

char Person::s_pool[sizeof(Person) * size];
void* Person::s_firstFree = initFreeList(Person::s_pool);

