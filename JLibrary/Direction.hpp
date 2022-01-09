// JLibrary
// Direction.hpp
// Created on 2022-01-08 by Justyn Durnford
// Last modified on 2022-01-08 by Justyn Durnford
// Header file for the Direction class.

#pragma once

#include "Angle.hpp"
#include "IntegerTypedefs.hpp"

import Vector2;

namespace jlib
{
	// 
	struct Direction
	{
		public:

		u8 id;
		Vector2f unitVector;
		Angle angle;

		enum : u8
		{
			UP = 0,
			RIGHT = 1,
			DOWN = 2,
			LEFT = 3,
		};
	};

	extern const Direction UP;
	extern const Direction RIGHT;
	extern const Direction DOWN;
	extern const Direction LEFT;
}