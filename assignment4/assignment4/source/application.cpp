//
// application.cpp --- Application implementation.
//
// Copyright (c) 2014 Paul Ward <asmodai@gmail.com>
//
// Time-stamp: <Thursday Apr 17, 2014 19:02:16 asmodai>
// Revision:   4
//
// Author:     Paul Ward <asmodai@gmail.com>
// Maintainer: Paul Ward <asmodai@gmail.com>
// Created:    15 Apr 2014 09:20:45
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
 * @file application.cpp
 * @author Paul Ward
 * @brief Application implementation.
 */
 
#include <algorithm>
#include <stdexcept>

#include "application.hpp"
#include "screen.hpp"
#include "keyboard.hpp"

using namespace ovision;

/**
 * @brief Add a view instance to the vector of managed views.
 * @param aView The view to manage.
 *
 * Managed views will be rendered to the console during the idle
 * loop.
 */
void
application::add_view(view &aView)
{
  mViews.push_back(&aView);
}

/**
 * @brief Add a callback for `keyboard press' events.
 * @param fn The function to add.
 * @see kbcallback_t
 */
void
application::add_key_callback(kbcallback_t fn)
{
  mKeyCallbacks.push_back(fn);
}

/**
 * @brief Return the current screen size.
 */
screen_size
application::get_screen_size()
{
  return screen::get_instance().get_size();
}

/**
 * @brief Return the current cursor position.
 */
screen_point
application::get_cursor_position()
{
  return screen::get_instance().get_cursor_pos();
}

/**
 * @brief Set the cursor position.
 * @param position The screen point the cursor is to be placed.
 */
void
application::set_cursor_position(screen_point &position)
{
  screen::get_instance().set_cursor_pos(position);
}

/**
 * @brief Enable the cursor.
 *
 * This will show the blinking caret on the screen.
 */
void
application::enable_cursor()
{
  screen::get_instance().enable_cursor();
}

/**
 * @brief Disable the cursor.
 *
 * This will hide the blinking caret on the screen.
 */
void
application::disable_cursor()
{
  screen::get_instance().disable_cursor();
}

/**
 * @brief Set the title of the console window.
 * @param title The new title to use.
 */
void
application::set_title(const string_t &title)
{
  screen::get_instance().set_title(title);
}

/** 
 * @brief Set the screen size.
 * @param extent The new screen size.
 */
void
application::set_screen_size(const screen_size &extent)
{
  screen::get_instance().set_size(extent);
}

/**
 * @brief Start the application main loop.
 */
int
application::start()
{
  extern draw_buffer GlobalDrawBuffer;

  mRunning    = true;
  mReturnCode = EXIT_SUCCESS;
  
  keyboard::get_instance().clear();
  mKey.character = 0;

  try {
    if (screen::get_instance().init() == false) {
      screen::get_instance().shutdown();
      std::cerr << "Could not initialise the Windows console." << std::endl;
      exit(EXIT_FAILURE);
    }

    screen::get_instance().clear_screen();
    GlobalDrawBuffer.clear();

    while (mRunning) {
      for (std::size_t i = 0; i < mViews.size(); ++i) {
        mViews[i]->render();
      }

      GlobalDrawBuffer.dump();

      while (mKey.character == 0) {
        mLastKey = mKey;
        mKey     = keyboard::get_instance().get_keyboard_event();
      }

      if (mKey.character == 3) {
        goto terminate_application;
      }

      for (std::size_t fn = 0; fn < mKeyCallbacks.size(); ++fn) {
        mKeyCallbacks[fn](mKey.character);
      }

     mKey.character = 0;
    }

terminate_application:
    screen::get_instance().shutdown();
  }

  // Catch any specific exceptions.
  catch (const std::exception &e) {
    screen::get_instance().shutdown();

    std::cerr << "An exception was caught:" << std::endl
              << e.what() << std::endl
              << "Terminating." << std::endl;

    return EXIT_FAILURE;
  }

  // Catch anything.
  catch (...) {
    screen::get_instance().shutdown();
    
    std::cerr << "An unhandled exception occured.  Terminating."
              << std::endl;
    
    return EXIT_FAILURE;
  }

  return mReturnCode;
}                                       // application::start

/**
 * @brief Stop the application main loop.
 *
 * This will result in the application returning to the 'start'
 * callee.
 */
void
application::stop()
{
  mRunning = false;
}

// application.cpp ends here
