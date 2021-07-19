// JLibraryDevelopment
// Event.hpp
// Created on 2021-07-08 by Justyn Durnford
// Last modified on 2021-07-16 by Justyn Durnford
// Header file that defines system events.

#pragma once

#include <JLibrary/System/Gamepad.hpp>
#include <JLibrary/System/Integer.hpp>
#include <JLibrary/System/Keyboard.hpp>
#include <JLibrary/System/Mouse.hpp>

namespace jlib
{
	// Defines a system event and its parameters.
	class Event
	{
		public:

		enum EventType
		{
			Closed,                 // The window requested to be closed (no data)
			Resized,                // The window was resized (data in event.size)
			LostFocus,              // The window lost the focus (no data)
			GainedFocus,            // The window gained the focus (no data)
			TextEntered,            // A character was entered (data in event.text)
			KeyPressed,             // A key was pressed (data in event.key)
			KeyReleased,            // A key was released (data in event.key)
			MouseWheelMoved,        // The mouse wheel was scrolled (data in event.mouseWheel) (deprecated)
			MouseWheelScrolled,     // The mouse wheel was scrolled (data in event.mouseWheelScroll)
			MouseButtonPressed,     // A mouse button was pressed (data in event.mouseButton)
			MouseButtonReleased,    // A mouse button was released (data in event.mouseButton)
			MouseMoved,             // The mouse cursor moved (data in event.mouseMove)
			MouseEntered,           // The mouse cursor entered the area of the window (no data)
			MouseLeft,              // The mouse cursor left the area of the window (no data)
			Count                   // Keep last -- the total number of event types
		};

		struct SizeEvent
		{
			u32 width;
			u32 height;
		};

		struct KeyEvent
		{
			Keyboard::Key code;

			// Flags: 
			// - [0]: alt
			// - [1]: control
			// - [2]: shift
			// - [3]: system
			std::bitset<4> flags;
		};

		struct TextEvent
		{
			u32 unicode;
		};

		struct MouseMoveEvent
		{
			i32 x;
			i32 y;
		};

		struct MouseButtonEvent
		{
			Mouse::Button button;
			i32           x;     
			i32           y;     
		};

		struct MouseWheelEvent
		{
			i32 delta;
			i32 x;    
			i32 y;    
		};

		struct MouseWheelScrollEvent
		{
			Mouse::Wheel wheel; 
			float        delta; 
			i32          x;     
			i32          y;     
		};

		union
		{
			SizeEvent             size;              // Size event parameters (Event::Resized)
			KeyEvent              key;               // Key event parameters (Event::KeyPressed, Event::KeyReleased)
			TextEvent             text;              // Text event parameters (Event::TextEntered)
			MouseMoveEvent        mouseMove;         // Mouse move event parameters (Event::MouseMoved)
			MouseButtonEvent      mouseButton;       // Mouse button event parameters (Event::MouseButtonPressed, Event::MouseButtonReleased)
			MouseWheelEvent       mouseWheel;        // Mouse wheel event parameters (Event::MouseWheelMoved) (deprecated)
			MouseWheelScrollEvent mouseWheelScroll;  // Mouse wheel event parameters (Event::MouseWheelScrolled)
		};

		EventType type;

		Event() { type = EventType::Count; }
	};
}