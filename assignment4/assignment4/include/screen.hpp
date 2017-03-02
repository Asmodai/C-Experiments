//
// screen.hpp --- Screen handling.
//
// Copyright (c) 2014 Paul Ward <asmodai@gmail.com>
//
// Time-stamp: <Thursday Apr 17, 2014 19:35:02 asmodai>
// Revision:   4
//
// Author:     Paul Ward <asmodai@gmail.com>
// Maintainer: Paul Ward <asmodai@gmail.com>
// Created:    15 Apr 2014 03:00:36
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
 * @file screen.hpp
 * @author Paul Ward
 * @brief Screen handling.
 */

#pragma once
#ifndef _screen_hpp_
#define _screen_hpp_

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <Windows.h>

#include "drawbuffer.hpp"

namespace ovision
{

  /**
   * @brief Screen handling singleton class.
   */
  class screen
  {
    
    // Private member fields.
   private:
    
    bool mInitialised;                  //!< Initialised?

    HANDLE mHInput;                     //!< Console input handle.
    HANDLE mHOutput;                    //!< Console output handle
    HANDLE mHStdOut;                    //!< Console standard output handle.

    DWORD         mSavedConsoleMode;    //!< Saved console mode.
    screen_size   mSavedScreenSize;     //!< Saved console size.
    screen_point  mSavedCursorPos;      //!< Saved cursor position
    CHAR_INFO    *mOutputBufferCI;      //!< Character/attribute buffer.
    std::size_t   mBufferCapacity;      //!< Buffer capacity.
    bool          mCursorDisabled;      //!< Cursor disabled?
    string_t      mOldTitle;            //!< Old console title.

    
    // Public static member functions.
  public:

    static screen &get_instance();

    static BOOL WINAPI call_console_event_handler(DWORD dwCtrlType);


    // Public member functions.
   public:

    // Execution functions.
    bool init();
    void shutdown();
    void suspend();
    void resume();

    // Screen utilities.
    void clear_screen() const;

    // Screen size functions.
    std::size_t get_columns() const;
    std::size_t get_rows() const;
    screen_size get_size() const;
    void        set_size(const screen_size &extent);

    // Cursor functions.
    screen_point get_cursor_pos() const;
    void         set_cursor_pos(const screen_point &position) const;
    void         enable_cursor();
    void         disable_cursor();
    bool         cursor_disabled();

    // Window title functions.
    void set_title(const string_t &title);
    void restore_title();

    // Character buffer functions.
    achar   get_character(const screen_point &pos) const;
    astring get_characters(const screen_point &pos, std::size_t count);
    void    set_character(const screen_point &pos, achar value);

    // Rendering function.
    void render_buffer(draw_buffer &buffer);

    // Accessor functions.
    HANDLE input_handle();

    // Windows callback function.
    BOOL WINAPI console_event_handler(DWORD dwCtrlType);

    
    // Private member functions.
  private:

    // Constructor function.
    screen();

    // Disabled functions.
    screen(const screen &);
    void operator = (const screen &);

    // Utility functions.
    void ensure_capacity(std::size_t count);

  };                                    // class screen

}                                       // namespace ovision

#endif // !_screen_hpp_

// screen.hpp ends here
