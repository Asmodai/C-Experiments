//
// posix.cpp --- POSIX implementation.
//
// Copyright (c) 2014 Paul Ward <asmodai@gmail.com>
//
// Time-stamp: <Thursday Apr 17, 2014 19:48:14 asmodai>
// Revision:   4
//
// Author:     Paul Ward <asmodai@gmail.com>
// Maintainer: Paul Ward <asmodai@gmail.com>
// Created:    16 Apr 2014 17:23:10
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
 * @file posix.cpp
 * @author Paul Ward
 * @brief POSIX implementation.
 */

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <cstdlib>
#include <cstring>

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <Shlwapi.h>
#include <psapi.h>

#pragma comment(lib, "shlwapi.lib")
#pragma comment(lib, "psapi.lib")

#include "types.hpp"
#include "compiler.hpp"
#include "posix.hpp"

/**
 * @brief Strip directory, suffix, and extension from file names.
 * @param path The path to strip.
 * @param stripExt If true, the extension is stripped.
 * @returns A pointer to a null-terminated string.
 * @note This does not conform to POSIX.1-2001.
 * @note The extension will be stripped by default.
 */
TCHAR *
posix::basename(TCHAR *path, const bool stripExt)
{
  TCHAR *strptr = path;
  
  // Strip the file extension, if required.
  if (stripExt) {
    PathRemoveExtension(strptr);
  }

  // Extract the file name component.
  strptr = PathFindFileName(strptr);

  // Return it.
  return strptr;
}

/**
 * @brief Get the program name.
 * @returns The program name.
 *
 * This function is not part of the POSIX specification itself, but is
 * a mighty useful function taken from Linux and FreeBSD.
 */
const TCHAR *
posix::getprogname()
{
  static TCHAR THE_PROGRAM_NAME[MAX_PATH];
  HANDLE       hProcess = GetCurrentProcess();

  /*
    * hProcess is set to a 'pseudo handle' which, annoyingly, is the
    * same value as INVALID_HANDLE_VALUE... so, don't test if the
    * handle is invalid, because it will be, even though the value
    * tells the psapi calls to deal with the current process.
    */
    
  if (!GetModuleBaseName(hProcess,
                          NULL,
                          THE_PROGRAM_NAME,
                          MAX_PATH))
  {
    throw std::runtime_error("Could not get program name.");
  }
    
  CloseHandle(hProcess);
    
  return (const TCHAR *)basename(THE_PROGRAM_NAME);
}

#pragma warning (push)
#pragma warning (disable : 4996)
/**
 * @brief Display a formatted warning message.
 * @param fmt The format string.
 * @param args The format arguments.
 *
 * This function is quite complex in its operation, and is designed to
 * avoid using C character arrays and pointers as much as possible.
 *
 * We attempt to write out the expanded format string to a vector of
 * characters (which simulates a C character array).
 *
 * If vsnprintf returns -1, then we double the size of the character
 * vector and then try again, and keep trying until vsnprintf returns
 * something else.
 *
 * If vsnprintf returns a value above -1, then we simply increment the
 * size of the character vector (by one element) and keep trying until
 * vsnprintf returns something else.
 *
 * If vsnprintf returns buffer.size() exactly, then everything worked
 * as planned and we can break out of the loop.
 */
void
posix::vwarn(const TCHAR *fmt, va_list args)
{
  std::vector<TCHAR> buffer(100, '\0');
    
  // Loop forever
  while (true) {     
    // This is the meat of the function, and uses a hack to succeed.
    // We treat a vector of characters as a C string. 
    auto n = _vsntprintf((TCHAR *)buffer.data(),
                           buffer.size(),
                           fmt,
                           args);
      
    // Has the vsnprintf operation succeeded in the amount of space we
    // have set aside for it?
    if ((n > -1) && (std::size_t(n) < buffer.size())) {
      // Yes, then we do not need to do anything else here.
      break;
    }
      
    // vsnprintf returns -1 upon error -- such as not enough space
    // in the buffer -- the code below takes advantage of this.
      
    // Did vsnprintf output something to the vector successfully?
    if (n > -1) {
      // Yes, but not enough, so just resize the vector by one element.
      buffer.resize(n + 1);
    } else {
      // No, so double the size of the vector.
      buffer.resize(buffer.size() * 2);
    }
      
    // At this point, our vector is resized so we simply loop back to
    // the top and try the whole vsnprintf thing again.
  }                                     // while (true)
    
  // Write the error message to stderr.
#if defined(OVISION_UNICODE)
  std::wcerr 
#else
  std::cerr
#endif
    << getprogname() << ": " << buffer.data() << std::endl;
}
#pragma warning (pop)

/**
 * @brief Display a formatted warning message.
 * @param fmt The format string.
 * @param ... The format args.
 */
void
posix::warn(const TCHAR *fmt, ...)
{
  va_list args;
  
  va_start(args, fmt);
  vwarn(fmt, args);
  va_end(args);
}

/**
 * @brief Display a formatted error message and exit.
 * @param errorVal The error value to return to the OS.
 * @param fmt The format string.
 * @param ... The format arguments.
 */
void
posix::err(const int errorVal, const TCHAR *fmt, ...)
{
  va_list args;

  va_start(args, fmt);
  vwarn(fmt, args);
  va_end(args);
    
  // Exit back to the operating system.
  exit(errorVal);
}

/**
 * @brief Display a formatted error message and exit.
 * @param eval The error value to return to the OS.
 * @param fmt The format string.
 * @param args The format arguments.
 */
void
posix::verr(const int eval, const TCHAR *fmt, va_list args)
{
  vwarn(fmt, args);
  exit(eval);
}

// posix.cpp ends here
