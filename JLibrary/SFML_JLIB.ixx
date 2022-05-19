// JLibrary
// SFML_JLIB.ixx
// Created on 2022-01-09 by Justyn Durnford
// Last modified on 2022-05-18 by Justyn Durnford
// Module file defining several functions to convert and copy data between SFML and JLIB code.

module;

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "Arithmetic.hpp"
#include "Color.hpp"

#include <cmath>

export module SFML_JLIB;

import Rect;
import Square;
import Vector2;
import Vector3;

export namespace jlib
{
	template <arithmetic T>
	sf::Vector2<T> to_sfml(const Vector2<T>& v)
	{
		return sf::Vector2<T>(v.x, v.y);
	}

	template <arithmetic T>
	sf::Vector3<T> to_sfml(const Vector3<T>& v)
	{
		return sf::Vector3<T>(v.x, v.y, v.z);
	}

	template <arithmetic T>
	sf::Rect<T> to_sfml(const Rect<T>& r)
	{
		return sf::Rect<T>(r.x, r.y, r.w, r.h);
	}

	template <arithmetic T>
	sf::Rect<T> to_sfml(const Square<T>& s)
	{
		return sf::Rect<T>(s.x, s.y, s.l, s.l);
	}

	sf::Color to_sfml(const Color& c)
	{
		return sf::Color(c.r, c.g, c.b, c.a);
	}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

	template <arithmetic T>
	Vector2<T> to_jlib(const sf::Vector2<T>& v)
	{
		return Vector2<T>(v.x, v.y);
	}

	template <arithmetic T>
	Vector3<T> to_jlib(const sf::Vector3<T>& v)
	{
		return jVector3<T>(v.x, v.y, v.z);
	}

	template <arithmetic T>
	Rect<T> to_jlib(const sf::Rect<T>& r)
	{
		return Rect<T>(r.left, r.top, r.width, r.height);
	}

	Color to_jlib(const sf::Color& c)
	{
		return Color(c.r, c.g, c.b, c.a);
	}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

	template <arithmetic T>
	void copy_data(const jlib::Vector2<T>& from, sf::Vector2<T>& to)
	{
		to.x = from.x;
		to.y = from.y;
	}

	template <arithmetic T>
	void copy_data(const jlib::Vector3<T>& from, sf::Vector3<T>& to)
	{
		to.x = from.x;
		to.y = from.y;
		to.z = from.z;
	}

	template <arithmetic T>
	void copy_data(const jlib::Rect<T>& from, sf::Rect<T>& to)
	{
		to.left = from.x;
		to.top = from.y;
		to.width = from.w;
		to.height = from.h;
	}

	template <arithmetic T>
	void copy_data(const jlib::Square<T>& from, sf::Rect<T>& to)
	{
		to.left = from.x;
		to.top = from.y;
		to.width = from.l;
		to.height = from.l;
	}

	void copy_data(const jlib::Color& from, sf::Color& to)
	{
		to.r = from.r;
		to.g = from.g;
		to.b = from.b;
		to.a = from.a;
	}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

	template <arithmetic T>
	void copy_data(const sf::Vector2<T>& from, jlib::Vector2<T>& to)
	{
		to.x = from.x;
		to.y = from.y;
	}

	template <arithmetic T>
	void copy_data(const sf::Vector3<T>& from, jlib::Vector3<T>& to)
	{
		to.x = from.x;
		to.y = from.y;
		to.z = from.z;
	}

	template <arithmetic T>
	void copy_data(const sf::Rect<T>& from, jlib::Rect<T>& to)
	{
		to.x = from.left;
		to.y = from.top;
		to.w = from.width;
		to.h = from.height;
	}

	void copy_data(const sf::Color& from, jlib::Color& to)
	{
		to.r = from.r;
		to.g = from.g;
		to.b = from.b;
		to.a = from.a;
	}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

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