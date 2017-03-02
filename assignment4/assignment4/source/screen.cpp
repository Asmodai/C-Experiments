//
// screen.cpp --- Screen handling.
//
// Copyright (c) 2014 Paul Ward <asmodai@gmail.com>
//
// Time-stamp: <Thursday Apr 17, 2014 19:32:12 asmodai>
// Revision:   4
//
// Author:     Paul Ward <asmodai@gmail.com>
// Maintainer: Paul Ward <asmodai@gmail.com>
// Created:    15 Apr 2014 03:00:56
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
 * @file screen.cpp
 * @author Paul Ward
 * @brief Screen handling.
 */
 
#include <iostream>
#include <cstddef>
#include <cstdlib>
#include <utility>
#include <numeric>

#include "posix.hpp"
#include "screen.hpp"

using namespace ovision;

/**
 * @brief Default Windows console mode flags.
 */
#define DEFAULT_CONSOLE_MODE   ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT

/**
 * @brief Ensures the character/attribute buffer has enough space
 *        for the data we wish to put to it.
 * @param count The amount of data we wish to use.
 */
void
screen::ensure_capacity(std::size_t count)
{
  count = (count + 1) & 0xFFFFFFFE;

  if (mBufferCapacity < count) {
    free(mOutputBufferCI);
    mOutputBufferCI = (CHAR_INFO *)malloc(sizeof(CHAR_INFO) * count);
    mBufferCapacity = count;
  }
}

/**
 * @brief Returns the singleton class instance.
 */
screen &
screen::get_instance()
{
  static screen sInstance;

  return sInstance;
}

/**
 * @brief Main windows console event handler callback.
 * @param dwCtrlType The type of the control code event.
 * @returns @c TRUE if the function succeeds; otherwise @c FALSE
 *          is returned.
 *
 * This is a kludge, as I don't really wish to spend too long
 * playing with functional objects.
 *
 * This function simply calls the non-static
 * 'console_event_handler' function.
 */
BOOL WINAPI
screen::call_console_event_handler(DWORD dwCtrlType)
{
  return screen::get_instance().console_event_handler(dwCtrlType);
}

/**
 * @brief Default constructor function.
 */
screen::screen()
{}

/**
 * @brief Initialise the Windows console.
 */
bool
screen::init()
{
  mHInput  = GetStdHandle(STD_INPUT_HANDLE);
  mHStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
  mHOutput = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE,
                                       0,
                                       NULL,
                                       CONSOLE_TEXTMODE_BUFFER,
                                       NULL);
  
  if (mHStdOut == INVALID_HANDLE_VALUE ||
      mHOutput == INVALID_HANDLE_VALUE)
  {
    return false;
  }
  
  if (!SetConsoleActiveScreenBuffer(mHOutput)) {
    return false;
  }
  
  mInitialised = true;
  
  GetConsoleMode(mHInput, &mSavedConsoleMode);
  SetConsoleCtrlHandler(screen::call_console_event_handler, TRUE);
  SetConsoleMode(mHInput, DEFAULT_CONSOLE_MODE);
  
  TCHAR oldTitle[MAX_PATH];
  GetConsoleTitle(oldTitle, MAX_PATH);
  mOldTitle = string_t(oldTitle);
  
  set_size(screen_size(80, 25));
  
  if (mCursorDisabled) {
    disable_cursor();
  }
  
  return true;
}                                       // screen::init

/**
 * @brief Restore the Windows console to its previous state.
 */
void
screen::shutdown()
{
  suspend();
}

/**
 * @brief Temporarily suspend the current console state.
 *
 * This function restores the console saved state.  In the future,
 * this function will snapshot our console state so it can be
 * restored during a resume.
 */
void
screen::suspend()
{
  SetConsoleActiveScreenBuffer(mHStdOut);
  SetConsoleCtrlHandler(screen::call_console_event_handler, FALSE);
  SetConsoleMode(mHInput, mSavedConsoleMode);
  restore_title();
}

/**
 * @brief Resumes the console state from the last suspended state.
 *
 * This simply reinitialises the console to our settings, it does
 * not restore the buffer state et al.
 */
void
screen::resume()
{
  GetConsoleMode(mHInput, &mSavedConsoleMode);
  SetConsoleActiveScreenBuffer(mHOutput);

  mSavedScreenSize = screen_size(get_columns(), get_rows());
  mSavedCursorPos  = get_cursor_pos();

  SetConsoleCtrlHandler(screen::call_console_event_handler, TRUE);
  SetConsoleMode(mHInput, DEFAULT_CONSOLE_MODE);
}

