// JLibrary
// Vector2.ixx
// Created on 2022-01-08 by Justyn Durnford
// Last modified on 2022-01-08 by Justyn Durnford
// Module file for the Vector2 template class.

module;

#include "Angle.hpp"
#include "IntegerTypedefs.hpp"

export module Vector2;

import Arithmetic;

export namespace jlib
{
	// Utility template class for representing, manipulating
	// and computing with vectors in 2-dimensional space.
	template <arithmetic T> class Vector2
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
		// Sets the x component of the Vector2 to new_x.
		// Sets the y component of the Vector2 to new_y.
		Vector2(T new_x, T new_y)
		{
			x = new_x;
			y = new_y;
		}

		// Constructs the Vector2 from the given Angle and magnitude.
		// Sets the x component of the Vector2 to F * cosine(angle).
		// Sets the y component of the Vector2 to F * sine(angle).
		Vector2(T F, Angle angle)
		{
			x = static_cast<T>(F * cosine(angle));
			y = static_cast<T>(F * sine(angle));
		}

		// Constructs the Vector2 as the displacement vector of the two points.
		// Sets the x component of the Vector2 to B.x - A.x.
		// Sets the y component of the Vector2 to B.y - A.y.
		Vector2(const Vector2<T>& A, const Vector2<T>& B)
		{
			x = B.x - A.x;
			y = B.y - A.y;
		}

		// Default copy constructor.
		Vector2(const Vector2& other) = default;

		// Default move constructor.
		Vector2(Vector2&& other) = default;

		// Constructs the Vector2 from another type of Vector2.
		// This constructor doesn't replace the copy constructor,
		// it's called only when U != T.
		template <arithmetic U>
		explicit Vector2(const Vector2<U>& other)
		{
			x = static_cast<T>(other.x);
			y = static_cast<T>(other.y);
		}

		// Default copy assignment operator.
		Vector2& operator = (const Vector2& other) = default;

		// Default move assignment operator.
		Vector2& operator = (Vector2&& other) = default;

		// Destructor.
		~Vector2() = default;

		// Sets all the values of the Vector2 at once.
		// Sets the x component of the Vector2 to new_x.
		// Sets the y component of the Vector2 to new_y.
		void set(T new_x, T new_y)
		{
			x = new_x;
			y = new_y;
		}

		// Copies the components of a different type of Vector2.
		template <arithmetic U>
		void copyFrom(const Vector2<U>& other)
		{
			x = static_cast<T>(other.x);
			y = static_cast<T>(other.y);
		}

		// Returns the magnitude of the Vector2.
		constexpr float magnitude() const
		{
			return std::sqrtf(std::powf(static_cast<float>(x), 2.0f) + std::powf(static_cast<float>(y), 2.0f));
		}

		// Returns the unit vector of this Vector2.
		Vector2<float> unitVector() const
		{
			constexpr float m = magnitude();
			return Vector2<float>(x / m, y / m);
		}

