// JLibraryDevelopment
// Text.cpp
// Created on 2021-07-17 by Justyn Durnford
// Last modified on 2021-07-17 by Justyn Durnford
// Source file for the Text class.

#include <JLibrary/Graphics/RenderTarget.hpp>
#include <JLibrary/Graphics/Text.hpp>
using namespace jlib;

#include <cmath>
using std::floor;

#include <string>
using std::size_t;
using std::string;
using std::wstring;

namespace
{
    // Add an underline or strikethrough line to the vertex array.
    void addLine(VertexArray& vertices, float lineLength, float lineTop, const Color& color, 
                 float offset, float thickness, float outlineThickness = 0)
    {
        float top = floor(lineTop + offset - (thickness / 2) + 0.5f);
        float bottom = top + floor(thickness + 0.5f);

        vertices.append(Vertex2(Point2f(-outlineThickness, top - outlineThickness), Point2f(1, 1), color));
        vertices.append(Vertex2(Point2f(lineLength + outlineThickness, top - outlineThickness), Point2f(1, 1), color));
        vertices.append(Vertex2(Point2f(-outlineThickness, bottom + outlineThickness), Point2f(1, 1), color));
        vertices.append(Vertex2(Point2f(-outlineThickness, bottom + outlineThickness), Point2f(1, 1), color));
        vertices.append(Vertex2(Point2f(lineLength + outlineThickness, top - outlineThickness), Point2f(1, 1), color));
        vertices.append(Vertex2(Point2f(lineLength + outlineThickness, bottom + outlineThickness), Point2f(1, 1), color));
    }

    // Add a glyph quad to the vertex array.
    void addGlyphQuad(VertexArray& vertices, Point2f position, const Color& color, const Glyph& glyph, float italicShear, float outlineThickness = 0)
    {
        float padding = 1.0;

        float left = glyph.bounds.vertex.x - padding;
        float top = glyph.bounds.vertex.y - padding;
        float right = glyph.bounds.vertex.x + glyph.bounds.width + padding;
        float bottom = glyph.bounds.vertex.y + glyph.bounds.height + padding;

        float u1 = static_cast<float>(glyph.textureRect.vertex.x) - padding;
        float v1 = static_cast<float>(glyph.textureRect.vertex.y) - padding;
        float u2 = static_cast<float>(glyph.textureRect.vertex.x + glyph.textureRect.width) + padding;
        float v2 = static_cast<float>(glyph.textureRect.vertex.y + glyph.textureRect.height) + padding;

        vertices.append(Vertex2(Point2f(position.x + left - italicShear * top - outlineThickness, position.y + top - outlineThickness), Point2f(u1, v1), color));
        vertices.append(Vertex2(Point2f(position.x + right - italicShear * top - outlineThickness, position.y + top - outlineThickness), Point2f(u2, v1), color));
        vertices.append(Vertex2(Point2f(position.x + left - italicShear * bottom - outlineThickness, position.y + bottom - outlineThickness), Point2f(u1, v2), color));
        vertices.append(Vertex2(Point2f(position.x + left - italicShear * bottom - outlineThickness, position.y + bottom - outlineThickness), Point2f(u1, v2), color));
        vertices.append(Vertex2(Point2f(position.x + right - italicShear * top - outlineThickness, position.y + top - outlineThickness), Point2f(u2, v1), color));
        vertices.append(Vertex2(Point2f(position.x + right - italicShear * bottom - outlineThickness, position.y + bottom - outlineThickness), Point2f(u2, v2), color));
    }
}


namespace jlib
{
    void Text::draw(RenderTarget& target, RenderStates states) const
    {
        if (font_)
        {
            ensureGeometryUpdate();

            states.transform *= transformation();
            states.texture = &font_->getTexture(characterSize_);

            // Only draw the outline if there is something to draw
            if (outlineThickness_ != 0)
                target.draw(outlineVertices_, states);

            target.draw(vertices_, states);
        }
    }


