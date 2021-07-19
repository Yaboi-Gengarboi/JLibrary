// JLibraryDevelopment
// GLSL.cpp
// Created on 2021-07-14 by Justyn Durnford
// Last modified on 2021-07-14 by Justyn Durnford
// Source file for functions defined in the GLSL namespace.

#include <JLibrary/Graphics/GLSL.hpp>
using namespace jlib;

#include <cstring>
using std::size_t;
using std::memcpy;

void jlib::copyMatrix(const float* source, float* dest, size_t elements)
{
    memcpy(dest, source, elements);
}

void jlib::copyMatrix(const Transformation& source, Matrix<float, 3, 3>& dest)
{
    const float* from = source.matrix().begin(); // 4x4
    float* to = dest.begin();                    // 3x3

    // Use only left-upper 3x3 block (for a 2D transform).
    to[0] = from[0];  to[1] = from[1];  to[2] = from[3];
    to[3] = from[4];  to[4] = from[5];  to[5] = from[7];
    to[6] = from[12]; to[7] = from[13]; to[8] = from[15];
}

void jlib::copyMatrix(const Transformation& source, Matrix<float, 4, 4>& dest)
{
    memcpy(dest.begin(), source.matrix().begin(), 16);
}

void jlib::copyVector(const Color& source, VectorN<float, 4>& dest)
{
    for (size_t i = 0; i < 4; ++i)
        dest[i] = (source[i] / 255.f);
}

void jlib::copyVector(const Color& source, VectorN<int, 4>& dest)
{
    for (size_t i = 0; i < 4; ++i)
        dest[i] = static_cast<int>(source[i]);
}