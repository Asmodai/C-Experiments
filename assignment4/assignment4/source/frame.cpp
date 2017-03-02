//
// frame.cpp --- Frame implementation.
//
// Copyright (c) 2014 Paul Ward <asmodai@gmail.com>
//
// Time-stamp: <Thursday Apr 17, 2014 19:19:32 asmodai>
// Revision:   3
//
// Author:     Paul Ward <asmodai@gmail.com>
// Maintainer: Paul Ward <asmodai@gmail.com>
// Created:    15 Apr 2014 08:51:35
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
 * @file frame.cpp
 * @author Paul Ward
 * @brief Frame implementation.
 */
 
#include "frame.hpp"
#include "drawbuffer.hpp"
#include "screen.hpp"

using namespace ovision;

/**
 * @brief Default constructor function.
 */
frame::frame()
  : view()
{}

/**
 * @brief Constructor function.
 * @param area The initial geometry of the frame.
 */
frame::frame(rect &area)
  : view(area)
{}

/**
 * @brief Set the frame title.
 * @param title The string to use as the title.
 */
void
frame::set_title(const string_t &title)
{
  mTitle = title;
}

/**
 * @brief Return the frame title.
 */
string_t &
frame::get_title()
{
  return mTitle;
}

/**
 * @brief Render the frame to a draw buffer.
 */
void
frame::render()
{
  extern draw_buffer GlobalDrawBuffer;
  std::size_t        half;
  std::size_t        halfPos;

  half    = mClientRect.extent.width / 2 - mTitle.length() / 2;
  halfPos = mClientRect.origin.y * screen::get_instance().get_columns();

  if (half % 2 != 0) {
    half--;
  }

  view::render();

  GlobalDrawBuffer.draw_rect(mInnerRect,
                             mInnerAttr,
                             mInnerAttr);

  GlobalDrawBuffer.move_str(half + halfPos, mTitle, mClientAttr, true);
}

// frame.cpp ends here
