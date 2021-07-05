// JLibraryDevelopment
// Matrix.hpp
// Created on 2021-05-23 by Justyn Durnford
// Last modified on 2021-07-03 by Justyn Durnford
// Header file for the Matrix template class.

#pragma once

#include <Jlibrary/Math/Arithmetic.hpp>
#include <initializer_list>
#include <stdexcept>

namespace jlib
{
	// Utility template class for representing and          
	// computing matrices of varying sizes.
	// 
	// IMPORTANT NOTE: A Matrix with dimensions R x C
	// represents a Matrix with R rows and C columns.
	// This seems a bit confusing to people who are
	// used to X x Y coordinates, but this is consistent
	// with how they are represented in mathematics.
	template <std::semiregular T, std::size_t R, std::size_t C> class Matrix
	{
		public:

		using value_type = T;
		using size_type = std::size_t;
		using reference = T&;
		using const_reference = const T&;
		using pointer = T*;
		using const_pointer = const T*;

		private:

		T** data_;

		// 
		void allocate()
		{
			if (R != 0 && C != 0)
			{
				data_ = new T*[R];
				for (std::size_t row_i(0); row_i < R; ++row_i)
					data_[row_i] = new T[C];
			}
			else
				data_ = nullptr;
		}

		// 
		void deallocate() noexcept
		{
			if (data_ != nullptr)
			{
				for (std::size_t row_i(0); row_i < R; ++row_i)
					delete[] data_[row_i];
				delete[] data_;
			}
		}

		// 
		void copyElements(T* dst_begin, const T* src_begin, std::size_t count)
		{
			for (std::size_t i(0); i < count; ++i)
				dst_begin[i] = src_begin[i];
		}

		public:

		// Default constructor.
		Matrix()
		{
			allocate();
		}

		// 1-parameter constructor.
		// Sets every element of the Matrix to value.
		Matrix(const T& value)
		{
			allocate();

			for (std::size_t row_i(0); row_i < R; ++row_i)
			{
				for (std::size_t col_i(0); col_i < C; ++col_i)
					data_[row_i][col_i] = value;
			}
		}

		// 2-dimensional std::initializer_list constructor.
		Matrix(std::initializer_list<std::initializer_list<T>> list)
		{
			allocate();
			std::size_t row_i(0);

			for (const auto& row : list)
				copyElements(data_[row_i++], row.begin(), C);
		}

		// Copy constructor.
		Matrix(const Matrix& other)
		{
			allocate();

			for (std::size_t row_i(0); row_i < R; ++row_i)
				copyElements(data_[row_i], other.data_[row_i], C);
		}

		// Constructs the Matrix from another type of Matrix.
		// This constructor doesn't replace the copy constructor,
		// it's called only when U != T.
		template <std::semiregular U>
		explicit Matrix(const Matrix<U, R, C>& other)
		{
			allocate();

			for (std::size_t row_i(0); row_i < R; ++row_i)
			{
				for (std::size_t col_i(0); col_i < C; ++col_i)
					data_[row_i][col_i] = static_cast<T>(other.data_[row_i][col_i]);
			}
		}

		// Move constructor.
		Matrix(Matrix&& other) noexcept
		{
			data_ = other.data_;
			other.data_ = nullptr;
		}

		// 2-dimensional std::initializer_list assignment operator.
		Matrix& operator = (std::initializer_list<std::initializer_list<T>> list)
		{
			std::size_t row_i(0);

			for (const auto& row : list)
				copyElements(data_[row_i++], row.begin(), C);

			return *this;
		}

		// Copy assignment operator.
		Matrix& operator = (const Matrix& other)
		{
			for (std::size_t row_i(0); row_i < R; ++row_i)
				copyElements(data_[row_i], other.data_[row_i], C);

			return *this;
		}

		// Move assignment operator.
		Matrix& operator = (Matrix&& other) noexcept
		{
			deallocate();

			data_ = other.data_;
			other.data_ = nullptr;

			return *this;
		}

		// Destructor.
		~Matrix() noexcept
		{
			deallocate();
		}

		// Returns the number of rows in the Matrix.
		std::size_t rowCount() const
		{
			return R;
		}

		// Returns the number of columns in the Matrix.
		std::size_t colCount() const
		{
			return C;
		}

		// Returns a copy of the given row.
		T* getRow(std::size_t row) const
		{
			if (row >= R)
				throw std::out_of_range("Invalid row index");

			T* arr = new T[C];
			for (std::size_t col_i(0); col_i < C; ++col_i)
				arr[col_i] = data_[row][col_i];

			return arr;
		}

		// Returns a copy of the given column.
		T* getCol(std::size_t col) const
		{
			if (col >= C)
				throw std::out_of_range("Invalid column index");

			T* arr = new T[R];
			for (std::size_t row_i(0); row_i < R; ++row_i)
				arr[row_i] = data_[row_i][col];

			return arr;
		}

		// Returns the submatrix formed by the row and col indices.
		template <std::size_t R2, std::size_t C2>
		Matrix<T, R2, C2> submatrix(std::size_t row_begin, std::size_t col_begin) const
		{
			if (row_begin >= R || row_begin + R2)
				throw std::out_of_range("Invalid row index");
			if (col_begin >= C || col_begin + C >= C2)
				throw std::out_of_range("Invalid column index");

			Matrix<T, R2, C2> M;

			for (std::size_t row_i(0); row_i < R2; ++row_i)
			{
				for (std::size_t col_i(0); col_i < C2; ++col_i)
					M.data_[row_i][col_i] = data_[row_begin + row_i][col_begin + col_i];
			}

			return M;
		}

		// Returns the nth element of the Matrix.
		// Performs bounds-checking.
		T& at(std::size_t n)
		{
			if (n >= R * C)
				throw std::out_of_range("Invalid matrix index");

			return data_[n / R][n % C];
		}

		// Returns the nth element of the Matrix.
		// Performs bounds-checking.
		const T& at(std::size_t n) const
		{
			if (n >= R * C)
				throw std::out_of_range("Invalid matrix index");

			return data_[n / R][n % C];
		}

		// Returns the element at [row][col].
		// Performs bounds-checking.
		T& at(std::size_t row, std::size_t col)
		{
			if (row >= R)
				throw std::out_of_range("Invalid row index");
			if (col >= C)
				throw std::out_of_range("Invalid column index");

			return data_[row][col];
		}

		// Returns the element at [row][col].
		// Performs bounds-checking.
		const T& at(std::size_t row, std::size_t col) const
		{
			if (row >= R)
				throw std::out_of_range("Invalid row index");
			if (col >= C)
				throw std::out_of_range("Invalid column index");

			return data_[row][col];
		}

		// Sets the nth element of the Matrix to value.
		// Performs bounds-checking.
		void set(std::size_t n, const T& value)
		{
			if (n >= R * C)
				throw std::out_of_range("Invalid matrix index");

			data_[n / R][n % C] = value;
		}

		// Sets the element at [row][col] to value.
		// Performs bounds-checking.
		void set(std::size_t row, std::size_t col, const T& value)
		{
			if (row >= R)
				throw std::out_of_range("Invalid row index");
			if (col >= C)
				throw std::out_of_range("Invalid column index");

			data_[row][col] = value;
		}

		// Returns the nth element of the Matrix.
		T& operator () (std::size_t n)
		{
			return data_[n / R][n % C];
		}

		// Returns the nth element of the Matrix.
		const T& operator () (std::size_t n) const
		{
			return data_[n / R][n % C];
		}

		// Returns the element at [row][col].
		T& operator () (std::size_t row, std::size_t col)
		{
			return data_[row][col];
		}

		// Returns the element at [row][col].
		const T& operator () (std::size_t row, std::size_t col) const
		{
			return data_[row][col];
		}
	};

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

