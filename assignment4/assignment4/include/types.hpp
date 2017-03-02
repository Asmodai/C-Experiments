//
// types.hpp --- Type definitions.
//
// Copyright (c) 2014 Paul Ward <asmodai@gmail.com>
//
// Time-stamp: <Wednesday Apr 16, 2014 21:33:06 asmodai>
// Revision:   5
//
// Author:     Paul Ward <asmodai@gmail.com>
// Maintainer: Paul Ward <asmodai@gmail.com>
// Created:    13 Apr 2014 19:41:23
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
 * @file types.hpp
 * @author Paul Ward
 * @brief Type definitions.
 */

#pragma once
#ifndef _types_hpp_
#define _types_hpp_

#include <cstdint>
#include <string>
#include <utility>
#include <bitset>

namespace ovision
{

  /**
   * @typedef char_t
   * @brief A character type dependant on OS character encoding.
   * @note This is either @c char or @c wchar_t
   *
   * @typedef uchar_t
   * @brief An unsigned character type dependant on OS character
   *        encoding.
   * @note On Unicode or multibyte character set systems, this is not
   *       unsigned.
   *
   * @typedef string_t
   * @brief A string type dependant on OS character encoding.
   * @note This is either @c std::string or @c std::wstring.
   */
#if defined(_MSC_VER)
# include <tchar.h>
  typedef _TSCHAR      char_t;
  typedef _TUCHAR      uchar_t;
  typedef std::wstring string_t;
#else
  typedef wchar_t      char_t;
  typedef wchar_t      uchar_t;
  typedef std::wstring string_t;
#endif

  /**
   * @brief Character attribute type.
   */
  typedef std::bitset<16> attr_t;

  /**
   * @brief Keyboard event structure.
   */
  typedef struct {
    std::uint16_t modifier;             //!< Modifier key information.
    char          character;            //!< Character for the key cap.
    std::uint16_t scancode;             //!< Raw scancode.
  } key_t;

}                                       // namespace ovision

#endif // !_types_hpp_

// types.hpp ends here
