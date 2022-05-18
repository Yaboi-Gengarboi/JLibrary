// JLibrary
// Vector2.ixx
// Created on 2022-01-08 by Justyn Durnford
// Last modified on 2022-05-17 by Justyn Durnford
// Module file for the Vector2 template struct.

module;

#include "Angle.hpp"
#include "Arithmetic.hpp"
#include "IntegerTypedefs.hpp"

export module Vector2;

export namespace jlib
{
	// Utility template struct for representing, manipulating
	// and computing with vectors in 2-dimensional space.
	template <arithmetic T> struct Vector2
	{
		T x;
		T y;

		// Default constructor.
		// Sets the x component of the Vector2 to 0.
		// Sets the y component of the Vector2 to 0.
		Vector2()
		{
			x = 0;
			y = 0;
		}

		// Constructs the Vector2 from the given coordinates.
		// Sets the x component of the Vector2 to new_x.
		// Sets the y component of the Vector2 to new_y.
		Vector2(T new_x, T new_y)
		{
			x = new_x;
			y = new_y;
		}

		// Constructs the Vector2 from the given polar.
		// Sets the x component of the Vector2 to radius * cosine(theta).
		// Sets the y component of the Vector2 to radius * sine(theta).
		Vector2(T radius, Angle theta)
		{
			x = static_cast<T>(radius * cosine(theta));
			y = static_cast<T>(radius * sine(theta));
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

		// Adds the components of the given Vector2 onto this one.
		void add(const Vector2& other)
		{
			x += other.x;
			y += other.y;
		}

		// Subtracts the components of the given Vector2 onto this one.
		void subtract(const Vector2& other)
		{
			x -= other.x;
			y -= other.y;
		}

		// Multiplies the components of the given Vector2 onto this one.
		void multiply(const Vector2& other)
		{
			x *= other.x;
			y *= other.y;
		}

		// Multiplies each component of the Vector2 by the given scalar value.
		template <arithmetic U>
		void multiply(U scalar)
		{
			x *= scalar;
			y *= scalar;
		}

		// Divides the components of the given Vector2 onto this one.
		void divide(const Vector2& other)
		{
			x /= other.x;
			y /= other.y;
		}

		// Divides each component of the Vector2 by the given scalar value.
		template <arithmetic U>
		void divide(U scalar)
		{
			x /= scalar;
			y /= scalar;
		}
	};

	///////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////

	// Returns a Vector2 whose elements are the absolute values of 
	// each of the given elements.
	template <arithmetic T>
	inline Vector2<T> abs(T x, T y)
	{
		return Vector2<T>(std::abs(x), std::abs(y));
	}

	// Returns a Vector2 whose elements are the absolute values of 
	// each of the specified Vector2's elements.
	template <arithmetic T>
	inline Vector2<T> abs(const Vector2<T>& vec)
	{
		return abs(vec.x, vec.y);
	}

	// Returns the angle between the 2 given Vector2s.
	template <arithmetic T>
	inline Angle angle_between(const Vector2<T>& A, const Vector2<T>& B)
	{
		return arccosine(dot_product(A, B) / (magnitude(A) * magnitude(B)));
	}

	// Checks if the 2 given Vector2s are orthogonal to eachother.
	template <arithmetic T>
	constexpr bool are_normal(const Vector2<T>& A, const Vector2<T>& B)
	{
		return dot_product(A, B) == 0.0f;
	}

	// Returns the scalar projection of A onto B.
	template <arithmetic T>
	constexpr float comp_proj(const Vector2<T>& A, const Vector2<T>& B)
	{
		return dot_product(A, B) / B.magnitude();
	}

	// Returns the distance between the 2 given Vector2s, treated as points.
	template <arithmetic T>
	constexpr float distance(const Vector2<T>& A, const Vector2<T>& B)
	{
		return std::sqrtf(distance_squared(A, B));
	}

	// Returns the distance squared between the 2 given Vector2s, treated as points.
	template <arithmetic T>
	constexpr float distance_squared(const Vector2<T>& A, const Vector2<T>& B)
	{
		return std::powf(static_cast<float>(B.x - A.x), 2.0f) + std::powf(static_cast<float>(B.y - A.y), 2.0f);
	}

	// Returns the horizontal distance between the 2 given Vector2s.
	template <arithmetic T>
	constexpr float distance_x(const Vector2<T>& A, const Vector2<T>& B)
	{
		return B.x - A.x;
	}

	// Returns the vertical distance between the 2 given Vector2s.
	template <arithmetic T>
	constexpr float distance_y(const Vector2<T>& A, const Vector2<T>& B)
	{
		return B.y - A.y;
	}

	// Returns the dot product of the 2 given Vector2s.
	template <arithmetic T>
	constexpr float dot_product(const Vector2<T>& A, const Vector2<T>& B)
	{
		return A.x * B.x + A.y * B.y;
	}

	// Returns the magnitude of the Vector2 constructed by the elements x and y.
	template <arithmetic T>
	constexpr float magnitude(T x, T y)
	{
		return std::sqrtf(std::powf(static_cast<float>(x), 2.0f) + std::powf(static_cast<float>(y), 2.0f));
	}

	// Returns the magnitude of the given Vector2.
	template <arithmetic T>
	constexpr float magnitude(const Vector2<T>& vec)
	{
		return magnitude(vec.x, vec.y);
	}

	// Returns a Vector2 whose elements are the maximum of each of the 
	// pairs of elements in two specified Vector2s.
	template <arithmetic T>
	inline Vector2<T> max(const Vector2<T>& A, const Vector2<T>& B)
	{
		return Vector2<T>(std::max(A.x, B.x), std::max(A.y, B.y));
	}

	// Returns a Vector2 whose elements are the minimum of each of the 
	// pairs of elements in two specified Vector2s.
	template <arithmetic T>
	inline Vector2<T> min(const Vector2<T>& A, const Vector2<T>& B)
	{
		return Vector2<T>(std::min(A.x, B.x), std::min(A.y, B.y));
	}

	// Normalizes the Vector2 by scaling each of its components so that it
	// has a magnitude of 1.
	template <arithmetic T>
	void normalize(Vector2<T>& vec)
	{
		vec.divide(magnitude(vec));
	}

	// Returns a normal vector of the Vector2 constructed by the elements x and y.
	template <arithmetic T>
	inline Vector2<T> normal_vector(T x, T y)
	{
		return Vector2<T>(-y, x);
	}

	// Returns a normal vector of the given Vector2.
	template <arithmetic T>
	inline Vector2<T> normal_vector(const Vector2<T>& vec)
	{
		return normal_vector(vec);
	}

	// Prints the given Vector2 to std::cout.
	template <arithmetic T>
	inline void print(const Vector2<T>& vec)
	{
		std::cout << to_string(vec);
	}

	// Prints the given Vector2 to std::cout with a newline.
	template <arithmetic T>
	inline void println(const Vector2<T>& vec)
	{
		std::cout << to_string(vec) << '\n';
	}

	// Returns a std::string representation of the Vector2 constructed by the elements x and y.
	template <arithmetic T>
	inline std::string to_string(T x, T y)
	{
		return '<' + std::to_string(x) + ", " + std::to_string(y) + '>';
	}

	// Returns a std::string representation of the given Vector2.
	template <arithmetic T>
	inline std::string to_string(const Vector2<T>& vec)
	{
		return '<' + std::to_string(vec.x) + ", " + std::to_string(vec.y) + '>';
	}

	// Returns a std::wstring representation of the Vector2 constructed by the elements x and y.
	template <arithmetic T>
	inline std::wstring to_wstring(T x, T y)
	{
		return L'<' + std::to_wstring(x) + L", " + std::to_wstring(y) + L'>';
	}

	// Returns a std::wstring representation of the given Vector2.
	template <arithmetic T>
	inline std::wstring to_wstring(const Vector2<T>& vec)
	{
		return L'<' + std::to_wstring(vec.x) + L", " + std::to_wstring(vec.y) + L'>';
	}

	// Returns a unit vector of the Vector2 constructed by the elements x and y.
	template <arithmetic T>
	Vector2<float> unit_vector(T x, T y)
	{
		const float mag = magnitude(x, y);
		return Vector2f(static_cast<float>(x) / mag, static_cast<float>(y) / mag);
	}

	// Returns a unit vector of the given Vector2.
	template <arithmetic T>
	Vector2<float> unit_vector(const Vector2<T>& vec)
	{
		return unit_vector(vec.x, vec.y);
	}

	// Returns the vector projection of A onto B.
	template <arithmetic T>
	Vector2<float> vector_proj(const Vector2<T>& A, const Vector2<T>& B)
	{
		float f = (dot_product(A, B) / dot_product(B, B));
		return Vector2<float>(B.x * f, B.y * f);
	}

	///////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////

	typedef jlib::Vector2<bool>   Vector2b;
	typedef jlib::Vector2<i8>     Vector2c;
	typedef jlib::Vector2<u8>     Vector2uc;
	typedef jlib::Vector2<i16>    Vector2s;
	typedef jlib::Vector2<u16>    Vector2us;
	typedef jlib::Vector2<i32>    Vector2i;
	typedef jlib::Vector2<u32>    Vector2u;
	typedef jlib::Vector2<i64>    Vector2l;
	typedef jlib::Vector2<u64>    Vector2ul;
	typedef jlib::Vector2<size_t> Vector2uz;
	typedef jlib::Vector2<float>  Vector2f;
	typedef jlib::Vector2<double> Vector2d;

	///////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////

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
		return magnitude(A) < magnitude(B);
	}