/**
 * @brief Clear the console screen.
 */
void
screen::clear_screen() const
{
  if (mInitialised) {
    COORD coord = { 0, 0 };
    DWORD cWritten;

    FillConsoleOutputCharacter(mHOutput,
                               ' ',
                               get_size().offset(),
                               coord,
                               &cWritten);
    FillConsoleOutputAttribute(mHOutput,
                               FOREGROUND_RED  |
                               FOREGROUND_BLUE |
                               FOREGROUND_GREEN,
                               get_size().offset(),
                               coord,
                               &cWritten);
  }
}

/**
 * @brief Returns the number of columns the console can address.
 */
std::size_t
screen::get_columns() const
{
  if (mInitialised) {
    CONSOLE_SCREEN_BUFFER_INFO info;

    GetConsoleScreenBufferInfo(mHOutput, &info);

    return __CAST(std::size_t, info.dwSize.X);
  }

  return 80;
}

/**
 * @brief Returns the number of rows the console can address.
 */
std::size_t
screen::get_rows() const
{
  if (mInitialised) {
    CONSOLE_SCREEN_BUFFER_INFO info;

    GetConsoleScreenBufferInfo(mHOutput, &info);

    return __CAST(std::size_t, info.dwSize.Y);
  }

  return 25;
}

/**
 * @brief Return the number of character cells the console can
 * address.
 */
screen_size 
screen::get_size() const
{
  if (mInitialised) {
    CONSOLE_SCREEN_BUFFER_INFO info;

    GetConsoleScreenBufferInfo(mHOutput, &info);

    return screen_size(__CAST(std::size_t, info.dwSize.X),
                       __CAST(std::size_t, info.dwSize.Y));
  }

  return screen_size(80, 25);
}

// DANGER * DANGER * DANGER * DANGER * DANGER * DANGER * DANGER * DANGER
//
// The logic flow of this function is dangerous for your health.  Please
// refrain from reading the logic flow of this function.
//
// In fact, if you really must look at this function then there is something
// really wrong with you.  Here, have a cute little kitten to look at.
//
//                   .               ,.
//                  T."-._..---.._,-"/|
//                  l|"-.  _.v._   (" |
//                  [l /.'_ \; _~"-.`-t
//                  Y " _(o} _{o)._ ^.|
//                  j  T  ,-<v>-.  T  ]
//                  \  l ( /-^-\ ) !  !
//                   \. \.  "~"  ./  /c-..,__
//                     ^r- .._ .- .-"  `- .  ~"--.
//                      > \.                      \
//                      ]   ^.                     \
//                      3  .  ">            .       Y
//         ,.__.--._   _j   \ ~   .         ;       |
//        (    ~"-._~"^._\   ^.    ^._      I     . l
//         "-._ ___ ~"-,_7    .Z-._   7"   Y      ;  \        _
//            /"   "~-(r r  _/_--._~-/    /      /,.--^-._   / Y
//            "-._    '"~~~>-._~]>--^---./____,.^~        ^.^  !
//                ~--._    '   Y---.                        \./
//                     ~~--._  l_   )                        \
//                           ~-._~~~---._,____..---           \
//                               ~----"~       \
//                                              \
//
// There, perhaps now you have forgotten why you were looking at this function
// in the first place and now wish to go off to watch cat videos on YouTube,
// or perhaps you just want to play with some string.
//
// Either way, go away.
//
// DANGER * DANGER * DANGER * DANGER * DANGER * DANGER * DANGER * DANGER
#pragma warning (push)
#pragma warning (disable : 4533)
/**
 * @brief Set the screen size to the given size.
 * @param extent The screen size.
 */
