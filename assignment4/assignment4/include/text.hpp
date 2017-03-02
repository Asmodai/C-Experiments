//
// text.hpp --- Text views.
//
// Copyright (c) 2014 Paul Ward <asmodai@gmail.com>
//
// Time-stamp: <Thursday Apr 17, 2014 21:16:08 asmodai>
// Revision:   6
//
// Author:     Paul Ward <asmodai@gmail.com>
// Maintainer: Paul Ward <asmodai@gmail.com>
// Created:    15 Apr 2014 11:46:26
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
 * @file text.hpp
 * @author Paul Ward
 * @brief Text views.
 */

#pragma once
#ifndef _text_hpp_
#define _text_hpp_

#include "char.hpp"
#include "view.hpp"

namespace ovision
{

  /**
   * @brief Text alignment types.
   */
  enum text_align{
    AlignLeft,                          //!< Align text to the left.
    AlignRight,                         //!< Align text to the right.
    AlignCenter                         //!< Align text to the center.
  };


  /**
   * @brief Text view class.
   */
  class text
    : public view
  {

    // Public protected fields.
  protected:

    astring     mContents;              //!< String contents.
    std::size_t mWidth;                 //!< View width.
    text_align  mAlignment;             //!< Text alignment.


    // Public member functions.
  public:

    // Constructor functions.
    text();

    text(const string_t &content,
         screen_point   &location,
         std::size_t     width,
         attr_t          attr);
    
    text(const string_t &content,
         screen_point   &location,
         std::size_t     width,
         text_align      alignment,
         attr_t          attr);
    
    text(const string_t &content,
         screen_point   &location,
         attr_t          attr);


    // Attribute functions.
    virtual attr_t get_attribute();
    virtual void   set_attribute(const attr_t attr);
    
    // String functions.
    virtual string_t get_text();
    virtual void     set_text(const string_t &content);
    virtual void     set_text(const astring &content);
    virtual void     append(char_t ch);
    virtual void     append(achar &ach);
    virtual void     append(char_t ch, attr_t attr);

    // Alignment functions.
    virtual text_align get_alignment();
    virtual void       set_alignment(const text_align alignment);

    // Render function.
    void render();

    
    // Private member functions.
  private:

    void vs2010_does_not_do_delegated_ctors_hrmph(const string_t &content,
                                                  screen_point   &location,
                                                  std::size_t     width,
                                                  text_align      alignment,
                                                  attr_t          attr);
    
  };                                    // class text

}                                       // namespace ovision

#endif // !_text_hpp_

// text.hpp ends here
