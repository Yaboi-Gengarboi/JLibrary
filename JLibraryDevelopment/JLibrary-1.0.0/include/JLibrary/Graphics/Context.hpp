// JLibraryDevelopment
// Context.hpp
// Created on 2021-07-08 by Justyn Durnford
// Last modified on 2021-07-18 by Justyn Durnford
// Header file for the Context class.

#pragma once

#include <JLibrary/Graphics/GlContext.hpp>

namespace jlib
{
    // 
	class Context : GlResource, NonCopyable
	{
		GlContext* context_;

		public:

		// Default constructor.
		// Creates and activates the context.
		Context();

		// Destructor.
		// Deactivates and destroys the context.
		~Context();

        // Activates or deactivate explicitly the context.
        // Returns true if successful.
        bool setActive(bool active);

        // Gets the settings of the context.
        // Note that these settings may be different than the ones
        // passed to the constructor; they are indeed adjusted if the
        // original settings are not directly supported by the system.
        const ContextSettings& settings() const;

        // Returns true if a given OpenGL extension is available.
        static bool isExtensionAvailable(const char* name);

        // Gets the address of an OpenGL function.
        // Returns nullptr on failure.
        static GlFunctionPointer getFunction(const char* name);

        // Gets the currently active context.
        // This function will only return jlib::Context objects.
        // Contexts created e.g. by RenderTargets or for internal
        // use will not be returned by this function.
        // Returns nullptr if none are active.
        static const Context* getActiveContext();

        // Gets the currently active context's ID.
        // The context ID is used to identify contexts when
        // managing unshareable OpenGL resources.
        // Returns 0 if no context is currently active.
        static u64 getActiveContextId();

        // Constructs a in-memory context.
        // This constructor is for internal use, you don't need
        // to bother with it.
        Context(const ContextSettings& settings, u32 width, u32 height);
	};
}