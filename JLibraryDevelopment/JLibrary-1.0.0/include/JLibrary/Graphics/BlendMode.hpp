// JLibraryDevelopment
// BlendMode.hpp
// Created on 2021-06-29 by Justyn Durnford
// Last modified on 2021-07-18 by Justyn Durnford
// Header file for the BlendMode struct.

#pragma once

namespace jlib
{
	// 
	struct BlendMode
	{
		// 
		enum Factor
		{
			Zero                   = 0, 
			One                    = 1, 
			SrcColor               = 2,             
			OneMinusSrcColor       = 3,     
			DstColor               = 4,             
			OneMinusDstColor       = 5,     
			SrcAlpha               = 7,             
			OneMinusSrcAlpha       = 8,     
			DstAlpha               = 9,             
			OneMinusDstAlpha       = 10
		};

		// 
		enum Equation
		{
			Add                    = 0,             
			Subtract               = 1,        
			ReverseSubtract        = 2, 
			Min                    = 3,             
			Max                    = 4
		};

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

		Factor   colorSrcFactor;
		Factor   colorDstFactor;
		Equation colorEquation; 
		Factor   alphaSrcFactor;
		Factor   alphaDstFactor;
		Equation alphaEquation; 

		// Default constructor.
		BlendMode();

		// Constructs the blend mode with the given factors and equation.
		BlendMode(Factor sourceFactor, Factor destinationFactor, Equation blendEquation = Add);

		// Constructs the blend mode with the given factors and equations.
		BlendMode(Factor colorSourceFactor, Factor colorDestinationFactor,
				  Equation colorBlendEquation, Factor alphaSourceFactor,
				  Factor alphaDestinationFactor, Equation alphaBlendEquation);
	};

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

	// Blend source and dest according to dest alpha.
	extern const BlendMode BlendAlpha;
	// Add source to dest.
	extern const BlendMode BlendAdd;      
	// Multiply source and dest.
	extern const BlendMode BlendMultiply; 
	// Take minimum between source and dest.
	extern const BlendMode BlendMin; 
	// Take maximum between source and dest.
	extern const BlendMode BlendMax;      
	// Overwrite dest with source.
	extern const BlendMode BlendNone;     
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

// Overload of binary operator ==
bool operator == (const jlib::BlendMode& A, const jlib::BlendMode& B);

// Overload of binary operator !=
bool operator != (const jlib::BlendMode& A, const jlib::BlendMode& B);