// JLibraryDevelopment
// EglContext.hpp
// Created on 2021-07-08 by Justyn Durnford
// Last modified on 2021-07-16 by Justyn Durnford
// Header file for the EglContext class.

#pragma once

#include <egl.h>
#include <JLibrary/Graphics/GlContext.hpp>
#include <JLibrary/Window/Window.hpp>
#include <JLibrary/Window/VideoMode.hpp>

namespace jlib
{
	// Checks the last EGL error.
	void eglCheckError(const char* file, unsigned int line, const char* expression);

	// Macro to quickly check every EGL API call.
	#ifdef _DEBUG

		// In debug mode, perform a test on every EGL call.
		// The do-while loop is needed so that glCheck can be used as a single statement in if/else branches.
		#define eglCheck(expr) do { expr; eglCheckError(__FILE__, __LINE__, #expr); } while (false)

	#else

		// Else, we don't add any overhead.
		#define eglCheck(x) (x)

	#endif // _DEBUG

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

	// 
	class EglContext : public GlContext
	{
		EGLDisplay  display_; // The internal EGL display.
		EGLContext  context_; // The internal EGL context.
		EGLSurface  surface_; // The internal EGL surface.
		EGLConfig   config_;  // The internal EGL config.

		// Helper to copy the picked EGL configuration.
		void updateSettings();

		public:

        // Creates a new context, not associated to a window.
        EglContext(EglContext* shared);

        // Creates a new context attached to a window.
        EglContext(EglContext* shared, const ContextSettings& settings, 
                   const Window* owner, u32 bitsPerPixel);

        // Creates a new context that embeds its own rendering target.
        EglContext(EglContext* shared, const ContextSettings& settings, u32 width, u32 height);

        // Destructor.
        ~EglContext();

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

        // Creates the context.
        void createContext(EglContext* shared);

        // Creates the EGL surface.
        // This function must be called when the activity (re)start, or
        // when the orientation change.
        void createSurface(EGLNativeWindowType window);

        // Destroys the EGL surface.
        // This function must be called when the activity is stopped, or
        // when the orientation change.
        void destroySurface();

        // Gets the best EGL visual for a given set of video settings.
        static EGLConfig getBestConfig(EGLDisplay display, u32 bitsPerPixel, 
                                       const ContextSettings& settings);
	};
}