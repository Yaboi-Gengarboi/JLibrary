// JLibraryIdeaTest
// main.cpp
// Created on 2021-06-11 by Justyn Durnford
// Last modified on 2021-06-28 by Justyn Durnford

#include <cstddef>
using std::size_t;

#ifdef _WIN64

constexpr size_t operator "" uz(unsigned long long n)
{
	return n;
}

#endif // _WIN64


int main()
{
	size_t i = 100uz;
	++i;

	return 0;
}