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
// Vertex3.hpp
// Created on 2021-06-11 by Justyn Durnford
// Last modified on 2021-07-02 by Justyn Durnford
// Header file for the Vertex3 class.

#pragma once

#include <JLibrary/Graphics/Color.hpp>
#include <JLibrary/Math/Point3.hpp>

namespace jlib
{
	// A specialized 3-dimensional float point with color 
	// and texture coordinates.
	class Vertex3
	{
		public:

		Point3f position;
		Point3f textureCoordinates;
		Color color;

		// Default constructor.
		Vertex3();

		// Position constructor.
		// Sets the position of the Vertex3 to the given position Point3.
		// Sets the texture coordinates of the Vertex3 to the given Coordinate Point3.
		// Sets the color of the Vertex3 to the given Color.
		Vertex3(const Point3f& pos, const Point3f& coord = Point3f(), const Color& col = Color());
	};

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

	// Returns the distance between the two given vertices.
	inline float distance_between(const Vertex3& A, const Vertex3& B);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

// Overload of binary operator ==
bool operator == (const jlib::Vertex3& A, const jlib::Vertex3& B);

// Overload of binary operator !=
bool operator != (const jlib::Vertex3& A, const jlib::Vertex3& B);