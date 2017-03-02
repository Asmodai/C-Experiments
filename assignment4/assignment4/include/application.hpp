//
// application.hpp --- Application class.
//
// Copyright (c) 2014 Paul Ward <asmodai@gmail.com>
//
// Time-stamp: <Thursday Apr 17, 2014 19:03:35 asmodai>
// Revision:   4
//
// Author:     Paul Ward <asmodai@gmail.com>
// Maintainer: Paul Ward <asmodai@gmail.com>
// Created:    15 Apr 2014 09:20:34
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
 * @file application.hpp
 * @author Paul Ward
 * @brief Application class.
 */

#pragma once
#ifndef _application_hpp_
#define _application_hpp_

#include <vector>
#include <functional>

#include "frame.hpp"

/**
 * @brief Main Object Vision namespace.
 */
namespace ovision
{

  /**
   * @brief Application controller class.
   */
  class application
  {

    // Public type definitions.
  public:

    /**
     * @typedef kbcallback_t
     * @brief A callback function with the signature
     *        @c void @c function_name @c (char @c *) called whenever
     *        the application receives a keyboard event.
     *
     * @typedef kbcallback_t
     * @brief A vector of keyboard callback functions.
     */
    typedef std::function<void(char_t)> kbcallback_t;
    typedef std::vector<kbcallback_t> kbcallback_vector;
    
    
    // Private member fields.
  private:
    
    std::vector<view *> mViews;         //!< Views to manage.
    key_t               mLastKey;       //!< Last key pressed.
    key_t               mKey;           //!< Current key pressed.
    kbcallback_vector   mKeyCallbacks;  //!< Callbacks to call after keypress.
    bool                mRunning;       //!< Is the application running?
    int                 mReturnCode;    //!< Application's return code.
    

    // Public member functions.
  public:

    // Screen size functions.
    screen_size get_screen_size();
    void        set_screen_size(const screen_size &extent);

    // Cursor functions.
    screen_point get_cursor_position();
    void         set_cursor_position(screen_point &position);
    void         enable_cursor();
    void         disable_cursor();

    // Title functions.
    void set_title(const string_t &title);

    // View functions.
    void add_view(view &aView);

    // Callback functions.
    void add_key_callback(kbcallback_t fn);

    // Execution functions.
    int  start(void);
    void stop();
    
  };                                    // class application

}                                       // namespace ovision

#endif // !_application_hpp_

// application.hpp ends here
