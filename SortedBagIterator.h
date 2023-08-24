#pragma once
#include "SortedBag.h"
#include <vector>

class SortedBag;

class SortedBagIterator
{
	friend class SortedBag;

private:
	const SortedBag& bag;
	SortedBagIterator(const SortedBag& b);

	std::vector<TComp> vec;
	std::vector<TComp>::iterator it;

public:
	TComp getCurrent();
	bool valid();
	void next();
	void first();
};

