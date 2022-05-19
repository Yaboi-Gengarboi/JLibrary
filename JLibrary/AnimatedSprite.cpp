// JLibrary
// AnimatedSprite.cpp
// Created on 2022-05-15 by Justyn Durnford
// Last modified on 2022-05-15 by Justyn Durnford
// Source file for the AnimatedSprite class.

#include "AnimatedSprite.hpp"

#include "SFML/Graphics/Rect.hpp"

#include "SFML/Graphics/Sprite.hpp"
using sf::Sprite;

#include "SFML/Graphics/Texture.hpp"
using sf::Texture;

#include "SFML/Graphics/RenderWindow.hpp"
using sf::RenderWindow;

namespace jlib
{
	AnimatedSprite::AnimatedSprite()
	{
		rows = 0;
		cols = 0;
		spriteCount = 0;
		spriteWidth = 0;
		spriteHeight = 0;
		spriteDuration = 0;
		rowIndex = 0;
		colIndex = 0;
		spriteCounter = 0;
		tickCounter = 0;
	}

	AnimatedSprite::AnimatedSprite(const Texture& texture, const Vector2i& new_startVertex, u16 new_rows,
								   u16 new_cols, u16 new_spriteCount, u16 new_spriteWidth, u16 new_spriteHeight, u16 new_spriteDuration)
	{
		startVertex = new_startVertex;
		rows = new_rows;
		cols = new_cols;
		spriteCount = new_spriteCount;
		spriteWidth = new_spriteWidth;
		spriteHeight = new_spriteHeight;
		spriteDuration = new_spriteDuration;
		rowIndex = 0;
		colIndex = 0;
		spriteCounter = 0;
		tickCounter = 0;
		spriteBounds = sf::IntRect(startVertex.x, startVertex.y, spriteWidth, spriteHeight);
		sprite.setTexture(texture);
		sprite.setTextureRect(spriteBounds);
	}

	void AnimatedSprite::reset()
	{
		rowIndex = 0;
		colIndex = 0;
		spriteCounter = 0;
		tickCounter = 0;
		spriteBounds.left = startVertex.x;
		spriteBounds.top = startVertex.y;
	}

	void AnimatedSprite::update()
	{
		++tickCounter;

		if (tickCounter == spriteDuration)
		{
			++spriteCounter;

			if (spriteCounter == spriteCount)
			{
				reset();
				sprite.setTextureRect(spriteBounds);
			}
			else
			{
				++colIndex;

				if (colIndex == cols)
				{
					colIndex = 0;
					++rowIndex;
				}

				spriteBounds.left = (colIndex * spriteWidth) + startVertex.x;
				spriteBounds.top = (rowIndex * spriteHeight) + startVertex.y;
				sprite.setTextureRect(spriteBounds);
				tickCounter = 0;
			}
		}
	}

	void AnimatedSprite::render(Ptr<RenderWindow> window)
	{
		window->draw(sprite);
	}
}