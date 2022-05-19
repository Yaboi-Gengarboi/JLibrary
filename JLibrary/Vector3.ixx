// JLibrary
// Vector3.ixx
// Created on 2022-01-08 by Justyn Durnford
// Last modified on 2022-05-17 by Justyn Durnford
// Module file for the Vector3 template struct.

module;

#include "Angle.hpp"
#include "Arithmetic.hpp"
#include "IntegerTypedefs.hpp"

export module Vector3;

export namespace jlib
{
	// Utility template struct for representing, manipulating
	// and computing with vectors in 3-dimensional space.
	template <arithmetic T> struct Vector3
	{
		T x;
		T y;
		T z;

		// Default constructor.
		// Sets the x component of the Vector3 to 0.
		// Sets the y component of the Vector3 to 0.
		// Sets the z component of the Vector3 to 0.
		Vector3()
		{
			x = 0;
			y = 0;
			z = 0;
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

		// Constructs the Vector3 from the given cylindrical coordinates.
		// Sets the x component of the Vector3 to radius * cosine(theta).
		// Sets the y component of the Vector3 to radius * sine(theta).
		// Sets the z component of the Vector3 to new_z.
		Vector3(T radius, Angle theta, T new_z)
		{
			x = static_cast<T>(radius * cosine(theta));
			y = static_cast<T>(radius * sine(theta));
			z = new_z;
		}

		// Constructs the Vector3 from the given spherical coordinates.
		// Sets the x component of the Vector3 to rho * sine(phi) * cosine(theta).
		// Sets the y component of the Vector3 to rho * sine(phi) * sine(theta).
		// Sets the z component of the Vector3 to rho * cosine(phi).
		Vector3(T rho, Angle theta, Angle phi)
		{
			x = static_cast<T>(rho * sine(phi) * cosine(theta));
			y = static_cast<T>(rho * sine(phi) * sine(theta));
			z = static_cast<T>(rho * cosine(phi));
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

		// Copies the components of a different type of Vector3.
		template <arithmetic U>
		void copyFrom(const Vector3<U>& other)
		{
			x = static_cast<T>(other.x);
			y = static_cast<T>(other.y);
			z = static_cast<T>(other.z);
		}

		// Adds the components of the given Vector3 onto this one.
		void add(const Vector3& other)
		{
			x += other.x;
			y += other.y;
			z += other.z;
		}

		// Subtracts the components of the given Vector3 onto this one.
		void subtract(const Vector3& other)
		{
			x -= other.x;
			y -= other.y;
			z -= other.z;
		}

		// Multiplies the components of the given Vector3 onto this one.
		void multiply(const Vector3& other)
		{
			x *= other.x;
			y *= other.y;
			z *= other.z;
		}

		// Multiplies each component of the Vector3 by the given scalar value.
		template <arithmetic U>
		void multiply(U scalar)
		{
			x *= scalar;
			y *= scalar;
			z *= scalar;
		}

		// Divides the components of the given Vector3 onto this one.
		void divide(const Vector3& other)
		{
			x /= other.x;
			y /= other.y;
			z /= other.z;
		}

		// Divides each component of the Vector3 by the given scalar value.
		template <arithmetic U>
		void divide(U scalar)
		{
			x /= scalar;
			y /= scalar;
			z /= scalar;
		}
	};

	///////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////

	// Returns a Vector3 whose elements are the absolute values of 
	// each of the given elements.
	template <arithmetic T>
	inline Vector3<T> abs(T x, T y, T z)
	{
		return Vector3<T>(std::abs(x), std::abs(y), std::abs(z));
	}

	// Returns a Vector3 whose elements are the absolute values of 
	// each of the specified Vector3's elements.
	template <arithmetic T>
	inline Vector3<T> abs(const Vector3<T>& vec)
	{
		return abs(vec.x, vec.y, vec.z);
	}

	// Returns the angle between the 2 given Vector3s.
	template <arithmetic T>
	Angle angle_between(const Vector3<T>& A, const Vector3<T>& B)
	{
		return arccosine(dot_product(A, B) / (A.magnitude() * B.magnitude()));
	}

	// Determines if the 2 given Vector3s are orthogonal to eachother.
	template <arithmetic T>
	constexpr bool are_normal(const Vector3<T>& A, const Vector3<T>& B)
	{
		return dot_product(A, B) == 0.0f;
	}

	// Returns the scalar projection of A onto B.
	template <arithmetic T>
	constexpr float comp_proj(const Vector3<T>& A, const Vector3<T>& B)
	{
		return dot_product(A, B) / B.magnitude();
	}

	// Returns the cross product of the 2 given Vector3s.
	template <arithmetic T>
	Vector3<T> cross_product(const Vector3<T>& A, const Vector3<T>& B)
	{
		return Vector3<T>(A.y * B.z - A.z * B.y, A.z * B.x - A.x * B.z, A.x * B.y - A.y * B.x);
	}

	// Returns the distance between the 2 given Vector3s.
	template <arithmetic T>
	constexpr float distance(const Vector3<T>& A, const Vector3<T>& B)
	{
		return std::sqrtf(distance_squared(A, B));
	}

	// Returns the distance squared between the 2 given Vector3s, treated as points.
	template <arithmetic T>
	constexpr float distance_squared(const Vector3<T>& A, const Vector3<T>& B)
	{
		return std::powf(static_cast<float>(B.x - A.x), 2.0f) + std::powf(static_cast<float>(B.y - A.y), 2.0f) + std::powf(static_cast<float>(B.z - A.z), 2.0f);
	}

	// Returns the x-distance between the 2 given Vector3s.
	template <arithmetic T>
	constexpr float distance_x(const Vector3<T>& A, const Vector3<T>& B)
	{
		return B.x - A.x;
	}

	// Returns the y-distance between the 2 given Vector3s.
	template <arithmetic T>
	constexpr float distance_y(const Vector3<T>& A, const Vector3<T>& B)
	{
		return B.y - A.y;
	}

	// Returns the z-distance between the 2 given Vector3s.
	template <arithmetic T>
	constexpr float distance_z(const Vector3<T>& A, const Vector3<T>& B)
	{
		return B.z - A.z;
	}

	// Returns the dot product of the 2 given Vector3s.
	template <arithmetic T>
	constexpr float dot_product(const Vector3<T>& A, const Vector3<T>& B)
	{
		return A.x * B.x + A.y * B.y + A.z * B.z;
	}

	// Returns the magnitude of the Vector3 constructed by the elements x, y and z.
	template <arithmetic T>
	constexpr float magnitude(T x, T y, T z)
	{
		return std::sqrtf(std::powf(static_cast<float>(x), 2.0f) + std::powf(static_cast<float>(y), 2.0f) + std::powf(static_cast<float>(z), 2.0f));
	}

	// Returns the magnitude of the given Vector3.
	template <arithmetic T>
	constexpr float magnitude(const Vector3<T>& vec)
	{
		return magnitude(vec.x, vec.y, vec.z);
	}

	// Returns a Vector3 whose elements are the maximum of each of the 
	// pairs of elements in two specified Vector3s.
	template <arithmetic T>
	inline Vector3<T> max(const Vector3<T>& A, const Vector3<T>& B)
	{
		return Vector3<T>(std::max(A.x, B.x), std::max(A.y, B.y), std::max(A.z, B.z));
	}

	// Returns a Vector3 whose elements are the minimum of each of the 
	// pairs of elements in two specified Vector3s.
	template <arithmetic T>
	inline Vector3<T> min(const Vector3<T>& A, const Vector3<T>& B)
	{
		return Vector3<T>(std::min(A.x, B.x), std::min(A.y, B.y), std::min(A.z, B.z));
	}

	// Normalizes the Vector3 by scaling each of its components so that it
	// has a magnitude of 1.
	template <arithmetic T>
	void normalize(Vector3<T>& vec)
	{
		vec.divide(magnitude(vec));
	}

	// Prints the given Vector3 to std::cout.
	template <arithmetic T>
	void print(const Vector3<T>& vec)
	{
		std::cout << to_string(vec);
	}

	// Prints the given Vector3 to std::coutwith a newline.
	template <arithmetic T>
	void println(const Vector3<T>& vec)
	{
		std::cout << to_string(vec) << '\n';
	}

	// Returns a std::string representation of the Vector3 constructed by the elements x, y and z.
	template <arithmetic T>
	inline std::string to_string(T x, T y, T z)
	{
		return '<' + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + '>';
	}

	// Returns a std::string representation of the given Vector3.
	template <arithmetic T>
	inline std::string to_string(const Vector3<T>& vec)
	{
		return '<' + std::to_string(vec.x) + ", " + std::to_string(vec.y) + ", " + std::to_string(vec.z) + '>';
	}

	// Returns a std::wstring representation of the Vector3 constructed by the elements x, y and z.
	template <arithmetic T>
	inline std::wstring to_wstring(T x, T y, T z)
	{
		return L'<' + std::to_wstring(x) + L", " + std::to_wstring(y) + L", " + std::to_wstring(z) + L'>';
	}

	// Returns a std::wstring representation of the given Vector3.
	template <arithmetic T>
	inline std::wstring to_wstring(const Vector3<T>& vec)
	{
		return L'<' + std::to_wstring(vec.x) + L", " + std::to_wstring(vec.y) + L", " + std::to_wstring(vec.z) + L'>';
	}

	// Returns a unit vector of the Vector3 constructed by the elements x, y and z.
	template <arithmetic T>
	Vector3<float> unit_vector(T x, T y, T z)
	{
		const float mag = magnitude(x, y, z);
		return Vector3<float>(static_cast<float>(x) / mag, static_cast<float>(y) / mag, static_cast<float>(z) / mag);
	}

	// Returns a unit vector of the given Vector3.
	template <arithmetic T>
	Vector3<float> unit_vector(const Vector3<T>& vec)
	{
		return unit_vector(vec.x, vec.y, vec.z);
	}

	// Returns the vector projection of A onto B.
	template <arithmetic T>
	Vector3<float> vector_proj(const Vector3<T>& A, const Vector3<T>& B)
	{
		const float f = (dot_product(A, B) / dot_product(A, A));
		return Vector3<float>(A.x * f, A.y * f, A.z * f);
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
	typedef jlib::Vector3<i64>    Vector3l;
	typedef jlib::Vector3<u64>    Vector3ul;
	typedef jlib::Vector3<size_t> Vector3uz;
	typedef jlib::Vector3<float>  Vector3f;
	typedef jlib::Vector3<double> Vector3d;

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
	std::ostream& operator << (std::ostream& os, const Vector3<T>& vec)
	{
		os << to_string(vec);
		return os;
	}

	// Overload of std::wostream operator <<
	template <arithmetic T>
	std::wostream& operator << (std::wostream& wos, const Vector3<T>& vec)
	{
		wos << to_wstring(vec);
		return wos;
	}
}