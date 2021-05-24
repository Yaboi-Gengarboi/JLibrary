// JLibraryDevelopment
// Vector3.hpp
// Created on 2021-05-23 by Justyn Durnford
// Last modified on 2021-05-24 by Justyn Durnford
// Header file for the Vector3 template class.

#pragma once

#include <JLibrary/Math/Point3.hpp>

namespace jl
{
    // Utility template class for representing, manipulating
    // and computing with vectors in 3-dimensional space.
    template <std_arithmetic T> class Vector3
    {
        public:

        T x;
        T y;
        T z;

        // Default constructor.
        // Creates a Vector3(0, 0, 0).
        Vector3()
        {
            x = static_cast<T>(0);
            y = static_cast<T>(0);
            z = static_cast<T>(0);
        }

        // Constructs the Vector3 from the given coordinates.
        // \param X: X coordinate
        // \param Y: Y coordinate
        // \param Z: Z coordinate
        Vector3(T X, T Y, T Z)
        {
            x = X;
            y = Y;
            z = Z;
        }

        // Constructs the Vector3 from the given Point3.
        // \param P: Point3 to copy the coordinates from 
        Vector3(const Point3<T>& P)
        {
            x = P.x;
            y = P.y;
            z = P.z;
        }

        // Constructs the Vector3 as the displacement vector of the two Point3s.
        // \param A: First Point3
        // \param B: Second Point3
        Vector3(const Point3<T>& A, const Point3<T>& B)
        {
            x = B.x - A.x;
            y = B.y - A.y;
            z = B.z - A.z;
        }

        // Constructs the Vector3 from another type of Vector3.
        //
        // This constructor doesn't replace the copy constructor,
        // it's called only when U != T.
        //
        // \param other: Vector3 to convert
        template <std_arithmetic U>
        explicit Vector3(const Vector3<U>& other)
        {
            x = static_cast<T>(other.x);
            y = static_cast<T>(other.y);
            z = static_cast<T>(other.z);
        }

        // Assigns the Vector3 from the given Point3.
        // \param P: Point3 to copy the coordinates from 
        Vector3& operator = (const Point3<T>& P)
        {
            x = P.x;
            y = P.y;
            z = P.z;

            return *this;
        }

        // Sets the Vector3 from the given coordinates.
        // \param X: X coordinate
        // \param Y: Y coordinate
        // \param Z: Z coordinate
        void set(T X, T Y, T Z)
        {
            x = X;
            y = Y;
            z = Z;
        }

        // Returns the magnitude of the Vector3.
        double magnitude() const
        {
            return std::sqrt(std::pow(x, 2) + std::pow(y, 2) + std::pow(z, 2));
        }

        // Returns the endpoint of the Point3.
        Point3<T> endpoint() const
        {
            return Point3<T>(x, y, z);
        }

        // Returns a unit vector in the direction of the Vector3.
        Vector3<double> unitVector() const
        {
            double m = magnitude();
            return Vector3<double>(x / m, y / m, z / m);
        }

        // Returns a std::string representation of the Vector3.
        std::string toString() const
        {
            return '<' + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + '>';
        }

        // Returns a std::wstring representation of the Vector3.
        std::wstring toWString() const
        {
            return L'<' + std::to_wstring(x) + L", " + std::to_wstring(y) + L", " + std::to_wstring(z) + L'>';
        }
    };

    // Returns the dot product of the 2 given Vector3s.
    template <std_arithmetic T, std_arithmetic U>
    inline double dot_product(const Vector3<T>& A, const Vector3<U>& B)
    {
        return static_cast<double>(A.x * B.x + A.y * B.y + A.z * B.z);
    }

    // Returns the cross product of the 2 given Vector3s.
    template <jl::std_arithmetic T, jl::std_arithmetic U, jl::std_arithmetic V>
    inline jl::Vector3<T> cross_product(const Vector3<U>& A, const Vector3<V>& B)
    {
        return Vector3<T>(A.y * B.z - A.z * B.y, -(A.x * B.z - A.z * B.x), A.x * B.y - A.y * B.x);
    }

    // Returns the scalar projection of A onto B.
    template <std_arithmetic T, std_arithmetic U>
    inline double scalar_proj(const Vector3<T>& A, const Vector3<U>& B)
    {
        return dot_product(A, B) / A.magnitude();
    }

