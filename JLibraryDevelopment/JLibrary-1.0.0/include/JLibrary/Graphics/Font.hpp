// JLibraryDevelopment
// Font.hpp
// Created on 2021-07-06 by Justyn Durnford
// Last modified on 2021-07-13 by Justyn Durnford
// Header file for the Font class.

#pragma once

#include <JLibrary/Graphics/Glyph.hpp>
#include <JLibrary/Graphics/Texture.hpp>
#include <JLibrary/Math/Rectangle.hpp>
#include <JLibrary/Math/Vector2.hpp>
#include <map>
#include <string>
#include <vector>

namespace jlib
{
	class InputStream;

	// Class for loading and manipulating character fonts.
	class Font
	{
		public:

		// Holds various information about a font.
		struct Info
		{
			std::string family;
		};

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

		private:

		// Shorthand for std::map<u64, Glyph>
		// Table mapping a codepoint to its glyph.
		typedef std::map<u64, Glyph> GlyphTable;

		// Structure defining a row of glyphs.
		struct Row
		{
			Row(u32 rowTop, u32 rowHeight) : 
				width(0), top(rowTop), height(rowHeight) {}

			u32 width;
			u32 top;
			u32 height;
		};

		// Structure defining a page of glyphs.
		struct Page
		{
			Page();

			GlyphTable       glyphs;  //!< Table mapping code points to their corresponding glyph
			Texture          texture; //!< Texture containing the pixels of the glyphs
			u32              nextRow; //!< Y position of the next new row in the texture
			std::vector<Row> rows;    //!< List containing the position of all the existing rows
		};

		// Shorthand for std::map<unsigned int, Page>
		// Table mapping a character size to its page (texture).
		typedef std::map<u32, Page> PageTable;

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

		void*                      library_;    
		void*                      face_;
		void*                      streamRec_;
		void*                      stroker_;
		int*                       refCount_;
		bool                       isSmooth_;
		Info                       info_;
		mutable PageTable          pages_;
		mutable std::vector<u8>    pixelBuffer_;

		// Loads a new glyph and store it in the cache.
		Glyph loadGlyph(u32 codePoint, u32 characterSize, bool bold, float outlineThickness) const;

		// Finds a suitable rectangle within the texture for a glyph.
		IntRect findGlyphRect(Page& page, u32 width, u32 height) const;

		// Makes sure that the given size is the current one.
		bool setCurrentSize(u32 characterSize) const;

		// Frees all the internal resources.
		void cleanup();

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

		public:

        // Default constructor.
        Font();

        // Copy constructor.
        Font(const Font& other);

        // Copy assignment operator.
        Font& operator = (const Font& other);

        // Destructor.
        ~Font();

        // Loads the font from a file.
        // The supported font formats are: TrueType, Type 1, CFF,
        // OpenType, SFNT, X11 PCF, Windows FNT, BDF, PFR and Type 42.
        // Note that this function knows nothing about the standard
        // fonts installed on the user's system, thus you can't
        // load them directly.
        // The JLibrary cannot preload all the font data in this
        // function, so the file has to remain accessible until
        // the jlib::Font object loads a new font or is destroyed.
        // Returns true if successful.
        bool loadFromFile(const std::string& filename);

        // Loads the font from a file in memory.
        // The supported font formats are: TrueType, Type 1, CFF,
        // OpenType, SFNT, X11 PCF, Windows FNT, BDF, PFR and Type 42.
        // The JLibrary cannot preload all the font data in this
        // function, so the file has to remain accessible until
        // the jlib::Font object loads a new font or is destroyed.
        // Returns true if successful.
        bool loadFromMemory(const void* data, std::size_t sizeInBytes);

        // Loads the font from a custom stream.
        // The supported font formats are: TrueType, Type 1, CFF,
        // OpenType, SFNT, X11 PCF, Windows FNT, BDF, PFR and Type 42.
        // The JLibrary cannot preload all the font data in this
        // function, so the file has to remain accessible until
        // the jlib::Font object loads a new font or is destroyed.
        // Returns true if successful.
        bool loadFromStream(InputStream& stream);

        // Gets the font information.
        const Info& getInfo() const;

        // Retrieves a glyph of the font.
        // If the font is a bitmap font, not all character sizes
        // might be available. If the glyph is not available at the
        // requested size, an empty glyph is returned.
        // You may want to use hasGlyph to determine if the
        // glyph exists before requesting it. If the glyph does not
        // exist, a font specific default is returned.
        // Be aware that using a negative value for the outline
        // thickness will cause distorted rendering.
        const Glyph& getGlyph(u32 codePoint, u32 characterSize, 
                              bool bold, float outlineThickness = 0) const;

        // Determines if this font has a glyph representing the requested code point.
        // Most fonts only include a very limited selection of glyphs from
        // specific Unicode subsets, like Latin, Cyrillic, or Asian characters.
        // While code points without representation will return a font specific
        // default character, it might be useful to verify whether specific
        // code points are included to determine whether a font is suited
        // to display text in a specific language.
        bool hasGlyph(u32 codePoint) const;

        // Gets the kerning offset of two glyphs.
        // The kerning is an extra offset (negative) to apply between two
        // glyphs when rendering them, to make the pair look more "natural".
        // For example, the pair "AV" have a special kerning to make them
        // closer than other characters. Most of the glyphs pairs have a
        // kerning offset of zero, though.
        float getKerning(u32 first, u32 second, u32 characterSize, bool bold = false) const;

        // Gets the line spacing.
        // Line spacing is the vertical offset to apply between two
        // consecutive lines of text.
        float getLineSpacing(u32 characterSize) const;

        // Gets the position of the underline.
        // Underline position is the vertical offset to apply between the
        // baseline and the underline.
        float getUnderlinePosition(u32 characterSize) const;

        // Gets the thickness of the underline
        // Underline thickness is the vertical size of the underline.
        float getUnderlineThickness(u32 characterSize) const;

        // Retrieves the texture containing the loaded glyphs of a certain size.
        // The contents of the returned texture changes as more glyphs
        // are requested, thus it is not very relevant. It is mainly
        // used internally by jlib::Text.
        const Texture& getTexture(u32 characterSize) const;

        // Enables or disable the smooth filter.
        // When the filter is activated, the font appears smoother
        // so that pixels are less noticeable. However if you want
        // the font to look exactly the same as its source file,
        // you should disable it.
        // The smooth filter is enabled by default.
        void setSmooth(bool smooth);

        // Returns true if the smooth filter is enabled.
        bool isSmooth() const;
	};
}