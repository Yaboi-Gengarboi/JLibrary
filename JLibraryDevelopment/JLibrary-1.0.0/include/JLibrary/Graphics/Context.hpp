////////////////////////////////////////////////////////////
//
// THIS IS A MODIFIED FILE FROM SFML 2.5.1
// 
// SFML - Simple and Fast Multimedia Library
// Copyright (C) 2007-2021 Laurent Gomila (laurent@sfml-dev.org)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
////////////////////////////////////////////////////////////
// 
// JLibraryDevelopment
// Context.hpp
// Created on 2021-06-30 by Justyn Durnford
// Last modified on 2021-06-30 by Justyn Durnford
// Header file for the Context class and the ContextSettings struct.

#pragma once

#include <JLibrary/Graphics/GlResource.hpp>
#include <JLibrary/System/Integer.hpp>
#include <JLibrary/System/NonCopyable.hpp>

typedef void (*GlFunctionPointer)();

namespace jlib
{
	// Structure defining the settings of the OpenGL
	// context attached to a window.
	struct ContextSettings
	{
		// Enumeration of the context attribute flags.
		enum Attribute
		{
			Default = 0,
			Core    = 1,
			Debug   = 4
		};

		u32 depthBits;         // Bits of the depth buffer.
		u32 stencilBits;       // Bits of the stencil buffer.
		u32 antialiasingLevel; // Level of antialiasing.
		u32 majorVersion;      // Major number of the context version to create.
		u32 minorVersion;      // Minor number of the context version to create.
		u32 attributeFlags;    // The attribute flags to create the context with.
		bool         sRgbCapable;       // Whether the context framebuffer is sRGB capable.

		// Default constructor.
		ContextSettings() = default;

		// Primary constructor.
		ContextSettings(u32 depth = 0, u32 stencil = 0, u32 antialiasing = 0, u32 major = 1, 
						u32 minor = 1, Attribute attributes = Default, bool sRgb = false);
	};
}