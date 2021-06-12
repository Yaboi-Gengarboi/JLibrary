// JLibraryDevelopment
// Vertex3.hpp
// Created on 2021-06-11 by Justyn Durnford
// Last modified on 2021-06-11 by Justyn Durnford
// Header file for the Vertex3 class.

#pragma once

#include <JLibrary/Graphics/Color.hpp>
#include <JLibrary/Math/Point3.hpp>

namespace jl
{
	// A specialized 3-dimensional float point with color 
	// and texture coordinates.
	class Vertex3
	{
		public:

		Point3_32f position;
		Color color;
		Point3_32f textureCoordinates;

		// Default constructor.
		Vertex3();

		// Position constructor.
		// Sets the position of the Vertex3 to the given position Point3.
		Vertex3(const Point3_32f& pos);

		// Position and color constructor.
		// Sets the position of the Vertex3 to the given position Point3.
		// Sets the color of the Vertex3 to the given Color.
		Vertex3(const Point3_32f& pos, const Color& col);

		// Position and texture coordinate constructor.
		// Sets the position of the Vertex3 to the given position Point3.
		// Sets the texture coordinatesof the Vertex3 to the given Coordinate Point3.
		Vertex3(const Point3_32f& pos, const Point3_32f& coord);

		// Full constructor.
		// Sets the position of the Vertex3 to the given position Point3.
		// Sets the color of the Vertex3 to the given Color.
		// Sets the texture coordinates of the Vertex3 to the given Coordinate Point3.
		Vertex3(const Point3_32f& pos, const Color& col, const Point3_32f& coord);

		// Copy constructor.
		Vertex3(const Vertex3& other) = default;

		// Move constructor.
		Vertex3(Vertex3&& other) = default;

		// Copy assignment operator.
		Vertex3& operator = (const Vertex3& other) = default;

		// Move assignment operator.
		Vertex3& operator = (Vertex3&& other) = default;

		// Destructor.
		~Vertex3() = default;
	};

	// Returns the distance between the two given vertices.
	inline float distance_between(const Vertex3& A, const Vertex3& B);
}

// Overload of binary operator ==
bool operator == (const jl::Vertex3& A, const jl::Vertex3& B);

// Overload of binary operator !=
bool operator != (const jl::Vertex3& A, const jl::Vertex3& B);