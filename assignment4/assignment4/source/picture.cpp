//
// picture.cpp --- Picture class implementation.
//
// Copyright (c) 2014 Paul Ward <asmodai@gmail.com>
//
// Time-stamp: <Monday Apr 28, 2014 09:26:24 asmodai>
// Revision:   2
//
// Author:     Paul Ward <asmodai@gmail.com>
// Maintainer: Paul Ward <asmodai@gmail.com>
// Created:    18 Apr 2014 15:33:42
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
 * @file picture.cpp
 * @author Paul Ward
 * @brief Picture class implementation.
 */
 
#include "screen.hpp"
#include "drawbuffer.hpp"
#include "picture.hpp"

using namespace ovision;

/**
 * @brief Default constructor function.
 */
picture::picture()
  : view()
{}

/**
 * @brief Constructor function.
 * @param area A rectangle that defines the views extents.
 */
picture::picture(rect &area)
  : view(area)
{
  mContent.set_size(screen_size(mInnerRect.extent.width,
                                mInnerRect.extent.height));
}

/**
 * @brief Set the picture map data.
 * @param data The picture map data.
 */
void
picture::set_picmap(const picmap &data)
{
  mContent = data;
}

/**
 * @brief Get the picture map data.
 * @returns The picture map data.
 */
picmap &
picture::get_picmap()
{
  return mContent;
}

/**
 * @brief Fill the view.
 * @param attr The attribute to fill with.
 */
void
picture::fill(attr_t attr)
{
  mContent.fill(screen_point(0, 0), attr);
}

/**
 * @brief Render the view.
 */
void
picture::render()
{
  extern draw_buffer GlobalDrawBuffer;
  std::size_t        left   = mInnerRect.left();
  std::size_t        right  = mInnerRect.right();
  std::size_t        top    = mInnerRect.top();
  std::size_t        bottom = mInnerRect.bottom();
  std::size_t        width  = screen::get_instance().get_columns();
  std::size_t        height = screen::get_instance().get_rows();
  std::size_t        pos    = 0;
  std::size_t        idx    = 0;

  view::render();

  for (std::size_t y = top; y < bottom; ++y) {
    for (std::size_t x = left; x < right; ++x) {  
      pos = x + y * width;

      GlobalDrawBuffer.put_char(pos, mContent.at(idx++));
    }
  }
}

// picture.cpp ends here
