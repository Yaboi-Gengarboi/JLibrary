// JLibraryDevelopment
// WindowImpl.cpp
// Created on 2021-07-15 by Justyn Durnford
// Last modified on 2021-07-17 by Justyn Durnford
// Source file for the WindowImpl class.

#pragma once

#ifdef _WIN32_WINDOWS
	#undef _WIN32_WINDOWS
#endif

#ifdef _WIN32_WINNT
	#undef _WIN32_WINNT
#endif

#define _WIN32_WINDOWS 0x0501
#define _WIN32_WINNT   0x0501
#define WINVER         0x0501

#include <JLibrary/Multithread/Sleep.hpp>
#include <JLibrary/Utility/Array.hpp>
#include <JLibrary/Utility/UTF.hpp>
#include <JLibrary/Window/WindowImpl.hpp>
#include <JLibrary/Window/WindowStyle.hpp>
using namespace jlib;

#include <cstring>
using std::size_t;

#include <iostream>
using std::cout;
using std::endl;

#include <string>
using std::wstring;

#include <vector>





// MinGW lacks the definition of some Win32 constants.
#ifndef XBUTTON1
	#define XBUTTON1 0x0001
#endif

#ifndef XBUTTON2
	#define XBUTTON2 0x0002
#endif

#ifndef WM_MOUSEHWHEEL
	#define WM_MOUSEHWHEEL 0x020E
#endif

#ifndef MAPVK_VK_TO_VSC
	#define MAPVK_VK_TO_VSC (0)
#endif

namespace
{
    u32                        windowCount = 0; // Windows owned by JLib.
    u32                        handleCount = 0; // All window handles.
    const wchar_t* className = L"JLib_Window";
    WindowImpl*                fullscreenWindow = nullptr;

    const GUID GUID_DEVINTERFACE_HID = { 0x4d1e55b2, 0xf16f, 0x11cf, { 0x88, 0xcb, 0x00, 0x11, 0x11, 0x00, 0x00, 0x30 } };

