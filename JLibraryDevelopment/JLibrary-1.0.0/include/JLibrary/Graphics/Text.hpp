////////////////////////////////////////////////////////////
//
// THIS IS A MODIFIED FILE FROM SFML 2.5.1
// 
// SFML - Simple and Fast Multimedia Library
// Copyright (C) 2007-2021 Laurent Gomila (laurent@sfml-dev.org)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
////////////////////////////////////////////////////////////
// 
// JLibraryDevelopment
// Text.hpp
// Created on 2021-07-06 by Justyn Durnford
// Last modified on 2021-07-06 by Justyn Durnford
// Header file for the Text class.

#pragma once

#include <JLibrary/Graphics/Drawable.hpp>
#include <JLibrary/Graphics/Font.hpp>
#include <JLibrary/Graphics/Transformable.hpp>
#include <JLibrary/Graphics/VertexArray.hpp>
#include <JLibrary/Math/Rectangle.hpp>
#include <JLibrary/System/StringConvert.hpp>

namespace jlib
{
	// Graphical text that can be drawn to a render target.
	class Text : public Drawable, public Transformable
	{
		public:

        // Enumeration of the string drawing styles.
        enum Style
        {
            Regular                = 0,
            Bold                   = 1,
            Italic                 = 2,
            Underlined             = 4,
            StrikeThrough          = 8
        };

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

        private:

        std::u32string      str_;                // String to display.
        const Font*         font_;               // Font used to display the string.
        u32                 characterSize_;      // Base size of characters, in pixels.
        float               letterSpacingFactor_;// Spacing factor between letters.
        float               lineSpacingFactor_;  // Spacing factor between lines.
        u32                 style_;              // Text style (see Style enum).
        Color               fillColor_;          // Text fill color.
        Color               outlineColor_;       // Text outline color.
        float               outlineThickness_;   // Thickness of the text's outline.
        mutable VertexArray vertices_;           // Vertex array containing the fill geometry.
        mutable VertexArray outlineVertices_;    // Vertex array containing the outline geometry.
        mutable FloatRect   bounds_;             // Bounding rectangle of the text (in local coordinates).
        mutable bool        geometryNeedUpdate_; // Does the geometry need to be recomputed?
        mutable u64         fontTextureID_;      // The font texture id.

        // Draws the text to a render target.
        virtual void draw(RenderTarget& target, RenderStates states) const;

        // Makes sure the text's geometry is updated.
        // All the attributes related to rendering are cached, such
        // that the geometry is only updated when necessary.
        void ensureGeometryUpdate() const;

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

        public:

        Text();

        // Constructs the text from a std::string, font and size.
        // Note that if the used font is a bitmap font, it is not
        // scalable, thus not all requested sizes will be available
        // to use. This needs to be taken into consideration when
        // setting the character size. If you need to display text
        // of a certain size, make sure the corresponding bitmap
        // font that supports that size is used.
        Text(const std::string& str, const Font& font, u32 characterSize = 30);

        // Constructs the text from a std::wstring, font and size.
        // Note that if the used font is a bitmap font, it is not
        // scalable, thus not all requested sizes will be available
        // to use. This needs to be taken into consideration when
        // setting the character size. If you need to display text
        // of a certain size, make sure the corresponding bitmap
        // font that supports that size is used.
        Text(const std::wstring& str, const Font& font, u32 characterSize = 30);

        // Constructs the text from a std::u32string, font and size.
        // Note that if the used font is a bitmap font, it is not
        // scalable, thus not all requested sizes will be available
        // to use. This needs to be taken into consideration when
        // setting the character size. If you need to display text
        // of a certain size, make sure the corresponding bitmap
        // font that supports that size is used.
        Text(const std::u32string& str, const Font& font, u32 characterSize = 30);

        // Sets the text's string.
        void setString(const std::string& str);

        // Sets the text's string.
        void setString(const std::wstring& str);

