// JLibraryDevelopment
// EglContext.cpp
// Created on 2021-07-08 by Justyn Durnford
// Last modified on 2021-07-09 by Justyn Durnford
// source file for the EglContext class.

#include <JLibrary/Graphics/EglContext.hpp>
#include <JLibrary/Multithread/Lock.hpp>
#include <JLibrary/Multithread/Mutex.hpp>
#include <JLibrary/Window/Window.hpp>
using namespace jlib;

#define SF_GLAD_EGL_IMPLEMENTATION
#include <egl.h>

#include <iostream>
using std::cout;
using std::endl;

#include <string>
using std::string;

namespace jlib
{
	EGLDisplay getInitializedDisplay()
	{
        static EGLDisplay display = EGL_NO_DISPLAY;

        if (display == EGL_NO_DISPLAY)
        {
            eglCheck(display = eglGetDisplay(EGL_DEFAULT_DISPLAY));
            eglCheck(eglInitialize(display, nullptr, nullptr));
        }

        return display;
	}

    void ensureInit()
    {
        static bool initialized = false;
        if (!initialized)
        {
            initialized = true;

            // We don't check the return value since the extension
            // flags are cleared even if loading fails.
            gladLoaderLoadEGL(EGL_NO_DISPLAY);

            // Continue loading with a display.
            gladLoaderLoadEGL(getInitializedDisplay());
        }
    }

    void eglCheckError(const char* file, unsigned int line, const char* expression)
    {
        // Obtain information about the success or failure of the most recent EGL
        // function called in the current thread
        EGLint errorCode = eglGetError();

        if (errorCode != EGL_SUCCESS)
        {
            string fileString(file);
            string error = "unknown error";
            string description = "no description";

            // Decode the error code returned
            switch (errorCode)
            {
                case EGL_NOT_INITIALIZED:
                {
                    error = "EGL_NOT_INITIALIZED";
                    description = "EGL is not initialized, or could not be initialized, for the specified display";
                    break;
                }

                case EGL_BAD_ACCESS:
                {
                    error = "EGL_BAD_ACCESS";
                    description = "EGL cannot access a requested resource (for example, a context is bound in another thread)";
                    break;
                }

                case EGL_BAD_ALLOC:
                {
                    error = "EGL_BAD_ALLOC";
                    description = "EGL failed to allocate resources for the requested operation";
                    break;
                }
                case EGL_BAD_ATTRIBUTE:
                {
                    error = "EGL_BAD_ATTRIBUTE";
                    description = "an unrecognized attribute or attribute value was passed in an attribute list";
                    break;
                }

                case EGL_BAD_CONTEXT:
                {
                    error = "EGL_BAD_CONTEXT";
                    description = "an EGLContext argument does not name a valid EGLContext";
                    break;
                }

                case EGL_BAD_CONFIG:
                {
                    error = "EGL_BAD_CONFIG";
                    description = "an EGLConfig argument does not name a valid EGLConfig";
                    break;
                }

                case EGL_BAD_CURRENT_SURFACE:
                {
                    error = "EGL_BAD_CURRENT_SURFACE";
                    description = "the current surface of the calling thread is a window, pbuffer, or pixmap that is no longer valid";
                    break;
                }

                case EGL_BAD_DISPLAY:
                {
                    error = "EGL_BAD_DISPLAY";
                    description = "an EGLDisplay argument does not name a valid EGLDisplay; or, EGL is not initialized on the specified EGLDisplay";
                    break;
                }


                case EGL_BAD_SURFACE:
                {
                    error = "EGL_BAD_SURFACE";
                    description = "an EGLSurface argument does not name a valid surface (window, pbuffer, or pixmap) configured for rendering";
                    break;
                }

                case EGL_BAD_MATCH:
                {
                    error = "EGL_BAD_MATCH";
                    description = "arguments are inconsistent; for example, an otherwise valid context requires buffers (e.g. depth or stencil) not allocated by an otherwise valid surface";
                    break;
                }

                case EGL_BAD_PARAMETER:
                {
                    error = "EGL_BAD_PARAMETER";
                    description = "one or more argument values are invalid";
                    break;
                }

                case EGL_BAD_NATIVE_PIXMAP:
                {
                    error = "EGL_BAD_NATIVE_PIXMAP";
                    description = "an EGLNativePixmapType argument does not refer to a valid native pixmap";
                    break;
                }

                case EGL_BAD_NATIVE_WINDOW:
                {
                    error = "EGL_BAD_NATIVE_WINDOW";
                    description = "an EGLNativeWindowType argument does not refer to a valid native window";
                    break;
                }

                case EGL_CONTEXT_LOST:
                {
                    error = "EGL_CONTEXT_LOST";
                    description = "a power management event has occurred. The application must destroy all contexts and reinitialize client API state and objects to continue rendering";
                    break;
                }
            }

            // Log the error
            cout << "An internal EGL call failed in "
                << fileString.substr(fileString.find_last_of("\\/") + 1) << " (" << line << ") : "
                << "\nExpression:\n   " << expression
                << "\nError description:\n   " << error << "\n   " << description << "\n"
                << endl;
        }
    }

