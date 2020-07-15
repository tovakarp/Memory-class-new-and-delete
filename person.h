#ifndef __PERSON_H__
#define __PERSON_H__

#include <iostream>
#include <cstddef>
#include <cstring>

class Person
{
public:
	Person(const char *name, unsigned int id, unsigned char age);
	
    static void *s_pool;
    static void *s_firstFree;

    /* throwing */	void* operator new ( size_t count );
	/* no-throw */	void* operator new (std::size_t size, const std::nothrow_t& nothrow_value) throw();	
	/* placement */	void* operator new (std::size_t size, void* ptr) throw();
	
    /* ordinary */	void operator delete  ( void* ptr ) throw();		
	/* no-throw */	void operator delete (void* ptr, const std::nothrow_t& nothrow_constant) throw();	
	/* placement */	void operator delete (void* ptr, void* voidptr2) throw();
	
private:
    char m_name[32];
    unsigned int m_id;
    unsigned char m_age;
	
	static void* getNextFreeBlock();
	
    /* throwing */	void* operator new [] ( size_t count );
	/* no-throw */	void* operator new [] (std::size_t size, const std::nothrow_t& nothrow_value) throw();	
	/* placement */	void* operator new [] (std::size_t size, void* ptr) throw();
    
    /* ordinary */	void operator delete [] ( void* ptr ) throw();		
	/* no-throw */	void operator delete [] (void* ptr, const std::nothrow_t& nothrow_constant) throw();	
	/* placement */	void operator delete [] (void* ptr, void* voidptr2) throw();
};

inline Person::Person(const char *name, unsigned int id, unsigned char age):
	m_id(id), 
	m_age(age)
{
    strcpy(m_name, name);
}



inline void* Person::operator new (size_t count)
{
	 //std::cout << "here\n";
    if (!s_firstFree)
    {
    	//std::cout << "could not allocate\n";
        throw std::bad_alloc();
    }

    return getNextFreeBlock();
}


inline void* Person::operator new (std::size_t size, const std::nothrow_t& nothrow_value) throw()
{
    if (!s_firstFree)
    {
        return NULL;
    }

    return getNextFreeBlock();
}


inline void* Person::operator new (std::size_t size, void* ptr) throw()
{
    return ptr;
}


inline void Person::operator delete (void* ptr) throw()
{
    if (!ptr)
    {
        return;
    }

    *(size_t*)ptr = *(size_t*)s_firstFree;
    s_firstFree = ptr;
}


inline void Person::operator delete (void* ptr, const std::nothrow_t& nothrow_constant) throw()
{
    operator delete(ptr);
}


inline void Person::operator delete (void* ptr, void* voidptr2) throw()
{}

#endif //__PERSON_H__
