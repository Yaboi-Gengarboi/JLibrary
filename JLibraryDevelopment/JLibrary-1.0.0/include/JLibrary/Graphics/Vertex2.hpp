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