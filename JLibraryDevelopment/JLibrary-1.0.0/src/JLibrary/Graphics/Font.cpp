// JLibraryDevelopment
// Font.cpp
// Created on 2021-07-09 by Justyn Durnford
// Last modified on 2021-07-16 by Justyn Durnford
// Source file for the Font class.

#pragma comment(lib, "freetype.lib")

#include <ft2build.h>
#include <freetype.h>
#include <ftglyph.h>
#include <ftoutln.h>
#include <ftbitmap.h>
#include <ftstroke.h>

#include <JLibrary/Graphics/Font.hpp>
#include <JLibrary/Graphics/GlContext.hpp>
#include <JLibrary/Utility/InputStream.hpp>
using namespace jlib;

#include <cmath>
using std::floor;

#include <cstdlib>


#include <cstring>
using std::memcpy;
using std::memset;

#include <iostream>
using std::cout;
using std::endl;

// <string>
using std::size_t;
using std::string;

#include <utility>
using std::make_pair;
using std::swap;

// <vector>
using std::vector;

// FreeType callbacks that operate on a jlib::InputStream.
unsigned long read(FT_Stream rec, unsigned long offset, unsigned char* buffer, unsigned long count)
{
    InputStream* stream = static_cast<InputStream*>(rec->descriptor.pointer);
    if (static_cast<u32>(stream->seek(offset)) == offset)
    {
        if (count > 0)
            return static_cast<u32>(stream->read(reinterpret_cast<char*>(buffer), count));
        else
            return 0;
    }
    else
        return count > 0 ? 0 : 1; // Error code is 0 if we're reading, or nonzero if we're seeking.
}

void close(FT_Stream)
{

}

// Helper to intepret memory as a specific type
template <typename T, typename U>
inline T reinterpret(const U& input)
{
    T output;
    memcpy(&output, &input, sizeof(U));
    return output;
}

