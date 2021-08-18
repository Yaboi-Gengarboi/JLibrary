// JLIB.cpp
// Created on 2021-08-07 by Justyn Durnford
// Last modified on 2021-08-18 by Justyn Durnford

#pragma warning(disable : 4996)

#include "JLIB.hpp"
using namespace jlib;

#include <algorithm>
using std::max;
using std::min;

#include <array>
using std::array;

#include <chrono>
using std::chrono::duration;
using std::chrono::system_clock;
using std::chrono::time_point;

#include <cmath>
using std::acosf;
using std::asinf;
using std::atanf;
using std::cosf;
using std::fabsf;
using std::fmodf;
using std::sinf;
using std::tanf;

#include <codecvt>
using std::codecvt_utf8;

#include <compare>
using std::strong_ordering;

#include <cstddef>
using std::ptrdiff_t;
using std::size_t;

#include <cstring>
using std::memcpy;

#include <initializer_list>
using std::initializer_list;

#include <iostream>
using std::cout;
using std::ostream;
using std::wostream;
using std::endl;

#include <locale>
using std::wstring_convert;

#include <numbers>
using std::numbers::pi_v;

#include <cstddef>
using std::size_t;

#include <stdexcept>
using std::out_of_range;

#include <string>
using std::string;
using std::wstring;
using std::to_string;
using std::to_wstring;

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

namespace jlib
{
	string wstr2str(const wstring& wstr)
	{
		wstring_convert<codecvt_utf8<wchar_t>, wchar_t> converter;
		return converter.to_bytes(wstr);
	}

