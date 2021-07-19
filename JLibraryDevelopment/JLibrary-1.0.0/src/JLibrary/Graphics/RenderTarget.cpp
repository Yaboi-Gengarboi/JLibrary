// JLibraryDevelopment
// RenderTarget.cpp
// Created on 2021-07-12 by Justyn Durnford
// Last modified on 2021-07-16 by Justyn Durnford
// Source file for the RenderTarget class.

#ifndef NOMINMAX
    #define NOMINMAX
#endif // NOMINMAX

#include <JLibrary/Graphics/Context.hpp>
#include <JLibrary/Graphics/Drawable.hpp>
#include <JLibrary/Graphics/RenderTarget.hpp>
#include <JLibrary/Graphics/Shader.hpp>
#include <JLibrary/Graphics/Texture.hpp>
#include <JLibrary/Graphics/VertexArray.hpp>
#include <JLibrary/Multithread/Lock.hpp>
#include <JLibrary/Multithread/Mutex.hpp>
using namespace jlib;

#include <algorithm>
using std::min;
using std::max;

#include <cassert>

#include <iostream>
using std::cout;
using std::endl;

#include <map>
using std::map;

// GL_QUADS is unavailable on OpenGL ES, thus we need to define GL_QUADS ourselves.
#ifndef GL_QUADS
	#define GL_QUADS 0
#endif // GL_QUADS

namespace
{
    // Mutex to protect ID generation and our context-RenderTarget-map.
    Mutex mutex;

    // Unique identifier, used for identifying RenderTargets when
    // tracking the currently active RenderTarget within a given context.
    u64 getUniqueId()
    {
        Lock lock(mutex);
        static u64 id = 1; // start at 1, zero is "no RenderTarget".
        return id++;
    }

    // Map to help us detect whether a different RenderTarge.t
    // has been activated within a single context
    typedef map<u64, u64> ContextRenderTargetMap;
    ContextRenderTargetMap contextRenderTargetMap;

    // Check if a RenderTarget with the given ID is active in the current context
    bool isActive(u64 id)
    {
        ContextRenderTargetMap::iterator iter = contextRenderTargetMap.find(Context::getActiveContextId());

        if ((iter == contextRenderTargetMap.end()) || (iter->second != id))
            return false;

        return true;
    }

    // Convert an sf::BlendMode::Factor constant to the corresponding OpenGL constant.
    u32 factorToGlConstant(BlendMode::Factor blendFactor)
    {
        switch (blendFactor)
        {
            case BlendMode::Zero:             return GL_ZERO;
            case BlendMode::One:              return GL_ONE;
            case BlendMode::SrcColor:         return GL_SRC_COLOR;
            case BlendMode::OneMinusSrcColor: return GL_ONE_MINUS_SRC_COLOR;
            case BlendMode::DstColor:         return GL_DST_COLOR;
            case BlendMode::OneMinusDstColor: return GL_ONE_MINUS_DST_COLOR;
            case BlendMode::SrcAlpha:         return GL_SRC_ALPHA;
            case BlendMode::OneMinusSrcAlpha: return GL_ONE_MINUS_SRC_ALPHA;
            case BlendMode::DstAlpha:         return GL_DST_ALPHA;
            case BlendMode::OneMinusDstAlpha: return GL_ONE_MINUS_DST_ALPHA;
        }

        cout << "Invalid value for sf::BlendMode::Factor! Fallback to sf::BlendMode::Zero." << endl;
        assert(false);
        return GL_ZERO;
    }

