// JLibraryDevelopment
// Sprite.cpp
// Created on 2021-07-14 by Justyn Durnford
// Last modified on 2021-07-18 by Justyn Durnford
// Source file for the Sprite class.

#include <JLibrary/Graphics/RenderTarget.hpp>
#include <JLibrary/Graphics/Sprite.hpp>
#include <JLibrary/Graphics/Texture.hpp>
using namespace jlib;

#include <cmath>
using std::abs;

#include <cstddef>
using std::size_t;

void Sprite::draw(RenderTarget& target, RenderStates states) const
{
    if (texture_ != nullptr)
    {
        states.transform *= transformation();
        states.texture = texture_;
        target.draw(vertices_.data(), 4, TriangleStrip, states);
    }
}

void Sprite::updatePositions()
{
    FloatRect bounds = getLocalBounds();

    vertices_[0].position = Point2f(0, 0);
    vertices_[1].position = Point2f(0, bounds.height);
    vertices_[2].position = Point2f(bounds.width, 0);
    vertices_[3].position = Point2f(bounds.width, bounds.height);
}

void Sprite::updateTextureCoordinates()
{
    float left = static_cast<float>(textureRect_.vertex.x);
    float right = left + textureRect_.width;
    float top = static_cast<float>(textureRect_.vertex.y);
    float bottom = top + textureRect_.height;

    vertices_[0].textureCoordinates = Point2f(left, top);
    vertices_[1].textureCoordinates = Point2f(left, bottom);
    vertices_[2].textureCoordinates = Point2f(right, top);
    vertices_[3].textureCoordinates = Point2f(right, bottom);
}

Sprite::Sprite()
{
    texture_ = nullptr;
}

Sprite::Sprite(const Texture& texture)
{
    texture_ = nullptr;
    setTexture(texture, true);
}

Sprite::Sprite(const Texture& texture, const IntRect& rectangle)
{
    texture_ = nullptr;
    // Compute the texture area.
    setTextureRect(rectangle);
    // Assign texture.
    setTexture(texture, false);
}

const Texture* Sprite::getTexture() const
{
    return texture_;
}

void Sprite::setTexture(const Texture& texture, bool resetRect)
{
    // Recompute the texture area if requested, or if there was no valid texture & rect before.
    if (resetRect || (!texture_ && (textureRect_ == IntRect())))
    {
        u32 width = texture.width();
        u32 height = texture.height();
        setTextureRect(IntRect(0, 0, width, height));
    }

    // Assign the new texture.
    texture_ = &texture;
}

const IntRect& Sprite::getTextureRect() const
{
    return textureRect_;
}

void Sprite::setTextureRect(const IntRect& rectangle)
{
    if (rectangle != textureRect_)
    {
        textureRect_ = rectangle;
        updatePositions();
        updateTextureCoordinates();
    }
}

const Color& Sprite::getColor() const
{
    return vertices_[0].color;
}

void Sprite::setColor(const Color& color)
{
    // Update the vertices' color.
    for (size_t i = 0; i < 4; ++i)
        vertices_[i].color = color;
}

FloatRect Sprite::getLocalBounds() const
{
    float width = static_cast<float>(abs(textureRect_.width));
    float height = static_cast<float>(abs(textureRect_.height));

    return FloatRect(0.f, 0.f, width, height);
}

FloatRect Sprite::getGlobalBounds() const
{
    return transformation().transformRectangle(getLocalBounds());
}