	// Returns the determinant of the 2x2 Matrix formed as
	// {  a,  b  }
	// {  c,  d  }
	template <std_arithmetic T>
	inline T determinant(T a, T b, T c, T d)
	{
		return (a * d) - (b * c);
	}

	// Returns the determinant of the 2x2 Matrix.
	template <std_arithmetic T>
	inline T determinant(const Matrix<T, 2, 2>& M)
	{
		return (M(0, 0) * M(1, 1)) - (M(1, 0) * M(0, 1));
	}

	// Returns the determinant of the 3x3 Matrix.
	template <std_arithmetic T>
	T determinant(const Matrix<T, 3, 3>& M)
	{
		T A = M(0, 0) * determinant(M(1, 1), M(1, 2), M(2, 1), M(2, 2));
		T B = M(0, 1) * determinant(M(1, 0), M(1, 2), M(2, 0), M(2, 2));
		T C = M(0, 2) * determinant(M(1, 0), M(1, 1), M(2, 0), M(2, 1));

		return A - B + C;
	}

	// Returns the determinant of the 4x4 Matrix.
	template <std_arithmetic T>
	T determinant(const Matrix<T, 4, 4>& M)
	{
		Matrix<T, 3, 3> A =
		{
			{ M(1, 1), M(1, 2), M(1, 3) },
			{ M(2, 1), M(2, 2), M(2, 3) },
			{ M(3, 1), M(3, 2), M(3, 3) }
		};

		Matrix<T, 3, 3> B =
		{
			{ M(1, 0), M(1, 2), M(1, 3) },
			{ M(2, 0), M(2, 2), M(2, 3) },
			{ M(3, 0), M(3, 2), M(3, 3) }
		};

		Matrix<T, 3, 3> C =
		{
			{ M(1, 0), M(1, 1), M(1, 3) },
			{ M(2, 0), M(2, 1), M(2, 3) },
			{ M(3, 0), M(3, 1), M(3, 3) }
		};

		Matrix<T, 3, 3> D =
		{
			{ M(1, 0), M(1, 1), M(1, 2) },
			{ M(2, 0), M(2, 1), M(2, 2) },
			{ M(3, 0), M(3, 1), M(3, 2) }
		};

		return M(0, 0) * determinant(A) - M(0, 1) * determinant(B) + M(0, 2) * determinant(C) - M(0, 3) * determinant(D);
	}

