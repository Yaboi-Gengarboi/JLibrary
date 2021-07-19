// JLibraryDevelopment
// Drawable.hpp
// Created on 2021-07-05 by Justyn Durnford
// Last modified on 2021-07-05 by Justyn Durnford
// Header file for the Drawable class.

#pragma once

#include <JLibrary/Graphics/RenderStates.hpp>

namespace jlib
{
	class RenderTarget;

	// Abstract base class for objects that can be drawn to a render target.
	class Drawable
	{
		protected:

		friend class RenderTarget;

        // Draw the object to a render target.
        // This is a pure virtual function that has to be implemented
        // by the derived class to define how the drawable should be drawn.
        virtual void draw(RenderTarget& target, RenderStates states) const = 0;

		public:

		// Destructor.
		virtual ~Drawable() {}
	};
}