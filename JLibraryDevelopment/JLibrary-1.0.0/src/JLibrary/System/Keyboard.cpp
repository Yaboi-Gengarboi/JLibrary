// JLibraryDevelopment
// Keyboard.cpp
// Created on 2021-05-24 by Justyn Durnford
// Last modified on 2021-06-13 by Justyn Durnford
// Source file for the Keyboard class.

#include <JLibrary/System/Keyboard.hpp>
#include <Windows.h>
using namespace std;
using namespace jlib;

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