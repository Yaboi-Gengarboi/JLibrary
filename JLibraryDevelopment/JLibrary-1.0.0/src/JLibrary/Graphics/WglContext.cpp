// JLibraryDevelopment
// WglContext.cpp
// Created on 2021-07-10 by Justyn Durnford
// Last modified on 2021-07-18 by Justyn Durnford
// Source file for the WglContext class.

#define SF_GLAD_WGL_IMPLEMENTATION
#include <JLibrary/Window/Window.hpp>
#include <JLibrary/Graphics/WglContext.hpp>
#include <JLibrary/Multithread/Lock.hpp>
#include <JLibrary/Multithread/Mutex.hpp>
#include <JLibrary/Multithread/ThreadLocalPtr.hpp>
using namespace jlib;

#include <cstddef>
using std::ptrdiff_t;
using std::size_t;

#include <iostream>
using std::cout;
using std::wcout;
using std::endl;

#include <sstream>
using std::ostringstream;

#include <string>
using std::wstring;

#include <vector>
using std::vector;

namespace priv
{
    // Some drivers are bugged and don't track the current HDC/HGLRC properly.
    // In order to deactivate successfully, we need to track it ourselves as well.
    ThreadLocalPtr<WglContext> currentContext(nullptr);

    void ensureInit()
    {
        static bool initialized = false;
        if (!initialized)
        {
            initialized = true;
            gladLoadWGL(nullptr, WglContext::getFunction);
        }
    }

