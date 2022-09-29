// JLibrary
// BitMatrix.ixx
// Created on July 05 2022 by Justyn Durnford
// Last modified on July 25 2022 by Justyn Durnford
// Module file for the BitMatrix class.

module;

#include <bitset>
#include <cstddef>
#include <stdexcept>

export module BitMatrix;

export namespace jlib
{
	// 
	template <std::size_t R, std::size_t C> class BitMatrix
	{
		std::bitset<R* C> _data;

		public:

		// Default constructor.
		BitMatrix() = default;

		// boolean constructor.
		// Sets every bit of the BitMatrix to the given boolean.
		BitMatrix(bool value)
		{
			_data.set(value);
		}

		// Returns the number of rows in the BitMatrix.
		constexpr std::size_t rowCount() const noexcept
		{
			return R;
		}

		// Returns the number of columns in the BitMatrix.
		constexpr std::size_t colCount() const noexcept
		{
			return C;
		}

		// Returns the number of bits in the BitMatrix.
		constexpr std::size_t size() const noexcept
		{
			return R * C;
		}

		// Returns the underlying std::bitset.
		constexpr std::bitset<R * C>& data() noexcept
		{
			return _data;
		}

		// Returns the underlying std::bitset.
		constexpr const std::bitset<R * C>& data() const noexcept
		{
			return _data;
		}

		// Returns the bit at the given index of the BitMatrix.
		// Throws a std::out_of_range if given an invalid index.
		constexpr bool at(std::size_t n)
		{
			if (n >= R * C)
				throw std::out_of_range("Invalid BitMatrix index");

			return _data[n];
		}

		// Returns the bit at the given index of the BitMatrix.
		// Throws a std::out_of_range if given an invalid index.
		constexpr const bool at(std::size_t n) const
		{
			if (n >= R * C)
				throw std::out_of_range("Invalid BitMatrix index");

			return _data[n];
		}

		// Returns the bit at [row][col].
		// Throws a std::out_of_range if given an invalid index.
		constexpr bool at(std::size_t row, std::size_t col)
		{
			if (row >= R)
				throw std::out_of_range("Invalid row index");
			if (col >= C)
				throw std::out_of_range("Invalid column index");

			return _data[(row * C) + col];
		}

		// Returns the bit at [row][col].
		// Throws a std::out_of_range if given an invalid index.
		constexpr const bool at(std::size_t row, std::size_t col) const
		{
			if (row >= R)
				throw std::out_of_range("Invalid row index");
			if (col >= C)
				throw std::out_of_range("Invalid column index");

			return _data[(row * C) + col];
		}

		// Sets the bit at the given index to the given value.
		// Throws a std::out_of_range if given an invalid index.
		constexpr void set(std::size_t n, bool value)
		{
			if (n >= R * C)
				throw std::out_of_range("Invalid BitMatrix index");

			_data[n] = value;
		}

		// Sets the bit at [row][col] to the given value.
		// Throws a std::out_of_range if given an invalid index.
		constexpr void set(std::size_t row, std::size_t col, bool value)
		{
			if (row >= R)
				throw std::out_of_range("Invalid row index");
			if (col >= C)
				throw std::out_of_range("Invalid column index");

			_data[(row * C) + col] = value;
		}

		// Returns the bit at the given index of the BitMatrix.
		// Does NOT perform bounds-checking.
		constexpr bool operator [] (std::size_t n) const
		{
			return _data[n];
		}

		// Returns the bit at [row][col].
		// Does NOT perform bounds-checking.
		constexpr bool operator () (std::size_t row, std::size_t col) const
		{
			return _data[(row * C) + col];
		}
	};
}