		// Returns a normal vector of this Vector2.
		Vector2 normal()
		{
			return Vector2(-y, x);
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

	// Converts the given Vector2 to another type of Vector2.
	template <arithmetic T, arithmetic U>
	Vector2<T> convert(const Vector2<U>& A)
	{
		T x = static_cast<T>(A.x);
		T y = static_cast<T>(A.y);

		return Vector2<T>(x, y);
	}

	// Returns the distance between the 2 given Vector2s.
	template <arithmetic T>
	float distance(const Vector2<T>& A, const Vector2<T>& B)
	{
		Vector2<T> C(A, B);
		return C.magnitude();
	}

	// Returns the horizontal distance between the 2 given Vector2s.
	template <arithmetic T>
	float distance_x(const Vector2<T>& A, const Vector2<T>& B)
	{
		float x = B.x - A.x;
		return x;
	}

	// Returns the vertical distance between the 2 given Vector2s.
	template <arithmetic T>
	float distance_y(const Vector2<T>& A, const Vector2<T>& B)
	{
		float y = B.y - A.y;
		return y;
	}

	// Returns the dot product of the 2 given Vector2s.
	template <arithmetic T>
	float dot_product(const Vector2<T>& A, const Vector2<T>& B)
	{
		return A.x * B.x + A.y * B.y;
	}

	// Returns the scalar projection of A onto B.
	template <arithmetic T>
	float scalar_proj(const Vector2<T>& A, const Vector2<T>& B)
	{
		return dot_product(A, B) / A.magnitude();
	}

	// Returns the vector projection of A onto B.
	template <arithmetic T>
	Vector2<float> vector_proj(const Vector2<T>& A, const Vector2<T>& B)
	{
		float f = (dot_product(A, B) / dot_product(A, A));
		return Vector2<float>(A.x * f, A.y * f);
	}

	// Returns the angle between the 2 given Vector2s.
	template <arithmetic T>
	Angle angle_between(const Vector2<T>& A, const Vector2<T>& B)
	{
		return arccosine(dot_product(A, B) / (A.magnitude() * B.magnitude()));
	}

	// Checks if the 2 given Vector2s are orthogonal to eachother.
	template <arithmetic T>
	bool are_normal(const Vector2<T>& A, const Vector2<T>& B)
	{
		return dot_product(A, B) == 0.0f;
	}

	typedef jlib::Vector2<bool>   Vector2b;
	typedef jlib::Vector2<i8>     Vector2c;
	typedef jlib::Vector2<u8>     Vector2uc;
	typedef jlib::Vector2<i16>    Vector2s;
	typedef jlib::Vector2<u16>    Vector2us;
	typedef jlib::Vector2<i32>    Vector2i;
	typedef jlib::Vector2<u32>    Vector2u;
	typedef jlib::Vector2<float>  Vector2f;

	// Overload of binary operator ==
	template <arithmetic T>
	bool operator == (const Vector2<T>& A, const Vector2<T>& B)
	{
		return (A.x == B.x) && (A.y == B.y);
	}

	// Overload of binary operator !=
	template <arithmetic T>
	bool operator != (const Vector2<T>& A, const Vector2<T>& B)
	{
		return (A.x != B.x) || (A.y != B.y);
	}

	// Overload of binary operator <
	template <arithmetic T>
	bool operator < (const Vector2<T>& A, const Vector2<T>& B)
	{
		return A.magnitude() < B.magnitude();
	}

	// Overload of binary operator <=
	template <arithmetic T>
	bool operator <= (const Vector2<T>& A, const Vector2<T>& B)
	{
		return A.magnitude() <= B.magnitude();
	}

	// Overload of binary operator >
	template <arithmetic T>
	bool operator > (const Vector2<T>& A, const Vector2<T>& B)
	{
		return A.magnitude() > B.magnitude();
	}

	// Overload of binary operator >=
	template <arithmetic T>
	bool operator >= (const Vector2<T>& A, const Vector2<T>& B)
	{
		return A.magnitude() >= B.magnitude();
	}

	// Overload of unary operator -
	template <arithmetic T>
	Vector2<T> operator - (const Vector2<T>& A)
	{
		return Vector2<T>(-A.x, -A.y);
	}

	// Overload of binary operator +
	template <arithmetic T>
	Vector2<T> operator + (const Vector2<T>& A, const Vector2<T>& B)
	{
		return Vector2<T>(A.x + B.x, A.y + B.y);
	}

	// Overload of binary operator -
	template <arithmetic T>
	Vector2<T> operator - (const Vector2<T>& A, const Vector2<T>& B)
	{
		return Vector2<T>(A.x - B.x, A.y - B.y);
	}

	// Overload of binary operator *
	template <arithmetic T>
	Vector2<T> operator * (const Vector2<T>& A, const Vector2<T>& B)
	{
		return Vector2<T>(A.x * B.x, A.y * B.y);
	}

	// Overload of binary operator *
	template <arithmetic T, arithmetic U>
	Vector2<T> operator * (const Vector2<T>& A, U scalar)
	{
		return Vector2<T>(A.x * scalar, A.y * scalar);
	}

	// Overload of binary operator *
	template <arithmetic T, arithmetic U>
	Vector2<T> operator * (U scalar, const Vector2<T>& A)
	{
		return Vector2<T>(A.x * scalar, A.y * scalar);
	}

	// Overload of binary operator /
	template <arithmetic T>
	Vector2<T> operator / (const Vector2<T>& A, const Vector2<T>& B)
	{
		return Vector2<T>(A.x / B.x, A.y / B.y);
	}

	// Overload of binary operator /
	template <arithmetic T, arithmetic U>
	Vector2<T> operator / (const Vector2<T>& A, U scalar)
	{
		return Vector2<T>(A.x / scalar, A.y / scalar);
	}

	// Overload of binary operator /
	template <arithmetic T, arithmetic U>
	Vector2<T> operator / (U scalar, const Vector2<T>& A)
	{
		return Vector2<T>(scalar / A.x, scalar / A.y);
	}

	// Overload of binary operator +=
	template <arithmetic T>
	Vector2<T>& operator += (Vector2<T>& A, const Vector2<T>& B)
	{
		A.x += B.x;
		A.y += B.y;

		return A;
	}

	// Overload of binary operator -=
	template <arithmetic T>
	Vector2<T>& operator -= (Vector2<T>& A, const Vector2<T>& B)
	{
		A.x -= B.x;
		A.y -= B.y;

		return A;
	}

	// Overload of binary operator *=
	template <arithmetic T, arithmetic U>
	Vector2<T>& operator *= (Vector2<T>& A, U scalar)
	{
		A.x *= scalar;
		A.y *= scalar;

		return A;
	}

	// Overload of binary operator /=
	template <arithmetic T, arithmetic U>
	Vector2<T>& operator /= (Vector2<T>& A, U scalar)
	{
		A.x /= scalar;
		A.y /= scalar;

		return A;
	}

	// Overload of std::ostream operator <<
	template <arithmetic T>
	std::ostream& operator << (std::ostream& os, const Vector2<T>& A)
	{
		os << A.toString();
		return os;
	}

	// Overload of std::wostream operator <<
	template <arithmetic T>
	std::wostream& operator << (std::wostream& wos, const Vector2<T>& A)
	{
		wos << A.toWideString();
		return wos;
	}
}