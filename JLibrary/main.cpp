// JLibrary
// main.cpp
// Created on 2022-01-08 by Justyn Durnford
// Last modified on 2022-02-16 by Justyn Durnford
// Test file for the JLibrary static library.

#include "JLibrary.hpp"
using namespace jlib;

#include <iostream>
using std::cout;

int main()
{
	Vector4i A = { 1, 1, 1, 1 };
	Vector4f B(A.unitVector());

	cout << B << '\n';
	cout << B.magnitude() << '\n';

	return 0;
}