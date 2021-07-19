// JLibraryDevelopment
// RenderTextureImplFBO.cpp
// Created on 2021-07-17 by Justyn Durnford
// Last modified on 2021-07-18 by Justyn Durnford
// Source file for the RenderTextureImplFBO class.

#include <JLibrary/Graphics/RenderTextureImplFBO.hpp>
#include <JLibrary/Multithread/Lock.hpp>
#include <JLibrary/Multithread/Mutex.hpp>
using namespace jlib;

#include <iostream>
using std::cout;
using std::endl;

#include <map>
using std::map;

#include <set>
using std::set;

#include <utility>
using std::pair;
using std::make_pair;

namespace
{
    // Set to track all active FBO mappings.
    // This is used to free active FBOs while their owning
    // RenderTextureImplFBO is still alive.
    set<map<u64, u32>*> frameBuffers;

    // Set to track all stale FBOs.
    // This is used to free stale FBOs after their owning
    // RenderTextureImplFBO has already been destroyed.
    // An FBO cannot be destroyed until it's containing context
    // becomes active, so the destruction of the RenderTextureImplFBO
    // has to be decoupled from the destruction of the FBOs themselves.
    set<pair<u64, u32>> staleFrameBuffers;

    // Mutex to protect both active and stale frame buffer sets.
    Mutex mutex;

    // This function is called either when a RenderTextureImplFBO is
    // destroyed or via contextDestroyCallback when context destruction
    // might trigger deletion of its contained stale FBOs.
    void destroyStaleFBOs()
    {
        u64 contextId = Context::getActiveContextId();

        for (set<pair<u64, u32>>::iterator iter = staleFrameBuffers.begin(); iter != staleFrameBuffers.end();)
        {
            if (iter->first == contextId)
            {
                GLuint frameBuffer = static_cast<GLuint>(iter->second);
                glCheck(GLEXT_glDeleteFramebuffers(1, &frameBuffer));

                staleFrameBuffers.erase(iter++);
            }
            else
                ++iter;
        }
    }

    // Callback that is called every time a context is destroyed.
    void contextDestroyCallback(void* arg)
    {
        Lock lock(mutex);

        u64 contextID = Context::getActiveContextId();

        // Destroy active frame buffer objects.
        for (set<map<u64, u32>*>::iterator frameBuffersIter = frameBuffers.begin(); frameBuffersIter != frameBuffers.end(); ++frameBuffersIter)
        {
            for (map<u64, u32>::iterator iter = (*frameBuffersIter)->begin(); iter != (*frameBuffersIter)->end(); ++iter)
            {
                if (iter->first == contextID)
                {
                    GLuint frameBuffer = static_cast<GLuint>(iter->second);
                    glCheck(GLEXT_glDeleteFramebuffers(1, &frameBuffer));

                    // Erase the entry from the RenderTextureImplFBO's map.
                    (*frameBuffersIter)->erase(iter);

                    break;
                }
            }
        }

        // Destroy stale frame buffer objects.
        destroyStaleFBOs();
    }
}

