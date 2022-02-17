// JLibrary
// VectorN.ixx
// Created on 2022-01-08 by Justyn Durnford
// Last modified on 2022-02-17 by Justyn Durnford
// Module file for the VectorN template class.

module;

#include "Arithmetic.hpp"
#include "IntegerTypedefs.hpp"

#include <cmath>
#include <stdexcept>
#include <string>

export module VectorN;

import FixedArray;
import MiscTemplateFunctions;

export namespace jlib
{
	// Utility template class for representing, manipulating
	// and computing with vectors with N-dimensions.
	template <arithmetic T, std::size_t N> class VectorN
	{
		public:

		using value_type = T;
		using size_type = std::size_t;
		using difference_type = std::ptrdiff_t;
		using pointer = value_type*;
		using const_pointer = const value_type*;
		using reference = value_type&;
		using const_reference = const value_type&;
		using iterator = value_type*;
		using const_iterator = const value_type*;
		using reverse_iterator = std::reverse_iterator<iterator>;
		using const_reverse_iterator = const std::reverse_iterator<iterator>;

		private:

		FixedArray<T, N> _data;

		public:

		// Default constructor.
		// Sets each component of the VectorN to 0.
		VectorN()
		{
			for (size_type i = 0; i < N; ++i)
				_data[i] = static_cast<T>(0);
		}

		// Constructs the VectorN from the given coordinates.
		VectorN(std::initializer_list<T> elems)
		{
			std::copy(elems.begin(), elems.end(), _data.data());
		}

		// Constructs the VectorN as the displacement vector of the two points.
		VectorN(const VectorN& A, const VectorN& B)
		{
			for (size_type i(0); i < N; ++i)
				_data[i] = B._data[i] - A._data[i];
		}

		// Constructs the VectorN from another type of VectorN.
		// This constructor doesn't replace the copy constructor,
		// it's called only when U != T.
		template <arithmetic U>
		VectorN(const VectorN<U, N>& other)
		{
			jlib::copy(other.data(), other.data() + N, data());
		}

		// Constructs the VectorN from the given coordinates.
		VectorN& operator = (std::initializer_list<T> elems)
		{
			std::copy(elems.begin(), elems.end(), _data.data());
			return *this;
		}

		// Copies the components of a different type of VectorN.
		template <arithmetic U>
		void copyFrom(const VectorN<U, N>& other)
		{
			jlib::copy(other.data(), other.data() + N, data());
		}

		// Returns the amount of dimensions the VectorN has.
		size_type dimensions() const
		{
			return N;
		}

		// Returns the first element of the VectorN.
		reference first()
		{
			return _data[0];
		}

		// Returns the first element of the VectorN.
		const_reference first() const
		{
			return _data[0];
		}

		// Returns the last element of the VectorN.
		reference last()
		{
			return _data[N - 1];
		}

		// Returns the last element of the VectorN.
		const_reference last() const
		{
			return _data[N - 1];
		}

		// Returns the pointer to the elements of the VectorN.
		pointer data()
		{
			return _data.data();
		}

		// Returns the pointer to the elements of the VectorN.
		const_pointer data() const
		{
			return _data.data();
		}

		// Returns an iterator pointing to the first element of the VectorN.
		// Returns nullptr if the dimension count is 0.
		iterator begin()
		{
			return _data;
		}

		// Returns an iterator pointing to the first element of the VectorN.
		// Returns nullptr if the dimension count is 0.
		const_iterator begin() const
		{
			return _data;
		}

		// Returns an iterator pointing to the first element of the VectorN.
		// Returns nullptr if the dimension count is 0.
		const_iterator cbegin() const
		{
			return _data;
		}

		// Returns a reverse iterator pointing to the first element of the VectorN.
		// Returns nullptr if the dimension count is 0.
		reverse_iterator rbegin()
		{
			return _data;
		}

		// Returns a reverse iterator pointing to the first element of the VectorN.
		// Returns nullptr if the dimension count is 0.
		const_reverse_iterator rbegin() const
		{
			return _data;
		}

		// Returns a reverse iterator pointing to the first element of the VectorN.
		// Returns nullptr if the dimension count is 0.
		const_reverse_iterator crbegin() const
		{
			return _data;
		}

		// Returns an iterator pointing to 1 past the last element of the VectorN.
		// Returns nullptr if the dimension count is 0.
		iterator end()
		{
			return _data + N;
		}

		// Returns an iterator pointing to 1 past the last element of the VectorN.
		// Returns nullptr if the dimension count is 0.
		const_iterator end() const
		{
			return _data + N;
		}

		// Returns an iterator pointing to 1 past the last element of the VectorN.
		// Returns nullptr if the dimension count is 0.
		const_iterator cend() const
		{
			return _data + N;
		}

		// Returns a reverse iterator pointing to 1 past the last element of the VectorN.
		// Returns nullptr if the dimension count is 0.
		reverse_iterator rend()
		{
			return _data + N;
		}

		// Returns a reverse iterator pointing to 1 past the last element of the VectorN.
		// Returns nullptr if the dimension count is 0.
		const_reverse_iterator rend() const
		{
			return _data + N;
		}

		// Returns a reverse iterator pointing to 1 past the last element of the VectorN.
		// Returns nullptr if the dimension count is 0.
		const_reverse_iterator crend() const
		{
			return _data + N;
		}

		// Returns the element at the given index.
		// Throws a std::out_of_range if given an invalid index.
		reference at(size_type index)
		{
			if (index >= N)
				throw std::out_of_range("ERROR: Invalid VectorN index.");
			return _data[index];
		}

		// Returns the element at the given index.
		// Throws a std::out_of_range if given an invalid index.
		const_reference at(size_type index) const
		{
			if (index >= N)
				throw std::out_of_range("ERROR: Invalid VectorN index.");
			return _data[index];
		}

		// Sets the element at the given index to the given value.
		// Throws a std::out_of_range if given an invalid index.
		void set(size_type index, const_reference value)
		{
			if (index >= N)
				throw std::out_of_range("ERROR: Invalid VectorN index.");
			_data[index] = value;
		}

		// Returns the magnitude of the VectorN.
		float magnitude() const
		{
			float value = 0.0f;

			for (size_type i = 0; i < N; ++i)
				value += std::powf(_data[i], 2);

			return std::sqrtf(value);
		}

		// Returns a unit vector in the direction of this VectorN.
		VectorN<float, N> unitVector() const
		{
			float m = magnitude();
			VectorN<float, N> new_vec(*this);

			for (size_type i = 0; i < N; ++i)
				new_vec[i] /= m;

			return new_vec;
		}

		// Returns a std::string representation of the VectorN.
		std::string toString() const
		{
			if (N == 0)
				return "";
			if (N == 1)
				return '<' + std::to_string(_data[0]) + '>';

			std::string str;

			str += '<';
			for (size_type i = 0; i < N - 1; ++i)
				str += std::to_string(_data[i]) + ", ";
			str += std::to_string(_data[N - 1]) + '>';

			return str;
		}

		// Returns a std::wstring representation of the VectorN.
		std::wstring toWideString() const
		{
			if (N == 0)
				return L"";
			if (N == 1)
				return L'<' + std::to_wstring(_data[0]) + L'>';

			std::wstring str;

			str += L'<';
			for (size_type i = 0; i < N - 1; ++i)
				str += std::to_wstring(_data[i]) + L", ";
			str += std::to_wstring(_data[N - 1]) + L'>';

			return str;
		}

		// Returns the element at the given index.
		reference operator [] (size_type index)
		{
			return _data[index];
		}

		// Returns the element at the given index.
		const_reference operator [] (size_type index) const
		{
			return _data[index];
		}
	};

