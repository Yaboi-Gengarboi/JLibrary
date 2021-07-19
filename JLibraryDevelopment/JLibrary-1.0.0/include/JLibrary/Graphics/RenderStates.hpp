// JLibraryDevelopment
// RenderStates.hpp
// Created on 2021-07-05 by Justyn Durnford
// Last modified on 2021-07-12 by Justyn Durnford
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
        Transformation transform;
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