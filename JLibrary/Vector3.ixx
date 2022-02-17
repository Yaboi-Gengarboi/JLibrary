// JLibrary
// Vector3.ixx
// Created on 2022-01-08 by Justyn Durnford
// Last modified on 2022-02-17 by Justyn Durnford
// Module file for the Vector3 template class.

module;

#include "Angle.hpp"
#include "Arithmetic.hpp"
#include "IntegerTypedefs.hpp"

export module Vector3;

export namespace jlib
{
	// Utility template class for representing, manipulating
	// and computing with vectors in 3-dimensional space.
	template <arithmetic T> class Vector3
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
		// Sets the x component of the Vector3 to new_x.
		// Sets the y component of the Vector3 to new_y.
		// Sets the z component of the Vector3 to new_z.
		Vector3(T new_x, T new_y, T new_z)
		{
			x = new_x;
			y = new_y;
			z = new_z;
		}

		// Constructs the Vector3 as the displacement vector of the two points.
		// Sets the x component of the Vector3 to B.x - A.x.
		// Sets the y component of the Vector3 to B.y - A.y.
		// Sets the z component of the Vector3 to B.z - A.z.
		Vector3(const Vector3<T>& A, const Vector3<T>& B)
		{
			x = B.x - A.x;
			y = B.y - A.y;
			z = B.z - A.z;
		}

		// Default copy constructor.
		Vector3(const Vector3& other) = default;

		// Default move constructor.
		Vector3(Vector3&& other) = default;

		// Constructs the Vector3 from another type of Vector3.
		// This constructor doesn't replace the copy constructor,
		// it's called only when U != T.
		template <arithmetic U>
		explicit Vector3(const Vector3<U>& other)
		{
			x = static_cast<T>(other.x);
			y = static_cast<T>(other.y);
			z = static_cast<T>(other.z);
		}

		// Default copy assignment operator.
		Vector3& operator = (const Vector3& other) = default;

		// Default move assignment operator.
		Vector3& operator = (Vector3&& other) = default;

		// Destructor.
		~Vector3() = default;

		// Sets all the values of the Vector3 at once.
		// Sets the x component of the Vector3 to new_x.
		// Sets the y component of the Vector3 to new_y.
		// Sets the z component of the Vector3 to new_z.
		void set(T new_x, T new_y, T new_z)
		{
			x = new_x;
			y = new_y;
			z = new_z;
		}

		// Copies the components of another Vector3.
		void copyFrom(const Vector3& other)
		{
			x = other.x;
			y = other.y;
			z = other.z;
		}

		// Copies the components of a different type of Vector3.
		template <arithmetic U>
		void copyFrom(const Vector3<U>& other)
		{
			x = static_cast<T>(other.x);
			y = static_cast<T>(other.y);
			z = static_cast<T>(other.z);
		}

		// Returns the magnitude of the Vector3.
		constexpr float magnitude() const
		{
			return std::sqrtf(std::powf(static_cast<float>(x), 2.0f) + std::powf(static_cast<float>(y), 2.0f) + std::powf(static_cast<float>(z), 2.0f));
		}