	// Overload of binary operator <=
	template <arithmetic T>
	bool operator <= (const Vector2<T>& A, const Vector2<T>& B)
	{
		return magnitude(A) <= magnitude(B);
	}

	// Overload of binary operator >
	template <arithmetic T>
	bool operator > (const Vector2<T>& A, const Vector2<T>& B)
	{
		return magnitude(A) > magnitude(B);
	}

	// Overload of binary operator >=
	template <arithmetic T>
	bool operator >= (const Vector2<T>& A, const Vector2<T>& B)
	{
		return magnitude(A) >= magnitude(B);
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
		A.add(B);
		return A;
	}

	// Overload of binary operator -=
	template <arithmetic T>
	Vector2<T>& operator -= (Vector2<T>& A, const Vector2<T>& B)
	{
		A.subtract(B);
		return A;
	}
	
	// Overload of binary operator *=
	template <arithmetic T>
	Vector2<T>& operator *= (Vector2<T>& A, const Vector2<T>& B)
	{
		A.multiply(B);
		return A;
	}

	// Overload of binary operator *=
	template <arithmetic T, arithmetic U>
	Vector2<T>& operator *= (Vector2<T>& A, U scalar)
	{
		A.multiply(scalar);
		return A;
	}

	// Overload of binary operator /=
	template <arithmetic T, arithmetic U>
	Vector2<T>& operator /= (Vector2<T>& A, U scalar)
	{
		A.divide(scalar);
		return A;
	}

	// Overload of binary operator /=
	template <arithmetic T>
	Vector2<T>& operator /= (Vector2<T>& A, const Vector2<T>& B)
	{
		A.divide(B);
		return A;
	}

	// Overload of std::ostream operator <<
	template <arithmetic T>
	std::ostream& operator << (std::ostream& os, const Vector2<T>& vec)
	{
		os << to_string(vec);
		return os;
	}

	// Overload of std::wostream operator <<
	template <arithmetic T>
	std::wostream& operator << (std::wostream& wos, const Vector2<T>& vec)
	{
		wos << to_wstring(vec);
		return wos;
	}
}