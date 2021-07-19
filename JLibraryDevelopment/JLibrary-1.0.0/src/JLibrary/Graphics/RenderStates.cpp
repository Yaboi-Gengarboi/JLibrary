// JLibraryDevelopment
// RenderStates.cpp
// Created on 2021-07-12 by Justyn Durnford
// Last modified on 2021-07-12 by Justyn Durnford
// Source file for the RenderStates struct.

#include <JLibrary/Graphics/RenderStates.hpp>
using namespace jlib;

// <cstddef>
using std::size_t;

namespace jlib
{
    const RenderStates RenderStates::Default(BlendMode(
          BlendMode::SrcAlpha, BlendMode::OneMinusSrcAlpha, BlendMode::Add,
          BlendMode::One, BlendMode::OneMinusSrcAlpha, BlendMode::Add));
}

RenderStates::RenderStates()
    : blendMode(BlendAlpha), transform(), texture(nullptr), shader(nullptr) {}

RenderStates::RenderStates(const Transformation& theTransform) 
    : blendMode(BlendAlpha), transform(theTransform), texture(nullptr), shader(nullptr) {}

RenderStates::RenderStates(const BlendMode& theBlendMode)
    : blendMode(theBlendMode), transform(), texture(nullptr), shader(nullptr) {}

RenderStates::RenderStates(const Texture* theTexture) 
    : blendMode(BlendAlpha), transform(), texture(theTexture), shader(nullptr) {}

RenderStates::RenderStates(const Shader* theShader) 
    : blendMode(BlendAlpha), transform(), texture(nullptr), shader(theShader) {}

RenderStates::RenderStates(const BlendMode& theBlendMode, const Transformation& theTransform,
                           const Texture* theTexture, const Shader* theShader) 
    : blendMode(theBlendMode), transform(theTransform), texture(theTexture), shader(theShader) {}