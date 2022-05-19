// JLibrary
// Mouse.cpp
// Created on 2022-04-03 by Justyn Durnford
// Last modified on 2022-05-17 by Justyn Durnford
// Implementation file for Mouse.hpp.

#include "Mouse.hpp"

#include <windows.h>

#include <SFML/Window/Window.hpp>
using sf::Window;
using sf::WindowHandle;

import Vector2;
using jlib::Vector2i;

namespace jlib
{
	Vector2i get_mouse_position()
	{
		POINT point;
		GetCursorPos(&point);
		return Vector2i(point.x, point.y);
	}

	Vector2i get_mouse_position(const sf::Window& window)
	{
		POINT point;
		WindowHandle handle = window.getSystemHandle();

		if (handle)
		{
			GetCursorPos(&point);
			ScreenToClient(handle, &point);
		}

		return Vector2i(point.x, point.y);
	}

	void setPosition(int x, int y)
	{
		SetCursorPos(x, y);
	}

	void setPosition(const Vector2i& vec)
	{
		SetCursorPos(vec.x, vec.y);
	}

	void setPosition(int x, int y, const sf::Window& window)
	{
		WindowHandle handle = window.getSystemHandle();

		if (handle)
		{
			POINT point{ x, y };
			ClientToScreen(handle, &point);
			SetCursorPos(point.x, point.y);
		}
	}

	void setPosition(const Vector2i& vec, const sf::Window& window)
	{
		WindowHandle handle = window.getSystemHandle();

		if (handle)
		{
			POINT point{ vec.x, vec.y };
			ClientToScreen(handle, &point);
			SetCursorPos(point.x, point.y);
		}
	}
}