    // Returns the vector projection of A onto B.
    template <std_arithmetic T, std_arithmetic U>
    Vector3<float> vector_proj(const Vector3<T>& A, const Vector3<T>& B)
    {
        double d = (dot_product(A, B) / dot_product(A, A));
        return Vector3<double>(A.x * d, A.y * d, A.z * d);
    }

    // Determines if the 2 given Vector3s are orthogonal to eachother.
    // - Returns true if dot_product(A, B) == 0.
    // - Returns false otherwise.
    template <std_arithmetic T, std_arithmetic U>
    inline bool are_normal(const Vector3<T>& A, const Vector3<U>& B)
    {
        return dot_product(A, B) == 0.0;
    }

    // Define common types
    typedef jl::Vector3<char>               Vector3_8;
    typedef jl::Vector3<unsigned char>      Vector3_8u;
    typedef jl::Vector3<short>              Vector3_16;
    typedef jl::Vector3<unsigned short>     Vector3_16u;
    typedef jl::Vector3<int>                Vector3_32;
    typedef jl::Vector3<unsigned int>       Vector3_32u;
    typedef jl::Vector3<long long>          Vector3_64;
    typedef jl::Vector3<unsigned long long> Vector3_64u;
    typedef jl::Vector3<float>              Vector3_32f;
    typedef jl::Vector3<double>             Vector3_64f;
}

// Overload of unary operator -
template <jl::std_arithmetic T>
jl::Vector3<T> operator - (const jl::Vector3<T>& A)
{
    return jl::Vector3<T>(-A.x, -A.y, -A.z);
}

// Overload of binary operator +
template <jl::std_arithmetic T>
jl::Vector3<T> operator + (const jl::Vector3<T>& A, const jl::Vector3<T>& B)
{
    return jl::Vector3<T>(A.x + B.x, A.y + B.y, A.z + B.z);
}

// Overload of binary operator -
template <jl::std_arithmetic T>
jl::Vector3<T> operator - (const jl::Vector3<T>& A, const jl::Vector3<T>& B)
{
    return jl::Vector3<T>(A.x - B.x, A.y - B.y, A.z - B.z);
}

// Overload of binary operator *
template <jl::std_arithmetic T, jl::std_arithmetic U>
jl::Vector3<T> operator * (const jl::Vector3<T>& A, U scalar)
{
    return jl::Vector3<T>(A.x * scalar, A.y * scalar, A.z * scalar);
}

// Overload of binary operator *
template <jl::std_arithmetic T, jl::std_arithmetic U>
jl::Vector3<T> operator * (U scalar, const jl::Vector3<T>& A)
{
    return jl::Vector3<T>(A.x * scalar, A.y * scalar, A.z * scalar);
}

// Overload of binary operator /
template <jl::std_arithmetic T, jl::std_arithmetic U>
jl::Vector3<T> operator / (const jl::Vector3<T>& A, U scalar)
{
    return jl::Vector3<T>(A.x / scalar, A.y / scalar, A.z / scalar);
}

// Overload of binary operator +=
template <jl::std_arithmetic T>
jl::Vector3<T>& operator += (jl::Vector3<T>& A, const jl::Vector3<T>& B)
{
    A.x += B.x;
    A.y += B.y;
    A.z += B.z;

    return A;
}

// Overload of binary operator -=
template <jl::std_arithmetic T>
jl::Vector3<T>& operator -= (jl::Vector3<T>& A, const jl::Vector3<T>& B)
{
    A.x -= B.x;
    A.y -= B.y;
    A.z -= B.z;

    return A;
}

// Overload of binary operator *=
template <jl::std_arithmetic T, jl::std_arithmetic U>
jl::Vector3<T>& operator *= (jl::Vector3<T>& A, U scalar)
{
    A.x *= scalar;
    A.y *= scalar;
    A.z *= scalar;

    return A;
}

// Overload of binary operator /=
template <jl::std_arithmetic T, jl::std_arithmetic U>
jl::Vector3<T>& operator /= (jl::Vector3<T>& A, U scalar)
{
    A.x /= scalar;
    A.y /= scalar;
    A.z /= scalar;

    return A;
}

// Overload of binary operator ==
template <jl::std_arithmetic T>
bool operator == (const jl::Vector3<T>& A, const jl::Vector3<T>& B)
{
    return (A.x == B.x) && (A.y == B.y) && (A.z == B.z);
}

// Overload of binary operator !=
template <jl::std_arithmetic T>
bool operator != (const jl::Vector3<T>& A, const jl::Vector3<T>& B)
{
    return (A.x != B.x) || (A.y != B.y) || (A.z != B.z);
}