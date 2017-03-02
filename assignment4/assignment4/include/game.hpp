//
// game.hpp --- Main game class.
//
// Copyright (c) 2014 Paul Ward <asmodai@gmail.com>
//
// Time-stamp: <Monday Apr 28, 2014 09:38:28 asmodai>
// Revision:   11
//
// Author:     Paul Ward <asmodai@gmail.com>
// Maintainer: Paul Ward <asmodai@gmail.com>
// Created:    16 Apr 2014 15:29:00
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

// }}}

/**
 * @file game.hpp
 * @author Paul Ward
 * @brief Main game class.
 */

#pragma once
#ifndef _game_hpp_
#define _game_hpp_

#include <cstddef>
#include <map>
#include <array>

#include "picture.hpp"
#include "text.hpp"
#include "application.hpp"

using namespace ovision;

/**
 * @brief Main game class.
 */
class game
{

  // Public types.
public:

  /**
   * @brief A map of guessed characters to integral count.
   */
  typedef std::map<char_t, std::size_t> guess_map;

  /**
   * @brief A vector of unsigneds.
   */
  typedef std::vector<std::size_t>      letter_map;
  

  // Private member fields.
private:

  // Game logic and utility fields.
  std::size_t           mTotalGuesses;  //!< Total guesses.
  std::size_t           mLivesLeft;     //!< Lives remaining.
  string_t              mWordFile;      //!< Word file
  std::vector<string_t> mWordVector;    //!< Vector of words.
  guess_map             mUsedGuesses;   //!< Used guesses.
  letter_map            mWordMap;       //!< Letter positions.
  std::size_t           mWordChosen;    //!< Word chosen.
  astring               mWordBuffer;    //!< Word buffer so far.
  bool                  mGuessedIt;     //!< Word guessed?

  // TUI fields.
  application mApp;                     //!< Application object.
  screen_size mScreenSize;              //!< Screen size.
  frame       mGameFrame;               //!< Main game frame.
  view        mInputView;               //!< 'Input' frame.
  text        mMessageText;             //!< Message text.
  text        mGuessesText;             //!< Guesses text.
  text        mRemainingText;           //!< Lives remaining text.
  text        mStatusText;              //!< Status text.
  text        mWordText;                //!< Word test.
  picture     mGraphic;                 //!< Hanging graphic.


  // Public member functions.
public:

  // Constructor function.
  game(string_t wordFile, std::size_t totalGuesses);

  // Utility functions.
  void read_word_file();
  void random_chooser();
  void reset_guesses();
  void compose_guesses();
  void compose_word_text();
  bool locate_characters(char_t ch);
  
  // Game logic function.
  void game_logic(text   &msgBuffer,
                  text   &guessBuffer,
                  text   &remainingBuffer,
                  text   &wordBuffer,
                  char_t  guess);

  // Execution function.
  int run();
  
};                                      // class game

#endif // !_game_hpp_

// game.hpp ends here
