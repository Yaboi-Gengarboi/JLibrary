// JLibraryDevelopment
// Vertex3.cpp
// Created on 2021-06-11 by Justyn Durnford
// Last modified on 2021-07-02 by Justyn Durnford
// Source file for the Vertex3 class.

#include <JLibrary/Graphics/Vertex3.hpp>
using namespace jlib;

Vertex3::Vertex3()
{
	color = 0xffffffff;
}

Vertex3::Vertex3(const Point3f& pos, const Point3f& coord, const Color& col)
{
	position = pos;
	textureCoordinates = coord;
	color = col;
}

inline float jlib::distance_between(const Vertex3& A, const Vertex3& B)
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