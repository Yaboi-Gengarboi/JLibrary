// JLibraryDevelopment
// Cursor.cpp
// Created on 2021-07-07 by Justyn Durnford
// Last modified on 2021-07-16 by Justyn Durnford
// Source file for the Cursor class.

#include <JLibrary/System/Cursor.hpp>
using namespace jlib;

#include <cstring>
using std::size_t;
using std::memset;

#include <iostream>
using std::cout;
using std::endl;

void Cursor::release()
{
	if (cursor_ != nullptr)
	{
		DestroyCursor(cursor_);
		cursor_ = nullptr;
	}
}

Cursor::Cursor()
{
	cursor_ = nullptr;
}

Cursor::~Cursor()
{
	release();
}

bool Cursor::loadFromPixels(const u8* pixels, u32 width, u32 height, Point2ui hotspot)
{
	if ((pixels == nullptr) || (width == 0) || (height == 0))
		return false;

	release();

	// Creates the bitmap that will hold the color data.
	BITMAPV5HEADER bitmapHeader;
	memset(&bitmapHeader, 0, sizeof(BITMAPV5HEADER));

	bitmapHeader.bV5Size = sizeof(BITMAPV5HEADER);
	bitmapHeader.bV5Width = width;
	bitmapHeader.bV5Height = -static_cast<int>(height); // Negative indicates origin is in upper-left corner
	bitmapHeader.bV5Planes = 1;
	bitmapHeader.bV5BitCount = 32;
	bitmapHeader.bV5Compression = BI_BITFIELDS;
	bitmapHeader.bV5RedMask = 0x00ff0000;
	bitmapHeader.bV5GreenMask = 0x0000ff00;
	bitmapHeader.bV5BlueMask = 0x000000ff;
	bitmapHeader.bV5AlphaMask = 0xff000000;

	u32* bitmapData = nullptr;

    HDC screenDC = GetDC(nullptr);
    HBITMAP color = CreateDIBSection
    (
        screenDC,
        reinterpret_cast<const BITMAPINFO*>(&bitmapHeader),
        DIB_RGB_COLORS,
        reinterpret_cast<void**>(&bitmapData),
        nullptr,
        0
    );
    ReleaseDC(nullptr, screenDC);

    if (color == nullptr)
    {
        cout << "Failed to create cursor color bitmap." << endl;
        return false;
    }

    // Fill the bitmap with the cursor color data.
    // We'll have to swap the red and blue channels here.
    u32* bitmapOffset = bitmapData;
    for (size_t remaining = width * height; remaining > 0; --remaining, pixels += 4)
        *bitmapOffset++ = (pixels[3] << 24) | (pixels[0] << 16) | (pixels[1] << 8) | pixels[2];

    // Create a dummy mask bitmap (it won't be used).
    HBITMAP mask = CreateBitmap(width, height, 1, 1, nullptr);

    if (mask == nullptr)
    {
        DeleteObject(color);
        cout << "Failed to create cursor mask bitmap." << endl;
        return false;
    }

    // Create the structure that describes the cursor.
    ICONINFO cursorInfo;
    memset(&cursorInfo, 0, sizeof(ICONINFO));

    cursorInfo.fIcon = FALSE; // This is a cursor and not an icon.
    cursorInfo.xHotspot = hotspot.x;
    cursorInfo.yHotspot = hotspot.y;
    cursorInfo.hbmColor = color;
    cursorInfo.hbmMask = mask;

    // Create the cursor
    cursor_ = reinterpret_cast<HCURSOR>(CreateIconIndirect(&cursorInfo));

    // The data has been copied into the cursor, so get rid of these
    DeleteObject(color);
    DeleteObject(mask);

    if (cursor_ == nullptr)
    {
        cout << "Failed to create cursor from bitmaps." << endl;
        return false;
    }

    return true;
}

bool Cursor::loadFromSystem(Cursor::Type type)
{
    release();

    LPCTSTR shape = nullptr;
    switch (type)
    {
        case Cursor::Arrow:                  shape = IDC_ARROW;       break;
        case Cursor::ArrowWait:              shape = IDC_APPSTARTING; break;
        case Cursor::Wait:                   shape = IDC_WAIT;        break;
        case Cursor::Text:                   shape = IDC_IBEAM;       break;
        case Cursor::Hand:                   shape = IDC_HAND;        break;
        case Cursor::SizeHorizontal:         shape = IDC_SIZEWE;      break;
        case Cursor::SizeVertical:           shape = IDC_SIZENS;      break;
        case Cursor::SizeTopLeftBottomRight: shape = IDC_SIZENWSE;    break;
        case Cursor::SizeBottomLeftTopRight: shape = IDC_SIZENESW;    break;
        case Cursor::SizeLeft:               shape = IDC_SIZEWE;      break;
        case Cursor::SizeRight:              shape = IDC_SIZEWE;      break;
        case Cursor::SizeTop:                shape = IDC_SIZENS;      break;
        case Cursor::SizeBottom:             shape = IDC_SIZENS;      break;
        case Cursor::SizeTopLeft:            shape = IDC_SIZENWSE;    break;
        case Cursor::SizeBottomRight:        shape = IDC_SIZENWSE;    break;
        case Cursor::SizeBottomLeft:         shape = IDC_SIZENESW;    break;
        case Cursor::SizeTopRight:           shape = IDC_SIZENESW;    break;
        case Cursor::SizeAll:                shape = IDC_SIZEALL;     break;
        case Cursor::Cross:                  shape = IDC_CROSS;       break;
        case Cursor::Help:                   shape = IDC_HELP;        break;
        case Cursor::NotAllowed:             shape = IDC_NO;          break;
        default:                             shape = IDC_ARROW;       break;
    }

    // Create a copy of the shared system cursor that can be destroyed later.
    cursor_ = CopyCursor(LoadCursor(nullptr, shape));

    if (cursor_ == nullptr)
    {
        cout << "Could not create copy of a system cursor" << endl;
        return false;
    }

    return true;
}