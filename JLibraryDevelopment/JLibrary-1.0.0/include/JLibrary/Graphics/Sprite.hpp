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
// Sprite.hpp
// Created on 2021-07-07 by Justyn Durnford
// Last modified on 2021-07-07 by Justyn Durnford
// Header file for the Sprite class.

#pragma once

#include <JLibrary/Graphics/Drawable.hpp>
#include <JLibrary/Graphics/Transformable.hpp>
#include <JLibrary/Graphics/Vertex2.hpp>
#include <JLibrary/Math/Rectangle.hpp>
#include <array>

namespace jlib
{
	class Texture;

	// Drawable representation of a texture, with its
	// own transformations, color, etc.
	class Sprite : public Drawable, public Transformable
	{
		std::array<Vertex2, 4> vertices_;
		const Texture* texture_;
		IntRect textureRect_;

        // Draws the sprite to a render target.
        virtual void draw(RenderTarget& target, RenderStates states) const;

        // Updates the vertices' positions.
        void updatePositions();

        // Updates the vertices' texture coordinates.
        void updateTexCoords();

		public:

        // Default constructor.
        // Creates an empty sprite with no source texture.
        Sprite();

        // Constructs the sprite from a source texture.
        explicit Sprite(const Texture& texture);

        // Constructs the sprite from a sub-rectangle of a source texture.
        Sprite(const Texture& texture, const IntRect& rectangle);

        // Changes the source texture of the sprite.
        // The texture argument refers to a texture that must
        // exist as long as the sprite uses it. Indeed, the sprite
        // doesn't store its own copy of the texture, but rather keeps
        // a pointer to the one that you passed to this function.
        // If the source texture is destroyed and the sprite tries to
        // use it, the behavior is undefined.
        // If resetRect is true, the TextureRect property of
        // the sprite is automatically adjusted to the size of the new
        // texture. If it is false, the texture rect is left unchanged.
        void setTexture(const Texture& texture, bool resetRect = false);

        // Sets the sub-rectangle of the texture that the sprite will display.
        // The texture rect is useful when you don't want to display
        // the whole texture, but rather a part of it.
        // By default, the texture rect covers the entire texture.
        void setTextureRect(const IntRect& rectangle);

        // Sets the global color of the sprite.
        // This color is modulated (multiplied) with the sprite's
        // texture. It can be used to colorize the sprite, or change
        // its global opacity.
        // By default, the sprite's color is opaque white.
        void setColor(const Color& color);

        // Gets the source texture of the sprite.
        // If the sprite has no source texture, a nulptr is returned.
        // The returned pointer is const, which means that you can't
        // modify the texture when you retrieve it with this function.
        const Texture* texture() const;

        // Gets the sub-rectangle of the texture displayed by the sprite.
        const IntRect& textureRect() const;

        // Gets the global color of the sprite.
        const Color& color() const;

        // Gets the local bounding rectangle of the entity.
        // The returned rectangle is in local coordinates, which means
        // that it ignores the transformations (translation, rotation,
        // scale, ...) that are applied to the entity.
        // In other words, this function returns the bounds of the
        // entity in the entity's coordinate system.
        FloatRect localBounds() const;

        // Gets the global bounding rectangle of the entity.
        // The returned rectangle is in global coordinates, which means
        // that it takes into account the transformations (translation,
        // rotation, scale, ...) that are applied to the entity.
        // In other words, this function returns the bounds of the
        // sprite in the global 2D world's coordinate system.
        FloatRect globalBounds() const;
	};
}