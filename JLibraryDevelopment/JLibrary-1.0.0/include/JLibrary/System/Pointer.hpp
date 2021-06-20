// JLibraryDevelopment
// Pointer.hpp
// Created on 2021-06-18 by Justyn Durnford
// Last modified on 2021-06-19 by Justyn Durnford
// Header file for the Pointer template class.

#pragma once

#include <cstddef>
#include <compare>

namespace jlib
{
	template <typename T> class Pointer
	{
		T* ptr_;

		public:

		// Default constructor.
		Pointer()
		{
			ptr_ = nullptr;
		}

		// Raw-pointer constructor.
		// Sets the given raw-pointer to nullptr.
		Pointer(T* ptr)
		{
			ptr_ = ptr;
			ptr = nullptr;
		}

		// Copy constructor.
		Pointer(const Pointer& other) = default;

		// Move constructor.
		Pointer(Pointer&& other) = default;

		// Raw-pointer assignment operator.
		// Sets the given raw-pointer to nullptr.
		Pointer& operator = (T* ptr)
		{
			ptr_ = ptr;
			ptr = nullptr;
			return *this;
		}

		// Copy assignment operator.
		Pointer& operator (const Pointer& other) = default;

		// Move assignment operator.
		Pointer& operator (Pointer && other) = default;

		// Destructor.
		~Pointer() = default;

		// Returns the stored raw-pointer.
		T* get()
		{
			return ptr_;
		}

		// Returns the stored raw-pointer.
		const T* get() const
		{
			return ptr_;
		}

		// Sets the stored raw-pointer to the given
		// raw-pointer.
		void set(T* ptr)
		{
			ptr_ = ptr;
		}

		// Resets the stored raw-pointer to nullptr.
		void reset()
		{
			ptr_ = nullptr;
		}

		// Releases the raw-pointer and sets the stored 
		// value to nullptr.
		T* release()
		{
			T* ptr = ptr_;
			ptr_ = nullptr;
			return ptr;
		}

		// Overload of dereference operator.
		T& operator * ()
		{
			return *ptr_;
		}

		// Overload of dereference operator.
		const T& operator * () const
		{
			return *ptr_;
		}

		// Overload of array-dereference operator.
		T& operator [] (std::ptrdiff_t offset)
		{
			return ptr_ + offset;
		}

		// Overload of array-dereference operator.
		const T& operator [] (std::ptrdiff_t offset) const
		{
			return ptr_ + offset;
		}

		// Overload of structure pointer dereference operator.
		T* operator -> ()
		{
			return ptr_;
		}

		// 
		const T* operator -> () const
		{
			return ptr_;
		}

		// Overload of implicit bool-cast operator.
		// Returns true if the stored raw-pointer
		// is NOT nullptr.
		operator bool() const noexcept
		{
			return ptr_ != nullptr;
		}
	};
}

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////

// Overload of binary == operator
template <typename T>
bool operator == (const jlib::Pointer<T>& A, const jlib::Pointer<T>& B)
{
	return A.get() == B.get();
}

// Overload of binary == operator
template <typename T>
bool operator == (const jlib::Pointer<T>& A, T* B)
{
	return A.get() == B;
}

// Overload of binary == operator
template <typename T>
bool operator == (const jlib::Pointer<T>& A, std::nullptr_t)
{
	return A.get() == nullptr;
}

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////

// Overload of binary != operator
template <typename T>
bool operator != (const jlib::Pointer<T>& A, const jlib::Pointer<T>& B)
{
	return A.get() != B.get();
}

// Overload of binary != operator
template <typename T>
bool operator != (const jlib::Pointer<T>& A, T* B)
{
	return A.get() != B;
}

// Overload of binary != operator
template <typename T>
bool operator != (const jlib::Pointer<T>& A, std::nullptr_t)
{
	return A.get() != nullptr;
}

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////

// Overload of binary < operator
template <typename T>
bool operator < (const jlib::Pointer<T>& A, const jlib::Pointer<T>& B)
{
	return A.get() < B.get();
}

// Overload of binary < operator
template <typename T>
bool operator < (const jlib::Pointer<T>& A, T* B)
{
	return A.get() < B;
}

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////

// Overload of binary <= operator
template <typename T>
bool operator <= (const jlib::Pointer<T>& A, const jlib::Pointer<T>& B)
{
	return A.get() <= B.get();
}

// Overload of binary <= operator
template <typename T>
bool operator <= (const jlib::Pointer<T>& A, T* B)
{
	return A.get() <= B;
}

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////

// Overload of binary > operator
template <typename T>
bool operator > (const jlib::Pointer<T>& A, const jlib::Pointer<T>& B)
{
	return A.get() > B.get();
}

// Overload of binary > operator
template <typename T>
bool operator > (const jlib::Pointer<T>& A, T* B)
{
	return A.get() > B;
}

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////

// Overload of binary >= operator
template <typename T>
bool operator >= (const jlib::Pointer<T>& A, const jlib::Pointer<T>& B)
{
	return A.get() >= B.get();
}

// Overload of binary >= operator
template <typename T>
bool operator >= (const jlib::Pointer<T>& A, T* B)
{
	return A.get() >= B;
}

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////

// Overload of binary <=> operator
template <typename T>
std::strong_ordering operator <=> (const jlib::Pointer<T>& A, const jlib::Pointer<T>& B)
{
	if (A.get() < B.get())
		return std::strong_ordering::less;
	if (A.get() > B.get())
		return std::strong_ordering::greater;
	return std::strong_ordering::equivalent;
}

// Overload of binary <=> operator
template <typename T>
std::strong_ordering operator <=> (const jlib::Pointer<T>& A, T* B)
{
	if (A.get() < B)
		return std::strong_ordering::less;
	if (A.get() > B)
		return std::strong_ordering::greater;
	return std::strong_ordering::equivalent;
}