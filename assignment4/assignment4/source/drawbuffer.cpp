//
// drawbuffer.cpp --- Drawing buffer class implementation.
//
// Copyright (c) 2014 Paul Ward <asmodai@gmail.com>
//
// Time-stamp: <Wednesday Sep 24, 2014 19:35:14 asmodai>
// Revision:   10
//
// Author:     Paul Ward <asmodai@gmail.com>
// Maintainer: Paul Ward <asmodai@gmail.com>
// Created:    13 Apr 2014 13:30:29
// Keywords:   
// URL:        not distributed yet
//
// {{{ License:
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 3
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, see <http://www.gnu.org/licenses/>.
//
// }}}
// {{{ Commentary:
//
// }}}

/**
 * @file drawbuffer.cpp
 * @author Paul Ward
 * @brief Drawing buffer class implementation.
 */
 
#include "drawbuffer.hpp"
#include "screen.hpp"

using namespace ovision;

/**
 * @brief Glyph type.
 */
typedef struct {
  char_t glyph;                         //!< Glyph character.
} glyphs;

/**
 * @brief DOS (or Alternate Character Set) graphics drawing glyphs.
 */
glyphs dos_glyphs[] = {
#if defined(OVISION_UNICODE)
  0x2502,                               // Horizontal line
  0x2510,                               // Top right corner
  0x2514,                               // Bottom left corner
  0x2500,                               // Vertical line
  0x2518,                               // Bottom right corner
  0x250C,                               // Top left corner
  0x2524,                               // Left long horz T
  0x251c,                               // Right long horz T
#else
  179,                                  // Horizontal line
  191,                                  // Top right corner
  192,                                  // Bottom left corner
  196,                                  // Vertical line
  217,                                  // Bottom right corner
  218,                                  // Top left corner
  180,                                  // Left long horz T
  195                                   // Right long horz T
#endif
};

/**
 * @def HORIZONTAL
 * @brief Horizontal line glyph.
 *
 * @def TOP_RIGHT
 * @brief Top-right corner glyph.
 *
 * @def BOTTOM_LEFT
 * @brief Bottom-left corner glyph.
 *
 * @def VERTICAL
 * @brief Vertical line glyph.
 *
 * @def BOTTOM_RIGHT
 * @brief Bottom-right corner glyph.
 *
 * @def TOP_LEFT
 * @brief Top-left corner glyph.
 *
 * @def LEFT_LONG_HORZ_T
 * @brief Left horizontal T junction.
 *
 * @def RIGHT_LONG_HORZ_T
 * @brief Right horizontal T junction.
 */
#define HORIZONTAL        0
#define TOP_RIGHT         1
#define BOTTOM_LEFT       2
#define VERTICAL          3
#define BOTTOM_RIGHT      4
#define TOP_LEFT          5
#define LEFT_LONG_HORZ_T  6
#define RIGHT_LONG_HORZ_T 7

/**
 * @brief Global draw buffer object.
 */
draw_buffer GlobalDrawBuffer;

/**
 * @brief Default constructor function.
 */
draw_buffer::draw_buffer()
{
  mSize = screen::get_instance().get_size();
  
  mData.reserve(mSize.offset());
  mData.assign(mSize.offset(), achar(' ', default_attributes));
}

/**
 * @brief Resize the draw buffer based on the console screen
 *        size.
 */
void
draw_buffer::resize()
{
  mSize = screen::get_instance().get_size();

  mData.reserve(mSize.offset());
  mData.assign(mSize.offset(), achar(' ', default_attributes));
}

/**
 * @brief Return the size of the buffer in bytes.
 */
std::size_t
draw_buffer::size() const
{
  return mData.size();
}

/**
 * @brief Return the buffer data.
 */
astring &
draw_buffer::data()
{
  return mData;
}

/**
 * @brief Clear the draw buffer.
 * @param attr An attribute used for each cell in the cleared
 *             buffer.
 */
void
draw_buffer::clear(attr_t attr)
{
  mData.assign(mSize.offset(), achar(' ', attr));
}

/**
 * @brief Fill (naive) the draw buffer.
 * @param attr An attribute to use.
 * @param clear @c true to clear all characters, @c false to just
 *              apply an attribute.
 * @param empty The character to fill with if @c clear is @c true.
 */
void
draw_buffer::fill(attr_t attr, bool clear, char_t empty)
{
  for (std::size_t i = 0; i < mData.size(); ++i) {
    if (clear) {
      mData[i].character = empty;
    }
    mData[i].attribute = attr;
  }
}

/**
 * @brief Fill (naive) an area in the draw buffer.
 * @param area An area of the buffer to fill.
 * @param attr An attribute to use.
 * @param clear @c true to clear all characters, @c false to just
 *              apply an attribute.
 * @param empty The character to fill with if @c clear is @c true.
 */
