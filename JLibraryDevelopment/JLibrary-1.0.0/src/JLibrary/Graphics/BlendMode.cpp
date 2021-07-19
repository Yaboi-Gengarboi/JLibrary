// JLibraryDevelopment
// BlendMode.cpp
// Created on 2021-06-30 by Justyn Durnford
// Last modified on 2021-07-16 by Justyn Durnford
// Source file for the BlendMode struct.

#include <JLibrary/Graphics/BlendMode.hpp>
using namespace jlib;

const BlendMode jlib::BlendAlpha(BlendMode::SrcAlpha, BlendMode::OneMinusSrcAlpha, BlendMode::Add,
                           BlendMode::One, BlendMode::OneMinusSrcAlpha, BlendMode::Add);
const BlendMode jlib::BlendAdd(BlendMode::SrcAlpha, BlendMode::One, BlendMode::Add,
                         BlendMode::One, BlendMode::One, BlendMode::Add);
const BlendMode jlib::BlendMultiply(BlendMode::DstColor, BlendMode::Zero, BlendMode::Add);
const BlendMode jlib::BlendMin(BlendMode::One, BlendMode::One, BlendMode::Min);
const BlendMode jlib::BlendMax(BlendMode::One, BlendMode::One, BlendMode::Max);
const BlendMode jlib::BlendNone(BlendMode::One, BlendMode::Zero, BlendMode::Add);

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