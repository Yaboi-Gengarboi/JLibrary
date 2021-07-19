// JLibraryDevelopment
// Vertex2.cpp
// Created on 2021-06-11 by Justyn Durnford
// Last modified on 2021-07-02 by Justyn Durnford
// Source file for the Vertex2 class.

#include <JLibrary/Graphics/Vertex2.hpp>
using namespace jlib;

Vertex2::Vertex2() 
{
	color = 0xffffffff;
}

Vertex2::Vertex2(const Point2f& pos, const Point2f& coord, const Color& col)
{
	position = pos;
	textureCoordinates = coord;
	color = col;
}

inline float jlib::distance_between(const Vertex2& A, const Vertex2& B)
{
	return distance_between(A.position, B.position);
}

bool operator == (const Vertex2& A, const Vertex2& B)
{
	return (A.position == B.position) && (A.color == B.color) && (A.textureCoordinates == B.textureCoordinates);
}

bool operator != (const Vertex2& A, const Vertex2& B)
{
	return (A.position != B.position) || (A.color != B.color) || (A.textureCoordinates != B.textureCoordinates);
}