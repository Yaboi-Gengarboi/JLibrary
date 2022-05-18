// JLibrary
// Gamepad.cpp
// Created on 2022-01-08 by Justyn Durnford
// Last modified on 2022-05-16 by Justyn Durnford
// Source file for the Joystick and Gamepad classes.

#include "Gamepad.hpp"
import MiscTemplateFunctions;

namespace jlib
{
	Joystick::Joystick()
	{
		xDeadzone = 0.1f;
		yDeadzone = 0.1f;
	}

	Joystick::Joystick(float X, float Y, float x_dz, float y_dz)
	{
		position.set(X, Y);
		xDeadzone = x_dz;
		yDeadzone = y_dz;
	}

	Joystick::Joystick(const Vector2f& Position, float x_dz, float y_dz)
	{
		position = Position;
		xDeadzone = x_dz;
		yDeadzone = y_dz;
	}

	void Joystick::setHorizontalDeadzone(float x_dz)
	{
		xDeadzone = x_dz;
	}

	void Joystick::setVerticalDeadzone(float y_dz)
	{
		yDeadzone = y_dz;
	}

	void Joystick::setDeadzones(float x_dz, float y_dz)
	{
		xDeadzone = x_dz;
		yDeadzone = y_dz;
	}

	bool Joystick::isStickInDeadZone() const
	{
		return (fabsf(position.x) <= xDeadzone) && (fabsf(position.y) <= yDeadzone);
	}

	Angle Joystick::getAngle() const
	{
		Angle angle;

		if (position.x >= 0.0f && position.y >= 0.0f)
		{
			angle = arctangent(position.y / position.x);
		}
		else if (position.x < 0.0f && position.y >= 0.0f)
		{
			angle = arctangent(position.y / position.x);
			angle.degree += 180.0f;
		}
		else if (position.x >= 0.0f && position.y < 0.0f)
		{
			angle = arctangent(position.y / position.x);
			angle.degree += 360.0f;
		}
		else if (position.x < 0.0f && position.y < 0.0f)
		{
			angle = arctangent(position.y / position.x);
			angle.degree += 180.0f;
		}

		return angle;
	}

	const Direction* Joystick::getDirection() const
	{
		const Angle angle(getAngle());

		if (angle.degree >= 45.0f && angle.degree < 135.0f)
			return static_cast<const Direction*>(&UP);
		if (angle.degree >= 135.0f && angle.degree < 225.0f)
			return static_cast<const Direction*>(&LEFT);
		if (angle.degree >= 225.0f && angle.degree < 315.0f)
			return static_cast<const Direction*>(&DOWN);

		return static_cast<const Direction*>(&RIGHT);
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

namespace jlib
{
	Gamepad::Gamepad()
	{
		_port = 0;
		leftTrigger = 0.0f;
		rightTrigger = 0.0f;
	}

	Gamepad::Gamepad(u8 Port, float lx_dz, float ly_dz, float rx_dz, float ry_dz)
	{
		_port = Port;
		leftTrigger = 0.0f;
		rightTrigger = 0.0f;
		leftStick.xDeadzone = lx_dz;
		leftStick.yDeadzone = ly_dz;
		rightStick.xDeadzone = rx_dz;
		rightStick.yDeadzone = ry_dz;
	}

	bool Gamepad::isConnected()
	{
		ZeroMemory(&_state, sizeof(XINPUT_STATE));
		DWORD result = XInputGetState(_port, &_state);

		return result == ERROR_SUCCESS;
	}

	u8 Gamepad::getPort() const
	{
		return _port + 1;
	}

	XINPUT_STATE Gamepad::getState() const
	{
		return _state;
	}

	void Gamepad::update()
	{
		// Update the Gamepad State.
		ZeroMemory(&_state, sizeof(XINPUT_STATE));
		XInputGetState(_port, &_state);

		// Update the left and right joysticks.
		leftStick.position.x =  static_cast<float>(_state.Gamepad.sThumbLX) / 32767.0f;
		leftStick.position.y =  static_cast<float>(_state.Gamepad.sThumbLY) / 32767.0f;
		rightStick.position.x = static_cast<float>(_state.Gamepad.sThumbRX) / 32767.0f;
		rightStick.position.y = static_cast<float>(_state.Gamepad.sThumbRY) / 32767.0f;

		// Clamp minimum joystick value.
		// This is necessary because the minumum value of a short
		// is further away from 0 than the maximum value is.
		clamp_min(leftStick.position.x, -1.0f);
		clamp_min(leftStick.position.y, -1.0f);
		clamp_min(rightStick.position.x, -1.0f);
		clamp_min(rightStick.position.y, -1.0f);

		// Update the left and right triggers.
		leftTrigger = _state.Gamepad.bLeftTrigger / 255.0f;
		rightTrigger = _state.Gamepad.bRightTrigger / 255.0f;
	}

	bool Gamepad::isButtonPressed(Button button) const
	{
		return _state.Gamepad.wButtons & button;
	}

	WORD Gamepad::getButtonStates() const
	{
		return _state.Gamepad.wButtons;
	}

	bool operator == (const Gamepad& A, const Gamepad& B)
	{
		return A.getPort() == B.getPort();
	}

	bool operator != (const Gamepad& A, const Gamepad& B)
	{
		return A.getPort() != B.getPort();
	}
}