bool RenderTextureImplFBO::create(u32 width, u32 height, u32 textureID, const ContextSettings& settings)
{
    // Store the dimensions.
    width_ = width;
    height_ = height;

    {
        TransientContextLock lock;

        // Make sure that extensions are initialized.
        ensureExtensionsInit();

        if (settings.antialiasingLevel && !(GLEXT_framebuffer_multisample && GLEXT_framebuffer_blit))
            return false;

        if (settings.stencilBits && !GLEXT_packed_depth_stencil)
            return false;

        #ifndef JLIB_OPENGL_ES

            // Check if the requested anti-aliasing level is supported
            if (settings.antialiasingLevel)
            {
                GLint samples = 0;
                glCheck(glGetIntegerv(GLEXT_GL_MAX_SAMPLES, &samples));

                if (settings.antialiasingLevel > static_cast<unsigned int>(samples))
                {
                    cout << "Impossible to create render texture (unsupported anti-aliasing level).";
                    cout << " Requested: " << settings.antialiasingLevel << " Maximum supported: " << samples << endl;
                    return false;
                }
            }

        #endif


        if (!settings.antialiasingLevel)
        {
            // Create the depth/stencil buffer if requested.
            if (settings.stencilBits)
            {

                #ifndef JLIB_OPENGL_ES

                    GLuint depthStencil = 0;
                    glCheck(GLEXT_glGenRenderbuffers(1, &depthStencil));
                    depthStencilBuffer_ = static_cast<u32>(depthStencil);
                    if (!depthStencilBuffer_)
                    {
                        cout << "Impossible to create render texture (failed to create the attached depth/stencil buffer)." << endl;
                        return false;
                    }
                    glCheck(GLEXT_glBindRenderbuffer(GLEXT_GL_RENDERBUFFER, depthStencilBuffer_));
                    glCheck(GLEXT_glRenderbufferStorage(GLEXT_GL_RENDERBUFFER, GLEXT_GL_DEPTH24_STENCIL8, width, height));

                #else

                    cout << "Impossible to create render texture (failed to create the attached depth/stencil buffer)." << endl;
                    return false;

                #endif // JLIB_OPENGL_ES

                stencil_ = true;

            }
            else if (settings.depthBits)
            {
                GLuint depthStencil = 0;
                glCheck(GLEXT_glGenRenderbuffers(1, &depthStencil));
                depthStencilBuffer_ = static_cast<u32>(depthStencil);
                if (!depthStencilBuffer_)
                {
                    cout << "Impossible to create render texture (failed to create the attached depth buffer)." << endl;
                    return false;
                }
                glCheck(GLEXT_glBindRenderbuffer(GLEXT_GL_RENDERBUFFER, depthStencilBuffer_));
                glCheck(GLEXT_glRenderbufferStorage(GLEXT_GL_RENDERBUFFER, GLEXT_GL_DEPTH_COMPONENT, width, height));
            }
        }
        else
        {

            #ifndef JLIB_OPENGL_ES

                // Create the multisample color buffer.
                GLuint color = 0;
                glCheck(GLEXT_glGenRenderbuffers(1, &color));
                colorBuffer_ = static_cast<u32>(color);
                if (!colorBuffer_)
                {
                    cout << "Impossible to create render texture (failed to create the attached multisample color buffer)." << endl;
                    return false;
                }
                glCheck(GLEXT_glBindRenderbuffer(GLEXT_GL_RENDERBUFFER, colorBuffer_));
                glCheck(GLEXT_glRenderbufferStorageMultisample(GLEXT_GL_RENDERBUFFER, settings.antialiasingLevel, GL_RGBA, width, height));

                // Create the multisample depth/stencil buffer if requested
                if (settings.stencilBits)
                {
                    GLuint depthStencil = 0;
                    glCheck(GLEXT_glGenRenderbuffers(1, &depthStencil));
                    depthStencilBuffer_ = static_cast<u32>(depthStencil);
                    if (!depthStencilBuffer_)
                    {
                        cout << "Impossible to create render texture (failed to create the attached multisample depth/stencil buffer)." << endl;
                        return false;
                    }
                    glCheck(GLEXT_glBindRenderbuffer(GLEXT_GL_RENDERBUFFER, depthStencilBuffer_));
                    glCheck(GLEXT_glRenderbufferStorageMultisample(GLEXT_GL_RENDERBUFFER, settings.antialiasingLevel, GLEXT_GL_DEPTH24_STENCIL8, width, height));

                    stencil_ = true;
                }
                else if (settings.depthBits)
                {
                    GLuint depthStencil = 0;
                    glCheck(GLEXT_glGenRenderbuffers(1, &depthStencil));
                    depthStencilBuffer_ = static_cast<u32>(depthStencil);
                    if (!depthStencilBuffer_)
                    {
                        cout << "Impossible to create render texture (failed to create the attached multisample depth buffer)." << endl;
                        return false;
                    }
                    glCheck(GLEXT_glBindRenderbuffer(GLEXT_GL_RENDERBUFFER, depthStencilBuffer_));
                    glCheck(GLEXT_glRenderbufferStorageMultisample(GLEXT_GL_RENDERBUFFER, settings.antialiasingLevel, GLEXT_GL_DEPTH_COMPONENT, width, height));
                }

            #else

                cout << "Impossible to create render texture (failed to create the multisample render buffers)" << endl;
                return false;

            #endif // JLIB_OPENGL_ES

            multisample_ = true;
        }
    }

    // Save our texture ID in order to be able to attach it to an FBO at any time.
    textureID_ = textureID;

    // We can't create an FBO now if there is no active context.
    if (!Context::getActiveContextId())
        return true;

    #ifndef JLIB_OPENGL_ES

        // Save the current bindings so we can restore them after we are done.
        GLint readFramebuffer = 0;
        GLint drawFramebuffer = 0;

        glCheck(glGetIntegerv(GLEXT_GL_READ_FRAMEBUFFER_BINDING, &readFramebuffer));
        glCheck(glGetIntegerv(GLEXT_GL_DRAW_FRAMEBUFFER_BINDING, &drawFramebuffer));

        if (createFrameBuffer())
        {
            // Restore previously bound framebuffers.
            glCheck(GLEXT_glBindFramebuffer(GLEXT_GL_READ_FRAMEBUFFER, readFramebuffer));
            glCheck(GLEXT_glBindFramebuffer(GLEXT_GL_DRAW_FRAMEBUFFER, drawFramebuffer));

            return true;
        }

    #else

        // Save the current binding so we can restore them after we are done.
        GLint frameBuffer = 0;

        glCheck(glGetIntegerv(GLEXT_GL_FRAMEBUFFER_BINDING, &frameBuffer));

        if (createFrameBuffer())
        {
            // Restore previously bound framebuffer.
            glCheck(GLEXT_glBindFramebuffer(GLEXT_GL_FRAMEBUFFER, frameBuffer));

            return true;
        }

    #endif

    return false;
}

