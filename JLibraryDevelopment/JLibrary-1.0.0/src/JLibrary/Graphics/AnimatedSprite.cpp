// JLibraryDevelopment
// AnimatedSprite.cpp
// Created on 2021-07-18 by Justyn Durnford
// Last modified on 2021-07-18 by Justyn Durnford
// Source file for the AnimatedSprite class.

#include <JLibrary/Graphics/AnimatedSprite.hpp>
using namespace jlib;

#include <cmath>
using std::abs;

#include <cstddef>
using std::size_t;

AnimatedSprite::AnimatedSprite()
{
	texture_ = nullptr;
	width_ = 0;
	height_ = 0;
	cols_ = 0;
	frames_ = 0;
}

AnimatedSprite::AnimatedSprite(const Texture& texture, u32 width, u32 height, u32 cols, u32 frames)
{
	texture_ = &texture;
	width_ = width;
	height_ = height;
	cols_ = cols;
	frames_ = frames;
}

const Texture* AnimatedSprite::getTexture() const
{
	return texture_;
}

void AnimatedSprite::setTexture(const Texture& texture)
{
	texture_ = &texture;
}

u32 AnimatedSprite::getWidth() const
{
	return width_;
}

u32 AnimatedSprite::getHeight() const
{
	return height_;
}

u32 AnimatedSprite::getRows() const
{
	return (frames_ / cols_) + 1;
}

u32 AnimatedSprite::getCols() const
{
	return cols_;
}

u32 AnimatedSprite::getFrameCount() const
{
	return frames_;
}

Sprite AnimatedSprite::getFrame(u32 frame)
{
	return Sprite(*texture_, IntRect(width_ * (frame % cols_), height_ * (frame / cols_), width_, height_));
}