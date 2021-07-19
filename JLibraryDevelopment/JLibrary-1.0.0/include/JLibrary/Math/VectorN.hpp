// JLibraryDevelopment
// VectorN.hpp
// Created on 2021-07-06 by Justyn Durnford
// Last modified on 2021-07-17 by Justyn Durnford
// Header file for the VectorN template class.

#pragma once

#include <JLibrary/Math/PointN.hpp>

namespace jlib
{
	// Utility template class for representing, manipulating
	// and computing with vectors with N-dimensions.
	template <std_arithmetic T, std::size_t N> class VectorN
	{
		// Copies each element from the given source.
		void copyFrom(const T* src_begin)
		{
			for (std::size_t i(0); i < N; ++i)
				data[i] = src_begin[i];
		}

		public:

		std::array<T, N> data;

		// Default constructor.
		// Sets each component of the VectorN to 0.
		VectorN()
		{
			for (T& elem : data)
				elem = static_cast<T>(0);
		}

		// Constructs the VectorN from the given coordinates.
		VectorN(std::initializer_list<T> list)
		{
			for (std::size_t i(0); i < N; ++i)
				data[i] = *(list.begin() + i);
		}

		// Constructs the VectorN as the displacement vector of the two PointNs.
		VectorN (const PointN<T, N>& A, const PointN<T, N>& B)
		{
			for (std::size_t i(0); i < N; ++i)
				data[i] = B[i] - A[i];
		}

		// Constructs the VectorN from another type of VectorN.
		// This constructor doesn't replace the copy constructor,
		// it's called only when U != T.
		template <std_arithmetic U>
		VectorN(const VectorN<U, N>& other)
		{
			for (std::size_t i(0); i < N; ++i)
				data[i] = static_cast<T>(other.data[i]);
		}

		// Constructs the VectorN from the given coordinates.
		VectorN& operator = (std::initializer_list<T> list)
		{
			for (std::size_t i(0); i < N; ++i)
				data[i] = *(list.begin() + i);
			return *this;
		}

		// Returns the amount of dimensions the VectorN has.
		std::size_t dimensions() const
		{
			return N;
		}

		// Returns the first element of the VectorN.
		// Throws a std::out_of_range if the VectorN is empty.
		T& first()
		{
			if (N == 0)
				throw std::out_of_range("ERROR: The PointN has 0 dimensions.");

			return data[0];
		}

		// Returns the first element of the VectorN.
		// Throws a std::out_of_range if the VectorN is empty.
		const T& first() const
		{
			if (N == 0)
				throw std::out_of_range("ERROR: The PointN has 0 dimensions.");

			return data[0];
		}

		// Returns the last element of the VectorN.
		// Throws a std::out_of_range if the VectorN is empty.
		T& last()
		{
			if (N == 0)
				throw std::out_of_range("ERROR: The PointN has 0 dimensions.");

			return data[N - 1];
		}

		// Returns the last element of the VectorN.
		// Throws a std::out_of_range if the VectorN is empty.
		const T& last() const
		{
			if (N == 0)
				throw std::out_of_range("ERROR: The PointN has 0 dimensions.");

			return data[N - 1];
		}

		// Returns the element at the given index.
		// Throws a std::out_of_range if given an invalid index.
		T& at(std::size_t index)
		{
			if (index >= N)
				throw std::out_of_range("ERROR: Invalid PointN index.");

			return data[index];
		}

		// Returns the element at the given index.
		// Throws a std::out_of_range if given an invalid index.
		const T& at(std::size_t index) const
		{
			if (index >= N)
				throw std::out_of_range("ERROR: Invalid PointN index.");

			return data[index];
		}

		// Returns the magnitude of the VectorN.
		float magnitude() const
		{
			float value = 0.f;

			for (std::size_t i(0); i < N; ++i)
				value += std::pow(data[i], 2);

			return std::sqrt(value);
		}

		// Returns the endpoint of the VectorN.
		PointN<T, N> endpoint() const
		{
			PointN<T, N> P;

			for (std::size_t i(0); i < N; ++i)
				P[i] = data[i];

			return P;
		}

		// Returns the element at the given index.
		T& operator [] (std::size_t index)
		{
			return data[index];
		}

		// Returns the element at the given index.
		const T& operator [] (std::size_t index) const
		{
			return data[index];
		}

		// Returns a std::string representation of the VectorN.
		std::string toString() const
		{
			if (N == 0)
				return "";
			if (N == 1)
				return '<' + std::to_string(data[0]) + '>';

			std::string str;

			str += '<';
			for (std::size_t i(0); i < N - 1; ++i)
				str += std::to_string(data[i]) + ", ";
			str += std::to_string(data[N - 1]) + '>';

			return str;
		}

		// Returns a std::wstring representation of the VectorN.
		std::wstring toWideString() const
		{
			if (N == 0)
				return L"";
			if (N == 1)
				return L'<' + std::to_wstring(data[0]) + L'>';

			std::wstring str;

			str += L'<';
			for (std::size_t i(0); i < N - 1; ++i)
				str += std::to_wstring(data[i]) + L", ";
			str += std::to_wstring(data[N - 1]) + L'>';

			return str;
		}
	};

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

