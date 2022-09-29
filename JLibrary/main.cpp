// JLibrary
// main.cpp
// Created on 2022-01-08 by Justyn Durnford
// Last modified on 2022-09-21 by Justyn Durnford
// Test file for the JLibrary static library.

#define AND &&
#define OR ||
#define IS ==
#define ISNOT !=
#define LET const auto

#include "Buffer.hpp"
#include "Conversions.hpp"
#include "Gamepad.hpp"
#include "Hexadecimal.hpp"
#include "Time.hpp"
import FixedGrid;
import FixedMatrix;
import LinearEquation1;
import Ptr;
import VectorN;

using namespace jlib;

#include <concepts>
using std::strong_ordering;

#include <fstream>
using std::fstream;
using std::ifstream;
using std::basic_ios;
using std::ofstream;

#include <iostream>
using std::cin;
using std::cout;
using std::wcin;
using std::wcout;
using std::endl;

#include <string>
using std::string;
using std::wstring;
using std::getline;
using std::to_string;

#include <vector>
using std::vector;

template <arithmetic T>
void println(const T& value)
{
	cout << value << '\n';
}

void println(bool b)
{
	if (b)
		cout << "true\n";
	else
		cout << "false\n";
}

void println(strong_ordering ordering)
{
	if (ordering == strong_ordering::less)
		cout << "less\n";
	else if (ordering == strong_ordering::greater)
		cout << "greater\n";
	else
		cout << "equal\n";
}

void println(const string& str)
{
	cout << str << '\n';
}

void println(const string* strs, size_t len)
{
	for (size_t i = 0; i < len; ++i)
		cout << strs[i] << '\n';
}

int main(int argc, char** argv)
{
	ifstream fin("test.txt");

	vector<string> lines;
	string line;

	while (getline(fin, line))
		lines.push_back(line);

	println(lines.data(), lines.size());

	return 0;
}