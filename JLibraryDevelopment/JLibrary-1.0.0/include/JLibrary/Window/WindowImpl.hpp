// JLibraryDevelopment
// WindowImpl.hpp
// Created on 2021-07-15 by Justyn Durnford
// Last modified on 2021-07-17 by Justyn Durnford
// Header file for the WindowImpl class.

#pragma once

#include <JLibrary/Window/Window.hpp>
#include <bitset>
#include <queue>
#include <set>

namespace jlib
{
	class WindowListener;

	// Abstract base class for OS-specific window implementation.
	class WindowImpl : NonCopyable
	{
		std::queue<Event> events_;
        HWND     handle_;           // Win32 handle of the window.
        LONG_PTR callback_;         // Stores the original event callback function of the control.
        HCURSOR  lastCursor_;       // Last cursor used -- this data is not owned by the window and is required to be always valid.
        HICON    icon_;             // Custom icon assigned to the window.
        u32      lastWidth_;        // The last handled width of the window.
        u32      lastHeight_;       // The last handles height of the window.
        u16      surrogate_;        // First half of the surrogate pair, in case we're receiving a Unicode character in two events.

        // Flags:
        // - [0]: isCursorVisible     Is the cursor visible or hidden?
        // - [1]: isKeyRepeatEnabled  Is the automatic key-repeat state for keydown events active?
        // - [2]: isResizing          Is the window being resized?
        // - [3]: isMouseInside       Is the mouse is inside the window?
        // - [4]: isFullscreen        Is the window fullscreen?
        // - [5]: isCursorGrabbed     Is the mouse cursor trapped?
        std::bitset<6> flags_;

        // Registers the window class.
        void registerWindowClass();

        // Switches to fullscreen mode.
        void switchToFullscreen(const VideoMode& mode);

        // Frees all the graphical resources attached to the window.
        void cleanup();

        // Enables or disables tracking for the mouse cursor leaving the window.
        void setTracking(bool track);

        // Grabs or releases the mouse cursor.
        // This is not to be confused with setMouseCursorGrabbed.
        // Here isCursorGrabbed (flags_[5]) is not modified; it is used,
        // for example, to release the cursor when switching to
        // another application.
        void grabCursor(bool grabbed);

        // Processes a Win32 event.
        void processEvent(UINT message, WPARAM wParam, LPARAM lParam);

        // Converts a Win32 virtual key code to a JLib key code.
        static Keyboard::Key virtualKeyCodeToSF(WPARAM key, LPARAM flags);

        // Function called whenever one of our windows receives a message.
        static LRESULT CALLBACK globalOnEvent(HWND handle, UINT message, WPARAM wParam, LPARAM lParam);

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

        protected:

        // Pushes a new event into the event queue.
        // This function is to be used by derived classes, to
        // notify the JLib window that a new event was triggered
        // by the system.
        void pushEvent(const Event& event);

        // Processes incoming events from the operating system.
        virtual void processEvents();

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

        public:

        // Default constructor.
        // Constructs the window implementation from an existing control.
        WindowImpl(WindowHandle handle);

        // Creates the window implementation.
        WindowImpl(VideoMode mode, const std::wstring& title, 
                   i32 style, const ContextSettings& settings);

        // Destructor.
        ~WindowImpl();

        // Creates a new window depending on the current OS.
        static WindowImpl* create(VideoMode mode, const std::wstring& title, 
                                  i32 style, const ContextSettings& settings);

        // Creates a new window depending on to the current OS.
        static WindowImpl* create(WindowHandle handle);

        // Returns the next window event available.
        // If there's no event available, this function calls the
        // window's internal event processing function.
        // The block parameter controls the behavior of the function
        // if no event is available: if it is true then the function
        // doesn't return until a new event is triggered; otherwise it
        // returns false to indicate that no event is available.
        bool popEvent(Event& event, bool block);

        // Gets the OS-specific handle of the window.
        virtual WindowHandle getSystemHandle() const;

        // Geta the position of the window.
        virtual Point2i getPosition() const;

        // Changes the position of the window on screen.
        virtual void setPosition(const Point2i& position);

        // Gets the client width of the window.
        virtual u32 getWidth() const;

        // Gets the cilent height of the window.
        virtual u32 getHeight() const;

        // Changes the width and height of the rendering region of the window.
        virtual void setSize(u32 width, u32 height);

        // Changes the title of the window.
        virtual void setTitle(const std::wstring& title);

        // Changes the window's icon.
        virtual void setIcon(u32 width, u32 height, const u8* pixels);

        // Shows or hides the window.
        virtual void setVisible(bool visible);

        // Shows or hides the mouse cursor.
        virtual void setMouseCursorVisible(bool visible);

        // Grabs or releases the mouse cursor.
        virtual void setMouseCursorGrabbed(bool grabbed);

        // Sets the displayed cursor to a native system cursor.
        virtual void setMouseCursor(const Cursor& cursor);

        // Enables or disables automatic key-repeat.
        virtual void setKeyRepeatEnabled(bool enabled);

        // Checks whether the window has the input focus.
        virtual bool hasFocus() const;

        // Requests the current window to be made the active foreground window.
        virtual void requestFocus();
	};
}