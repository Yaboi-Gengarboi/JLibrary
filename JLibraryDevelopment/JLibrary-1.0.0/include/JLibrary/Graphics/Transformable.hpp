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
// Transformable.hpp
// Created on 2021-06-03 by Justyn Durnford
// Last modified on 2021-06-29 by Justyn Durnford
// Header file for the Transformable class.

#pragma once

#include <JLibrary/Graphics/Transformation.hpp>

namespace jlib
{
	//
	class Transformable
	{
		Point2f origin_;   // Origin of the translation/rotation/scaling.
		Point2f position_; // Actuall position of the object.
		float rotation_;      // Degrees.
		float x_scale_;
		float y_scale_;
		mutable Transformation transformation_;
		mutable bool transformationUpdate_;
		mutable Transformation inverseTransformation_;
		mutable bool inverseTransformationUpdate_;

		public:

		// Default constructor.
		Transformable();

		// Copy constructor.
		Transformable(const Transformable& other) = default;

		// Move constructor.
		Transformable(Transformable&& other) = default;

		// Copy assignment operator.
		Transformable& operator = (const Transformable& other) = default;

		// Move assignment operator.
		Transformable& operator = (Transformable&& other) = default;

		// Virtual destructor.
		virtual ~Transformable();

		// Returns the position of the transformable object.
		Point2f position() const;

		// Returns the origin of the transformable object.
		Point2f origin() const;

		// Returns the rotation angle of the transformable object.
		float rotation() const;

		// Returns the x scale factor of the transformable object.
		float x_scale() const;

		// Returns the y scale factor of the transformable object.
		float y_scale() const;

		// Returns the total transformation of the transformable object.
		const Transformation& transformation() const;

		// Returns the inverse of the total transformation of the transformable object.
		const Transformation& inverseTransformation() const;

		// Sets the position of the transformable object to the Point2_32f given as (X, Y).
		void setPosition(float X, float Y);

		// Sets the position of the transformable object to the given Point2_32f.
		void setPosition(const Point2f& position);

		// Sets the origin of the transformable object to the Point2_32f given as (X, Y).
		void setOrigin(float X, float Y);

		// Sets the origin of the transformable object to the given Point2_32f.
		void setOrigin(const Point2f& origin);

		// Sets the rotation angle of the transformable object to the given float.
		void setRotation(float degree);

		// Sets the scale factors of the transformable object to the given factors.
		void setScale(float scale_x, float scale_y);

		// Move the transformable object's position by the given offset.
		void move(float offset_x, float offset_y);

		// Move the transformable object's position by the given offset.
		void move(const Vector2f& offset);

		// Rotates the transformable object by the given angle.
		void rotate(float degree);

		// Scales the transformable object by the given scales.
		void scale(float scale_x, float scale_y);
	};
}