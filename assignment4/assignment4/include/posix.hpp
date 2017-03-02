//
// posix.hpp --- Stuff stolen from POSIX.
//
// Copyright (c) 2014 Paul Ward <asmodai@gmail.com>
//
// Time-stamp: <Thursday Apr 17, 2014 18:58:35 asmodai>
// Revision:   24
//
// Author:     Paul Ward <asmodai@gmail.com>
// Maintainer: Paul Ward <asmodai@gmail.com>
// Created:    15 Apr 2014 21:31:30
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
 * @file posix.hpp
 * @author Paul Ward
 * @brief Stuff stolen from POSIX.
 */

#pragma once
#ifndef _posix_hpp_
#define _posix_hpp_

#include <cstdarg>
#include <tchar.h>

/**
 * @brief Utility functions that are present on POSIX-conforming operating
 *        systems.
 */
namespace posix
{

  // Pathname functions.
  TCHAR *basename(TCHAR *path, const bool stripExt = true);

  // Program name functions.
  const TCHAR *getprogname();

  // Warning functions.
  void vwarn(const TCHAR *fmt, va_list args);
  void warn(const TCHAR *fmt, ...);

  // Error functions.
  void err(const int errorVal, const TCHAR *fmt, ...);
  void verr(const int eval, const TCHAR *fmt, va_list args);
  
};                                      // namespace posix

#endif // !_posix_hpp_

// posix.hpp ends here
