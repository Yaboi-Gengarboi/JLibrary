// JLibraryDevelopment
// Vertex2.cpp
// Created on 2021-06-11 by Justyn Durnford
// Last modified on 2021-06-11 by Justyn Durnford
// Source file for the Vertex2 class.

#include <JLibrary/Graphics/Vertex2.hpp>
using namespace std;
using namespace jl;

Vertex2::Vertex2() 
	: color(0xffffffff) {}

Vertex2::Vertex2(const Point2_32f& pos) 
	: position(pos), color(0xffffffff) {}

Vertex2::Vertex2(const Point2_32f& pos, const Point2_32f& coord) 
	: position(pos), color(0xffffffff), textureCoordinates(coord) {}

Vertex2::Vertex2(const Point2_32f& pos, const Color& col) 
	: position(pos), color(col) {}

Vertex2::Vertex2(const Point2_32f& pos, const Color& col, const Point2_32f& coord)
	: position(pos), color(col), textureCoordinates(coord) {}

inline float jl::distance_between(const Vertex2& A, const Vertex2& B)
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