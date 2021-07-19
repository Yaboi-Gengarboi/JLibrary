// JLibraryDevelopment
// Vector2.hpp
// Created on 2021-05-23 by Justyn Durnford
// Last modified on 2021-07-17 by Justyn Durnford
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
            x = F * std::cosf(angle.degree);
            y = F * std::sinf(angle.degree);
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

        // Sets all the values of the Vector2 at once.
        // Sets the x component of the Vector2 to X.
        // Sets the y component of the Vector2 to Y.
        void set(T X, T Y)
        {
            x = X;
            y = Y;
        }

        // Returns the magnitude of the Vector2.
        float magnitude() const
        {
            return std::sqrtf(std::powf(x, 2.f) + std::powf(y, 2.f));
        }

        // Returns the endpoint of the Vector2.
        Point2<T> endpoint() const
        {
            return Point2<T>(x, y);
        }

        // Returns a std::string representation of the Vector2.
        std::string toString() const
        {
            return '<' + std::to_string(x) + ", " + std::to_string(y) + '>';
        }

        // Returns a std::wstring representation of the Vector2.
        std::wstring toWideString() const
        {
            return L'<' + std::to_wstring(x) + L", " + std::to_wstring(y) + L'>';
        }
    };

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

    // Converts the given Point2 to a Vector2.
    template <std_arithmetic T>
    Vector2<T> point_to_vector(const Point2<T>& P)
    {
        return Vector2<T>(P.x, P.y);
    }

    // Returns the unit vector of the given Vector2.
    template <std_arithmetic T>
    Vector2<float> unit_vector(const Vector2<T>& A)
    {
        return Vector2<T>(A) / A.magnitude();
    }

    // Returns a normal vector of the given Vector2.
    template <std_arithmetic T>
    Vector2<T> normal_vector(const Vector2<T>& A)
    {
        return Vector2<T>(-A.y, A.x);
    }

    // Returns the dot product of the 2 given Vector2s.
    template <std_arithmetic T>
    float dot_product(const Vector2<T>& A, const Vector2<T>& B)
    {
        return A.x * B.x + A.y * B.y;
    }

    // Returns the scalar projection of A onto B.
    template <std_arithmetic T>
    float scalar_proj(const Vector2<T>& A, const Vector2<T>& B)
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
    bool are_normal(const Vector2<T>& A, const Vector2<T>& B)
    {
        return dot_product(A, B) == 0.f;
    }

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

    // Shorthand for jlib::Vector2<char>
    typedef jlib::Vector2<char>                  Vector2c;
    // Shorthand for jlib::Vector2<unsigned char>
    typedef jlib::Vector2<unsigned char>         Vector2uc;
    // Shorthand for jlib::Vector2<short>
    typedef jlib::Vector2<short>                 Vector2s;
    // Shorthand for jlib::Vector2<unsigned short>
    typedef jlib::Vector2<unsigned short>        Vector2us;
    // Shorthand for jlib::Vector2<int>
    typedef jlib::Vector2<int>                   Vector2i;
    // Shorthand for jlib::Vector2<unsigned int>
    typedef jlib::Vector2<unsigned int>          Vector2ui;
    // Shorthand for jlib::Vector2<float>
    typedef jlib::Vector2<float>                 Vector2f;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

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