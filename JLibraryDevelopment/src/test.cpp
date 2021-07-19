// JLibraryDevelopment
// test.cpp
// Created on 2021-05-23 by Justyn Durnford
// Last updated on 2021-07-18 by Justyn Durnford
// Main file for testing.

#ifndef NOMINMAX
	#define NOMINMAX
#endif // NOMINMAX

#include <JLibrary/Graphics.hpp>
#include <JLibrary/Math.hpp>
#include <JLibrary/System.hpp>
#include <JLibrary/Utility.hpp>
#include <JLibrary/Window.hpp>
using namespace jlib;

#include <compare>
using std::strong_ordering;

#include <iostream>
using std::cout;
using std::wcout;
using std::endl;

#include <string>
using std::size_t;
using std::string;
using std::wstring;

#include <thread>
using std::thread;

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

void println()
{
	cout << endl;
}

void println(bool b)
{
	if (b)
		cout << "true";
	else
		cout << "false";
	cout << endl;
}

void println(strong_ordering order)
{
	if (order == strong_ordering::less)
		cout << "less";
	else if (order == strong_ordering::greater)
		cout << "greater";
	else
		cout << "equal";
	cout << endl;
}

void println(const string& str)
{
	cout << str << endl;
}

void println(const wstring& wstr)
{
	wcout << wstr << endl;
}

template <std_arithmetic T, size_t R, size_t C>
void print_matrix(const Matrix<T, R, C>& M)
{
	for (size_t row_i(0); row_i < R; ++row_i)
	{
		cout << "{ ";
		for (size_t col_i(0); col_i < C - 1; ++col_i)
			cout << M(row_i, col_i) << ", ";
		cout << M(row_i, C - 1) << " }" << endl;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

void test_gamepad()
{

}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	Clock clock;
	Event event;

	// Create main window.
	RenderWindow window(VideoMode(800, 600), L"JLibrary Development", WindowStyle::Titlebar | WindowStyle::Close);
	window.setFramerateLimit(60);

	// Start the loop.
	while (window.isOpen())
	{
		// Process events.
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
				// Close window: exit.
				case Event::Closed:
					window.close();
					break;

				default:
					break;
			}
		}

		// Clear screen.
		window.clear();

		// Update the window.
		window.display();
	}

	return 0;
}