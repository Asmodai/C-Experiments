//
// game.cpp --- Main game implementation.
//
// Copyright (c) 2014 Paul Ward <asmodai@gmail.com>
//
// Time-stamp: <Friday Apr 25, 2014 09:21:18 asmodai>
// Revision:   7
//
// Author:     Paul Ward <asmodai@gmail.com>
// Maintainer: Paul Ward <asmodai@gmail.com>
// Created:    16 Apr 2014 15:29:10
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
 * @file game.cpp
 * @author Paul Ward
 * @brief Main game implementation.
 */

#include <random>
#include <ctime>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <cctype>
#include <random>

#include "posix.hpp"
#include "gamepic.hpp"
#include "game.hpp"

using namespace ovision;

/**
 * @brief Constructor method.
 * @param wordFile The path of the word file to use.
 * @param totalGuesses The number of guesses per word.
 */
game::game(string_t wordFile, std::size_t totalGuesses)
  : mWordFile(wordFile),
    mTotalGuesses(totalGuesses)
{
  mApp.set_screen_size(screen_size(80, 25));

  mScreenSize = mApp.get_screen_size();
  mGuessedIt  = false;

  read_word_file();
}

/**
 * @brief Read the word file, loading the words.
 */
void
game::read_word_file()
{
  std::ifstream file;
  char          ch;
  string_t      buf;

  // Open the file.
  file.open(mWordFile);

  // If the file isn't open, complain.
  if (!file.is_open()) {
    posix::err(EXIT_FILE_IMAGINARY,
      _T("File \"%s\" could not be opened."),
      mWordFile.c_str());
  }

  // Otherwise, iterate over the file reading each line.
  while (!file.eof()) {
    do {
      file.get(ch);

      buf += std::toupper(ch);
    } while (ch != '\n' && !file.eof());
    buf[buf.length() - 1] = L'\0';

    // If the word is valid, store it in the vector.
    if (buf.length() > 0 && buf[0] != L'\0') {
      mWordVector.push_back(buf);
    }

    buf.clear();
  }

  // If the vector is empty, complain.
  if (mWordVector.size() == 0) {
    posix::err(EXIT_NO_WORDS,
      _T("The word file contains no words."));
  }
}

/**
 * @brief Choose a random word.
 *
 * Depending on the quality of the Standard C++ Library, this function
 * might be using a non-deterministic random number generator based on
 * hardware entropy, or it might be using a pseudo random number
 * generator.
 *
 * The value from the random number generator is then fed into a
 * uniform integer distribution post-processor, which will produce
 * values @f$i@f$ uniformly distributed on the closed interval
 * @f$[a,b]@f$, that is, distributed according to the discrete
 * probability function @f$P(i|a,b)=\frac{1}{b-a+1}@f$.
 */
void
game::random_chooser()
{
  std::size_t                                vecSize = mWordVector.size();
  std::random_device                         rd;
  std::uniform_int_distribution<std::size_t> dist(vecSize);
  std::size_t                                rnd     = dist(rd);

  if (rnd > mWordVector.size()) {
    rnd %= vecSize;
  }

  mWordChosen = rnd;

  mWordMap.clear();
  mWordMap.reserve(mWordVector[mWordChosen].length() - 1);
  mWordMap.assign(mWordVector[mWordChosen].length() - 1, 0);
}

/**
 * @brief Reset the guess data.
 */
void
game::reset_guesses()
{
  for (char_t c = 'A'; c < 'Z'; ++c) {
    mUsedGuesses[c] = 0;
  }

  mLivesLeft = mTotalGuesses;
  mGuessedIt = false;
}

/**
 * @brief Compose the guess indicator string.
 */
void
game::compose_guesses()
{
#if defined(OVISION_UNICODE)
  std::wstringstream str;
#else
  std::stringstream  str;
#endif

  if (mLivesLeft == 0) {
    str << "You have used up all your guesses.";
  } else {
    str << mLivesLeft << " incorrect "
        << (mLivesLeft == 1 ? "guess" : "guesses")
        << " remaining.";
  }

  mRemainingText.set_text(str.str());
}

/**
 * @brief Compose the text field that displays the word to guess.
 */