    // Convert an sf::BlendMode::BlendEquation constant to the corresponding OpenGL constant.
    u32 equationToGlConstant(BlendMode::Equation blendEquation)
    {
        switch (blendEquation)
        {
            case BlendMode::Add:
                return GLEXT_GL_FUNC_ADD;
            case BlendMode::Subtract:
                if (GLEXT_blend_subtract)
                    return GLEXT_GL_FUNC_SUBTRACT;
                break;
            case BlendMode::ReverseSubtract:
                if (GLEXT_blend_subtract)
                    return GLEXT_GL_FUNC_REVERSE_SUBTRACT;
                break;
            case BlendMode::Min:
                if (GLEXT_blend_minmax)
                    return GLEXT_GL_MIN;
                break;
            case BlendMode::Max:
                if (GLEXT_blend_minmax)
                    return GLEXT_GL_MAX;
                break;
        }

        static bool warned = false;
        if (!warned)
        {
            cout << "OpenGL extension EXT_blend_minmax or EXT_blend_subtract unavailable" << endl;
            cout << "Some blending equations will fallback to sf::BlendMode::Add" << endl;
            cout << "Ensure that hardware acceleration is enabled if available" << endl;

            warned = true;
        }

        return GLEXT_GL_FUNC_ADD;
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

void RenderTarget::applyCurrentView()
{
    // Set the viewport.
    IntRect viewport = getViewport(view_);
    i32 top = getHeight() - (viewport.vertex.x + viewport.height);
    glCheck(glViewport(viewport.vertex.x, top, viewport.width, viewport.height));

    // Set the projection matrix.
    glCheck(glMatrixMode(GL_PROJECTION));
    glCheck(glLoadMatrixf(view_.getTransformation().matrix().begin()));

    // Go back to model-view mode.
    glCheck(glMatrixMode(GL_MODELVIEW));

    cache_.flags[2] = false;
}

void RenderTarget::applyBlendMode(const BlendMode& mode)
{
    // Apply the blend mode, falling back to the non-separate versions if necessary.
    if (GLEXT_blend_func_separate)
    {
        glCheck(GLEXT_glBlendFuncSeparate(
            factorToGlConstant(mode.colorSrcFactor), factorToGlConstant(mode.colorDstFactor),
            factorToGlConstant(mode.alphaSrcFactor), factorToGlConstant(mode.alphaDstFactor)));
    }
    else
    {
        glCheck(glBlendFunc(
            factorToGlConstant(mode.colorSrcFactor),
            factorToGlConstant(mode.colorDstFactor)));
    }

    if (GLEXT_blend_minmax || GLEXT_blend_subtract)
    {
        if (GLEXT_blend_equation_separate)
        {
            glCheck(GLEXT_glBlendEquationSeparate(
                equationToGlConstant(mode.colorEquation),
                equationToGlConstant(mode.alphaEquation)));
        }
        else
        {
            glCheck(GLEXT_glBlendEquation(equationToGlConstant(mode.colorEquation)));
        }
    }
    else if ((mode.colorEquation != BlendMode::Add) || (mode.alphaEquation != BlendMode::Add))
    {
        static bool warned = false;

        if (!warned)
        {
            #ifdef JLIB_OPENGL_ES
                cout << "OpenGL ES extension OES_blend_subtract unavailable" << endl;
            #else
                cout << "OpenGL extension EXT_blend_minmax and EXT_blend_subtract unavailable" << endl;
            #endif
            cout << "Selecting a blend equation not possible" << endl;
            cout << "Ensure that hardware acceleration is enabled if available" << endl;

            warned = true;
        }
    }

    cache_.lastBlendMode = mode;
}

void RenderTarget::applyTransform(const Transformation& transform)
{
    // No need to call glMatrixMode(GL_MODELVIEW), it is always the
    // current mode (for optimization purpose, since it's the most used)
    if (transform == Transformation::Identity)
        glCheck(glLoadIdentity());
    else
        glCheck(glLoadMatrixf(transform.matrix().begin()));
}

void RenderTarget::applyTexture(const Texture* texture)
{
    Texture::bind(texture, Texture::Pixels);

    cache_.lastTextureID = texture ? texture->cacheID_ : 0;
}

void RenderTarget::applyShader(const Shader* shader)
{
    Shader::bind(shader);
}

void RenderTarget::setupDraw(bool useVertexCache, const RenderStates& states)
{
    // Enable or disable sRGB encoding.
    // This is needed for drivers that do not check the format 
    // of the surface drawn to before applying sRGB conversion.
    if (!cache_.flags[0])
    {
        if (isSRGB())
            glCheck(glEnable(GL_FRAMEBUFFER_SRGB));
        else
            glCheck(glDisable(GL_FRAMEBUFFER_SRGB));
    }

    // First set the persistent OpenGL states if it's the very first call.
    if (!cache_.flags[1])
        resetGLStates();

    if (useVertexCache)
    {
        // Since vertices are transformed, we must use an identity transform to render them.
        if (!cache_.flags[0] || !cache_.flags[4])
            glCheck(glLoadIdentity());
    }
    else
        applyTransform(states.transform);

    // Apply the view.
    if (!cache_.flags[0] || cache_.flags[2])
        applyCurrentView();

    // Apply the blend mode.
    if (!cache_.flags[0] || (states.blendMode != cache_.lastBlendMode))
        applyBlendMode(states.blendMode);

    // Apply the texture.
    if (!cache_.flags[0] || (states.texture && states.texture->flags_[4]))
    {
        // If the texture is an FBO attachment, always rebind it
        // in order to inform the OpenGL driver that we want changes
        // made to it in other contexts to be visible here as well.
        // This saves us from having to call glFlush() in
        // RenderTextureImplFBO which can be quite costly.
        // See: https://www.khronos.org/opengl/wiki/Memory_Model
        applyTexture(states.texture);
    }
    else
    {
        u64 textureId = states.texture ? states.texture->cacheID_ : 0;
        if (textureId != cache_.lastTextureID)
            applyTexture(states.texture);
    }

    // Apply the shader.
    if (states.shader)
        applyShader(states.shader);
}

void RenderTarget::drawPrimitives(PrimitiveType type, size_t firstVertex, size_t vertexCount)
{
    // Find the OpenGL primitive type.
    static const GLenum modes[] = { GL_POINTS, GL_LINES, GL_LINE_STRIP, GL_TRIANGLES,
                                   GL_TRIANGLE_STRIP, GL_TRIANGLE_FAN, GL_QUADS };
    GLenum mode = modes[type];

    // Draw the primitives.
    glCheck(glDrawArrays(mode, static_cast<GLint>(firstVertex), static_cast<GLsizei>(vertexCount)));
}

void RenderTarget::cleanupDraw(const RenderStates& states)
{
    // Unbind the shader, if any.
    if (states.shader)
        applyShader(nullptr);

    // If the texture we used to draw belonged to a RenderTexture, then forcibly unbind that texture.
    // This prevents a bug where some drivers do not clear RenderTextures properly.
    if (states.texture && states.texture->flags_[4])
        applyTexture(nullptr);

    // Re-enable the cache at the end of the draw if it was disabled.
    cache_.flags[0] = true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

RenderTarget::RenderTarget() 
    : defaultView_(), view_(), cache_()
{
    id_ = 0;
    cache_.flags[1] = false;
}

void RenderTarget::initialize()
{
    // Setup the default and current views.
    defaultView_.reset(FloatRect(0, 0, static_cast<float>(getWidth()), static_cast<float>(getHeight())));
    view_ = defaultView_;

    // Set GL states only on first draw, so that we don't pollute user's states.
    cache_.flags[1] = false;

    // Generate a unique ID for this RenderTarget to track
    // whether it is active within a specific context.
    id_ = getUniqueId();
}

RenderTarget::~RenderTarget() {}

void RenderTarget::clear(const Color& color)
{
    if (isActive(id_) || setActive(true))
    {
        // Unbind texture to fix RenderTexture preventing clear.
        applyTexture(NULL);

        glCheck(glClearColor(color[0] / 255.f, color[1] / 255.f, color[2] / 255.f, color[3] / 255.f));
        glCheck(glClear(GL_COLOR_BUFFER_BIT));
    }
}

void RenderTarget::setView(const View& view)
{
    view_ = view;
    cache_.flags[2] = true;
}

const View& RenderTarget::getView() const
{
    return view_;
}

const View& RenderTarget::getDefaultView() const
{
    return defaultView_;
}

IntRect RenderTarget::getViewport(const View& view) const
{
    float w = static_cast<float>(getWidth());
    float h = static_cast<float>(getHeight());
    const FloatRect& viewport = view.getViewport();

    return IntRect(static_cast<int>(0.5f + w * viewport.vertex.x),
        static_cast<int>(0.5f + h * viewport.vertex.y),
        static_cast<int>(0.5f + w * viewport.width),
        static_cast<int>(0.5f + h * viewport.height));
}

Point2f RenderTarget::mapPixelToCoords(const Point2i& point) const
{
    return mapPixelToCoords(point, getView());
}

Point2f RenderTarget::mapPixelToCoords(const Point2i& point, const View& view) const
{
    // First, convert from viewport coordinates to homogeneous coordinates.
    Point2f normalized;
    IntRect viewport = getViewport(view);
    normalized.x = -1.f + 2.f * (point.x - viewport.vertex.x) / viewport.width;
    normalized.y = 1.f - 2.f * (point.y - viewport.vertex.y) / viewport.height;

    // Then transform by the inverse of the view matrix.
    return view.getInverseTransformation().transformPoint(normalized);
}

Point2i RenderTarget::mapCoordsToPixel(const Point2f& point) const
{
    return mapCoordsToPixel(point, getView());
}

Point2i RenderTarget::mapCoordsToPixel(const Point2f& point, const View& view) const
{
    // First, transform the point by the view matrix.
    Point2f normalized = view.getTransformation().transformPoint(point);

    // Then convert to viewport coordinates.
    Point2i pixel;
    IntRect viewport = getViewport(view);
    pixel.x = static_cast<int>((normalized.x + 1.f) / 2.f * viewport.width + viewport.vertex.x);
    pixel.y = static_cast<int>((-normalized.y + 1.f) / 2.f * viewport.height + viewport.vertex.y);

    return pixel;
}

void RenderTarget::draw(const Drawable& drawable, const RenderStates& states)
{
    drawable.draw(*this, states);
}

void RenderTarget::draw(const Vertex2* vertices, size_t vertexCount, 
                        PrimitiveType type, const RenderStates& states)
{
    // Nothing to draw?
    if (!vertices || (vertexCount == 0))
        return;

    // GL_QUADS is unavailable on OpenGL ES.
    #ifdef JLIB_OPENGL_ES
        if (type == Quads)
        {
            cout << "jlib::Quads primitive type is not supported on OpenGL ES platforms, drawing skipped" << endl;
            return;
        }
    #endif

    if (isActive(id_) || setActive(true))
    {
        // Check if the vertex count is low enough so that we can pre-transform them.
        bool useVertexCache = (vertexCount <= StatesCache::VertexCacheSize);

        if (useVertexCache)
        {
            // Pre-transform the vertices and store them into the vertex cache.
            for (size_t i = 0; i < vertexCount; ++i)
            {
                Vertex2& vertex = cache_.vertexCache[i];
                vertex.position = states.transform * vertices[i].position;
                vertex.color = vertices[i].color;
                vertex.textureCoordinates = vertices[i].textureCoordinates;
            }
        }

        setupDraw(useVertexCache, states);

        // Check if texture coordinates array is needed, and update client state accordingly.
        bool enableTexCoordsArray = (states.texture || states.shader);
        if (!cache_.flags[0] || (enableTexCoordsArray != cache_.flags[3]))
        {
            if (enableTexCoordsArray)
                glCheck(glEnableClientState(GL_TEXTURE_COORD_ARRAY));
            else
                glCheck(glDisableClientState(GL_TEXTURE_COORD_ARRAY));
        }

        // If we switch between non-cache and cache mode or enable texture
        // coordinates we need to set up the pointers to the vertices' components.
        if (!cache_.flags[0] || !useVertexCache || !cache_.flags[4])
        {
            const char* data = reinterpret_cast<const char*>(vertices);

            // If we pre-transform the vertices, we must use our internal vertex cache.
            if (useVertexCache)
                data = reinterpret_cast<const char*>(cache_.vertexCache.data());

            glCheck(glVertexPointer(2, GL_FLOAT, sizeof(Vertex2), data + 0));
            glCheck(glColorPointer(4, GL_UNSIGNED_BYTE, sizeof(Vertex2), data + 8));
            if (enableTexCoordsArray)
                glCheck(glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex2), data + 12));
        }
        else if (enableTexCoordsArray && !cache_.flags[3])
        {
            // If we enter this block, we are already using our internal vertex cache.
            const char* data = reinterpret_cast<const char*>(cache_.vertexCache.data());

            glCheck(glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex2), data + 12));
        }

