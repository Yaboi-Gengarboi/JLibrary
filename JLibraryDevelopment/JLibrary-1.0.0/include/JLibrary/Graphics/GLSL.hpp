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
// GLSL.hpp
// Created on 2021-07-06 by Justyn Durnford
// Last modified on 2021-07-06 by Justyn Durnford
// Header defining the GLSL namespace.

#pragma once

#include <JLibrary/Graphics/Transformation.hpp>
#include <JLibrary/Graphics/Color.hpp>
#include <JLibrary/Math/Vector3.hpp>
#include <JLibrary/Math/VectorN.hpp>

namespace jlib
{
	// Namespace with GLSL types.
	namespace glsl
    {
        // 2D float point.
        typedef Point2<float>            Pt2;
        // 3D float point.              
        typedef Point3<float>            Pt3;
        // 4D float point.              
        typedef PointN<float, 4>         Pt4;
                                        
        // 2D int point.                
        typedef Point2<int>             Ipt2;
        // 3D int point.                
        typedef Point3<int>             Ipt3;
        // 4D int point.                
        typedef PointN<int, 4>          Ipt4;
                                        
        // 2D bool point.               
        typedef Point2<bool>            Bpt2;
        // 3D bool point.               
        typedef Point3<bool>            Bpt3;
        // 4D bool point.               
        typedef PointN<bool, 4>         Bpt4;

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

		// 2D float vector.
		typedef Vector2<float>          Vec2;
        // 3D float vector.            
        typedef Vector3<float>          Vec3;
        // 4D float vector.            
        typedef VectorN<float, 4>       Vec4;
                                       
		// 2D int vector.              
        typedef Vector2<int>           Ivec2;
        // 3D int vector.              
        typedef Vector3<int>           Ivec3;
        // 4D int vector.              
        typedef VectorN<int, 4>        Ivec4;
                                       
        // 2D bool vector.             
        typedef Vector2<bool>          Bvec2;
        // 3D bool vector.             
        typedef Vector3<bool>          Bvec3;
        // 4D bool vector.
        typedef VectorN<bool, 4>       Bvec4;

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

        // 3x3 float matrix.
        typedef Matrix<float, 3, 3>    Mat3;
        // 4x4 float matrix.
        typedef Matrix<float, 4, 4>    Mat4;
	}
}