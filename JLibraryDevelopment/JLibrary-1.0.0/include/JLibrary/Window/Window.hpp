// JLibraryDevelopment
// Window.hpp
// Created on 2021-07-08 by Justyn Durnford
// Last modified on 2021-07-17 by Justyn Durnford
// Header file for the Window class.

#pragma once

#include <JLibrary/Graphics/GlContext.hpp>
#include <JLibrary/System/Clock.hpp>
#include <JLibrary/System/Cursor.hpp>
#include <JLibrary/Utility/NonCopyable.hpp>
#include <JLibrary/Utility/StringConvert.hpp>
#include <JLibrary/Window/Event.hpp>
#include <JLibrary/Window/VideoMode.hpp>
#include <JLibrary/Window/WindowHandle.hpp>
#include <JLibrary/Window/WindowImpl.hpp>
#include <JLibrary/Window/WindowStyle.hpp>
#include <bitset>
#include <queue>
#include <windows.h>

namespace jlib
{
    class GlContext;
    class WindowImpl;

	// Window that serves as a target for OpenGL rendering.
	class Window : GlResource, NonCopyable
	{
		private:

        u32 width_;
        u32 height_;
        Clock clock_;
        Duration frameTimeLimit_;
		GlContext* context_;
        WindowImpl* impl_;

        // Processes an event before it is sent to the user.
        // This function is called every time an event is received
        // from the internal window (through pollEvent or waitEvent).
        // It filters out unwanted events, and performs whatever internal
        // stuff the window needs before the event is returned to the
        // user.
        bool filterEvent(const Event& event);

        // Performs some common internal initializations.
        void initialize();

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

		protected:

        // Function called after the window has been created.
        // This function is called so that derived classes can
        // perform their own specific initialization as soon as
        // the window is created.
        virtual void onCreate();

        // Function called after the window has been resized.
        // This function is called so that derived classes can
        // perform custom actions when the size of the window changes.
        virtual void onResize();

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

        public:

        // Default constructor.
        // This constructor doesn't actually create the window,
        // use the other constructors or call create() to do so.
        Window();

        // Constructs a new window.
        // This constructor creates the window with the size and pixel
        // depth defined in mode. An optional style can be passed to
        // customize the look and behavior of the window (borders,
        // title bar, resizable, closable, ...). If style contains
        // Style::Fullscreen, then mode must be a valid video mode.
        // The fourth parameter is an optional structure specifying
        // advanced OpenGL context settings such as antialiasing,
        // depth-buffer bits, etc.
        Window(VideoMode mode, const std::wstring& title, i32 style = WindowStyle::Default,
               const ContextSettings& settings = ContextSettings());

        // Constructs the window from an existing control.
        // Use this constructor if you want to create an OpenGL
        // rendering area into an already existing control.
        // The second parameter is an optional structure specifying
        // advanced OpenGL context settings such as antialiasing,
        // depth-buffer bits, etc.
        explicit Window(WindowHandle handle, const ContextSettings& settings = ContextSettings());

        // Destructor.
        // Closes the window and frees all the resources attached to it.
        virtual ~Window();

        // Creates (or recreates) the window.
        // If the window was already created, it closes it first.
        // If style contains Style::Fullscreen, then mode
        // must be a valid video mode.
        // The fourth parameter is an optional structure specifying
        // advanced OpenGL context settings such as antialiasing,
        // depth-buffer bits, etc.
        void create(VideoMode mode, const std::wstring& title, i32 style = WindowStyle::Default,
                    const ContextSettings& settings = ContextSettings());

        // Creates (or recreates) the window from an existing control.
        // Use this function if you want to create an OpenGL
        // rendering area into an already existing control.
        // If the window was already created, it closes it first.
        // The second parameter is an optional structure specifying
        // advanced OpenGL context settings such as antialiasing,
        // depth-buffer bits, etc.
        void create(WindowHandle handle, const ContextSettings& settings = ContextSettings());

        // Closes the window and destroys all the attached resources.
        // After calling this function, the jlib::Window instance remains
        // valid and you can call create() to recreate the window.
        // All other functions such as pollEvent() or display() will
        // still work (i.e. you don't have to test isOpen() every time),
        // and will have no effect on closed windows.
        void close();

        // Returns true if the window is open.
        // This function returns whether or not the window exists.
        // Note that a hidden window (setVisible(false)) is open
        // (therefore this function would return true).
        bool isOpen() const;

        // Gets the settings of the OpenGL context of the window.
        // Note that these settings may be different from what was
        // passed to the constructor or the create() function,
        // if one or more settings were not supported. In this case,
        // SFML chose the closest match.
        const ContextSettings& getSettings() const;

