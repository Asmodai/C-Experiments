//
// view.hpp --- View metaclass.
//
// Copyright (c) 2014 Paul Ward <asmodai@gmail.com>
//
// Time-stamp: <Thursday Apr 17, 2014 19:42:38 asmodai>
// Revision:   4
//
// Author:     Paul Ward <asmodai@gmail.com>
// Maintainer: Paul Ward <asmodai@gmail.com>
// Created:    15 Apr 2014 08:46:53
// Keywords:   
// URL:        not distributed yet
//
// {{{ License:
//
// This file is part of foobar.
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

// }}}

/**
 * @file view.hpp
 * @author Paul Ward
 * @brief View metaclass.
 */

#pragma once
#ifndef _view_hpp_
#define _view_hpp_

#include "rect.hpp"
#include "types.hpp"

namespace ovision
{

  /**
   * @brief Base view class.
   */
  class view
  {

    // Protected member fields.
  protected:
    rect   mClientRect;                 //!< Main (outer) rect.
    rect   mInnerRect;                  //!< Inner rect.
    attr_t mClientAttr;                 //!< Client attributes
    attr_t mInnerAttr;                  //!< Inner attributes.
    bool   mDrawBorder;                 //!< Draw a border?


    // Public member functions.
  public:

    // Constructor and destructor functions.
    view();
    view(rect &area);
    view(rect &area, attr_t clientAttr, attr_t innerAttr);
    virtual ~view();

    // Rect functions.
    virtual rect &client_rect();
    virtual rect &inner_rect();

    // Attribute functions.
    virtual attr_t get_inner_attribute();
    virtual void   set_inner_attribute(const attr_t attr);
    virtual attr_t get_client_attribute();
    virtual void   set_client_attribute(const attr_t attr);

    // Border functions.
    virtual bool get_draw_border() const;
    virtual void set_draw_border(bool flag);

    // Render function.
    virtual void render();

  };                                    // class view

}                                       // namespace ovision

#endif // !_view_hpp_

// view.hpp ends here
