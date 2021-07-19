// JLibraryDevelopment
// ContextSettings.hpp
// Created on 2021-07-08 by Justyn Durnford
// Last modified on 2021-07-12 by Justyn Durnford
// Header file for the ContextSettings struct.

#pragma once

#include <JLibrary/System/Integer.hpp>

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

		u32  depthBits;         // Bits of the depth buffer.
		u32  stencilBits;       // Bits of the stencil buffer.
		u32  antialiasingLevel; // Level of antialiasing.
		u32  majorVersion;      // Major number of the context version to create.
		u32  minorVersion;      // Minor number of the context version to create.
		u32  attributeFlags;    // The attribute flags to create the context with.
		bool sRgbCapable;       // Whether the context framebuffer is sRGB capable.

		// Primary constructor.
		ContextSettings(u32 depth = 0, u32 stencil = 0, u32 antialiasing = 0, u32 major = 1,
						u32 minor = 1, u32 attributes = Attribute::Default, bool sRgb = false)
		{
			depthBits = depth;
			stencilBits = stencil;
			antialiasingLevel = antialiasing;
			majorVersion = major;
			minorVersion = minor;
			attributeFlags = attributes;
			sRgbCapable = sRgb;
		}
	};
}