void
game::compose_word_text()
{
  std::size_t buflen = (mWordVector[mWordChosen].size() - 1) * 2;

  // Reserve a large-enough area for the string.
  if ((mWordBuffer.size() / 2) != buflen) {
    mWordBuffer.reserve(buflen);
  }

  // Clear the string.
  mWordBuffer.clear();
  mWordBuffer.assign(buflen - 1,
                     achar(L' ', fg_white | bg_blue));

  // Build the string.
  for (std::size_t i = 0; i < mWordBuffer.size(); ++i) {
    if (i % 2 == 0) {
      if (mWordMap.size() > 0 && mWordMap[i / 2] > 0) {
        mWordBuffer[i] = achar(mWordVector[mWordChosen][i / 2],
                               fg_white | fg_intense | bg_blue);
      } else {
        mWordBuffer[i] = achar(L'_', fg_white | fg_intense | bg_blue);
      }
    }
  }

  // Set the text view's contents.
  mWordText.set_text(mWordBuffer);
}

/**
 * @brief Locate the users guessed letter within the word.
 * @param ch The users guess.
 * @returns @c true if the letter was found; otherwise @c false is
 *          returned.
 */
bool
game::locate_characters(char_t ch)
{
  bool        valid = false;
  std::size_t len   = mWordVector[mWordChosen].length();
  std::size_t i     = 0;

  for (i = 0; i < len; ++i) {
    if (mWordVector[mWordChosen][i] == ch) {
      valid       = true;
      mWordMap[i] = 1;
    }
  }

  // Here be lamda.
  if (std::all_of(mWordMap.begin(),
                  mWordMap.end(),
                  [](std::size_t val) {
                    return val == 1;
                  }))
  {
    mGuessedIt = true;
  }

  return valid;
}

/**
 * @brief Game logic callback function.
 * @param msgBuffer Buffer used for messages.
 * @param guessBuffer Buffer used for guess status.
 * @param remainingBuffer Buffer used for guesses remaining.
 * @param wordBuffer Buffer used for the word to guess.
 * @param guess The users guess.
 */
void
game::game_logic(text   &msgBuffer,
                 text   &guessBuffer,
                 text   &remainingBuffer,
                 text   &wordBuffer,
                 char_t  guess)
{
  msgBuffer.set_text(L"");

  // Do something based on the following logic:
  if (mUsedGuesses[guess] > 0) {        // Have we used this guess before?
    // Yes, increment guess count and lose a life.
    mUsedGuesses[guess]++;
    mLivesLeft--;

    mGraphic.set_picmap(pic_generator::compute_picmap(mLivesLeft,
      mTotalGuesses));

    msgBuffer.set_attribute(fg_red | fg_intense | bg_blue);
    msgBuffer.set_text(L"Uh oh, you have already tried that letter!");
  } else if (locate_characters(guess)) { // Have we guessed correctly?
    // Yes, increment guess count and show success.
    mUsedGuesses[guess]++;

    msgBuffer.set_attribute(fg_green | fg_intense | bg_blue);
    msgBuffer.set_text(L"You have found one!");
    guessBuffer.append(guess, fg_green | fg_intense);
  } else {                              // Everything else...
    // ... simply assume the user guessed wrongly and increment the guess
    // count and lose a life.
    mUsedGuesses[guess]++;
    mLivesLeft--;

    mGraphic.set_picmap(pic_generator::compute_picmap(mLivesLeft,
      mTotalGuesses));

    msgBuffer.set_attribute(fg_red | fg_intense | bg_blue);
    msgBuffer.set_text(L"Sorry, that was an incorrect guess!");
    guessBuffer.append(guess, fg_red | fg_intense);
  }

  compose_guesses();
  compose_word_text();
  
  if (mLivesLeft == 0) {                // Have we used all our lives?
    // Yes.  Hang the victim until he is dead.
#if defined(OVISION_UNICODE)
    std::wstringstream str;
#else
    std::stringstream  str;
#endif

    str << L"The word was: " << mWordVector[mWordChosen];

    mGameFrame.set_client_attribute(fg_white | fg_intense | bg_red);
    mGameFrame.set_inner_attribute(fg_white | fg_intense | bg_red);

    wordBuffer.set_attribute(fg_yellow | fg_intense | bg_red);
    wordBuffer.set_text(str.str());

    mGraphic.set_picmap(pic_generator::compute_picmap(0,
      mTotalGuesses));

    msgBuffer.set_attribute(fg_yellow | fg_intense | bg_red);
    msgBuffer.set_text(L"HARD LUCK - GAME OVER!  New game? (Y/N)");
    
    return;
  } else if (mGuessedIt) {              // or have we guessed the word?
    // Yes, inform the user of their success.
    msgBuffer.set_attribute(fg_green | fg_intense | bg_blue);
    msgBuffer.set_text(L"WELL DONE - You got it right!  New game? (Y/N)");

    return;
  }
}                                       // game_logic

