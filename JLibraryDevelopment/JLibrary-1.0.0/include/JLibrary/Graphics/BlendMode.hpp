// JLibraryDevelopment
// BlendMode.hpp
// Created on 2021-06-13 by Justyn Durnford
// Last modified on 2021-06-13 by Justyn Durnford
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
			Zero,
			One,
			SourceColor,
			OneMinusSourceColor,
			DestinationColor,
			SourceAlpha,
			OneMinusSourceAlpha,
			DestinationAlpha,
			OneMinusDestinationAlpha
		};

		// 
		enum Equation
		{
			Add,
			Subtract,
			ReverseSubtract,
			Min,
			Max
		};

		Factor colorSourceFactor;
		Factor colorDestinationFactor;
		Equation colorEquation;
		Factor alphaSourceFactor;
		Factor alphaDestinationFactor;
		Equation alphaEquation;

		// Default constructor.
		BlendMode();

		// 
		BlendMode(Factor sourceFactor, Factor destinationFactor);

		// 
		BlendMode(Factor sourceFactor, Factor destinationFactor, Equation blendEquation);

		// 
		BlendMode(Factor ColorSourceFactor, Factor ColorDestinationFactor, Equation ColorBlendEquation,
				  Factor AlphaSourceFactor, Factor AlphaDestinationFactor, Equation AlphaBlendEquation);

		// Copy constructor.
		BlendMode(const BlendMode& other) = default;

		// Move constructor.
		BlendMode(BlendMode&& other) = default;

		// Copy assignment operator.
		BlendMode& operator = (const BlendMode& other) = default;

		// Move assignment operator.
		BlendMode& operator = (BlendMode&& other) = default;

		// Destructor.
		~BlendMode() = default;
	};

	// Common BlendModes.
	extern const BlendMode BlendAlpha;
	extern const BlendMode BlendAdd;
	extern const BlendMode BlendMultiply;
	extern const BlendMode BlendMin;
	extern const BlendMode BlendMax;
	extern const BlendMode BlendNone;
}

// Overload binary operator ==
bool operator == (const jlib::BlendMode& A, const jlib::BlendMode& B);

// Overload binary operator !=
bool operator == (const jlib::BlendMode& A, const jlib::BlendMode& B);