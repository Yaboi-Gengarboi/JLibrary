// JLibraryDevelopment
// Glyph.hpp
// Created on 2021-06-19 by Justyn Durnford
// Last modified on 2021-06-23 by Justyn Durnford
// Header file for the Glyph struct.

#pragma once

#include <JLibrary/Math/Rectangle.hpp>

namespace jlib
{
	struct Glyph
	{
		float advanceOffset;
		int lDelta;
		int rDelta;
		Rectangle<float> bounds;
		Rectangle<int> textureRect;

		// Default constructor.
		Glyph() : advanceOffset(0.f), lDelta(0), rDelta(0) {}
	};
}