    void setProcessDpiAware()
    {
        // Try SetProcessDpiAwareness first.
        HINSTANCE shCoreDll = LoadLibrary(L"Shcore.dll");

        if (shCoreDll)
        {
            enum ProcessDpiAwareness
            {
                ProcessDpiUnaware = 0,
                ProcessSystemDpiAware = 1,
                ProcessPerMonitorDpiAware = 2
            };

            typedef HRESULT(WINAPI* SetProcessDpiAwarenessFuncType)(ProcessDpiAwareness);
            SetProcessDpiAwarenessFuncType SetProcessDpiAwarenessFunc = reinterpret_cast<SetProcessDpiAwarenessFuncType>(GetProcAddress(shCoreDll, "SetProcessDpiAwareness"));

            if (SetProcessDpiAwarenessFunc)
            {
                // We only check for E_INVALIDARG because we would get
                // E_ACCESSDENIED if the DPI was already set previously
                // and S_OK means the call was successful.
                if (SetProcessDpiAwarenessFunc(ProcessSystemDpiAware) == E_INVALIDARG)
                    cout << "Failed to set process DPI awareness" << endl;
                else
                {
                    FreeLibrary(shCoreDll);
                    return;
                }
            }

            FreeLibrary(shCoreDll);
        }

        // Fall back to SetProcessDPIAware if SetProcessDpiAwareness
        // is not available on this system.
        HINSTANCE user32Dll = LoadLibrary(L"user32.dll");

        if (user32Dll)
        {
            typedef BOOL(WINAPI* SetProcessDPIAwareFuncType)(void);
            SetProcessDPIAwareFuncType SetProcessDPIAwareFunc = reinterpret_cast<SetProcessDPIAwareFuncType>(GetProcAddress(user32Dll, "SetProcessDPIAware"));

            if (SetProcessDPIAwareFunc)
            {
                if (!SetProcessDPIAwareFunc())
                    cout << "Failed to set process DPI awareness" << endl;
            }

            FreeLibrary(user32Dll);
        }
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

void WindowImpl::registerWindowClass()
{
    WNDCLASSW windowClass;
    windowClass.style = 0;
    windowClass.lpfnWndProc = &WindowImpl::globalOnEvent;
    windowClass.cbClsExtra = 0;
    windowClass.cbWndExtra = 0;
    windowClass.hInstance = GetModuleHandleW(nullptr);
    windowClass.hIcon = nullptr;
    windowClass.hCursor = 0;
    windowClass.hbrBackground = 0;
    windowClass.lpszMenuName = nullptr;
    windowClass.lpszClassName = className;
    RegisterClassW(&windowClass);
}

void WindowImpl::switchToFullscreen(const VideoMode& mode)
{
    DEVMODE devMode;
    devMode.dmSize = sizeof(devMode);
    devMode.dmPelsWidth = mode.width;
    devMode.dmPelsHeight = mode.height;
    devMode.dmBitsPerPel = mode.bitsPerPixel;
    devMode.dmFields = DM_PELSWIDTH | DM_PELSHEIGHT | DM_BITSPERPEL;

    // Apply fullscreen mode.
    if (ChangeDisplaySettingsW(&devMode, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
    {
        cout << "Failed to change display mode for fullscreen." << endl;
        return;
    }

    // Make the window flags compatible with fullscreen mode.
    SetWindowLongW(handle_, GWL_STYLE, WS_POPUP | WS_CLIPCHILDREN | WS_CLIPSIBLINGS);
    SetWindowLongW(handle_, GWL_EXSTYLE, WS_EX_APPWINDOW);

    // Resize the window so that it fits the entire screen.
    SetWindowPos(handle_, HWND_TOP, 0, 0, mode.width, mode.height, SWP_FRAMECHANGED);
    ShowWindow(handle_, SW_SHOW);

    // Set "this" as the current fullscreen window.
    fullscreenWindow = this;
}

void WindowImpl::cleanup()
{
    // Restore the previous video mode (in case we were running in fullscreen).
    if (fullscreenWindow == this)
    {
        ChangeDisplaySettingsW(nullptr, 0);
        fullscreenWindow = nullptr;
    }

    // Unhide the mouse cursor (in case it was hidden).
    setMouseCursorVisible(true);

    // No longer track the cursor.
    setTracking(false);

    // No longer capture the cursor.
    ReleaseCapture();
}

void WindowImpl::setTracking(bool track)
{
    TRACKMOUSEEVENT mouseEvent;
    mouseEvent.cbSize = sizeof(TRACKMOUSEEVENT);
    mouseEvent.dwFlags = track ? TME_LEAVE : TME_CANCEL;
    mouseEvent.hwndTrack = handle_;
    mouseEvent.dwHoverTime = HOVER_DEFAULT;
    TrackMouseEvent(&mouseEvent);
}

void WindowImpl::grabCursor(bool grabbed)
{
    if (grabbed)
    {
        RECT rect;
        GetClientRect(handle_, &rect);
        MapWindowPoints(handle_, nullptr, reinterpret_cast<LPPOINT>(&rect), 2);
        ClipCursor(&rect);
    }
    else
        ClipCursor(nullptr);
}

void WindowImpl::processEvent(UINT message, WPARAM wParam, LPARAM lParam)
{
    // Don't process any message until window is created.
    if (handle_ == nullptr)
        return;

    switch (message)
    {
        // Destroy event.
        case WM_DESTROY:
        {
            // Here we must cleanup resources!
            cleanup();
            break;
        }

        // Set cursor event.
        case WM_SETCURSOR:
        {
            // The mouse has moved, if the cursor is in our window we must refresh the cursor.
            if (LOWORD(lParam) == HTCLIENT)
                SetCursor(lastCursor_);
            break;
        }

        // Close event.
        case WM_CLOSE:
        {
            Event event;
            event.type = Event::Closed;
            pushEvent(event);
            break;
        }

        // Resize event.
        case WM_SIZE:
        {
            // Consider only events triggered by a maximize or a un-maximize.
            if (wParam != SIZE_MINIMIZED && !flags_[2] && (lastWidth_ != getWidth()) && (lastHeight_ != getHeight()))
            {
                // Update the last handled size.
                lastWidth_ = getWidth();
                lastHeight_ = getHeight();

                // Push a resize event.
                Event event;
                event.type = Event::Resized;
                event.size.width = lastWidth_;
                event.size.height = lastHeight_;
                pushEvent(event);

                // Restore/update cursor grabbing.
                grabCursor(flags_[5]);
            }
            break;
        }

        // Start resizing.
        case WM_ENTERSIZEMOVE:
        {
            flags_[2] = true;
            grabCursor(false);
            break;
        }

        // Stop resizing.
        case WM_EXITSIZEMOVE:
        {
            flags_[2] = false;

            // Ignore cases where the window has only been moved.
            if (lastWidth_ != getWidth() && lastHeight_ != getHeight())
            {
                // Update the last handled size.
                lastWidth_ = getWidth();
                lastHeight_ = getHeight();

                // Push a resize event.
                Event event;
                event.type = Event::Resized;
                event.size.width = lastWidth_;
                event.size.height = lastHeight_;
                pushEvent(event);
            }

            // Restore/update cursor grabbing.
            grabCursor(flags_[5]);
            break;
        }

        // The system request the min/max window size and position.
        case WM_GETMINMAXINFO:
        {
            // We override the returned information to remove the default limit
            // (the OS doesn't allow windows bigger than the desktop by default).
            MINMAXINFO* info = reinterpret_cast<MINMAXINFO*>(lParam);
            info->ptMaxTrackSize.x = 50000;
            info->ptMaxTrackSize.y = 50000;
            break;
        }

        // Gain focus event.
        case WM_SETFOCUS:
        {
            // Restore cursor grabbing.
            grabCursor(flags_[5]);

            Event event;
            event.type = Event::GainedFocus;
            pushEvent(event);
            break;
        }

        // Lost focus event.
        case WM_KILLFOCUS:
        {
            // Ungrab the cursor
            grabCursor(false);

            Event event;
            event.type = Event::LostFocus;
            pushEvent(event);
            break;
        }

        // Text event.
        case WM_CHAR:
        {
            if (flags_[1] || ((lParam & (1 << 30)) == 0))
            {
                // Get the code of the typed character.
                u32 character = static_cast<u32>(wParam);

                // Check if it is the first part of a surrogate pair, or a regular character.
                if ((character >= 0xD800) && (character <= 0xDBFF))
                {
                    // First part of a surrogate pair: store it and wait for the second one.
                    surrogate_ = static_cast<u16>(character);
                }
                else
                {
                    // Check if it is the second part of a surrogate pair, or a regular character.
                    if ((character >= 0xDC00) && (character <= 0xDFFF))
                    {
                        // Convert the UTF-16 surrogate pair to a single UTF-32 value.
                        u16 utf16[] = { surrogate_, static_cast<u16>(character) };
                        UTF16::toUTF32(utf16, utf16 + 2, &character);
                        surrogate_ = 0;
                    }

                    // Send a TextEntered event.
                    Event event;
                    event.type = Event::TextEntered;
                    event.text.unicode = character;
                    pushEvent(event);
                }
            }
            break;
        }

        // Keydown event.
        case WM_KEYDOWN:
        case WM_SYSKEYDOWN:
        {
            if (flags_[1] || ((HIWORD(lParam) & KF_REPEAT) == 0))
            {
                Event event;
                event.type = Event::KeyPressed;
                event.key.flags[0] = HIWORD(GetKeyState(VK_MENU)) != 0;
                event.key.flags[1] = HIWORD(GetKeyState(VK_CONTROL)) != 0;
                event.key.flags[2] = HIWORD(GetKeyState(VK_SHIFT)) != 0;
                event.key.flags[3] = HIWORD(GetKeyState(VK_LWIN)) || HIWORD(GetKeyState(VK_RWIN));
                event.key.code = virtualKeyCodeToSF(wParam, lParam);
                pushEvent(event);
            }
            break;
        }

        // Keyup event.
        case WM_KEYUP:
        case WM_SYSKEYUP:
        {
            Event event;
            event.type = Event::KeyReleased;
            event.key.flags[0] = HIWORD(GetKeyState(VK_MENU)) != 0;
            event.key.flags[1] = HIWORD(GetKeyState(VK_CONTROL)) != 0;
            event.key.flags[2] = HIWORD(GetKeyState(VK_SHIFT)) != 0;
            event.key.flags[3] = HIWORD(GetKeyState(VK_LWIN)) || HIWORD(GetKeyState(VK_RWIN));
            event.key.code = virtualKeyCodeToSF(wParam, lParam);
            pushEvent(event);
            break;
        }

        // Vertical mouse wheel event.
        case WM_MOUSEWHEEL:
        {
            // Mouse position is in screen coordinates, convert it to window coordinates.
            POINT position;
            position.x = static_cast<i16>(LOWORD(lParam));
            position.y = static_cast<i16>(HIWORD(lParam));
            ScreenToClient(handle_, &position);

            i16 delta = static_cast<i16>(HIWORD(wParam));

            Event event;

            event.type = Event::MouseWheelMoved;
            event.mouseWheel.delta = delta / 120;
            event.mouseWheel.x = position.x;
            event.mouseWheel.y = position.y;
            pushEvent(event);

            event.type = Event::MouseWheelScrolled;
            event.mouseWheelScroll.wheel = Mouse::VerticalWheel;
            event.mouseWheelScroll.delta = static_cast<float>(delta) / 120.f;
            event.mouseWheelScroll.x = position.x;
            event.mouseWheelScroll.y = position.y;
            pushEvent(event);
            break;
        }

        // Horizontal mouse wheel event.
        case WM_MOUSEHWHEEL:
        {
            // Mouse position is in screen coordinates, convert it to window coordinates.
            POINT position;
            position.x = static_cast<i16>(LOWORD(lParam));
            position.y = static_cast<i16>(HIWORD(lParam));
            ScreenToClient(handle_, &position);

            i16 delta = static_cast<i16>(HIWORD(wParam));

            Event event;
            event.type = Event::MouseWheelScrolled;
            event.mouseWheelScroll.wheel = Mouse::HorizontalWheel;
            event.mouseWheelScroll.delta = -static_cast<float>(delta) / 120.f;
            event.mouseWheelScroll.x = position.x;
            event.mouseWheelScroll.y = position.y;
            pushEvent(event);
            break;
        }

        // Mouse left button down event.
        case WM_LBUTTONDOWN:
        {
            Event event;
            event.type = Event::MouseButtonPressed;
            event.mouseButton.button = Mouse::Left;
            event.mouseButton.x = static_cast<i16>(LOWORD(lParam));
            event.mouseButton.y = static_cast<i16>(HIWORD(lParam));
            pushEvent(event);
            break;
        }

        // Mouse left button up event.
        case WM_LBUTTONUP:
        {
            Event event;
            event.type = Event::MouseButtonReleased;
            event.mouseButton.button = Mouse::Left;
            event.mouseButton.x = static_cast<i16>(LOWORD(lParam));
            event.mouseButton.y = static_cast<i16>(HIWORD(lParam));
            pushEvent(event);
            break;
        }

        // Mouse right button down event.
        case WM_RBUTTONDOWN:
        {
            Event event;
            event.type = Event::MouseButtonPressed;
            event.mouseButton.button = Mouse::Right;
            event.mouseButton.x = static_cast<i16>(LOWORD(lParam));
            event.mouseButton.y = static_cast<i16>(HIWORD(lParam));
            pushEvent(event);
            break;
        }

        // Mouse right button up event.
        case WM_RBUTTONUP:
        {
            Event event;
            event.type = Event::MouseButtonReleased;
            event.mouseButton.button = Mouse::Right;
            event.mouseButton.x = static_cast<i16>(LOWORD(lParam));
            event.mouseButton.y = static_cast<i16>(HIWORD(lParam));
            pushEvent(event);
            break;
        }

        // Mouse wheel button down event.
        case WM_MBUTTONDOWN:
        {
            Event event;
            event.type = Event::MouseButtonPressed;
            event.mouseButton.button = Mouse::Middle;
            event.mouseButton.x = static_cast<i16>(LOWORD(lParam));
            event.mouseButton.y = static_cast<i16>(HIWORD(lParam));
            pushEvent(event);
            break;
        }

        // Mouse wheel button up event.
        case WM_MBUTTONUP:
        {
            Event event;
            event.type = Event::MouseButtonReleased;
            event.mouseButton.button = Mouse::Middle;
            event.mouseButton.x = static_cast<i16>(LOWORD(lParam));
            event.mouseButton.y = static_cast<i16>(HIWORD(lParam));
            pushEvent(event);
            break;
        }

        // Mouse leave event.
        case WM_MOUSELEAVE:
        {
            // Avoid this firing a second time in case the cursor is dragged outside.
            if (flags_[3])
            {
                flags_[3] = false;

                // Generate a MouseLeft event.
                Event event;
                event.type = Event::MouseLeft;
                pushEvent(event);
            }
            break;
        }

        // Mouse move event.
        case WM_MOUSEMOVE:
        {
            // Extract the mouse local coordinates.
            int x = static_cast<i16>(LOWORD(lParam));
            int y = static_cast<i16>(HIWORD(lParam));

            // Get the client area of the window.
            RECT area;
            GetClientRect(handle_, &area);

            // Capture the mouse in case the user wants to drag it outside.
            if ((wParam & (MK_LBUTTON | MK_MBUTTON | MK_RBUTTON | MK_XBUTTON1 | MK_XBUTTON2)) == 0)
            {
                // Only release the capture if we really have it.
                if (GetCapture() == handle_)
                    ReleaseCapture();
            }
            else if (GetCapture() != handle_)
            {
                // Set the capture to continue receiving mouse events.
                SetCapture(handle_);
            }

            // If the cursor is outside the client area...
            if ((x < area.left) || (x > area.right) || (y < area.top) || (y > area.bottom))
            {
                // and it used to be inside, the mouse left it.
                if (flags_[3])
                {
                    flags_[3] = false;

                    // No longer care for the mouse leaving the window.
                    setTracking(false);

                    // Generate a MouseLeft event.
                    Event event;
                    event.type = Event::MouseLeft;
                    pushEvent(event);
                }
            }
            else
            {
                // and vice-versa.
                if (!flags_[3])
                {
                    flags_[3] = true;

                    // Look for the mouse leaving the window.
                    setTracking(true);

                    // Generate a MouseEntered event.
                    Event event;
                    event.type = Event::MouseEntered;
                    pushEvent(event);
                }
            }

            // Generate a MouseMove event.
            Event event;
            event.type = Event::MouseMoved;
            event.mouseMove.x = x;
            event.mouseMove.y = y;
            pushEvent(event);
            break;
        }
    }
}

void WindowImpl::pushEvent(const Event& event)
{
    events_.push(event);
}

void WindowImpl::processEvents()
{
    // We process the window events only if we own it.
    if (!callback_)
    {
        MSG message;
        while (PeekMessageW(&message, nullptr, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&message);
            DispatchMessageW(&message);
        }
    }
}

WindowImpl::WindowImpl(WindowHandle handle)
{
    handle_ = handle;
    callback_ = 0;
    lastCursor_ = LoadCursor(nullptr, IDC_ARROW);
    icon_ = nullptr;
    lastWidth_ = 0;
    lastHeight_ = 0;
    surrogate_ = 0;

    flags_[0] = true;
    flags_[1] = true;

    // Set that this process is DPI aware and can handle DPI scaling.
    setProcessDpiAware();

    if (handle_ != nullptr)
    {
        ++handleCount;

        // We change the event procedure of the control (it is important to save the old one).
        SetWindowLongPtrW(handle_, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));
        callback_ = SetWindowLongPtrW(handle_, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&WindowImpl::globalOnEvent));
    }
}

WindowImpl::WindowImpl(VideoMode mode, const wstring& title, 
                       i32 style, const ContextSettings& settings)
{
    handle_ = nullptr;
    callback_ = 0;
    lastCursor_ = LoadCursor(nullptr, IDC_ARROW);
    icon_ = nullptr;
    lastWidth_ = mode.width;
    lastHeight_ = mode.height;
    surrogate_ = 0;

    flags_[0] = true;
    flags_[1] = true;
    flags_[4] = ((style & WindowStyle::Fullscreen) != 0);
    flags_[5] = flags_[4];

    // Set that this process is DPI aware and can handle DPI scaling.
    setProcessDpiAware();

    // Register the window class at first call.
    if (windowCount == 0)
        registerWindowClass();

    // Compute position and size.
    HDC screenDC = GetDC(nullptr);
    int left = (GetDeviceCaps(screenDC, HORZRES) - static_cast<int>(mode.width)) / 2;
    int top = (GetDeviceCaps(screenDC, VERTRES) - static_cast<int>(mode.height)) / 2;
    int width = mode.width;
    int height = mode.height;
    ReleaseDC(nullptr, screenDC);

    // Choose the window style according to the Style parameter.
    DWORD win32Style = WS_VISIBLE;
    if (style == WindowStyle::None)
        win32Style |= WS_POPUP;
    else
    {
        if (style & WindowStyle::Titlebar) win32Style |= WS_CAPTION | WS_MINIMIZEBOX;
        if (style & WindowStyle::Resize)   win32Style |= WS_THICKFRAME | WS_MAXIMIZEBOX;
        if (style & WindowStyle::Close)    win32Style |= WS_SYSMENU;
    }

    // In windowed mode, adjust width and height so that window will have the requested client area.
    if (!flags_[4])
    {
        RECT rectangle = { 0, 0, width, height };
        AdjustWindowRect(&rectangle, win32Style, false);
        width = rectangle.right - rectangle.left;
        height = rectangle.bottom - rectangle.top;
    }

    // Create the window
    handle_ = CreateWindowW(className, title.data(), win32Style, left, top, width, height, nullptr, nullptr, GetModuleHandle(nullptr), this);

    if (handle_ != nullptr)
        ++handleCount;

    // By default, the OS limits the size of the window the the desktop size,
    // we have to resize it after creation to apply the real size.
    setSize(mode.width, mode.height);

    // Switch to fullscreen if requested.
    if (flags_[4])
        switchToFullscreen(mode);

    // Increment window count.
    windowCount++;
}

Keyboard::Key WindowImpl::virtualKeyCodeToSF(WPARAM key, LPARAM flags)
{
    switch (key)
    {
        // Check the scancode to distinguish between left and right shift
        case VK_SHIFT:
        {
            static UINT lShift = MapVirtualKeyW(VK_LSHIFT, MAPVK_VK_TO_VSC);
            UINT scancode = static_cast<UINT>((flags & (0xFF << 16)) >> 16);
            return scancode == lShift ? Keyboard::LShift : Keyboard::RShift;
        }

        // Check the "extended" flag to distinguish between left and right alt
        case VK_MENU: return (HIWORD(flags) & KF_EXTENDED) ? Keyboard::RAlt : Keyboard::LAlt;

        // Check the "extended" flag to distinguish between left and right control
        case VK_CONTROL: return (HIWORD(flags) & KF_EXTENDED) ? Keyboard::RControl : Keyboard::LControl;

        // Other keys are reported properly
        case VK_LWIN:       return Keyboard::LWindow;
        case VK_RWIN:       return Keyboard::RWindow;
        case VK_APPS:       return Keyboard::Menu;
        case VK_OEM_1:      return Keyboard::Semicolon;
        case VK_OEM_2:      return Keyboard::Slash;
        case VK_OEM_PLUS:   return Keyboard::Equal;
        case VK_OEM_MINUS:  return Keyboard::Hyphen;
        case VK_OEM_4:      return Keyboard::LBracket;
        case VK_OEM_6:      return Keyboard::RBracket;
        case VK_OEM_COMMA:  return Keyboard::Comma;
        case VK_OEM_PERIOD: return Keyboard::Period;
        case VK_OEM_7:      return Keyboard::Quote;
        case VK_OEM_5:      return Keyboard::Backslash;
        case VK_OEM_3:      return Keyboard::Tilde;
        case VK_ESCAPE:     return Keyboard::Escape;
        case VK_SPACE:      return Keyboard::Space;
        case VK_RETURN:     return Keyboard::Enter;
        case VK_BACK:       return Keyboard::Backspace;
        case VK_TAB:        return Keyboard::Tab;
        case VK_PRIOR:      return Keyboard::PageUp;
        case VK_NEXT:       return Keyboard::PageDown;
        case VK_END:        return Keyboard::End;
        case VK_HOME:       return Keyboard::Home;
        case VK_INSERT:     return Keyboard::Insert;
        case VK_DELETE:     return Keyboard::Delete;
        case VK_ADD:        return Keyboard::Add;
        case VK_SUBTRACT:   return Keyboard::Subtract;
        case VK_MULTIPLY:   return Keyboard::Multiply;
        case VK_DIVIDE:     return Keyboard::Divide;
        case VK_PAUSE:      return Keyboard::Pause;
        case VK_F1:         return Keyboard::F1;
        case VK_F2:         return Keyboard::F2;
        case VK_F3:         return Keyboard::F3;
        case VK_F4:         return Keyboard::F4;
        case VK_F5:         return Keyboard::F5;
        case VK_F6:         return Keyboard::F6;
        case VK_F7:         return Keyboard::F7;
        case VK_F8:         return Keyboard::F8;
        case VK_F9:         return Keyboard::F9;
        case VK_F10:        return Keyboard::F10;
        case VK_F11:        return Keyboard::F11;
        case VK_F12:        return Keyboard::F12;
        case VK_F13:        return Keyboard::F13;
        case VK_F14:        return Keyboard::F14;
        case VK_F15:        return Keyboard::F15;
        case VK_LEFT:       return Keyboard::Left;
        case VK_RIGHT:      return Keyboard::Right;
        case VK_UP:         return Keyboard::Up;
        case VK_DOWN:       return Keyboard::Down;
        case VK_NUMPAD0:    return Keyboard::Numpad0;
        case VK_NUMPAD1:    return Keyboard::Numpad1;
        case VK_NUMPAD2:    return Keyboard::Numpad2;
        case VK_NUMPAD3:    return Keyboard::Numpad3;
        case VK_NUMPAD4:    return Keyboard::Numpad4;
        case VK_NUMPAD5:    return Keyboard::Numpad5;
        case VK_NUMPAD6:    return Keyboard::Numpad6;
        case VK_NUMPAD7:    return Keyboard::Numpad7;
        case VK_NUMPAD8:    return Keyboard::Numpad8;
        case VK_NUMPAD9:    return Keyboard::Numpad9;
        case 'A':           return Keyboard::A;
        case 'Z':           return Keyboard::Z;
        case 'E':           return Keyboard::E;
        case 'R':           return Keyboard::R;
        case 'T':           return Keyboard::T;
        case 'Y':           return Keyboard::Y;
        case 'U':           return Keyboard::U;
        case 'I':           return Keyboard::I;
        case 'O':           return Keyboard::O;
        case 'P':           return Keyboard::P;
        case 'Q':           return Keyboard::Q;
        case 'S':           return Keyboard::S;
        case 'D':           return Keyboard::D;
        case 'F':           return Keyboard::F;
        case 'G':           return Keyboard::G;
        case 'H':           return Keyboard::H;
        case 'J':           return Keyboard::J;
        case 'K':           return Keyboard::K;
        case 'L':           return Keyboard::L;
        case 'M':           return Keyboard::M;
        case 'W':           return Keyboard::W;
        case 'X':           return Keyboard::X;
        case 'C':           return Keyboard::C;
        case 'V':           return Keyboard::V;
        case 'B':           return Keyboard::B;
        case 'N':           return Keyboard::N;
        case '0':           return Keyboard::Num0;
        case '1':           return Keyboard::Num1;
        case '2':           return Keyboard::Num2;
        case '3':           return Keyboard::Num3;
        case '4':           return Keyboard::Num4;
        case '5':           return Keyboard::Num5;
        case '6':           return Keyboard::Num6;
        case '7':           return Keyboard::Num7;
        case '8':           return Keyboard::Num8;
        case '9':           return Keyboard::Num9;
    }

    return Keyboard::Unknown;
}

LRESULT CALLBACK WindowImpl::globalOnEvent(HWND handle, UINT message, WPARAM wParam, LPARAM lParam)
{
    // Associate handle and Window instance when the creation message is received.
    if (message == WM_CREATE)
    {
        // Get WindowImplWin32 instance (it was passed as the last argument of CreateWindow).
        LONG_PTR window = (LONG_PTR)reinterpret_cast<CREATESTRUCT*>(lParam)->lpCreateParams;

        // Set as the "user data" parameter of the window.
        SetWindowLongPtrW(handle, GWLP_USERDATA, window);
    }

    // Get the WindowImpl instance corresponding to the window handle.
    WindowImpl* window = handle ? reinterpret_cast<WindowImpl*>(GetWindowLongPtr(handle, GWLP_USERDATA)) : nullptr;

    // Forward the event to the appropriate function.
    if (window)
    {
        window->processEvent(message, wParam, lParam);

        if (window->callback_)
            return CallWindowProcW(reinterpret_cast<WNDPROC>(window->callback_), handle, message, wParam, lParam);
    }

    // We don't forward the WM_CLOSE message to prevent the OS from automatically destroying the window.
    if (message == WM_CLOSE)
        return 0;

    // Don't forward the menu system command, so that pressing ALT or F10 doesn't steal the focus.
    if ((message == WM_SYSCOMMAND) && (wParam == SC_KEYMENU))
        return 0;

    return DefWindowProcW(handle, message, wParam, lParam);
}

WindowImpl::~WindowImpl()
{
    // Destroy the custom icon, if any.
    if (icon_)
        DestroyIcon(icon_);

    if (handle_)
        --handleCount;

    if (!callback_)
    {
        // Destroy the window.
        if (handle_)
            DestroyWindow(handle_);

        // Decrement the window count.
        windowCount--;

        // Unregister window class if we were the last window.
        if (windowCount == 0)
            UnregisterClassW(className, GetModuleHandleW(nullptr));
    }
    else // The window is external: remove the hook on its message callback
        SetWindowLongPtrW(handle_, GWLP_WNDPROC, callback_);
}

WindowImpl* WindowImpl::create(VideoMode mode, const wstring& title,
                               i32 style, const ContextSettings& settings)
{
    return new WindowImpl(mode, title, style, settings);
}

WindowImpl* WindowImpl::create(WindowHandle handle)
{
    return new WindowImpl(handle);
}

bool WindowImpl::popEvent(Event& event, bool block)
{
    // If the event queue is empty, let's first check if new events are available from the OS.
    if (events_.empty())
    {
        // Get events from the system.
        processEvents();

        // In blocking mode, we must process events until one is triggered.
        if (block)
        {
            // Here we use a manual wait loop instead of the optimized
            // wait-event provided by the OS, so that we don't events
            // which require polling.
            while (events_.empty())
            {
                sleep(Duration(10.f));
                processEvents();
            }
        }
    }

    // Pop the first event of the queue, if it is not empty.
    if (!events_.empty())
    {
        event = events_.front();
        events_.pop();

        return true;
    }

    return false;
}

WindowHandle WindowImpl::getSystemHandle() const
{
    return handle_;
}

Point2i WindowImpl::getPosition() const
{
    RECT rect;
    GetWindowRect(handle_, &rect);
    return Point2i(rect.left, rect.top);
}

void WindowImpl::setPosition(const Point2i& position)
{
    SetWindowPos(handle_, nullptr, position.x, position.y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

    if (flags_[5])
        grabCursor(true);
}

u32 WindowImpl::getWidth() const
{
    RECT rect;
    GetClientRect(handle_, &rect);
    return rect.right - rect.left;
}

u32 WindowImpl::getHeight() const
{
    RECT rect;
    GetClientRect(handle_, &rect);
    return rect.bottom - rect.top;
}

void WindowImpl::setSize(u32 width, u32 height)
{
    // SetWindowPos wants the total size of the window (including title bar and borders),
    // so we have to compute it.
    RECT rectangle = { 0, 0, static_cast<long>(width), static_cast<long>(height) };
    AdjustWindowRect(&rectangle, GetWindowLong(handle_, GWL_STYLE), false);
    int w = rectangle.right - rectangle.left;
    int h = rectangle.bottom - rectangle.top;

    SetWindowPos(handle_, nullptr, 0, 0, w, h, SWP_NOMOVE | SWP_NOZORDER);
}

void WindowImpl::setTitle(const wstring& title)
{
    SetWindowTextW(handle_, title.data());
}

void WindowImpl::setIcon(u32 width, u32 height, const u8* pixels)
{
    // First destroy the previous one.
    if (icon_)
        DestroyIcon(icon_);

    // Windows wants BGRA pixels: swap red and blue channels.
    Array<u8> iconPixels(width * height * 4);
    for (size_t i = 0; i < iconPixels.size() / 4; ++i)
    {
        iconPixels[i * 4 + 0] = pixels[i * 4 + 2];
        iconPixels[i * 4 + 1] = pixels[i * 4 + 1];
        iconPixels[i * 4 + 2] = pixels[i * 4 + 0];
        iconPixels[i * 4 + 3] = pixels[i * 4 + 3];
    }

    // Create the icon from the pixel array.
    icon_ = CreateIcon(GetModuleHandleW(nullptr), width, height, 1, 32, nullptr, iconPixels.data());

    // Set it as both big and small icon of the window.
    if (icon_)
    {
        SendMessageW(handle_, WM_SETICON, ICON_BIG, (LPARAM)icon_);
        SendMessageW(handle_, WM_SETICON, ICON_SMALL, (LPARAM)icon_);
    }
    else
        cout << "Failed to set the window's icon." << endl;
}

void WindowImpl::setVisible(bool visible)
{
    ShowWindow(handle_, visible ? SW_SHOW : SW_HIDE);
}

void WindowImpl::setMouseCursorVisible(bool visible)
{
    // Don't call twice ShowCursor with the same parameter value;
    // we don't want to increment/decrement the internal counter
    // more than once.
    if (visible != flags_[0])
    {
        flags_[0] = visible;
        ShowCursor(visible);
    }
}

void WindowImpl::setMouseCursorGrabbed(bool grabbed)
{
    flags_[5] = grabbed;
    grabCursor(flags_[5]);
}

void WindowImpl::setMouseCursor(const Cursor& cursor)
{
    lastCursor_ = cursor.cursor_;
    SetCursor(lastCursor_);
}

void WindowImpl::setKeyRepeatEnabled(bool enabled)
{
    flags_[1] = enabled;
}

bool WindowImpl::hasFocus() const
{
    return handle_ == GetForegroundWindow();
}

void WindowImpl::requestFocus()
{
    // Allow focus stealing only within the same process; compare PIDs of current and foreground window.
    DWORD thisPid = GetWindowThreadProcessId(handle_, nullptr);
    DWORD foregroundPid = GetWindowThreadProcessId(GetForegroundWindow(), nullptr);

    // The window requesting focus belongs to the same process as the current window: steal focus.
    if (thisPid == foregroundPid)
        SetForegroundWindow(handle_);
    else
    {
        // Different process: don't steal focus, but create a taskbar notification ("flash").
        FLASHWINFO info;
        info.cbSize = sizeof(info);
        info.hwnd = handle_;
        info.dwFlags = FLASHW_TRAY;
        info.dwTimeout = 0;
        info.uCount = 3;

        FlashWindowEx(&info);
    }
}