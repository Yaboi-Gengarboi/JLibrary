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
// Vector2.hpp
// Created on 2021-05-23 by Justyn Durnford
// Last modified on 2021-06-13 by Justyn Durnford
// Header file for the Vector2 template class.

#pragma once

#include <JLibrary/Math/Angle.hpp>
#include <JLibrary/Math/Point2.hpp>

namespace jlib
{
    // Utility template class for representing, manipulating
    // and computing with vectors in 2-dimensional space.
    template <std_arithmetic T> class Vector2
    {
        public:

        T x;
        T y;

        // Default constructor.
        // Sets the x component of the Vector2 to 0.
        // Sets the y component of the Vector2 to 0.
        Vector2()
        {
            x = static_cast<T>(0);
            y = static_cast<T>(0);
        }

        // Constructs the Vector2 from the given coordinates.
        // Sets the x component of the Vector2 to X.
		// Sets the y component of the Vector2 to Y.
        Vector2(T X, T Y)
        {
            x = X;
            y = Y;
        }

        // Constructs the Vector2 from the given magnitude and Angle.
        // Sets the x component of the Vector2 to F * std::cos(angle).
        // Sets the y component of the Vector2 to F * std::sin(angle).
        Vector2(float F, const Angle& angle)
        {
            x = F * std::cos(angle.degree);
            y = F * std::sin(angle.degree);
        }

        // Constructs the Vector2 from the given Point2.
        // Sets the x component of the Vector2 to the x component of the given Point2.
		// Sets the y component of the Vector2 to the y component of the given Point2.
        Vector2(const Point2<T>& P)
        {
            x = P.x;
            y = P.y;
        }

        // Constructs the Vector2 as the displacement vector of the two Point2s.
        // Sets the x component of the Vector2 to B.x - A.x.
        // Sets the y component of the Vector2 to B.y - A.y.
        Vector2(const Point2<T>& A, const Point2<T>& B)
        {
            x = B.x - A.x;
            y = B.y - A.y;
        }

        // Constructs the Vector2 from another type of Vector2.
        // This constructor doesn't replace the copy constructor,
        // it's called only when U != T.
        template <std_arithmetic U>
        explicit Vector2(const Vector2<U>& other)
        {
            x = static_cast<T>(other.x);
            y = static_cast<T>(other.y);
        }

        // Copy constructor.
        Vector2(const Vector2& other) = default;

        // Move constructor.
        Vector2(Vector2&& other) = default;

        // Assigns the Vector2 from the given Point2.
        // Sets the x component of the Vector2 to the x component of the given Point2.
        // Sets the y component of the Vector2 to the y component of the given Point2.
        Vector2& operator = (const Point2<T>& P)
        {
            x = P.x;
            y = P.y;

            return *this;
        }

        // Copy assignment operator.
        Vector2& operator = (const Vector2& other) = default;

        // Move assignment operator.
        Vector2& operator = (Vector2 && other) = default;

        // Sets all the values of the Vector2 at once.
        // Sets the x component of the Vector2 to X.
        // Sets the y component of the Vector2 to Y.
        void set(T X, T Y)
        {
            x = X;
            y = Y;
        }

        // Returns the magnitude of the Vector2.
        inline float magnitude() const
        {
            return std::sqrt(std::powf(x, 2.f) + std::powf(y, 2.f));
        }

        // Returns the endpoint of the Point2.
        inline Point2<T> endpoint() const
        {
            return Point2<T>(x, y);
        }

        // Returns a unit vector in the direction of the Vector2.
        Vector2<float> unitVector() const
        {
            float m = magnitude();
            return Vector2<float>(x / m, y / m);
        }

        // Returns a std::string representation of the Vector2.
        inline std::string toString() const
        {
            return '<' + std::to_string(x) + ", " + std::to_string(y) + '>';
        }

        // Returns a std::wstring representation of the Vector2.
        inline std::wstring toWString() const
        {
            return L'<' + std::to_wstring(x) + L", " + std::to_wstring(y) + L'>';
        }
    };

    // Returns the dot product of the 2 given Vector2s.
    template <std_arithmetic T>
    inline float dot_product(const Vector2<T>& A, const Vector2<T>& B)
    {
        return A.x * B.x + A.y * B.y;
    }

