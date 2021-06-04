// JLibraryDevelopment
// Vector2.hpp
// Created on 2021-05-23 by Justyn Durnford
// Last modified on 2021-05-29 by Justyn Durnford
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
    typedef jl::Vector2<char>               Vector2_8i;
    typedef jl::Vector2<unsigned char>      Vector2_8u;
    typedef jl::Vector2<short>              Vector2_16i;
    typedef jl::Vector2<unsigned short>     Vector2_16u;
    typedef jl::Vector2<int>                Vector2_32i;
    typedef jl::Vector2<unsigned int>       Vector2_32u;
    typedef jl::Vector2<float>              Vector2_32f;
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