	// Converts the given PointN to a VectorN.
	template <std_arithmetic T, std::size_t N>
	VectorN<T, N> point_to_vector(const PointN<T, N>& P)
	{
		VectorN<T, N> V;

		for (std::size_t i = 0; i < N; ++i)
			V[i] = P[i];

		return V;
	}

	// Returns a unit vector in the direction of the VectorN.
	template <std_arithmetic T, std::size_t N>
	VectorN<float, N> unit_vector(const VectorN<T, N>& A)
	{
		return VectorN<T, N>(A) / A.magnitude();
	}

	// Returns the dot product of the 2 given VectorNs.
	template <std_arithmetic T, std::size_t N>
	float dot_product(const VectorN<T, N>& A, const VectorN<T, N>& B)
	{
		float value = 0.f;

		for (std::size_t i(0); i < N; ++i)
			value += (A[i] * B[i]);

		return value;
	}

	// Returns the scalar projection of A onto B.
	template <std_arithmetic T, std::size_t N>
	float scalar_proj(const VectorN<T, N>& A, const VectorN<T, N>& B)
	{
		return dot_product(A, B) / A.magnitude();
	}

	// Returns the vector projection of A onto B.
	template <std_arithmetic T, std::size_t N>
	VectorN<float, N> vector_proj(const VectorN<T, N>& A, const VectorN<T, N>& B)
	{
		float f = (dot_product(A, B) / dot_product(A, A));
		VectorN<float, N> V;

		for (std::size_t i(0); i < N; ++i)
			V[i] *= f;

		return V;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

// Overload of binary operator ==
template <jlib::std_arithmetic T, std::size_t N>
bool operator == (const jlib::VectorN<T, N>& A, const jlib::VectorN<T, N>& B)
{
	return A.data == B.data;
}

// Overload of binary operator !=
template <jlib::std_arithmetic T, std::size_t N>
bool operator != (const jlib::VectorN<T, N>& A, const jlib::VectorN<T, N>& B)
{
	return A.data != B.data;
}

// Overload of unary operator -
template <jlib::std_arithmetic T, std::size_t N>
jlib::VectorN<T, N> operator - (const jlib::VectorN<T, N>& A)
{
	jlib::VectorN<T, N> V;

	for (std::size_t i(0); i < N; ++i)
		V[i] = A[i] * -1;

	return V;
}

// Overload of binary operator +
template <jlib::std_arithmetic T, std::size_t N>
jlib::VectorN<T, N> operator + (const jlib::VectorN<T, N>& A, const jlib::VectorN<T, N>& B)
{
	jlib::VectorN<T, N> V;

	for (std::size_t i(0); i < N; ++i)
		V[i] = A[i] + B[i];

	return V;
}

// Overload of binary operator -
template <jlib::std_arithmetic T, std::size_t N>
jlib::VectorN<T, N> operator - (const jlib::VectorN<T, N>& A, const jlib::VectorN<T, N>& B)
{
	jlib::VectorN<T, N> V;

	for (std::size_t i(0); i < N; ++i)
		V[i] = A[i] - B[i];

	return V;
}

// Overload of binary operator *
template <jlib::std_arithmetic T, jlib::std_arithmetic U, std::size_t N>
jlib::VectorN<T, N> operator * (const jlib::VectorN<T, N>& A, U scalar)
{
	jlib::VectorN<T, N> V;

	for (std::size_t i(0); i < N; ++i)
		V[i] = A[i] * scalar;

	return V;
}

// Overload of binary operator /
template <jlib::std_arithmetic T, jlib::std_arithmetic U, std::size_t N>
jlib::VectorN<T, N> operator / (const jlib::VectorN<T, N>& A, U scalar)
{
	jlib::VectorN<T, N> V;

	for (std::size_t i(0); i < N; ++i)
		V[i] = A[i] / scalar;

	return V;
}

// Overload of binary operator +=
template <jlib::std_arithmetic T, std::size_t N>
jlib::VectorN<T, N>& operator += (const jlib::VectorN<T, N>& A, const jlib::VectorN<T, N>& B)
{
	for (std::size_t i(0); i < N; ++i)
		A[i] += B[i];

	return A;
}

// Overload of binary operator -=
template <jlib::std_arithmetic T, std::size_t N>
jlib::VectorN<T, N>& operator -= (const jlib::VectorN<T, N>& A, const jlib::VectorN<T, N>& B)
{
	for (std::size_t i(0); i < N; ++i)
		A[i] -= B[i];

	return A;
}

// Overload of binary operator *=
template <jlib::std_arithmetic T, jlib::std_arithmetic U, std::size_t N>
jlib::VectorN<T, N>& operator *= (jlib::VectorN<T, N>& A, U scalar)
{
	for (std::size_t i(0); i < N; ++i)
		A[i] *= scalar;

	return A;
}

// Overload of binary operator /=
template <jlib::std_arithmetic T, jlib::std_arithmetic U, std::size_t N>
jlib::VectorN<T, N>& operator /= (jlib::VectorN<T, N>& A, U scalar)
{
	for (std::size_t i(0); i < N; ++i)
		A[i] /= scalar;

	return A;
}