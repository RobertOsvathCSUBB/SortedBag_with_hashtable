#include "SortedBag.h"
#include "SortedBagIterator.h"
#include <cmath>

SortedBag::SortedBag(Relation r) : rel(r)
{
	this->cap = 11;
	this->buckets = new Node*[this->cap];
	for (int i = 0; i < this->cap; i++)
		this->buckets[i] = nullptr;
	this->totalSize = 0;
}

// Theta(1)
int SortedBag::hash(TComp e) const
{
	return std::abs(e % this->cap);
}

// Worst case: every element is in the bucket of e -> Theta(totalSize)
// Best case: the bucket of e is empty -> Theta(1)
// Total case: O(totalSize)
void SortedBag::add(TComp e)
{
	int hashIndex = this->hash(e);
	Node* current = this->buckets[hashIndex];
	Node* previous = nullptr;
	while (current != nullptr && (this->rel(current->elem, e) || current->elem == e))
	{
		if (current->elem == e)
		{
			current->freq++;
			this->totalSize++;
			return;
		}
		previous = current;
		current = current->next;
	}

	Node* newNode = new Node(e);
	if (previous == nullptr)
	{
		newNode->next = this->buckets[hashIndex];
		this->buckets[hashIndex] = newNode;
	}
	else
	{
		previous->next = newNode;
		newNode->next = current;
	}

	this->totalSize++;
}

// Worst case: every element is in the bucket of e and e is at the 
//							end of the sll -> Theta(totalSize)
// Best case: the element on the first position in its bucket, or is not 
//				found in the bag -> Theta(1)
// Total case: O(totalSize)
bool SortedBag::remove(TComp e)
{
	int hash = this->hash(e);
	Node* current = this->buckets[hash];
	Node* previous = nullptr;
	while (current != nullptr)
	{
		if (current->elem == e)
		{
			if (current->freq > 1)
			{
				current->freq--;
				this->totalSize--;
				return true;
			}
			if (previous != nullptr)
				previous->next = current->next;
			else
				this->buckets[hash] = current->next;
			delete current;
			this->totalSize--;
			return true;
		}
		previous = current;
		current = current->next;
	}
	return false;
}

// Worst case: every element is in the bucket of e and e is at the 
//							end of the sll -> Theta(totalSize)
// Best case: the element on the first position in its bucket, or is not 
//				found in the bag -> Theta(1)
// Total case: O(totalSize)
bool SortedBag::search(TComp e) const
{
	int hash = this->hash(e);
	Node* current = this->buckets[hash];
	while (current != nullptr)
	{
		if (current->elem == e)
			return true;
		current = current->next;
	}
	return false;
}

// Worst case: every element is in the bucket of e and e is at the 
//							end of the sll -> Theta(totalSize)
// Best case: the element on the first position in its bucket, or is not 
//				found in the bag -> Theta(1)
// Total case: O(totalSize)
int SortedBag::nrOccurrences(TComp e) const
{
	int hash = this->hash(e);
	Node* current = this->buckets[hash];
	while (current != nullptr)
	{
		if (current->elem == e)
			return current->freq;
		current = current->next;
	}
	return 0;
}

// Theta(1)
int SortedBag::size() const 
{
	return this->totalSize;
}

// Theta(1)
bool SortedBag::isEmpty() const 
{
	return this->totalSize == 0;
}

SortedBagIterator SortedBag::iterator() const
{
	return SortedBagIterator(*this);
}

SortedBag::~SortedBag() 
{
	for (int i = 0; i < this->cap; i++)
	{
		Node* current = this->buckets[i];
		Node* next = nullptr;
		while (current != nullptr)
		{
			next = current->next;
			delete current;
			current = next;
		}
	}
}

// Worst case: every add operation is Theta(totalSize of this bag)
//				-> Theta(totalSize of b * totalSize of this bag)
// Best case: every add operation is Theta(1) -> Theta(totalSize of b)
// Total cas: O(totalSize of b * totalSize of this bag)
void SortedBag::addAll(const SortedBag& b)
{
	SortedBagIterator it = b.iterator();
	while (it.valid())
	{
		TComp current = it.getCurrent();
		this->add(current);
		it.next();
	}
}