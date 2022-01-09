// JLibrary
// Gamepad.hpp
// Created on 2022-01-08 by Justyn Durnford
// Last modified on 2022-01-08 by Justyn Durnford
// Header file for the Joystick and Gamepad classes.

#pragma once

#pragma comment(lib, "XInput.lib")
#pragma comment(lib, "Xinput9_1_0.lib")

#include "Angle.hpp"
#include "Direction.hpp"
#include "IntegerTypedefs.hpp"

#include <windows.h>
#include <xinput.h>

import Vector2;

namespace jlib
{
	// 
	class Joystick
	{
		public:

		Vector2f position;
		float xDeadzone, yDeadzone;

		// Default constructor.
		// Sets the position of the Joystick to (0, 0).
		// Sets the deadzones of the Joystick to 0.1f.
		Joystick();

		// 3-float constructor.
		// Sets the position of the Joystick to (X, Y).
		// Sets the horizontal deadzone of the Joystick to x_dz.
		// Sets the vertical deadzone of the Joysticl to y_dz.
		Joystick(float X, float Y, float x_dz, float y_dz);

		// Vector2f& float constructor.
		// Sets the position of the Joystick to Position.
		// Sets the horizontal deadzone of the Joystick to x_dz.
		// Sets the vertical deadzone of the Joysticl to y_dz.
		Joystick(const Vector2f& Position, float x_dz, float y_dz);

		// Sets the horizontal deadzone of the Joystick to x_dz.
		void setHorizontalDeadzone(float x_dz);

		// Sets the vertical deadzone of the Joysticl to y_dz.
		void setVerticalDeadzone(float y_dz);

		// Sets the horizontal deadzone of the Joystick to x_dz.
		// Sets the vertical deadzone of the Joysticl to y_dz.
		void setDeadzones(float x_dz, float y_dz);

		// Returns true if the Joystick's position is within its deadzone.
		bool isStickInDeadZone() const;

		// Returns the angle of the Joystick.
		Angle getAngle() const;

		// Returns the direction of the Joystick's angle.
		const Direction* getDirection() const;
	};
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

namespace jlib
{
	// 
	class Gamepad
	{
		public:

		enum Button
		{
			A = XINPUT_GAMEPAD_A,
			B = XINPUT_GAMEPAD_B,
			X = XINPUT_GAMEPAD_X,
			Y = XINPUT_GAMEPAD_Y,
			DPadUp = XINPUT_GAMEPAD_DPAD_UP,
			DPadDown = XINPUT_GAMEPAD_DPAD_DOWN,
			DPadLeft = XINPUT_GAMEPAD_DPAD_LEFT,
			DPadRight = XINPUT_GAMEPAD_DPAD_RIGHT,
			LShoulder = XINPUT_GAMEPAD_LEFT_SHOULDER,
			RShoulder = XINPUT_GAMEPAD_RIGHT_SHOULDER,
			LThumbstick = XINPUT_GAMEPAD_LEFT_THUMB,
			RThumbstick = XINPUT_GAMEPAD_RIGHT_THUMB,
			Start = XINPUT_GAMEPAD_START,
			Back = XINPUT_GAMEPAD_BACK,
			Count = 14
		};

		private:

		u8 _port;
		XINPUT_STATE _state;
		WORD _oldButtonStates;

		public:

		Joystick leftStick, rightStick;
		float leftTrigger, rightTrigger;

		// Default constructor.
		// Sets the horizontal and vertical deadzones of each Joystick to 0.1f.
		// Sets the values of each Trigger to 0.0f.
		Gamepad();

		// 1-unsigned char, 4-float constructor.
		// Sets the port of the Gamepad to Port.
		// Sets the horizontal deadzone for the left Joystick to lx_dz.
		// Sets the vertical deadzone for the left Joystick to ly_dz.
		// Sets the horizontal deadzone for the right Joystick to rx_dz.
		// Sets the vertical deadzone for the right Joystick to ry_dz.
		// Sets the values of each Trigger to 0.0f.
		Gamepad(u8 Port, float lx_dz, float ly_dz, float rx_dz, float ry_dz);

		// 
		bool isConnected();

		// 
		u8 getPort() const;

		// 
		XINPUT_STATE getState() const;

		// 
		bool isButtonPressed(Button button) const;

		// 
		bool isButtonHeld(Button button) const;

		// 
		bool isButtonReleased(Button button) const;

		// 
		void update();
	};
}

// Overload of binary operator ==
bool operator == (const jlib::Gamepad& A, const jlib::Gamepad& B);

// Overload of binary operator !=
bool operator != (const jlib::Gamepad& A, const jlib::Gamepad& B);