	// Returns the dot product of the given Matrices.
	template <std_arithmetic T, std::size_t M, std::size_t N, std::size_t P>
	Matrix<T, M, P> dot_product(const Matrix<T, M, N>& A, const Matrix<T, N, P>& B)
	{
		Matrix<T, M, P> C;
		T value;

		for (std::size_t m(0); m < M; ++m)
		{
			T* row(A.getRow(m));

			for (std::size_t p(0); p < P; ++p)
			{
				value = 0;
				T* col(B.getCol(p));

				for (std::size_t n(0); n < N; ++n)
					value += row[n] * col[n];

				delete[] col;
				C(m, p) = value;
			}

			delete[] row;
		}

		return C;
	}
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

// Overload of binary operator == 
template <std::regular T, std::size_t R, std::size_t C>
bool operator == (const jlib::Matrix<T, R, C>& A, const jlib::Matrix<T, R, C>& B)
{
	for (std::size_t row_i(0); row_i < R; ++row_i)
	{
		for (std::size_t col_i(0); col_i < C; ++col_i)
		{
			if (A(row_i, col_i) != B(row_i, col_i))
				return false;
		}
	}

	return true;
}

// Overload of binary operator != 
template <std::regular T, std::size_t R, std::size_t C>
bool operator != (const jlib::Matrix<T, R, C>& A, const jlib::Matrix<T, R, C>& B)
{
	for (std::size_t row_i(0); row_i < R; ++row_i)
	{
		for (std::size_t col_i(0); col_i < C; ++col_i)
		{
			if (A(row_i, col_i) != B(row_i, col_i))
				return true;
		}
	}

	return false;
}

// Overload of unary operator -
template <jlib::std_arithmetic T, std::size_t R, std::size_t C>
jlib::Matrix<T, R, C> operator - (const jlib::Matrix<T, R, C>& A)
{
	jlib::Matrix<T, R, C> M;

	for (std::size_t row_i(0); row_i < R; ++row_i)
	{
		for (std::size_t col_i(0); col_i < C; ++col_i)
			M(row_i, col_i) = A(row_i, col_i) * static_cast<T>(-1);
	}

	return M;
}

// Overload of binary operator +
template <jlib::std_arithmetic T, std::size_t R, std::size_t C>
jlib::Matrix<T, R, C> operator + (const jlib::Matrix<T, R, C>& A, const jlib::Matrix<T, R, C>& B)
{
	jlib::Matrix<T, R, C> M;

	for (std::size_t row_i(0); row_i < R; ++row_i)
	{
		for (std::size_t col_i(0); col_i < C; ++col_i)
			M(row_i, col_i) = A(row_i, col_i) + B(row_i, col_i);
	}

	return M;
}

// Overload of binary operator -
template <jlib::std_arithmetic T, std::size_t R, std::size_t C>
jlib::Matrix<T, R, C> operator - (const jlib::Matrix<T, R, C>& A, const jlib::Matrix<T, R, C>& B)
{
	jlib::Matrix<T, C, R> M;

	for (std::size_t row_i(0); row_i < R; ++row_i)
	{
		for (std::size_t col_i(0); col_i < C; ++col_i)
			M(row_i, col_i) = A(row_i, col_i) - B(row_i, col_i);
	}

	return M;
}

// Overload of binary operator *
template <jlib::std_arithmetic T, jlib::std_arithmetic U, std::size_t R, std::size_t C>
jlib::Matrix<T, R, C> operator * (const jlib::Matrix<T, R, C>& A, U scalar)
{
	jlib::Matrix<T, C, R> M;
	
	for (std::size_t row_i(0); row_i < R; ++row_i)
	{
		for (std::size_t col_i(0); col_i < C; ++col_i)
			M(row_i, col_i) = A(row_i, col_i) * scalar;
	}

	return M;
}

// Overload of binary operator *
template <jlib::std_arithmetic T, jlib::std_arithmetic U, std::size_t R, std::size_t C>
jlib::Matrix<T, R, C> operator * (U scalar, const jlib::Matrix<T, R, C>& A)
{
	jlib::Matrix<T, C, R> M;
	
	for (std::size_t row_i(0); row_i < R; ++row_i)
	{
		for (std::size_t col_i(0); col_i < C; ++col_i)
			M(row_i, col_i) = A(row_i, col_i) * scalar;
	}

	return M;
}

// Overload of binary operator /
template <jlib::std_arithmetic T, jlib::std_arithmetic U, std::size_t R, std::size_t C>
jlib::Matrix<T, R, C> operator / (const jlib::Matrix<T, R, C>& A, U scalar)
{
	jlib::Matrix<T, C, R> M;
	
	for (std::size_t row_i(0); row_i < R; ++row_i)
	{
		for (std::size_t col_i(0); col_i < C; ++col_i)
			M(row_i, col_i) = A(row_i, col_i) / scalar;
	}

	return M;
}

// Overload of binary operator +=
template <jlib::std_arithmetic T, std::size_t R, std::size_t C>
jlib::Matrix<T, R, C>& operator += (jlib::Matrix<T, R, C>& A, const jlib::Matrix<T, R, C>& B)
{
	for (std::size_t row_i(0); row_i < R; ++row_i)
	{
		for (std::size_t col_i(0); col_i < C; ++col_i)
			A(row_i, col_i) += B(row_i, col_i);
	}

	return A;
}

// Overload of binary operator -=
template <jlib::std_arithmetic T, std::size_t R, std::size_t C>
jlib::Matrix<T, R, C>& operator -= (jlib::Matrix<T, R, C>& A, const jlib::Matrix<T, R, C>& B)
{
	for (std::size_t row_i(0); row_i < R; ++row_i)
	{
		for (std::size_t col_i(0); col_i < C; ++col_i)
			A(row_i, col_i) -= B(row_i, col_i);
	}

	return A;
}

// Overload of binary operator *=
template <jlib::std_arithmetic T, jlib::std_arithmetic U, std::size_t R, std::size_t C>
jlib::Matrix<T, R, C>& operator *= (jlib::Matrix<T, R, C>& M, U scalar)
{
	for (std::size_t row_i(0); row_i < R; ++row_i)
	{
		for (std::size_t col_i(0); col_i < C; ++col_i)
			M(row_i, col_i) *= scalar;
	}

	return M;
}

// Overload of binary operator /=
template <jlib::std_arithmetic T, jlib::std_arithmetic U, std::size_t R, std::size_t C>
jlib::Matrix<T, R, C>& operator /= (jlib::Matrix<T, R, C>& M, U scalar)
{
	for (std::size_t row_i(0); row_i < R; ++row_i)
	{
		for (std::size_t col_i(0); col_i < C; ++col_i)
			M(row_i, col_i) /= scalar;
	}

	return M;
}