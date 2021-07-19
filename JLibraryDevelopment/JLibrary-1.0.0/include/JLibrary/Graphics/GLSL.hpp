// JLibraryDevelopment
// GLSL.hpp
// Created on 2021-07-06 by Justyn Durnford
// Last modified on 2021-07-14 by Justyn Durnford
// Header file defining the GLSL namespace.

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

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

    // Copies a source transformation into the destination Matrix.
    void copyMatrix(const float* source, float* dest, std::size_t elements);

    // Copies a source transformation into the destination Matrix.
    void copyMatrix(const Transformation& source, Matrix<float, 3, 3>& dest);

    // Copies a source transformation into the destination Matrix.
    void copyMatrix(const Transformation& source, Matrix<float, 4, 4>& dest);

    // Copies a source Color into the desitination Vector.
    void copyVector(const Color& source, VectorN<float, 4>& dest);

    // Copies a source Color into the desitination Vector.
    void copyVector(const Color& source, VectorN<int, 4>& dest);
}