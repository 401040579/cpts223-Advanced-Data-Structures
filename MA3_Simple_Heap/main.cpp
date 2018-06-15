//***************************************************************************//
//**
//**  Simple Heap implementation
//**    Copyright 2016 - Aaron S. Crandall
//**
//**
//**
//***************************************************************************//

#include <iostream>
#include <string>
#include "Heap.h"

void heapTests()
{
	Heap<int> myHeap;

	// Add some items to build a heap
	myHeap.insert(890);
	myHeap.insert(567);
	myHeap.insert(456);
	myHeap.insert(921);
	myHeap.insert(678);
	myHeap.insert(123);
	myHeap.insert(234);
	myHeap.insert(345);
	myHeap.insert(750);

	// This will build a heap that looks like this:
	//                    123 
	//                   /   \
	//                345     234 
	//                / \     / \
	//              678 890 567 456 
	//              / \
	//            921 750


	cout << " [x] Current elements in the heap: " << endl;
	myHeap.printAll();
	cout << " [x] Beginning to remove elements from the heap: " << endl;
	cout << "  [x] Once adjustHeap is implemented (properly) these deleteMin calls will come in low->high order." << endl;
	while (myHeap.isEmpty() == false)
	{
		int top = myHeap.deleteMin();
		cout << "  [x] deleteMin top: " << top << endl;
	}

	cout << " [x] Done. " << endl;
}

int main(int argc, char* argv[])
{
	heapTests();
}