/**
 * @brief Run the game.
 * @returns The application exit value.
 */
int
game::run()
{
#if defined(OVISION_UNICODE)
  std::wstringstream wordsLoaded;
#else
  std::stringstream  wordsLoaded;
#endif

  // Set up the UI components.
  mGameFrame = frame(rect(screen_point(0, 0),
                          screen_size(mScreenSize.width,
                                      mScreenSize.height - 7)));
  
  mInputView = view(rect(screen_point(0, 18),
                         screen_size(mScreenSize.width,
                                     7)),
                    fg_white | bg_black | fg_intense,
                    fg_grey | bg_black);

  mMessageText = text(L"Welcome to HANGMAN.  Press CONTROL+C to quit.",
                      screen_point(1, 16),
                      mApp.get_screen_size().width - 1,
                      AlignCenter,
                      fg_yellow | fg_intense | bg_blue);

  mGuessesText = text(L"Guesses: ",
                      screen_point(2, 20),
                      fg_grey | bg_black);

  mWordText = text(L"",
                   screen_point(28, 9),
                   mApp.get_screen_size().width - 31,
                   AlignCenter,
                   fg_green | fg_intense | bg_blue);

  mRemainingText = text(L"",
                        screen_point(2, 22),
                        fg_grey | bg_black);

  mGraphic = picture(rect(5, 3, 24, 12));

  wordsLoaded << mWordVector.size()
               << " word" << (mWordVector.size() == 1 ? "" : "s")
               << " loaded, "
    << mTotalGuesses << " incorrect guesses per game.";

  mStatusText = text(wordsLoaded.str(),
                     screen_point(2, 23),
                     fg_grey | bg_black);

  mApp.set_title(L"Hangman");
  mApp.disable_cursor();  

  mGameFrame.set_title(string_t(_T("Super Hangman : Intel 8086 Edition")));

  mGraphic.set_picmap(pic_generator::compute_picmap(mTotalGuesses,
                                                    mTotalGuesses));

  // Initialise game logic.
  reset_guesses();
  random_chooser();
  compose_word_text();

  // Manage the UI components.
  mApp.add_view(mGameFrame);
  mApp.add_view(mInputView);
  mApp.add_view(mMessageText);
  mApp.add_view(mStatusText);
  mApp.add_view(mGuessesText);
  mApp.add_view(mRemainingText);
  mApp.add_view(mWordText);
  mApp.add_view(mGraphic);

  // Set up the keypress callback to call our game logic.  We do this with a
  // lamnda function
  mApp.add_key_callback(
      [this](char_t ch)
      {
        if (mLivesLeft > 0 && !mGuessedIt && // We have lives left and NOT
            ((ch >= 'a' && ch <= 'z')     || // guessed the word and the guess
             (ch >= 'A' && ch <= 'Z')))      // letter is valid.
        {
          // Process the user's guess.
          ch = (char_t)std::toupper(ch);
          game_logic(mMessageText,
                     mGuessesText,
                     mRemainingText,
                     mWordText,
                     ch);
        } else {                        // Some other event.
          // At this point, we simply assume the user is being prompted with
          // some Y/N prompt.
          if (ch == 'y' || ch == 'Y') { // Has the Y key been pressed?
            // Yes. Set up for a new game.
            reset_guesses();
            
            mLivesLeft = mTotalGuesses;
            
            random_chooser();
            
            mGameFrame.set_client_attribute(fg_white | fg_intense | bg_blue);
            
            mGameFrame.set_inner_attribute(fg_white | fg_intense | bg_blue);

            mGuessesText.set_attribute(fg_grey | bg_black);
            mGuessesText.set_text(L"Guesses: ");
            mWordText.set_text(L"");
            
            mMessageText.set_attribute(fg_yellow | fg_intense | bg_blue);
            
            mMessageText.set_text(
                L"A new word has been chosen, start guessing!");
            
            mGraphic.set_picmap( pic_generator::compute_picmap(mTotalGuesses,
                                                               mTotalGuesses));
                              
            compose_guesses();
            compose_word_text();
          } else if (ch == 'n' || ch == 'N') { // Has the N key been pressed?
            // Stop the application and exit.
            mApp.stop();
          }
        }
      });                               // lambda
  
  // Start the application.
  return mApp.start();
}                                       // run

// game.cpp ends here