    void EglContext::updateSettings()
    {
        EGLBoolean result = EGL_FALSE;
        EGLint tmp = 0;

        // Update the internal context settings with the current config
        eglCheck(result = eglGetConfigAttrib(display_, config_, EGL_DEPTH_SIZE, &tmp));

        if (result == EGL_FALSE)
            cout << "Failed to retrieve EGL_DEPTH_SIZE" << endl;

        settings_.depthBits = tmp;

        eglCheck(result = eglGetConfigAttrib(display_, config_, EGL_STENCIL_SIZE, &tmp));

        if (result == EGL_FALSE)
            cout << "Failed to retrieve EGL_STENCIL_SIZE" << endl;

        settings_.stencilBits = tmp;

        eglCheck(result = eglGetConfigAttrib(display_, config_, EGL_SAMPLES, &tmp));

        if (result == EGL_FALSE)
            cout << "Failed to retrieve EGL_SAMPLES" << endl;

        settings_.antialiasingLevel = tmp;

        settings_.majorVersion = 1;
        settings_.minorVersion = 1;
        settings_.attributeFlags = ContextSettings::Default;
    }

    EglContext::EglContext(EglContext* shared) :
        display_(EGL_NO_DISPLAY),
        context_(EGL_NO_CONTEXT),
        surface_(EGL_NO_SURFACE),
        config_(nullptr)
    {
        ensureInit();

        // Get the initialized EGL display.
        display_ = getInitializedDisplay();

        // Get the best EGL config matching the default video settings.
        config_ = getBestConfig(display_, VideoMode::getDesktopMode().bitsPerPixel, ContextSettings());
        updateSettings();

        // Note: The EGL specs say that attrib_list can be nullptr when passed to eglCreatePbufferSurface,
        // but this is resulting in a segfault.
        EGLint attrib_list[] = 
        {
            EGL_WIDTH,  1,
            EGL_HEIGHT, 1,
            EGL_NONE
        };

        eglCheck(surface_ = eglCreatePbufferSurface(display_, config_, attrib_list));

        // Create EGL context
        createContext(shared);
    }

    EglContext::EglContext(EglContext* shared, const ContextSettings& settings, 
                           const Window* owner, u32 bitsPerPixel) :
        display_(EGL_NO_DISPLAY),
        context_(EGL_NO_CONTEXT),
        surface_(EGL_NO_SURFACE),
        config_(nullptr)
    {
        ensureInit();

        // Get the initialized EGL display.
        display_ = getInitializedDisplay();

        // Get the best EGL config matching the requested video settings.
        config_ = getBestConfig(display_, bitsPerPixel, settings);
        updateSettings();

        // Create EGL context.
        createContext(shared);

        // Create EGL surface.
        createSurface((EGLNativeWindowType)owner->getSystemHandle());
    }

