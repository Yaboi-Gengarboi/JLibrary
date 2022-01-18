// JLibrary
// main.cpp
// Created on 2022-01-08 by Justyn Durnford
// Last modified on 2022-01-15 by Justyn Durnford
// Test file for the JLibrary static library.

#include "JLibrary.hpp"
using namespace jlib;

#include <iostream>
using std::cout;
using std::endl;

#include <string>
using std::string;
using std::size_t;
using std::to_string;

template <typename T, size_t N>
void print_array(const FixedArray<T, N>& arr)
{
	string str("{ ");
	const size_t len = N - 1;

	for (size_t i = 0; i < len; ++i)
		str += to_string(arr[i]) + ", ";

	str += to_string(arr[len]) + " }";

	cout << str << endl;
}

template <typename T>
void print_array(const Array<T>& arr)
{
	string str("{ ");
	const size_t len = arr.size() - 1;

	for (size_t i = 0; i < len; ++i)
		str += to_string(arr[i]) + ", ";

	str += to_string(arr[len]) + " }";

	cout << str << endl;
}

int main()
{
	FixedMatrix<i16, 3, 3> mat3x3
	{
		{0, 1, 2},
		{3, 4, 5},
		{6, 7, 8}
	};

	FixedArray<i16, 3> row0(mat3x3.getRow(0));
	print_array(row0);

	return 0;
}