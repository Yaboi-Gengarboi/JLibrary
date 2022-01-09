// JLibrary
// SFML_JLIB_Convert.hpp
// Created on 2022-01-08 by Justyn Durnford
// Last modified on 2022-01-08 by Justyn Durnford
// Header file defining several functions to convert between SFML and JLIB code.

#pragma once

#ifdef INCLUDE_SFML

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "Color.hpp"

#include <cmath>

import Arithmetic;
import Rect;
import Square;
import Vector2;
import Vector3;

///////////////////////////////////////////////////////////////////////////////////////////////////
// JLIB -> SFML                                                                                  //
///////////////////////////////////////////////////////////////////////////////////////////////////

template <jlib::arithmetic T>
sf::Vector2<T> jlib_to_sfml(const jlib::Vector2<T>& v)
{
	return sf::Vector2<T>(v.x, v.y);
}

template <jlib::arithmetic T>
sf::Vector3<T> jlib_to_sfml(const jlib::Vector3<T>& v)
{
	return sf::Vector3<T>(v.x, v.y, v.z);
}

template <jlib::arithmetic T>
sf::Rect<T> jlib_to_sfml(const jlib::Rect<T>& r)
{
	return sf::Rect<T>(r.x, r.y, r.w, r.h);
}

template <jlib::arithmetic T>
sf::Rect<T> jlib_to_sfml(const jlib::Square<T>& s)
{
	return sf::Rect<T>(s.x, s.y, s.l, s.l);
}

sf::Color jlib_to_sfml(const jlib::Color& c)
{
	return sf::Color(c.r, c.g, c.b, c.a);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// SFML -> JLIB                                                                                  //
///////////////////////////////////////////////////////////////////////////////////////////////////

template <jlib::arithmetic T>
jlib::Vector2<T> sfml_to_jlib(const sf::Vector2<T>& v)
{
	return jlib::Vector2<T>(v.x, v.y);
}

template <jlib::arithmetic T>
jlib::Vector3<T> sfml_to_jlib(const sf::Vector3<T>& v)
{
	return jlib::Vector3<T>(v.x, v.y, v.z);
}

template <jlib::arithmetic T>
jlib::Rect<T> sfml_to_jlib(const sf::Rect<T>& r)
{
	return jlib::Rect<T>(r.left, r.top, r.width, r.height);
}

jlib::Color sfml_to_jlib(const sf::Color& c)
{
	return jlib::Color(c.r, c.g, c.b, c.a);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// JLIB Functions with SFML objects                                                              //
///////////////////////////////////////////////////////////////////////////////////////////////////

namespace jlib
{
	template <arithmetic T>
	constexpr float magnitude(const sf::Vector2<T>& v)
	{
		return std::sqrtf(std::powf(static_cast<float>(v.x), 2.0f) + std::powf(static_cast<float>(v.y), 2.0f));
	}

	template <arithmetic T>
	constexpr float magnitude(const sf::Vector3<T>& v)
	{
		return std::sqrtf(std::powf(static_cast<float>(v.x), 2.0f) + std::powf(static_cast<float>(v.y), 2.0f) + std::powf(static_cast<float>(v.z), 2.0f));
	}

	template <arithmetic T>
	sf::Vector2<T> unit_vector(const sf::Vector2<T>& v)
	{
		constexpr float m = magnitude(v);
		return sf::Vector2<float>(v.x / m, v.y / m);
	}

	template <arithmetic T>
	sf::Vector3<T> unit_vector(const sf::Vector3<T>& v)
	{
		constexpr float m = magnitude(v);
		return sf::Vector3<float>(v.x / m, v.y / m, v.z / m);
	}

	template <arithmetic T>
	std::string to_string(const sf::Vector2<T>& v)
	{
		return '<' + std::to_string(v.x) + ", " + std::to_string(v.y) + '>';
	}

	template <arithmetic T>
	std::string to_string(const sf::Vector3<T>& v)
	{
		return '<' + std::to_string(v.x) + ", " + std::to_string(v.y) + ", " + std::to_string(v.z) + '>';
	}

	template <arithmetic T>
	std::wstring to_wstring(const sf::Vector2<T>& v)
	{
		return L'<' + std::to_wstring(v.x) + L", " + std::to_wstring(v.y) + L'>';
	}

	template <arithmetic T>
	std::wstring to_wstring(const sf::Vector3<T>& v)
	{
		return L'<' + std::to_wstring(v.x) + L", " + std::to_wstring(v.y) + L", " + std::to_wstring(v.z) + L'>';
	}
}

#endif // #ifdef INCLUDE_SFML