    ////////////////////////////////////////////////////////////
    void Text::ensureGeometryUpdate() const
    {
        if (!font_)
            return;

        // Do nothing, if geometry has not changed and the font texture has not changed
        if (!geometryNeedUpdate_ && font_->getTexture(characterSize_).cacheID_ == fontTextureID_)
            return;

        // Save the current fonts texture id
        fontTextureID_ = font_->getTexture(characterSize_).cacheID_;

        // Mark geometry as updated
        geometryNeedUpdate_ = false;

        // Clear the previous geometry
        vertices_.clear();
        outlineVertices_.clear();
        bounds_ = FloatRect();

        // No text: nothing to draw
        if (str_.empty())
            return;

        // Compute values related to the text style
        bool  isBold = style_ & Bold;
        bool  isUnderlined = style_ & Underlined;
        bool  isStrikeThrough = style_ & StrikeThrough;
        float italicShear = (style_ & Italic) ? 0.209f : 0.f; // 12 degrees in radians
        float underlineOffset = font_->getUnderlinePosition(characterSize_);
        float underlineThickness = font_->getUnderlineThickness(characterSize_);

        // Compute the location of the strike through dynamically
        // We use the center point of the lowercase 'x' glyph as the reference
        // We reuse the underline thickness as the thickness of the strike through as well
        FloatRect xBounds = font_->getGlyph(L'x', characterSize_, isBold).bounds;
        float strikeThroughOffset = xBounds.vertex.y + xBounds.height / 2.f;

        // Precompute the variables needed by the algorithm
        float whitespaceWidth = font_->getGlyph(L' ', characterSize_, isBold).advanceOffset;
        float letterSpacing = (whitespaceWidth / 3.f) * (letterSpacingFactor_ - 1.f);
        whitespaceWidth += letterSpacing;
        float lineSpacing = font_->getLineSpacing(characterSize_) * lineSpacingFactor_;
        float x = 0.f;
        float y = static_cast<float>(characterSize_);

        // Create one quad for each character
        float minX = static_cast<float>(characterSize_);
        float minY = static_cast<float>(characterSize_);
        float maxX = 0.f;
        float maxY = 0.f;
        wchar_t prevChar = 0;
        for (std::size_t i = 0; i < str_.size(); ++i)
        {
           wchar_t curChar = str_[i];

            // Skip the \r char to avoid weird graphical issues
            if (curChar == '\r')
                continue;

            // Apply the kerning offset
            x += font_->getKerning(prevChar, curChar, characterSize_);

            // If we're using the underlined style and there's a new line, draw a line
            if (isUnderlined && (curChar == L'\n' && prevChar != L'\n'))
            {
                addLine(vertices_, x, y, fillColor_, underlineOffset, underlineThickness);

                if (outlineThickness_ != 0)
                    addLine(outlineVertices_, x, y, outlineColor_, underlineOffset, underlineThickness, outlineThickness_);
            }

            // If we're using the strike through style and there's a new line, draw a line across all characters
            if (isStrikeThrough && (curChar == L'\n' && prevChar != L'\n'))
            {
                addLine(vertices_, x, y, fillColor_, strikeThroughOffset, underlineThickness);

                if (outlineThickness_ != 0)
                    addLine(outlineVertices_, x, y, outlineColor_, strikeThroughOffset, underlineThickness, outlineThickness_);
            }

            prevChar = curChar;

            // Handle special characters
            if ((curChar == L' ') || (curChar == L'\n') || (curChar == L'\t'))
            {
                // Update the current bounds (min coordinates)
                minX = std::min(minX, x);
                minY = std::min(minY, y);

                switch (curChar)
                {
                    case L' ':  x += whitespaceWidth;     break;
                    case L'\t': x += whitespaceWidth * 4; break;
                    case L'\n': y += lineSpacing; x = 0;  break;
                }

                // Update the current bounds (max coordinates)
                maxX = std::max(maxX, x);
                maxY = std::max(maxY, y);

                // Next glyph, no need to create a quad for whitespace
                continue;
            }

            // Apply the outline
            if (outlineThickness_ != 0)
            {
                const Glyph& glyph = font_->getGlyph(curChar, characterSize_, isBold, outlineThickness_);

                float left = glyph.bounds.vertex.x;
                float top = glyph.bounds.vertex.y;
                float right = glyph.bounds.vertex.x + glyph.bounds.width;
                float bottom = glyph.bounds.vertex.y + glyph.bounds.height;

                // Add the outline glyph to the vertices
                addGlyphQuad(outlineVertices_, Point2f(x, y), outlineColor_, glyph, italicShear, outlineThickness_);

                // Update the current bounds with the outlined glyph bounds
                minX = std::min(minX, x + left - italicShear * bottom - outlineThickness_);
                maxX = std::max(maxX, x + right - italicShear * top - outlineThickness_);
                minY = std::min(minY, y + top - outlineThickness_);
                maxY = std::max(maxY, y + bottom - outlineThickness_);
            }

            // Extract the current glyph's description
            const Glyph& glyph = font_->getGlyph(curChar, characterSize_, isBold);

            // Add the glyph to the vertices
            addGlyphQuad(vertices_, Point2f(x, y), fillColor_, glyph, italicShear);

            // Update the current bounds with the non outlined glyph bounds
            if (outlineThickness_ == 0)
            {
                float left = glyph.bounds.vertex.x;
                float top = glyph.bounds.vertex.y;
                float right = glyph.bounds.vertex.x + glyph.bounds.width;
                float bottom = glyph.bounds.vertex.y + glyph.bounds.height;

                minX = std::min(minX, x + left - italicShear * bottom);
                maxX = std::max(maxX, x + right - italicShear * top);
                minY = std::min(minY, y + top);
                maxY = std::max(maxY, y + bottom);
            }

            // Advance to the next character
            x += glyph.advanceOffset + letterSpacing;
        }

        // If we're using the underlined style, add the last line
        if (isUnderlined && (x > 0))
        {
            addLine(vertices_, x, y, fillColor_, underlineOffset, underlineThickness);

            if (outlineThickness_ != 0)
                addLine(outlineVertices_, x, y, outlineColor_, underlineOffset, underlineThickness, outlineThickness_);
        }

        // If we're using the strike through style, add the last line across all characters
        if (isStrikeThrough && (x > 0))
        {
            addLine(vertices_, x, y, fillColor_, strikeThroughOffset, underlineThickness);

            if (outlineThickness_ != 0)
                addLine(outlineVertices_, x, y, outlineColor_, strikeThroughOffset, underlineThickness, outlineThickness_);
        }

        // Update the bounding rectangle
        bounds_.vertex.x = minX;
        bounds_.vertex.y = minY;
        bounds_.width = maxX - minX;
        bounds_.height = maxY - minY;
    }


