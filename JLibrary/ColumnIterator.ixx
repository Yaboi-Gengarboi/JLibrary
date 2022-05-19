// JLibrary
// Matrix.ixx
// Created on 2022-01-08 by Justyn Durnford
// Last modified on 2022-04-05 by Justyn Durnford
// Module file for the Matrix template class.

module;

#include <compare>
#include <cstddef>
#include <iterator>

export module ColumnIterator;

export namespace jlib
{
	// 
	template <typename T> class ColumnIterator
	{
		public:

		using value_type = T;
		using pointer = T*;
		using const_pointer = const T*;
		using reference = T&;
		using const_reference = const T&;
		using difference_type = std::ptrdiff_t;
		using iterator_category = std::random_access_iterator_tag;

		private:

		pointer _ptr;
		std::size_t _rowSize;

		public:

		// 
		ColumnIterator()
		{
			_ptr = nullptr;
		}

		// 
		ColumnIterator(pointer ptr)
		{
			_ptr = ptr;
		}

		// 
		ColumnIterator(std::nullptr_t)
		{
			_ptr = nullptr;
		}

		// 
		ColumnIterator(const ColumnIterator& other) = default;

		// 
		ColumnIterator(ColumnIterator&& other) = default;

		// 
		ColumnIterator& operator = (const ColumnIterator& other) = default;

		// 
		ColumnIterator& operator = (ColumnIterator&& other) = default;

		// 
		~ColumnIterator() = default;

		// 
		ColumnIterator& operator ++ () noexcept
		{
			_ptr += _rowSize;
			return *this;
		}

		// 
		ColumnIterator& operator ++ (int) noexcept
		{
			ColumnIterator tmp = *this;
			++(*this);
			return tmp;
		}

		// 
		ColumnIterator& operator -- () noexcept
		{
			_ptr -= _rowSize;
			return *this;
		}

		// 
		ColumnIterator& operator -- (int) noexcept
		{
			ColumnIterator tmp = *this;
			--(*this);
			return tmp;
		}

		// 
		ColumnIterator& operator += (std::ptrdiff_t offset) noexcept
		{
			_ptr += offset * _rowSize;
			return *this;
		}

		// 
		ColumnIterator& operator -= (std::ptrdiff_t offset) noexcept
		{
			_ptr -= offset * _rowSize;
			return *this;
		}

		// 
		friend ColumnIterator operator + (const ColumnIterator& A, std::ptrdiff_t offset)
		{
			return ColumnIterator(A._ptr + offset * _rowSize);
		}

		// 
		friend ColumnIterator operator - (const ColumnIterator& A, std::ptrdiff_t offset)
		{
			return ColumnIterator(A._ptr - offset * _rowSize);
		}

		// 
		reference operator * () const noexcept
		{
			return *_ptr;
		}

		// 
		pointer operator -> () const noexcept
		{
			return _ptr;
		}

		// 
		reference operator [] (std::ptrdiff_t offset)
		{
			return *(_ptr + offset * _rowSize);
		}

		// 
		bool operator == (const ColumnIterator& other)
		{
			return _ptr == other._ptr;
		}

		// 
		bool operator != (const ColumnIterator& other)
		{
			return _ptr != other._ptr;
		}

		// 
		bool operator < (const ColumnIterator& other)
		{
			return _ptr < other._ptr;
		}

		// 
		bool operator <= (const ColumnIterator& other)
		{
			return _ptr <= other._ptr;
		}

		// 
		bool operator > (const ColumnIterator& other)
		{
			return _ptr > other._ptr;
		}

		// 
		bool operator >= (const ColumnIterator& other)
		{
			return _ptr >= other._ptr;
		}

		// 
		std::strong_ordering operator <=> (const ColumnIterator& other)
		{
			if (_ptr < other._ptr)
				return std::strong_ordering::less;
			if (_ptr > other._ptr)
				return std::strong_ordering::greater;
			return std::strong_ordering::equal;
		}
	};
}