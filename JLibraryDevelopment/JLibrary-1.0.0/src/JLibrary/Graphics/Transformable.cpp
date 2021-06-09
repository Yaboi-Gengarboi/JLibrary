// JLibraryDevelopment
// Transformable.cpp
// Created on 2021-06-09 by Justyn Durnford
// Last modified on 2021-06-09 by Justyn Durnford
// Source file for the Transformable class.

#include <JLibrary/Graphics/Transformable.hpp>
#include <cmath>
using namespace std;
using namespace jl;

Transformable::Transformable()
{
	rotation_ = 0.f;
	scale_.x = 1.f;
	scale_.y = 1.f;
	transformationUpdate_ = true;
	inverseTransformationUpdate_ = true;
}

Transformable::~Transformable() {}

Point2_32f Transformable::position() const
{
	return position_;
}

Point2_32f Transformable::origin() const
{
	return origin_;
}

float Transformable::rotation() const
{
	return rotation_;
}

Vector2_32f Transformable::scale() const
{
	return scale_;
}

const Transformation& Transformable::transformation() const
{
	if (transformationUpdate_) // Update transformation
	{
		float angle = -rotation_ * 3.141592654f / 180.f;
		float cosine = cos(angle);
		float sine = sin(angle);
		float sxc = scale_.x * cosine;
		float syc = scale_.y * cosine;
		float sxs = scale_.x * sine;
		float sys = scale_.y * sine;
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

void Transformable::setPosition(const Point2_32f& position)
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

void Transformable::setOrigin(const Point2_32f& origin)
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
	scale_.x = scale_x;
	scale_.y = scale_y;
}

void Transformable::setScale(const Vector2_32f& scale)
{
	scale_ = scale;
}

void Transformable::move(float offset_x, float offset_y)
{
	position_.x += offset_x;
	position_.y += offset_y;
	transformationUpdate_ = true;
	inverseTransformationUpdate_ = true;
}

void Transformable::move(const Vector2_32f& offset)
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
	scale_.x *= scale_x;
	scale_.y *= scale_y;
	transformationUpdate_ = true;
	inverseTransformationUpdate_ = true;
}

void Transformable::scale(const Vector2_32f& scale)
{
	scale_.x *= scale.x;
	scale_.y *= scale.y;
	transformationUpdate_ = true;
	inverseTransformationUpdate_ = true;
}