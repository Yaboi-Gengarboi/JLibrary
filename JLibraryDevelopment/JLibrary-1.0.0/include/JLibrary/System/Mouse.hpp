// JLibraryDevelopment
// Mouse.hpp
// Created on 2021-05-25 by Justyn Durnford
// Last modified on 2021-07-19 by Justyn Durnford
// Header file for the Mouse class.

#pragma once

#include <JLibrary/Math/Point2.hpp>

namespace jlib
{
	class Mouse
	{
		public:

		enum Button
		{
			Left,
			Right,
			Middle
		};

		enum Wheel
		{
			VerticalWheel,
			HorizontalWheel
		};

		// 
		static bool isButtonPressed(Button button);

		// 
		static Point2ui getPosition();

		// 
		static void setPosition(const Point2ui& pos);
	};
}