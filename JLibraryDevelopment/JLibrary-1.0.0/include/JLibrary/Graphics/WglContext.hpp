// JLibraryDevelopment
// WglContext.hpp
// Created on 2021-07-10 by Justyn Durnford
// Last modified on 2021-07-16 by Justyn Durnford
// Header file for the WglContext class.

#pragma once

#include <wgl.h>
#include <JLibrary/Graphics/GlContext.hpp>
#include <JLibrary/Window/Window.hpp>

namespace jlib
{
	// Windows (WGL) implementation of OpenGL contexts.
	class WglContext : public GlContext
	{
		HWND        window_;        // Window to which the context is attached.
		HPBUFFERARB pbuffer_;       // Handle to a pbuffer if one was created.
		HDC         deviceContext_; // Device context associated to the context.
		HGLRC       context_;       // OpenGL context.
		bool        ownsWindow_;    // Do we own the target window?

        // Sets the pixel format of the device context.
        void setDevicePixelFormat(u32 bitsPerPixel);

        // Updates the context settings from the selected pixel format.
        void updateSettingsFromPixelFormat();

        // Creates the context's drawing surface.
        void createSurface(WglContext* shared, u32 width, u32 height, u32 bitsPerPixel);

        // Creates the context's drawing surface from an existing window.
        void createSurface(HWND window, u32 bitsPerPixel);

        // Creates the context.
        void createContext(WglContext* shared);

        public:

        // Creates a new default context.
        WglContext(WglContext* shared);

        // Creates a new context attached to a window.
        WglContext(WglContext* shared, const ContextSettings& settings, 
                   const WindowImpl* owner, u32 bitsPerPixel);

        // Creates a new context that embeds its own rendering target.
        WglContext(WglContext* shared, const ContextSettings& settings, u32 width, u32 height);

        // Destructor.
        ~WglContext();

        // Gets the address of an OpenGL function.
        // Returns nullptr on failure.
        static GlFunctionPointer getFunction(const char* name);

        // Activates the context as the current target for rendering.
        // Returns true if successful.
        virtual bool makeCurrent(bool current);

        // Displays what has been rendered to the context so far.
        virtual void display();

        // Enables or disables vertical synchronization.
        // Activating vertical synchronization will limit the number
        // of frames displayed to the refresh rate of the monitor.
        // This can avoid some visual artifacts, and limit the framerate
        // to a good value (but not constant across different computers).
        virtual void setVerticalSyncEnabled(bool enabled);

        // Selects the best pixel format for a given set of settings.
        static i32 selectBestPixelFormat(HDC deviceContext, u32 bitsPerPixel, 
                                         const ContextSettings& settings, bool pbuffer = false);
	};
}