void
screen::set_size(const screen_size &extent)
{
  static unsigned recurseTries = 0;

  // We implement a 'fake' recursion here using 'goto' rather than a
  // function call.  This behaves like recursion, but without risking
  // blowing away the stack.
fake_recurse:

  if (recurseTries >= 10) {
    // We've tried to jiggle the console size too many times, let's give up.
    goto give_up;
  }

  if (mInitialised) {
    CONSOLE_SCREEN_BUFFER_INFO info;
    extern draw_buffer         GlobalDrawBuffer;

    // Try to get the console buffer info.
    if (!GetConsoleScreenBufferInfo(mHOutput, &info)) {
      // Not a console, bye.
      return;
    }

    // Should we bother trying to resize the console?
    if (info.dwSize.X == __CAST(SHORT, extent.width) &&
        info.dwSize.Y == __CAST(SHORT, extent.height))
    {
      // Check if the window size needs changing.
      if (info.srWindow.Right  == __CAST(SHORT, extent.width) &&
          info.srWindow.Bottom == __CAST(SHORT, extent.height))
      {
        // Sizes are already the same, bye.
        return;
      }
    }

    // First, copy and clamp our new sizes.
    COORD newSize;
    
    newSize.X = 
      extent.width > __CAST(screen_size_type,
                            std::numeric_limits<SHORT>::max())
        ? std::numeric_limits<SHORT>::max()
        : __CAST(SHORT, extent.width);

    newSize.Y = 
      extent.height > __CAST(screen_size_type,
                             std::numeric_limits<SHORT>::max())
        ? std::numeric_limits<SHORT>::max()
        : __CAST(SHORT, extent.height);

    // Now build our window size.
    SMALL_RECT newWindow = {
      0,
      0,
      newSize.X,
      newSize.Y
    };

    // Now get the existing information.
    CONSOLE_SCREEN_BUFFER_INFOEX infoEx;

    infoEx.cbSize = sizeof(CONSOLE_SCREEN_BUFFER_INFOEX);
    if (!GetConsoleScreenBufferInfoEx(mHOutput, &infoEx)) {
      shutdown();

      posix::err(GetLastError(),
                 L"Could not read extended console information.");
    }

    // Modify it.
    infoEx.dwSize          = newSize;
    infoEx.srWindow.Right  = newWindow.Right;
    infoEx.srWindow.Bottom = newWindow.Bottom;

    // Send it back to the console.
    if (!SetConsoleScreenBufferInfoEx(mHOutput, &infoEx)) {
      shutdown();

      posix::err(GetLastError(),
                 L"Could not resize the console window to %dx%d\n",
                 __CAST(SHORT, extent.width),
                 __CAST(SHORT, extent.height));
    }

    // Test it.
    // Try to get the console buffer info.
    GetConsoleScreenBufferInfo(mHOutput, &info);

    if (info.srWindow.Right  < __CAST(SHORT, extent.width) ||
        info.srWindow.Bottom < __CAST(SHORT, extent.height))
    {
      // Recurse until the size is solved.
      recurseTries++;
      goto fake_recurse;
    }

give_up:
    GlobalDrawBuffer.resize();
    recurseTries = 0;
  }                                     // if (mInitialised)
}                                       // screen::set_size
#pragma warning (pop)

/**
 * @brief Returns the current cursor position.
 */
screen_point
screen::get_cursor_pos() const
{
  CONSOLE_SCREEN_BUFFER_INFO info;
  
  GetConsoleScreenBufferInfo(mHOutput, &info);
  
  return screen_point(info.dwCursorPosition.X, info.dwCursorPosition.Y);
}

/**
 * @brief Sets the cursor position
 * @param position The position to place the cursor.
 */
void
screen::set_cursor_pos(const screen_point &position) const
{
  COORD curPos;

  curPos.X = position.x;
  curPos.Y = position.y;

  SetConsoleCursorPosition(mHOutput, curPos);
}

/**
 * @brief Disables the cursor.
 */
void
screen::disable_cursor()
{
  CONSOLE_CURSOR_INFO cinfo;

  GetConsoleCursorInfo(mHOutput, &cinfo);

  cinfo.dwSize    = 2;
  cinfo.bVisible  = FALSE;
  mCursorDisabled = true;

  SetConsoleCursorInfo(mHOutput, &cinfo);
}

/**
 * @brief Enables the cursor.
 */
void
screen::enable_cursor()
{
  CONSOLE_CURSOR_INFO cinfo;

  GetConsoleCursorInfo(mHOutput, &cinfo);

  cinfo.dwSize    = 25;
  cinfo.bVisible  = TRUE;
  mCursorDisabled = false;

  SetConsoleCursorInfo(mHOutput, &cinfo);
}

/**
 * @brief Returns the character at the given position in the
 *        console's buffer.
 * @param pos The position.
 * @returns A character/attribute pair.
 */
achar
screen::get_character(const screen_point &pos) const
{
  COORD coord;
  DWORD cRead;
  WORD  attr;
  TCHAR ch;

  coord.Y = __CAST(SHORT, pos.y);
  coord.X = __CAST(SHORT, pos.x);

  ReadConsoleOutputAttribute(mHOutput, &attr, 1, coord, &cRead);
  ReadConsoleOutputCharacter(mHOutput, (TCHAR *)&ch, 1, coord, &cRead);

  return achar(__CAST(char_t, ch), __CAST(attr_t, attr));
}