void
draw_buffer::fill(rect &area, attr_t attr, bool clear, char_t empty)
{
  std::size_t left   = area.left();
  std::size_t right  = area.right();
  std::size_t top    = area.top();
  std::size_t bottom = area.bottom();
  std::size_t loc    = 0;
  std::size_t width  = screen::get_instance().get_columns();

  for (std::size_t x = left; x < right; ++x) {
    for (std::size_t y = top; y < bottom; ++y) {
      loc = x + y * width;

      if (clear) {
        mData[loc].character = empty;
      }
      mData[loc].attribute = attr;
    }
  }
}

/**
 * @brief Draw a rectangle in the draw buffer.
 * @param shape The rectangle geometry.
 * @param border The attribute for the rectangle border.
 * @param inside The attribute for the rectangle internals.
 * @param decoration @c true if you wish there to be a drawn
 *                   border, @c false for no border.
 */
void
draw_buffer::draw_rect(rect   &shape,
                       attr_t  border,
                       attr_t  inside,
                       bool    decoration)
{
  std::size_t left   = shape.left();
  std::size_t right  = shape.right();
  std::size_t top    = shape.top();
  std::size_t bottom = shape.bottom();
  std::size_t loc    = 0;
  std::size_t width  = screen::get_instance().get_columns();

  for (std::size_t x = left; x < right; ++x) {
    for (std::size_t y = top; y < bottom; ++y)
    {
      loc = x + y * width;

      if (y == top || y == bottom - 1) {
        if (decoration) {
          if (x == left && y == top) {
            mData[loc].character = dos_glyphs[TOP_LEFT].glyph;
            mData[loc].attribute = border;
          } else if (x == right - 1 && y == top) {
            mData[loc].character = dos_glyphs[TOP_RIGHT].glyph;
            mData[loc].attribute = border;
          } else if (x == left && y == bottom - 1) {
            mData[loc].character = dos_glyphs[BOTTOM_LEFT].glyph;
            mData[loc].attribute = border;
          } else if (x == right - 1 && y == bottom - 1) {
            mData[loc].character = dos_glyphs[BOTTOM_RIGHT].glyph;
            mData[loc].attribute = border;
          } else {
            mData[loc].character = dos_glyphs[VERTICAL].glyph;
            mData[loc].attribute = border;
          }
        }
      } else if (decoration && (x == left || x == right - 1)) {
        mData[loc].character = dos_glyphs[HORIZONTAL].glyph;
        mData[loc].attribute = border;
      } else {
        mData[loc].character = ' ';
        mData[loc].attribute = inside;
      }
    }
  }
}                                       // drawbuffer_::draw_rect

/**
 * @brief Move a buffer (or something else) to the buffer.
 * @param indent The offset the data will be placed at.
 * @param source The source data or buffer.
 * @param attr The attribute(s) to be used.
 * @param count The number of times the data is written.
 */
void
draw_buffer::move_buf(std::size_t  indent,
                      const void  *source,
                      attr_t       attr,
                      std::size_t  count)
{
  if (!count || (indent >= mSize.offset())) {
    return;
  }

  if (count + indent > mSize.offset()) {
    count = mSize.offset() - indent;
  }

  achar        *dest = &mData[indent];
  const char_t *s    = __CAST(const char_t *, source);

  if (attr.count() > 0) {
    while (count-- && *s) {
      dest->character = *s++;
      dest->attribute = attr;
      *dest++;
    }
  } else {
    while (count-- && *s) {
      dest->character = *s++;
      *dest++;
    }
  }
}

/**
 * @brief Move a character to the buffer.
 * @param indent The offset the character will be placed at.
 * @param c The character.
 * @param attr The attribute(s) for the character.
 * @param count The number of characters to write.
 */
void
draw_buffer::move_char(std::size_t indent,
                       char_t      c,
                       attr_t      attr,
                       std::size_t count)
{
  if (!count || (indent >= mSize.offset())) {
    return;
  }
  
  if (count + indent > mSize.offset()) {
    count = mSize.offset() - indent;
  }
  
  if (attr.count() > 0 ) {
    if (c) {
      for (std::size_t pos = 0; pos < count; ++pos) {
        mData[indent + pos].character = c;
        mData[indent + pos].attribute = attr;
      }
    } else {
      for (std::size_t pos = 0; pos < count; ++pos) {
        mData[indent + pos].attribute = attr;
      }
    } 
  } else {
    for (std::size_t pos = 0; pos < count; ++pos) {
      mData[indent + pos].character = c;
    }
  }
}

/**
 * @brief Move a character to the buffer.
 * @param indent The offset the character will be placed at.
 * @param c The attributed character.
 * @param count The number of characters to write.
 */
