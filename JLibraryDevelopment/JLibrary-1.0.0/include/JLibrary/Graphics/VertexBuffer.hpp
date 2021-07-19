// JLibraryDevelopment
// VertexBuffer.hpp
// Created on 2021-07-05 by Justyn Durnford
// Last modified on 2021-07-15 by Justyn Durnford
// Header file for the VertexBuffer class.

#pragma once

#include <JLibrary/Graphics/Drawable.hpp>
#include <JLibrary/Graphics/GlResource.hpp>
#include <JLibrary/Graphics/PrimitiveType.hpp>

namespace jlib
{
	class RenderTarget;
	class Vertex2;

	// Vertex buffer storage for one or more 2D primitives.
	class VertexBuffer : public Drawable, private GlResource
	{
		public:

        // Usage specifiers.
        // If data is going to be updated once or more every frame,
        // set the usage to Stream. If data is going to be set once
        // and used for a long time without being modified, set the
        // usage to Static. For everything else Dynamic should be a
        // good compromise.
        enum Usage
        {
            Stream,  
            Dynamic, 
            Static   
        };

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

        private:

        u32           buffer_;        
        std::size_t   size_;          
        PrimitiveType primitiveType_; 
        Usage         usage_;     

        // Draws the vertex buffer to a render target.
        virtual void draw(RenderTarget& target, RenderStates states) const;

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

        public:

        // Default constructor.
        // Creates an empty vertex buffer.
        VertexBuffer();

        // Constructs a VertexBuffer with a specific PrimitiveType.
        explicit VertexBuffer(PrimitiveType type);

        // Constructs a VertexBuffer with a specific usage specifier.
        explicit VertexBuffer(Usage usage);

        // Constructs a VertexBuffer with a specific PrimitiveType and usage specifier.
        VertexBuffer(PrimitiveType type, Usage usage);

        // Copy constructor.
        VertexBuffer(const VertexBuffer& other);

        // Copy assignment operator
        VertexBuffer& operator = (const VertexBuffer& other);

        // Destructor.
        ~VertexBuffer();

        // Creates the vertex buffer and allocates enough graphics
        // memory to hold vertexCount vertices. Any previously
        // allocated memory is freed in the process.
        // In order to deallocate previously allocated memory pass 0
        // as vertexCount. Don't forget to recreate with a non-zero
        // value when graphics memory should be allocated again.
        // Returns true if successful.
        bool create(std::size_t vertexCount);

        // Returns the vertex count.
        std::size_t getVertexCount() const;

        // Updates the whole buffer from an array of vertices.
        // The vertex array is assumed to have the same size as
        // the created buffer.
        // No additional check is performed on the size of the vertex
        // array, passing invalid arguments will lead to undefined
        // behavior.
        // This function does nothing if vertices is nullptr or if the
        // buffer was not previously created.
        // Returns true if successful.
        bool update(const Vertex2* vertices);
        
        // Updates a part of the buffer from an array of vertices.
        // offset is specified as the number of vertices to skip
        // from the beginning of the buffer.
        //  - If offset is 0 and vertexCount is equal to the size of
        //    the currently created buffer, its whole contents are replaced.
        //  - If \p offset is 0 and \p vertexCount is greater than the
        //    size of the currently created buffer, a new buffer is created
        //    containing the vertex data.
        //  - If offset is 0 and vertexCount is less than the size of
        //    the currently created buffer, only the corresponding region
        //    is updated.
        //  - If offset is not 0 and offset + vertexCount is greater
        //    than the size of the currently created buffer, the update fails.
        // No additional check is performed on the size of the vertex
        // array, passing invalid arguments will lead to undefined
        // behavior.
        // Returns true if successful.
        bool update(const Vertex2* vertices, std::size_t vertexCount, u32 offset);

        // Copies the contents of another buffer into this buffer.
        // Returns true if successful.
        bool update(const VertexBuffer& vertexBuffer);

        // Swaps the contents of this vertex buffer with those of another.
        void swapWith(VertexBuffer& other);

        // Gets the underlying OpenGL handle of the vertex buffer.
        // You shouldn't need to use this function, unless you have
        // very specific stuff to implement that the JLibrary doesn't 
        // support, or implement a temporary workaround until a bug is fixed.
        u32 getNativeHandle() const;

        // Gets the type of primitives drawn by the vertex buffer.
        PrimitiveType getPrimitiveType() const;

        // Sets the type of primitives to draw.
        // This function defines how the vertices must be interpreted
        // when it's time to draw them.
        void setPrimitiveType(PrimitiveType type);

        // Gets the usage specifier of this vertex buffer.
        Usage getUsage() const;

        // Sets the usage specifier of this vertex buffer.
        // This function provides a hint about how this vertex buffer is
        // going to be used in terms of data update frequency.
        // After changing the usage specifier, the vertex buffer has
        // to be updated with new data for the usage specifier to
        // take effect.
        void setUsage(Usage usage);

        // Binds a vertex buffer for rendering.
        // This function is not part of the graphics API, it mustn't be
        // used when drawing JLibrary entities. It must be used only if you
        // mix jlib::VertexBuffer with OpenGL code.
        static void bind(const VertexBuffer* vertexBuffer);

        // Returns true if the system supports vertex buffers.
        // This function should always be called before using
        // the vertex buffer features. If it returns false, then
        // any attempt to use jlib::VertexBuffer will fail.
        static bool isAvailable();
	};
}