    Text::Text() : fillColor_(255, 255, 255), outlineColor_(0, 0, 0), outlineThickness_(0),
                   vertices_(Triangles), outlineVertices_(Triangles)
    {
        font_ = nullptr;
        characterSize_ = 30;
        letterSpacingFactor_ = 1.f;
        lineSpacingFactor_ = 1.f;
        style_ = Regular;
        outlineThickness_ = 0;
        geometryNeedUpdate_ = false;
        fontTextureID_ = 0;
    }

    Text::Text(const string& string, const Font& font, u32 characterSize) : fillColor_(255, 255, 255),
               outlineColor_(0, 0, 0), vertices_(Triangles), outlineVertices_(Triangles)
    {
        str_ = str_to_wstr(string);
        font_ = &font;
        characterSize_ = characterSize;
        letterSpacingFactor_ = 1.f;
        lineSpacingFactor_ = 1.f;
        style_ = Regular;
        outlineThickness_ = 0;
        geometryNeedUpdate_ = true;
        fontTextureID_ = 0;
    }

    Text::Text(const wstring& wstring, const Font& font, u32 characterSize) : fillColor_(255, 255, 255),
               outlineColor_(0, 0, 0), vertices_(Triangles), outlineVertices_(Triangles)
    {
        str_ = wstring;
        font_ = &font;
        characterSize_ = characterSize;
        letterSpacingFactor_ = 1.f;
        lineSpacingFactor_ = 1.f;
        style_ = Regular;
        outlineThickness_ = 0;
        geometryNeedUpdate_ = true;
        fontTextureID_ = 0;
    }

    const wstring& Text::getString() const
    {
        return str_;
    }

    void Text::setString(const string& str)
    {
        str_ = str_to_wstr(str);
        geometryNeedUpdate_ = true;
    }

    void Text::setString(const wstring& wstring)
    {
        str_ = wstring;
        geometryNeedUpdate_ = true;
    }

    const Font* Text::getFont() const
    {
        return font_;
    }

    void Text::setFont(const Font& font)
    {
        if (font_ != &font)
        {
            font_ = &font;
            geometryNeedUpdate_ = true;
        }
    }

