// JLibrary
// main.cpp
// Created on 2022-01-08 by Justyn Durnford
// Last modified on 2022-05-18 by Justyn Durnford
// Test file for the JLibrary static library.

#define AND &&
#define OR ||
#define IS ==
#define ISNOT !=
#define LET const auto

#include "Gamepad.hpp"
import VectorN;
using namespace jlib;

#include <concepts>
using std::strong_ordering;

#include <iostream>
using std::cin;
using std::cout;
using std::wcin;
using std::wcout;
using std::endl;

#include <string>
using std::string;
using std::wstring;
using std::to_string;

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

int main()
{
	Gamepad controller;
	Vector2f oldPosition;
	Vector2f newPosition;
	WORD oldButtonStates = 0;
	WORD newButtonStates = 0;
	controller.update();

	while (controller.isConnected())
	{
		newPosition = controller.leftStick.position;
		newButtonStates = controller.getButtonStates();

		if (oldPosition ISNOT newPosition OR oldButtonStates ISNOT newButtonStates)
		{
			oldPosition = newPosition;
			oldButtonStates = newButtonStates;
			cout << oldPosition << ", " << oldButtonStates << '\n';
		}

		controller.update();
	}

	return 0;
}