bool RenderTextureImplFBO::createFrameBuffer()
{
    // Create the framebuffer object.
    GLuint frameBuffer = 0;
    glCheck(GLEXT_glGenFramebuffers(1, &frameBuffer));

    if (!frameBuffer)
    {
        cout << "Impossible to create render texture (failed to create the frame buffer object)." << endl;
        return false;
    }
    glCheck(GLEXT_glBindFramebuffer(GLEXT_GL_FRAMEBUFFER, frameBuffer));

    // Link the depth/stencil renderbuffer to the frame buffer.
    if (!multisample_ && depthStencilBuffer_)
    {
        glCheck(GLEXT_glFramebufferRenderbuffer(GLEXT_GL_FRAMEBUFFER, GLEXT_GL_DEPTH_ATTACHMENT, GLEXT_GL_RENDERBUFFER, depthStencilBuffer_));

        #ifndef JLIB_OPENGL_ES

            if (stencil_)
                glCheck(GLEXT_glFramebufferRenderbuffer(GLEXT_GL_FRAMEBUFFER, GLEXT_GL_STENCIL_ATTACHMENT, GLEXT_GL_RENDERBUFFER, depthStencilBuffer_));

        #endif

    }

    // Link the texture to the frame buffer.
    glCheck(GLEXT_glFramebufferTexture2D(GLEXT_GL_FRAMEBUFFER, GLEXT_GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureID_, 0));

    // A final check, just to be sure...
    GLenum status;
    glCheck(status = GLEXT_glCheckFramebufferStatus(GLEXT_GL_FRAMEBUFFER));
    if (status != GLEXT_GL_FRAMEBUFFER_COMPLETE)
    {
        glCheck(GLEXT_glBindFramebuffer(GLEXT_GL_FRAMEBUFFER, 0));
        glCheck(GLEXT_glDeleteFramebuffers(1, &frameBuffer));
        cout << "Impossible to create render texture (failed to link the target texture to the frame buffer)." << endl;
        return false;
    }

    {
        Lock lock(mutex);

        // Insert the FBO into our map.
        frameBuffers_.insert(make_pair(Context::getActiveContextId(), static_cast<u32>(frameBuffer)));
    }

    #ifndef JLIB_OPENGL_ES

        if (multisample_)
        {
            // Create the multisample framebuffer object.
            GLuint multisampleFrameBuffer = 0;
            glCheck(GLEXT_glGenFramebuffers(1, &multisampleFrameBuffer));

            if (!multisampleFrameBuffer)
            {
                cout << "Impossible to create render texture (failed to create the multisample frame buffer object)" << endl;
                return false;
            }
            glCheck(GLEXT_glBindFramebuffer(GLEXT_GL_FRAMEBUFFER, multisampleFrameBuffer));

            // Link the multisample color buffer to the frame buffer.
            glCheck(GLEXT_glBindRenderbuffer(GLEXT_GL_RENDERBUFFER, colorBuffer_));
            glCheck(GLEXT_glFramebufferRenderbuffer(GLEXT_GL_FRAMEBUFFER, GLEXT_GL_COLOR_ATTACHMENT0, GLEXT_GL_RENDERBUFFER, colorBuffer_));

            // Link the depth/stencil renderbuffer to the frame buffer.
            if (depthStencilBuffer_)
            {
                glCheck(GLEXT_glFramebufferRenderbuffer(GLEXT_GL_FRAMEBUFFER, GLEXT_GL_DEPTH_ATTACHMENT, GLEXT_GL_RENDERBUFFER, depthStencilBuffer_));

                if (stencil_)
                    glCheck(GLEXT_glFramebufferRenderbuffer(GLEXT_GL_FRAMEBUFFER, GLEXT_GL_STENCIL_ATTACHMENT, GLEXT_GL_RENDERBUFFER, depthStencilBuffer_));
            }

            // A final check, just to be sure...
            glCheck(status = GLEXT_glCheckFramebufferStatus(GLEXT_GL_FRAMEBUFFER));
            if (status != GLEXT_GL_FRAMEBUFFER_COMPLETE)
            {
                glCheck(GLEXT_glBindFramebuffer(GLEXT_GL_FRAMEBUFFER, 0));
                glCheck(GLEXT_glDeleteFramebuffers(1, &multisampleFrameBuffer));
                cout << "Impossible to create render texture (failed to link the render buffers to the multisample frame buffer)." << endl;
                return false;
            }

            {
                Lock lock(mutex);

                // Insert the FBO into our map.
                multisampleFrameBuffers_.insert(make_pair(Context::getActiveContextId(), static_cast<u32>(multisampleFrameBuffer)));
            }
        }

    #endif

    return true;
}

