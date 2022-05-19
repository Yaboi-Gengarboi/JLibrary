// JLibrary
// Mouse.hpp
// Created on 2022-04-03 by Justyn Durnford
// Last modified on 2022-05-17 by Justyn Durnford
// Header file defining several mouse-related functions.

#pragma once

#include <SFML/Window/Window.hpp>

import Vector2;

namespace jlib
{
	// Returns the position of the mouse.
	Vector2i get_mouse_position();

	// Returns the position of the mouse relative to the given window.
	Vector2i get_mouse_position(const sf::Window& window);

	// Sets the position of the mouse to the given point.
	void setPosition(int x, int y);

	// Sets the position of the mouse to the given point.
	void setPosition(const Vector2i& vec);

	// Sets the position of the mouse to the given point relative to the given window.
	void setPosition(int x, int y, const sf::Window& window);

	// Sets the position of the mouse to the given point relative to the given window.
	void setPosition(const Vector2i& vec, const sf::Window& window);
}