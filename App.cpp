#include "SortedBag.h"
#include "SortedBagIterator.h"
#include <iostream>
#include "ShortTest.h"
#include "ExtendedTest.h"
#include <cassert>

using namespace std;

void testAddAll()
{
	cout << "Test add all" << endl;
	SortedBag b1{ relation1 }, b2{ relation1 };
	for (int i = 1; i <= 100; i++)
	{
		b1.add(i);
		b2.add(i);
		b2.add(i + 100);
	}
	b1.addAll(b2);
	SortedBagIterator it = b1.iterator();
	int i = 1;
	while (it.valid())
	{
		TComp current = it.getCurrent();
		assert(current = i);
		it.next();
		if (i <= 100)
		{
			current = it.getCurrent();
			assert(current == i);
			it.next();
		}
		i++;
	}
}

int main() {
	testAll();
	testAllExtended();
	testAddAll();
	
	cout << "Test over" << endl;
	system("pause");
}
