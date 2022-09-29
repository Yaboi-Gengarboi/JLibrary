// JLibrary
// FixedGrid.ixx
// Created on 2022-06-25 by Justyn Durnford
// Last modified on 2022-09-21 by Justyn Durnford
// Module file for the FixedGrid class.

module;

#include <stdexcept>
#include <cstddef>

export module FixedGrid;

import FixedArray;
import Vector3;

export namespace jlib
{
    template <typename T, size_t LENGTH, size_t WIDTH, size_t HEIGHT>
    class FixedGrid
    {
        public:

		using value_type = T;
		using size_type = std::size_t;
		using difference_type = std::ptrdiff_t;
		using reference = value_type&;
		using const_reference = const value_type&;
		using pointer = value_type*;
		using const_pointer = const value_type*;
		using iterator = FixedArray<T, LENGTH * WIDTH * HEIGHT>::iterator;
		using const_iterator = FixedArray<T, LENGTH * WIDTH * HEIGHT>::const_iterator;
		using row_iterator = iterator;
		using const_row_iterator = const_iterator;
		using reverse_iterator = FixedArray<T, LENGTH * WIDTH * HEIGHT>::reverse_iterator;
		using const_reverse_iterator = FixedArray<T, LENGTH * WIDTH * HEIGHT>::const_reverse_iterator;

        private:

        FixedArray<T, LENGTH * WIDTH * HEIGHT> _data;

        public:

		// Default constructor.
		FixedGrid() = default;

		// 1-parameter constructor.
		// Sets every element of the FixedGrid to value.
		FixedGrid(const_reference value)
		{
			std::fill(data(), dataEnd(), value);
		}

		// Returns the number of elements in the FixedMatrix.
		constexpr size_type size() const noexcept
		{
			return LENGTH * WIDTH * HEIGHT;
		}

		// Returns the pointer of the FixedGrid.
		constexpr pointer data() noexcept
		{
			return _data.data();
		}

		// Returns the pointer of the FixedGrid.
		constexpr const_pointer data() const noexcept
		{
			return _data.data();
		}

		// Returns a pointer to 1 past the last element of the FixedGrid.
		constexpr pointer dataEnd() noexcept
		{
			return _data.dataEnd();
		}

		// Returns a pointer to 1 past the last element of the FixedGrid.
		constexpr const_pointer dataEnd() const noexcept
		{
			return _data.dataEnd();
		}

		// 
		constexpr reference operator [] (size_type n)
		{
			return _data[n];
		}

		// 
		constexpr const_reference operator [] (size_type n) const
		{
			return _data[n];
		}

        // 
        constexpr reference operator () (size_type x, size_type y, size_type z)
        {
            return _data[z * WIDTH * HEIGHT + y * WIDTH + x];
        }

		// 
		constexpr const_reference operator () (size_type x, size_type y, size_type z) const
		{
			return _data[z * WIDTH * HEIGHT + y * WIDTH + x];
		}
    };

}