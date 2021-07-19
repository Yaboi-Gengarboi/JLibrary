// JLibraryDevelopment
// Clipboard.cpp
// Created on 2021-07-07 by Justyn Durnford
// Last modified on 2021-07-07 by Justyn Durnford
// Source file for the Clipboard class.

#include <JLibrary/System/Clipboard.hpp>
using namespace jlib;

#include <iostream>
using std::cout;
using std::endl;

#include <cstring>
using std::memcpy;

// <string>
using std::wstring;

#include <windows.h>

wstring Clipboard::getString()
{
    wstring text;

    if (!IsClipboardFormatAvailable(CF_UNICODETEXT))
    {
        cout << "Failed to get the clipboard data in Unicode format." << endl;
        return text;
    }

    if (!OpenClipboard(nullptr))
    {
        cout << "Failed to open the Win32 clipboard." << endl;
        return text;
    }

    HANDLE clipboard_handle = GetClipboardData(CF_UNICODETEXT);

    if (!clipboard_handle)
    {
        cout << "Failed to get Win32 handle for clipboard content." << endl;
        CloseClipboard();
        return text;
    }

    text = (static_cast<wchar_t*>(GlobalLock(clipboard_handle)));
    GlobalUnlock(clipboard_handle);

    CloseClipboard();
    return text;
}

void Clipboard::setString(const wstring& text)
{
    if (!OpenClipboard(NULL))
    {
        cout << "Failed to open the Win32 clipboard." << endl;
        return;
    }

    if (!EmptyClipboard())
    {
        cout << "Failed to empty the Win32 clipboard." << endl;
        return;
    }

    // Create a Win32-compatible string
    size_t string_size = (text.size() + 1) * sizeof(WCHAR);
    HANDLE string_handle = GlobalAlloc(GMEM_MOVEABLE, string_size);

    if (string_handle)
    {
        memcpy(GlobalLock(string_handle), text.data(), string_size);
        GlobalUnlock(string_handle);
        SetClipboardData(CF_UNICODETEXT, string_handle);
    }

    CloseClipboard();
}