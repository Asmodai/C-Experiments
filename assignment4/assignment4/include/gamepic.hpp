//
// gamepic.hpp --- Game picture builder.
//
// Copyright (c) 2014 Paul Ward <asmodai@gmail.com>
//
// Time-stamp: <Wednesday Sep 24, 2014 19:29:02 asmodai>
// Revision:   4
//
// Author:     Paul Ward <asmodai@gmail.com>
// Maintainer: Paul Ward <asmodai@gmail.com>
// Created:    18 Apr 2014 19:31:59
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
 * @file gamepic.hpp
 * @author Paul Ward
 * @brief Game picture builder.
 */

#pragma once
#ifndef _gamepic_hpp_
#define _gamepic_hpp_

#include "compiler.hpp"
#include "char.hpp"
#include "picmap.hpp"
#include "types.hpp"

using namespace ovision;

#include "../resources/background.tpm"
#include "../resources/gallows.tpm"
#include "../resources/victim1.tpm"
#include "../resources/victim2.tpm"
#include "../resources/hangman.tpm"

/**
 * @brief Picture generator.
 *
 * This class generates the 'hangman' pictures used by the game.
 */
class pic_generator
{

  // Public member fields.
public:
  
  static std::size_t mMaxGuesses;       //!< Maximum number of guesses.


  // Public static member functions.
public:

  /**
   * @brief COmpute the picture for a given number of lives used.
   * @param lives The number of lives used the picture will represent.
   * @param maximum The maximum number of lives.
   * @returns The computed picture.
   */
  static
  picmap &
  compute_picmap(std::size_t lives, std::size_t maximum)
  {
    static std::size_t gheight = GALLOWS1_height;
    static std::size_t vheight = VICTIM1_height;
    static std::size_t hheight = HANGMAN1_height;
    
    std::size_t used = maximum - lives;

    if (used == maximum) {
      return victim2();
    } else {
      lives--;

      if (lives <= vheight) {           // 0...3
        return victim1(lives);
      } else if (lives > vheight && lives < hheight + vheight) { // 4...7
        return hangman(lives - vheight);
      } else {
        return gallows1(lives - (hheight + vheight));
      }

    }

    return background();
  }


  // Private static member functions.
private:

  /**
   * @brief Geerate the background field.
   * @returns A computed picture.
   */
  static
  picmap &
  background()
  {
    static picmap      base;
    static std::size_t len = BACKGROUND_width * BACKGROUND_height;

    base.clear();
    base.assign(len, achar(' ', bg_black));

    for (std::size_t i = 0; i < len; ++i) {
      base.at(i).character = BACKGROUND_elems[i];
      base.at(i).attribute = BACKGROUND_attrs[i];
    }

    return base;
  }

  /**
   * @brief Overlay a picture by a limited amount (i.e, n lines).
   * @param base The base picture to draw on.
   * @param glyphs The picture data to draw.
   * @param attrs The attributes for the data.
   * @param left The left coordinate to draw at.
   * @param top The top coordinate to draw at.
   * @param width The width of the data.
   * @param height The height of the data.
   * @param lines The number of lines of the data to draw.
   * @param from_top @c true if the data is drawn from the top, or
   *                 @c false if the data is drawn from the bottom.
   * @returns The composited picture.
   */
  static
  picmap &
  limited_overlay(picmap      &base,
                  char_t       glyphs[],
                  attr_t       attrs[],
                  std::size_t  left,
                  std::size_t  top,
                  std::size_t  width,
                  std::size_t  height,
                  std::size_t  lines,
                  bool         from_top)
  {
    std::size_t right    = width + left;
    std::size_t bottom   = height + top;
    std::size_t bg_width = BACKGROUND_width;
    std::size_t pos      = 0;
    std::size_t i        = 0;
    
    if (lines > 0) {
      if (!from_top) {
        top += lines;
        i   += lines * width;
      } else {
        bottom -= lines;
      }
    }
    
    for (std::size_t y = top; y < bottom; ++y) {
      for (std::size_t x = left; x < right; ++x) {
        pos = x + y * bg_width;
        
        base.at(pos).character = glyphs[i];
        base.at(pos).attribute = attrs[i];
        
        i++;
      }
    }
    
    return base;
  }

  /**
   * @brief Overlay a picture.
   * @param base The base picture to draw on.
   * @param glyphs The picture data to draw.
   * @param attrs The attributes for the data.
   * @param left The left coordinate to draw at.
   * @param top The top coordinate to draw at.
   * @param width The width of the data.
   * @param height The height of the data.
   * @returns The composited picture.
   */
  static
  picmap &
  overlay(picmap      &base,
          char_t       glyphs[],
          attr_t       attrs[],
          std::size_t  left,
          std::size_t  top,
          std::size_t  width,
          std::size_t  height)
  {
    return limited_overlay(base,
                           glyphs,
                           attrs,
                           left,
                           top,
                           width,
                           height,
                           0,
                           false);
  }

  /**
   * @brief Draw the hangman picture.
   * @returns A composited picture.
   */
  static
  picmap &
  hangman(std::size_t lines)
  {
    static picmap base;
    
    base = gallows1(0);
    
    return limited_overlay(base,
                           HANGMAN1_elems,
                           HANGMAN1_attrs,
                           15,
                           6,
                           HANGMAN1_width,
                           HANGMAN1_height,
                           lines,
                           false);
  }

  /**
   * @brief Draw the gallows.
   * @returns A composited picture.
   */
  static
  picmap &
  gallows1(std::size_t lines)
  {
    static picmap base;
    
    base = background();

    return limited_overlay(base,
                           GALLOWS1_elems,
                           GALLOWS1_attrs,
                           4,
                           1,
                           GALLOWS1_width,
                           GALLOWS1_height,
                           lines,
                           false);
  }

  /**
   * @brief draw the victim standing on the gallows.
   * @returns A composited picture.
   */
  static
  picmap &
  victim1(std::size_t lines)
  {
    static picmap base;
    
    base = hangman(0);

    return limited_overlay(base,
                           VICTIM1_elems,
                           VICTIM1_attrs,
                           7,
                           2,
                           VICTIM1_width,
                           VICTIM1_height,
                           lines,
                           true);
  }

  /**
   * @brief Draw the victim swinging from the gallows.
   * @returns A composited picture.
   */
  static
  picmap &
  victim2()
  {
    static picmap base;
    
    base = hangman(0);

    return overlay(base,
                   VICTIM2_elems,
                   VICTIM2_attrs,
                   5,
                   2,
                   VICTIM2_width,
                   VICTIM2_height);
  }

};                                      // class pic_generator

#endif // !_gamepic_hpp_

// gamepic.hpp ends here
