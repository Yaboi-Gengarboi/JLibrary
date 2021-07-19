// JLibraryDevelopment
// Cursor.hpp
// Created on 2021-07-07 by Justyn Durnford
// Last modified on 2021-07-16 by Justyn Durnford
// Header file for the Cursor class.

#pragma once

#include <JLibrary/Math/Point2.hpp>
#include <JLibrary/System/Integer.hpp>
#include <JLibrary/Utility/NonCopyable.hpp>
#include <windows.h>

namespace jlib
{
	// Class that defines the appearance of a system cursor.
	class Cursor : NonCopyable
	{
		public:

        enum Type
        {
            Arrow,                  
            ArrowWait,              
            Wait,                   
            Text,                   
            Hand,                   
            SizeHorizontal,         
            SizeVertical,           
            SizeTopLeftBottomRight, 
            SizeBottomLeftTopRight, 
            SizeLeft,               
            SizeRight,              
            SizeTop,                
            SizeBottom,             
            SizeTopLeft,            
            SizeBottomRight,        
            SizeBottomLeft,         
            SizeTopRight,           
            SizeAll,                
            Cross,                  
            Help,                   
            NotAllowed              
        };

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

        private:

        friend class WindowImpl;

        HCURSOR cursor_;

        // Releases the cursor if one has been loaded.
        void release();

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

        public:

        // Default constructor.
        // This constructor doesn't actually create the cursor;
        // initially the new instance is invalid and must not be
        // used until either loadFromPixels() or loadFromSystem()
        // is called and successfully created a cursor.
        Cursor();

        // Destructor.
        // This destructor releases the system resources
        // associated with this cursor, if any.
        ~Cursor();

        // Creates a cursor with the provided image.
        // pixels must be an array of width by height pixels
        // in 32-bit RGBA format. If not, this will cause undefined behavior.
        // If pixels is nullptr or either width or height are 0,
        // the current cursor is left unchanged and the function will
        // return false.
        // In addition to specifying the pixel data, you can also
        // specify the location of the hotspot of the cursor. The
        // hotspot is the pixel coordinate within the cursor image
        // which will be located exactly where the mouse pointer
        // position is. Any mouse actions that are performed will
        // return the window/screen location of the hotspot.
        // Returns true if successful.
        bool loadFromPixels(const u8* pixels, u32 width, u32 height, Point2ui hotspot);

        // Creates a native system cursor.
        bool loadFromSystem(Type type);
	};
}