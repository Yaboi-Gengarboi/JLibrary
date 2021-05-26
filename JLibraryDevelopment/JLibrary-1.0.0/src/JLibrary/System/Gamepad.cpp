// JLibraryDevelopment
// Gamepad.cpp
// Created on 2021-05-25 by Justyn Durnford
// Last modified on 2021-05-25 by Justyn Durnford
// Source file for the Joystick and Gamepad classes.

#include <JLibrary/System/Gamepad.hpp>
using namespace std;
using namespace jl;

Joystick::Joystick()
{
	xDeadzone = 0.1f;
	yDeadzone = 0.1f;
}

Joystick::Joystick(float x_pos, float y_pos, float x_dz, float y_dz)
{
	position.set(x_pos, y_pos);
	xDeadzone = x_dz;
	yDeadzone = y_dz;
}

Joystick::Joystick(const Point2_32f& new_pos, float x_dz, float y_dz)
{
	position = new_pos;
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

Gamepad::Gamepad(unsigned char port, float lx_dz, float ly_dz, float rx_dz, float ry_dz)
{
	port_ = port;
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
	DWORD result = XInputGetState(port_ + 1u, &state_);

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
	XInputGetState(port_ + 1u, &state_);

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
		buttonStates_[0ull] = true;
	else
		buttonStates_[0ull] = false;
	if (state_.Gamepad.wButtons & XINPUT_GAMEPAD_B)
		buttonStates_[1ull] = true;
	else
		buttonStates_[1ull] = false;
	if (state_.Gamepad.wButtons & XINPUT_GAMEPAD_X)
		buttonStates_[2ull] = true;
	else
		buttonStates_[2ull] = false;
	if (state_.Gamepad.wButtons & XINPUT_GAMEPAD_Y)
		buttonStates_[3ull] = true;
	else
		buttonStates_[3ull] = true;
	if (state_.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP)
		buttonStates_[4ull] = true;
	else
		buttonStates_[4ull] = false;
	if (state_.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN)
		buttonStates_[5ull] = true;
	else
		buttonStates_[5ull] = false;
	if (state_.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT)
		buttonStates_[6ull] = true;
	else
		buttonStates_[6ull] = false;
	if (state_.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT)
		buttonStates_[7ull] = true;
	else
		buttonStates_[7ull] = false;
	if (state_.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER)
		buttonStates_[8ull] = true;
	else
		buttonStates_[8ull] = false;
	if (state_.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER)
		buttonStates_[9ull] = true;
	else
		buttonStates_[9ull] = false;
	if (state_.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_THUMB)
		buttonStates_[10ull] = true;
	else
		buttonStates_[10ull] = false;
	if (state_.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_THUMB)
		buttonStates_[11ull] = true;
	else
		buttonStates_[11ull] = false;
}

bool Gamepad::isButtonPressed(Button button) const
{
	return buttonStates_[static_cast<std::underlying_type<Button>::type>(button)];
}