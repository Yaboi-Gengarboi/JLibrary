// JLibraryDevelopment
// Vertex2.hpp
// Created on 2021-06-09 by Justyn Durnford
// Last modified on 2021-07-02 by Justyn Durnford
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

		Point2f position;
		Point2f textureCoordinates;
		Color color;

		// Default constructor.
		Vertex2();

		// Position constructor.
		// Sets the position of the Vertex2 to the given position Point2.
		// Sets the texture coordinates of the Vertex2 to the given Coordinate Point2.
		// Sets the color of the Vertex2 to the given Color.
		Vertex2(const Point2f& pos, const Point2f& coord = Point2f(), const Color& col = Color());
	};

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

	// Returns the distance between the two given vertices.
	inline float distance_between(const Vertex2& A, const Vertex2& B);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

// Overload of binary operator ==
bool operator == (const jlib::Vertex2& A, const jlib::Vertex2& B);

// Overload of binary operator !=
bool operator != (const jlib::Vertex2& A, const jlib::Vertex2& B);