		// Returns the unit vector of this Vector3.
		Vector3<float> unitVector() const
		{
			constexpr float m = magnitude();
			return Vector3<float>(x / m, y / m, z / m);
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

	///////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////

	// Converts the given Vector3 to another type of Vector3.
	template <arithmetic T, arithmetic U>
	Vector3<T> convert(const Vector3<U>& A)
	{
		return Vector3<T>(static_cast<T>(A.x), static_cast<T>(A.y), static_cast<T>(A.z));
	}

	// Returns the distance between the 2 given Vector3s.
	template <arithmetic T>
	float distance(const Vector3<T>& A, const Vector3<T>& B)
	{
		Vector3<T> C(A, B);
		return C.magnitude();
	}

	// Returns the x-distance between the 2 given Vector3s.
	template <arithmetic T>
	float distance_x(const Vector3<T>& A, const Vector3<T>& B)
	{
		return B.x - A.x;
	}

	// Returns the y-distance between the 2 given Vector3s.
	template <arithmetic T>
	float distance_y(const Vector3<T>& A, const Vector3<T>& B)
	{
		return B.y - A.y;
	}

	// Returns the z-distance between the 2 given Vector3s.
	template <arithmetic T>
	float distance_z(const Vector3<T>& A, const Vector3<T>& B)
	{
		return B.z - A.z;
	}

	// Returns the dot product of the 2 given Vector3s.
	template <arithmetic T>
	float dot_product(const Vector3<T>& A, const Vector3<T>& B)
	{
		return A.x * B.x + A.y * B.y + A.z * B.z;
	}

	// Returns the cross product of the 2 given Vector3s.
	template <arithmetic T>
	Vector3<T> cross_product(const Vector3<T>& A, const Vector3<T>& B)
	{
		return Vector3<T>(A.y * B.z - A.z * B.y, -(A.x * B.z - A.z * B.x), A.x * B.y - A.y * B.x);
	}

	// Returns the scalar projection of A onto B.
	template <arithmetic T>
	float scalar_proj(const Vector3<T>& A, const Vector3<T>& B)
	{
		return dot_product(A, B) / A.magnitude();
	}

	// Returns the vector projection of A onto B.
	template <arithmetic T>
	Vector3<float> vector_proj(const Vector3<T>& A, const Vector3<T>& B)
	{
		float f = (dot_product(A, B) / dot_product(A, A));
		return Vector3<float>(A.x * f, A.y * f, A.z * f);
	}

	// Determines if the 2 given Vector3s are orthogonal to eachother.
	template <arithmetic T>
	bool are_normal(const Vector3<T>& A, const Vector3<T>& B)
	{
		return dot_product(A, B) == 0.f;
	}

	///////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////

	typedef jlib::Vector3<bool>   Vector3b;
	typedef jlib::Vector3<i8>     Vector3c;
	typedef jlib::Vector3<u8>     Vector3uc;
	typedef jlib::Vector3<i16>    Vector3s;
	typedef jlib::Vector3<u16>    Vector3us;
	typedef jlib::Vector3<i32>    Vector3i;
	typedef jlib::Vector3<u32>    Vector3u;
	typedef jlib::Vector3<float>  Vector3f;

	///////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////

	// Overload of binary operator ==
	template <arithmetic T>
	bool operator == (const Vector3<T>& A, const Vector3<T>& B)
	{
		return (A.x == B.x) && (A.y == B.y) && (A.z == B.z);
	}

	// Overload of binary operator !=
	template <arithmetic T>
	bool operator != (const Vector3<T>& A, const Vector3<T>& B)
	{
		return (A.x != B.x) || (A.y != B.y) || (A.z != B.z);
	}

	// Overload of binary operator <
	template <arithmetic T>
	bool operator < (const Vector3<T>& A, const Vector3<T>& B)
	{
		return A.magnitude() < B.magnitude();
	}

	// Overload of binary operator <=
	template <arithmetic T>
	bool operator <= (const Vector3<T>& A, const Vector3<T>& B)
	{
		return A.magnitude() <= B.magnitude();
	}

	// Overload of binary operator >
	template <arithmetic T>
	bool operator > (const Vector3<T>& A, const Vector3<T>& B)
	{
		return A.magnitude() > B.magnitude();
	}

	// Overload of binary operator >=
	template <arithmetic T>
	bool operator >= (const Vector3<T>& A, const Vector3<T>& B)
	{
		return A.magnitude() >= B.magnitude();
	}

	// Overload of unary operator -
	template <arithmetic T>
	Vector3<T> operator - (const Vector3<T>& A)
	{
		return Vector3<T>(-A.x, -A.y, -A.z);
	}

	// Overload of binary operator +
	template <arithmetic T>
	Vector3<T> operator + (const Vector3<T>& A, const Vector3<T>& B)
	{
		return Vector3<T>(A.x + B.x, A.y + B.y, A.z + B.z);
	}

	// Overload of binary operator -
	template <arithmetic T>
	Vector3<T> operator - (const Vector3<T>& A, const Vector3<T>& B)
	{
		return Vector3<T>(A.x - B.x, A.y - B.y, A.z - B.z);
	}

	// Overload of binary operator *
	template <arithmetic T>
	Vector3<T> operator * (const Vector3<T>& A, const Vector3<T>& B)
	{
		return Vector3<T>(A.x * B.x, A.y * B.y, A.z * B.z);
	}

	// Overload of binary operator *
	template <arithmetic T, arithmetic U>
	Vector3<T> operator * (const Vector3<T>& A, U scalar)
	{
		return Vector3<T>(A.x * scalar, A.y * scalar, A.z * scalar);
	}

	// Overload of binary operator *
	template <arithmetic T, arithmetic U>
	Vector3<T> operator * (U scalar, const Vector3<T>& A)
	{
		return Vector3<T>(A.x * scalar, A.y * scalar, A.z * scalar);
	}

	// Overload of binary operator /
	template <arithmetic T>
	Vector3<T> operator / (const Vector3<T>& A, const Vector3<T>& B)
	{
		return Vector3<T>(A.x / B.x, A.y / B.y, A.z / B.z);
	}

	// Overload of binary operator /
	template <arithmetic T, arithmetic U>
	Vector3<T> operator / (const Vector3<T>& A, U scalar)
	{
		return Vector3<T>(A.x / scalar, A.y / scalar, A.z / scalar);
	}

	// Overload of binary operator /
	template <arithmetic T, arithmetic U>
	Vector3<T> operator / (U scalar, const Vector3<T>& A)
	{
		return Vector3<T>(scalar / A.x, scalar / A.y, scalar / A.z);
	}

	// Overload of binary operator +=
	template <arithmetic T>
	Vector3<T>& operator += (Vector3<T>& A, const Vector3<T>& B)
	{
		A.x += B.x;
		A.y += B.y;
		A.z += B.z;

		return A;
	}

	// Overload of binary operator -=
	template <arithmetic T>
	Vector3<T>& operator -= (Vector3<T>& A, const Vector3<T>& B)
	{
		A.x -= B.x;
		A.y -= B.y;
		A.z -= B.z;

		return A;
	}

	// Overload of binary operator *=
	template <arithmetic T, arithmetic U>
	Vector3<T>& operator *= (Vector3<T>& A, U scalar)
	{
		A.x *= scalar;
		A.y *= scalar;
		A.z *= scalar;

		return A;
	}

	// Overload of binary operator /=
	template <arithmetic T, arithmetic U>
	Vector3<T>& operator /= (Vector3<T>& A, U scalar)
	{
		A.x /= scalar;
		A.y /= scalar;
		A.z /= scalar;

		return A;
	}

	// Overload of std::ostream operator <<
	template <arithmetic T>
	std::ostream& operator << (std::ostream& os, const Vector3<T>& A)
	{
		os << A.toString();
		return os;
	}

	// Overload of std::wostream operator <<
	template <arithmetic T>
	std::wostream& operator << (std::wostream& wos, const Vector3<T>& A)
	{
		wos << A.toWideString();
		return wos;
	}
}