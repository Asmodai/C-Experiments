//
// picture.hpp --- Picture view class.
//
// Copyright (c) 2014 Paul Ward <asmodai@gmail.com>
//
// Time-stamp: <Monday Apr 28, 2014 09:35:06 asmodai>
// Revision:   2
//
// Author:     Paul Ward <asmodai@gmail.com>
// Maintainer: Paul Ward <asmodai@gmail.com>
// Created:    18 Apr 2014 15:33:27
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
 * @file picture.hpp
 * @author Paul Ward
 * @brief Picture view class.
 */

#pragma once
#ifndef _picture_hpp_
#define _picture_hpp_

#include "char.hpp"
#include "view.hpp"
#include "picmap.hpp"

namespace ovision
{

  /**
   * @brief Picture view class.
   */
  class picture
    : public view
  {

    // Protected member fields.
  protected:

    picmap mContent;                    //!< Picture contents.


    // Public member functions.
  public:
    
    // Constructor functions.
    picture();
    picture(rect &area);

    // Accessor functions.
    virtual void    set_picmap(const picmap &data);
    virtual picmap &get_picmap();

    // Drawing functions.
    void fill(attr_t attr);

    // Utility functions.
    void render();
    
  };                                    // class picture
  
}                                       // namespace ovision

#endif // !_picture_hpp_

// picture.hpp ends here
