// JLibraryDevelopment
// Gamepad.hpp
// Created on 2021-05-25 by Justyn Durnford
// Last modified on 2021-05-28 by Justyn Durnford
// Header file for the Joystick and Gamepad classes.

#pragma once
#pragma comment(lib,"XInput.lib")
#pragma comment(lib,"Xinput9_1_0.lib")

#include <JLibrary/Math/Point2.hpp>
#include <bitset>
#include <Windows.h>
#include <Xinput.h>

class Joystick
{
	public:

	jl::Point2_32f position;
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

	// Point2_32f& float constructor.
	// Sets the position of the Joystick to Position.
	// Sets the horizontal deadzone of the Joystick to x_dz.
	// Sets the vertical deadzone of the Joysticl to y_dz.
	Joystick(const jl::Point2_32f& Position, float x_dz, float y_dz);

	// Copy constructor.
	Joystick(const Joystick& other) = delete;

	// Move constructor.
	Joystick(Joystick&& other) = delete;

	// Copy assignment operator.
	Joystick& operator = (const Joystick& other) = delete;

	// Move assignment operator.
	Joystick& operator = (Joystick&& other) = delete;

	// Destructor.
	~Joystick() = default;

	// Sets the horizontal deadzone of the Joystick to x_dz.
	void setHorizontalDeadzone(float x_dz);

	// Sets the vertical deadzone of the Joysticl to y_dz.
	void setVerticalDeadzone(float y_dz);

	// Sets the horizontal deadzone of the Joystick to x_dz.
	// Sets the vertical deadzone of the Joysticl to y_dz.
	void setDeadzones(float x_dz, float y_dz);

	// Returns true if the Joystick's position is within its deadzone.
	bool isStickInDeadZone() const;
};

class Gamepad
{
	public:

	enum Button
	{
		A = 0,
		B = 1,
		X = 2,
		Y = 3,
		DPadUp = 4,
		DPadDown = 5,
		DPadLeft = 6,
		DPadRight = 7,
		LShoulder = 8,
		RShoulder = 9,
		LThumbstick = 10,
		RThumbstick = 11,
		Start = 12,
		Select = 13
	};

	private:

	unsigned char port_;
	XINPUT_STATE state_;
	std::bitset<14> buttonStates_;

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
	Gamepad(unsigned char Port, float lx_dz, float ly_dz, float rx_dz, float ry_dz);

	// Copy constructor.
	Gamepad(const Gamepad& other) = delete;

	// Move constructor.
	Gamepad(Gamepad&& other) = delete;

	// Copy assignment operator.
	Gamepad& operator = (const Gamepad& other) = delete;

	// Move assignment operator.
	Gamepad& operator = (Gamepad&& other) = delete;

	// Destructor.
	~Gamepad() = default;

	// 
	bool isConnected();

	// 
	unsigned char port() const;

	// 
	XINPUT_STATE state() const;

	// 
	bool isButtonPressed(Button button) const;

	// 
	void update();
};