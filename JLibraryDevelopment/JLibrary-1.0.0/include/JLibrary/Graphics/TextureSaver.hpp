// JLibraryDevelopment
// TextureSaver.hpp
// Created on 2021-07-17 by Justyn Durnford
// Last modified on 2021-07-17 by Justyn Durnford
// Header file for the TextureSaver class.

#pragma once

#include <JLibrary/Graphics/GlContext.hpp>

namespace jlib
{
	// Automatic wrapper for saving and restoring the current texture binding.
	class TextureSaver
	{
		GLint textureBinding_;

		public:

		// Default constructor.
		// The current texture binding is saved.
		TextureSaver();

		// Destructor.
		// The previous texture binding is restored.
		~TextureSaver() noexcept;
	};
}