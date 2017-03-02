//
// keyboard.cpp --- Keyboard handling implementation.
//
// Copyright (c) 2014 Paul Ward <asmodai@gmail.com>
//
// Time-stamp: <Thursday Apr 17, 2014 19:23:29 asmodai>
// Revision:   3
//
// Author:     Paul Ward <asmodai@gmail.com>
// Maintainer: Paul Ward <asmodai@gmail.com>
// Created:    15 Apr 2014 09:23:15
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
 * @file keyboard.cpp
 * @author Paul Ward
 * @brief Keyboard handling implementation.
 */
 
#include "keyboard.hpp"
#include "screen.hpp"

using namespace ovision;

/**
 * @brief Return the shared (singleton) instance of the keyboard
 *        handler class.
 */
keyboard &
keyboard::get_instance()
{
  static keyboard sInstance;

  return sInstance;
}

/**
 * @brief Constructor function.
 */
keyboard::keyboard()
{
  mLastKey.character = 0;
  mLastKey.modifier  = 0;
  mLastKey.scancode  = 0;
}

/**
 * @brief Clear any keyboard events.
 */
void
keyboard::clear()
{
  FlushConsoleInputBuffer(screen::get_instance().input_handle());
}

/**
 * @brief Has any key been pressed?
 * @returns @c true if there is a keyboard event in the queue;
 *          otherwise @c false is returned.
 *
 * This should not be used for keyboard entry, only for looping
 * until a key is pressed.
 */
bool
keyboard::kbhit()
{
  DWORD cEvents;

  while (PeekConsoleInput(screen::get_instance().input_handle(),
                          &mInputRecord,
                          1,
                          &cEvents)
         && cEvents == 1)
  {
    if (mInputRecord.EventType != KEY_EVENT) {
      ReadConsoleInput(screen::get_instance().input_handle(),
                       &mInputRecord,
                       1,
                       &cEvents);
      continue;
    }

    if (!mInputRecord.Event.KeyEvent.bKeyDown) {
      ReadConsoleInput(screen::get_instance().input_handle(),
                       &mInputRecord,
                       1,
                       &cEvents);
    } else {
      return true;
    }
  }

  return false;
}

/**
 * @brief Get a keyboard event from the input buffer.
 * @returns Information about the keyboard event, if any.
 */
key_t
keyboard::get_keyboard_event()
{
  
  DWORD cEvents;

  if (screen::get_instance().cursor_disabled()) {
    screen::get_instance().disable_cursor();
  }

  ReadConsoleInput(screen::get_instance().input_handle(),
                   &mInputRecord,
                   1,
                   &cEvents);



  if (mInputRecord.Event.KeyEvent.bKeyDown) {
    DWORD dwCtlState  = mInputRecord.Event.KeyEvent.dwControlKeyState;
    mLastKey.modifier = 0;

    if (dwCtlState & SHIFT_PRESSED) {
      mLastKey.modifier = KEY_SHIFT;
    }

    if (dwCtlState & LEFT_CTRL_PRESSED | RIGHT_CTRL_PRESSED) {
      mLastKey.modifier = KEY_CONTROL;
    }

    if (dwCtlState & LEFT_ALT_PRESSED | RIGHT_ALT_PRESSED) {
      mLastKey.modifier = KEY_ALT;
    }

    mLastKey.scancode  = mInputRecord.Event.KeyEvent.wVirtualScanCode;
    mLastKey.character = mInputRecord.Event.KeyEvent.uChar.AsciiChar;
  } else {
    mLastKey.character = 0;
  }

  if (screen::get_instance().cursor_disabled()) {
    screen::get_instance().disable_cursor();
  }

  return mLastKey;
}                                       // keyboard::get_keyboard_event

// keyboard.cpp ends here
