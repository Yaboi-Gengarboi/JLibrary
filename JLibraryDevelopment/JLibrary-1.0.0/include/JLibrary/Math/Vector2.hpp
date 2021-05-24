// JLibraryDevelopment
// Vector2.hpp
// Created on 2021-05-23 by Justyn Durnford
// Last modified on 2021-05-24 by Justyn Durnford
// Header file for the Vector2 template class.

#pragma once

#include <JLibrary/Math/Point2.hpp>

namespace jl
{
    // Utility template class for representing, manipulating
    // and computing with vectors in 2-dimensional space.
    template <std_arithmetic T> class Vector2
    {
        public:

        T x;
        T y;

        // Default constructor.
        // Creates a Vector2(0, 0).
        Vector2()
        {
            x = static_cast<T>(0);
            y = static_cast<T>(0);
        }

        // Constructs the Vector2 from the given coordinates.
        // \param X: X coordinate
        // \param Y: Y coordinate
        Vector2(T X, T Y)
        {
            x = X;
            y = Y;
        }

        // Constructs the Vector2 from the given Point2.
        // \param P: Point2 to copy the coordinates from 
        Vector2(const Point2<T>& P)
        {
            x = P.x;
            y = P.y;
        }

        // Constructs the Vector2 as the displacement vector of the two Point2s.
        // \param A: First Point2
        // \param B: Second Point2
        Vector2(const Point2<T>& A, const Point2<T>& B)
        {
            x = B.x - A.x;
            y = B.y - A.y;
        }

        // Constructs the Vector2 from another type of Vector2.
        //
        // This constructor doesn't replace the copy constructor,
        // it's called only when U != T.
        //
        // \param other: Vector2 to convert
        template <std_arithmetic U>
        explicit Vector2(const Vector2<U>& other)
        {
            x = static_cast<T>(other.x);
            y = static_cast<T>(other.y);
        }

        // Assigns the Vector2 from the given Point2.
        // \param P: Point2 to copy the coordinates from 
        Vector2& operator = (const Point2<T>& P)
        {
            x = P.x;
            y = P.y;

            return *this;
        }

        // Sets the Vector2 from the given coordinates.
        // \param X: X coordinate
        // \param Y: Y coordinate
        void set(T X, T Y)
        {
            x = X;
            y = Y;
        }

        // Returns the magnitude of the Vector2.
        double magnitude() const
        {
            return std::sqrt(std::pow(x, 2) + std::pow(y, 2));
        }

        // Returns the endpoint of the Point2.
        Point2<T> endpoint() const
        {
            return Point2<T>(x, y);
        }

        // Returns a unit vector in the direction of the Vector2.
        Vector2<double> unitVector() const
        {
            double m = magnitude();
            return Vector2<double>(x / m, y / m);
        }

        // Returns a std::string representation of the Vector2.
        std::string toString() const
        {
            return '<' + std::to_string(x) + ", " + std::to_string(y) + '>';
        }

        // Returns a std::wstring representation of the Vector2.
        std::wstring toWString() const
        {
            return L'<' + std::to_wstring(x) + L", " + std::to_wstring(y) + L'>';
        }
    };

    // Returns the dot product of the 2 given Vector2s.
    template <std_arithmetic T, std_arithmetic U>
    inline double dot_product(const Vector2<T>& A, const Vector2<U>& B)
    {
        return static_cast<double>(A.x * B.x + A.y * B.y);
    }

    // Returns the scalar projection of A onto B.
    template <std_arithmetic T, std_arithmetic U>
    inline double scalar_proj(const Vector2<T>& A, const Vector2<U>& B)
    {
        return dot_product(A, B) / A.magnitude();
    }

    // Returns the vector projection of A onto B.
    template <std_arithmetic T, std_arithmetic U>
    Vector2<double> vector_proj(const Vector2<T>& A, const Vector2<U>& B)
    {
        double d = (dot_product(A, B) / dot_product(A, A));
        return Vector2<double>(A.x * d, A.y * d);
    }

