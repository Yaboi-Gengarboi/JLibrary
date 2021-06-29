// JLibraryDevelopment
// test.cpp
// Created on 2021-05-23 by Justyn Durnford
// Last updated on 2021-06-27 by Justyn Durnford
// Main file for testing.

#ifndef NOMINMAX
#define NOMINMAX
#endif // NOMINMAX

#include <JLibrary/Graphics.hpp>
#include <JLibrary/Math.hpp>
#include <JLibrary/System.hpp>
using namespace jlib;

#include <algorithm>
#include <array>
#include <cmath>
#include <concepts>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <limits>
#include <string>
using namespace std;

unsigned int constructed = 0;
unsigned int destructed = 0;

struct Counter
{
	Counter()
	{
		++constructed;
	}

	Counter(const Counter& other) = default;

	Counter(Counter&& other) = default;

	Counter& operator = (const Counter& other) = default;

	Counter& operator = (Counter&& other) = default;

	~Counter()
	{
		++destructed;
	}
};

void println()
{
	cout << endl;
}

void println(const string& str)
{
	cout << str << endl;
}

void println(const wstring& wstr)
{
	wcout << wstr << endl;
}

template <std_arithmetic T, size_t R, size_t C>
void print(const Matrix<T, R, C>& M)
{
	for (size_t row_i(0u); row_i < R; ++row_i)
	{
		cout << "{ ";
		for (size_t col_i(0u); col_i < C - 1u; ++col_i)
			cout << M(row_i, col_i) << ", ";
		cout << M(row_i, C - 1u) << " }" << endl;
	}
}

void test_fraction()
{
	Fraction<uint8_t> A(1, 4);
	Fraction<uint8_t> B(2, 3);

	Fraction<uint8_t> C = A + B;
	++C;

	// Expected Fraction: 23 / 12
	cout << C.toString() << endl;

	Fraction<uint8_t> D(C - Fraction<uint8_t>(1, 3));
	D /= Fraction<uint8_t>(1, 2);

	// Expected Fraction: 114 / 36
	cout << D.toString() << endl;
}

void test_vector()
{
	Point2f a(1.2f, 0.8f);
	Point2f b(3.5f, 7.3f);

	Vector2f c(a, b);

	// Expected Vector2: <2.3f, 6.5f>
	cout << c.toString() << endl;

	c *= 2.4f;
	Vector2f d(6.7f, 21.9f);
	Vector2f e = d - c;
	Vector3f f(e.x, e.y, 5.f);

	// Expected Vector3: <1.18, 6.3, 5.0>
	cout << f.toString() << endl;

	f += Vector3f(3.49f, 0.027f, 1.365f);
	Vector3f g = f.unitVector();

	// Expected Vector3: <0.461601, 0.625385, 0.629141>
	cout << g.toString() << endl;
}

void test_matrix()
{
	Matrix<int, 3, 3> A
	{
		{ 5, 1, -8 },
		{ -3, 1, 1 },
		{ -1, -11, 4 }
	};

	Matrix<int, 3, 3> B
	{
		{ -7, -2, 10 },
		{ 5, 0, 3 },
		{ -2, 14, -5 }
	};

	Matrix<int, 3, 3> C = A + B;

	// Expected Matrix:
	// { -2, -1,  2 }
	// {  2,  1,  4 }
	// { -3,  3, -1 }    
	print(C);

	// Expected determinant: 54
	cout << determinant(C) << endl;

	Matrix<float, 2, 2> D;
	D(0, 0) = 1.f;
	D(1, 0) = 1.f;
	D(0, 1) = -2.f;
	D(1, 1) = 2.f;

	D *= 1.5f;

	// Expected Matrix:
	// {  1.5f,  1.5f }
	// { -3.0f,  3.0f }
	print(D);

	// Expected determinant: 9.0f
	cout << determinant(D) << endl;

	Matrix<float, 2, 2> E = (D - Matrix<float, 2, 2>(0.5f)) / 2.f;
	E(1, 0) += 0.25f;
	E(0, 1) -= 0.5f;

	// Expected Matrix:
	// {  0.5f,  0.75f }
	// { -2.25f,  1.25f }
	print(E);

	// Expected determinant: 2.3125f
	cout << determinant(E) << endl;

	Matrix<int, 4, 4> F =
	{
		{  0,  1,  2,  3 },
		{  4,  5,  6,  7 },
		{  8,  9, 10, 11 },
		{ 12, 13, 14, 15 }
	};

	print(F);

	cout << F(7) << endl;
	cout << F(2) << endl;
	cout << F(8) << endl;
	cout << F(13) << endl;
	cout << F(0) << endl;
	cout << F(15) << endl;
}

void test_matrix_memory_leak()
{
	for (int i = 0; i < 5000; ++i)
	{
		Matrix<int, 3, 3> A
		{
			{ 5, 1, -8 },
			{ -3, 1, 1 },
			{ -1, -11, 4 }
		};

		Matrix<int, 3, 3> B
		{
			{ -7, -2, 10 },
			{ 5, 0, 3 },
			{ -2, 14, -5 }
		};

		print(dot_product(A, B));
	}
}

int main()
{


	return 0;
}