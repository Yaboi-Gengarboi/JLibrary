// JLibraryDevelopment
// Mouse.cpp
// Created on 2021-05-25 by Justyn Durnford
// Last modified on 2021-06-13 by Justyn Durnford
// Source file for the Mouse class.

#include <JLibrary/System/Mouse.hpp>
#include <windows.h>
using namespace std;
using namespace jlib;

bool Mouse::isButtonPressed(Button button)
{
	int virtual_key = 0;

	switch (button)
	{
		case Mouse::Left:     virtual_key = GetSystemMetrics(SM_SWAPBUTTON) ? VK_RBUTTON : VK_LBUTTON; break;
		case Mouse::Right:    virtual_key = GetSystemMetrics(SM_SWAPBUTTON) ? VK_LBUTTON : VK_RBUTTON; break;
		case Mouse::Middle:   virtual_key = VK_MBUTTON;  break;
		default:              virtual_key = 0;           break;
	}

	return (GetAsyncKeyState(virtual_key) & 0x8000) != 0;
}

Point2_32u Mouse::getPosition()
{
	POINT pos;
	GetCursorPos(&pos);
	return Point2_32u(pos.x, pos.y);
}

void Mouse::setPosition(const Point2_32u& pos)
{
	SetCursorPos(pos.x, pos.y);
}