#include "SortedBagIterator.h"
#include "SortedBag.h"
#include <exception>
#include <algorithm>

using namespace std;

SortedBagIterator::SortedBagIterator(const SortedBag& b) : bag(b)
{
	for (int i = 0; i < this->bag.cap; i++)
	{
		SortedBag::Node* current = this->bag.buckets[i];
		while (current != nullptr)
		{
			for (int k = 0; k < current->freq; k++)
			{
				this->vec.push_back(current->elem);
			}
			current = current->next;
		}
	}
	sort(this->vec.begin(), this->vec.end(),
		[this](const TComp& a, const TComp& b)
		{
			return this->bag.rel(a, b);
		});
	this->first();
}

TComp SortedBagIterator::getCurrent()
{
	if (!this->valid())
		throw exception();
	return (*this->it);
}

bool SortedBagIterator::valid()
{
	return this->it != this->vec.end();
}

void SortedBagIterator::next()
{
	if (!this->valid())
		throw exception();
	it++;
}

void SortedBagIterator::first()
{
	this->it = this->vec.begin();
}

