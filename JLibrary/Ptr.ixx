// JLibrary
// Ptr.ixx
// Created on 2022-01-08 by Justyn Durnford
// Last modified on 2022-01-08 by Justyn Durnford
// Module file for the Ptr template class.

module;

#include <compare>
#include <cstddef>
#include <iostream>

export module Ptr;

export namespace jlib
{
	// Utility template wrapper class for pointers.
	// This class is NOT intended to be used for memory
	// allocation, it is simply for pointing to objects.
	template <typename T> class Ptr
	{
		T* _ptr;

		public:

		// Default constructor.
		Ptr()
		{
			_ptr = nullptr;
		}

		// Value constructor.
		Ptr(T* ptr)
		{
			_ptr = ptr;
		}

		// Copy constructor.
		Ptr(Ptr& other) = default;

		// Move constructor.
		Ptr(Ptr&& other) noexcept
		{
			_ptr = other._ptr;
			other._ptr = nullptr;
		}

		// Value assignment operator.
		Ptr& operator = (T* ptr)
		{
			_ptr = ptr;
			return *this;
		}

		// Copy assignment operator.
		Ptr& operator = (Ptr& other) = default;

		// Move assignment operator.
		Ptr& operator = (Ptr&& other) noexcept
		{
			_ptr = other._ptr;
			other._ptr = nullptr;
			return *this;
		}

		// Destructor.
		~Ptr() = default;

		// Resets the pointer to nullptr.
		void reset()
		{
			_ptr = nullptr;
		}

		// Returns the underlying raw-pointer.
		T* get()
		{
			return _ptr;
		}

		// Returns the underlying raw-pointer.
		const T* get() const
		{
			return _ptr;
		}

		// Releases and returns the underlying raw-pointer.
		T* release()
		{
			T* ptr = _ptr;
			_ptr = nullptr;
			return ptr;
		}

		// Dereference operator.
		T& operator * ()
		{
			return *_ptr;
		}

		// Dereference operator.
		const T& operator * () const
		{
			return *_ptr;
		}

		// Structure pointer dereference operator.
		T* operator -> ()
		{
			return _ptr;
		}

		// Conversion operator to implicitly convert the pointer to its raw pointer type (T*).
		operator T* () const
		{
			return static_cast<T*>(_ptr);
		}

		// Returns true if the Pointer != nullptr.
		operator bool() const
		{
			return _ptr != nullptr;
		}

		// Overload of unary operator ++
		Ptr& operator ++ ()
		{
			++_ptr;
			return *this;
		}

		// Overload of unary operator ++
		Ptr operator ++ (int)
		{
			Ptr p(*this);
			++_ptr;
			return p;
		}

		// Overload of unary operator --
		Ptr& operator -- ()
		{
			--_ptr;
			return *this;
		}

		// Overload of unary operator --
		Ptr operator -- (int)
		{
			Ptr p(*this);
			--_ptr;
			return p;
		}
	};

	// Overload of binary operator +
	template <typename T>
	Ptr<T> operator + (const Ptr<T>& A, std::ptrdiff_t offset)
	{
		return Ptr<T>(A.get() + offset);
	}

	// Overload of binary operator -
	template <typename T>
	Ptr<T> operator - (const Ptr<T>& A, std::ptrdiff_t offset)
	{
		return Ptr<T>(A.get() - offset);
	}

	// Overload of binary operator -
	template <typename T>
	std::ptrdiff_t operator - (const Ptr<T>& A, const Ptr<T>& B)
	{
		return A.get() - B.get();
	}

	// Overload of binary operator -
	template <typename T>
	std::ptrdiff_t operator - (const Ptr<T>& A, const T* B)
	{
		return A.get() - B;
	}

	// Overload of binary operator +=
	template <typename T>
	Ptr<T>& operator += (Ptr<T>& A, std::ptrdiff_t offset)
	{
		A.get() += offset;
		return *this;
	}

	// Overload of binary operator -=
	template <typename T>
	Ptr<T>& operator -= (Ptr<T>& A, std::ptrdiff_t offset)
	{
		A.get() -= offset;
		return *this;
	}

	// Overload of binary operator ==
	template <typename T>
	bool operator == (const Ptr<T>& A, const Ptr<T>& B)
	{
		return A.get() == B.get();
	}

	// Overload of binary operator ==
	template <typename T>
	bool operator == (const Ptr<T>& A, const T* B)
	{
		return A.get() == B;
	}

	// Overload of binary operator ==
	template <typename T>
	bool operator == (const Ptr<T>& A, std::nullptr_t)
	{
		return A.get() == nullptr;
	}

	// Overload of binary operator !=
	template <typename T>
	bool operator != (const Ptr<T>& A, const Ptr<T>& B)
	{
		return A.get() != B.get();
	}

	// Overload of binary operator !=
	template <typename T>
	bool operator != (const Ptr<T>& A, const T* B)
	{
		return A.get() != B;
	}

	// Overload of binary operator !=
	template <typename T>
	bool operator != (const Ptr<T>& A, std::nullptr_t)
	{
		return A.get() != nullptr;
	}

	// Overload of binary operator <
	template <typename T>
	bool operator < (const Ptr<T>& A, const Ptr<T>& B)
	{
		return A.get() < B.get();
	}

	// Overload of binary operator <
	template <typename T>
	bool operator < (const Ptr<T>& A, const T* B)
	{
		return A.get() < B;
	}

	// Overload of binary operator <=
	template <typename T>
	bool operator <= (const Ptr<T>& A, const Ptr<T>& B)
	{
		return A.get() <= B.get();
	}

	// Overload of binary operator <=
	template <typename T>
	bool operator <= (const Ptr<T>& A, const T* B)
	{
		return A.get() <= B;
	}

	// Overload of binary operator >
	template <typename T>
	bool operator > (const Ptr<T>& A, const Ptr<T>& B)
	{
		return A.get() > B.get();
	}

	// Overload of binary operator >
	template <typename T>
	bool operator > (const Ptr<T>& A, const T* B)
	{
		return A.get() > B;
	}

	// Overload of binary operator >=
	template <typename T>
	bool operator >= (const Ptr<T>& A, const Ptr<T>& B)
	{
		return A.get() >= B.get();
	}

	// Overload of binary operator >=
	template <typename T>
	bool operator >= (const Ptr<T>& A, const T* B)
	{
		return A.get() > B;
	}

	// Overload of binary operator <=>
	template <typename T>
	std::strong_ordering operator <=> (const Ptr<T>& A, const Ptr<T>& B)
	{
		return A.get() <=> B.get();
	}

	// Overload of binary operator <=>
	template <typename T>
	std::strong_ordering operator <=> (const Ptr<T>& A, const T* B)
	{
		return A.get() <=> B;
	}

	// Overload of std::ostream operator <<
	template <typename T>
	std::ostream& operator << (std::ostream& os, const Ptr<T>& A)
	{
		os << A.get();
		return os;
	}

	// Overload of std::wostream operator <<
	template <typename T>
	std::wostream& operator << (std::wostream& wos, const Ptr<T>& A)
	{
		wos << A.get();
		return wos;
	}
}