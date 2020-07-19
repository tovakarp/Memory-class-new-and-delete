#ifndef __PERSON_H__
#define __PERSON_H__

#include <new>		// for std::nothrow_t
#include <cstring>

class Person
{
public:
	Person(const char *name = "", unsigned int id = 0, unsigned char age = 0);

    /* throwing */	void* operator new ( size_t count );
	/* no-throw */	void* operator new (std::size_t size, const std::nothrow_t& nothrow_value) throw();	
	/* placement */	void* operator new (std::size_t size, void* ptr) throw();
	
    /* ordinary */	void operator delete  ( void* ptr ) throw();		
	/* no-throw */	void operator delete (void* ptr, const std::nothrow_t& nothrow_constant) throw();	
	/* placement */	void operator delete (void* ptr, void* voidptr2) throw();
	
private:		
    static char s_pool[];
    static void *s_firstFree;

    char m_name[32];
    unsigned int m_id;
    unsigned char m_age;

	
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
    memcpy(m_name, name, 32);
}



inline void* Person::operator new (size_t count)
{
    if (!s_firstFree) 
    {
        throw std::bad_alloc();
    }
	
	void* freeBlock = s_firstFree;
	s_firstFree = *reinterpret_cast<Person**>(s_firstFree);
	
    return freeBlock;
}


inline void* Person::operator new (std::size_t size, const std::nothrow_t& nothrow_value) throw()
{
    if (!s_firstFree)
    {
        return NULL;
    }

    void* freeBlock = s_firstFree;
	s_firstFree = *reinterpret_cast<Person**>(s_firstFree);
	
    return freeBlock;
}


inline void* Person::operator new (std::size_t size, void* ptr) throw()
{
    return ptr;
}


inline void Person::operator delete (void* ptr) throw()
{
    if (ptr)
    {
        *reinterpret_cast<Person**>(ptr) = (Person*)s_firstFree;
    	s_firstFree = ptr;
    }
}



inline void Person::operator delete (void* ptr, const std::nothrow_t& nothrow_constant) throw()
{
    operator delete(ptr);
}


inline void Person::operator delete (void* ptr, void* voidptr2) throw()
{}



#endif //__PERSON_H__