	///////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////

	// Returns the distance between the 2 given JVectorNs.
	template <arithmetic T, std::size_t N>
	float distance(const VectorN<T, N>& A, const VectorN<T, N>& B)
	{
		VectorN<T, N> C(A, B);
		return C.magnitude();
	}

	// Returns the dot product of the 2 given JVectorNs.
	template <arithmetic T, std::size_t N>
	float dot_product(const VectorN<T, N>& A, const VectorN<T, N>& B)
	{
		float value = 0.0f;

		for (std::size_t i(0); i < N; ++i)
			value += (A[i] * B[i]);

		return value;
	}

	// Returns the scalar projection of A onto B.
	template <arithmetic T, std::size_t N>
	float comp_proj(const VectorN<T, N>& A, const VectorN<T, N>& B)
	{
		return dot_product(A, B) / B.magnitude();
	}

	// Returns the vector projection of A onto B.
	template <arithmetic T, std::size_t N>
	VectorN<float, N> vector_proj(const VectorN<T, N>& A, const VectorN<T, N>& B)
	{
		float f = (dot_product(A, B) / dot_product(A, A));
		VectorN<float, N> V;

		for (std::size_t i(0); i < N; ++i)
			V[i] *= f;

		return V;
	}

	///////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////

	typedef jlib::VectorN<bool, 4>   Vector4b;
	typedef jlib::VectorN<i8, 4>     Vector4c;
	typedef jlib::VectorN<u8, 4>     Vector4uc;
	typedef jlib::VectorN<i16, 4>    Vector4s;
	typedef jlib::VectorN<u16, 4>    Vector4us;
	typedef jlib::VectorN<i32, 4>    Vector4i;
	typedef jlib::VectorN<u32, 4>    Vector4u;
	typedef jlib::VectorN<float, 4>  Vector4f;

