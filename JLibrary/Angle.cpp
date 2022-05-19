// JLibrary
// Angle.cpp
// Created on 2022-01-08 by Justyn Durnford
// Last modified on 2022-05-15 by Justyn Durnford
// Source file for the Angle class.

#include "Angle.hpp"
#include "Constants.hpp"

#include <array>
using std::array;

#include <cmath>
using std::acosf;
using std::asinf;
using std::atanf;
using std::cosf;
using std::fabsf;
using std::fmodf;
using std::sinf;
using std::tanf;

#include <compare>
using std::strong_ordering;

#include <iostream>
using std::cout;
using std::ostream;
using std::wostream;

#include <string>
using std::string;
using std::wstring;
using std::to_string;
using std::to_wstring;

namespace jlib
{
	constexpr float to_radians(float degree)
	{
		return degree * JLIB_TO_RAD;
	}

	constexpr float to_degrees(float radian)
	{
		return radian * JLIB_TO_DEG;
	}

	void restrict_360(float& degree)
	{
		if (degree < 0.0f)
			degree += 360.0f * fmodf(degree, 360.0f);
		if (degree > 360.0f)
			degree -= 360.0f * fmodf(degree, 360.0f);
	}

	array<float, 2> sincos(float degree)
	{
		float rad = to_radians(degree);

		array<float, 2> arr = { sinf(rad), cosf(rad) };
		return arr;
	}

	Angle::Angle()
	{
		degree = 0.0f;
	}

	Angle::Angle(float new_degree)
	{
		degree = new_degree;
	}

	Angle& Angle::operator = (float new_degree)
	{
		degree = new_degree;
		return *this;
	}

	string Angle::toString() const
	{
		return to_string(degree) + '\370';
	}

	wstring Angle::toWideString() const
	{
		return to_wstring(degree) + L'\370';
	}

	float sine(Angle angle)
	{
		if (fmodf(angle.degree, 180.0f) == 0.0f)
			return 0.0f;

		return sinf(to_radians(angle.degree));
	}

	float cosine(Angle angle)
	{
		if ((fmodf(angle.degree, 90.0f) == 0.0f) && ((fmodf(angle.degree, 180.0f) != 0.0f)))
			return 0.0f;

		return cosf(to_radians(angle.degree));
	}

	float tangent(Angle angle)
	{
		return tanf(to_radians(angle.degree));
	}

	Angle arcsine(float value)
	{
		return Angle(to_degrees(asinf(value)));
	}

	Angle arccosine(float value)
	{
		return Angle(to_degrees(acosf(value)));
	}

	Angle arctangent(float value)
	{
		return Angle(to_degrees(atanf(value)));
	}

	Angle& least(Angle& A, Angle& B)
	{
		if (A.degree < B.degree)
			return A;
		if (A.degree > B.degree)
			return B;
		return A;
	}

	Angle& greatest(Angle& A, Angle& B)
	{
		if (A.degree < B.degree)
			return B;
		if (A.degree > B.degree)
			return A;
		return A;
	}

	void print(const Angle& angle)
	{
		cout << angle.toString();
	}

	void println(const Angle& angle)
	{
		cout << angle.toString() << '\n';
	}

	bool operator == (Angle A, Angle B)
	{
		return A.degree == B.degree;
	}

	bool operator == (Angle A, float degree)
	{
		return A.degree == degree;
	}

	bool operator != (Angle A, Angle B)
	{
		return A.degree != B.degree;
	}

	bool operator != (Angle A, float degree)
	{
		return A.degree != degree;
	}

	bool operator < (Angle A, Angle B)
	{
		return A.degree < B.degree;
	}

	bool operator < (Angle A, float degree)
	{
		return A.degree < degree;
	}

	bool operator <= (Angle A, Angle B)
	{
		return A.degree <= B.degree;
	}

	bool operator <= (Angle A, float degree)
	{
		return A.degree <= degree;
	}

	bool operator > (Angle A, Angle B)
	{
		return A.degree > B.degree;
	}

	bool operator > (Angle A, float degree)
	{
		return A.degree > degree;
	}

	bool operator >= (Angle A, Angle B)
	{
		return A.degree >= B.degree;
	}

	bool operator >= (Angle A, float degree)
	{
		return A.degree >= degree;
	}

	strong_ordering operator <=> (Angle A, Angle B)
	{
		if (A.degree < B.degree)
			return strong_ordering::less;
		if (A.degree > B.degree)
			return strong_ordering::greater;
		return strong_ordering::equivalent;
	}

	strong_ordering operator <=> (Angle A, float degree)
	{
		if (A.degree < degree)
			return strong_ordering::less;
		if (A.degree > degree)
			return strong_ordering::greater;
		return strong_ordering::equivalent;
	}

	Angle operator - (Angle A)
	{
		return Angle(-A.degree);
	}

	Angle operator + (Angle A, Angle B)
	{
		return Angle(A.degree + B.degree);
	}

	Angle operator + (Angle A, float degree)
	{
		return Angle(A.degree + degree);
	}

	Angle operator - (Angle A, Angle B)
	{
		return Angle(A.degree - B.degree);
	}

	Angle operator - (Angle A, float degree)
	{
		return Angle(A.degree - degree);
	}

	Angle operator * (Angle A, float scalar)
	{
		return Angle(A.degree * scalar);
	}

	Angle operator / (Angle A, float scalar)
	{
		return Angle(A.degree / scalar);
	}

	Angle& operator += (Angle& A, Angle B)
	{
		A.degree += B.degree;
		return A;
	}

	Angle& operator += (Angle& A, float degree)
	{
		A.degree += degree;
		return A;
	}

	Angle& operator -= (Angle& A, Angle B)
	{
		A.degree -= B.degree;
		return A;
	}

	Angle& operator -= (Angle& A, float degree)
	{
		A.degree -= degree;
		return A;
	}

	Angle& operator *= (Angle& A, float scalar)
	{
		A.degree *= scalar;
		return A;
	}

	Angle& operator /= (Angle& A, float scalar)
	{
		A.degree /= scalar;
		return A;
	}

	ostream& operator << (ostream& os, Angle A)
	{
		os << A.toString();
		return os;
	}

	wostream& operator << (wostream& wos, Angle A)
	{
		wos << A.toWideString();
		return wos;
	}
}