    // Determines if the 2 given Vector2s are orthogonal to eachother.
    // - Returns true if dot_product(A, B) == 0.
    // - Returns false otherwise.
    template <std_arithmetic T, std_arithmetic U>
    inline bool are_normal(const Vector2<T>& A, const Vector2<U>& B)
    {
        return dot_product(A, B) == 0.0;
    }

    // Define common types
    typedef jl::Vector2<char>               Vector2_8;
    typedef jl::Vector2<unsigned char>      Vector2_8u;
    typedef jl::Vector2<short>              Vector2_16;
    typedef jl::Vector2<unsigned short>     Vector2_16u;
    typedef jl::Vector2<int>                Vector2_32;
    typedef jl::Vector2<unsigned int>       Vector2_32u;
    typedef jl::Vector2<long long>          Vector2_64;
    typedef jl::Vector2<unsigned long long> Vector2_64u;
    typedef jl::Vector2<float>              Vector2_32f;
    typedef jl::Vector2<double>             Vector2_64f;
}

// Overload of unary operator -
template <jl::std_arithmetic T>
jl::Vector2<T> operator - (const jl::Vector2<T>& A)
{
    return jl::Vector2<T>(-A.x, -A.y);
}

// Overload of binary operator +
template <jl::std_arithmetic T>
jl::Vector2<T> operator + (const jl::Vector2<T>& A, const jl::Vector2<T>& B)
{
    return jl::Vector2<T>(A.x + B.x, A.y + B.y);
}

// Overload of binary operator -
template <jl::std_arithmetic T>
jl::Vector2<T> operator - (const jl::Vector2<T>& A, const jl::Vector2<T>& B)
{
    return jl::Vector2<T>(A.x - B.x, A.y - B.y);
}

// Overload of binary operator *
template <jl::std_arithmetic T, jl::std_arithmetic U>
jl::Vector2<T> operator * (const jl::Vector2<T>& A, U scalar)
{
    return jl::Vector2<T>(A.x * scalar, A.y * scalar);
}

// Overload of binary operator *
template <jl::std_arithmetic T, jl::std_arithmetic U>
jl::Vector2<T> operator * (U scalar, const jl::Vector2<T>& A)
{
    return jl::Vector2<T>(A.x * scalar, A.y * scalar);
}

// Overload of binary operator /
template <jl::std_arithmetic T, jl::std_arithmetic U>
jl::Vector2<T> operator / (const jl::Vector2<T>& A, U scalar)
{
    return jl::Vector2<T>(A.x / scalar, A.y / scalar);
}

// Overload of binary operator +=
template <jl::std_arithmetic T>
jl::Vector2<T>& operator += (jl::Vector2<T>& A, const jl::Vector2<T>& B)
{
    A.x += B.x;
    A.y += B.y;

    return A;
}

// Overload of binary operator -=
template <jl::std_arithmetic T>
jl::Vector2<T>& operator -= (jl::Vector2<T>& A, const jl::Vector2<T>& B)
{
    A.x -= B.x;
    A.y -= B.y;

    return A;
}

// Overload of binary operator *=
template <jl::std_arithmetic T, jl::std_arithmetic U>
jl::Vector2<T>& operator *= (jl::Vector2<T>& A, U scalar)
{
    A.x *= scalar;
    A.y *= scalar;

    return A;
}

// Overload of binary operator /=
template <jl::std_arithmetic T, jl::std_arithmetic U>
jl::Vector2<T>& operator /= (jl::Vector2<T>& A, U scalar)
{
    A.x /= scalar;
    A.y /= scalar;

    return A;
}

// Overload of binary operator ==
template <jl::std_arithmetic T>
bool operator == (const jl::Vector2<T>& A, const jl::Vector2<T>& B)
{
    return (A.x == B.x) && (A.y == B.y);
}

// Overload of binary operator !=
template <jl::std_arithmetic T>
bool operator != (const jl::Vector2<T>& A, const jl::Vector2<T>& B)
{
    return (A.x != B.x) || (A.y != B.y);
}