//
// compiler.hpp --- Compiler helpers.
//
// Copyright (c) 2014 Paul Ward <asmodai@gmail.com>
//
// Time-stamp: <Wednesday Apr 16, 2014 15:18:18 asmodai>
// Revision:   2
//
// Author:     Paul Ward <asmodai@gmail.com>
// Maintainer: Paul Ward <asmodai@gmail.com>
// Created:    12 Apr 2014 08:32:34
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
 * @file compiler.hpp
 * @author Paul Ward
 * @brief Compiler helpers.
 */

#pragma once
#ifndef _compiler_hpp_
#define _compiler_hpp_

#define EXIT_NUM_ARGS         2
#define EXIT_NOT_A_NUMBER     3
#define EXIT_INVALID_FILENAME 4
#define EXIT_FILE_IMAGINARY   5
#define EXIT_NO_WORDS         6

/**
 * @def OVISION_UNICODE
 * @brief Are we to use Unicode rather than ASCII?
 *
 * If this is built on a compiler that does Unicode or MBCS, then this
 * flag is set so that we can use the wide character version of API
 * and the like.
 */
#if defined(_UNICODE) || defined(UNICODE) || defined(_MBCS)
# define OVISION_UNICODE
#endif

/**
 * @brief A convenience macro for casting.
 * @param __dt The data type to cast to.
 * @param __st The something to cast.
 */
#define __CAST(__dt, __st) static_cast<__dt>(__st)

#endif /* !_compiler_hpp_ */

// compiler.hpp ends here
