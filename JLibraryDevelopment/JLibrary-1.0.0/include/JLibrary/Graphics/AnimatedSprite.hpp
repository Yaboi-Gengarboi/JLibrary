// JLibraryDevelopment
// AnimatedSprite.hpp
// Created on 2021-07-17 by Justyn Durnford
// Last modified on 2021-07-19 by Justyn Durnford
// Header file for the AnimatedSprite class.

#pragma once

#include <JLibrary/Graphics/Sprite.hpp>
#include <JLibrary/Graphics/Texture.hpp>
#include <JLibrary/Graphics/Vertex2.hpp>

namespace jlib
{
	// A class to generate individual Sprites from a 
	// spritesheet to generate and animated sprite.
	class AnimatedSprite
	{
		const Texture* texture_;
		u32 width_;
		u32 height_;
		u32 cols_;
		u32 frames_;

		public:

		// Default constructor.
		// Creates an empty AnimatedSprite with no source texture.
		AnimatedSprite();

		// Constructs the AnimatedSprite from a source texture,
		// a given frame count and frame dimensions.
		AnimatedSprite(const Texture& texture, u32 width, u32 height, u32 cols, u32 frames);

		// Gets the source texture of the AnimatedSprite.
		// If the sprite has no source texture, a nulptr is returned.
		// The returned pointer is const, which means that you can't
		// modify the texture when you retrieve it with this function.
		const Texture* getTexture() const;

		// Changes the source texture of the AnimatedSprite.
		// The texture argument refers to a texture that must
		// exist as long as the sprite uses it. Indeed, the sprite
		// doesn't store its own copy of the texture, but rather keeps
		// a pointer to the one that you passed to this function.
		// If the source texture is destroyed and the sprite tries to
		// use it, the behavior is undefined.
		void setTexture(const Texture& texture);

		// Returns the width of a Sprite frame.
		u32 getWidth() const;

		// Returns the height of a Sprite frame.
		u32 getHeight() const;

		// Returns the amount of rows of the spritesheet the AnimatedSprite uses.
		u32 getRows() const;

		// Returns the amount of columns of the spritesheet the AnimatedSprite uses.
		u32 getCols() const;

		// Returns the amount of frames the AnimatedSprite has.
		u32 getFrameCount() const;

		// Gets the Sprite generated at the given frame.
		Sprite getFrame(u32 frame);
	};
}