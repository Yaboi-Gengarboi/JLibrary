////////////////////////////////////////////////////////////
//
// THIS IS A MODIFIED FILE FROM SFML 2.5.1
// 
// SFML - Simple and Fast Multimedia Library
// Copyright (C) 2007-2021 Laurent Gomila (laurent@sfml-dev.org)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
////////////////////////////////////////////////////////////
// 
// JLibraryDevelopment
// Transformable.cpp
// Created on 2021-06-09 by Justyn Durnford
// Last modified on 2021-06-27 by Justyn Durnford
// Source file for the Transformable class.

#include <JLibrary/Graphics/Transformable.hpp>
#include <cmath>
using namespace std;
using namespace jlib;

Transformable::Transformable()
{
	rotation_ = 0.f;
	x_scale_ = 1.f;
	y_scale_ = 1.f;
	transformationUpdate_ = true;
	inverseTransformationUpdate_ = true;
}

Transformable::~Transformable() {}

Point2f Transformable::position() const
{
	return position_;
}

Point2f Transformable::origin() const
{
	return origin_;
}

float Transformable::rotation() const
{
	return rotation_;
}

float Transformable::x_scale() const
{
	return x_scale_;
}

float Transformable::y_scale() const
{
	return y_scale_;
}

const Transformation& Transformable::transformation() const
{
	if (transformationUpdate_) // Update transformation
	{
		float angle = -rotation_ * 3.141592654f / 180.f;
		float cosine = cos(angle);
		float sine = sin(angle);
		float sxc = x_scale_ * cosine;
		float syc = y_scale_ * cosine;
		float sxs = x_scale_ * sine;
		float sys = y_scale_ * sine;
		float tx = -origin_.x * sxc - origin_.y * sys + origin_.x;
		float ty = origin_.x * sxs - origin_.y * syc + origin_.y;

		transformation_ = Transformation(sxc, sys, tx, -sxs, syc, ty, 0.f, 0.f, 1.f);
		transformationUpdate_ = false;
	}

	return transformation_;
}

const Transformation& Transformable::inverseTransformation() const
{
	if (inverseTransformationUpdate_) // Update inverse transformation
	{
		inverseTransformation_ = transformation().inverse();
		inverseTransformationUpdate_ = false;
	}

	return inverseTransformation_;
}

void Transformable::setPosition(float X, float Y)
{
	position_.x = X;
	position_.y = Y;
	transformationUpdate_ = true;
	inverseTransformationUpdate_ = true;
}

void Transformable::setPosition(const Point2f& position)
{
	position_ = position;
	transformationUpdate_ = true;
	inverseTransformationUpdate_ = true;
}

void Transformable::setOrigin(float X, float Y)
{
	origin_.x = X;
	origin_.y = Y;
	transformationUpdate_ = true;
	inverseTransformationUpdate_ = true;
}

void Transformable::setOrigin(const Point2f& origin)
{
	origin_ = origin;
	transformationUpdate_ = true;
	inverseTransformationUpdate_ = true;
}

void Transformable::setRotation(float degree)
{
	rotation_ = fmod(degree, 360.f);
	if (rotation_ < 0.f)
		rotation_ += 360.f;

	transformationUpdate_ = true;
	inverseTransformationUpdate_ = true;
}

void Transformable::setScale(float scale_x, float scale_y)
{
	x_scale_ = scale_x;
	y_scale_ = scale_y;
}

void Transformable::move(float offset_x, float offset_y)
{
	position_.x += offset_x;
	position_.y += offset_y;
	transformationUpdate_ = true;
	inverseTransformationUpdate_ = true;
}

void Transformable::move(const Vector2f& offset)
{
	position_.x += offset.x;
	position_.y += offset.y;
	transformationUpdate_ = true;
	inverseTransformationUpdate_ = true;
}

void Transformable::rotate(float degree)
{
	setRotation(degree);
}

void Transformable::scale(float scale_x, float scale_y)
{
	x_scale_ *= scale_x;
	y_scale_ *= scale_y;
	transformationUpdate_ = true;
	inverseTransformationUpdate_ = true;
}