        drawPrimitives(type, 0, vertexCount);
        cleanupDraw(states);

        // Update the cache.
        cache_.flags[3] = enableTexCoordsArray;
        cache_.flags[4] = useVertexCache;
    }
}

void RenderTarget::draw(const VertexBuffer& vertexBuffer, const RenderStates& states)
{
    draw(vertexBuffer, 0, vertexBuffer.getVertexCount(), states);
}

void RenderTarget::draw(const VertexBuffer& vertexBuffer, size_t firstVertex,
                        size_t vertexCount, const RenderStates& states)
{
    // VertexBuffer not supported?
    if (!VertexBuffer::isAvailable())
    {
        cout << "jlib::VertexBuffer is not available, drawing skipped" << endl;
        return;
    }

    // Sanity check.
    if (firstVertex > vertexBuffer.getVertexCount())
        return;

    // Clamp vertexCount to something that makes sense.
    vertexCount = min(vertexCount, vertexBuffer.getVertexCount() - firstVertex);

    // Nothing to draw?
    if (!vertexCount || !vertexBuffer.getNativeHandle())
        return;

    // GL_QUADS is unavailable on OpenGL ES.
    #ifdef JLIB_OPENGL_ES
    if (vertexBuffer.getPrimitiveType() == Quads)
    {
        cout << "sf::Quads primitive type is not supported on OpenGL ES platforms, drawing skipped" << endl;
        return;
    }
    #endif

    if (isActive(id_) || setActive(true))
    {
        setupDraw(false, states);

        // Bind vertex buffer.
        VertexBuffer::bind(&vertexBuffer);

        // Always enable texture coordinates.
        if (!cache_.flags[0] || !cache_.flags[3])
            glCheck(glEnableClientState(GL_TEXTURE_COORD_ARRAY));

        glCheck(glVertexPointer(2, GL_FLOAT, sizeof(Vertex2), reinterpret_cast<const void*>(0)));
        glCheck(glColorPointer(4, GL_UNSIGNED_BYTE, sizeof(Vertex2), reinterpret_cast<const void*>(8)));
        glCheck(glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex2), reinterpret_cast<const void*>(12)));

        drawPrimitives(vertexBuffer.getPrimitiveType(), firstVertex, vertexCount);

        // Unbind vertex buffer.
        VertexBuffer::bind(nullptr);

        cleanupDraw(states);

        // Update the cache.
        cache_.flags[3] = true;
        cache_.flags[4] = false;
    }
}

