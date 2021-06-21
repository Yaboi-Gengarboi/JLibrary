// JLibraryIdeaTest
// main.cpp
// Created on 2021-06-11 by Justyn Durnford
// Last modified on 2021-06-20 by Justyn Durnford

import Point2;

#include <iostream>
using std::cout;
using std::endl;

class NonCopyable
{
	public:

	// Default constructor.
	NonCopyable() = default;

	// Disabled copy constructor.
	NonCopyable(const NonCopyable& other) = delete;

	// Move constructor.
	NonCopyable(NonCopyable&& other) = default;

	// Disabled copy assignment operator.
	NonCopyable& operator = (const NonCopyable& other) = delete;

	// Move assignment operator.
	NonCopyable& operator = (NonCopyable&& other) = default;

	// Destructor.
	virtual ~NonCopyable() = default;
};

class A : public NonCopyable
{
	int a;

	public:

	// Default constructor.
	A()
	{
		a = 0;
	}

	// int constructor.
	A(int i)
	{
		a = i;
	}

	// Move constructor.
	A(A&& other) = default;

	// Move assignment operator.
	A& operator = (A&& other) = default;

	// Destructor.
	~A() = default;

	int get() const
	{
		return a;
	}
};

int main()
{
	A a(5);

	return 0;
}