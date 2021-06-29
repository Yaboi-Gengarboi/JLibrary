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
// Vector3.hpp
// Created on 2021-05-23 by Justyn Durnford
// Last modified on 2021-06-28 by Justyn Durnford
// Header file for the Vector3 template class.

#pragma once

#include <JLibrary/Math/Point3.hpp>

namespace jlib
{
    // Utility template class for representing, manipulating
    // and computing with vectors in 3-dimensional space.
    template <std_arithmetic T> struct Vector3
    {
        public:

        T x;
        T y;
        T z;

        // Default constructor.
        // Sets the x component of the Vector3 to 0.
        // Sets the y component of the Vector3 to 0.
        // Sets the z component of the Vector3 to 0.
        Vector3()
        {
            x = static_cast<T>(0);
            y = static_cast<T>(0);
            z = static_cast<T>(0);
        }

        // Constructs the Vector3 from the given coordinates.
        // Sets the x component of the Vector3 to X.
        // Sets the y component of the Vector3 to Y.
        // Sets the z component of the Vector3 to Z.
        Vector3(T X, T Y, T Z)
        {
            x = X;
            y = Y;
            z = Z;
        }

        // Constructs the Vector3 as the displacement vector of the two Point3s.
        // Sets the x component of the Vector3 to B.x - A.x.
        // Sets the y component of the Vector3 to B.y - A.y.
        // Sets the z component of the Vector3 to B.z - A.z.
        Vector3(const Point3<T>& A, const Point3<T>& B)
        {
            x = B.x - A.x;
            y = B.y - A.y;
            z = B.z - A.z;
        }

        // Constructs the Vector3 from another type of Vector3.
        // This constructor doesn't replace the copy constructor,
        // it's called only when U != T.
        template <std_arithmetic U>
        explicit Vector3(const Vector3<U>& other)
        {
            x = static_cast<T>(other.x);
            y = static_cast<T>(other.y);
            z = static_cast<T>(other.z);
        }

        // Copy constructor.
        Vector3(const Vector3& other) = default;

        // Move constructor.
        Vector3(Vector3&& other) = default;

        // Assigns the Vector3 from the given Point3.
        // Sets the x component of the Vector3 to the x component of the given Point3.
        // Sets the y component of the Vector3 to the y component of the given Point3.
        // Sets the z component of the Vector3 to the z component of the given Point3.
        Vector3& operator = (const Point3<T>& P)
        {
            x = P.x;
            y = P.y;
            z = P.z;

            return *this;
        }

        // Copy assignment operator.
        Vector3& operator = (const Vector3& other) = default;

        // Move assignment operator.
        Vector3& operator = (Vector3&& other) = default;

        // Sets all the values of the Vector3 at once.
        // Sets the x component of the Vector3 to X.
        // Sets the y component of the Vector3 to Y.
        // Sets the z component of the Vector3 to Z.
        void set(T X, T Y, T Z)
        {
            x = X;
            y = Y;
            z = Z;
        }

        // Returns the magnitude of the Vector3.
        inline float magnitude() const
        {
            return std::sqrtf(std::powf(x, 2.f) + std::powf(y, 2.f) + std::powf(z, 2.f));
        }

        // Returns the endpoint of the Point3.
        inline Point3<T> endpoint() const
        {
            return Point3<T>(x, y, z);
        }

        // Returns a unit vector in the direction of the Vector3.
        Vector3<float> unitVector() const
        {
            float m = magnitude();
            return Vector3<float>(x / m, y / m, z / m);
        }

        // Returns a std::string representation of the Vector3.
        inline std::string toString() const
        {
            return '<' + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + '>';
        }

        // Returns a std::wstring representation of the Vector3.
        inline std::wstring toWideString() const
        {
            return L'<' + std::to_wstring(x) + L", " + std::to_wstring(y) + L", " + std::to_wstring(z) + L'>';
        }
    };

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

    // Returns the dot product of the 2 given Vector3s.
    template <std_arithmetic T>
    inline float dot_product(const Vector3<T>& A, const Vector3<T>& B)
    {
        return A.x * B.x + A.y * B.y + A.z * B.z;
    }

    // Returns the cross product of the 2 given Vector3s.
    template <jlib::std_arithmetic T>
    inline jlib::Vector3<T> cross_product(const Vector3<T>& A, const Vector3<T>& B)
    {
        return Vector3<T>(A.y * B.z - A.z * B.y, -(A.x * B.z - A.z * B.x), A.x * B.y - A.y * B.x);
    }

    // Returns the scalar projection of A onto B.
    template <std_arithmetic T>
    inline double scalar_proj(const Vector3<T>& A, const Vector3<T>& B)
    {
        return dot_product(A, B) / A.magnitude();
    }

