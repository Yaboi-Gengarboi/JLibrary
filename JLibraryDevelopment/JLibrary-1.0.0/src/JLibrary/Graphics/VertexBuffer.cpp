// JLibraryDevelopment
// VertexBuffer.cpp
// Created on 2021-07-15 by Justyn Durnford
// Last modified on 2021-07-15 by Justyn Durnford
// Source file for the VertexBuffer class.

#include <JLibrary/Graphics/GlContext.hpp>
#include <JLibrary/Graphics/RenderTarget.hpp>
#include <JLibrary/Graphics/VertexBuffer.hpp>
#include <JLibrary/Multithread/Lock.hpp>
#include <JLibrary/Multithread/Mutex.hpp>
using namespace jlib;

#include <cstring>
using std::size_t;
using std::memcpy;

#include <iostream>
using std::cout;
using std::endl;

#include <utility>
using std::swap;

namespace
{
    Mutex isAvailableMutex;

    GLenum usageToGlEnum(VertexBuffer::Usage usage)
    {
        switch (usage)
        {
            case VertexBuffer::Static:  return GLEXT_GL_STATIC_DRAW;  break;
            case VertexBuffer::Dynamic: return GLEXT_GL_DYNAMIC_DRAW; break;
            default:                    return GLEXT_GL_STREAM_DRAW;  break;
        }
    }
}

void VertexBuffer::draw(RenderTarget& target, RenderStates states) const
{
    if (buffer_ && size_)
        target.draw(*this, 0, size_, states);
}

VertexBuffer::VertexBuffer()
{
    buffer_ = 0;
    size_ = 0;
    primitiveType_ = PrimitiveType::Points;
    usage_ = Usage::Stream;
}

VertexBuffer::VertexBuffer(PrimitiveType type)
{
    buffer_ = 0;
    size_ = 0;
    primitiveType_ = type;
    usage_ = Usage::Stream;
}

VertexBuffer::VertexBuffer(VertexBuffer::Usage usage)
{
    buffer_ = 0;
    size_ = 0;
    primitiveType_ = PrimitiveType::Points;
    usage_ = usage;
}

VertexBuffer::VertexBuffer(PrimitiveType type, VertexBuffer::Usage usage)
{
    buffer_ = 0;
    size_ = 0;
    primitiveType_ = type;
    usage_ = usage;
}

VertexBuffer::VertexBuffer(const VertexBuffer& other)
{
    buffer_ = 0;
    size_ = 0;
    primitiveType_ = other.primitiveType_;
    usage_ = other.usage_;

    if (other.buffer_ && other.size_)
    {
        if (!create(other.size_))
        {
            cout << "Could not create vertex buffer for copying." << endl;
            return;
        }

        if (!update(other))
            cout << "Could not copy vertex buffer." << endl;
    }
}

VertexBuffer& VertexBuffer::operator = (const VertexBuffer& other)
{
    VertexBuffer temp(other);
    swapWith(temp);
    return *this;
}

VertexBuffer::~VertexBuffer()
{
    if (buffer_ != 0)
    {
        TransientContextLock contextLock;
        glCheck(GLEXT_glDeleteBuffers(1, &buffer_));
    }
}

bool VertexBuffer::create(size_t vertexCount)
{
    if (!isAvailable())
        return false;

    TransientContextLock contextLock;

    if (!buffer_)
        glCheck(GLEXT_glGenBuffers(1, &buffer_));

    if (!buffer_)
    {
        cout << "Could not create vertex buffer, generation failed" << endl;
        return false;
    }

    glCheck(GLEXT_glBindBuffer(GLEXT_GL_ARRAY_BUFFER, buffer_));
    glCheck(GLEXT_glBufferData(GLEXT_GL_ARRAY_BUFFER, sizeof(Vertex2) * vertexCount, 0, usageToGlEnum(usage_)));
    glCheck(GLEXT_glBindBuffer(GLEXT_GL_ARRAY_BUFFER, 0));

    size_ = vertexCount;

    return true;
}

size_t VertexBuffer::getVertexCount() const
{
    return size_;
}

bool VertexBuffer::update(const Vertex2* vertices)
{
    return update(vertices, size_, 0);
}

bool VertexBuffer::update(const Vertex2* vertices, size_t vertexCount, u32 offset)
{
    // Sanity checks.
    if (!buffer_)
        return false;

    if (!vertices)
        return false;

    if (offset && (offset + vertexCount > size_))
        return false;

    TransientContextLock contextLock;

    glCheck(GLEXT_glBindBuffer(GLEXT_GL_ARRAY_BUFFER, buffer_));

    // Check if we need to resize or orphan the buffer.
    if (vertexCount >= size_)
    {
        glCheck(GLEXT_glBufferData(GLEXT_GL_ARRAY_BUFFER, sizeof(Vertex2) * vertexCount, 0, usageToGlEnum(usage_)));
        size_ = vertexCount;
    }

    glCheck(GLEXT_glBufferSubData(GLEXT_GL_ARRAY_BUFFER, sizeof(Vertex2) * offset, sizeof(Vertex2) * vertexCount, vertices));
    glCheck(GLEXT_glBindBuffer(GLEXT_GL_ARRAY_BUFFER, 0));

    return true;
}

