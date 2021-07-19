// JLibraryDevelopment
// Window.cpp
// Created on 2021-07-15 by Justyn Durnford
// Last modified on 2021-07-18 by Justyn Durnford
// Source file for the Window class.

#include <JLibrary/Multithread/Sleep.hpp>
#include <JLibrary/Window/Window.hpp>
using namespace jlib;

#include <iostream>
using std::cout;
using std::endl;

#include <string>
using std::wstring;

namespace
{
    const Window* fullscreenWindow = nullptr;
}

bool Window::filterEvent(const Event& event)
{
    // Notify resize events to the derived class.
    if (event.type == Event::Resized)
    {
        // Cache the new size.
        width_ = event.size.width;
        height_ = event.size.height;

        // Notify the derived class.
        onResize();
    }

    return true;
}

void Window::initialize()
{
    // Setup default behaviors.
    setVisible(true);
    setMouseCursorVisible(true);
    setVerticalSyncEnabled(false);
    setKeyRepeatEnabled(true);
    setFramerateLimit(0);

    // Get and cache the initial size of the window.
    width_ = impl_->getWidth();
    height_ = impl_->getHeight();

    // Reset frame time.
    clock_.restart();

    // Activate the window.
    setActive();

    // Notify any derived class.
    onCreate();
}

void Window::onCreate() { /* Nothing by default. */ }

void Window::onResize() { /* Nothing by default. */ }

Window::Window()
{
    width_ = 0;
    height_ = 0;
    frameTimeLimit_ = Duration(0.f);
    context_ = nullptr;
    impl_ = nullptr;
}

Window::Window(VideoMode mode, const wstring& title, i32 style, const ContextSettings& settings)
{
    width_ = 0;
    height_ = 0;
    frameTimeLimit_ = Duration(0.f);
    context_ = nullptr;
    impl_ = nullptr;

	create(mode, title, style, settings);
}

Window::Window(WindowHandle handle, const ContextSettings& settings)
{
    width_ = 0;
    height_ = 0;
    frameTimeLimit_ = Duration(0.f);
    context_ = nullptr;
    impl_ = nullptr;

    create(handle, settings);
}

Window::~Window()
{
	close();
}

void Window::create(VideoMode mode, const wstring& title, i32 style, const ContextSettings& settings)
{
    // Destroy the previous window implementation.
    close();

    // Fullscreen style requires some tests.
    if (style & WindowStyle::Fullscreen)
    {
        // Make sure there's not already a fullscreen window (only one is allowed).
        if (fullscreenWindow != nullptr)
        {
            cout << "Creating two fullscreen windows is not allowed, switching to windowed mode." << endl;
            style = style & ~WindowStyle::Fullscreen;
        }
        else
        {
            // Make sure that the chosen video mode is compatible.
            if (!mode.isValid())
            {
                cout << "The requested video mode is not available, switching to a valid mode." << endl;
                mode = VideoMode::getFullscreenModes()[0];
            }

            // Update the fullscreen window.
            fullscreenWindow = this;
        }
    }

    // Check validity of style.
    if ((style & WindowStyle::Close) || (style & WindowStyle::Resize))
        style |= WindowStyle::Titlebar;

    // Recreate the window implementation.
    impl_ = WindowImpl::create(mode, title, style, settings);

    // Recreate the context.
    context_ = GlContext::create(settings, impl_, mode.bitsPerPixel);

    // Perform common initializations
    initialize();
}

void Window::create(WindowHandle handle, const ContextSettings& settings)
{
    // Destroy the previous window implementation.
    close();

    // Recreate the window implementation.
    impl_ = WindowImpl::create(handle);

    // Recreate the context.
    context_ = GlContext::create(settings, impl_, VideoMode::getDesktopMode().bitsPerPixel);

    // Perform common initializations.
    initialize();
}

void Window::close()
{
    // Delete the context.
    delete context_;
    context_ = NULL;

    // Delete the window implementation.
    delete impl_;
    impl_ = NULL;

    // Update the fullscreen window.
    if (this == fullscreenWindow)
        fullscreenWindow = nullptr;
}

bool Window::isOpen() const
{
    return impl_ != nullptr;
}

const ContextSettings& Window::getSettings() const
{
    static const ContextSettings empty(0, 0, 0);
    return context_ ? context_->settings() : empty;
}

bool Window::pollEvent(Event& event)
{
    if (impl_ && impl_->popEvent(event, false))
        return filterEvent(event);
    return false;
}

bool Window::waitEvent(Event& event)
{
    if (impl_ && impl_->popEvent(event, true))
        return filterEvent(event);
    return false;
}

Point2i Window::getPosition() const
{
    return impl_ ? impl_->getPosition() : Point2i();
}

void Window::setPosition(const Point2i& position)
{
    if (impl_)
        impl_->setPosition(position);
}

u32 Window::getWidth() const
{
    return width_;
}

void Window::setWidth(u32 width)
{
    if (impl_)
    {
        impl_->setSize(width, height_);

        // Cache the new size.
        width_ = width;

        // Notify any derived class.
        onResize();
    }
}

u32 Window::getHeight() const
{
    return height_;
}

void Window::setHeight(u32 height)
{
    if (impl_)
    {
        impl_->setSize(width_, height);

        // Cache the new size.
        height_ = height;

        // Notify any derived class.
        onResize();
    }
}

void Window::setSize(u32 width, u32 height)
{
    if (impl_)
    {
        impl_->setSize(width, height);

        // Cache the new size.
        width_ = width;
        height_ = height;

        // Notify any derived class.
        onResize();
    }
}

void Window::setTitle(const wstring& title)
{
    if (impl_)
        impl_->setTitle(title);
}

void Window::setIcon(u32 width, u32 height, const u8* pixels)
{
    if (impl_)
        impl_->setIcon(width, height, pixels);
}

void Window::setVisible(bool visible)
{
    if (impl_)
        impl_->setVisible(visible);
}

void Window::setVerticalSyncEnabled(bool enabled)
{
    if (setActive())
        context_->setVerticalSyncEnabled(enabled);
}

void Window::setMouseCursorVisible(bool visible)
{
    if (impl_)
        impl_->setMouseCursorVisible(visible);
}

void Window::setMouseCursorGrabbed(bool grabbed)
{
    if (impl_)
        impl_->setMouseCursorGrabbed(grabbed);
}

void Window::setMouseCursor(const Cursor& cursor)
{
    if (impl_)
        impl_->setMouseCursor(cursor);
}

void Window::setKeyRepeatEnabled(bool enabled)
{
    if (impl_)
        impl_->setKeyRepeatEnabled(enabled);
}

void Window::setFramerateLimit(u32 limit)
{
    if (limit > 0)
        frameTimeLimit_ = Duration(1.f / limit);
    else
        frameTimeLimit_ = Duration(0.f);
}

bool Window::setActive(bool active) const
{
    if (context_)
    {
        if (context_->setActive(active))
            return true;
        else
        {
            cout << "Failed to activate the window's context" << endl;
            return false;
        }
    }
    else
        return false;
}

bool Window::hasFocus() const
{
    return impl_ && impl_->hasFocus();
}

void Window::requestFocus()
{
    if (impl_)
        impl_->requestFocus();
}

void Window::display()
{
    // Display the backbuffer on screen.
    if (setActive())
        context_->display();

    // Limit the framerate if needed.
    if (frameTimeLimit_ != TimeZero)
    {
        sleep(frameTimeLimit_ - clock_.timeElapsed());
        clock_.restart();
    }
}

WindowHandle Window::getSystemHandle() const
{
    return impl_ ? impl_->getSystemHandle() : 0;
}