/**
 * @brief Returns a specific number of sequential characters from
 *        the console's buffer.
 * @param pos The starting position.
 * @param count The number of characters to get.
 * @returns A character/attribute string.
 */
astring
screen::get_characters(const screen_point &pos, std::size_t count)
{
  COORD    coord;
  DWORD    cRead;
  WORD    *attr;
  TCHAR   *ch;
  astring  res;

  res.reserve(count);

  if ((attr = (WORD *)malloc(sizeof(WORD) * count)) == NULL) {
    shutdown();
    perror("Out of memory.");
  }

  if ((ch = (TCHAR *)malloc(sizeof(TCHAR) * count)) == NULL) {
    shutdown();
    perror("Out of memory.");
  }

  coord.Y = __CAST(SHORT, pos.x);
  coord.X = __CAST(SHORT, pos.y);

  ReadConsoleOutputAttribute(mHOutput, attr, count, coord, &cRead);
  ReadConsoleOutputCharacter(mHOutput, ch, count, coord, &cRead);

  for (count = 0; count < cRead; count++) {
    res.push_back(achar(ch[count], attr[count]));
  }

  free(attr);
  free(ch);

  return res;
}

/**
 * @brief Sets the character at the given position to the given
 *        value.
 * @param pos The position.
 * @param value The character/attribute pair.
 */
void
screen::set_character(const screen_point &pos, achar value)
{
  COORD      coord;
  COORD      dwBufferSize  = { 1, 1 };
  COORD      dwBufferCoord = { 0, 0 };
  SMALL_RECT region;

  ensure_capacity(1);

  coord.Y = __CAST(short, pos.x);
  coord.X = __CAST(short, pos.y);

  region.Top  = region.Bottom = coord.Y;
  region.Left = region.Right  = coord.X;

#if defined(OVISION_UNICODE)
  mOutputBufferCI[0].Char.UnicodeChar = value.character;
#else
  mOutputBufferCI[0].Char.AsciiChar   = value.character;
#endif

  mOutputBufferCI[0].Attributes = __CAST(WORD, value.attribute.to_ulong());

  WriteConsoleOutput(mHOutput,
                     mOutputBufferCI,
                     dwBufferSize,
                     dwBufferCoord,
                     &region);
}

/**
 * @brief Returns the current console input handle.
 */
HANDLE
screen::input_handle()
{
  return mHInput;
}

/**
 * @brief Is the cursor disabled?
 */
bool
screen::cursor_disabled()
{
  return mCursorDisabled;
}

/**
 * @brief Set the title of the console window.
 * @param title The new title to use.
 */
void
screen::set_title(const string_t &title)
{
  SetConsoleTitle(title.c_str());
}

/**
 * @brief Restores the previous console window title.
 *
 * This function restores the title from before the application
 * screen was initialised.  This allows the window title to be
 * set numerous times without consequence.
 */
void
screen::restore_title()
{
  SetConsoleTitle(mOldTitle.c_str());
}

/**
 * @brief Renders a @c draw_buffer to the console.
 * @param buffer The buffer to render.
 */
void
screen::render_buffer(draw_buffer &buffer)
{
  COORD      size  = { get_columns(), get_rows() };
  COORD      coord = { 0, 0 };
  SMALL_RECT wr    = { 0, 0, get_columns(), get_rows() };

  ensure_capacity(buffer.size());

  for (std::size_t i = 0; i < buffer.size(); ++i) {
    mOutputBufferCI[i].Char.UnicodeChar = buffer.data()[i].character;
    mOutputBufferCI[i].Attributes       = 
      __CAST(WORD, buffer.data()[i].attribute.to_ulong());
  }

  WriteConsoleOutput(mHOutput,
                     mOutputBufferCI,
                     size,
                     coord,
                     &wr);

  if (mCursorDisabled) {
    disable_cursor();
  }
}

/**
 * @brief Handles control code events.
 * @param dwCtrlType The type of control code event.
 * @returns @c TRUE if the event was handled successfully;
 *          otherwise @c FALSE is returned.
 */
BOOL WINAPI
screen::console_event_handler(DWORD dwCtrlType)
{
  if (dwCtrlType == CTRL_C_EVENT ||
      dwCtrlType == CTRL_BREAK_EVENT)
  {
    return FALSE;
  }

  return FALSE;
}

// screen.cpp ends here