bool RenderTarget::isSRGB() const
{
    // By default sRGB encoding is not enabled for an arbitrary RenderTarget.
    return false;
}

bool RenderTarget::setActive(bool active)
{
    // Mark this RenderTarget as active or no longer active in the tracking map.
    {
        Lock lock(mutex);

        u64 contextId = Context::getActiveContextId();

        ContextRenderTargetMap::iterator iter = contextRenderTargetMap.find(contextId);

        if (active)
        {
            if (iter == contextRenderTargetMap.end())
            {
                contextRenderTargetMap[contextId] = id_;

                cache_.flags[0] = false;
                cache_.flags[1] = false;
            }
            else if (iter->second != id_)
            {
                iter->second = id_;
                cache_.flags[0] = false;
            }
        }
        else
        {
            if (iter != contextRenderTargetMap.end())
                contextRenderTargetMap.erase(iter);

            cache_.flags[0] = false;
        }
    }

    return true;
}


////////////////////////////////////////////////////////////
void RenderTarget::pushGLStates()
{
    if (isActive(id_) || setActive(true))
    {
        #ifdef _DEBUG

            // Make sure that the user didn't leave an unchecked OpenGL error.
            GLenum error = glGetError();
            if (error != GL_NO_ERROR)
            {
                cout << "OpenGL error (" << error << ") detected in user code, "
                     << "you should check for errors with glGetError()" << endl;
            }
        
        #endif

        #ifndef JLIB_OPENGL_ES

            glCheck(glPushClientAttrib(GL_CLIENT_ALL_ATTRIB_BITS));
            glCheck(glPushAttrib(GL_ALL_ATTRIB_BITS));

        #endif

        glCheck(glMatrixMode(GL_MODELVIEW));
        glCheck(glPushMatrix());
        glCheck(glMatrixMode(GL_PROJECTION));
        glCheck(glPushMatrix());
        glCheck(glMatrixMode(GL_TEXTURE));
        glCheck(glPushMatrix());
    }

    resetGLStates();
}