	///////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////

	// Overload of binary operator ==
	template <arithmetic T, std::size_t N>
	bool operator == (const VectorN<T, N>& A, const VectorN<T, N>& B)
	{
		for (std::size_t i = 0; i < N; ++i)
		{
			if (A[i] != B[i])
				return false;
		}

		return true;
	}

	// Overload of binary operator !=
	template <arithmetic T, std::size_t N>
	bool operator != (const VectorN<T, N>& A, const VectorN<T, N>& B)
	{
		for (std::size_t i = 0; i < N; ++i)
		{
			if (A[i] != B[i])
				return true;
		}

		return false;
	}

	// Overload of binary operator <
	template <arithmetic T, std::size_t N>
	bool operator < (const VectorN<T, N>& A, const VectorN<T, N>& B)
	{
		return A.magnitude() < B.magnitude();
	}

	// Overload of binary operator <=
	template <arithmetic T, std::size_t N>
	bool operator <= (const VectorN<T, N>& A, const VectorN<T, N>& B)
	{
		return A.magnitude() <= B.magnitude();
	}

	// Overload of binary operator >
	template <arithmetic T, std::size_t N>
	bool operator > (const VectorN<T, N>& A, const VectorN<T, N>& B)
	{
		return A.magnitude() > B.magnitude();
	}

	// Overload of binary operator >=
	template <arithmetic T, std::size_t N>
	bool operator >= (const VectorN<T, N>& A, const VectorN<T, N>& B)
	{
		return A.magnitude() >= B.magnitude();
	}

	// Overload of unary operator -
	template <arithmetic T, std::size_t N>
	VectorN<T, N> operator - (const VectorN<T, N>& A)
	{
		VectorN<T, N> V;

		for (std::size_t i(0); i < N; ++i)
			V[i] = A[i] * -1;

		return V;
	}

	// Overload of binary operator +
	template <arithmetic T, std::size_t N>
	VectorN<T, N> operator + (const VectorN<T, N>& A, const VectorN<T, N>& B)
	{
		VectorN<T, N> V;

		for (std::size_t i(0); i < N; ++i)
			V[i] = A[i] + B[i];

		return V;
	}

