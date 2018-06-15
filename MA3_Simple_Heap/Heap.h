//***************************************************************************//
//**
//**  Simple Heap implementation - With solution
//**    Copyright 2016 - Aaron S. Crandall
//**
//**
//***************************************************************************//

#ifndef HEAP_H
#define HEAP_H

#include <vector>
#include <stdexcept>      // std::out_of_range
using namespace std;

template<typename T>
class Heap
{
private:
	vector<T> _items;

	void buildHeap()
	{
		for (int i = _items.size()/2; i >= 0; i--)
		{
			adjustHeap(i);
		}
	}


	//MA TODO: Implement adjustHeap!
	//Percolates the item specified at by index down into its proper location within a heap.
	// Used for dequeue operations and array to heap conversions
	void adjustHeap(int index)
	{
		// The ONLY code you'd need to do for this MA would be in this function call
		int child;
		T tmp = std::move(_items[index]);
		int current_position = _items.size();
		for (; index * 2 <= current_position; index = child)
		{
			if (index == 0) child = 1;
			else child = index * 2;
			if (child != current_position && _items[child + 1] < _items[child])
				++child;
			if (_items[child] < tmp)
				_items[index] = std::move(_items[child]);
			else
				break;
		}
		_items[index] = tmp;
	}


public:
	Heap()
	{
	}

	Heap(const vector<T> &unsorted)
	{
		for (int i = 0; i < unsorted.size(); i++)
		{
			_items.push(unsorted[i]);
		}
		buildHeap();
	}

	//Adds a new item to the heap
	void insert(T item)
	{

		//calculate positions
		int current_position = _items.size();
		int parent_position = (current_position - 1) / 2;

		//insert element (note: may get erased if we hit the WHILE loop)
		_items.push_back(item);

		//get parent element if it exists
		T *parent = NULL;
		if (parent_position >= 0)
		{
			parent = &_items[parent_position];
		}

		//only continue if we have a non-null parent
		if (parent != NULL)
		{
			//bubble up
			while (current_position > 0 && item < *parent)
			{
				_items[current_position] = *parent;
				current_position = parent_position;
				parent_position = (current_position - 1) / 2;
				if (parent_position >= 0)
				{
					parent = &_items[parent_position];
				}
			}

			//after finding the correct location, we can finally place our item
			_items[current_position] = item;
		}
	}


	//Returns the top-most item in our heap without actually removing the item from the heap
	T& getFirst()
	{
		if( size() > 0 )
			return _items[0];
		else
			throw std::out_of_range("No elements in Heap.");
	}


	//Removes the top-most item from the heap and returns it to the caller
	T deleteMin()
	{
		int last_position = _items.size() - 1;
		T last_item = _items[last_position];
		T top = _items[0];
		_items[0] = last_item;
		_items.erase(_items.begin() + last_position);

		//percolate down
		adjustHeap(0);
		return top;
	}


	// Returns true if heap is empty, false otherwise
	bool isEmpty() const
	{
		return _items.size() == 0;
	}


	// Return size (N) of the Heap
	int size() const
	{
		return _items.size();
	}

	// Simple debugging print out
	void printAll() const
	{
     		for(int i = 0; i < _items.size(); i++)
     		{
          		cout << "  [x] Heap element [" << i << "]. key=" << _items[i] << endl;
     		}
	}
};

#endif