void
draw_buffer::move_char(std::size_t indent,
                       achar       c,
                       std::size_t count)
{
  if (!count || (indent >= mSize.offset())) {
    return;
  }

  if (count + indent > mSize.offset()) {
    count = mSize.offset() - indent;
  }

  if (c.character) {
    for (std::size_t pos = 0; pos < count; ++pos) {
      mData[indent + pos] = c;
    }
  } else {
    for (std::size_t pos = 0; pos < count; ++pos) {
      mData[indent + pos].attribute = c.attribute;
    }
  }
}

/**
 * @brief Move a C string to the buffer.
 * @param indent The offset the string will be placed at.
 * @param str The C string.
 * @param attrs The attribute(s) for the string.
 * @param decoration Decorate the string as a title?
 */
void
draw_buffer::move_cstr(std::size_t   indent,
                       const char_t *str,
                       attr_t        attrs,
                       bool          decoration)
{
  std::size_t pos = 0;
  std::size_t i   = 0;
  string_t    nstr(str);
  std::size_t len = nstr.length();

  if (decoration) {
    move_char(indent - 2,
              dos_glyphs[LEFT_LONG_HORZ_T].glyph,
              attrs,
              1);
    move_char(indent - 1,
              ' ',
              attrs,
              1);
  }

  for (i = 0; i < len; ++i) {
    if (nstr[i] == '\n') {
      pos += (mSize.width - (pos % mSize.width));
    } else {
      mData[indent + pos].character = nstr[i];
      mData[indent + pos].attribute = attrs;

      pos++;
    }
  }

  if (decoration) {
    move_char(indent + pos + 1,
              dos_glyphs[RIGHT_LONG_HORZ_T].glyph,
              attrs,
              1);
    move_char(indent + pos,
              ' ',
              attrs,
              1);
  }
}                                       // draw_buffer::move_cstr

/**
 * @brief Move a string to the buffer.
 * @param indent The offset the string will be placed at.
 * @param str The attributed string.
 * @param decoration Decorate the string as a title?
 */
void
draw_buffer::move_str(std::size_t    indent,
                      const astring &str,
                      bool           decoration)
{
  std::size_t pos = 0;
  std::size_t i   = 0;
  std::size_t len = str.size();

  if (len == 0) {
    return;
  }

  if (decoration) {
    move_char(indent - 2,
              dos_glyphs[LEFT_LONG_HORZ_T].glyph,
              str[0].attribute,
              1);
    move_char(indent - 1,
              ' ',
              str[0].attribute,
              1);
  }

  for (i = 0; i < len; ++i) {
    if (str[i].character == L'\n') {
      pos += (mSize.width - (pos % mSize.width));
    } else {
      move_char(indent + pos,
                str[i].character,
                __CAST(attr_t, str[i].attribute.to_ullong()),
                1);
      
      pos++;
    }
  }

  if (decoration) {
    move_char(indent + pos + 1,
              dos_glyphs[RIGHT_LONG_HORZ_T].glyph,
              str[0].attribute,
              1);
    move_char(indent + pos,
              ' ',
              str[0].attribute,
              1);
  }
}                                       // draw_buffer::move_str

/**
 * @brief Move a string to the buffer.
 * @param indent The offset the string will be placed at.
 * @param str The string.
 * @param attrs The attribute(s) for the string.
 * @param decoration Decorate the string as a title?
 */
void
draw_buffer::move_str(std::size_t     indent,
                      const string_t &str,
                      attr_t          attrs,
                      bool            decoration)
{
  move_cstr(indent, str.c_str(), attrs, decoration);
}

/**
 * @brief Dump the buffer to standard output.
 * @note This is only available in debug builds.
 */
void
draw_buffer::dump()
{
  screen::get_instance().render_buffer(*this);
}

/**
 * @brief Put an attribute to the buffer.
 * @param indent The offset the attribute will be placed at.
 * @param attr The attribute(s).
 */
void
draw_buffer::put_attribute(std::size_t indent, attr_t attr)
{
  mData[indent].attribute = attr;
}

/**
 * @brief Put a character to the buffer.
 * @param indent The offset the character will be placed at.
 * @param c The character.
 * @param attr The attribute(s) for the character.
 */
void
draw_buffer::put_char(std::size_t indent, char_t c, attr_t attr)
{
  mData[indent].character = c;
  mData[indent].attribute = attr;
}

/**
 * @brief Put a character to the buffer.
 * @param indent The offset the character will be placed at.
 * @param c The attributed character.
 */
void
draw_buffer::put_char(std::size_t indent, achar c)
{
  put_char(indent, c.character, c.attribute);
}

// drawbuffer.cpp ends here
