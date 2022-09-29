// UnitConverter
// main.cpp 
// Created on 2022-09-08 by Justyn Durnford
// Last modified on 2022-09-09 by Justyn Durnford
// Main file for the UnitConverter program.

#include "Conversions.hpp"
using namespace jlib;

#include <iomanip>
using std::setprecision;

#include <iostream>
using std::cin;
using std::cout;
using std::cerr;

#include <limits>
using std::numeric_limits;

#include <string>
using std::string;
using std::getline;
using std::stof;
using std::stoi;

void println(float f)
{
	cout << setprecision(numeric_limits<float>::digits10 + 1) << f << '\n';
}

void choose_function(int n, float f)
{
	switch (n)
	{
		case 0: println(to_fahrenheit(f));  break;
		case 1: println(to_celcius(f));     break;
		case 2: println(to_centimeters(f)); break;
		case 3: println(to_inches(f));      break;
		case 4: println(to_feet(f));        break;
		case 5: println(to_meters(f));      break;
		case 6: println(to_miles(f));       break;
		case 7: println(to_kilometers(f));  break;
		case 8: println(to_miph(f));        break;
		case 9: println(to_kmph(f));        break;

		default:

		cerr << "ERROR: Invalid option chosen.\n";

		break;
	}
}

int main(int argc, char** argv)
{
	int i = 0;
	float f = 0.0f;
	string line;

	if (argc == 2)
	{
		try
		{
			i = stoi(argv[0]);
			f = stof(argv[1]);
		}
		catch (...)
		{
			cerr << "ERROR: Unable to parse arguments.\n";
			return 1;
		}

		choose_function(i, f);
	}
	else
	{
		cout << "Select conversion: \n";
		cout << "0: celcius to fahrenheit.\n";
		cout << "1: fahrenheit to celcius.\n";
		cout << "2: inches to centimeters.\n";
		cout << "3: centimeters to inches.\n";
		cout << "4: meters to feet.\n";
		cout << "5: feet to meters.\n";
		cout << "6: kilometers to miles.\n";
		cout << "7: miles to kilometers.\n";
		cout << "8: kmph to miph.\n";
		cout << "9: miph to kmph.\n";

		getline(cin, line);

		try { i = stoi(line); }
		catch (...)
		{
			cerr << "ERROR: Unable to parse argument.\n";
			return 1;
		}

		cout << "Enter the number to convert.\n";

		getline(cin, line);

		try { f = stof(line); }
		catch (...)
		{
			cerr << "ERROR: Unable to parse argument.\n";
			return 1;
		}

		choose_function(i, f);
	}

	return 0;
}