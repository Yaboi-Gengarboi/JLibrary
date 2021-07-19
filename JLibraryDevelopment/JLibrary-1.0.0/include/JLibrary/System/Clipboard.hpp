// JLibraryDevelopment
// Clipboard.hpp
// Created on 2021-07-07 by Justyn Durnford
// Last modified on 2021-07-18 by Justyn Durnford
// Header file for the Clipboard class.

#pragma once

#include <JLibrary/Utility/StringConvert.hpp>

namespace jlib
{
	// Gives access to the system clipboard.
	class Clipboard
	{
		public:

        // Gets the content of the clipboard as string data.
        // This function returns the content of the clipboard
        // as a string. If the clipboard does not contain string
        // it returns an empty std::wstring object.
        static std::wstring getString();

        // Sets the content of the clipboard as string data.
        // This function sets the content of the clipboard as a string.
        static void setString(const std::wstring& text);
	};
}