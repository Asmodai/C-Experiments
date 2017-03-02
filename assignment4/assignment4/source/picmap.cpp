//
// picmap.cpp --- Picture map implementation.
//
// Copyright (c) 2014 Paul Ward <asmodai@gmail.com>
//
// Time-stamp: <Monday Apr 28, 2014 09:24:32 asmodai>
// Revision:   2
//
// Author:     Paul Ward <asmodai@gmail.com>
// Maintainer: Paul Ward <asmodai@gmail.com>
// Created:    18 Apr 2014 16:01:37
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
 * @file picmap.cpp
 * @author Paul Ward
 * @brief Picture map implementation.
 */
 
#include "picmap.hpp"

using namespace ovision;

/**
 * @brief Default constructor function.
 */
picmap::picmap()
{
  mArea.origin.x     = mArea.origin.y      = 0;
  mArea.extent.width = mArea.extent.height = 0;
}

/**
 * @brief Constructor function.
 * @param width The initial picture width.
 * @param height The initial picture height.
 */
picmap::picmap(screen_size_type width, screen_size_type height)
{
  mArea.origin.x = 0;
  mArea.origin.y = 0;
  mArea.extent.width = width;
  mArea.extent.height = height;

  mData.assign(mArea.extent.offset(), achar(L' ', bg_black));
}

/**
 * @brief Copy constructor function.
 * @param other The other object to copy from.
 */
picmap::picmap(const picmap &other)
{
  mArea = other.mArea;
  mData = other.mData;
}

/**
 * @brief Return the picture data.
 */
astring &
picmap::data()
{
  return mData;
}

/**
 * @brief Return the area of the picture as a rect.
 */
rect &
picmap::get_area()
{
  return mArea;
}

/**
 * @brief Return the size of the ASCII/Unicode data.
 */
std::size_t
picmap::size()
{
  return mData.size();
}

/**
 * @brief Return the picture element at a given index.
 * @param index The index of the picture element to obtain.
 */
achar &
picmap::at(std::size_t index)
{
  return mData.at(index);
}

/**
 * @brief Assign elements to the picture data.
 * @param elems The number of elements to assign.
 * @param value The ASCII/unicode glyph to assign.
 */
void
picmap::assign(std::size_t elems, achar &value)
{
  mData.reserve(elems);
  mData.assign(elems, value);
}

/**
 * @brief Set the size of the picture.
 * @param extent The size of the picture.
 * @note This function will blank out the picture with spaces.
 */
void
picmap::set_size(screen_size &extent)
{
  mArea.extent = extent;

  mData.assign(mArea.extent.offset(), achar(L' ', bg_black));
}

/**
 * @brief Clear the picture data.
 */
void
picmap::clear()
{
  mData.clear();
}

/**
 * @brief Fill the picture with an attribute.
 * @param origin The offset to start the fill from.
 * @param attr The attribute to fill with.
 *
 * This fill method does not fill with a character or glyph, but with
 * an attribute.  Eventually there might be a character/glyph fill
 * function.
 */
void
picmap::fill(const screen_point &origin, attr_t attr)
{
  std::size_t pos = mData.size();
  std::size_t i   = 0;

  for (i = origin.offset(); i < pos; ++i) {
    mData[i].attribute = attr;
  }
}

/**
 * @brief Fill a rectangular region of the picture.
 * @param origin The origin location for the fill.
 * @param region The rectangular region to fill.
 * @param attr The attribute to fill with.
 *
 * This fill method does not fill with a character or glyph, but with
 * an attribute.  Eventually there might be a character/glyph fill
 * function.
 */
void
picmap::fill(const screen_point &origin, const rect &region, attr_t attr)
{
  std::size_t pos = region.origin.offset() + origin.offset();
  std::size_t i   = 0;

  for (i = 0; i < pos; ++i) {
    mData[i].attribute = attr;
  }
}

// picmap.cpp ends here
