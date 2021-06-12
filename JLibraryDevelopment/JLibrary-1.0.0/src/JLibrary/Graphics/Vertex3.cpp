// JLibraryDevelopment
// Vertex3.cpp
// Created on 2021-06-11 by Justyn Durnford
// Last modified on 2021-06-11 by Justyn Durnford
// Source file for the Vertex3 class.

#include <JLibrary/Graphics/Vertex3.hpp>
using namespace std;
using namespace jl;

Vertex3::Vertex3()
	: color(0xffffffff) {}

Vertex3::Vertex3(const Point3_32f& pos)
	: position(pos), color(0xffffffff) {}

Vertex3::Vertex3(const Point3_32f& pos, const Point3_32f& coord)
	: position(pos), color(0xffffffff), textureCoordinates(coord) {}

Vertex3::Vertex3(const Point3_32f& pos, const Color& col)
	: position(pos), color(col) {}

Vertex3::Vertex3(const Point3_32f& pos, const Color& col, const Point3_32f& coord)
	: position(pos), color(col), textureCoordinates(coord) {}

inline float jl::distance_between(const Vertex3& A, const Vertex3& B)
{
	return distance_between(A.position, B.position);
}

bool operator == (const Vertex3& A, const Vertex3& B)
{
	return (A.position == B.position) && (A.color == B.color) && (A.textureCoordinates == B.textureCoordinates);
}

bool operator != (const Vertex3& A, const Vertex3& B)
{
	return (A.position != B.position) || (A.color != B.color) || (A.textureCoordinates != B.textureCoordinates);
}