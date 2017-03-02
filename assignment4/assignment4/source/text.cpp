//
// text.cpp --- Text view implementation.
//
// Copyright (c) 2014 Paul Ward <asmodai@gmail.com>
//
// Time-stamp: <Monday Apr 28, 2014 09:30:07 asmodai>
// Revision:   4
//
// Author:     Paul Ward <asmodai@gmail.com>
// Maintainer: Paul Ward <asmodai@gmail.com>
// Created:    15 Apr 2014 11:46:37
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
 * @file text.cpp
 * @author Paul Ward
 * @brief Text view implementation.
 */
 
#include "text.hpp"
#include "screen.hpp"

using namespace ovision;

/**
 * @brief Scan a string and count the number of newlines.
 * @param str The string to scan.
 * @returns The number of newlines found in the string or, if no
 *          newlines are found, @c 0 is returned.
 */
static
std::size_t
scan_for_newline(const string_t &str)
{
  std::size_t len = str.length();
  std::size_t i   = 0;
  std::size_t nls = 1;

  for (i = 0; i < len; ++i) {
    if (str[i] == '\n') {
      nls++;
    }
  }

  return nls;
}

/**
 * @brief Convenience function for the constructors.
 *
 * C++11 adds in 'delegated constructors' that allow constructors
 * to call other constructors from the same class, similar to how
 * constructors for a base class may be called.
 *
 * Visual Studio 2010 lacks this functionality, so this function
 * exists to avoid replicating code across multiple constructor
 * functions.
 */
void
text::vs2010_does_not_do_delegated_ctors_hrmph(const string_t &content,
                                               screen_point   &location,
                                               std::size_t     width,
                                               text_align      alignment,
                                               attr_t          attr)
{
  mWidth     = width;
  mAlignment = alignment;

  mClientRect.origin = location;
  mInnerRect.origin  = location;

  mClientAttr = attr;
  mInnerAttr  = attr;

  mInnerRect.extent.height = scan_for_newline(content);
  mInnerRect.extent.width  = mWidth;

  mContents.from_string(content, mInnerAttr);

  mClientRect.extent = mInnerRect.extent;
}

/**
 * @brief Default constructor function.
 */
text::text()
  : view(),
    mContents(),
    mAlignment(AlignLeft)
{}

/**
 * @brief Constructor function.
 * @param content The initial string content.
 * @param location The coordinates of the view.
 * @param attr The attributes to use for the view.
 */
text::text(const string_t &content, screen_point &location, attr_t attr)
  : view()
{  
  vs2010_does_not_do_delegated_ctors_hrmph(content,
                                           location,
                                           content.length(),
                                           AlignLeft,
                                           attr);
}

/**
 * @brief Constructor function.
 * @param content The initial string content.
 * @param location The coordinates of the view.
 * @param width The width of the view.
 * @param attr The attributes to use for the view.
 */
text::text(const string_t &content,
           screen_point   &location,
           std::size_t     width,
           attr_t          attr)
  : view()
{
  vs2010_does_not_do_delegated_ctors_hrmph(content,
                                           location,
                                           width,
                                           AlignLeft,
                                           attr);
}

/**
 * @brief Constructor function.
 * @param content The initial string content.
 * @param location The coordinates of the view.
 * @param width The width of the view.
 * @param alignment The text alignment.
 * @param attr The attributes to use for the view.
 */
text::text(const string_t &content,
           screen_point   &location,
           std::size_t     width,
           text_align      alignment,
           attr_t          attr)
  : view()
{
  vs2010_does_not_do_delegated_ctors_hrmph(content,
                                           location,
                                           width,
                                           alignment,
                                           attr);
}

/**
 * @brief Set the attributes for the view.
 * @param attr The attributes.
 */
void
text::set_attribute(const attr_t attr)
{
  mInnerAttr = mClientAttr = attr;
}

/**
 * @brief Get the attributes for the view.
 */
attr_t
text::get_attribute()
{
  return mInnerAttr;
}

/**
 * @brief Set the text alignment for the view.
 * @param alignment The alignment.
 */
void
text::set_alignment(const text_align alignment)
{
  mAlignment = alignment;
}

/**
 * @brief Get the alignment for the view.
 */
text_align
text::get_alignment()
{
  return mAlignment;
}

/**
 * @brief Append a character to the view.
 * @param ch The character.
 */
void
text::append(char_t ch)
{
  append(achar(ch, mInnerAttr));
}

/**
 * @brief Append an attributed character to the view.
 * @param ach The attributed character.
 */
void
text::append(achar &ach)
{
  mContents.push_back(ach);

  if (__CAST(std::size_t, mClientRect.extent.width) < mContents.length()) {
    mInnerRect.extent.width = mContents.length();
    mClientRect.extent      = mInnerRect.extent;
  }
}

/**
 * @brief Append a character and attribute to the view.
 * @param ch The character.
 * @param attr The attribute.
 */
void
text::append(char_t ch, attr_t attr)
{
  append(achar(ch, attr));
}

/**
 * @brief Set the text for the view.
 * @param content The text string.
 */
void
text::set_text(const string_t &content)
{
  std::size_t lines = scan_for_newline(content);

  mContents.from_string(content, mInnerAttr);

  if (__CAST(std::size_t, mClientRect.extent.height) < lines) {
    mInnerRect.extent.height = lines;
    mClientRect.extent       = mInnerRect.extent;
  }

  if (__CAST(std::size_t, mClientRect.extent.width) < mContents.length()) {
    mInnerRect.extent.width = mContents.length();
    mClientRect.extent      = mInnerRect.extent;
    mWidth                  = mInnerRect.extent.width;
  }
}

/**
 * @brief Set the text for the view.
 * @param content The text string.
 */
void
text::set_text(const astring &content)
{
  std::size_t lines = scan_for_newline(content.to_string());

  mContents = content;

  if (__CAST(std::size_t, mClientRect.extent.height) < lines) {
    mInnerRect.extent.height = lines;
    mClientRect.extent       = mInnerRect.extent;
  }

  if (__CAST(std::size_t, mClientRect.extent.width) < mContents.length()) {
    mInnerRect.extent.width = mContents.length();
    mClientRect.extent      = mInnerRect.extent;
    mWidth                  = mInnerRect.extent.width;
  }
}

/**
 * @brief Get the text for the view.
 */
string_t
text::get_text()
{
  return mContents.to_string();
}

/**
 * @brief Render the view to a draw buffer.
 */
void
text::render()
{
  extern draw_buffer GlobalDrawBuffer;

  std::size_t len = mContents.size();
  std::size_t pos = mClientRect.origin.x +
                    mClientRect.origin.y *
                    screen::get_instance().get_columns();

  if (len % 2 != 0) {
    len++;
  }

  switch (mAlignment) {
    case AlignRight:
      pos += (mClientRect.extent.width - len);
      break;

    case AlignCenter:
      pos += ((mClientRect.extent.width / 2) - (len / 2));
      break;

    case AlignLeft:
    default:
      /* Do nothing. */
      break;
  }
  
  GlobalDrawBuffer.move_str(pos,
                            mContents,
                            false);
}

// text.cpp ends here
