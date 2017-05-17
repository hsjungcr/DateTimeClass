//-----------------------------------------------------------------------------
//	File: ArraySort.h
//	Using pure pointers and no indices will be implemented in re-submit
//
//	functions:
//	void quickSort(Comparable** arr, int from, int to);
//	int partition(Comparable** arr, int from, int to);
//	void SortFirstMiddleLast(Comparable** arr, int from, int mid, int to);
//	void insertionSort(Comparable** arr, int from, int to);
//	void safeRead(istream& sin, Comparable* d, const char* prompt);
//	void printArray(ostream & sout, Comparable **a, int size);
//	void swap(Comparable*& a, Comparable* &b);
//-----------------------------------------------------------------------------
#ifndef ARRAYSORT_H
#define ARRAYSORT_H
#include <iostream>
#include "DateTime.h"
using namespace std;
using namespace HJ_DATETIME;
//----------------------------------------------------------------------------
// One of two choices for format of these function
// This set uses pointers in the way that the STL uses iterators
//----------------------------------------------------------------------------
namespace HJ_ARRAYSORT
{
	void quickSort(Comparable** arr, int from, int to);
	int partition(Comparable** arr, int from, int to);
	void SortFirstMiddleLast(Comparable** arr, int from, int mid, int to);
	void insertionSort(Comparable** arr, int from, int to);
	void safeRead(istream& sin, Comparable* d, const char* prompt);
	void printArray(ostream & sout, Comparable **a, int size);
	void swap(Comparable*& a, Comparable* &b);
}
#endif