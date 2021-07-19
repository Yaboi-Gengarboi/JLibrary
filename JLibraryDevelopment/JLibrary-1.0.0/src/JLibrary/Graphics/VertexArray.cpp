// JLibraryDevelopment
// VertexArray.cpp
// Created on 2021-07-14 by Justyn Durnford
// Last modified on 2021-07-15 by Justyn Durnford
// Source file for the VertexArray class.

#include <JLibrary/Graphics/VertexArray.hpp>
#include <JLibrary/Graphics/RenderTarget.hpp>
using namespace jlib;

#include <vector>
using std::size_t;
using std::vector;

void VertexArray::draw(RenderTarget& target, RenderStates states) const
{
    if (!vertices_.empty())
        target.draw(&vertices_[0], vertices_.size(), primitiveType_, states);
}

VertexArray::VertexArray()
{
    primitiveType_ = PrimitiveType::Points;
}

VertexArray::VertexArray(PrimitiveType type, size_t vertexCount)
{
    vertices_.resize(vertexCount);
    primitiveType_ = type;
}

size_t VertexArray::getVertexCount() const
{
    return vertices_.size();
}

void VertexArray::clear()
{
    vertices_.clear();
}

void VertexArray::resize(size_t vertexCount)
{
    vertices_.resize(vertexCount);
}

void VertexArray::append(const Vertex2& vertex)
{
    vertices_.push_back(vertex);
}

PrimitiveType VertexArray::getPrimitiveType() const
{
    return primitiveType_;
}

void VertexArray::setPrimitiveType(PrimitiveType type)
{
    primitiveType_ = type;
}

FloatRect VertexArray::getBounds() const
{
    if (!vertices_.empty())
    {
        float left = vertices_[0].position.x;
        float top = vertices_[0].position.y;
        float right = vertices_[0].position.x;
        float bottom = vertices_[0].position.y;

        for (size_t i = 1; i < vertices_.size(); ++i)
        {
            Point2f position = vertices_[i].position;

            // Update left and right.
            if (position.x < left)
                left = position.x;
            else if (position.x > right)
                right = position.x;

            // Update top and bottom.
            if (position.y < top)
                top = position.y;
            else if (position.y > bottom)
                bottom = position.y;
        }

        return FloatRect(left, top, right - left, bottom - top);
    }

    return FloatRect();
}

Vertex2& VertexArray::operator [] (size_t index)
{
    return vertices_[index];
}

const Vertex2& VertexArray::operator [] (size_t index) const
{
    return vertices_[index];
}