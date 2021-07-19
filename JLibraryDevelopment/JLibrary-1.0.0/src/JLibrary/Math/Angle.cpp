// JLibraryDevelopment
// Angle.cpp
// Created on 2021-06-12 by Justyn Durnford
// Last modified on 2021-07-03 by Justyn Durnford
// Source file for the Angle class.

#include <JLibrary/Math/Angle.hpp>
using namespace jlib;

#include <cmath>
using std::cosf;
using std::fmodf;
using std::sinf;
using std::tanf;

#include <compare>
using std::strong_ordering;

#include <string>
using std::string;
using std::u32string;
using std::wstring;
using std::to_string;
using std::to_wstring;

const float Angle::PI = 3.141592654f;

Angle::Angle()
{
	degree = 0.f;
}

Angle::Angle(float Degree)
{
	degree = Degree;
}

Angle& Angle::operator = (float Degree)
{
	degree = Degree;
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

float jlib::to_radians(float degree)
{
	return degree * Angle::PI / 180.f;
}

float jlib::to_degrees(float radian)
{
	return radian * 180.f / Angle::PI;
}

Angle& jlib::least(Angle& A, Angle& B)
{
	if (A.degree < B.degree)
		return A;
	if (A.degree > B.degree)
		return B;
	return A;
}

Angle& jlib::greatest(Angle& A, Angle& B)
{
	if (A.degree < B.degree)
		return B;
	if (A.degree > B.degree)
		return A;
	return A;
}

float jlib::sine(const Angle& angle)
{
	if (fmodf(angle.degree, 180.f) == 0.f)
		return 0.f;

	return sinf(to_radians(angle.degree));
}

float jlib::cosine(const Angle& angle)
{
	if ((fmodf(angle.degree, 90.f) == 0.f) && ((fmodf(angle.degree, 180.f) != 0.f)))
		return 0.f;

	return cosf(to_radians(angle.degree));
}

float jlib::tangent(const Angle& angle)
{
	return tanf(to_radians(angle.degree));
}

bool operator == (const Angle& A, const Angle& B)
{
	return A.degree == B.degree;
}

bool operator == (const Angle& A, float degree)
{
	return A.degree == degree;
}

bool operator != (const Angle& A, const Angle& B)
{
	return A.degree != B.degree;
}

bool operator != (const Angle& A, float degree)
{
	return A.degree != degree;
}

bool operator < (const Angle& A, const Angle& B)
{
	return A.degree < B.degree;
}

bool operator < (const Angle& A, float degree)
{
	return A.degree < degree;
}

bool operator <= (const Angle& A, const Angle& B)
{
	return A.degree <= B.degree;
}

bool operator <= (const Angle& A, float degree)
{
	return A.degree <= degree;
}

bool operator > (const Angle& A, const Angle& B)
{
	return A.degree > B.degree;
}

bool operator > (const Angle& A, float degree)
{
	return A.degree > degree;
}

bool operator >= (const Angle& A, const Angle& B)
{
	return A.degree >= B.degree;
}

bool operator >= (const Angle& A, float degree)
{
	return A.degree >= degree;
}

strong_ordering operator <=> (const Angle& A, const Angle& B)
{
	if (A.degree < B.degree)
		return strong_ordering::less;
	if (A.degree > B.degree)
		return strong_ordering::greater;
	return strong_ordering::equivalent;
}

strong_ordering operator <=> (const Angle& A, float degree)
{
	if (A.degree < degree)
		return strong_ordering::less;
	if (A.degree > degree)
		return strong_ordering::greater;
	return strong_ordering::equivalent;
}

Angle operator - (const Angle& A)
{
	return Angle(-A.degree);
}

Angle operator + (const Angle& A, const Angle& B)
{
	return Angle(A.degree + B.degree);
}

Angle operator + (const Angle& A, float degree)
{
	return Angle(A.degree + degree);
}

Angle operator - (const Angle& A, const Angle& B)
{
	return Angle(A.degree - B.degree);
}

Angle operator - (const Angle& A, float degree)
{
	return Angle(A.degree - degree);
}

Angle operator * (const Angle& A, float scalar)
{
	return Angle(A.degree * scalar);
}

Angle operator / (const Angle& A, float scalar)
{
	return Angle(A.degree / scalar);
}

Angle& operator += (Angle& A, const Angle& B)
{
	A.degree += B.degree;
	return A;
}

Angle& operator += (Angle& A, float degree)
{
	A.degree += degree;
	return A;
}

Angle& operator -= (Angle& A, const Angle& B)
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