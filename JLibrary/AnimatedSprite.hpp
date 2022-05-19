// JLibrary
// AnimatedSprite.hpp
// Created on 2022-05-15 by Justyn Durnford
// Last modified on 2022-05-15 by Justyn Durnford
// Header file for the AnimatedSprite class.

#pragma once

#include "SFML/Graphics/Rect.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "IntegerTypedefs.hpp"

import Ptr;
import Vector2;

namespace jlib
{
	// Class that represents a Sprite that changes over time.
	class AnimatedSprite
	{
		public:

		sf::Sprite sprite;
		Vector2i startVertex;
		sf::IntRect spriteBounds;
		u16 rows;
		u16 cols;
		u16 spriteCount;
		u16 spriteWidth;
		u16 spriteHeight;
		u16 spriteDuration;
		u16 rowIndex;
		u16 colIndex;
		u16 spriteCounter;
		u16 tickCounter;

		// Default constructor.
		AnimatedSprite();

		// Primary constructor.
		AnimatedSprite(const sf::Texture& texture, const Vector2i& new_startVertex, u16 new_rows, u16 new_cols,
					   u16 new_spriteCount, u16 new_spriteWidth, u16 new_spriteHeight, u16 new_spriteDuration);

		// Move constructor.
		AnimatedSprite(AnimatedSprite&& other) = default;

		// Move assignment operator.
		AnimatedSprite& operator = (AnimatedSprite&& other) = default;

		// Destructor.
		~AnimatedSprite() = default;

		// Resets the AnimatedSprite.
		void reset();

		// Updates the AnimatedSprite.
		void update();

		// Draws the AnimatedSprite to the window.
		void render(Ptr<sf::RenderWindow> window);
	};
}