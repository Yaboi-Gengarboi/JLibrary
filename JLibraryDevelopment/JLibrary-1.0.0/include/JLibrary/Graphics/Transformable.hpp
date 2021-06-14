// JLibraryDevelopment
// Transformable.hpp
// Created on 2021-06-03 by Justyn Durnford
// Last modified on 2021-06-13 by Justyn Durnford
// Header file for the Transformable class.

#pragma once

#include <JLibrary/Graphics/Transformation.hpp>

namespace jlib
{
	//
	class Transformable
	{
		Point2_32f origin_;   // Origin of the translation/rotation/scaling.
		Point2_32f position_; // Actuall position of the object.
		float rotation_;      // Degrees.
		Vector2_32f scale_;
		mutable Transformation transformation_;
		mutable bool transformationUpdate_;
		mutable Transformation inverseTransformation_;
		mutable bool inverseTransformationUpdate_;

		public:

		// Default constructor.
		Transformable();

		// Virtual destructor.
		virtual ~Transformable();

		// Returns the position of the transformable object.
		Point2_32f position() const;

		// Returns the origin of the transformable object.
		Point2_32f origin() const;

		// Returns the rotation angle of the transformable object.
		float rotation() const;

		// Returns the scale factors of the transformable object.
		Vector2_32f scale() const;

		// Returns the total transformation of the transformable object.
		const Transformation& transformation() const;

		// Returns the inverse of the total transformation of the transformable object.
		const Transformation& inverseTransformation() const;

		// Sets the position of the transformable object to the Point2_32f given as (X, Y).
		void setPosition(float X, float Y);

		// Sets the position of the transformable object to the given Point2_32f.
		void setPosition(const Point2_32f& position);

		// Sets the origin of the transformable object to the Point2_32f given as (X, Y).
		void setOrigin(float X, float Y);

		// Sets the origin of the transformable object to the given Point2_32f.
		void setOrigin(const Point2_32f& origin);

		// Sets the rotation angle of the transformable object to the given float.
		void setRotation(float degree);

		// Sets the scale factors of the transformable object to the given factors.
		void setScale(float scale_x, float scale_y);

		// Sets the scale factors of the transformable object to the given factors.
		void setScale(const Vector2_32f& scale);

		// Move the transformable object's position by the given offset.
		void move(float offset_x, float offset_y);

		// Move the transformable object's position by the given offset.
		void move(const Vector2_32f& offset);

		// Rotates the transformable object by the given angle.
		void rotate(float degree);

		// Scales the transformable object by the given scales.
		void scale(float scale_x, float scale_y);

		// Scales the transformable object by the given scale.
		void scale(const Vector2_32f& scale);
	};
}