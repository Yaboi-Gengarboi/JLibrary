// JLibraryDevelopment
// Pointer.hpp
// Created on 2021-07-02 by Justyn Durnford
// Last modified on 2021-07-02 by Justyn Durnford
// Header file for the Pointer template class.

#pragma once

#include <compare>
#include <cstddef>

namespace jlib
{
	// 
	template <typename T> class Pointer
	{
		T* ptr_;

		public:

		// Default constructor.
		// Sets the Pointer to nullptr.
		Pointer()
		{
			ptr_ = nullptr;
		}
		
		// Primary constructor.
		Pointer(T* ptr)
		{
			ptr_ = ptr;
		}

		// Nullptr constructor.
		Pointer(std::nullptr_t)
		{
			ptr_ = nullptr;
		}

		// Copy constructor.
		Pointer(const Pointer& other) = default;

		// Move constructor.
		Pointer(Pointer&& other) noexcept
		{
			ptr_ = other.ptr_;
			other.ptr_ = nullptr;
		}

		// Primary assignment operator.
		Pointer& operator = (T* ptr)
		{
			ptr_ = ptr;
			return *this;
		}

		// Nullptr assignment operator.
		Pointer& operator = (std::nullptr_t)
		{
			ptr_ = nullptr;
			return *this;
		}

		// Copy assignment operator.
		Pointer& operator = (const Pointer& other) = default;

		// Move assignment operator.
		Pointer& operator = (Pointer && other) noexcept
		{
			ptr_ = other.ptr_;
			other.ptr_ = nullptr;
			return *this;
		}

		// Returns a read-only copy of the underlying pointer.
		const T* get() const
		{
			return ptr_;
		}

		// Returns true if the Pointer is NOT nullptr.
		bool isValid() const
		{
			return ptr_ != nullptr;
		}

		// Returns true if the Pointer IS nullptr.
		bool isNullptr() const
		{
			return ptr_ == nullptr;
		}

		// Sets the Pointer to the given address.
		void set(T* ptr)
		{
			ptr_ = ptr;
		}

		// Sets the Pointer to nullptr.
		void reset()
		{
			ptr_ = nullptr;
		}

		// Returns the value of the Pointer and
		// resets the value.
		T* release()
		{
			T* ptr = ptr_;
			ptr_ = nullptr;
			return ptr;
		}

		// Overload of operator *
		T& operator * ()
		{
			return *ptr_;
		}

		// Overload of operator *
		const T& operator * () const
		{
			return *ptr_;
		}

		// Overload of operator ->
		T* operator -> ()
		{
			return ptr_;
		}

		// Overload of operator ->
		const T* operator -> () const
		{
			return ptr_;
		}

		// Overload of operator []
		T& operator [] (std::ptrdiff_t offset)
		{
			return *(ptr_ + offset);
		}

		// Overload of operator []
		const T& operator [] (std::ptrdiff_t offset) const
		{
			return *(ptr_ + offset);
		}
	};
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

// Overload of binary operator ==
template <typename T>
bool operator == (const jlib::Pointer<T>& A, const jlib::Pointer<T>& B)
{
	return A.get() == B.get();
}

// Overload of binary operator ==
template <typename T>
bool operator == (const jlib::Pointer<T>& A, const T* B)
{
	return A.get() == B;
}

// Overload of binary operator ==
template <typename T>
bool operator == (const jlib::Pointer<T>& A, std::nullptr_t)
{
	return A.get() == nullptr;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

// Overload of binary operator !=
template <typename T>
bool operator != (const jlib::Pointer<T>& A, const jlib::Pointer<T>& B)
{
	return A.get() != B.get();
}

// Overload of binary operator !=
template <typename T>
bool operator != (const jlib::Pointer<T>& A, const T* B)
{
	return A.get() != B;
}

// Overload of binary operator !=
template <typename T>
bool operator != (const jlib::Pointer<T>& A, std::nullptr_t)
{
	return A.get() != nullptr;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

// Overload of binary operator <
template <typename T>
bool operator < (const jlib::Pointer<T>& A, const jlib::Pointer<T>& B)
{
	return A.get() < B.get();
}

// Overload of binary operator <
template <typename T>
bool operator < (const jlib::Pointer<T>& A, const T* B)
{
	return A.get() < B;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

// Overload of binary operator <=
template <typename T>
bool operator <= (const jlib::Pointer<T>& A, const jlib::Pointer<T>& B)
{
	return A.get() <= B.get();
}

// Overload of binary operator <=
template <typename T>
bool operator <= (const jlib::Pointer<T>& A, const T* B)
{
	return A.get() <= B;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

// Overload of binary operator >
template <typename T>
bool operator > (const jlib::Pointer<T>& A, const jlib::Pointer<T>& B)
{
	return A.get() > B.get();
}

// Overload of binary operator >
template <typename T>
bool operator > (const jlib::Pointer<T>& A, const T* B)
{
	return A.get() > B;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

// Overload of binary operator >=
template <typename T>
bool operator >= (const jlib::Pointer<T>& A, const jlib::Pointer<T>& B)
{
	return A.get() >= B.get();
}

// Overload of binary operator >=
template <typename T>
bool operator >= (const jlib::Pointer<T>& A, const T* B)
{
	return A.get() >= B;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

// Overload of binary operator <=>
template <typename T>
std::strong_ordering operator <=> (const jlib::Pointer<T>& A, const jlib::Pointer<T>& B)
{
	return A.get() <=> B.get();
}

// Overload of binary operator <=>
template <typename T>
std::strong_ordering operator <=> (const jlib::Pointer<T>& A, const T* B)
{
	return A.get() <=> B;
}