    // Returns the scalar projection of A onto B.
    template <std_arithmetic T>
    inline float scalar_proj(const Vector2<T>& A, const Vector2<T>& B)
    {
        return dot_product(A, B) / A.magnitude();
    }

    // Returns the vector projection of A onto B.
    template <std_arithmetic T>
    Vector2<float> vector_proj(const Vector2<T>& A, const Vector2<T>& B)
    {
        float f = (dot_product(A, B) / dot_product(A, A));
        return Vector2<float>(A.x * f, A.y * f);
    }

    // Checks if the 2 given Vector2s are orthogonal to eachother.
    template <std_arithmetic T>
    inline bool are_normal(const Vector2<T>& A, const Vector2<T>& B)
    {
        return dot_product(A, B) == 0.f;
    }

    // Define common types
    typedef jlib::Vector2<char>               Vector2_8i;
    typedef jlib::Vector2<unsigned char>      Vector2_8u;
    typedef jlib::Vector2<short>              Vector2_16i;
    typedef jlib::Vector2<unsigned short>     Vector2_16u;
    typedef jlib::Vector2<int>                Vector2_32i;
    typedef jlib::Vector2<unsigned int>       Vector2_32u;
    typedef jlib::Vector2<float>              Vector2_32f;
}

// Overload of unary operator -
template <jlib::std_arithmetic T>
jlib::Vector2<T> operator - (const jlib::Vector2<T>& A)
{
    return jlib::Vector2<T>(-A.x, -A.y);
}

// Overload of binary operator +
template <jlib::std_arithmetic T>
jlib::Vector2<T> operator + (const jlib::Vector2<T>& A, const jlib::Vector2<T>& B)
{
    return jlib::Vector2<T>(A.x + B.x, A.y + B.y);
}

// Overload of binary operator -
template <jlib::std_arithmetic T>
jlib::Vector2<T> operator - (const jlib::Vector2<T>& A, const jlib::Vector2<T>& B)
{
    return jlib::Vector2<T>(A.x - B.x, A.y - B.y);
}

// Overload of binary operator *
template <jlib::std_arithmetic T, jlib::std_arithmetic U>
jlib::Vector2<T> operator * (const jlib::Vector2<T>& A, U scalar)
{
    return jlib::Vector2<T>(A.x * scalar, A.y * scalar);
}

// Overload of binary operator /
template <jlib::std_arithmetic T, jlib::std_arithmetic U>
jlib::Vector2<T> operator / (const jlib::Vector2<T>& A, U scalar)
{
    return jlib::Vector2<T>(A.x / scalar, A.y / scalar);
}

// Overload of binary operator +=
template <jlib::std_arithmetic T>
jlib::Vector2<T>& operator += (jlib::Vector2<T>& A, const jlib::Vector2<T>& B)
{
    A.x += B.x;
    A.y += B.y;

    return A;
}

// Overload of binary operator -=
template <jlib::std_arithmetic T>
jlib::Vector2<T>& operator -= (jlib::Vector2<T>& A, const jlib::Vector2<T>& B)
{
    A.x -= B.x;
    A.y -= B.y;

    return A;
}

// Overload of binary operator *=
template <jlib::std_arithmetic T, jlib::std_arithmetic U>
jlib::Vector2<T>& operator *= (jlib::Vector2<T>& A, U scalar)
{
    A.x *= scalar;
    A.y *= scalar;

    return A;
}

// Overload of binary operator /=
template <jlib::std_arithmetic T, jlib::std_arithmetic U>
jlib::Vector2<T>& operator /= (jlib::Vector2<T>& A, U scalar)
{
    A.x /= scalar;
    A.y /= scalar;

    return A;
}

// Overload of binary operator ==
template <jlib::std_arithmetic T>
bool operator == (const jlib::Vector2<T>& A, const jlib::Vector2<T>& B)
{
    return (A.x == B.x) && (A.y == B.y);
}

// Overload of binary operator !=
template <jlib::std_arithmetic T>
bool operator != (const jlib::Vector2<T>& A, const jlib::Vector2<T>& B)
{
    return (A.x != B.x) || (A.y != B.y);
}