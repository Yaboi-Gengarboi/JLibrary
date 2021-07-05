////////////////////////////////////////////////////////////
//
// THIS IS A MODIFIED FILE FROM SFML 2.5.1
// 
// SFML - Simple and Fast Multimedia Library
// Copyright (C) 2007-2021 Laurent Gomila (laurent@sfml-dev.org)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
////////////////////////////////////////////////////////////
// 
// JLibraryDevelopment
// Mouse.cpp
// Created on 2021-05-25 by Justyn Durnford
// Last modified on 2021-07-02 by Justyn Durnford
// Source file for the Mouse class.

#include <JLibrary/System/Mouse.hpp>
using namespace jlib;

#include <windows.h>

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

Point2ui Mouse::getPosition()
{
	POINT pos;
	GetCursorPos(&pos);
	return Point2ui(pos.x, pos.y);
}

void Mouse::setPosition(const Point2ui& pos)
{
	SetCursorPos(pos.x, pos.y);
}