	// Overload of binary operator -
	template <arithmetic T, std::size_t N>
	VectorN<T, N> operator - (const VectorN<T, N>& A, const VectorN<T, N>& B)
	{
		VectorN<T, N> V;

		for (std::size_t i(0); i < N; ++i)
			V[i] = A[i] - B[i];

		return V;
	}

	// Overload of binary operator *
	template <arithmetic T, std::size_t N>
	VectorN<T, N> operator * (const VectorN<T, N>& A, const VectorN<T, N>& B)
	{
		VectorN<T, N> V;

		for (std::size_t i(0); i < N; ++i)
			V[i] = A[i] * B[i];

		return V;
	}

	// Overload of binary operator *
	template <arithmetic T, arithmetic U, std::size_t N>
	VectorN<T, N> operator * (const VectorN<T, N>& A, U scalar)
	{
		VectorN<T, N> V;

		for (std::size_t i(0); i < N; ++i)
			V[i] = A[i] * scalar;

		return V;
	}

	// Overload of binary operator *
	template <arithmetic T, arithmetic U, std::size_t N>
	VectorN<T, N> operator * (U scalar, const VectorN<T, N>& A)
	{
		VectorN<T, N> V;

		for (std::size_t i(0); i < N; ++i)
			V[i] = A[i] * scalar;

		return V;
	}

	// Overload of binary operator /
	template <arithmetic T, std::size_t N>
	VectorN<T, N> operator / (const VectorN<T, N>& A, const VectorN<T, N>& B)
	{
		VectorN<T, N> V;

		for (std::size_t i(0); i < N; ++i)
			V[i] = A[i] / B[i];

		return V;
	}

	// Overload of binary operator /
	template <arithmetic T, arithmetic U, std::size_t N>
	VectorN<T, N> operator / (const VectorN<T, N>& A, U scalar)
	{
		VectorN<T, N> V;

		for (std::size_t i(0); i < N; ++i)
			V[i] = A[i] / scalar;

		return V;
	}

	// Overload of binary operator *
	template <arithmetic T, arithmetic U, std::size_t N>
	VectorN<T, N> operator / (U scalar, const VectorN<T, N>& A)
	{
		VectorN<T, N> V;

		for (std::size_t i(0); i < N; ++i)
			V[i] = scalar / A[i];

		return V;
	}

	// Overload of binary operator +=
	template <arithmetic T, std::size_t N>
	VectorN<T, N>& operator += (VectorN<T, N>& A, const VectorN<T, N>& B)
	{
		for (std::size_t i(0); i < N; ++i)
			A[i] += B[i];

		return A;
	}

	// Overload of binary operator -=
	template <arithmetic T, std::size_t N>
	VectorN<T, N>& operator -= (VectorN<T, N>& A, const VectorN<T, N>& B)
	{
		for (std::size_t i(0); i < N; ++i)
			A[i] -= B[i];

		return A;
	}

	// Overload of binary operator *=
	template <arithmetic T, arithmetic U, std::size_t N>
	VectorN<T, N>& operator *= (VectorN<T, N>& A, U scalar)
	{
		for (std::size_t i(0); i < N; ++i)
			A[i] *= scalar;

		return A;
	}

	// Overload of binary operator /=
	template <arithmetic T, arithmetic U, std::size_t N>
	VectorN<T, N>& operator /= (VectorN<T, N>& A, U scalar)
	{
		for (std::size_t i(0); i < N; ++i)
			A[i] /= scalar;

		return A;
	}

	// Overload of std::ostream operator <<
	template <arithmetic T, std::size_t N>
	std::ostream& operator << (std::ostream& os, const VectorN<T, N>& A)
	{
		os << A.toString();
		return os;
	}

	// Overload of std::wostream operator <<
	template <arithmetic T, std::size_t N>
	std::wostream& operator << (std::wostream& wos, const VectorN<T, N>& A)
	{
		wos << A.toWideString();
		return wos;
	}
}