    EglContext::EglContext(EglContext* shared, const ContextSettings& settings, u32 width, u32 height) :
        display_(EGL_NO_DISPLAY),
        context_(EGL_NO_CONTEXT),
        surface_(EGL_NO_SURFACE),
        config_(nullptr)
    {
        ensureInit();
    }

    EglContext::~EglContext()
    {
        // Notify unshared OpenGL resources of context destruction.
        cleanupUnsharedResources();

        // Deactivate the current context.
        EGLContext currentContext = EGL_NO_CONTEXT;
        eglCheck(currentContext = eglGetCurrentContext());

        if (currentContext == context_)
            eglCheck(eglMakeCurrent(display_, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT));

        // Destroy context.
        if (context_ != EGL_NO_CONTEXT)
            eglCheck(eglDestroyContext(display_, context_));

        // Destroy surface.
        if (surface_ != EGL_NO_SURFACE)
            eglCheck(eglDestroySurface(display_, surface_));
    }

    GlFunctionPointer EglContext::getFunction(const char* name)
    {
        ensureInit();
        return reinterpret_cast<GlFunctionPointer>(eglGetProcAddress(name));
    }

    bool EglContext::makeCurrent(bool current)
    {
        if (surface_ == EGL_NO_SURFACE)
            return false;

        EGLBoolean result = EGL_FALSE;

        if (current)
            eglCheck(result = eglMakeCurrent(display_, surface_, surface_, context_));
        else
            eglCheck(result = eglMakeCurrent(display_, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT));

        return (result != EGL_FALSE);
    }

    void EglContext::display()
    {
        if (surface_ != EGL_NO_SURFACE)
            eglCheck(eglSwapBuffers(display_, surface_));
    }

    void EglContext::setVerticalSyncEnabled(bool enabled)
    {
        eglCheck(eglSwapInterval(display_, enabled ? 1 : 0));
    }

    void EglContext::createContext(EglContext* shared)
    {
        const EGLint contextVersion[] = 
        {
            EGL_CONTEXT_CLIENT_VERSION, 1,
            EGL_NONE
        };

        EGLContext toShared;

        if (shared != nullptr)
            toShared = shared->context_;
        else
            toShared = EGL_NO_CONTEXT;

        if (toShared != EGL_NO_CONTEXT)
            eglMakeCurrent(display_, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);

        // Create EGL context.
        eglCheck(context_ = eglCreateContext(display_, config_, toShared, contextVersion));
    }

    void EglContext::createSurface(EGLNativeWindowType window)
    {
        eglCheck(surface_ = eglCreateWindowSurface(display_, config_, window, nullptr));
    }

    void EglContext::destroySurface()
    {
        // Ensures that this context is no longer active since our surface is going to be destroyed.
        setActive(false);

        eglCheck(eglDestroySurface(display_, surface_));
        surface_ = EGL_NO_SURFACE;
    }

    EGLConfig EglContext::getBestConfig(EGLDisplay display, u32 bitsPerPixel, 
                                        const ContextSettings& settings)
    {
        ensureInit();

        // Set our video settings constraint
        const EGLint attributes[] = {
            EGL_BUFFER_SIZE, static_cast<EGLint>(bitsPerPixel),
            EGL_DEPTH_SIZE, static_cast<EGLint>(settings.depthBits),
            EGL_STENCIL_SIZE, static_cast<EGLint>(settings.stencilBits),
            EGL_SAMPLE_BUFFERS, static_cast<EGLint>(settings.antialiasingLevel ? 1 : 0),
            EGL_SAMPLES, static_cast<EGLint>(settings.antialiasingLevel),
            EGL_SURFACE_TYPE, EGL_WINDOW_BIT | EGL_PBUFFER_BIT,
            EGL_RENDERABLE_TYPE, EGL_OPENGL_ES_BIT,
            EGL_NONE
        };

        EGLint configCount;
        EGLConfig configs[1];

        // Ask EGL for the best config matching our video settings
        eglCheck(eglChooseConfig(display, attributes, configs, 1, &configCount));

        // TODO: This should check EGL_CONFORMANT and pick the first conformant configuration.

        return configs[0];
    }
}