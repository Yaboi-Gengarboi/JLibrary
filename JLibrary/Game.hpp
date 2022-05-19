// JLibrary
// Game.hpp
// Created on 2022-04-03 by Justyn Durnford
// Last modified on 2022-05-18 by Justyn Durnford
// Header file for the Game base class.

#pragma once

#include "IntegerTypedefs.hpp"
#include "Time.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

namespace jlib
{
	const u32 nonScalableWindowStyle = sf::Style::Titlebar | sf::Style::Close;

	// 
	class Game
	{
		protected:

		sf::RenderWindow _window;
		sf::Event _event;
		Clock _clock;

		// 
		virtual void processEvents() = 0;

		// 
		virtual void update(Duration dt) = 0;

		// 
		virtual void render() = 0;

		public:

		// 
		Game();

		// 
		Game(u32 window_width, u32 window_height, const sf::String& title, 
			 u32 style = nonScalableWindowStyle,
			 const sf::ContextSettings& settings = sf::ContextSettings());

		// 
		virtual ~Game() = default;

		// 
		virtual void run() = 0;
	};
}