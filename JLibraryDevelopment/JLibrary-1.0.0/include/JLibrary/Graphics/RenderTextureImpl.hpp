// JLibraryDevelopment
// RenderTextureImpl.hpp
// Created on 2021-07-17 by Justyn Durnford
// Last modified on 2021-07-17 by Justyn Durnford
// Header file for the RenderTextureImpl class.

#pragma once

#include <JLibrary/System/Integer.hpp>
#include <JLibrary/Utility/NonCopyable.hpp>

namespace jlib
{
    struct ContextSettings;

	class RenderTextureImpl : NonCopyable
	{
		public:

        // Destructor.
        virtual ~RenderTextureImpl() {}

        // Creates the render texture implementation.
        // Returns true if successful.
        virtual bool create(u32 width, u32 height, u32 textureId, const ContextSettings& settings) = 0;

        // Activates or deactivates the render texture for rendering.
        // Returns true if successful.
        virtual bool activate(bool active) = 0;

        // Updates the pixels of the target texture.
        virtual void updateTexture(u32 textureId) = 0;
	};
}