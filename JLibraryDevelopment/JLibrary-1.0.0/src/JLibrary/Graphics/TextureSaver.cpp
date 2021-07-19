// JLibraryDevelopment
// TextureSaver.cpp
// Created on 2021-07-17 by Justyn Durnford
// Last modified on 2021-07-17 by Justyn Durnford
// Source file for the TextureSaver class.

#include <JLibrary/Graphics/TextureSaver.hpp>
using namespace jlib;

TextureSaver::TextureSaver()
{
    glCheck(glGetIntegerv(GL_TEXTURE_BINDING_2D, &textureBinding_));
}

TextureSaver::~TextureSaver() noexcept
{
    glCheck(glBindTexture(GL_TEXTURE_2D, textureBinding_));
}