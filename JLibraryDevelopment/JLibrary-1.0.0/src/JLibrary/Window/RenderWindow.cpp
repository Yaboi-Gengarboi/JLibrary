// JLibraryDevelopment
// RenderWindow.cpp
// Created on 2021-07-17 by Justyn Durnford
// Last modified on 2021-07-18 by Justyn Durnford
// Source file for the RenderWindow class.

#include <JLibrary/Graphics/RenderTextureImplDefault.hpp>
#include <JLibrary/Graphics/RenderTextureImplFBO.hpp>
#include <JLibrary/Window/RenderWindow.hpp>
using namespace jlib;

#include <iostream>
using std::cout;
using std::endl;

#include <string>
using std::wstring;

void RenderWindow::onCreate()
{
    // Just initialize the render target part.
    RenderTarget::initialize();
}

void RenderWindow::onResize()
{
    // Update the current view (recompute the viewport, which is stored in relative coordinates).
    setView(getView());
}

RenderWindow::RenderWindow() {}

RenderWindow::RenderWindow(VideoMode mode, const wstring & title, u32 style,
                           const ContextSettings& settings)
{
    // Don't call the base class constructor because it contains virtual function calls.
    create(mode, title, style, settings);
}

RenderWindow::RenderWindow(WindowHandle handle, const ContextSettings& settings)
{
    // Don't call the base class constructor because it contains virtual function calls.
    create(handle, settings);
}

RenderWindow::~RenderWindow() {}

u32 RenderWindow::getWidth() const
{
    return Window::getWidth();
}

u32 RenderWindow::getHeight() const
{
    return Window::getHeight();
}

bool RenderWindow::setActive(bool active)
{
    bool result = Window::setActive(active);

    // Update RenderTarget tracking.
    if (result)
        RenderTarget::setActive(active);

    // If FBOs are available, make sure none are bound when we
    // try to draw to the default framebuffer of the RenderWindow.
    if (active && result && RenderTextureImplFBO::isAvailable())
    {
        RenderTextureImplFBO::unbind();
        return true;
    }

    return result;
}