bool RenderTextureImplFBO::activate(bool active)
{
    // Unbind the FBO if requested.
    if (!active)
    {
        glCheck(GLEXT_glBindFramebuffer(GLEXT_GL_FRAMEBUFFER, 0));
        return true;
    }

    u64 contextID = Context::getActiveContextId();

    // In the odd case we have to activate and there is no active
    // context yet, we have to create one.
    if (!contextID)
    {
        if (!context_)
            context_ = new Context;

        context_->setActive(true);

        contextID = Context::getActiveContextId();

        if (!contextID)
        {
            cout << "Impossible to activate render texture (failed to create backup context)" << endl;
            return false;
        }
    }

    // Lookup the FBO corresponding to the currently active context
    // If none is found, there is no FBO corresponding to the
    // currently active context so we will have to create a new FBO.
    {
        Lock lock(mutex);

        map<u64, u32>::iterator iter;

        if (multisample_)
        {
            iter = multisampleFrameBuffers_.find(contextID);

            if (iter != multisampleFrameBuffers_.end())
            {
                glCheck(GLEXT_glBindFramebuffer(GLEXT_GL_FRAMEBUFFER, iter->second));
                return true;
            }
        }
        else
        {
            iter = frameBuffers_.find(contextID);

            if (iter != frameBuffers_.end())
            {
                glCheck(GLEXT_glBindFramebuffer(GLEXT_GL_FRAMEBUFFER, iter->second));
                return true;
            }
        }
    }

    return createFrameBuffer();
}

