// JLibraryDevelopment
// Vector3.hpp
// Created on 2021-05-23 by Justyn Durnford
// Last modified on 2021-07-17 by Justyn Durnford
// Header file for the Vector3 template class.

#pragma once

#include <JLibrary/Math/Angle.hpp>
#include <JLibrary/Math/Point3.hpp>

namespace jlib
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
        float magnitude() const
        {
            return std::sqrtf(std::powf(x, 2.f) + std::powf(y, 2.f) + std::powf(z, 2.f));
        }

        // Returns the endpoint of the Vector3.
        Point3<T> endpoint() const
        {
            return Point3<T>(x, y, z);
        }

        // Returns a std::string representation of the Vector3.
        std::string toString() const
        {
            return '<' + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + '>';
        }

        // Returns a std::wstring representation of the Vector3.
        std::wstring toWideString() const
        {
            return L'<' + std::to_wstring(x) + L", " + std::to_wstring(y) + L", " + std::to_wstring(z) + L'>';
        }
    };

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

    // Converts the given Point3 to a Vector3.
    template <std_arithmetic T>
    Vector3<T> point_to_vector(const Point3<T>& P)
    {
        return Vector3<T>(P.x, P.y, P.z);
    }

    // Returns a unit vector in the direction of the Vector3.
    template <std_arithmetic T>
    Vector3<T> unit_vector(const Vector3<T>& A)
    {
        return Vector3<T>(A) / A.magnitude();
    }

    // Returns the dot product of the 2 given Vector3s.
    template <std_arithmetic T>
    float dot_product(const Vector3<T>& A, const Vector3<T>& B)
    {
        return A.x * B.x + A.y * B.y + A.z * B.z;
    }

    // Returns the cross product of the 2 given Vector3s.
    template <jlib::std_arithmetic T>
    jlib::Vector3<T> cross_product(const Vector3<T>& A, const Vector3<T>& B)
    {
        return Vector3<T>(A.y * B.z - A.z * B.y, -(A.x * B.z - A.z * B.x), A.x * B.y - A.y * B.x);
    }

    // Returns the scalar projection of A onto B.
    template <std_arithmetic T>
    float scalar_proj(const Vector3<T>& A, const Vector3<T>& B)
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
    bool are_normal(const Vector3<T>& A, const Vector3<T>& B)
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