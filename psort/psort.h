#ifndef _PSORT_H_
#define _PSORT_H_

#include <iostream>
#include <vector>
#include <omp.h>

using std::vector;

namespace ParallelSort
{
	template <class T>
	void psort(vector<T>* array);

	template <class T>
	void psort(vector<T>* array, int left, int right);
	
	template <class T>
	void insertionSort(vector<T>* array, int left, int right);

	template <class T>
	void build_maxheap(vector<T>* a, int left, int n);

	template <class T>
	void max_heapify(vector<T>* a, int i, int n);

	template <class T>
	void heapsort(vector<T>* a, int left, int right);
}

#include "psort.cpp"
#endif
