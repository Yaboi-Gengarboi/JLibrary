// JLibraryDevelopment
// BlendMode.cpp
// Created on 2021-06-13 by Justyn Durnford
// Last modified on 2021-06-14 by Justyn Durnford
// Source file for the BlendMode struct.

#include <JLibrary/Graphics/BlendMode.hpp>
using namespace std;
using namespace jlib;

BlendMode::BlendMode()
{
	colorSourceFactor = Factor::SourceAlpha;
	colorDestinationFactor = Factor::OneMinusSourceAlpha;
	colorEquation = Equation::Add;
	alphaSourceFactor = Factor::One;
	alphaDestinationFactor = Factor::OneMinusSourceAlpha;
	alphaEquation = Equation::Add;
}

BlendMode::BlendMode(Factor sourceFactor, Factor destinationFactor)
{
	colorSourceFactor = sourceFactor;
	colorDestinationFactor = destinationFactor;
	colorEquation = Equation::Add;
	alphaSourceFactor = sourceFactor;
	alphaDestinationFactor = destinationFactor;
	alphaEquation = Equation::Add;
}

BlendMode::BlendMode(Factor sourceFactor, Factor destinationFactor, Equation blendEquation)
{
	colorSourceFactor = sourceFactor;
	colorDestinationFactor = destinationFactor;
	colorEquation = blendEquation;
	alphaSourceFactor = sourceFactor;
	alphaDestinationFactor = destinationFactor;
	alphaEquation = blendEquation;
}

BlendMode::BlendMode(Factor ColorSourceFactor, Factor ColorDestinationFactor, Equation ColorBlendEquation,
					 Factor AlphaSourceFactor, Factor AlphaDestinationFactor, Equation AlphaBlendEquation)
{
	colorSourceFactor = ColorSourceFactor;
	colorDestinationFactor = ColorDestinationFactor;
	colorEquation = ColorBlendEquation;
	alphaSourceFactor = AlphaSourceFactor;
	alphaDestinationFactor = AlphaDestinationFactor;
	alphaEquation = AlphaBlendEquation;
}

const BlendMode BlendAlpha(BlendMode::SourceAlpha, BlendMode::OneMinusSourceAlpha, BlendMode::Add, BlendMode::One, BlendMode::OneMinusSourceAlpha, BlendMode::Add);
const BlendMode BlendAdd(BlendMode::SourceAlpha, BlendMode::One, BlendMode::Add, BlendMode::One, BlendMode::One, BlendMode::Add);
const BlendMode BlendMultiply(BlendMode::DestinationColor, BlendMode::Zero, BlendMode::Add);
const BlendMode BlendMin(BlendMode::One, BlendMode::One, BlendMode::Min);
const BlendMode BlendMax(BlendMode::One, BlendMode::One, BlendMode::Max);
const BlendMode BlendNone(BlendMode::One, BlendMode::Zero, BlendMode::Add);

bool operator == (const BlendMode& A, const BlendMode& B)
{
	return (A.colorSourceFactor == B.colorSourceFactor) && 
		   (A.colorDestinationFactor == B.colorDestinationFactor) &&
		   (A.colorEquation == B.colorEquation) &&
		   (A.alphaSourceFactor == B.alphaSourceFactor) &&
		   (A.alphaDestinationFactor == B.alphaDestinationFactor) &&
		   (A.alphaEquation == B.alphaEquation);
}

bool operator != (const BlendMode& A, const BlendMode& B)
{
	return (A.colorSourceFactor != B.colorSourceFactor) ||
		   (A.colorDestinationFactor != B.colorDestinationFactor) ||
		   (A.colorEquation != B.colorEquation) ||
		   (A.alphaSourceFactor != B.alphaSourceFactor) ||
		   (A.alphaDestinationFactor != B.alphaDestinationFactor) ||
		   (A.alphaEquation != B.alphaEquation);
}