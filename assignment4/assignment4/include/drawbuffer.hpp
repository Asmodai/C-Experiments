//
// drawbuffer.hpp --- Drawing buffer class.
//
// Copyright (c) 2014 Paul Ward <asmodai@gmail.com>
//
// Time-stamp: <Friday Apr 25, 2014 09:01:04 asmodai>
// Revision:   6
//
// Author:     Paul Ward <asmodai@gmail.com>
// Maintainer: Paul Ward <asmodai@gmail.com>
// Created:    13 Apr 2014 13:18:48
// Keywords:   
// URL:        not distributed yet
//
// {{{ License:
//
// This file is part of Object Vision.
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
 * @file drawbuffer.hpp
 * @author Paul Ward
 * @brief Drawing buffer class.
 */

#pragma once
#ifndef _drawbuffer_hpp_
#define _drawbuffer_hpp_

#include "types.hpp"
#include "rect.hpp"
#include "char.hpp"

namespace ovision
{

  /**
   * @brief Display/draw buffer class.
   */
  class draw_buffer
  {
    
    // Protected member fields.
  protected:
       
    screen_size mSize;                  //!< Buffer size.
    astring     mData;                  //!< Attributed string data.
    

    // Public member functions.
  public:

    // Constructor functions.
    draw_buffer();

    // Buffer functions.
    void     resize();
    std::size_t  size() const;
    astring &data();

    // Buffer drawing functions.
    void clear(attr_t attr = default_attributes);
    
    void fill(attr_t attr,
              bool   clear = false,
              char_t empty = ' ');
    
    void fill(rect   &area,
              attr_t  attr,
              bool    clear = false,
              char_t  empty = ' ');
    
    void draw_rect(rect   &shape,
                   attr_t  border,
                   attr_t  inside,
                   bool    decoration = false);

    // Buffer data movement.
    void move_char(std::size_t indent,
                   char_t      c,
                   attr_t      attr,
                   std::size_t count);
    
    void move_char(std::size_t indent,
                   achar       c,
                   std::size_t count);
    
    void move_str(std::size_t    indent,
                  const astring &str,
                  bool           decoration = false);
    
    void move_str(std::size_t     indent,
                  const string_t &str,
                  attr_t          attrs,
                  bool            decoration = false);
    
    void move_cstr(std::size_t   indent,
                   const char_t *str,
                   attr_t        attrs,
                   bool          decoration = false);
    
    void move_buf(std::size_t  indent,
                  const void  *source,
                  attr_t       attr,
                  std::size_t  count);

    // Single character cell functions.
    void put_attribute(std::size_t indent, attr_t attr);
    void put_char(std::size_t indent, char_t c, attr_t attr);
    void put_char(std::size_t indent, achar c);

    // Utility functions.
    void dump();

  };                                    // class draw_buffer
  
}                                       // namespace ovision

#endif // !_drawbuffer_hpp_

// drawbuffer.hpp ends here
