//
// picmap.hpp --- Picture map class.
//
// Copyright (c) 2014 Paul Ward <asmodai@gmail.com>
//
// Time-stamp: <Friday Apr 25, 2014 08:58:46 asmodai>
// Revision:   2
//
// Author:     Paul Ward <asmodai@gmail.com>
// Maintainer: Paul Ward <asmodai@gmail.com>
// Created:    18 Apr 2014 15:34:04
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
 * @file picmap.hpp
 * @author Paul Ward
 * @brief Picture map class.
 */

#pragma once
#ifndef _picmap_hpp_
#define _picmap_hpp_

#include "char.hpp"
#include "rect.hpp"

namespace ovision
{

  /**
   * @brief Picture map class.
   *
   * This class provides a very simple picture representation using
   * ANSI characters and attributes.
   */
  class picmap
  {

    // Protected member fields.
  protected:

    astring mData;                      //!< Picture data.
    rect    mArea;                      //!< Data attributes.


    // Public member functions.
  public:

    // Constructors.
    picmap();

    picmap(screen_size_type width,
           screen_size_type height);

    picmap(screen_size &size);

    picmap(const picmap &other);


    // Reader functions.
    astring     &data();
    std::size_t  size();
    achar       &at(std::size_t index);

    // Writer functions.
    void assign(std::size_t elems, achar &value);
    void set_size(screen_size &extent);
    
    // Utility functions.
    rect &get_area();

    // Drawing functions.
    void clear();
    void fill(const screen_point &origin, attr_t attr);
    void fill(const screen_point &origin, const rect &region, attr_t attr);
 
  };                                    // class picmap

}                                       // namespace ovision

#endif // !_picmap_hpp_

// picmap.hpp ends here
