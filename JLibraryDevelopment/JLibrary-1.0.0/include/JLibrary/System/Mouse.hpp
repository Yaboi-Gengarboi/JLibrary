// JLibraryDevelopment
// Mouse.hpp
// Created on 2021-05-25 by Justyn Durnford
// Last modified on 2021-05-25 by Justyn Durnford
// Header file for the Mouse class.

#pragma once

#include <JLibrary/Math/Point2.hpp>

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
	static jl::Point2_32u getPosition();

	// 
	static void setPosition(const jl::Point2_32u& pos);
};