// JLibrary
// Direction.cpp
// Created on 2022-01-08 by Justyn Durnford
// Last modified on 2022-01-08 by Justyn Durnford
// Source file for the Direction class.

#include "Direction.hpp"

namespace jlib
{
	const Direction UP{ 0, Vector2f(0.0f, 1.0f), Angle(90.0f) };
	const Direction RIGHT{ 1, Vector2f(1.0f, 0.0f), Angle(0.0f) };
	const Direction DOWN{ 2, Vector2f(0.0f, -1.0f), Angle(270.0f) };
	const Direction LEFT{ 3, Vector2f(-1.0f, 0.0f), Angle(180.0f) };
}