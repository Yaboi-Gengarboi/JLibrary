// JLibraryDevelopment
// View.cpp
// Created on 2021-07-15 by Justyn Durnford
// Last modified on 2021-07-16 by Justyn Durnford
// Source file for the View class.

#include <JLibrary/Window/View.hpp>
using namespace jlib;

#include <cmath>
using std::cosf;
using std::fmodf;
using std::sinf;

View::View()
{
    width_ = 0;
    height_ = 0;
    viewport_.set(0.f, 0.f, 1.f, 1.f);
    transformUpdated_ = false;
    invTransformUpdated_ = false;
    reset(FloatRect(0, 0, 1000, 1000));
}

View::View(const FloatRect& rectangle)
{
    viewport_.set(0.f, 0.f, 1.f, 1.f);
    transformUpdated_ = false;
    invTransformUpdated_ = false;
    reset(rectangle);
}

View::View(const Point2f& center, float width, float height)
{
    center_ = center;
    width_ = width;
    height_ = height;
    viewport_.set(0.f, 0.f, 1.f, 1.f);
    transformUpdated_ = false;
    invTransformUpdated_ = false;
}

Point2f View::getCenter() const
{
    return center_;
}

void View::setCenter(const Point2f& center)
{
    center_ = center;
    transformUpdated_ = false;
    invTransformUpdated_ = false;
}

void View::setCenter(float x, float y)
{
    center_.set(x, y);
    transformUpdated_ = false;
    invTransformUpdated_ = false;
}

float View::getWidth() const
{
    return width_;
}

void View::setWidth(float width)
{
    width_ = width;
    transformUpdated_ = false;
    invTransformUpdated_ = false;
}

float View::getHeight() const
{
    return height_;
}

void View::setHeight(float height)
{
    height_ = height;
    transformUpdated_ = false;
    invTransformUpdated_ = false;
}

void View::setSize(float width, float height)
{
    width_ = width;
    height_ = height;
    transformUpdated_ = false;
    invTransformUpdated_ = false;
}

Angle View::getRotation() const
{
    return rotation_;
}

void View::setRotation(Angle angle)
{
    rotation_.degree = fmodf(angle.degree, 360.f);
    if (rotation_ < 0.f)
        rotation_ += 360.f;

    transformUpdated_ = false;
    invTransformUpdated_ = false;
}

const FloatRect& View::getViewport() const
{
    return viewport_;
}

void View::setViewport(const FloatRect& viewport)
{
    viewport_ = viewport;
}

void View::reset(const FloatRect& rectangle)
{
    center_.x = rectangle.vertex.x + rectangle.width / 2.f;
    center_.y = rectangle.vertex.y + rectangle.height / 2.f;
    width_ = rectangle.width;
    height_ = rectangle.height;
    rotation_ = 0.f;

    transformUpdated_ = false;
    invTransformUpdated_ = false;
}

void View::move(float offsetX, float offsetY)
{
    setCenter(center_.x + offsetX, center_.y + offsetY);
}

void View::move(const Vector2f& offset)
{
    setCenter(center_.x + offset.x, center_.y + offset.y);
}

void View::rotate(Angle angle)
{
    setRotation(rotation_ + angle);
}

void View::zoom(float factor)
{
    setSize(width_ * factor, height_ * factor);
}

const Transformation& View::getTransformation() const
{
    // Recompute the matrix if needed.
    if (!transformUpdated_)
    {
        // Rotation components.
        float angle = to_radians(rotation_.degree);
        float cosine = static_cast<float>(cosf(angle));
        float sine = static_cast<float>(sinf(angle));
        float tx = -center_.x * cosine - center_.y * sine + center_.x;
        float ty = center_.x * sine - center_.y * cosine + center_.y;

        // Projection components.
        float a = 2.f / width_;
        float b = -2.f / height_;
        float c = -a * center_.x;
        float d = -b * center_.y;

        // Rebuild the projection matrix.
        transform_ = Transformation(a * cosine, a * sine, a * tx + c,
                                    -b * sine, b * cosine, b * ty + d,
                                    0.f, 0.f, 1.f);
        transformUpdated_ = true;
    }

    return transform_;
}

const Transformation& View::getInverseTransformation() const
{
    // Recompute the matrix if needed.
    if (!invTransformUpdated_)
    {
        inverseTransform_ = getTransformation().inverse();
        invTransformUpdated_ = true;
    }

    return inverseTransform_;
}