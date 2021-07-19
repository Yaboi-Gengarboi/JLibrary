// JLibraryDevelopment
// Shape.cpp
// Created on 2021-07-14 by Justyn Durnford
// Last modified on 2021-07-14 by Justyn Durnford
// Source file for the Shape class.

#include <JLibrary/Graphics/RenderTarget.hpp>
#include <JLibrary/Graphics/Shape.hpp>
#include <JLibrary/Graphics/Texture.hpp>
using namespace jlib;

#include <cmath>


#include <cstddef>
using std::size_t;

void Shape::draw(RenderTarget& target, RenderStates states) const
{
    states.transform *= transformation();

    // Render the inside.
    states.texture = texture_;
    target.draw(vertices_, states);

    // Render the outline.
    if (outlineThickness_ != 0)
    {
        states.texture = nullptr;
        target.draw(outlineVertices_, states);
    }
}

void Shape::updateFillColors()
{
    for (size_t i = 0; i < vertices_.getVertexCount(); ++i)
        vertices_[i].color = fillColor_;
}

void Shape::updateTexCoords()
{
    for (size_t i = 0; i < vertices_.getVertexCount(); ++i)
    {
        float xratio, yratio;

        if (insideBounds_.width > 0)
            xratio = (vertices_[i].position.x - insideBounds_.vertex.x) / insideBounds_.width;
        else
            xratio = 0;

        if (insideBounds_.height > 0)
            yratio = (vertices_[i].position.y - insideBounds_.vertex.y) / insideBounds_.height;
        else
            yratio = 0;

        vertices_[i].textureCoordinates.x = textureRect_.vertex.x + textureRect_.width * xratio;
        vertices_[i].textureCoordinates.y = textureRect_.vertex.y + textureRect_.height * yratio;
    }
}

void Shape::updateOutline()
{
    // Return if there is no outline.
    if (outlineThickness_ == 0.f)
    {
        outlineVertices_.clear();
        bounds_ = insideBounds_;
        return;
    }

    size_t count = vertices_.getVertexCount() - 2;
    outlineVertices_.resize((count + 1) * 2);

    for (size_t i = 0; i < count; ++i)
    {
        size_t index = i + 1;

        // Get the two segments shared by the current point.
        Point2f p0;

        if (i == 0)
            p0 = vertices_[count].position;
        else
            p0 = vertices_[index - 1].position;

        Point2f p1 = vertices_[index + 0].position;
        Point2f p2 = vertices_[index + 1].position;

        // Compute their normal.
        Vector2f n1 = normal_vector(Vector2f(p0, p1));
        Vector2f n2 = normal_vector(Vector2f(p1, p2));

        // Make sure that the normals point towards the outside of the shape
        // (this depends on the order in which the points were defined).
        if (dot_product(n1, Vector2f(p1, vertices_[0].position)) > 0)
            n1 = -n1;
        if (dot_product(n2, Vector2f(p1, vertices_[0].position)) > 0)
            n2 = -n2;

        // Combine them to get the extrusion direction.
        float factor = 1.f + (n1.x * n2.x + n1.y * n2.y);
        Vector2f normal = (n1 + n2) / factor;

        // Update the outline points.
        outlineVertices_[i * 2 + 0].position = p1;
        outlineVertices_[i * 2 + 1].position.x = p1.x + normal.x * outlineThickness_;
        outlineVertices_[i * 2 + 1].position.y = p1.y + normal.y * outlineThickness_;
    }

    // Duplicate the first point at the end, to close the outline.
    outlineVertices_[count * 2 + 0].position = outlineVertices_[0].position;
    outlineVertices_[count * 2 + 1].position = outlineVertices_[1].position;

    // Update outline colors.
    updateOutlineColors();

    // Update the shape's bounds.
    bounds_ = outlineVertices_.getBounds();
}

void Shape::updateOutlineColors()
{
    for (size_t i = 0; i < outlineVertices_.getVertexCount(); ++i)
        outlineVertices_[i].color = outlineColor_;
}

Shape::Shape() : vertices_(TriangleFan), outlineVertices_(TriangleStrip)
{
    texture_ = nullptr;
    fillColor_ = Color(255, 255, 255, 255);
    outlineColor_ = Color(255, 255, 255, 255);
    outlineThickness_ = 0;
}

void Shape::update()
{
    // Get the total number of points of the shape.
    size_t count = getPointCount();
    if (count < 3)
    {
        vertices_.resize(0);
        outlineVertices_.resize(0);
        return;
    }

    vertices_.resize(count + 2); // + 2 for center and repeated first point.

    // Position.
    for (size_t i = 0; i < count; ++i)
        vertices_[i + 1].position = getPoint(i);
    vertices_[count + 1].position = vertices_[1].position;

    // Update the bounding rectangle.
    vertices_[0] = vertices_[1]; // so that the result of getBounds() is correct.
    insideBounds_ = vertices_.getBounds();

    // Compute the center and make it the first vertex.
    vertices_[0].position.x = insideBounds_.vertex.x + insideBounds_.width / 2;
    vertices_[0].position.y = insideBounds_.vertex.y + insideBounds_.height / 2;

    // Color.
    updateFillColors();

    // Texture coordinates.
    updateTexCoords();

    // Outline.
    updateOutline();
}

Shape::~Shape() {}

const Texture* Shape::getTexture() const
{
    return texture_;
}

void Shape::setTexture(const Texture* texture, bool resetRect)
{
    if (texture)
    {
        // Recompute the texture area if requested, or if there was no texture & rect before.
        if (resetRect || (!texture_ && (textureRect_ == IntRect())))
            setTextureRect(IntRect(0, 0, texture->width(), texture->height()));
    }

    // Assign the new texture.
    texture_ = texture;
}

const IntRect& Shape::getTextureRect() const
{
    return textureRect_;
}

void Shape::setTextureRect(const IntRect& rect)
{
    textureRect_ = rect;
    updateTexCoords();
}

const Color& Shape::getFillColor() const
{
    return fillColor_;
}

void Shape::setFillColor(const Color& color)
{
    fillColor_ = color;
    updateFillColors();
}

const Color& Shape::getOutlineColor() const
{
    return outlineColor_;
}

void Shape::setOutlineColor(const Color& color)
{
    outlineColor_ = color;
    updateOutlineColors();
}

float Shape::getOutlineThickness() const
{
    return outlineThickness_;
}

void Shape::setOutlineThickness(float thickness)
{
    outlineThickness_ = thickness;
    update(); // recompute everything because the whole shape must be offset.
}

FloatRect Shape::getLocalBounds() const
{
    return bounds_;
}

FloatRect Shape::getGlobalBounds() const
{
    return transformation().transformRectangle(getLocalBounds());
}