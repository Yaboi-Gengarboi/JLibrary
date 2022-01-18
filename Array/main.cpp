// Array
// main.cpp
// Created on 2022-01-14 by Justyn Durnford
// Last modified on 2022-01-14 by Justyn Durnford
// Test file for the Array template class.

import Array;

#include <cstddef>
using std::size_t;

#include <iostream>
using std::cout;
using std::endl;

template <typename T>
void print_array(const jlib::Array<T>& arr)
{
	const size_t len = arr.size() - 1;
	cout << "{ ";

	for (size_t i = 0; i < len; ++i)
		cout << arr[i] << ", ";

	cout << arr[len] << " }" << endl;
}

template <typename T>
void print_array_address(const jlib::Array<T>& arr)
{
	cout << arr.data() << endl;
}

int main()
{
	return 0;
}