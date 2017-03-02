//
// frame.hpp --- Frames
//
// Copyright (c) 2014 Paul Ward <asmodai@gmail.com>
//
// Time-stamp: <Thursday Apr 17, 2014 19:20:19 asmodai>
// Revision:   5
//
// Author:     Paul Ward <asmodai@gmail.com>
// Maintainer: Paul Ward <asmodai@gmail.com>
// Created:    15 Apr 2014 08:49:21
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
 * @file frame.hpp
 * @author Paul Ward
 * @brief Frames
 */

#pragma once
#ifndef _frame_hpp_
#define _frame_hpp_

#include "view.hpp"
#include "char.hpp"

namespace ovision
{

  /**
   * @brief Frame class
   *
   * A frame is a view that has a border and, optionally, a title
   * string.
   */
  class frame
    : public view
  {

    // Protected member fields.
  protected:

    string_t mTitle;                    //!< The title for the frame.


    // Public member functions.
  public:

    // Constructor functions.
    frame();
    frame(rect &area);

    // Title functions.
    virtual void      set_title(const string_t &title);
    virtual string_t &get_title();

    // Render function.
    void render();

  };                                    // class frame
  
}                                       // namespace ovision

#endif // !_frame_hpp_

// frame.hpp ends here
