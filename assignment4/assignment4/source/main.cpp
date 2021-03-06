#include <limits>
#include <cstdlib>                      // For EXIT_SUCCESS et al.

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <Windows.h>
#include <tchar.h>

#include "posix.hpp"
#include "game.hpp"

/**
 * @brief Maximum number of guesses.
 *
 * This limit is set because otherwise the graphics subsystem becomes
 * far too complex for this assignment.
 */
const std::size_t gMaxGuesses = 16;

/**
 * @brief Read the number of guesses from the command line.
 * @param str The command line argument.
 * @returns The number of guesses as an unsigned value.
 *
 * This function also ensures that the number of guesses does not
 * overflow the unsigned value.
 */
std::size_t
read_guesses(const TCHAR *str)
{
  std::size_t  val = 0;
  TCHAR       *endptr;

  errno = 0;
  val   = _tcstol(str, &endptr, 10);

  if ((errno == ERANGE)                         &&
      (val == std::numeric_limits<long>::max()  ||
       val == std::numeric_limits<long>::min()) ||
      (errno != 0 && val == 0))
  {
    posix::err(EXIT_NOT_A_NUMBER, _T("Number of guesses is not a number."));
  }

  if (endptr == str) {
    posix::err(EXIT_NOT_A_NUMBER, _T("Number of guesses is not a number."));
  }

  return val > gMaxGuesses ? gMaxGuesses : val;
}

/**
 * @brief Main routine.
 * @param argc Number of arguments.
 * @param argv Array of argument strings.
 *
 * This is a special Windows-only version of main.  It's purpose is to
 * be portable across ASCII, Unicode, and multi-byte character sets.
 *
 * Likewise, TCHAR will either be an ASCII 'char', or a Unicode/MBCS
 * 'wchar_t'.
 */
int
_tmain(int argc, TCHAR *argv[])
{
  // Validate number of arguments.
  if (argc != 3) {
    posix::err(EXIT_NUM_ARGS,
          _T("Not enough arguments:  %s <guesses> <word file>"),
          posix::getprogname());
  }

  // Validate that the filename is valid.
  if (_tcslen(argv[2]) == 0 && _tcslen(argv[2]) >= MAX_PATH) {
    posix::err(EXIT_INVALID_FILENAME,
      _T("Invalid or no file name specified."));
  }

  // Create the game object.
  game theGame(ovision::string_t(argv[1]),
               read_guesses(argv[2]));

  // Enter the game.
  return theGame.run();
}

// EOF
