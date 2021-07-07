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
// RenderStates.hpp
// Created on 2021-07-05 by Justyn Durnford
// Last modified on 2021-07-05 by Justyn Durnford
// Header file for the RenderStates struct.

#pragma once

#include <JLibrary/Graphics/BlendMode.hpp>
#include <JLibrary/Graphics/Transformation.hpp>

namespace jlib
{
	class Shader;
	class Texture;

	// Defines the states used for drawing to a RenderTarget.
	struct RenderStates
	{
		public:

        static const RenderStates Default;

        BlendMode      blendMode;
        Transformation      transform;
        const Texture* texture;
        const Shader* shader;

        // Default constructor.
        // Constructing a default set of render states is equivalent
        // to using sf::RenderStates::Default.
        // The default set defines:
        // - The BlendAlpha blend mode.
        // - The identity transform.
        // - A null texture.
        // - A null shader.
        RenderStates();

        // Constructs a default set of render states with a custom blend mode.
        RenderStates(const BlendMode& theBlendMode);

        // Constructs a default set of render states with a custom transform.
        RenderStates(const Transformation& theTransform);

        // Constructs a default set of render states with a custom texture.
        RenderStates(const Texture* theTexture);

        // Constructs a default set of render states with a custom shader.
        RenderStates(const Shader* theShader);

        // Constructs a set of render states with all its attributes.
        RenderStates(const BlendMode& theBlendMode, const Transformation& theTransform,
                     const Texture* theTexture, const Shader* theShader);
	};
}