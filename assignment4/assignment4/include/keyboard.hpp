//
// keyboard.hpp --- Keyboard handling.
//
// Copyright (c) 2014 Paul Ward <asmodai@gmail.com>
//
// Time-stamp: <Thursday Apr 17, 2014 19:24:41 asmodai>
// Revision:   3
//
// Author:     Paul Ward <asmodai@gmail.com>
// Maintainer: Paul Ward <asmodai@gmail.com>
// Created:    15 Apr 2014 09:22:41
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
 * @file keyboard.hpp
 * @author Paul Ward
 * @brief Keyboard handling.
 */

#pragma once
#ifndef _keyboard_hpp_
#define _keyboard_hpp_

#include "compiler.hpp"
#include "types.hpp"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include <iostream>

/**
 * @def KEY_ALT
 * @brief 'Alt' modifier key.
 *
 * @def KEY_CONTROL
 * @brief 'Control' modifier key.
 *
 * @def KEY_SHIFT
 * @brief 'Shift' modifier key.
 */
#define KEY_ALT     0x01
#define KEY_CONTROL 0x02
#define KEY_SHIFT   0x04
 
namespace ovision
{

  class screen;

  /**
   * @brief Keyboard controller class.
   */
  class keyboard
  {

    friend class screen;

    
    // Private member fields.
  private:

    INPUT_RECORD mInputRecord;          //!< Keyboard input record.
    key_t        mLastKey;              //!< Last key pressed.


    // Public static functions.
  public:

    static keyboard &get_instance();


    // Public member functions.
  public:

    void  clear();
    bool  kbhit();
    key_t get_keyboard_event();

    
    // Private member functions.
  private:

    // Constructor functions.
    keyboard();

    // Disabled functions.
    keyboard(const keyboard &);
    void operator = (const keyboard &);

  };                                    // class keyboard

}                                       // namespace ovision

#endif // !_keyboard_hpp_

// keyboard.hpp ends here
