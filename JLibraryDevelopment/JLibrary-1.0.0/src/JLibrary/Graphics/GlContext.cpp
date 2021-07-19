// JLibraryDevelopment
// GlContext.cpp
// Created on 2021-07-02 by Justyn Durnford
// Last modified on 2021-07-17 by Justyn Durnford
// Source file for the GlContext class.

#ifndef SF_GLAD_GL_IMPLEMENTATION
    #define SF_GLAD_GL_IMPLEMENTATION
#endif // SF_GLAD_GL_IMPLEMENTATION

#include <JLibrary/Graphics/Context.hpp>
#include <JLibrary/Graphics/EglContext.hpp>
#include <JLibrary/Multithread/Lock.hpp>
#include <JLibrary/Multithread/Mutex.hpp>
#include <JLibrary/Multithread/ThreadLocalPtr.hpp>
using namespace jlib;

#include <cassert>

#include <cctype>
using std::isdigit;

#include <cmath>
using std::abs;

#include <cstring>
using std::strcmp;
using std::strlen;
using std::strncmp;
using std::strstr;

#include <iostream>
using std::cout;
using std::boolalpha;
using std::endl;
using std::noboolalpha;

#include <set>
using std::set;

#include <string>
using std::size_t;
using std::string;

#include <utility>
using std::pair;
using std::make_pair;

#include <vector>
using std::vector;

#if !defined(GL_MAJOR_VERSION)
#define GL_MAJOR_VERSION 0x821B
#endif

#if !defined(GL_MINOR_VERSION)
#define GL_MINOR_VERSION 0x821C
#endif

#if defined(JLIB_OPENGL_ES)
    typedef EglContext ContextType;
#else
    #include <JLibrary/Graphics/WglContext.hpp>
    typedef WglContext ContextType;
#endif
typedef void (APIENTRY* glEnableFuncType)(GLenum);
typedef GLenum(APIENTRY* glGetErrorFuncType)();
typedef void (APIENTRY* glGetIntegervFuncType)(GLenum, GLint*);
typedef const GLubyte* (APIENTRY* glGetStringFuncType)(GLenum);
typedef const GLubyte* (APIENTRY* glGetStringiFuncType)(GLenum, GLuint);
typedef GLboolean(APIENTRY* glIsEnabledFuncType)(GLenum);

#if !defined(GL_MULTISAMPLE)
    #define GL_MULTISAMPLE 0x809D
#endif

#if !defined(GL_MAJOR_VERSION)
    #define GL_MAJOR_VERSION 0x821B
#endif

#if !defined(GL_MINOR_VERSION)
    #define GL_MINOR_VERSION 0x821C
#endif

#if !defined(GL_NUM_EXTENSIONS)
    #define GL_NUM_EXTENSIONS 0x821D
#endif

#if !defined(GL_CONTEXT_FLAGS)
    #define GL_CONTEXT_FLAGS 0x821E
#endif

#if !defined(GL_FRAMEBUFFER_SRGB)
    #define GL_FRAMEBUFFER_SRGB 0x8DB9
#endif

#if !defined(GL_CONTEXT_FLAG_DEBUG_BIT)
    #define GL_CONTEXT_FLAG_DEBUG_BIT 0x00000002
#endif

#if !defined(GL_CONTEXT_PROFILE_MASK)
    #define GL_CONTEXT_PROFILE_MASK 0x9126
#endif

#if !defined(GL_CONTEXT_CORE_PROFILE_BIT)
    #define GL_CONTEXT_CORE_PROFILE_BIT 0x00000001
#endif

#if !defined(GL_CONTEXT_COMPATIBILITY_PROFILE_BIT)
    #define GL_CONTEXT_COMPATIBILITY_PROFILE_BIT 0x00000002
#endif

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

namespace
{
    // AMD drivers have issues with internal synchronization
    // We need to make sure that no operating system context
    // or pixel format operations are performed simultaneously
    // This mutex is also used to protect the shared context
    // from being locked on multiple threads and for managing
    // the resource count.
    Mutex mutex;

    // OpenGL resources counter.
    u32 resourceCount = 0;

    // This per-thread variable holds the current context for each thread.
    ThreadLocalPtr<GlContext> currentContext(nullptr);

    // The hidden, inactive context that will be shared with all other contexts.
    ContextType* sharedContext = nullptr;