    void ensureExtensionsInit(HDC deviceContext)
    {
        static bool initialized = false;
        if (!initialized)
        {
            initialized = true;

            // We don't check the return value since the extension
            // flags are cleared even if loading fails.
            gladLoadWGL(deviceContext, WglContext::getFunction);
        }
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

wstring getErrorString(DWORD errorCode)
{
    PTCHAR buffer;
    if (FormatMessage(FORMAT_MESSAGE_MAX_WIDTH_MASK | FORMAT_MESSAGE_ALLOCATE_BUFFER | 
                      FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, 
                      nullptr, errorCode, 0, reinterpret_cast<LPTSTR>(&buffer), 256, nullptr) != 0)
    {
        wstring errMsg(buffer);
        LocalFree(buffer);
        return errMsg;
    }

    ostringstream ss;
    ss << "Error " << errorCode;
    return wstring(str_to_wstr(ss.str()));
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

void WglContext::setDevicePixelFormat(u32 bitsPerPixel)
{
    int bestFormat = selectBestPixelFormat(deviceContext_, bitsPerPixel, settings_);

    if (bestFormat == 0)
    {
        wcout << L"Failed to find a suitable pixel format for device context: " << getErrorString(GetLastError()) << endl
              << L"Cannot create OpenGL context" << endl;
        return;
    }

    // Extract the depth and stencil bits from the chosen format
    PIXELFORMATDESCRIPTOR actualFormat;
    actualFormat.nSize = sizeof(actualFormat);
    actualFormat.nVersion = 1;
    DescribePixelFormat(deviceContext_, bestFormat, sizeof(actualFormat), &actualFormat);

    // Set the chosen pixel format
    if (SetPixelFormat(deviceContext_, bestFormat, &actualFormat) == false)
    {
        wcout << L"Failed to set pixel format for device context: " << getErrorString(GetLastError()) << endl
              << L"Cannot create OpenGL context" << endl;
        return;
    }
}

void WglContext::updateSettingsFromPixelFormat()
{
    int format = GetPixelFormat(deviceContext_);

    if (format == 0)
    {
        wcout << L"Failed to get selected pixel format: " << getErrorString(GetLastError()) << endl;
        return;
    }

    PIXELFORMATDESCRIPTOR actualFormat;
    actualFormat.nSize = sizeof(actualFormat);
    actualFormat.nVersion = 1;

    if (DescribePixelFormat(deviceContext_, format, sizeof(actualFormat), &actualFormat) == 0)
    {
        wcout << L"Failed to retrieve pixel format information: " << getErrorString(GetLastError()) << endl;
        return;
    }

    if (SF_GLAD_WGL_ARB_pixel_format)
    {
        const int attributes[] = { WGL_DEPTH_BITS_ARB, WGL_STENCIL_BITS_ARB };
        int values[2];

        if (wglGetPixelFormatAttribivARB(deviceContext_, format, PFD_MAIN_PLANE, 2, attributes, values) == TRUE)
        {
            settings_.depthBits = values[0];
            settings_.stencilBits = values[1];
        }
        else
        {
            wcout << L"Failed to retrieve pixel format information: " << getErrorString(GetLastError()) << endl;
            settings_.depthBits = actualFormat.cDepthBits;
            settings_.stencilBits = actualFormat.cStencilBits;
        }

        if (SF_GLAD_WGL_ARB_multisample)
        {
            const int sampleAttributes[] = { WGL_SAMPLE_BUFFERS_ARB, WGL_SAMPLES_ARB };
            int sampleValues[2];

            if (wglGetPixelFormatAttribivARB(deviceContext_, format, PFD_MAIN_PLANE, 2, sampleAttributes, sampleValues) == TRUE)
                settings_.antialiasingLevel = sampleValues[0] ? sampleValues[1] : 0;
            else
            {
                wcout << L"Failed to retrieve pixel format multisampling information: " << getErrorString(GetLastError()) << endl;
                settings_.antialiasingLevel = 0;
            }
        }
        else
            settings_.antialiasingLevel = 0;

        if (SF_GLAD_WGL_ARB_framebuffer_sRGB || SF_GLAD_WGL_EXT_framebuffer_sRGB)
        {
            const int sRgbCapableAttribute = WGL_FRAMEBUFFER_SRGB_CAPABLE_ARB;
            int sRgbCapableValue = 0;

            if (wglGetPixelFormatAttribivARB(deviceContext_, format, PFD_MAIN_PLANE, 1, &sRgbCapableAttribute, &sRgbCapableValue) == TRUE)
                settings_.sRgbCapable = (sRgbCapableValue == TRUE);
            else
            {
                wcout << L"Failed to retrieve pixel format sRGB capability information: " << getErrorString(GetLastError()) << endl;
                settings_.sRgbCapable = false;
            }
        }
        else
            settings_.sRgbCapable = false;
    }
    else
    {
        settings_.depthBits = actualFormat.cDepthBits;
        settings_.stencilBits = actualFormat.cStencilBits;
        settings_.antialiasingLevel = 0;
    }
}

void WglContext::createSurface(WglContext* shared, u32 width, u32 height, u32 bitsPerPixel)
{
    // Check if the shared context already exists and pbuffers are supported.
    if (shared && shared->deviceContext_ && SF_GLAD_WGL_ARB_pbuffer)
    {
        i32 bestFormat = selectBestPixelFormat(shared->deviceContext_, bitsPerPixel, settings_, true);

        if (bestFormat > 0)
        {
            i32 attributes[] = { 0, 0 };

            pbuffer_ = wglCreatePbufferARB(shared->deviceContext_, bestFormat, width, height, attributes);

            if (pbuffer_)
            {
                window_ = shared->window_;
                deviceContext_ = wglGetPbufferDCARB(pbuffer_);

                if (!deviceContext_)
                {
                    wcout << L"Failed to retrieve pixel buffer device context: " << getErrorString(GetLastError()) << endl;

                    wglDestroyPbufferARB(pbuffer_);
                    pbuffer_ = nullptr;
                }
            }
            else
                wcout << "Failed to create pixel buffer: " << getErrorString(GetLastError()) << endl;
        }
    }

    // If pbuffers are not available we use a hidden window as the off-screen surface to draw to.
    if (!deviceContext_)
    {
        // We can't create a memory DC, the resulting context wouldn't be compatible
        // with other contexts and thus wglShareLists would always fail.

        // Create the hidden window
        window_ = CreateWindowA("STATIC", "", WS_POPUP | WS_DISABLED, 0, 0, width, height, nullptr, nullptr, GetModuleHandle(nullptr), nullptr);
        ShowWindow(window_, SW_HIDE);
        deviceContext_ = GetDC(window_);

        ownsWindow_ = true;

        // Set the pixel format of the device context
        setDevicePixelFormat(bitsPerPixel);
    }

    // Update context settings from the selected pixel format
    updateSettingsFromPixelFormat();
}

void WglContext::createSurface(HWND window, u32 bitsPerPixel)
{
    window_ = window;
    deviceContext_ = GetDC(window);

    // Set the pixel format of the device context
    setDevicePixelFormat(bitsPerPixel);

    // Update context settings from the selected pixel format
    updateSettingsFromPixelFormat();
}

void WglContext::createContext(WglContext* shared)
{
    // We can't create an OpenGL context if we don't have a DC
    if (!deviceContext_)
        return;

    // Get a working copy of the context settings
    ContextSettings settings = settings_;

    // Get the context to share display lists with
    HGLRC sharedContext = shared ? shared->context_ : nullptr;

    // Create the OpenGL context -- first try using wglCreateContextAttribsARB
    while (!context_ && settings_.majorVersion)
    {
        if (SF_GLAD_WGL_ARB_create_context)
        {
            vector<i32> attributes;

            // Check if the user requested a specific context version (anything > 1.1)
            if ((settings_.majorVersion > 1) || ((settings_.majorVersion == 1) && (settings_.minorVersion > 1)))
            {
                attributes.push_back(WGL_CONTEXT_MAJOR_VERSION_ARB);
                attributes.push_back(settings_.majorVersion);
                attributes.push_back(WGL_CONTEXT_MINOR_VERSION_ARB);
                attributes.push_back(settings_.minorVersion);
            }

            // Check if setting the profile is supported
            if (SF_GLAD_WGL_ARB_create_context_profile)
            {
                i32 profile = (settings_.attributeFlags & ContextSettings::Core) ? WGL_CONTEXT_CORE_PROFILE_BIT_ARB : WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB;
                i32 debug = (settings_.attributeFlags & ContextSettings::Debug) ? WGL_CONTEXT_DEBUG_BIT_ARB : 0;

                attributes.push_back(WGL_CONTEXT_PROFILE_MASK_ARB);
                attributes.push_back(profile);
                attributes.push_back(WGL_CONTEXT_FLAGS_ARB);
                attributes.push_back(debug);
            }
            else
            {
                if ((settings_.attributeFlags & ContextSettings::Core) || (settings_.attributeFlags & ContextSettings::Debug))
                    cout << "Selecting a profile during context creation is not supported,"
                         << "disabling comptibility and debug" << endl;

                settings_.attributeFlags = ContextSettings::Default;
            }

            // Append the terminating 0
            attributes.push_back(0);
            attributes.push_back(0);

            if (sharedContext)
            {
                static Mutex mutex;
                Lock lock(mutex);

                if (priv::currentContext == shared)
                {
                    if (wglMakeCurrent(shared->deviceContext_, nullptr) == FALSE)
                    {
                        wcout << L"Failed to deactivate shared context before sharing: " << getErrorString(GetLastError()) << endl;
                        return;
                    }

                    priv::currentContext = nullptr;
                }
            }

            // Create the context.
            context_ = wglCreateContextAttribsARB(deviceContext_, sharedContext, &attributes[0]);
        }
        else // If wglCreateContextAttribsARB is not supported, there is no need to keep trying.
            break;

        // If we couldn't create the context, first try disabling flags,
        // then lower the version number and try again -- stop at 0.0
        // Invalid version numbers will be generated by this algorithm (like 3.9), but we really don't care
        if (!context_)
        {
            if (settings_.attributeFlags != ContextSettings::Default)
                settings_.attributeFlags = ContextSettings::Default;
            else if (settings_.minorVersion > 0)
            {
                // If the minor version is not 0, we decrease it and try again.
                settings_.minorVersion--;

                settings_.attributeFlags = settings.attributeFlags;
            }
            else
            {
                // If the minor version is 0, we decrease the major version.
                settings_.majorVersion--;
                settings_.minorVersion = 9;

                settings_.attributeFlags = settings.attributeFlags;
            }
        }
    }

    // If wglCreateContextAttribsARB failed, use wglCreateContext.
    if (!context_)
    {
        // set the context version to 1.1 (arbitrary) and disable flags.
        settings_.majorVersion = 1;
        settings_.minorVersion = 1;
        settings_.attributeFlags = ContextSettings::Default;

        context_ = wglCreateContext(deviceContext_);
        if (!context_)
        {
            wcout << L"Failed to create an OpenGL context for this window: " << getErrorString(GetLastError()) << endl;
            return;
        }

        // Share this context with others.
        if (sharedContext)
        {
            // wglShareLists doesn't seem to be thread-safe.
            static Mutex mutex;
            Lock lock(mutex);

            if (priv::currentContext == shared)
            {
                if (wglMakeCurrent(shared->deviceContext_, nullptr) == false)
                {
                    wcout << L"Failed to deactivate shared context before sharing: " << getErrorString(GetLastError()) << endl;
                    return;
                }

                priv::currentContext = nullptr;
            }

            if (wglShareLists(sharedContext, context_) == false)
                wcout << L"Failed to share the OpenGL context: " << getErrorString(GetLastError()) << endl;
        }
    }

    // If we are the shared context, initialize extensions now.
    // This enables us to re-create the shared context using extensions if we need to.
    if (!shared && context_)
    {
        makeCurrent(true);
        priv::ensureExtensionsInit(deviceContext_);
        makeCurrent(false);
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

WglContext::WglContext(WglContext* shared) :
    window_(nullptr),
    pbuffer_(nullptr),
    deviceContext_(nullptr),
    context_(nullptr),
    ownsWindow_(false)
{
    priv::ensureInit();

    // TODO: Delegate to the other constructor in C++11.

    // Save the creation settings.
    settings_ = ContextSettings();

    // Create the rendering surface (window or pbuffer_ if supported).
    createSurface(shared, 1, 1, VideoMode::getDesktopMode().bitsPerPixel);

    // Create the context.
    createContext(shared);
}

WglContext::WglContext(WglContext* shared, const ContextSettings& settings, 
                       const WindowImpl* owner, u32 bitsPerPixel) :
    window_(nullptr),
    pbuffer_(nullptr),
    deviceContext_(nullptr),
    context_(nullptr),
    ownsWindow_(false)
{
    priv::ensureInit();

    // Save the creation settings.
    settings_ = settings;

    // Create the rendering surface from the owner window.
    createSurface(owner->getSystemHandle(), bitsPerPixel);

    // Create the context.
    createContext(shared);
}

WglContext::WglContext(WglContext* shared, const ContextSettings& settings, u32 width, u32 height) :
    window_(nullptr),
    pbuffer_(nullptr),
    deviceContext_(nullptr),
    context_(nullptr),
    ownsWindow_(false)
{
    priv::ensureInit();

    // Save the creation settings
    settings_ = settings;

    // Create the rendering surface (window or pbuffer if supported)
    createSurface(shared, width, height, VideoMode::getDesktopMode().bitsPerPixel);

    // Create the context
    createContext(shared);
}

WglContext::~WglContext()
{
    // Notify unshared OpenGL resources of context destruction
    cleanupUnsharedResources();

    // Destroy the OpenGL context
    if (context_)
    {
        if (priv::currentContext == this)
        {
            if (wglMakeCurrent(deviceContext_, nullptr) == TRUE)
                priv::currentContext = nullptr;
        }

        wglDeleteContext(context_);
    }

    // Destroy the device context
    if (deviceContext_)
    {
        if (pbuffer_)
        {
            wglReleasePbufferDCARB(pbuffer_, deviceContext_);
            wglDestroyPbufferARB(pbuffer_);
        }
        else
        {
            ReleaseDC(window_, deviceContext_);
        }
    }

    // Destroy the window if we own it
    if (window_ && ownsWindow_)
        DestroyWindow(window_);
}

GlFunctionPointer WglContext::getFunction(const char* name)
{
    GlFunctionPointer address = reinterpret_cast<GlFunctionPointer>(wglGetProcAddress(reinterpret_cast<LPCSTR>(name)));

    if (address)
    {
        // Test whether the returned value is a valid error code
        ptrdiff_t errorCode = reinterpret_cast<ptrdiff_t>(address);

        if ((errorCode != -1) && (errorCode != 1) && (errorCode != 2) && (errorCode != 3))
            return address;
    }

    static HMODULE module = nullptr;

    if (!module)
        module = GetModuleHandleA("OpenGL32.dll");

    if (module)
        return reinterpret_cast<GlFunctionPointer>(GetProcAddress(module, reinterpret_cast<LPCSTR>(name)));

    return 0;
}

bool WglContext::makeCurrent(bool current)
{
    if (!deviceContext_ || !context_)
        return false;

    if (wglMakeCurrent(deviceContext_, current ? context_ : nullptr) == false)
    {
        wcout << L"Failed to " << (current ? L"activate" : L"deactivate") << L" OpenGL context: " << getErrorString(GetLastError()) << endl;
        return false;
    }

    priv::currentContext = (current ? this : nullptr);
    return true;
}

void WglContext::display()
{
    if (deviceContext_ && context_)
        SwapBuffers(deviceContext_);
}

void WglContext::setVerticalSyncEnabled(bool enabled)
{
    // Make sure that extensions are initialized.
    priv::ensureExtensionsInit(deviceContext_);

    if (SF_GLAD_WGL_EXT_swap_control)
    {
        if (wglSwapIntervalEXT(enabled ? 1 : 0) == false)
            wcout << L"Setting vertical sync failed: " << getErrorString(GetLastError()) << endl;
    }
    else
    {
        static bool warned = false;

        if (!warned)
        {
            // wglSwapIntervalEXT not supported.
            cout << "Setting vertical sync not supported." << endl;
            warned = true;
        }
    }
}

int WglContext::selectBestPixelFormat(HDC deviceContext, u32 bitsPerPixel, 
                                      const ContextSettings& settings, bool pbuffer)
{
    priv::ensureInit();

    // Let's find a suitable pixel format -- first try with wglChoosePixelFormatARB
    i32 bestFormat = 0;
    if (SF_GLAD_WGL_ARB_pixel_format)
    {
        // Define the basic attributes we want for our window
        int intAttributes[] =
        {
            WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
            WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
            WGL_DOUBLE_BUFFER_ARB,  GL_TRUE,
            WGL_PIXEL_TYPE_ARB,     WGL_TYPE_RGBA_ARB,
            0,                      0
        };

        // Let's check how many formats are supporting our requirements
        i32  formats[512];
        UINT nbFormats = 0; // We must initialize to 0 otherwise broken drivers might fill with garbage in the following call
        bool isValid = wglChoosePixelFormatARB(deviceContext, intAttributes, nullptr, 512, formats, &nbFormats) != false;

        if (!isValid)
            wcout << L"Failed to enumerate pixel formats: " << getErrorString(GetLastError()) << endl;

        // Get the best format among the returned ones
        if (isValid && (nbFormats > 0))
        {
            i32 bestScore = 0x7FFFFFFF;
            for (UINT i = 0; i < nbFormats; ++i)
            {
                // Extract the components of the current format
                i32 values[7];
                const i32 attributes[] =
                {
                    WGL_RED_BITS_ARB,
                    WGL_GREEN_BITS_ARB,
                    WGL_BLUE_BITS_ARB,
                    WGL_ALPHA_BITS_ARB,
                    WGL_DEPTH_BITS_ARB,
                    WGL_STENCIL_BITS_ARB,
                    WGL_ACCELERATION_ARB
                };

                if (wglGetPixelFormatAttribivARB(deviceContext, formats[i], PFD_MAIN_PLANE, 7, attributes, values) == false)
                {
                    wcout << L"Failed to retrieve pixel format information: " << getErrorString(GetLastError()) << endl;
                    break;
                }

                i32 sampleValues[2] = { 0, 0 };
                if (SF_GLAD_WGL_ARB_multisample)
                {
                    const i32 sampleAttributes[] =
                    {
                        WGL_SAMPLE_BUFFERS_ARB,
                        WGL_SAMPLES_ARB
                    };

                    if (wglGetPixelFormatAttribivARB(deviceContext, formats[i], PFD_MAIN_PLANE, 2, sampleAttributes, sampleValues) == false)
                    {
                        wcout << L"Failed to retrieve pixel format multisampling information: " << getErrorString(GetLastError()) << endl;
                        break;
                    }
                }

                i32 sRgbCapableValue = 0;
                if (SF_GLAD_WGL_ARB_framebuffer_sRGB || SF_GLAD_WGL_EXT_framebuffer_sRGB)
                {
                    const i32 sRgbCapableAttribute = WGL_FRAMEBUFFER_SRGB_CAPABLE_ARB;

                    if (wglGetPixelFormatAttribivARB(deviceContext, formats[i], PFD_MAIN_PLANE, 1, &sRgbCapableAttribute, &sRgbCapableValue) == false)
                    {
                        wcout << L"Failed to retrieve pixel format sRGB capability information: " << getErrorString(GetLastError()) << endl;
                        break;
                    }
                }

                if (pbuffer)
                {
                    const i32 pbufferAttributes[] = { WGL_DRAW_TO_PBUFFER_ARB };

                    i32 pbufferValue = 0;

                    if (wglGetPixelFormatAttribivARB(deviceContext, formats[i], PFD_MAIN_PLANE, 1, pbufferAttributes, &pbufferValue) == false)
                    {
                        wcout << L"Failed to retrieve pixel format pbuffer information: " << getErrorString(GetLastError()) << endl;
                        break;
                    }

                    if (pbufferValue != GL_TRUE)
                        continue;
                }

                // Evaluate the current configuration
                i32 color = values[0] + values[1] + values[2] + values[3];
                i32 score = evaluateFormat(bitsPerPixel, settings, color, values[4], values[5], sampleValues[0] ? sampleValues[1] : 0, values[6] == WGL_FULL_ACCELERATION_ARB, sRgbCapableValue == TRUE);

                // Keep it if it's better than the current best
                if (score < bestScore)
                {
                    bestScore = score;
                    bestFormat = formats[i];
                }
            }
        }
    }

    // ChoosePixelFormat doesn't support pbuffers
    if (pbuffer)
        return bestFormat;

    // Find a pixel format with ChoosePixelFormat, if wglChoosePixelFormatARB is not supported
    if (bestFormat == 0)
    {
        // Setup a pixel format descriptor from the rendering settings
        PIXELFORMATDESCRIPTOR descriptor;
        ZeroMemory(&descriptor, sizeof(descriptor));
        descriptor.nSize = sizeof(descriptor);
        descriptor.nVersion = 1;
        descriptor.iLayerType = PFD_MAIN_PLANE;
        descriptor.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
        descriptor.iPixelType = PFD_TYPE_RGBA;
        descriptor.cColorBits = static_cast<BYTE>(bitsPerPixel);
        descriptor.cDepthBits = static_cast<BYTE>(settings.depthBits);
        descriptor.cStencilBits = static_cast<BYTE>(settings.stencilBits);
        descriptor.cAlphaBits = bitsPerPixel == 32 ? 8 : 0;

        // Get the pixel format that best matches our requirements
        bestFormat = ChoosePixelFormat(deviceContext, &descriptor);
    }

    return bestFormat;
}