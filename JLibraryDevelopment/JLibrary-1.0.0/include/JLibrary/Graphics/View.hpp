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
// View.hpp
// Created on 2021-07-05 by Justyn Durnford
// Last modified on 2021-07-05 by Justyn Durnford
// Header file for the View class.

#pragma once

#include <JLibrary/Graphics/Transformation.hpp>
#include <JLibrary/Math/Rectangle.hpp>
#include <JLibrary/Math/Vector2.hpp>

namespace jlib
{
	// 2D camera that defines what region is shown on screen.
	class View
	{
        Point2f                center_;             
        float                  width_;
        float                  height_;
        Angle                  rotation_;           
        FloatRect              viewport_;
        mutable Transformation transform_;
        mutable Transformation inverseTransform_;
        mutable bool           transformUpdated_;
        mutable bool           invTransformUpdated_;

        public:

        // Default constructor.
        // This constructor creates a default view of (0, 0, 1000, 1000).
        View();

        // Constructs the view from a rectangle.
        explicit View(const FloatRect& rectangle);

        // Constructs the view from its center and size.
        View(const Vector2f& center, const Vector2f& size);

        // Sets the center of the view.
        void setCenter(float x, float y);

        // Sets the center of the view.
        void setCenter(const Point2f& center);

        // Sets the width of the view.
        float setWidth(float width) const;

        // Sets the height of the view.
        float setHeight(float height) const;

        // Sets the size of the view.
        void setSize(float width, float height);

        // Sets the orientation of the view.
        // The default rotation of a view is 0 degrees.
        void setRotation(Angle angle);

        // Sets the target viewport.
        // The viewport is the rectangle into which the contents of the
        // view are displayed, expressed as a factor (between 0 and 1)
        // of the size of the RenderTarget to which the view is applied.
        // For example, a view which takes the left side of the target would
        // be defined with View.setViewport(jlib::FloatRect(0, 0, 0.5, 1)).
        // By default, a view has a viewport which covers the entire target.
        void setViewport(const FloatRect& viewport);

        // Resets the view to the given rectangle.
        // Note that this function also resets the rotation angle to 0.
        void reset(const FloatRect& rectangle);

        // Gets the center of the view.
        Point2f center() const;

        // Gets the width of the view.
        float width() const;

        // Gets the height of the view.
        float height() const;

        // Gets the current orientation of the view.
        Angle rotation() const;

        // Gets the target viewport rectangle of the view.
        FloatRect viewport() const;

        // Moves the view relative to its current position.
        void move(float offsetX, float offsetY);

        //  Moves the view relative to its current position.
        void move(const Vector2f& offset);

        // Rotates the view relative to its current orientation.
        void rotate(Angle angle);

        // Resizes the view rectangle relative to its current size.
        // Resizing the view simulates a zoom, as the zone displayed on
        // screen grows or shrinks.
        void zoom(float factor);

        // Gets the projection transformation of the view.
        // This function is meant for internal use only.
        const Transformation& getTransformation() const;

        // Gets the inverse projection transformation of the view.
        // This function is meant for internal use only.
        const Transformation& getInverseTransformation() const;
	};
}