// Combine outline thickness, boldness and font glyph index into a single 64-bit key.
u64 combine(float outlineThickness, bool bold, u32 index)
{
    return (static_cast<u64>(reinterpret<u32>(outlineThickness)) << 32) | (static_cast<u64>(bold) << 31) | index;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

Font::Page::Page() :
    nextRow(3)
{
    // Make sure that the texture is initialized by default
    Image image;
    image.create(128, 128, Color(255, 255, 255, 0));

    // Reserve a 2x2 white square for texturing underlines
    for (int x = 0; x < 2; ++x)
        for (int y = 0; y < 2; ++y)
            image.setPixel(x, y, Color(255, 255, 255, 255));

    // Create the texture
    texture.loadFromImage(image);
    texture.setSmooth(true);
}

Glyph Font::loadGlyph(u32 codePoint, u32 characterSize, bool bold, float outlineThickness) const
{
    // The glyph to return.
    Glyph glyph;

    // First, transform our ugly void* to a FT_Face.
    FT_Face face = static_cast<FT_Face>(face_);
    if (!face)
        return glyph;

    // Set the character size.
    if (!setCurrentSize(characterSize))
        return glyph;

    // Load the glyph corresponding to the code point.
    FT_Int32 flags = FT_LOAD_TARGET_NORMAL | FT_LOAD_FORCE_AUTOHINT;
    if (outlineThickness != 0)
        flags |= FT_LOAD_NO_BITMAP;
    if (FT_Load_Char(face, codePoint, flags) != 0)
        return glyph;

    // Retrieve the glyph.
    FT_Glyph glyphDesc;
    if (FT_Get_Glyph(face->glyph, &glyphDesc) != 0)
        return glyph;

    // Apply bold and outline (there is no fallback for outline) if necessary,
    // first technique using outline (highest quality).
    FT_Pos weight = 1 << 6;
    bool outline = (glyphDesc->format == FT_GLYPH_FORMAT_OUTLINE);
    if (outline)
    {
        if (bold)
        {
            FT_OutlineGlyph outlineGlyph = (FT_OutlineGlyph)glyphDesc;
            FT_Outline_Embolden(&outlineGlyph->outline, weight);
        }

        if (outlineThickness != 0)
        {
            FT_Stroker stroker = static_cast<FT_Stroker>(stroker_);

            FT_Stroker_Set(stroker, static_cast<FT_Fixed>(outlineThickness * static_cast<float>(1 << 6)), FT_STROKER_LINECAP_ROUND, FT_STROKER_LINEJOIN_ROUND, 0);
            FT_Glyph_Stroke(&glyphDesc, stroker, true);
        }
    }

    // Convert the glyph to a bitmap (i.e. rasterize it)
    FT_Glyph_To_Bitmap(&glyphDesc, FT_RENDER_MODE_NORMAL, 0, 1);
    FT_Bitmap& bitmap = reinterpret_cast<FT_BitmapGlyph>(glyphDesc)->bitmap;

    // Apply bold if necessary -- fallback technique using bitmap (lower quality)
    if (!outline)
    {
        if (bold)
            FT_Bitmap_Embolden(static_cast<FT_Library>(library_), &bitmap, weight, weight);

        if (outlineThickness != 0)
            cout << "Failed to outline glyph (no fallback available)" << endl;
    }

    // Compute the glyph's advance offset
    glyph.advanceOffset = static_cast<float>(face->glyph->metrics.horiAdvance) / static_cast<float>(1 << 6);
    if (bold)
        glyph.advanceOffset += static_cast<float>(weight) / static_cast<float>(1 << 6);

    glyph.lDelta = face->glyph->lsb_delta;
    glyph.rDelta = face->glyph->rsb_delta;

    int width = bitmap.width;
    int height = bitmap.rows;

    if ((width > 0) && (height > 0))
    {
        // Leave a small padding around characters, so that filtering doesn't
        // pollute them with pixels from neighbors
        const u32 padding = 2;

        width += 2 * padding;
        height += 2 * padding;

        // Get the glyphs page corresponding to the character size
        Page& page = pages_[characterSize];

        // Find a good position for the new glyph into the texture
        glyph.textureRect = findGlyphRect(page, width, height);

        // Make sure the texture data is positioned in the center
        // of the allocated texture rectangle
        glyph.textureRect.vertex.x += padding;
        glyph.textureRect.vertex.y += padding;
        glyph.textureRect.width -= 2 * padding;
        glyph.textureRect.height -= 2 * padding;

        // Compute the glyph's bounding box
        glyph.bounds.vertex.x = static_cast<float>(face->glyph->metrics.horiBearingX) / static_cast<float>(1 << 6);
        glyph.bounds.vertex.y = -static_cast<float>(face->glyph->metrics.horiBearingY) / static_cast<float>(1 << 6);
        glyph.bounds.width = static_cast<float>(face->glyph->metrics.width) / static_cast<float>(1 << 6) + outlineThickness * 2;
        glyph.bounds.height = static_cast<float>(face->glyph->metrics.height) / static_cast<float>(1 << 6) + outlineThickness * 2;

        // Resize the pixel buffer to the new size and fill it with transparent white pixels
        pixelBuffer_.resize(width * height * 4);

        u8* current = &pixelBuffer_[0];
        u8* end = current + width * height * 4;

        while (current != end)
        {
            (*current++) = 255;
            (*current++) = 255;
            (*current++) = 255;
            (*current++) = 0;
        }

        // Extract the glyph's pixels from the bitmap
        const u8* pixels = bitmap.buffer;
        if (bitmap.pixel_mode == FT_PIXEL_MODE_MONO)
        {
            // Pixels are 1 bit monochrome values
            for (u32 y = padding; y < height - padding; ++y)
            {
                for (u32 x = padding; x < width - padding; ++x)
                {
                    // The color channels remain white, just fill the alpha channel
                    size_t index = x + y * width;
                    pixelBuffer_[index * 4 + 3] = ((pixels[(x - padding) / 8]) & (1 << (7 - ((x - padding) % 8)))) ? 255 : 0;
                }
                pixels += bitmap.pitch;
            }
        }
        else
        {
            // Pixels are 8 bits gray levels
            for (unsigned int y = padding; y < height - padding; ++y)
            {
                for (unsigned int x = padding; x < width - padding; ++x)
                {
                    // The color channels remain white, just fill the alpha channel
                    size_t index = x + y * width;
                    pixelBuffer_[index * 4 + 3] = pixels[x - padding];
                }
                pixels += bitmap.pitch;
            }
        }

        // Write the pixels to the texture
        unsigned int x = glyph.textureRect.vertex.x - padding;
        unsigned int y = glyph.textureRect.vertex.y - padding;
        unsigned int w = glyph.textureRect.width + 2 * padding;
        unsigned int h = glyph.textureRect.height + 2 * padding;
        page.texture.update(&pixelBuffer_[0], w, h, x, y);
    }

    // Delete the FT glyph
    FT_Done_Glyph(glyphDesc);

    // Done :)
    return glyph;
}

IntRect Font::findGlyphRect(Page& page, u32 width, u32 height) const
{
    // Find the line that fits well the glyph.
    Row* row = nullptr;
    float bestRatio = 0;
    for (vector<Row>::iterator it = page.rows.begin(); it != page.rows.end() && !row; ++it)
    {
        float ratio = static_cast<float>(height) / it->height;

        // Ignore rows that are either too small or too high.
        if ((ratio < 0.7f) || (ratio > 1.f))
            continue;

        // Check if there's enough horizontal space left in the row.
        if (width > page.texture.width() - it->width)
            continue;

        // Make sure that this new row is the best found so far.
        if (ratio < bestRatio)
            continue;

        // The current row passed all the tests: we can select it.
        row = &*it;
        bestRatio = ratio;
    }

    // If we didn't find a matching row, create a new one (10% taller than the glyph).
    if (!row)
    {
        int rowHeight = height + height / 10;
        while ((page.nextRow + rowHeight >= page.texture.height()) || (width >= page.texture.width()))
        {
            // Not enough space: resize the texture if possible.
            unsigned int textureWidth = page.texture.width();
            unsigned int textureHeight = page.texture.height();
            if ((textureWidth * 2 <= Texture::getMaximumSize()) && (textureHeight * 2 <= Texture::getMaximumSize()))
            {
                // Make the texture 2 times bigger.
                Texture newTexture;
                newTexture.create(textureWidth * 2, textureHeight * 2);
                newTexture.setSmooth(isSmooth_);
                newTexture.update(page.texture);
                page.texture.swapWith(newTexture);
            }
            else
            {
                // Oops, we've reached the maximum texture size...
                cout << "Failed to add a new character to the font: the maximum texture size has been reached" << endl;
                return IntRect(0, 0, 2, 2);
            }
        }

        // We can now create the new row
        page.rows.push_back(Row(page.nextRow, rowHeight));
        page.nextRow += rowHeight;
        row = &page.rows.back();
    }

    // Find the glyph's rectangle on the selected row
    IntRect rect(row->width, row->top, width, height);

    // Update the row informations
    row->width += width;

    return rect;
}

bool Font::setCurrentSize(u32 characterSize) const
{
    // FT_Set_Pixel_Sizes is an expensive function, so we must call it
    // only when necessary to avoid killing performances.

    FT_Face face = static_cast<FT_Face>(face_);
    FT_UShort currentSize = face->size->metrics.x_ppem;

    if (currentSize != characterSize)
    {
        FT_Error result = FT_Set_Pixel_Sizes(face, 0, characterSize);

        if (result == FT_Err_Invalid_Pixel_Size)
        {
            // In the case of bitmap fonts, resizing can
            // fail if the requested size is not available.
            if (!FT_IS_SCALABLE(face))
            {
                cout << "Failed to set bitmap font size to " << characterSize << endl;
                cout << "Available sizes are: ";
                for (int i = 0; i < face->num_fixed_sizes; ++i)
                {
                    const u32 size = (face->available_sizes[i].y_ppem + 32) >> 6;
                    cout << size << " ";
                }
                cout << endl;
            }
            else
            {
                cout << "Failed to set font size to " << characterSize << endl;
            }
        }

        return result == FT_Err_Ok;
    }

    return true;
}

void Font::cleanup()
{
    // Check if we must destroy the FreeType pointers.
    if (refCount_ != nullptr)
    {
        // Decrease the reference counter.
        (*refCount_)--;

        // Free the resources only if we are the last owner.
        if (*refCount_ == 0)
        {
            // Delete the reference counter.
            delete refCount_;

            // Destroy the stroker.
            if (stroker_)
                FT_Stroker_Done(static_cast<FT_Stroker>(stroker_));

            // Destroy the font face.
            if (face_)
                FT_Done_Face(static_cast<FT_Face>(face_));

            // Destroy the stream rec instance, if any (must be done after FT_Done_Face!)
            if (streamRec_)
                delete static_cast<FT_StreamRec*>(streamRec_);

            // Close the library.
            if (library_)
                FT_Done_FreeType(static_cast<FT_Library>(library_));
        }
    }

    // Reset members.
    library_ = nullptr;
    face_ = nullptr;
    stroker_ = nullptr;
    streamRec_ = nullptr;
    refCount_ = nullptr;
    pages_.clear();
    vector<u8>().swap(pixelBuffer_);
}

Font::Font()
{
    library_ = nullptr;
    face_ = nullptr;
    streamRec_ = nullptr;
    stroker_ = nullptr;
    refCount_ = nullptr;
    isSmooth_ = true;
}

Font::Font(const Font& other)
{
    library_ = other.library_;
    face_ = other.face_;
    streamRec_ = other.streamRec_;
    stroker_ = other.stroker_;
    isSmooth_ = other.isSmooth_;
    info_ = other.info_;
    pages_ = other.pages_;
    pixelBuffer_ = other.pixelBuffer_;

    // Note: as FreeType doesn't provide functions for copying/cloning,
    // we must share all the FreeType pointers.
    if (refCount_ != nullptr)
        (*refCount_)++;
}

Font& Font::operator = (const Font& other)
{
    Font temp(other);

    swap(library_,     temp.library_);
    swap(face_,        temp.face_);
    swap(streamRec_,   temp.streamRec_);
    swap(stroker_,     temp.stroker_);
    swap(refCount_,    temp.refCount_);
    swap(isSmooth_,    temp.isSmooth_);
    swap(info_,        temp.info_);
    swap(pages_,       temp.pages_);
    swap(pixelBuffer_, temp.pixelBuffer_);

    return *this;
}

Font::~Font()
{
    cleanup();
}

bool Font::loadFromFile(const string& filename)
{
    // Cleanup the previous resources.
    cleanup();
    refCount_ = new int(1);

    // Initialize FreeType
    // Note: we initialize FreeType for every font instance in order to avoid having a single
    // global manager that would create a lot of issues regarding creation and destruction order.
    FT_Library library;
    if (FT_Init_FreeType(&library) != 0)
    {
        cout << "Failed to load font \"" << filename << "\" (failed to initialize FreeType)" << endl;
        return false;
    }
    library_ = library;

    // Load the new font face from the specified file.
    FT_Face face;
    if (FT_New_Face(static_cast<FT_Library>(library_), filename.c_str(), 0, &face) != 0)
    {
        cout << "Failed to load font \"" << filename << "\" (failed to create the font face)" << endl;
        return false;
    }

    // Load the stroker that will be used to outline the font.
    FT_Stroker stroker;
    if (FT_Stroker_New(static_cast<FT_Library>(library_), &stroker) != 0)
    {
        cout << "Failed to load font \"" << filename << "\" (failed to create the stroker)" << endl;
        FT_Done_Face(face);
        return false;
    }

    // Select the unicode character map.
    if (FT_Select_Charmap(face, FT_ENCODING_UNICODE) != 0)
    {
        cout << "Failed to load font \"" << filename << "\" (failed to set the Unicode character set)" << endl;
        FT_Stroker_Done(stroker);
        FT_Done_Face(face);
        return false;
    }

    // Store the loaded font in our ugly void* :)
    stroker_ = stroker;
    face_ = face;

    // Store the font information.
    info_.family = face->family_name ? face->family_name : string();

    return true;
}

bool Font::loadFromMemory(const void* data, size_t sizeInBytes)
{
    // Cleanup the previous resources.
    cleanup();
    refCount_ = new int(1);

    // Initialize FreeType.
    // Note: we initialize FreeType for every font instance in order to avoid having a single
    // global manager that would create a lot of issues regarding creation and destruction order.
    FT_Library library;
    if (FT_Init_FreeType(&library) != 0)
    {
        cout << "Failed to load font from memory (failed to initialize FreeType)" << endl;
        return false;
    }
    library_ = library;

    // Load the new font face from the specified file.
    FT_Face face;
    if (FT_New_Memory_Face(static_cast<FT_Library>(library_), reinterpret_cast<const FT_Byte*>(data), static_cast<FT_Long>(sizeInBytes), 0, &face) != 0)
    {
        cout << "Failed to load font from memory (failed to create the font face)" << endl;
        return false;
    }

    // Load the stroker that will be used to outline the font.
    FT_Stroker stroker;
    if (FT_Stroker_New(static_cast<FT_Library>(library_), &stroker) != 0)
    {
        cout << "Failed to load font from memory (failed to create the stroker)" << endl;
        FT_Done_Face(face);
        return false;
    }

    // Select the Unicode character map.
    if (FT_Select_Charmap(face, FT_ENCODING_UNICODE) != 0)
    {
        cout << "Failed to load font from memory (failed to set the Unicode character set)" << endl;
        FT_Stroker_Done(stroker);
        FT_Done_Face(face);
        return false;
    }

    // Store the loaded font in our ugly void* :)
    stroker_ = stroker;
    face_ = face;

    // Store the font information.
    info_.family = face->family_name ? face->family_name : string();

    return true;
}

bool Font::loadFromStream(InputStream& stream)
{
    // Cleanup the previous resources.
    cleanup();
    refCount_ = new int(1);

    // Initialize FreeType.
    // Note: we initialize FreeType for every font instance in order to avoid having a single
    // global manager that would create a lot of issues regarding creation and destruction order.
    FT_Library library;
    if (FT_Init_FreeType(&library) != 0)
    {
        cout << "Failed to load font from stream (failed to initialize FreeType)" << endl;
        return false;
    }
    library_ = library;

    // Make sure that the stream's reading position is at the beginning.
    stream.seek(0);

    // Prepare a wrapper for our stream, that we'll pass to FreeType callbacks.
    FT_StreamRec* rec = new FT_StreamRec;
    memset(rec, 0, sizeof(*rec));
    rec->base = nullptr;
    rec->size = static_cast<u32>(stream.size());
    rec->pos = 0;
    rec->descriptor.pointer = &stream;
    rec->read = &read;
    rec->close = &close;

    // Setup the FreeType callbacks that will read our stream.
    FT_Open_Args args;
    args.flags = FT_OPEN_STREAM;
    args.stream = rec;
    args.driver = 0;

    // Load the new font face from the specified stream.
    FT_Face face;
    if (FT_Open_Face(static_cast<FT_Library>(library_), &args, 0, &face) != 0)
    {
        cout << "Failed to load font from stream (failed to create the font face)" << endl;
        delete rec;
        return false;
    }

    // Load the stroker that will be used to outline the font.
    FT_Stroker stroker;
    if (FT_Stroker_New(static_cast<FT_Library>(library_), &stroker) != 0)
    {
        cout << "Failed to load font from stream (failed to create the stroker)" << endl;
        FT_Done_Face(face);
        delete rec;
        return false;
    }

    // Select the Unicode character map.
    if (FT_Select_Charmap(face, FT_ENCODING_UNICODE) != 0)
    {
        cout << "Failed to load font from stream (failed to set the Unicode character set)" << endl;
        FT_Done_Face(face);
        FT_Stroker_Done(stroker);
        delete rec;
        return false;
    }

    // Store the loaded font in our ugly void* :)
    stroker_ = stroker;
    face_ = face;
    streamRec_ = rec;

    // Store the font information.
    info_.family = face->family_name ? face->family_name : std::string();

    return true;
}

const Font::Info& Font::getInfo() const
{
    return info_;
}

const Glyph& Font::getGlyph(u32 codePoint, u32 characterSize, bool bold, float outlineThickness) const
{
    // Get the page corresponding to the character size.
    GlyphTable& glyphs = pages_[characterSize].glyphs;

    // Build the key by combining the glyph index (based on code point), bold flag, and outline thickness.
    u64 key = combine(outlineThickness, bold, FT_Get_Char_Index(static_cast<FT_Face>(face_), codePoint));

    // Search the glyph into the cache.
    GlyphTable::const_iterator it = glyphs.find(key);
    if (it != glyphs.end())
    {
        // Found: just return it.
        return it->second;
    }
    else
    {
        // Not found: we have to load it.
        Glyph glyph = loadGlyph(codePoint, characterSize, bold, outlineThickness);
        return glyphs.insert(make_pair(key, glyph)).first->second;
    }
}

bool Font::hasGlyph(u32 codePoint) const
{
    return FT_Get_Char_Index(static_cast<FT_Face>(face_), codePoint) != 0;
}

float Font::getKerning(u32 first, u32 second, u32 characterSize, bool bold) const
{
    // Special case where first or second is 0 (null character).
    if (first == 0 || second == 0)
        return 0.f;

    FT_Face face = static_cast<FT_Face>(face_);

    if (face && setCurrentSize(characterSize))
    {
        // Convert the characters to indices.
        FT_UInt index1 = FT_Get_Char_Index(face, first);
        FT_UInt index2 = FT_Get_Char_Index(face, second);

        // Retrieve position compensation deltas generated by FT_LOAD_FORCE_AUTOHINT flag.
        float firstRsbDelta = getGlyph(first, characterSize, bold).rDelta;
        float secondLsbDelta = getGlyph(second, characterSize, bold).lDelta;

        // Get the kerning vector if present.
        FT_Vector kerning;
        kerning.x = kerning.y = 0;
        if (FT_HAS_KERNING(face))
            FT_Get_Kerning(face, index1, index2, FT_KERNING_UNFITTED, &kerning);

        // X advance is already in pixels for bitmap fonts.
        if (!FT_IS_SCALABLE(face))
            return static_cast<float>(kerning.x);

        // Combine kerning with compensation deltas and return the X advance.
        // Flooring is required as we use FT_KERNING_UNFITTED flag which is not quantized in 64 based grid.
        return floor((secondLsbDelta - firstRsbDelta + static_cast<float>(kerning.x) + 32) / static_cast<float>(1 << 6));
    }

    return 0.f;
}

float Font::getLineSpacing(u32 characterSize) const
{
    FT_Face face = static_cast<FT_Face>(face_);

    if (face && setCurrentSize(characterSize))
        return static_cast<float>(face->size->metrics.height) / static_cast<float>(1 << 6);

    return 0.f;
}

float Font::getUnderlinePosition(u32 characterSize) const
{
    FT_Face face = static_cast<FT_Face>(face_);

    if (face && setCurrentSize(characterSize))
    {
        // Return a fixed position if font is a bitmap font.
        if (!FT_IS_SCALABLE(face))
            return characterSize / 10.f;

        return -static_cast<float>(FT_MulFix(face->underline_position, face->size->metrics.y_scale)) / static_cast<float>(1 << 6);
    }

    return 0.f;
}

float Font::getUnderlineThickness(u32 characterSize) const
{
    FT_Face face = static_cast<FT_Face>(face_);

    if (face && setCurrentSize(characterSize))
    {
        // Return a fixed thickness if font is a bitmap font.
        if (!FT_IS_SCALABLE(face))
            return characterSize / 14.f;

        return static_cast<float>(FT_MulFix(face->underline_thickness, face->size->metrics.y_scale)) / static_cast<float>(1 << 6);
    }
    
    return 0.f;
}

const Texture& Font::getTexture(u32 characterSize) const
{
    return pages_[characterSize].texture;
}

void Font::setSmooth(bool smooth)
{
    if (smooth != isSmooth_)
    {
        isSmooth_ = smooth;

        for (Font::PageTable::iterator page = pages_.begin(); page != pages_.end(); ++page)
            page->second.texture.setSmooth(isSmooth_);
    }
}

bool Font::isSmooth() const
{
    return isSmooth_;
}