    // Returns the vector projection of A onto B.
    template <std_arithmetic T>
    Vector3<float> vector_proj(const Vector3<T>& A, const Vector3<T>& B)
    {
        float f = (dot_product(A, B) / dot_product(A, A));
        return Vector3<float>(A.x * f, A.y * f, A.z * f);
    }

    // Determines if the 2 given Vector3s are orthogonal to eachother.
    template <std_arithmetic T>
    inline bool are_normal(const Vector3<T>& A, const Vector3<T>& B)
    {
        return dot_product(A, B) == 0.f;
    }

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

    // Shorthand for jlib::Vector3<char>
    typedef jlib::Vector3<char>                  Vector3c;
    // Shorthand for jlib::Vector3<unsigned char>
    typedef jlib::Vector3<unsigned char>         Vector3uc;
    // Shorthand for jlib::Vector3<short>
    typedef jlib::Vector3<short>                 Vector3s;
    // Shorthand for jlib::Vector3<unsigned short>
    typedef jlib::Vector3<unsigned short>        Vector3us;
    // Shorthand for jlib::Vector3<int>
    typedef jlib::Vector3<int>                   Vector3i;
    // Shorthand for jlib::Vector3<unsigned int>
    typedef jlib::Vector3<unsigned int>          Vector3ui;
    // Shorthand for jlib::Vector3<float>
    typedef jlib::Vector3<float>                 Vector3f;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

// Overload of unary operator -
template <jlib::std_arithmetic T>
jlib::Vector3<T> operator - (const jlib::Vector3<T>& A)
{
    return jlib::Vector3<T>(-A.x, -A.y, -A.z);
}

// Overload of binary operator +
template <jlib::std_arithmetic T>
jlib::Vector3<T> operator + (const jlib::Vector3<T>& A, const jlib::Vector3<T>& B)
{
    return jlib::Vector3<T>(A.x + B.x, A.y + B.y, A.z + B.z);
}

// Overload of binary operator -
template <jlib::std_arithmetic T>
jlib::Vector3<T> operator - (const jlib::Vector3<T>& A, const jlib::Vector3<T>& B)
{
    return jlib::Vector3<T>(A.x - B.x, A.y - B.y, A.z - B.z);
}

// Overload of binary operator *
template <jlib::std_arithmetic T, jlib::std_arithmetic U>
jlib::Vector3<T> operator * (const jlib::Vector3<T>& A, U scalar)
{
    return jlib::Vector3<T>(A.x * scalar, A.y * scalar, A.z * scalar);
}

// Overload of binary operator /
template <jlib::std_arithmetic T, jlib::std_arithmetic U>
jlib::Vector3<T> operator / (const jlib::Vector3<T>& A, U scalar)
{
    return jlib::Vector3<T>(A.x / scalar, A.y / scalar, A.z / scalar);
}

// Overload of binary operator +=
template <jlib::std_arithmetic T>
jlib::Vector3<T>& operator += (jlib::Vector3<T>& A, const jlib::Vector3<T>& B)
{
    A.x += B.x;
    A.y += B.y;
    A.z += B.z;

    return A;
}

// Overload of binary operator -=
template <jlib::std_arithmetic T>
jlib::Vector3<T>& operator -= (jlib::Vector3<T>& A, const jlib::Vector3<T>& B)
{
    A.x -= B.x;
    A.y -= B.y;
    A.z -= B.z;

    return A;
}

// Overload of binary operator *=
template <jlib::std_arithmetic T, jlib::std_arithmetic U>
jlib::Vector3<T>& operator *= (jlib::Vector3<T>& A, U scalar)
{
    A.x *= scalar;
    A.y *= scalar;
    A.z *= scalar;

    return A;
}

// Overload of binary operator /=
template <jlib::std_arithmetic T, jlib::std_arithmetic U>
jlib::Vector3<T>& operator /= (jlib::Vector3<T>& A, U scalar)
{
    A.x /= scalar;
    A.y /= scalar;
    A.z /= scalar;

    return A;
}

// Overload of binary operator ==
template <jlib::std_arithmetic T>
bool operator == (const jlib::Vector3<T>& A, const jlib::Vector3<T>& B)
{
    return (A.x == B.x) && (A.y == B.y) && (A.z == B.z);
}

// Overload of binary operator !=
template <jlib::std_arithmetic T>
bool operator != (const jlib::Vector3<T>& A, const jlib::Vector3<T>& B)
{
    return (A.x != B.x) || (A.y != B.y) || (A.z != B.z);
}