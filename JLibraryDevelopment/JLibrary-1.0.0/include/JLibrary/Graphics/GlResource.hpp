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
// GlResource.hpp
// Created on 2021-06-30 by Justyn Durnford
// Last modified on 2021-07-01 by Justyn Durnford
// Header file for the GlResource class.

#include <JLibrary/System/NonCopyable.hpp>

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