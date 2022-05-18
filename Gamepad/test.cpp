// JLibrary
// Gamepad
// test.cpp
// Created on 2022-03-06 by Justyn Durnford
// Last modified on 2022-03-06 by Justyn Durnford
// Test file for the Gamepad class.

#include "Gamepad.hpp"
using namespace jlib;

#include <iostream>
using std::cout;
using std::endl;

#include <string>
using std::string;

string leftStickPosStr;
string rightStickPosStr;

int main()
{
	Gamepad controller;

	while (true)
	{
		controller.update();

		if (controller.isConnected())
		{
			leftStickPosStr = controller.leftStick.position.toString();
			rightStickPosStr = controller.rightStick.position.toString();
			cout << leftStickPosStr << '\t' << rightStickPosStr << '\n';
		}
	}

	return 0;
}