////////////////////////////////////////////////////////////
void RenderTarget::popGLStates()
{
    if (isActive(id_) || setActive(true))
    {
        glCheck(glMatrixMode(GL_PROJECTION));
        glCheck(glPopMatrix());
        glCheck(glMatrixMode(GL_MODELVIEW));
        glCheck(glPopMatrix());
        glCheck(glMatrixMode(GL_TEXTURE));
        glCheck(glPopMatrix());

        #ifndef JLIB_OPENGL_ES

            glCheck(glPopClientAttrib());
            glCheck(glPopAttrib());

        #endif
    }
}

void RenderTarget::resetGLStates()
{
    // Check here to make sure a context change does not happen after activate(true).
    bool shaderAvailable = Shader::isAvailable();
    bool vertexBufferAvailable = VertexBuffer::isAvailable();

    if (isActive(id_) || setActive(true))
    {
        // Make sure that extensions are initialized.
        ensureExtensionsInit();

        // Make sure that the texture unit which is active is the number 0
        if (GLEXT_multitexture)
        {
            glCheck(GLEXT_glClientActiveTexture(GLEXT_GL_TEXTURE0));
            glCheck(GLEXT_glActiveTexture(GLEXT_GL_TEXTURE0));
        }

        // Define the default OpenGL states.
        glCheck(glDisable(GL_CULL_FACE));
        glCheck(glDisable(GL_LIGHTING));
        glCheck(glDisable(GL_DEPTH_TEST));
        glCheck(glDisable(GL_ALPHA_TEST));
        glCheck(glEnable(GL_TEXTURE_2D));
        glCheck(glEnable(GL_BLEND));
        glCheck(glMatrixMode(GL_MODELVIEW));
        glCheck(glLoadIdentity());
        glCheck(glEnableClientState(GL_VERTEX_ARRAY));
        glCheck(glEnableClientState(GL_COLOR_ARRAY));
        glCheck(glEnableClientState(GL_TEXTURE_COORD_ARRAY));
        cache_.flags[1] = true;

        // Apply the default JLIB states.
        applyBlendMode(BlendAlpha);
        applyTexture(nullptr);
        if (shaderAvailable)
            applyShader(nullptr);

        if (vertexBufferAvailable)
            glCheck(VertexBuffer::bind(nullptr));

        cache_.flags[3] = true;
        cache_.flags[4] = false;

        // Set the default view.
        setView(getView());

        cache_.flags[0] = true;
    }
}