// JLibraryDevelopment
// VertexArray.hpp
// Created on 2021-07-05 by Justyn Durnford
// Last modified on 2021-07-15 by Justyn Durnford
// Header file for the VertexArray class.

#pragma once

#include <JLibrary/Graphics/Drawable.hpp>
#include <JLibrary/Graphics/PrimitiveType.hpp>
#include <JLibrary/Graphics/Vertex2.hpp>
#include <JLibrary/Math/Rectangle.hpp>
#include <vector>

namespace jlib
{
	// Defines a set of one or more 2D primitives.
	class VertexArray : public Drawable
	{
		std::vector<Vertex2> vertices_;
		PrimitiveType primitiveType_;

		// Draws the vertex array to a render target.
		virtual void draw(RenderTarget& target, RenderStates states) const;

		public:

        // Default constructor.
        // Creates an empty vertex array.
        VertexArray();

        // Constructs the vertex array with a type and an initial number of vertices.
        explicit VertexArray(PrimitiveType type, std::size_t vertexCount = 0);

        // Returns the vertex count.
        std::size_t getVertexCount() const;

        // Clears the vertex array.
        // This function removes all the vertices from the array.
        // It doesn't deallocate the corresponding memory, so that
        // adding new vertices after clearing doesn't involve
        // reallocating all the memory.
        void clear();

        // Resizes the vertex array.
        // If vertexCount is greater than the current size, the previous
        // vertices are kept and new (default-constructed) vertices are added.
        // If vertexCount is less than the current size, existing vertices
        // are removed from the array.
        void resize(std::size_t vertexCount);

        // Adds a vertex to the end of the array.
        void append(const Vertex2& vertex);

        // Gets the type of primitives drawn by the vertex array.
        PrimitiveType getPrimitiveType() const;

        // Sets the type of primitives to draw.
        // This function defines how the vertices must be interpreted
        // when it's time to draw them.
        void setPrimitiveType(PrimitiveType type);

        // Computes the bounding rectangle of the vertex array.
        // This function returns the minimal axis-aligned rectangle
        // that contains all the vertices of the array.
        FloatRect getBounds() const;

        // Gets a read-write access vertex by its index.
        // This function doesn't check the index, it must be in range
        // [0, getVertexCount() - 1]. The behavior is undefined otherwise.
        Vertex2& operator [] (std::size_t index);

        // Gets a read-only access vertex by its index.
        // This function doesn't check the index, it must be in range
        // [0, getVertexCount() - 1]. The behavior is undefined otherwise.
        const Vertex2& operator [] (std::size_t index) const;
	};
}