void RenderTextureImplFBO::updateTexture(u32 textureID)
{
    // If multisampling is enabled, we need to resolve by blitting
    // from our FBO with multisample renderbuffer attachments
    // to our FBO to which our target texture is attached.

    #ifndef JLIB_OPENGL_ES

        // In case of multisampling, make sure both FBOs
        // are already available within the current context.
        if (multisample_ && width_ && height_ && activate(true))
        {
            u64 contextID = Context::getActiveContextId();

            Lock lock(mutex);

            map<u64, unsigned int>::iterator iter = frameBuffers_.find(contextID);
            map<u64, unsigned int>::iterator multisampleIter = multisampleFrameBuffers_.find(contextID);

            if ((iter != frameBuffers_.end()) && (multisampleIter != multisampleFrameBuffers_.end()))
            {
                // Set up the blit target (draw framebuffer) and blit (from the read framebuffer, our multisample FBO).
                glCheck(GLEXT_glBindFramebuffer(GLEXT_GL_DRAW_FRAMEBUFFER, iter->second));
                glCheck(GLEXT_glBlitFramebuffer(0, 0, width_, height_, 0, 0, width_, height_, GL_COLOR_BUFFER_BIT, GL_NEAREST));
                glCheck(GLEXT_glBindFramebuffer(GLEXT_GL_DRAW_FRAMEBUFFER, multisampleIter->second));
            }
        }

    #endif // JLIB_OPENGL_ES
}

RenderTextureImplFBO::RenderTextureImplFBO()
{
    depthStencilBuffer_ = 0;
    colorBuffer_ = 0;
    width_ = 0;
    height_ = 0;
    context_ = nullptr;
    textureID_ = 0;
    multisample_ = false;
    stencil_ = false;

    Lock lock(mutex);

    // Register the context destruction callback.
    registerContextDestroyCallback(contextDestroyCallback, 0);

    // Insert the new frame buffer mapping into the set of all active mappings.
    frameBuffers.insert(&frameBuffers_);
    frameBuffers.insert(&multisampleFrameBuffers_);
}

RenderTextureImplFBO::~RenderTextureImplFBO()
{
    TransientContextLock contextLock;
    Lock lock(mutex);

    // Remove the frame buffer mapping from the set of all active mappings.
    frameBuffers.erase(&frameBuffers_);
    frameBuffers.erase(&multisampleFrameBuffers_);

    // Destroy the color buffer.
    if (colorBuffer_)
    {
        GLuint colorBuffer = static_cast<GLuint>(colorBuffer_);
        glCheck(GLEXT_glDeleteRenderbuffers(1, &colorBuffer));
    }

    // Destroy the depth/stencil buffer.
    if (depthStencilBuffer_)
    {
        GLuint depthStencilBuffer = static_cast<GLuint>(depthStencilBuffer_);
        glCheck(GLEXT_glDeleteRenderbuffers(1, &depthStencilBuffer));
    }

    // Move all frame buffer objects to stale set.
    for (map<u64, u32>::iterator iter = frameBuffers_.begin(); iter != frameBuffers_.end(); ++iter)
        staleFrameBuffers.insert(make_pair(iter->first, iter->second));

    for (map<u64, u32>::iterator iter = multisampleFrameBuffers_.begin(); iter != multisampleFrameBuffers_.end(); ++iter)
        staleFrameBuffers.insert(make_pair(iter->first, iter->second));

    // Clean up FBOs.
    destroyStaleFBOs();

    // Delete the backup context if we had to create one.
    delete context_;
}

bool RenderTextureImplFBO::isAvailable()
{
    TransientContextLock lock;

    // Make sure that extensions are initialized.
    ensureExtensionsInit();

    return GLEXT_framebuffer_object != 0;
}

u32 RenderTextureImplFBO::getMaximumAntialiasingLevel()
{
    TransientContextLock lock;
    GLint samples = 0;

    #ifndef JLIB_OPENGL_ES
        glCheck(glGetIntegerv(GLEXT_GL_MAX_SAMPLES, &samples));
    #endif

    return static_cast<u32>(samples);
}

u32 RenderTextureImplFBO::getWidth() const
{
    return width_;
}

u32 RenderTextureImplFBO::getHeight() const
{
    return height_;
}

void RenderTextureImplFBO::unbind()
{
    glCheck(GLEXT_glBindFramebuffer(GLEXT_GL_FRAMEBUFFER, 0));
}