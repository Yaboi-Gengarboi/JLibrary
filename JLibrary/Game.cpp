// JLibrary
// Game.cpp
// Created on 2022-04-03 by Justyn Durnford
// Last modified on 2022-04-03 by Justyn Durnford
// Source file for the Game base class.

#include "Game.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
using sf::ContextSettings;
using sf::String;
using sf::VideoMode;

namespace jlib
{
	Game::Game() : _window(VideoMode(800u, 600u), "", nonScalableWindowStyle) {}

	Game::Game(u32 window_width, u32 window_height, const String& title, 
		u32 style, const ContextSettings& settings) : 
		_window(VideoMode(window_width, window_height), title, style, settings) {}
}