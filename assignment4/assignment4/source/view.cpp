//
// view.cpp --- View implementation.
//
// Copyright (c) 2014 Paul Ward <asmodai@gmail.com>
//
// Time-stamp: <Monday Apr 28, 2014 09:31:58 asmodai>
// Revision:   3
//
// Author:     Paul Ward <asmodai@gmail.com>
// Maintainer: Paul Ward <asmodai@gmail.com>
// Created:    15 Apr 2014 09:01:26
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
 * @file view.cpp
 * @author Paul Ward
 * @brief View implementation.
 */
 
#include "view.hpp"
#include "screen.hpp"
#include "drawbuffer.hpp"

using namespace ovision;

/**
 * @brief Default view client (outer) rect attributes.
 */
const attr_t DefaultViewClientAttr = fg_white | bg_blue | fg_intense;

/**
 * @brief Default view inner rect attributes.
 */
const attr_t DefaultViewInnerAttr  = fg_grey | bg_blue;

/**
 * @brief Default constructor function.
 */
view::view()
  : mClientRect(rect()),
    mInnerRect(rect()),
    mClientAttr(DefaultViewClientAttr),
    mInnerAttr(DefaultViewInnerAttr),
    mDrawBorder(true)
{}

/**
 * @brief Constructor method.
 * @param area The geometry rect for the view.
 */
view::view(rect &area)
  : mClientRect(area),
    mInnerRect(area.contract_copy(1, 1)),
    mClientAttr(DefaultViewClientAttr),
    mInnerAttr(DefaultViewInnerAttr),
    mDrawBorder(true)
{}

/**
 * @brief Constructor method.
 * @param area The geometry rect.
 * @param clientAttr Attributes for the client area.
 * @param innerAttr Attributes for the inner area.
 */
view::view(rect &area, attr_t clientAttr, attr_t innerAttr)
  : mClientRect(area),
    mInnerRect(area.contract_copy(1, 1)),
    mClientAttr(clientAttr),
    mInnerAttr(innerAttr),
    mDrawBorder(true)
{}

/**
 * @brief Destructor function.
 */
view::~view()
{}

/**
 * @brief Return the client rect geometry.
 */
rect &
view::client_rect()
{
  return mClientRect;
}

/**
 * @brief Return the inner rect geometry.
 */
rect &
view::inner_rect()
{
  return mInnerRect;
}

/**
 * @brief Return the inner rect attribute.
 */
attr_t
view::get_inner_attribute()
{
  return mInnerAttr;
}

/**
 * @brief Return the outer rect attribute.
 */
attr_t
view::get_client_attribute()
{
  return mClientAttr;
}

/**
 * @brief Set the inner rect attribute.
 */
void
view::set_inner_attribute(const attr_t attr)
{
  mInnerAttr = attr;
}

/**
 * @brief Set the outer rect attribute.
 */
void
view::set_client_attribute(const attr_t attr)
{
  mClientAttr = attr;
}

/**
 * @brief Does the view have a border?
 * @returns @c true if the view draws a border; otherwise @c false
 *          is returned.
 */
bool
view::get_draw_border() const
{
  return mDrawBorder;
}

/**
 * @brief Set whether the fiew draws a border.
 * @param flag @c true if the view should draw a border; @c false
 *             otherwise.
 */
void
view::set_draw_border(bool flag)
{
  mDrawBorder = flag;
}

/**
 * @brief Render the view to a draw buffer.
 */
void
view::render()
{
  extern draw_buffer GlobalDrawBuffer;

  GlobalDrawBuffer.draw_rect(mClientRect,
                             mClientAttr,
                             mClientAttr,
                             mDrawBorder);
  
  GlobalDrawBuffer.draw_rect(mInnerRect,
                             mInnerAttr,
                             mInnerAttr);
}

// view.cpp ends here
