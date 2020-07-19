#include "person.h"

int main()
{
	// MemoryPool is set to 3
	
	// Allocate 3 people
	Person *p1 = new Person();
	Person *p2 = new Person();
	Person *p3 = new Person();
	
	// Allocate impossible amount of memory (and dont manage!!!!)
	try
	{
		Person *p4 = new Person();
	}
	catch(std::bad_alloc &ba)
	{}
	
	// delete person and allocate another person
	delete p1;
	Person *p4 = new Person();
	
	
	// delete all people and clear memory
	delete p2;
	delete p3;
	delete p4;
	
	
    return 0;
}
