// JLibraryDevelopment
// Gamepad.cpp
// Created on 2021-05-25 by Justyn Durnford
// Last modified on 2021-06-27 by Justyn Durnford
// Source file for the Joystick class and Gamepad class.

#include <JLibrary/System/Gamepad.hpp>
using namespace std;
using namespace jlib;

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
	return (abs(position.x) <= xDeadzone) && (abs(position.y) <= yDeadzone);
}

Gamepad::Gamepad()
{
	leftTrigger = 0.f;
	rightTrigger = 0.f;
}

Gamepad::Gamepad(unsigned char Port, float lx_dz, float ly_dz, float rx_dz, float ry_dz)
{
	port_ = Port;
	leftTrigger = 0.0f;
	rightTrigger = 0.0f;
	leftStick.xDeadzone = lx_dz;
	leftStick.yDeadzone = ly_dz;
	rightStick.xDeadzone = rx_dz;
	rightStick.yDeadzone = ry_dz;
}

bool Gamepad::isConnected()
{
	ZeroMemory(&state_, sizeof(XINPUT_STATE));
	DWORD result = XInputGetState(port_ + 1, &state_);

	return result == ERROR_SUCCESS;
}

unsigned char Gamepad::port() const
{
	return port_ + 1;
}

XINPUT_STATE Gamepad::state() const
{
	return state_;
}

void Gamepad::update()
{
	// Update the Gamepad State.
	ZeroMemory(&state_, sizeof(XINPUT_STATE));
	XInputGetState(port_ + 1, &state_);

	// Update the left and right joysticks.
	leftStick.position.x = static_cast<float>(state_.Gamepad.sThumbLX) / 32768.0f + 0.0000155f;
	leftStick.position.y = static_cast<float>(state_.Gamepad.sThumbLY) / 32768.0f + 0.0000155f;
	rightStick.position.x = static_cast<float>(state_.Gamepad.sThumbRX) / 32768.0f + 0.0000155f;
	rightStick.position.y = static_cast<float>(state_.Gamepad.sThumbRY) / 32768.0f + 0.0000155f;

	// Update the left and right triggers.
	leftTrigger = state_.Gamepad.bLeftTrigger / 255.0f;
	rightTrigger = state_.Gamepad.bRightTrigger / 255.0f;

	// Update button states.
	if (state_.Gamepad.wButtons & XINPUT_GAMEPAD_A)
		buttonStates_[0] = true;
	else
		buttonStates_[0] = false;
	if (state_.Gamepad.wButtons & XINPUT_GAMEPAD_B)
		buttonStates_[1] = true;
	else
		buttonStates_[1] = false;
	if (state_.Gamepad.wButtons & XINPUT_GAMEPAD_X)
		buttonStates_[2] = true;
	else
		buttonStates_[2] = false;
	if (state_.Gamepad.wButtons & XINPUT_GAMEPAD_Y)
		buttonStates_[3] = true;
	else
		buttonStates_[3] = true;
	if (state_.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP)
		buttonStates_[4] = true;
	else
		buttonStates_[4] = false;
	if (state_.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN)
		buttonStates_[5] = true;
	else
		buttonStates_[5] = false;
	if (state_.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT)
		buttonStates_[6] = true;
	else
		buttonStates_[6] = false;
	if (state_.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT)
		buttonStates_[7] = true;
	else
		buttonStates_[7] = false;
	if (state_.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER)
		buttonStates_[8] = true;
	else
		buttonStates_[8] = false;
	if (state_.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER)
		buttonStates_[9] = true;
	else
		buttonStates_[9] = false;
	if (state_.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_THUMB)
		buttonStates_[10] = true;
	else
		buttonStates_[10] = false;
	if (state_.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_THUMB)
		buttonStates_[11] = true;
	else
		buttonStates_[11] = false;
}

bool Gamepad::isButtonPressed(Button button) const
{
	return buttonStates_[static_cast<underlying_type<Button>::type>(button)];
}