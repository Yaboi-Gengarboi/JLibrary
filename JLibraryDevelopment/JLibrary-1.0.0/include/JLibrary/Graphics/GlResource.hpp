// JLibraryDevelopment
// GlResource.hpp
// Created on 2021-06-30 by Justyn Durnford
// Last modified on 2021-07-07 by Justyn Durnford
// Header file for the GlResource class.

#include <JLibrary/Utility/NonCopyable.hpp>

#pragma once

namespace jlib
{
	typedef void(*ContextDestroyCallback)(void*);

	// Base class for classes that require an OpenGL context.
	class GlResource
	{
		protected:

		// Default constructor.
		GlResource();

		// Destructor.
		~GlResource();

		// Register a function to be called when a context is destroyed.
		// This is used for internal purposes in order to properly clean up 
		// OpenGL resources that cannot be shared between contexts.
		static void registerContextDestroyCallback(ContextDestroyCallback callback, void* arg);

		// RAII helper class to temporarily lock an available context for use.
		class TransientContextLock : NonCopyable
		{
			public:
			
			// Default constructor.
			TransientContextLock();

			// Destructor.
			~TransientContextLock();
		};
	};
}