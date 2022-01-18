// FixedArray
// main.cpp
// Created on 2022-01-14 by Justyn Durnford
// Last modified on 2022-01-14 by Justyn Durnford
// Test file for the FixedArray template class.

import FixedArray;

#include <array>
#include <iostream>

template <typename T, std::size_t N>
void print_array(const jlib::FixedArray<T, N>& arr)
{
	std::cout << "{ ";

	for (std::size_t i = 0; i < N - 1; ++i)
		std::cout << arr[i] << ", ";

	std::cout << arr[N - 1] << " }" << std::endl;
}

int main()
{
	jlib::FixedArray<int, 10> arr1{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

	print_array(arr1);

	return 0;
}