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
// Vertex2.hpp
// Created on 2021-06-09 by Justyn Durnford
// Last modified on 2021-06-13 by Justyn Durnford
// Header file for the Vertex2 class.

#pragma once

#include <JLibrary/Graphics/Color.hpp>
#include <JLibrary/Math/Point2.hpp>

namespace jlib
{
	// A specialized 2-dimensional float point with color 
	// and texture coordinates.
	class Vertex2
	{
		public:

		Point2_32f position;
		Color color;
		Point2_32f textureCoordinates;

		// Default constructor.
		Vertex2();

		// Position constructor.
		// Sets the position of the Vertex2 to the given position Point2.
		Vertex2(const Point2_32f& pos);

		// Position and color constructor.
		// Sets the position of the Vertex2 to the given position Point2.
		// Sets the color of the Vertex2 to the given Color.
		Vertex2(const Point2_32f& pos, const Color& col);

		// Position and texture coordinate constructor.
		// Sets the position of the Vertex2 to the given position Point2.
		// Sets the texture coordinates of the Vertex2 to the given Coordinate Point2.
		Vertex2(const Point2_32f& pos, const Point2_32f& coord);

		// Full constructor.
		// Sets the position of the Vertex2 to the given position Point2.
		// Sets the color of the Vertex2 to the given Color.
		// Sets the texture coordinates of the Vertex2 to the given Coordinate Point2.
		Vertex2(const Point2_32f& pos, const Color& col, const Point2_32f& coord);

		// Copy constructor.
		Vertex2(const Vertex2& other) = default;

		// Move constructor.
		Vertex2(Vertex2&& other) = default;

		// Copy assignment operator.
		Vertex2& operator = (const Vertex2& other) = default;

		// Move assignment operator.
		Vertex2& operator = (Vertex2&& other) = default;

		// Destructor.
		~Vertex2() = default;
	};

	// Returns the distance between the two given vertices.
	inline float distance_between(const Vertex2& A, const Vertex2& B);
}

// Overload of binary operator ==
bool operator == (const jlib::Vertex2& A, const jlib::Vertex2& B);

// Overload of binary operator !=
bool operator != (const jlib::Vertex2& A, const jlib::Vertex2& B);