        // Pops the event on top of the event queue, if any, and returns it.
        // This function is not blocking: if there's no pending event then
        // it will return false and leave event unmodified.
        // Note that more than one event may be present in the event queue,
        // thus you should always call this function in a loop
        // to make sure that you process every pending event.
        bool pollEvent(Event& event);

        // Waits for an event and returns it.
        // This function is blocking: if there's no pending event then
        // it will wait until an event is received.
        // After this function returns (and no error occurred),
        // the event object is always valid and filled properly.
        // This function is typically used when you have a thread that
        // is dedicated to events handling: you want to make this thread
        // sleep as long as no new event is received.
        bool waitEvent(Event& event);

        // Gets the position of the window.
        Point2i getPosition() const;

        // Changes the position of the window on screen.
        // This function only works for top-level windows
        // (i.e. it will be ignored for windows created from
        // the handle of a child window/control).
        void setPosition(const Point2i& position);

        // Gets the width of the rendering region of the window.
        // The width doesn't include the titlebar and borders
        // of the window.
        u32 getWidth() const;

        // Sets the width of the rendering region of the window.
        void setWidth(u32 width);

        // Gets the height of the rendering region of the window.
        // The height doesn't include the titlebar and borders
        // of the window.
        u32 getHeight() const;

        // Sets the height of the rendering region of the window.
        void setHeight(u32 height);

        // Changes the size of the rendering region of the window.
        void setSize(u32 width, u32 height);

        // Changes the title of the window.
        void setTitle(const std::wstring& title);

        // Changes the window's icon.
        // pixels must be an array of width x height pixels
        // in 32-bits RGBA format.
        // The OS default icon is used by default.
        void setIcon(u32 width, u32 height, const u8* pixels);

        // Shows or hides the window.
        // The window is shown by default.
        void setVisible(bool visible);

        // Enables or disables vertical synchronization.
        // Activating vertical synchronization will limit the number
        // of frames displayed to the refresh rate of the monitor.
        // This can avoid some visual artifacts, and limit the framerate
        // to a good value (but not constant across different computers).
        // Vertical synchronization is disabled by default.
        void setVerticalSyncEnabled(bool enabled);

        // Shows or hides the mouse cursor.
        // The mouse cursor is visible by default.
        void setMouseCursorVisible(bool visible);

        // Grabs or releases the mouse cursor.
        // If set, grabs the mouse cursor inside this window's client
        // area so it may no longer be moved outside its bounds.
        // Note that grabbing is only active while the window has
        // focus.
        void setMouseCursorGrabbed(bool grabbed);

        // Sets the displayed cursor to a native system cursor.
        // Upon window creation, the arrow cursor is used by default.
        void setMouseCursor(const Cursor& cursor);

        // Enables or disables automatic key-repeat.
        // If key repeat is enabled, you will receive repeated
        // KeyPressed events while keeping a key pressed. If it is disabled,
        // you will only get a single event when the key is pressed.
        // Key repeat is enabled by default.
        void setKeyRepeatEnabled(bool enabled);

        // Limits the framerate to a maximum fixed frequency.
        // If a limit is set, the window will use a small delay after
        // each call to display() to ensure that the current frame
        // lasted long enough to match the framerate limit.
        // The precision depends on the underlying OS, so the results 
        // may be a little unprecise (for example, you can get 65 FPS when
        // requesting 60).
        // Use 0 to disable the limit.
        void setFramerateLimit(u32 limit);

        // Activates or deactivates the window as the current target for OpenGL rendering.
        // A window is active only on the current thread, if you want to
        // make it active on another thread you have to deactivate it
        // on the previous thread first if it was active.
        // Only one window can be active on a thread at a time, thus
        // the window previously active (if any) automatically gets deactivated.
        // This is not to be confused with requestFocus().
        // Returns true if successful.
        bool setActive(bool active = true) const;

        // Checks whether the window has the input focus.
        // At any given time, only one window may have the input focus
        // to receive input events such as keystrokes or most mouse
        // events.
        bool hasFocus() const;

        // Requests the current window to be made the active foreground window.
        // At any given time, only one window may have the input focus
        // to receive input events such as keystrokes or mouse events.
        // If a window requests focus, it only hints to the operating
        // system, that it would like to be focused. The operating system
        // is free to deny the request.
        // This is not to be confused with setActive().
        void requestFocus();

        // Displays on screen what has been rendered to the window so far.
        // This function is typically called after all OpenGL rendering
        // has been done for the current frame, in order to show
        // it on screen.
        void display();

        // Gets the OS-specific handle of the window.
        // You shouldn't need to use this function, unless you have
        // very specific stuff to implement that SFML doesn't support,
        // or implement a temporary workaround until a bug is fixed.
        WindowHandle getSystemHandle() const;
	};
}