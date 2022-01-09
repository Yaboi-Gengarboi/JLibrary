// JLibrary
// Constants.hpp
// Created on 2022-01-08 by Justyn Durnford
// Last modified on 2022-01-08 by Justyn Durnford
// Header file defining several numeric constants.

#pragma once

#include <numbers>

namespace jlib
{
	constexpr float JLIB_PI     = std::numbers::pi_v<float>;
	constexpr float JLIB_2PI    = std::numbers::pi_v<float> * 2.0f;
	constexpr float JLIB_PI_2   = std::numbers::pi_v<float> / 2.0f;
	constexpr float JLIB_PI_3   = std::numbers::pi_v<float> / 3.0f;
	constexpr float JLIB_PI_4   = std::numbers::pi_v<float> / 4.0f;
	constexpr float JLIB_PI_6   = std::numbers::pi_v<float> / 6.0f;
	constexpr float JLIB_TO_RAD = std::numbers::pi_v<float> / 180.0f;
	constexpr float JLIB_TO_DEG = 180.f / std::numbers::pi_v<float>;
	constexpr float JLIB_SQRT2  = std::numbers::sqrt2_v<float>;
	constexpr float JLIB_SQRT3  = std::numbers::sqrt3_v<float>;
}