bool VertexBuffer::update(const VertexBuffer& vertexBuffer)
{
    #ifdef JLIB_OPENGL_ES
        return false;
    #else

        if (!buffer_ || !vertexBuffer.buffer_)
            return false;

        TransientContextLock contextLock;

        // Make sure that extensions are initialized.
        ensureExtensionsInit();

        if (GLEXT_copy_buffer)
        {
            glCheck(GLEXT_glBindBuffer(GLEXT_GL_COPY_READ_BUFFER, vertexBuffer.buffer_));
            glCheck(GLEXT_glBindBuffer(GLEXT_GL_COPY_WRITE_BUFFER, buffer_));
            glCheck(GLEXT_glCopyBufferSubData(GLEXT_GL_COPY_READ_BUFFER, GLEXT_GL_COPY_WRITE_BUFFER, 0, 0, sizeof(Vertex2) * vertexBuffer.size_));
            glCheck(GLEXT_glBindBuffer(GLEXT_GL_COPY_WRITE_BUFFER, 0));
            glCheck(GLEXT_glBindBuffer(GLEXT_GL_COPY_READ_BUFFER, 0));

            return true;
        }

        glCheck(GLEXT_glBindBuffer(GLEXT_GL_ARRAY_BUFFER, buffer_));
        glCheck(GLEXT_glBufferData(GLEXT_GL_ARRAY_BUFFER, sizeof(Vertex2) * vertexBuffer.size_, 0, usageToGlEnum(usage_)));

        void* destination = nullptr;
        glCheck(destination = GLEXT_glMapBuffer(GLEXT_GL_ARRAY_BUFFER, GLEXT_GL_WRITE_ONLY));

        glCheck(GLEXT_glBindBuffer(GLEXT_GL_ARRAY_BUFFER, vertexBuffer.buffer_));

        void* source = nullptr;
        glCheck(source = GLEXT_glMapBuffer(GLEXT_GL_ARRAY_BUFFER, GLEXT_GL_READ_ONLY));

        memcpy(destination, source, sizeof(Vertex2) * vertexBuffer.size_);

        GLboolean sourceResult = GL_FALSE;
        glCheck(sourceResult = GLEXT_glUnmapBuffer(GLEXT_GL_ARRAY_BUFFER));

        glCheck(GLEXT_glBindBuffer(GLEXT_GL_ARRAY_BUFFER, buffer_));

        GLboolean destinationResult = GL_FALSE;
        glCheck(destinationResult = GLEXT_glUnmapBuffer(GLEXT_GL_ARRAY_BUFFER));

        glCheck(GLEXT_glBindBuffer(GLEXT_GL_ARRAY_BUFFER, 0));

        if ((sourceResult == GL_FALSE) || (destinationResult == GL_FALSE))
            return false;

        return true;

    #endif // SFML_OPENGL_ES
}

void VertexBuffer::swapWith(VertexBuffer& other)
{
    swap(size_,          other.size_);
    swap(buffer_,        other.buffer_);
    swap(primitiveType_, other.primitiveType_);
    swap(usage_,         other.usage_);
}

u32 VertexBuffer::getNativeHandle() const
{
    return buffer_;
}

PrimitiveType VertexBuffer::getPrimitiveType() const
{
    return primitiveType_;
}

void VertexBuffer::setPrimitiveType(PrimitiveType type)
{
    primitiveType_ = type;
}

VertexBuffer::Usage VertexBuffer::getUsage() const
{
    return usage_;
}

void VertexBuffer::setUsage(VertexBuffer::Usage usage)
{
    usage_ = usage;
}

void VertexBuffer::bind(const VertexBuffer* vertexBuffer)
{
    if (!isAvailable())
        return;

    TransientContextLock lock;

    glCheck(GLEXT_glBindBuffer(GLEXT_GL_ARRAY_BUFFER, vertexBuffer ? vertexBuffer->buffer_ : 0));
}

bool VertexBuffer::isAvailable()
{
    Lock lock(isAvailableMutex);

    static bool checked = false;
    static bool available = false;

    if (!checked)
    {
        checked = true;
        TransientContextLock contextLock;

        // Make sure that extensions are initialized.
        ensureExtensionsInit();

        available = GLEXT_vertex_buffer_object;
    }

    return available;
}