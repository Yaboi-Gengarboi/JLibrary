// JLibraryDevelopment
// Mouse.hpp
// Created on 2021-05-25 by Justyn Durnford
// Last modified on 2021-06-13 by Justyn Durnford
// Header file for the Mouse class.

#pragma once

#ifndef NOMINMAX
#define NOMINMAX
#endif // NOMINMAX

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

		// 
		static bool isButtonPressed(Button button);

		// 
		static Point2_32u getPosition();

		// 
		static void setPosition(const Point2_32u& pos);
	};
}