	wstring str2wstr(const string& str)
	{
		wstring_convert<codecvt_utf8<wchar_t>, wchar_t> converter;
		return converter.from_bytes(str);
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

namespace jlib
{
	String::String(size_type len)
	{
		_data.resize(len);
	}

	String::String(char c, size_type count)
	{
		string str;
		str.resize(count, c);
		_data = str2wstr(str);
	}

	String::String(wchar_t c, size_type count)
	{
		_data.resize(count, c);
	}

	String::String(const char* cstr)
	{
		string str(cstr);
		_data = str2wstr(str);
	}

	String::String(const wchar_t* wcstr)
	{
		_data = wcstr;
	}

	String::String(const string& str)
	{
		_data = str2wstr(str);
	}

	String::String(const wstring& wstr)
	{
		_data = wstr;
	}

	String& String::operator = (const char* cstr)
	{
		string str(cstr);
		_data = str2wstr(str);
		return *this;
	}

	String& String::operator = (const wchar_t* wcstr)
	{
		_data = wcstr;
		return *this;
	}

	String& String::operator = (const string& str)
	{
		_data = str2wstr(str);
		return *this;
	}

	String& String::operator = (const wstring& wstr)
	{
		_data = wstr;
		return *this;
	}

	String::reference String::at(size_type index)
	{
		return _data.at(index);
	}

	String::const_reference String::at(size_type index) const
	{
		return _data.at(index);
	}

	String::reference String::front()
	{
		return _data.front();
	}

	String::const_reference String::front() const
	{
		return _data.front();
	}

	String::reference String::back()
	{
		return _data.back();
	}

	String::const_reference String::back() const
	{
		return _data.back();
	}

	constexpr String::size_type String::size() const noexcept
	{
		return _data.size();
	}

	constexpr String::size_type String::capacity() const noexcept
	{
		return _data.capacity();
	}

	constexpr bool String::isEmpty() const noexcept
	{
		return _data.empty();
	}

	constexpr String::pointer String::data() noexcept
	{
		return &(_data[0]);
	}

	constexpr String::const_pointer String::data() const noexcept
	{
		return _data.data();
	}

	constexpr String::iterator String::begin() noexcept
	{
		return _data.begin();
	}

	constexpr String::const_iterator String::begin() const noexcept
	{
		return _data.cbegin();
	}

	constexpr String::const_iterator String::cbegin() const noexcept
	{
		return _data.cbegin();
	}

	constexpr String::iterator String::end() noexcept
	{
		return _data.end();
	}

	constexpr String::const_iterator String::end() const noexcept
	{
		return _data.cend();
	}

	constexpr String::const_iterator String::cend() const noexcept
	{
		return _data.cend();
	}

	constexpr String::reverse_iterator String::rbegin() noexcept
	{
		return _data.rbegin();
	}

	constexpr String::const_reverse_iterator String::rbegin() const noexcept
	{
		return _data.crbegin();
	}

	constexpr String::const_reverse_iterator String::crbegin() const noexcept
	{
		return _data.crbegin();
	}

	constexpr String::reverse_iterator String::rend() noexcept
	{
		return _data.rend();
	}

	constexpr String::const_reverse_iterator String::rend() const noexcept
	{
		return _data.crend();
	}

	constexpr String::const_reverse_iterator String::crend() const noexcept
	{
		return _data.crend();
	}

	String::size_type String::find(const String& str, size_type start) const noexcept
	{
		return _data.find(str._data, start);
	}

	constexpr void String::clear() noexcept
	{
		_data.clear();
	}

	void String::shrink_to_fit()
	{
		_data.shrink_to_fit();
	}

	void String::append(char c, size_type count)
	{
		_data.append(count, static_cast<wchar_t>(c));
	}

	void String::append(wchar_t c, size_type count)
	{
		_data.append(count, c);
	}

	void String::append(const String& str)
	{
		_data.append(str._data);
	}

	void String::resize(size_type len)
	{
		_data.resize(len);
	}

	void String::resize(size_type len, char c)
	{
		_data.resize(len, static_cast<wchar_t>(c));
	}

	void String::resize(size_type len, wchar_t c)
	{
		_data.resize(len, c);
	}

	void String::insert(const String& str, size_type pos)
	{
		_data.insert(pos, str._data);
	}

	void String::erase(size_type pos, size_type count)
	{
		_data.erase(pos, count);
	}

	void String::erase(const_iterator first, const_iterator last)
	{
		_data.erase(first, last);
	}

	void String::replace(size_type pos, size_type len, const String& str)
	{
		_data.replace(pos, len, str._data);
	}

	String String::substr(size_type pos, size_type len) const
	{
		return String(_data.substr(pos, len));
	}

	String String::substr(const_iterator first, const_iterator last) const
	{
		if (first >= last)
			return String(L"");

		String newstr;
		size_type i = 0;
		const_iterator pos = first;

		while (pos != last)
		{
			newstr[i] = *pos;
			++pos;
		}

		return newstr;
	}

	void String::replace(const String& oldstr, const String& newstr)
	{
		size_type step = newstr.size();
		size_type len = oldstr.size();
		size_type pos = find(oldstr);

		// Replace each occurrence of search.
		while (pos != npos)
		{
			replace(pos, len, newstr);
			pos = find(oldstr, pos + step);
		}
	}

	constexpr int String::compareWith(const String& other) const
	{
		return _data.compare(other._data);
	}

	string String::toString() const
	{
		return wstr2str(_data);
	}

	wstring String::toWideString() const
	{
		return _data;
	}

	String::reference String::operator [] (size_type index)
	{
		return _data[index];
	}

	String::const_reference String::operator [] (size_type index) const
	{
		return _data[index];
	}

	String& String::operator += (char c)
	{
		append(c, 1);
		return *this;
	}

	String& String::operator += (wchar_t c)
	{
		append(c, 1);
		return *this;
	}

	String& String::operator += (const String& str)
	{
		append(str);
		return *this;
	}

	String::operator string() const
	{
		return toString();
	}

	String::operator wstring() const
	{
		return _data;
	}
}

String operator + (const String& A, const String& B)
{
	String C(A);
	C += B;
	return C;
}

bool operator == (const String& A, const String& B)
{
	return A.compareWith(B) == 0;
}

bool operator != (const String& A, const String& B)
{
	return A.compareWith(B) != 0;
}

bool operator < (const String& A, const String& B)
{
	return A.compareWith(B) < 0;
}

bool operator <= (const String& A, const String& B)
{
	return A.compareWith(B) <= 0;
}

bool operator > (const String& A, const String& B)
{
	return A.compareWith(B) > 0;
}

bool operator >= (const String& A, const String& B)
{
	return A.compareWith(B) >= 0;
}

strong_ordering operator <=> (const String& A, const String& B)
{
	int result = A.compareWith(B);

	if (result < 0)
		return strong_ordering::less;
	if (result > 0)
		return strong_ordering::greater;
	return strong_ordering::equivalent;
}

ostream& operator << (ostream& os, const String& A)
{
	os << A.toString();
	return os;
}

wostream& operator << (wostream& wos, const String& A)
{
	wos << A.toWideString();
	return wos;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

namespace jlib
{
	Angle::Angle()
	{
		degree = 0.0f;
	}

	Angle::Angle(float Degree)
	{
		degree = Degree;
	}

	Angle& Angle::operator = (float Degree)
	{
		degree = Degree;
		return *this;
	}

	string Angle::toString() const
	{
		return to_string(degree) + '\370';
	}

	constexpr float to_radians(float degree)
	{
		return degree * pi_v<float> / 180.0f;
	}

	constexpr float to_degrees(float radian)
	{
		return radian * 180.f / pi_v<float>;
	}

	float sine(Angle angle)
	{
		if (fmodf(angle.degree, 180.0f) == 0.0f)
			return 0.0f;

		return sinf(to_radians(angle.degree));
	}

	float cosine(Angle angle)
	{
		if ((fmodf(angle.degree, 90.0f) == 0.0f) && ((fmodf(angle.degree, 180.0f) != 0.0f)))
			return 0.0f;

		return cosf(to_radians(angle.degree));
	}

	float tangent(Angle angle)
	{
		return tanf(to_radians(angle.degree));
	}

	Angle arcsine(float value)
	{
		return Angle(to_degrees(asinf(value)));
	}

	Angle arccosine(float value)
	{
		return Angle(to_degrees(acosf(value)));
	}

	Angle arctangent(float value)
	{
		return Angle(to_degrees(atanf(value)));
	}

	Angle& least(Angle& A, Angle& B)
	{
		if (A.degree < B.degree)
			return A;
		if (A.degree > B.degree)
			return B;
		return A;
	}

	Angle& greatest(Angle& A, Angle& B)
	{
		if (A.degree < B.degree)
			return B;
		if (A.degree > B.degree)
			return A;
		return A;
	}
}

bool operator == (Angle A, Angle B)
{
	return A.degree == B.degree;
}

bool operator == (Angle A, float degree)
{
	return A.degree == degree;
}

bool operator != (Angle A, Angle B)
{
	return A.degree != B.degree;
}

bool operator != (Angle A, float degree)
{
	return A.degree != degree;
}

bool operator < (Angle A, Angle B)
{
	return A.degree < B.degree;
}

bool operator < (Angle A, float degree)
{
	return A.degree < degree;
}

bool operator <= (Angle A, Angle B)
{
	return A.degree <= B.degree;
}

bool operator <= (Angle A, float degree)
{
	return A.degree <= degree;
}

bool operator > (Angle A, Angle B)
{
	return A.degree > B.degree;
}

bool operator > (Angle A, float degree)
{
	return A.degree > degree;
}

bool operator >= (Angle A, Angle B)
{
	return A.degree >= B.degree;
}

bool operator >= (Angle A, float degree)
{
	return A.degree >= degree;
}

strong_ordering operator <=> (Angle A, Angle B)
{
	if (A.degree < B.degree)
		return strong_ordering::less;
	if (A.degree > B.degree)
		return strong_ordering::greater;
	return strong_ordering::equivalent;
}

strong_ordering operator <=> (Angle A, float degree)
{
	if (A.degree < degree)
		return strong_ordering::less;
	if (A.degree > degree)
		return strong_ordering::greater;
	return strong_ordering::equivalent;
}

Angle operator - (Angle A)
{
	return Angle(-A.degree);
}

Angle operator + (Angle A, Angle B)
{
	return Angle(A.degree + B.degree);
}

Angle operator + (Angle A, float degree)
{
	return Angle(A.degree + degree);
}

Angle operator - (Angle A, Angle B)
{
	return Angle(A.degree - B.degree);
}

Angle operator - (Angle A, float degree)
{
	return Angle(A.degree - degree);
}

Angle operator * (Angle A, float scalar)
{
	return Angle(A.degree * scalar);
}

Angle operator / (Angle A, float scalar)
{
	return Angle(A.degree / scalar);
}

Angle& operator += (Angle& A, Angle B)
{
	A.degree += B.degree;
	return A;
}

Angle& operator += (Angle& A, float degree)
{
	A.degree += degree;
	return A;
}

Angle& operator -= (Angle& A, Angle B)
{
	A.degree -= B.degree;
	return A;
}

Angle& operator -= (Angle& A, float degree)
{
	A.degree -= degree;
	return A;
}

Angle& operator *= (Angle& A, float scalar)
{
	A.degree *= scalar;
	return A;
}

Angle& operator /= (Angle& A, float scalar)
{
	A.degree /= scalar;
	return A;
}

ostream& operator << (ostream& os, Angle A)
{
	os << A.toString();
	return os;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

namespace jlib
{
	bool Keyboard::isKeyPressed(Key key)
	{
		int virtual_key = 0;

		switch (key)
		{
			case Keyboard::A:          virtual_key = 'A';           break;
			case Keyboard::B:          virtual_key = 'B';           break;
			case Keyboard::C:          virtual_key = 'C';           break;
			case Keyboard::D:          virtual_key = 'D';           break;
			case Keyboard::E:          virtual_key = 'E';           break;
			case Keyboard::F:          virtual_key = 'F';           break;
			case Keyboard::G:          virtual_key = 'G';           break;
			case Keyboard::H:          virtual_key = 'H';           break;
			case Keyboard::I:          virtual_key = 'I';           break;
			case Keyboard::J:          virtual_key = 'J';           break;
			case Keyboard::K:          virtual_key = 'K';           break;
			case Keyboard::L:          virtual_key = 'L';           break;
			case Keyboard::M:          virtual_key = 'M';           break;
			case Keyboard::N:          virtual_key = 'N';           break;
			case Keyboard::O:          virtual_key = 'O';           break;
			case Keyboard::P:          virtual_key = 'P';           break;
			case Keyboard::Q:          virtual_key = 'Q';           break;
			case Keyboard::R:          virtual_key = 'R';           break;
			case Keyboard::S:          virtual_key = 'S';           break;
			case Keyboard::T:          virtual_key = 'T';           break;
			case Keyboard::U:          virtual_key = 'U';           break;
			case Keyboard::V:          virtual_key = 'V';           break;
			case Keyboard::W:          virtual_key = 'W';           break;
			case Keyboard::X:          virtual_key = 'X';           break;
			case Keyboard::Y:          virtual_key = 'Y';           break;
			case Keyboard::Z:          virtual_key = 'Z';           break;
			case Keyboard::Num0:       virtual_key = '0';           break;
			case Keyboard::Num1:       virtual_key = '1';           break;
			case Keyboard::Num2:       virtual_key = '2';           break;
			case Keyboard::Num3:       virtual_key = '3';           break;
			case Keyboard::Num4:       virtual_key = '4';           break;
			case Keyboard::Num5:       virtual_key = '5';           break;
			case Keyboard::Num6:       virtual_key = '6';           break;
			case Keyboard::Num7:       virtual_key = '7';           break;
			case Keyboard::Num8:       virtual_key = '8';           break;
			case Keyboard::Num9:       virtual_key = '9';           break;
			case Keyboard::Escape:     virtual_key = VK_ESCAPE;     break;
			case Keyboard::LControl:   virtual_key = VK_LCONTROL;   break;
			case Keyboard::LShift:     virtual_key = VK_LSHIFT;     break;
			case Keyboard::LAlt:       virtual_key = VK_LMENU;      break;
			case Keyboard::LWindow:    virtual_key = VK_LWIN;       break;
			case Keyboard::RControl:   virtual_key = VK_RCONTROL;   break;
			case Keyboard::RShift:     virtual_key = VK_RSHIFT;     break;
			case Keyboard::RAlt:       virtual_key = VK_RMENU;      break;
			case Keyboard::RWindow:    virtual_key = VK_RWIN;       break;
			case Keyboard::Menu:       virtual_key = VK_APPS;       break;
			case Keyboard::LBracket:   virtual_key = VK_OEM_4;      break;
			case Keyboard::RBracket:   virtual_key = VK_OEM_6;      break;
			case Keyboard::Semicolon:  virtual_key = VK_OEM_1;      break;
			case Keyboard::Comma:      virtual_key = VK_OEM_COMMA;  break;
			case Keyboard::Period:     virtual_key = VK_OEM_PERIOD; break;
			case Keyboard::Quote:      virtual_key = VK_OEM_7;      break;
			case Keyboard::Slash:      virtual_key = VK_OEM_2;      break;
			case Keyboard::Backslash:  virtual_key = VK_OEM_5;      break;
			case Keyboard::Tilde:      virtual_key = VK_OEM_3;      break;
			case Keyboard::Equal:      virtual_key = VK_OEM_PLUS;   break;
			case Keyboard::Hyphen:     virtual_key = VK_OEM_MINUS;  break;
			case Keyboard::Space:      virtual_key = VK_SPACE;      break;
			case Keyboard::Enter:      virtual_key = VK_RETURN;     break;
			case Keyboard::Backspace:  virtual_key = VK_BACK;       break;
			case Keyboard::Tab:        virtual_key = VK_TAB;        break;
			case Keyboard::PageUp:     virtual_key = VK_PRIOR;      break;
			case Keyboard::PageDown:   virtual_key = VK_NEXT;       break;
			case Keyboard::End:        virtual_key = VK_END;        break;
			case Keyboard::Home:       virtual_key = VK_HOME;       break;
			case Keyboard::Insert:     virtual_key = VK_INSERT;     break;
			case Keyboard::Delete:     virtual_key = VK_DELETE;     break;
			case Keyboard::Add:        virtual_key = VK_ADD;        break;
			case Keyboard::Subtract:   virtual_key = VK_SUBTRACT;   break;
			case Keyboard::Multiply:   virtual_key = VK_MULTIPLY;   break;
			case Keyboard::Divide:     virtual_key = VK_DIVIDE;     break;
			case Keyboard::Left:       virtual_key = VK_LEFT;       break;
			case Keyboard::Right:      virtual_key = VK_RIGHT;      break;
			case Keyboard::Up:         virtual_key = VK_UP;         break;
			case Keyboard::Down:       virtual_key = VK_DOWN;       break;
			case Keyboard::Numpad0:    virtual_key = VK_NUMPAD0;    break;
			case Keyboard::Numpad1:    virtual_key = VK_NUMPAD1;    break;
			case Keyboard::Numpad2:    virtual_key = VK_NUMPAD2;    break;
			case Keyboard::Numpad3:    virtual_key = VK_NUMPAD3;    break;
			case Keyboard::Numpad4:    virtual_key = VK_NUMPAD4;    break;
			case Keyboard::Numpad5:    virtual_key = VK_NUMPAD5;    break;
			case Keyboard::Numpad6:    virtual_key = VK_NUMPAD6;    break;
			case Keyboard::Numpad7:    virtual_key = VK_NUMPAD7;    break;
			case Keyboard::Numpad8:    virtual_key = VK_NUMPAD8;    break;
			case Keyboard::Numpad9:    virtual_key = VK_NUMPAD9;    break;
			case Keyboard::F1:         virtual_key = VK_F1;         break;
			case Keyboard::F2:         virtual_key = VK_F2;         break;
			case Keyboard::F3:         virtual_key = VK_F3;         break;
			case Keyboard::F4:         virtual_key = VK_F4;         break;
			case Keyboard::F5:         virtual_key = VK_F5;         break;
			case Keyboard::F6:         virtual_key = VK_F6;         break;
			case Keyboard::F7:         virtual_key = VK_F7;         break;
			case Keyboard::F8:         virtual_key = VK_F8;         break;
			case Keyboard::F9:         virtual_key = VK_F9;         break;
			case Keyboard::F10:        virtual_key = VK_F10;        break;
			case Keyboard::F11:        virtual_key = VK_F11;        break;
			case Keyboard::F12:        virtual_key = VK_F12;        break;
			case Keyboard::F13:        virtual_key = VK_F13;        break;
			case Keyboard::F14:        virtual_key = VK_F14;        break;
			case Keyboard::F15:        virtual_key = VK_F15;        break;
			case Keyboard::Pause:      virtual_key = VK_PAUSE;      break;
			default:                   virtual_key = 0;             break;
		}

		return (GetAsyncKeyState(virtual_key) & 0x8000) != 0;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

namespace jlib
{
	bool Mouse::_isVisible = true;

	bool Mouse::isCursorVisible()
	{
		return _isVisible;
	}

	void Mouse::hide()
	{
		ShowCursor(FALSE);
		_isVisible = false;
	}

	void Mouse::show()
	{
		ShowCursor(TRUE);
		_isVisible = true;
	}

	bool Mouse::isButtonPressed(Button button)
	{
		i32 virtual_key = 0;

		switch (button)
		{
			case Mouse::Left:     virtual_key = GetSystemMetrics(SM_SWAPBUTTON) ? VK_RBUTTON : VK_LBUTTON; break;
			case Mouse::Right:    virtual_key = GetSystemMetrics(SM_SWAPBUTTON) ? VK_LBUTTON : VK_RBUTTON; break;
			case Mouse::Middle:   virtual_key = VK_MBUTTON;  break;
			default:              virtual_key = 0;           break;
		}

		return (GetAsyncKeyState(virtual_key) & 0x8000) != 0;
	}

	Vector2i Mouse::getPosition()
	{
		POINT pos;
		GetCursorPos(&pos);
		return Vector2i(pos.x, pos.y);
	}

	void Mouse::setPosition(const Vector2i& pos)
	{
		SetCursorPos(pos.x, pos.y);
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

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
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

namespace jlib
{
	Gamepad::Gamepad()
	{
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
		DWORD result = XInputGetState(_port + 1, &_state);

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
		XInputGetState(_port + 1, &_state);

		// Update the left and right joysticks.
		leftStick.position.x = static_cast<float>(_state.Gamepad.sThumbLX) / 32768.0f + 0.0000155f;
		leftStick.position.y = static_cast<float>(_state.Gamepad.sThumbLY) / 32768.0f + 0.0000155f;
		rightStick.position.x = static_cast<float>(_state.Gamepad.sThumbRX) / 32768.0f + 0.0000155f;
		rightStick.position.y = static_cast<float>(_state.Gamepad.sThumbRY) / 32768.0f + 0.0000155f;

		// Update the left and right triggers.
		leftTrigger = _state.Gamepad.bLeftTrigger / 255.0f;
		rightTrigger = _state.Gamepad.bRightTrigger / 255.0f;
	}

	bool Gamepad::isButtonPressed(Button button) const
	{
		return _state.Gamepad.wButtons & button;
	}
}

bool operator == (const Gamepad& A, const Gamepad& B)
{
	return A.getPort() == B.getPort();
}

bool operator != (const Gamepad& A, const Gamepad& B)
{
	return A.getPort() != B.getPort();
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

namespace jlib
{
	string Clipboard::getString()
	{
		string text;

		if (!IsClipboardFormatAvailable(CF_UNICODETEXT))
		{
			cout << "Failed to get the clipboard data in Unicode format." << endl;
			return text;
		}

		if (!OpenClipboard(nullptr))
		{
			cout << "Failed to open the Win32 clipboard." << endl;
			return text;
		}

		HANDLE clipboard_handle = GetClipboardData(CF_TEXT);

		if (!clipboard_handle)
		{
			cout << "Failed to get Win32 handle for clipboard content." << endl;
			CloseClipboard();
			return text;
		}

		text = (static_cast<char*>(GlobalLock(clipboard_handle)));
		GlobalUnlock(clipboard_handle);

		CloseClipboard();
		return text;
	}

	wstring Clipboard::getWideString()
	{
		wstring text;

		if (!IsClipboardFormatAvailable(CF_UNICODETEXT))
		{
			cout << "Failed to get the clipboard data in Unicode format." << endl;
			return text;
		}

		if (!OpenClipboard(nullptr))
		{
			cout << "Failed to open the Win32 clipboard." << endl;
			return text;
		}

		HANDLE clipboard_handle = GetClipboardData(CF_UNICODETEXT);

		if (!clipboard_handle)
		{
			cout << "Failed to get Win32 handle for clipboard content." << endl;
			CloseClipboard();
			return text;
		}

		text = (static_cast<wchar_t*>(GlobalLock(clipboard_handle)));
		GlobalUnlock(clipboard_handle);

		CloseClipboard();
		return text;
	}

	void Clipboard::setString(const string& text)
	{
		if (!OpenClipboard(NULL))
		{
			cout << "Failed to open the Win32 clipboard." << endl;
			return;
		}

		if (!EmptyClipboard())
		{
			cout << "Failed to empty the Win32 clipboard." << endl;
			return;
		}

		// Create a Win32-compatible string
		size_t string_size = (text.size() + 1) * sizeof(char);
		HANDLE string_handle = GlobalAlloc(GMEM_MOVEABLE, string_size);

		if (string_handle)
		{
			memcpy(GlobalLock(string_handle), text.data(), string_size);
			GlobalUnlock(string_handle);
			SetClipboardData(CF_UNICODETEXT, string_handle);
		}

		CloseClipboard();
	}

	void Clipboard::setWideString(const wstring& text)
	{
		if (!OpenClipboard(NULL))
		{
			cout << "Failed to open the Win32 clipboard." << endl;
			return;
		}

		if (!EmptyClipboard())
		{
			cout << "Failed to empty the Win32 clipboard." << endl;
			return;
		}

		// Create a Win32-compatible string
		size_t string_size = (text.size() + 1) * sizeof(wchar_t);
		HANDLE string_handle = GlobalAlloc(GMEM_MOVEABLE, string_size);

		if (string_handle)
		{
			memcpy(GlobalLock(string_handle), text.data(), string_size);
			GlobalUnlock(string_handle);
			SetClipboardData(CF_UNICODETEXT, string_handle);
		}

		CloseClipboard();
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

namespace jlib
{
	const Duration jlib::TimeZero = Duration(0.f);

	Clock::Clock()
	{
		_start = now();
	}

	TimePoint Clock::startTime() const
	{
		return _start;
	}

	TimePoint Clock::now() const
	{
		return system_clock::now();
	}

	Duration Clock::restart()
	{
		TimePoint time(now());
		Duration time_elapsed(time - _start);
		_start = time;
		return time_elapsed;
	}

	Duration Clock::timeElapsed() const
	{
		return now() - _start;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

namespace jlib
{
	Color::Color()
	{
		r = 0;
		g = 0;
		b = 0;
		a = 0;
	}

	Color::Color(u8 R, u8 G, u8 B, u8 A)
	{
		r = R;
		g = G;
		b = B;
		a = A;
	}

	Color::Color(u32 color)
	{
		r = (color & 0xff000000) >> 24;
		g = (color & 0x00ff0000) >> 16;
		b = (color & 0x0000ff00) >> 8;
		a = (color & 0x000000ff) >> 0;
	}

	Color::Color(const array<u8, 4>& arr)
	{
		r = arr[0];
		g = arr[1];
		b = arr[2];
		a = arr[3];
	}

	Color::Color(initializer_list<u8> list)
	{
		r = *(list.begin() + 0);
		g = *(list.begin() + 1);
		b = *(list.begin() + 2);
		a = *(list.begin() + 3);
	}

	Color& Color::operator = (u32 color)
	{
		r = (color & 0xff000000) >> 24;
		g = (color & 0x00ff0000) >> 16;
		b = (color & 0x0000ff00) >> 8;
		a = (color & 0x000000ff) >> 0;

		return *this;
	}

	Color& Color::operator = (const array<u8, 4>& arr)
	{
		r = arr[0];
		g = arr[1];
		b = arr[2];
		a = arr[3];

		return *this;
	}

	Color& Color::operator = (initializer_list<u8> list)
	{
		r = *(list.begin() + 0);
		g = *(list.begin() + 1);
		b = *(list.begin() + 2);
		a = *(list.begin() + 3);

		return *this;
	}

	void Color::set(u8 R, u8 G, u8 B, u8 A)
	{
		r = R;
		g = G;
		b = B;
		a = A;
	}

	void Color::set(u32 color)
	{
		r = (color & 0xff000000) >> 24;
		g = (color & 0x00ff0000) >> 16;
		b = (color & 0x0000ff00) >> 8;
		a = (color & 0x000000ff) >> 0;
	}

	void Color::set(const array<u8, 4>& arr)
	{
		r = arr[0];
		g = arr[1];
		b = arr[2];
		a = arr[3];
	}

	u32 Color::toInt() const
	{
		return (r << 24) | (g << 16) | (b << 8) | a;
	}

	array<u8, 4> Color::toArray() const
	{
		return array<u8, 4>{ r, g, b, a };
	}

	string Color::toString() const
	{
		string str;
		str.reserve(8);
		str += to_hex_str(r);
		str += to_hex_str(g);
		str += to_hex_str(b);
		str += to_hex_str(a);
		return str;
	}

	array<u8, 4> to_bytes(u32 i)
	{
		array<u8, 4> bytes;

		bytes[0] = (i & 0xff000000) >> 24;
		bytes[1] = (i & 0x00ff0000) >> 16;
		bytes[2] = (i & 0x0000ff00) >> 8;
		bytes[3] = (i & 0x000000ff) >> 0;

		return bytes;
	}

	string to_hex_str(u8 cbyte)
	{
		string hexstr("00");

		for (u8 i = 0; i < 2; ++i)
		{
			switch (cbyte % 16)
			{
				case 10: hexstr[1 - i] = 'a';               break;
				case 11: hexstr[1 - i] = 'b';               break;
				case 12: hexstr[1 - i] = 'c';               break;
				case 13: hexstr[1 - i] = 'd';               break;
				case 14: hexstr[1 - i] = 'e';               break;
				case 15: hexstr[1 - i] = 'f';               break;
				default: hexstr[1 - i] = (cbyte % 16) + 48; break;
			}

			cbyte /= 16;
		}

		return hexstr;
	}

	void copy_color_data(const Color* src, u8* dst, size_t bytes)
	{
		const u8* ptr = reinterpret_cast<const u8*>(src);
		memcpy(dst, ptr, bytes);
	}
}

bool operator == (const Color& A, const Color& B)
{
	return (A.r == B.r) && (A.g == B.g) && (A.b == B.b) && (A.a == B.a);
}

bool operator != (const Color& A, const Color& B)
{
	return (A.r != B.r) && (A.g != B.g) && (A.b != B.b) && (A.a != B.a);
}

Color operator + (const Color& A, const Color& B)
{
	int r = clamp_of(int(A.r) + int(B.r), 0, 255);
	int g = clamp_of(int(A.g) + int(B.g), 0, 255);
	int b = clamp_of(int(A.b) + int(B.b), 0, 255);
	int a = clamp_of(int(A.a) + int(B.a), 0, 255);

	return Color(r, g, b, a);
}

Color operator - (const Color& A, const Color& B)
{
	int r = clamp_of(int(A.r) - int(B.r), 0, 255);
	int g = clamp_of(int(A.g) - int(B.g), 0, 255);
	int b = clamp_of(int(A.b) - int(B.b), 0, 255);
	int a = clamp_of(int(A.a) - int(B.a), 0, 255);

	return Color(r, g, b, a);
}

Color& operator += (Color& A, const Color& B)
{
	A.r = u8(clamp_of(int(A.r) + int(B.r), 0, 255));
	A.g = u8(clamp_of(int(A.g) + int(B.g), 0, 255));
	A.b = u8(clamp_of(int(A.b) + int(B.b), 0, 255));
	A.a = u8(clamp_of(int(A.a) + int(B.a), 0, 255));

	return A;
}

Color& operator -= (Color& A, const Color& B)
{
	A.r = u8(clamp_of(int(A.r) - int(B.r), 0, 255));
	A.g = u8(clamp_of(int(A.g) - int(B.g), 0, 255));
	A.b = u8(clamp_of(int(A.b) - int(B.b), 0, 255));
	A.a = u8(clamp_of(int(A.a) - int(B.a), 0, 255));

	return A;
}

Color operator * (const Color& A, float f)
{
	float r = clamp_of(A.r * f, 0.0f, 255.0f);
	float g = clamp_of(A.g * f, 0.0f, 255.0f);
	float b = clamp_of(A.b * f, 0.0f, 255.0f);
	float a = clamp_of(A.a * f, 0.0f, 255.0f);

	return Color(r, g, b, a);
}

Color operator / (const Color& A, float f)
{
	float r = clamp_of(A.r / f, 0.0f, 255.0f);
	float g = clamp_of(A.g / f, 0.0f, 255.0f);
	float b = clamp_of(A.b / f, 0.0f, 255.0f);
	float a = clamp_of(A.a / f, 0.0f, 255.0f);

	return Color(r, g, b, a);
}

Color& operator *= (Color& A, float f)
{
	A.r = u8(clamp_of(A.r * f, 0.0f, 255.0f));
	A.g = u8(clamp_of(A.g * f, 0.0f, 255.0f));
	A.b = u8(clamp_of(A.b * f, 0.0f, 255.0f));
	A.a = u8(clamp_of(A.a * f, 0.0f, 255.0f));

	return A;
}

Color& operator /= (Color& A, float f)
{
	A.r = u8(clamp_of(A.r / f, 0.0f, 255.0f));
	A.g = u8(clamp_of(A.g / f, 0.0f, 255.0f));
	A.b = u8(clamp_of(A.b / f, 0.0f, 255.0f));
	A.a = u8(clamp_of(A.a / f, 0.0f, 255.0f));

	return A;
}

ostream& operator << (ostream& os, const Color& A)
{
	os << A.toString();
	return os;
}