    // Unique identifier, used for identifying contexts when managing unshareable OpenGL resources.
    u64 id = 1; // start at 1, zero is "no context."

    // Set containing callback functions to be called whenever a
    // context is going to be destroyed.
    // Unshareable OpenGL resources rely on this to clean up properly
    // whenever a context containing them is destroyed.
    typedef set<pair<ContextDestroyCallback, void*>> ContextDestroyCallbacks;
    ContextDestroyCallbacks contextDestroyCallbacks;

    // This structure contains all the state necessary to
    // track TransientContext usage.
    struct TransientContext : private NonCopyable
    {
        u32 referenceCount;
        Context* context;
        Lock* sharedContextLock;
        bool         useSharedContext;

        // Constructor.
        TransientContext() :
            referenceCount(0),
            context(0),
            sharedContextLock(0),
            useSharedContext(false)
        {
            if (resourceCount == 0)
                context = new Context;
            else if (!currentContext)
            {
                sharedContextLock = new Lock(mutex);
                useSharedContext = true;
                sharedContext->setActive(true);
            }
        }

        // Destructor.
        ~TransientContext()
        {
            if (useSharedContext)
                sharedContext->setActive(false);

            delete sharedContextLock;
            delete context;
        }
    };

    // This per-thread variable tracks if and how a transient
    // context is currently being used on the current thread.
    ThreadLocalPtr<TransientContext> transientContext(nullptr);

    // Supported OpenGL extensions.
    vector<string> extensions;

    // Load our extensions vector with the supported extensions.
    void loadExtensions()
    {
        extensions.clear();

        glGetErrorFuncType glGetErrorFunc = reinterpret_cast<glGetErrorFuncType>(GlContext::getFunction("glGetError"));
        glGetIntegervFuncType glGetIntegervFunc = reinterpret_cast<glGetIntegervFuncType>(GlContext::getFunction("glGetIntegerv"));
        glGetStringFuncType glGetStringFunc = reinterpret_cast<glGetStringFuncType>(GlContext::getFunction("glGetString"));

        if (!glGetErrorFunc || !glGetIntegervFunc || !glGetStringFunc)
            return;

        // Check whether a >= 3.0 context is available.
        i32 majorVersion = 0;
        glGetIntegervFunc(GL_MAJOR_VERSION, &majorVersion);

        glGetStringiFuncType glGetStringiFunc = reinterpret_cast<glGetStringiFuncType>(GlContext::getFunction("glGetStringi"));

        if (glGetErrorFunc() == GL_INVALID_ENUM || !glGetStringiFunc)
        {
            // Try to load the < 3.0 way.
            const char* extensionString = reinterpret_cast<const char*>(glGetStringFunc(GL_EXTENSIONS));

            do
            {
                const char* extension = extensionString;

                while (*extensionString && (*extensionString != ' '))
                    extensionString++;

                extensions.push_back(string(extension, extensionString));
            } 
            while (*extensionString++);
        }
        else
        {
            // Try to load the >= 3.0 way.
            int numExtensions = 0;
            glGetIntegervFunc(GL_NUM_EXTENSIONS, &numExtensions);

            if (numExtensions)
            {
                for (u32 i = 0; i < static_cast<u32>(numExtensions); ++i)
                {
                    const char* extensionString = reinterpret_cast<const char*>(glGetStringiFunc(GL_EXTENSIONS, i));

                    extensions.push_back(extensionString);
                }
            }
        }
    }