    u32 Text::getCharacterSize() const
    {
        return characterSize_;
    }

    void Text::setCharacterSize(u32 size)
    {
        if (characterSize_ != size)
        {
            characterSize_ = size;
            geometryNeedUpdate_ = true;
        }
    }

    float Text::getLetterSpacing() const
    {
        return letterSpacingFactor_;
    }

    void Text::setLetterSpacing(float spacingFactor)
    {
        if (letterSpacingFactor_ != spacingFactor)
        {
            letterSpacingFactor_ = spacingFactor;
            geometryNeedUpdate_ = true;
        }
    }

    float Text::getLineSpacing() const
    {
        return lineSpacingFactor_;
    }

    void Text::setLineSpacing(float spacingFactor)
    {
        if (lineSpacingFactor_ != spacingFactor)
        {
            lineSpacingFactor_ = spacingFactor;
            geometryNeedUpdate_ = true;
        }
    }

    u32 Text::getStyle() const
    {
        return style_;
    }

    void Text::setStyle(u32 style)
    {
        if (style_ != style)
        {
            style_ = style;
            geometryNeedUpdate_ = true;
        }
    }

    const Color& Text::getFillColor() const
    {
        return fillColor_;
    }

    void Text::setFillColor(const Color& color)
    {
        if (color != fillColor_)
        {
            fillColor_ = color;

            // Change vertex colors directly, no need to update whole geometry
            // (if geometry is updated anyway, we can skip this step)
            if (!geometryNeedUpdate_)
            {
                for (size_t i = 0; i < vertices_.getVertexCount(); ++i)
                    vertices_[i].color = fillColor_;
            }
        }
    }

    const Color& Text::getOutlineColor() const
    {
        return outlineColor_;
    }

    void Text::setOutlineColor(const Color& color)
    {
        if (color != outlineColor_)
        {
            outlineColor_ = color;

            // Change vertex colors directly, no need to update whole geometry
            // (if geometry is updated anyway, we can skip this step)
            if (!geometryNeedUpdate_)
            {
                for (size_t i = 0; i < outlineVertices_.getVertexCount(); ++i)
                    outlineVertices_[i].color = outlineColor_;
            }
        }
    }

    float Text::getOutlineThickness() const
    {
        return outlineThickness_;
    }

    void Text::setOutlineThickness(float thickness)
    {
        if (thickness != outlineThickness_)
        {
            outlineThickness_ = thickness;
            geometryNeedUpdate_ = true;
        }
    }

    Point2f Text::findCharacterPos(size_t index) const
    {
        // Make sure that we have a valid font
        if (!font_)
            return Point2f();

        // Adjust the index if it's out of range
        if (index > str_.size())
            index = str_.size();

        // Precompute the variables needed by the algorithm
        bool  isBold = style_ & Bold;
        float whitespaceWidth = font_->getGlyph(L' ', characterSize_, isBold).advanceOffset;
        float letterSpacing = (whitespaceWidth / 3.f) * (letterSpacingFactor_ - 1.f);
        whitespaceWidth += letterSpacing;
        float lineSpacing = font_->getLineSpacing(characterSize_) * lineSpacingFactor_;

        // Compute the position
        Point2f position;
        wchar_t prevChar = 0;
        for (size_t i = 0; i < index; ++i)
        {
            wchar_t curChar = str_[i];

            // Apply the kerning offset
            position.x += font_->getKerning(prevChar, curChar, characterSize_);
            prevChar = curChar;

            // Handle special characters
            switch (curChar)
            {
                case ' ':  position.x += whitespaceWidth;             continue;
                case '\t': position.x += whitespaceWidth * 4;         continue;
                case '\n': position.y += lineSpacing; position.x = 0; continue;
            }

            // For regular characters, add the advanceOffset offset of the glyph
            position.x += font_->getGlyph(curChar, characterSize_, isBold).advanceOffset + letterSpacing;
        }

        // Transform the position to global coordinates
        position = transformation().transformPoint(position);

        return position;
    }

    FloatRect Text::getLocalBounds() const
    {
        ensureGeometryUpdate();
        return bounds_;
    }

    FloatRect Text::getGlobalBounds() const
    {
        return transformation().transformRectangle(getLocalBounds());
    }
}