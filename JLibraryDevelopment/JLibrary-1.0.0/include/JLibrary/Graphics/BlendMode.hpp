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
// BlendMode.hpp
// Created on 2021-06-29 by Justyn Durnford
// Last modified on 2021-07-01 by Justyn Durnford
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