        // Sets the text's string.
        void setString(const std::u32string& str);

        // Sets the text's font.
        // The font argument refers to a font that must
        // exist as long as the text uses it. Indeed, the text
        // doesn't store its own copy of the font, but rather keeps
        // a pointer to the one that you passed to this function.
        // If the font is destroyed and the text tries to
        // use it, the behavior is undefined.
        void setFont(const Font& font);

        // Sets the character size.
        // The default size is 30.
        // Note that if the used font is a bitmap font, it is not
        // scalable, thus not all requested sizes will be available
        // to use. This needs to be taken into consideration when
        // setting the character size. If you need to display text
        // of a certain size, make sure the corresponding bitmap
        // font that supports that size is used.
        void setCharacterSize(u32 size);

        // Sets the line spacing factor.
        // The default spacing between lines is defined by the font.
        // This method enables you to set a factor for the spacing
        // between lines. By default the line spacing factor is 1.
        void setLineSpacing(float spacingFactor);

        // Sets the letter spacing factor.
        // The default spacing between letters is defined by the font.
        // This factor doesn't directly apply to the existing
        // spacing between each character, it rather adds a fixed
        // space between them which is calculated from the font
        // metrics and the character size.
        // Note that factors below 1 (including negative numbers) bring
        // characters closer to each other.
        // By default the letter spacing factor is 1.
        void setLetterSpacing(float spacingFactor);

        // Sets the text's style.
        // You can pass a combination of one or more styles, for
        // example jlib::Text::Bold | jlib::Text::Italic.
        // The default style is jlib::Text::Regular.
        void setStyle(u32 style);

        // Sets the fill color of the text.
        /// By default, the text's fill color is opaque white.
        /// Setting the fill color to a transparent color with an outline
        /// will cause the outline to be displayed in the fill area of the text.
        void setFillColor(const Color& color);

        // Sets the outline color of the text.
        // By default, the text's outline color is opaque black.
        void setOutlineColor(const Color& color);

        // Sets the thickness of the text's outline.
        // By default, the outline thickness is 0.
        // Be aware that using a negative value for the outline
        // thickness will cause distorted rendering.
        void setOutlineThickness(float thickness);

        // Gets the text's string.
        const std::u32string& str() const;

        // Gets the text's font.
        // If the text has no font attached, a nullptr is returned.
        // The returned pointer is const, which means that you
        // cannot modify the font when you get it from this function.
        const Font* font() const;

        // Gets the character size in pixels.
        u32 getCharacterSize() const;

        // Gets the size of the letter spacing factor.
        float getLetterSpacing() const;

        // Gets the size of the line spacing factor.
        float getLineSpacing() const;

        // Gets the text's style.
        u32 getStyle() const;

        // Gets the fill color of the text.
        const Color& getFillColor() const;

        // Gets the outline color of the text.
        const Color& getOutlineColor() const;

        // Gets the outline thickness of the text in pixels.
        float getOutlineThickness() const;

        // Returns the position of the character at the given index.
        // This function computes the visual position of a character
        // from its index in the string. The returned position is
        // in global coordinates (translation, rotation, scale and
        // origin are applied).
        // If the index is out of range, the position of the end of
        // the string is returned.
        Vector2f findCharacterPos(std::size_t index) const;

        // Gets the local bounding rectangle of the entity.
        // The returned rectangle is in local coordinates, which means
        // that it ignores the transformations (translation, rotation,
        // scale, ...) that are applied to the entity.
        // In other words, this function returns the bounds of the
        // entity in the entity's coordinate system.
        FloatRect getLocalBounds() const;

        // Gets the global bounding rectangle of the entity.
        // The returned rectangle is in global coordinates, which means
        // that it takes into account the transformations (translation,
        // rotation, scale, ...) that are applied to the entity.
        // In other words, this function returns the bounds of the
        // text in the global 2D world's coordinate system.
        FloatRect getGlobalBounds() const;
	};
}