    // Helper to parse OpenGL version strings.
    bool parseVersionString(const char* version, const char* prefix, u32& major, u32& minor)
    {
        size_t prefixLength = strlen(prefix);

        if ((strlen(version) >= (prefixLength + 3))       &&
            (strncmp(version, prefix, prefixLength) == 0) &&
             isdigit(version[prefixLength])               &&
            (version[prefixLength + 1] == '.')            &&
             isdigit(version[prefixLength + 2]))
        {
            major = version[prefixLength] - '0';
            minor = version[prefixLength + 2] - '0';

            return true;
        }

        return false;
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

void jlib::ensureExtensionsInit()
{
    static bool initialized = false;
    if (!initialized)
    {
        initialized = true;

        #ifdef JLIB_OPENGL_ES
            gladLoadGLES1(reinterpret_cast<GLADloadfunc>(Context::getFunction));
        #else
            gladLoadGL(reinterpret_cast<GLADloadfunc>(Context::getFunction));
        #endif

        // Retrieve the context version number.
        int majorVersion = 0;
        int minorVersion = 0;

        // Try the new way first.
        glGetIntegerv(GL_MAJOR_VERSION, &majorVersion);
        glGetIntegerv(GL_MINOR_VERSION, &minorVersion);

        if (glGetError() == GL_INVALID_ENUM)
        {
            // Try the old way.
            const GLubyte* version = glGetString(GL_VERSION);
            if (version)
            {
                // The beginning of the returned string is "major.minor" (this is standard).
                majorVersion = version[0] - '0';
                minorVersion = version[2] - '0';
            }
            else
            {
                // Can't get the version number, assume 1.1.
                majorVersion = 1;
                minorVersion = 1;
            }
        }

        if ((majorVersion < 1) || ((majorVersion == 1) && (minorVersion < 1)))
        {
            cout << "sfml-graphics requires support for OpenGL 1.1 or greater" << endl;
            cout << "Ensure that hardware acceleration is enabled if available" << endl;
        }
    }
}

void jlib::glCheckError(const char* file, u32 line, const char* expression)
{
    // Get the last error.
    GLenum errorCode = glGetError();

    if (errorCode != GL_NO_ERROR)
    {
        string fileString = file;
        string error = "Unknown error.";
        string description = "No description.";

        // Decode the error code.
        switch (errorCode)
        {
            case GL_INVALID_ENUM:
            {
                error = "GL_INVALID_ENUM";
                description = "An unacceptable value has been specified for an enumerated argument.";
                break;
            }

            case GL_INVALID_VALUE:
            {
                error = "GL_INVALID_VALUE";
                description = "A numeric argument is out of range.";
                break;
            }

            case GL_INVALID_OPERATION:
            {
                error = "GL_INVALID_OPERATION";
                description = "The specified operation is not allowed in the current state.";
                break;
            }

            case GL_STACK_OVERFLOW:
            {
                error = "GL_STACK_OVERFLOW";
                description = "This command would cause a stack overflow.";
                break;
            }

            case GL_STACK_UNDERFLOW:
            {
                error = "GL_STACK_UNDERFLOW";
                description = "This command would cause a stack underflow.";
                break;
            }

            case GL_OUT_OF_MEMORY:
            {
                error = "GL_OUT_OF_MEMORY";
                description = "There is not enough memory left to execute the command.";
                break;
            }

            case GLEXT_GL_INVALID_FRAMEBUFFER_OPERATION:
            {
                error = "GL_INVALID_FRAMEBUFFER_OPERATION";
                description = "The object bound to FRAMEBUFFER_BINDING is not \"framebuffer complete\".";
                break;
            }
        }

        // Log the error.
        cout << "An internal OpenGL call failed in "
             << fileString.substr(fileString.find_last_of("\\/") + 1) << "(" << line << ")."
             << "\nExpression:\n   " << expression
             << "\nError description:\n   " << error << "\n   " << description << "\n"
             << endl;
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

void GlContext::initialize(const ContextSettings& requestedSettings)
{
    // Activate the context
    setActive(true);

    // Retrieve the context version number
    i32 majorVersion = 0;
    i32 minorVersion = 0;

    // Try the new way first
    glGetIntegervFuncType glGetIntegervFunc = reinterpret_cast<glGetIntegervFuncType>(getFunction("glGetIntegerv"));
    glGetErrorFuncType glGetErrorFunc = reinterpret_cast<glGetErrorFuncType>(getFunction("glGetError"));
    glGetStringFuncType glGetStringFunc = reinterpret_cast<glGetStringFuncType>(getFunction("glGetString"));
    glEnableFuncType glEnableFunc = reinterpret_cast<glEnableFuncType>(getFunction("glEnable"));
    glIsEnabledFuncType glIsEnabledFunc = reinterpret_cast<glIsEnabledFuncType>(getFunction("glIsEnabled"));

    if (!glGetIntegervFunc || !glGetErrorFunc || !glGetStringFunc || !glEnableFunc || !glIsEnabledFunc)
    {
        cout << "Could not load necessary function to initialize OpenGL context" << endl;
        return;
    }

    glGetIntegervFunc(GL_MAJOR_VERSION, &majorVersion);
    glGetIntegervFunc(GL_MINOR_VERSION, &minorVersion);

    if (glGetErrorFunc() != GL_INVALID_ENUM)
    {
        settings_.majorVersion = static_cast<u32>(majorVersion);
        settings_.minorVersion = static_cast<u32>(minorVersion);
    }
    else
    {
        // Try the old way

        // If we can't get the version number, assume 1.1
        settings_.majorVersion = 1;
        settings_.minorVersion = 1;

        const char* version = reinterpret_cast<const char*>(glGetStringFunc(GL_VERSION));
        if (version)
        {
            // OpenGL ES Common Lite profile: The beginning of the returned string is "OpenGL ES-CL major.minor"
            // OpenGL ES Common profile:      The beginning of the returned string is "OpenGL ES-CM major.minor"
            // OpenGL ES Full profile:        The beginning of the returned string is "OpenGL ES major.minor"
            // Desktop OpenGL:                The beginning of the returned string is "major.minor"

            if (!parseVersionString(version, "OpenGL ES-CL ", settings_.majorVersion, settings_.minorVersion) &&
                !parseVersionString(version, "OpenGL ES-CM ", settings_.majorVersion, settings_.minorVersion) &&
                !parseVersionString(version, "OpenGL ES ", settings_.majorVersion, settings_.minorVersion)    &&
                !parseVersionString(version, "", settings_.majorVersion, settings_.minorVersion))
                cout << "Unable to parse OpenGL version string: \"" << version << "\", defaulting to 1.1" << endl;
        }
        else
            cout << "Unable to retrieve OpenGL version string, defaulting to 1.1" << endl;
    }

    // 3.0 contexts only deprecate features, but do not remove them yet
    // 3.1 contexts remove features if ARB_compatibility is not present
    // 3.2+ contexts remove features only if a core profile is requested

    // If the context was created with wglCreateContext, it is guaranteed to be compatibility.
    // If a 3.0 context was created with wglCreateContextAttribsARB, it is guaranteed to be compatibility.
    // If a 3.1 context was created with wglCreateContextAttribsARB, the compatibility flag
    // is set only if ARB_compatibility is present
    // If a 3.2+ context was created with wglCreateContextAttribsARB, the compatibility flag
    // would have been set correctly already depending on whether ARB_create_context_profile is supported.

    // If the user requests a 3.0 context, it will be a compatibility context regardless of the requested profile.
    // If the user requests a 3.1 context and its creation was successful, the specification
    // states that it will not be a compatibility profile context regardless of the requested
    // profile unless ARB_compatibility is present.

    settings_.attributeFlags = ContextSettings::Default;

    if (settings_.majorVersion >= 3)
    {
        // Retrieve the context flags
        int flags = 0;
        glGetIntegervFunc(GL_CONTEXT_FLAGS, &flags);

        if (flags & GL_CONTEXT_FLAG_DEBUG_BIT)
            settings_.attributeFlags |= ContextSettings::Debug;

        if ((settings_.majorVersion == 3) && (settings_.minorVersion == 1))
        {
            settings_.attributeFlags |= ContextSettings::Core;

            glGetStringiFuncType glGetStringiFunc = reinterpret_cast<glGetStringiFuncType>(getFunction("glGetStringi"));

            if (glGetStringiFunc)
            {
                i32 numExtensions = 0;
                glGetIntegervFunc(GL_NUM_EXTENSIONS, &numExtensions);

                for (u32 i = 0; i < static_cast<u32>(numExtensions); ++i)
                {
                    const char* extensionString = reinterpret_cast<const char*>(glGetStringiFunc(GL_EXTENSIONS, i));

                    if (strstr(extensionString, "GL_ARB_compatibility"))
                    {
                        settings_.attributeFlags &= ~static_cast<u32>(ContextSettings::Core);
                        break;
                    }
                }
            }
        }
        else if ((settings_.majorVersion > 3) || (settings_.minorVersion >= 2))
        {
            // Retrieve the context profile
            i32 profile = 0;
            glGetIntegervFunc(GL_CONTEXT_PROFILE_MASK, &profile);

            if (profile & GL_CONTEXT_CORE_PROFILE_BIT)
                settings_.attributeFlags |= ContextSettings::Core;
        }
    }

    // Enable anti-aliasing if requested by the user and supported
    if ((requestedSettings.antialiasingLevel > 0) && (settings_.antialiasingLevel > 0))
        glEnableFunc(GL_MULTISAMPLE);
    else
        settings_.antialiasingLevel = 0;

    // Enable sRGB if requested by the user and supported
    if (requestedSettings.sRgbCapable && settings_.sRgbCapable)
    {
        glEnableFunc(GL_FRAMEBUFFER_SRGB);

        // Check to see if the enable was successful
        if (glIsEnabledFunc(GL_FRAMEBUFFER_SRGB) == GL_FALSE)
        {
            cout << "Warning: Failed to enable GL_FRAMEBUFFER_SRGB" << endl;
            settings_.sRgbCapable = false;
        }
    }
    else
        settings_.sRgbCapable = false;
}

void GlContext::checkSettings(const ContextSettings& requestedSettings)
{
    // Perform checks to inform the user if they are getting a context they might not have expected

    glGetStringFuncType glGetStringFunc = reinterpret_cast<glGetStringFuncType>(getFunction("glGetString"));

    if (!glGetStringFunc)
    {
        cout << "Could not load glGetString function" << endl;
        return;
    }

    // Detect any known non-accelerated implementations and warn
    const char* vendorName = reinterpret_cast<const char*>(glGetStringFunc(GL_VENDOR));
    const char* rendererName = reinterpret_cast<const char*>(glGetStringFunc(GL_RENDERER));

    if (vendorName && rendererName)
    {
        if ((strcmp(vendorName, "Microsoft Corporation") == 0) && 
            (strcmp(rendererName, "GDI Generic") == 0))
        {
            cout << "Warning: Detected \"Microsoft Corporation GDI Generic\" OpenGL implementation" << endl
                 << "The current OpenGL implementation is not hardware-accelerated" << endl;
        }
    }

    int version = settings_.majorVersion * 10 + settings_.minorVersion;
    int requestedVersion = requestedSettings.majorVersion * 10 + requestedSettings.minorVersion;

    if ((settings_.attributeFlags != requestedSettings.attributeFlags) ||
        (version < requestedVersion) ||
        (settings_.stencilBits < requestedSettings.stencilBits) ||
        (settings_.antialiasingLevel < requestedSettings.antialiasingLevel) ||
        (settings_.depthBits < requestedSettings.depthBits) ||
        (!settings_.sRgbCapable && requestedSettings.sRgbCapable))
    {
        cout << "Warning: The created OpenGL context does not fully meet the settings that were requested" << std::endl;
        cout << "Requested: version = " << requestedSettings.majorVersion << "." << requestedSettings.minorVersion
             << " ; depth bits = " << requestedSettings.depthBits
             << " ; stencil bits = " << requestedSettings.stencilBits
             << " ; AA level = " << requestedSettings.antialiasingLevel
             << boolalpha
             << " ; core = " << ((requestedSettings.attributeFlags & ContextSettings::Core) != 0)
             << " ; debug = " << ((requestedSettings.attributeFlags & ContextSettings::Debug) != 0)
             << " ; sRGB = " << requestedSettings.sRgbCapable
             << noboolalpha << endl;
        cout << "Created: version = " << settings_.majorVersion << "." << settings_.minorVersion
             << " ; depth bits = " << settings_.depthBits
             << " ; stencil bits = " << settings_.stencilBits
             << " ; AA level = " << settings_.antialiasingLevel
             << boolalpha
             << " ; core = " << ((settings_.attributeFlags & ContextSettings::Core) != 0)
             << " ; debug = " << ((settings_.attributeFlags & ContextSettings::Debug) != 0)
             << " ; sRGB = " << settings_.sRgbCapable
             << noboolalpha << endl;
    }
}

GlContext::GlContext() : id_(id++) {}

void GlContext::cleanupUnsharedResources()
{
    // Save the current context so we can restore it later
    GlContext* contextToRestore = currentContext;

    // If this context is already active there is no need to save it
    if (contextToRestore == this)
        contextToRestore = nullptr;

    // Make this context active so resources can be freed
    setActive(true);

    // Call the registered destruction callbacks
    for (ContextDestroyCallbacks::iterator iter = contextDestroyCallbacks.begin(); iter != contextDestroyCallbacks.end(); ++iter)
        iter->first(iter->second);

    // Make the originally active context active again
    if (contextToRestore)
        contextToRestore->setActive(true);
}

i32 GlContext::evaluateFormat(u32 bitsPerPixel, const ContextSettings& settings, 
                              i32 colorBits, i32 depthBits, i32 stencilBits, 
                              i32 antialiasing, bool accelerated, bool sRgb)
{
    i32 colorDiff = static_cast<i32>(bitsPerPixel) - colorBits;
    i32 depthDiff = static_cast<i32>(settings.depthBits) - depthBits;
    i32 stencilDiff = static_cast<i32>(settings.stencilBits) - stencilBits;
    i32 antialiasingDiff = static_cast<i32>(settings.antialiasingLevel) - antialiasing;

    // Weight sub-scores so that better settings don't score equally as bad as worse settings
    colorDiff *= ((colorDiff > 0) ? 100000 : 1);
    depthDiff *= ((depthDiff > 0) ? 100000 : 1);
    stencilDiff *= ((stencilDiff > 0) ? 100000 : 1);
    antialiasingDiff *= ((antialiasingDiff > 0) ? 100000 : 1);

    // Aggregate the scores
    i32 score = abs(colorDiff) + abs(depthDiff) + abs(stencilDiff) + abs(antialiasingDiff);

    // If the user wants an sRGB capable format, try really hard to get one
    if (settings.sRgbCapable && !sRgb)
        score += 10000000;

    // Make sure we prefer hardware acceleration over features
    if (!accelerated)
        score += 100000000;

    return score;
}

GlContext::~GlContext()
{
    if (sharedContext != nullptr)
    {
        if (this == currentContext)
            currentContext = nullptr;
    }
}

void GlContext::initResource()
{
    // Protect from concurrent access.
    Lock lock(mutex);

    // If this is the very first resource, trigger the global context initialization.
    if (resourceCount == 0)
    {
        if (sharedContext)
        {
            // Increment the resources counter.
            ++resourceCount;
            return;
        }

        // Create the shared context.
        sharedContext = new ContextType(nullptr);
        sharedContext->initialize(ContextSettings());

        // Load our extensions vector.
        loadExtensions();

        // Deactivate the shared context so that others can activate it when necessary.
        sharedContext->setActive(false);
    }

    // Increment the resources counter.
    ++resourceCount;
}

void GlContext::cleanupResource()
{
    // Protect from concurrent access.
    Lock lock(mutex);

    // Decrement the resources counter.
    --resourceCount;

    // If there's no more resource alive, we can trigger the global context cleanup.
    if (resourceCount == 0)
    {
        if (!sharedContext)
            return;

        // Destroy the shared context.
        delete sharedContext;
        sharedContext = nullptr;
    }
}

void GlContext::registerContextDestroyCallback(ContextDestroyCallback callback, void* arg)
{
    contextDestroyCallbacks.insert(make_pair(callback, arg));
}

void GlContext::acquireTransientContext()
{
    // Protect from concurrent access.
    Lock lock(mutex);

    // If this is the first TransientContextLock on this thread,
    // construct the state object.
    if (!transientContext)
        transientContext = new TransientContext;

    // Increase the reference count.
    ++(transientContext->referenceCount);
}

void GlContext::releaseTransientContext()
{
    // Protect from concurrent access
    Lock lock(mutex);

    // Make sure a matching acquireTransientContext() was called
    assert(transientContext);

    // Decrease the reference count
    transientContext->referenceCount--;

    // If this is the last TransientContextLock that is released
    // destroy the state object
    if (transientContext->referenceCount == 0)
    {
        delete transientContext;
        transientContext = nullptr;
    }
}

GlContext* GlContext::create()
{
    // Make sure that there's an active context 
    // (context creation may need extensions, and thus a valid context).
    assert(sharedContext != nullptr);

    Lock lock(mutex);

    GlContext* context = nullptr;

    // We don't use acquireTransientContext here since we have
    // to ensure we have exclusive access to the shared context
    // in order to make sure it is not active during context creation.
    {
        sharedContext->setActive(true);

        // Create the context
        context = new ContextType(sharedContext);

        sharedContext->setActive(false);
    }

    context->initialize(ContextSettings());

    return context;
}

GlContext* GlContext::create(const ContextSettings& settings, const WindowImpl* owner, u32 bitsPerPixel)
{
    // Make sure that there's an active context 
    // (context creation may need extensions, and thus a valid context).
    assert(sharedContext != nullptr);

    Lock lock(mutex);

    // If resourceCount is 1 we know that we are inside jlib::Context or jlib::Window
    // Only in this situation we allow the user to indirectly 
    // re-create the shared context as a core context.

    // Check if we need to convert our shared context into a core context.
    if ((resourceCount == 1) &&
        (settings.attributeFlags & ContextSettings::Core) &&
        !(sharedContext->settings_.attributeFlags & ContextSettings::Core))
    {
        // Re-create our shared context as a core context.
        ContextSettings sharedSettings(0, 0, 0, settings.majorVersion, settings.minorVersion, settings.attributeFlags);

        delete sharedContext;
        sharedContext = new ContextType(nullptr, sharedSettings, 1, 1);
        sharedContext->initialize(sharedSettings);

        // Reload our extensions vector.
        loadExtensions();
    }

    GlContext* context = nullptr;

    // We don't use acquireTransientContext here since we have
    // to ensure we have exclusive access to the shared context
    // in order to make sure it is not active during context creation.
    {
        sharedContext->setActive(true);

        // Create the context
        context = new ContextType(sharedContext, settings, owner, bitsPerPixel);

        sharedContext->setActive(false);
    }

    context->initialize(settings);
    context->checkSettings(settings);

    return context;
}

GlContext* GlContext::create(const ContextSettings& settings, u32 width, u32 height)
{
    // Make sure that there's an active context 
    // (context creation may need extensions, and thus a valid context).
    assert(sharedContext != nullptr);

    Lock lock(mutex);

    // If resourceCount is 1 we know that we are inside jlib::Context or jlib::Window.
    // Only in this situation we allow the user to indirectly 
    // re-create the shared context as a core context.

    // Check if we need to convert our shared context into a core context
    if ((resourceCount == 1) &&
        (settings.attributeFlags & ContextSettings::Core) &&
        !(sharedContext->settings_.attributeFlags & ContextSettings::Core))
    {
        // Re-create our shared context as a core context.
        ContextSettings sharedSettings(0, 0, 0, settings.majorVersion, settings.minorVersion, settings.attributeFlags);

        delete sharedContext;
        sharedContext = new ContextType(nullptr, sharedSettings, 1, 1);
        sharedContext->initialize(sharedSettings);

        // Reload our extensions vector.
        loadExtensions();
    }

    GlContext* context = nullptr;

    // We don't use acquireTransientContext here since we have
    // to ensure we have exclusive access to the shared context
    // in order to make sure it is not active during context creation.
    {
        sharedContext->setActive(true);

        // Create the context
        context = new ContextType(sharedContext, settings, width, height);

        sharedContext->setActive(false);
    }

    context->initialize(settings);
    context->checkSettings(settings);

    return context;
}

bool GlContext::isExtensionAvailable(const char* name)
{
    for (const string& elem : extensions)
    {
        if (elem == name)
            return true;
    }

    return false;
}

GlFunctionPointer GlContext::getFunction(const char* name)
{
    Lock lock(mutex);
    return ContextType::getFunction(name);
}

const GlContext* GlContext::getActiveContext()
{
    return currentContext;
}

u64 GlContext::getActiveContextId()
{
    return currentContext ? currentContext->id_ : 0;
}

const ContextSettings& GlContext::settings() const
{
    return settings_;
}

bool GlContext::setActive(bool active)
{
    if (active)
    {
        if (this != currentContext)
        {
            Lock lock(mutex);

            // Activate the context
            if (makeCurrent(true))
            {
                // Set it as the new current context for this thread
                currentContext = this;
                return true;
            }
            else
                return false;
        }
        else // This context is already the active one on this thread, don't do anything.
            return true;
    }
    else
    {
        if (this == currentContext)
        {
            Lock lock(mutex);

            // Deactivate the context
            if (makeCurrent(false))
            {
                currentContext = nullptr;
                return true;
            }
            else
                return false;
        }
        else // This context is not the active one on this thread, don't do anything.
            return true;
    }
}