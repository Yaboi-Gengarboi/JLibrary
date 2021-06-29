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
// Vertex3.cpp
// Created on 2021-06-11 by Justyn Durnford
// Last modified on 2021-06-27 by Justyn Durnford
// Source file for the Vertex3 class.

#include <JLibrary/Graphics/Vertex3.hpp>
using namespace std;
using namespace jlib;

Vertex3::Vertex3()
	: color(0xffffffff) {}

Vertex3::Vertex3(const Point3f& pos)
	: position(pos), color(0xffffffff) {}

Vertex3::Vertex3(const Point3f& pos, const Point3f& coord)
	: position(pos), color(0xffffffff), textureCoordinates(coord) {}

Vertex3::Vertex3(const Point3f& pos, const Color& col)
	: position(pos), color(col) {}

Vertex3::Vertex3(const Point3f& pos, const Color& col, const Point3f& coord)
	: position(pos), color(col), textureCoordinates(coord) {}

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