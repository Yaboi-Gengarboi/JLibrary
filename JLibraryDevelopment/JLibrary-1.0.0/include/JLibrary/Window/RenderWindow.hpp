// JLibraryDevelopment
// RenderWindow.hpp
// Created on 2021-07-17 by Justyn Durnford
// Last modified on 2021-07-17 by Justyn Durnford
// Header file for the RenderWindow class.

#pragma once

#include <JLibrary/Graphics/RenderTarget.hpp>
#include <JLibrary/Window/Window.hpp>

namespace jlib
{
	class RenderWindow : public Window, public RenderTarget
	{
		protected:

		// Function called after the window has been created.
        // This function is called so that derived classes can
        /// perform their own specific initialization as soon as
        /// the window is created.
		virtual void onCreate();

		// Function called after the window has been resized.
        // This function is called so that derived classes can
        // perform custom actions when the size of the window changes.
		virtual void onResize();

		public:

        // Default constructor.
        // This constructor doesn't actually create the window,
        // use the other constructors or call create() to do so.
        RenderWindow();

        // Constructs a new window.
        // This constructor creates the window with the size and pixel
        // depth defined in mode. An optional style can be passed to
        // customize the look and behavior of the window (borders,
        // title bar, resizable, closable, ...).
        // The fourth parameter is an optional structure specifying
        // advanced OpenGL context settings such as antialiasing,
        // depth-buffer bits, etc. You shouldn't care about these
        // parameters for a regular usage of the graphics module.
        RenderWindow(VideoMode mode, const std::wstring & title, u32 style = WindowStyle::Default, 
                     const ContextSettings& settings = ContextSettings());

        // Constructs the window from an existing control.
        // Use this constructor if you want to create a JLib
        // rendering area into an already existing control.
        // The second parameter is an optional structure specifying
        // advanced OpenGL context settings such as antialiasing,
        // depth-buffer bits, etc. You shouldn't care about these
        // parameters for a regular usage of the graphics module.
        explicit RenderWindow(WindowHandle handle, const ContextSettings& settings = ContextSettings());

        // Destructor.
        // Closes the window and frees all the resources attached to it.
        virtual ~RenderWindow();

        // Gets the width of the rendering region of the window.
        // The width doesn't include the titlebar and borders
        // of the window.
        virtual u32 getWidth() const;

        // Gets the height of the rendering region of the window.
        // The height doesn't include the titlebar and borders
        // of the window.
        virtual u32 getHeight() const;

        // Activates or deactivates the window as the current target
        // or OpenGL rendering.
        // A window is active only on the current thread, if you want to
        // make it active on another thread you have to deactivate it
        // on the previous thread first if it was active.
        // Only one window can be active on a thread at a time, thus
        // the window previously active (if any) automatically gets deactivated.
        // This is not to be confused with requestFocus().
        // Returns true if successful.
        bool setActive(bool active = true);
	};
}