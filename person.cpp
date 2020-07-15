#include "person.h"


static void* initMemoryPool(size_t size)
{
    void *ptrToPool = ::operator new(sizeof(Person) * size);
    void *cur = ptrToPool;
    size_t i = 0;

    while (i < size - 1)
    {
        *(size_t *) cur = *(size_t *) cur + sizeof(Person);
        *(size_t *) cur += sizeof(Person);
        ++i;
    }
    
    *(size_t*)cur = NULL;

    return ptrToPool;
}


void* Person::s_pool = initMemoryPool(2);
void* Person::s_firstFree = Person::s_pool;


void* Person::getNextFreeBlock()
{
    void* ptrToHead = s_firstFree;

    *(size_t*)s_firstFree = *(char*)s_firstFree + sizeof(Person);
    
    if(*(size_t*)s_firstFree >= *(char*)s_pool + sizeof(Person) * 1)
    	return NULL;
    return ptrToHead;
}


