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
// GlContext.hpp
// Created on 2021-06-30 by Justyn Durnford
// Last modified on 2021-07-04 by Justyn Durnford
// Header file for the GlContext class.

#pragma once

#include <JLibrary/Graphics/Context.hpp>
#include <JLibrary/Graphics/GlResource.hpp>
#include <JLibrary/System/NonCopyable.hpp>
#include <string>

namespace jlib
{
	// Abstract class representing an OpenGL context.
	class GlContext : NonCopyable
	{
		const u64 id_;

        // Perform various initializations after the context construction.
        void initialize(const ContextSettings& requestedSettings);

        // Check whether the context is compatible with the requested settings.
        void checkSettings(const ContextSettings& requestedSettings);

		protected:

		ContextSettings settings_;

		// Default constructor.
		// This constructor is meant for derived classes only.
		GlContext();

		// Activate the context as the current target for rendering.
		// Returns true on success, false if any error happened.
		virtual bool makeCurrent(bool current) = 0;

		// Notifies unshared GlResources of context destruction.
		void cleanupUnsharedResources();

		// 
		static i32 evaluateFormat(u32 bitsPerPixel, const ContextSettings& settings, 
								  i32 colorBits, i32 depthBits, i32 stencilBits, 
								  i32 antialiasing, bool accelerated, bool sRgb);

		public:

		// Checks whether or not a given OpenGL extension is available.
		// Returns true if available, false if unavailable.
		static bool isExtensionAvailable(const std::string& name);

		// Gets the address of an OpenGL function.
		// Returns the address of the OpenGL function, nullptr on failure.
		static GlFunctionPointer getFunction(const std::string& name);

		// Gets the currently active context.
		// Returns nullptr if none is active.
		static const GlContext* getActiveContext();

		// Returns the ID of the currently active context.
		// Returns 0 if no context is currently active.
		static u64 getActiveContextId();

		// Destructor.
		virtual ~GlContext();

		// Returns the settings of the context.
		// Note that these settings may be different than the ones
		// passed to the constructor; they are indeed adjusted if the
		// original settings are not directly supported by the system.
		const ContextSettings& getSettings() const;

		// Activate or deactivate the context as the current target for rendering.
		// A context is active only on the current thread, if you want to
		// make it active on another thread you have to deactivate it
		// on the previous thread first if it was active.
		// Only one context can be active on a thread at a time, thus
		// the context previously active (if any) automatically gets deactivated.
		// Returns true if the operation was successful, false otherwise.
		bool setActive(bool isActive);

		// Displays what has been rendered to the context so far.
		virtual void display() = 0;

		// Enable or disable vertical synchronization.
		// Activating vertical synchronization will limit the number
		// of frames displayed to the refresh rate of the monitor.
		// This can avoid some visual artifacts, and limit the framerate
		// to a good value (but not constant across different computers).
		virtual void setVerticalSyncEnabled(bool enabled) = 0;
	};
}