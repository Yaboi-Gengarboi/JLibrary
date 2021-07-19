// JLibraryDevelopment
// Pointer.hpp
// Created on 2021-07-16 by Justyn Durnford
// Last modified on 2021-07-17 by Justyn Durnford
// Header file for the Ptr template class.

#pragma once

#include <compare>
#include <cstddef>

namespace jlib
{
	// Utility template wrapper class for pointers.
	// This class is NOT intended to be used for memory
	// allocation, it is simply for pointing to objects.
	template <typename T> class Ptr
	{
		T* ptr_;

		public:

		// Default constructor.
		Ptr()
		{
			ptr_ = nullptr;
		}

		// Value constructor.
		Ptr(T* ptr)
		{
			ptr_ = ptr;
		}

		// Copy constructor.
		Ptr(Ptr& other) = default;

		// Move constructor.
		Ptr(Ptr&& other) noexcept
		{
			ptr_ = other.ptr_;
			other.ptr_ = nullptr;
		}

		// Value assignment operator.
		Ptr& operator = (T* ptr)
		{
			ptr_ = ptr;
			return *this;
		}

		// Copy assignment operator.
		Ptr& operator = (Ptr& other) = default;

		// Move assignment operator.
		Ptr& operator = (Ptr&& other) noexcept
		{
			ptr_ = other.ptr_;
			other.ptr_ = nullptr;
			return *this;
		}

		// Destructor.
		~Ptr() = default;

		// Resets the pointer to nullptr.
		void reset()
		{
			ptr_ = nullptr;
		}

		// Dereference operator.
		T& operator * ()
		{
			return *ptr_;
		}

		// Dereference operator.
		const T& operator * () const
		{
			return *ptr_;
		}

		// Structure pointer dereference operator.
		T* operator -> ()
		{
			return ptr_;
		}

		// Returns true if the Pointer != nullptr.
		operator bool() const
		{
			return ptr_ != nullptr;
		}

		// Overload of unary operator ++
		Ptr& operator ++ ()
		{
			++ptr_;
			return *this;
		}

		// Overload of unary operator ++
		Ptr operator ++ (int)
		{
			Ptr p(*this);
			++ptr_;
			return p;
		}

		// Overload of unary operator --
		Ptr& operator -- ()
		{
			--ptr_;
			return *this;
		}

		// Overload of unary operator --
		Ptr operator -- (int)
		{
			Ptr p(*this);
			--ptr_;
			return p;
		}

		// Overload of binary operator +
		Ptr operator + (std::ptrdiff_t offset)
		{
			return Ptr(ptr_ + offset);
		}

		// Overload of binary operator -
		Ptr operator - (std::ptrdiff_t offset)
		{
			return Ptr(ptr_ - offset);
		}

		// Overload of binary operator -
		std::ptrdiff_t operator - (const Ptr& other)
		{
			return ptr_ - other.ptr_;
		}

		// Overload of binary operator -
		std::ptrdiff_t operator - (const T* ptr)
		{
			return ptr_ - ptr;
		}

		// Overload of binary operator +=
		Ptr& operator += (std::ptrdiff_t offset)
		{
			ptr_ += offset;
			return *this;
		}

		// Overload of binary operator -=
		Ptr& operator -= (std::ptrdiff_t offset)
		{
			ptr_ -= offset;
			return *this;
		}

		// Overload of binary operator ==
		bool operator == (const Ptr& other)
		{
			return ptr_ == other.ptr_;
		}

		// Overload of binary operator ==
		bool operator == (const T* ptr)
		{
			return ptr_ == ptr;
		}

		// Overload of binary operator ==
		bool operator == (std::nullptr_t)
		{
			return ptr_ == nullptr;
		}

		// Overload of binary operator !=
		bool operator != (const Ptr& other)
		{
			return ptr_ != other.ptr_;
		}

		// Overload of binary operator !=
		bool operator != (const T* ptr)
		{
			return ptr_ != ptr;
		}

		// Overload of binary operator !=
		bool operator != (std::nullptr_t)
		{
			return ptr_ != nullptr;
		}

		// Overload of binary operator <
		bool operator < (const Ptr& other)
		{
			return ptr_ < other.ptr_;
		}

		// Overload of binary operator <
		bool operator < (const T* ptr)
		{
			return ptr_ < ptr;
		}

		// Overload of binary operator <=
		bool operator <= (const Ptr& other)
		{
			return ptr_ <= other.ptr_;
		}

		// Overload of binary operator <=
		bool operator <= (const T* ptr)
		{
			return ptr_ <= ptr;
		}

		// Overload of binary operator >
		bool operator > (const Ptr& other)
		{
			return ptr_ > other.ptr_;
		}

		// Overload of binary operator >
		bool operator > (const T* ptr)
		{
			return ptr_ > ptr;
		}

		// Overload of binary operator >=
		bool operator >= (const Ptr& other)
		{
			return ptr_ >= other.ptr_;
		}

		// Overload of binary operator >=
		bool operator >= (const T* ptr)
		{
			return ptr_ >= ptr;
		}

		// Overload of binary operator <=>
		std::strong_ordering operator <=> (const Ptr& other)
		{
			return ptr_ <=> other.ptr_;
		}

		// Overload of binary operator <=>
		std::strong_ordering operator <=> (const T* ptr)
		{
			return ptr_ <=> ptr;
		}
	};
}