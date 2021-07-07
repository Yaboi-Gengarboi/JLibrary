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
// Shape.hpp
// Created on 2021-07-07 by Justyn Durnford
// Last modified on 2021-07-07 by Justyn Durnford
// Header file for the Shape class.

#pragma once

#include <JLibrary/Graphics/Drawable.hpp>
#include <JLibrary/Graphics/Transformable.hpp>
#include <JLibrary/Graphics/VertexArray.hpp>

namespace jlib
{
	// Base class for textured shapes with outline.
	class Shape : public Drawable, public Transformable
	{
        const Texture* texture_;          // Texture of the shape
        IntRect        textureRect_;      // Rectangle defining the area of the source texture to display
        Color          fillColor_;        // Fill color
        Color          outlineColor_;     // Outline color
        float          outlineThickness_; // Thickness of the shape's outline
        VertexArray    vertices_;         // Vertex array containing the fill geometry
        VertexArray    outlineVertices_;  // Vertex array containing the outline geometry
        FloatRect      insideBounds_;     // Bounding rectangle of the inside (fill)
        FloatRect      bounds_;           // Bounding rectangle of the whole shape (outline + fill)

        // Draws the shape to a render target.
        virtual void draw(RenderTarget& target, RenderStates states) const;

        // Updates the fill vertices' color.
        void updateFillColors();

        // Updates the fill vertices' texture coordinates.
        void updateTexCoords();

        // Updates the outline vertices' position.
        void updateOutline();

        // Updates the outline vertices' color.
        void updateOutlineColors();

        protected:

        // Default constructor.
        Shape();

        // Recomputes the internal geometry of the shape.
        // This function must be called by the derived class everytime
        // the shape's points change (i.e. the result of either
        // getPointCount or getPoint is different).
        void update();

        public:

        // Destructor.
        virtual ~Shape();

        // Changes the source texture of the shape.
        // The texture argument refers to a texture that must
        // exist as long as the shape uses it. Indeed, the shape
        // doesn't store its own copy of the texture, but rather keeps
        // a pointer to the one that you passed to this function.
        // If the source texture is destroyed and the shape tries to
        // use it, the behavior is undefined.
        // texture can be nullptr to disable texturing.
        // If resetRect is true, the TextureRect property of
        // the shape is automatically adjusted to the size of the new
        // texture. If it is false, the texture rect is left unchanged.
        void setTexture(const Texture* texture, bool resetRect = false);

        // Sets the sub-rectangle of the texture that the shape will display.
        /// The texture rect is useful when you don't want to display
        /// the whole texture, but rather a part of it.
        /// By default, the texture rect covers the entire texture.
        void setTextureRect(const IntRect& rect);

        // Sets the fill color of the shape.
        // This color is modulated (multiplied) with the shape's
        // texture if any. It can be used to colorize the shape,
        // or change its global opacity.
        // You can use jlib::Color::Transparent to make the inside of
        // the shape transparent, and have the outline alone.
        // By default, the shape's fill color is opaque white.
        void setFillColor(const Color& color);

        // Sets the outline color of the shape.
        // By default, the shape's outline color is opaque white.
        void setOutlineColor(const Color& color);

        // Sets the thickness of the shape's outline.
        // Note that negative values are allowed (so that the outline
        // expands towards the center of the shape), and using zero
        // disables the outline.
        // By default, the outline thickness is 0.
        void setOutlineThickness(float thickness);

        // Gets the source texture of the shape.
        // If the shape has no source texture, a nullptr is returned.
        // The returned pointer is const, which means that you can't
        // modify the texture when you retrieve it with this function.
        const Texture* getTexture() const;

        // Gets the sub-rectangle of the texture displayed by the shape.
        const IntRect& getTextureRect() const;

        // Gets the fill color of the shape.
        const Color& getFillColor() const;

        // Gets the outline color of the shape.
        const Color& getOutlineColor() const;

        // Gets the outline thickness of the shape.
        float getOutlineThickness() const;

        // Gets the total number of points of the shape.
        virtual std::size_t getPointCount() const = 0;

        // Gets a point of the shape.
        // The returned point is in local coordinates, that is,
        // the shape's transforms (position, rotation, scale) are
        // not taken into account.
        // The result is undefined if the index is out of the valid range.
        virtual Point2f getPoint(std::size_t index) const = 0;

        // Gets the local bounding rectangle of the entity.
        // The returned rectangle is in local coordinates, which means
        // that it ignores the transformations (translation, rotation,
        // scale, ...) that are applied to the entity.
        // In other words, this function returns the bounds of the
        // entity in the entity's coordinate system.
        FloatRect getLocalBounds() const;

        // Gets the global (non-minimal) bounding rectangle of the entity.
        // The returned rectangle is in global coordinates, which means
        // that it takes into account the transformations (translation,
        // rotation, scale, ...) that are applied to the entity.
        // In other words, this function returns the bounds of the
        // shape in the global 2D world's coordinate system.
        // This function does not necessarily return the minimal
        // bounding rectangle. It merely ensures that the returned
        // rectangle covers all the vertices (but possibly more).
        // This allows for a fast approximation of the bounds as a
        // first check; you may want to use more precise checks
        // on top of that.
        FloatRect getGlobalBounds() const;
	};
}