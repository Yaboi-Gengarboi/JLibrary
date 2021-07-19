// JLibraryIdeaTest
// main.cpp
// Created on 2021-06-11 by Justyn Durnford
// Last modified on 2021-07-13 by Justyn Durnford

#include <compare>
using std::strong_ordering;

#include <concepts>
using std::unsigned_integral;

#include <cstddef>
using std::size_t;

#include <iostream>
using std::cout;
using std::wcout;
using std::endl;

#include <string>
using std::string;
using std::wstring;

#ifdef _WIN64

	constexpr size_t operator "" uz(unsigned long long n)
	{
		return n;
	}

#endif // _WIN64

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

class IDClass
{
	unsigned short id_;
	string name_;

	public:

	IDClass() = default;

	IDClass(unsigned short id, const string& name)
	{
		id_ = id;
		name_ = name;
	}

	unsigned short getID() const
	{
		return id_;
	}

	void setID(unsigned short id)
	{
		id_ = id;
	}

	const string& getName() const
	{
		return name_;
	}

	void setName(const string& name)
	{
		name_ = name;
	}
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

bool operator == (const IDClass& A, const IDClass& B)
{
	return A.getID() == B.getID();
}

bool operator != (const IDClass& A, const IDClass& B)
{
	return A.getID() != B.getID();
}

strong_ordering operator <=> (const IDClass& A, const IDClass& B)
{
	return A.getID() <=> B.getID();
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	cout << 11 / 4 << endl;

	return 0;
}