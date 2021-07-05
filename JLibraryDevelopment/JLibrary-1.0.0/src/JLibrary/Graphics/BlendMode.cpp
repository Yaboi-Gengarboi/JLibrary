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
// BlendMode.cpp
// Created on 2021-06-30 by Justyn Durnford
// Last modified on 2021-07-02 by Justyn Durnford
// Source file for the BlendMode struct.

#include <JLibrary/Graphics/BlendMode.hpp>
using namespace jlib;

const BlendMode BlendAlpha(BlendMode::SrcAlpha, BlendMode::OneMinusSrcAlpha, BlendMode::Add,
                           BlendMode::One, BlendMode::OneMinusSrcAlpha, BlendMode::Add);
const BlendMode BlendAdd(BlendMode::SrcAlpha, BlendMode::One, BlendMode::Add,
                         BlendMode::One, BlendMode::One, BlendMode::Add);
const BlendMode BlendMultiply(BlendMode::DstColor, BlendMode::Zero, BlendMode::Add);
const BlendMode BlendMin(BlendMode::One, BlendMode::One, BlendMode::Min);
const BlendMode BlendMax(BlendMode::One, BlendMode::One, BlendMode::Max);
const BlendMode BlendNone(BlendMode::One, BlendMode::Zero, BlendMode::Add);

BlendMode::BlendMode()
{
    colorSrcFactor = BlendMode::SrcAlpha;
    colorDstFactor = BlendMode::OneMinusSrcAlpha;
    colorEquation = BlendMode::Add;
    alphaSrcFactor = BlendMode::One;
    alphaDstFactor = BlendMode::OneMinusSrcAlpha;
    alphaEquation = BlendMode::Add;
}

BlendMode::BlendMode(Factor sourceFactor, Factor destinationFactor, Equation blendEquation)
{
    colorSrcFactor = sourceFactor;
    colorDstFactor = destinationFactor;
    colorEquation = blendEquation;
    alphaSrcFactor = sourceFactor;
    alphaDstFactor = destinationFactor;
    alphaEquation = blendEquation;
}

BlendMode::BlendMode(Factor colorSourceFactor, Factor colorDestinationFactor,
                     Equation colorBlendEquation, Factor alphaSourceFactor,
                     Factor alphaDestinationFactor, Equation alphaBlendEquation)
{
    colorSrcFactor = colorSourceFactor;
    colorDstFactor = colorDestinationFactor;
    colorEquation = colorBlendEquation;
    alphaSrcFactor = alphaSourceFactor;
    alphaDstFactor = alphaDestinationFactor;
    alphaEquation = alphaBlendEquation;
}


bool operator == (const BlendMode& A, const BlendMode& B)
{
    return (A.colorSrcFactor == B.colorSrcFactor) &&
           (A.colorDstFactor == B.colorDstFactor) &&
           (A.colorEquation  == B.colorEquation)  &&
           (A.alphaSrcFactor == B.alphaSrcFactor) &&
           (A.alphaDstFactor == B.alphaDstFactor) &&
           (A.alphaEquation  == B.alphaEquation);
}


bool operator != (const BlendMode& A, const BlendMode& B)
{
    return (A.colorSrcFactor != B.colorSrcFactor) ||
           (A.colorDstFactor != B.colorDstFactor) ||
           (A.colorEquation  != B.colorEquation)  ||
           (A.alphaSrcFactor != B.alphaSrcFactor) ||
           (A.alphaDstFactor != B.alphaDstFactor) ||
           (A.alphaEquation  != B.alphaEquation);
}