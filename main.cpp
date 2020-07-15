#include <iostream>

#include "person.h"

using std::cout;
using std::endl;

int main()
{
	Person *p = new Person("TovaSima", 123, 20);

	delete p;
	void *ptr;

	::operator delete (Person::s_pool);
			
    return 0;
}
