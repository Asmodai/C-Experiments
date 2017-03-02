//
// char.hpp --- Attributed character class.
//
// Copyright (c) 2014 Paul Ward <asmodai@gmail.com>
//
// Time-stamp: <Friday Apr 18, 2014 00:14:00 asmodai>
// Revision:   6
//
// Author:     Paul Ward <asmodai@gmail.com>
// Maintainer: Paul Ward <asmodai@gmail.com>
// Created:    14 Apr 2014 18:43:55
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
//
// This is a header-only implementation, comments are inline.
//
// }}}

/**
 * @file char.hpp
 * @author Paul Ward
 * @brief Attributed character class.
 */

#pragma once
#ifndef _char_hpp_
#define _char_hpp_

#include <cstddef>
#include <vector>
#include <string>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include "compiler.hpp"
#include "types.hpp"

namespace ovision
{

  /**
   * @brief Attributed character base class.
   * @tparam _Tc The type of the character.
   * @tparam _Ta The type of the attribute.
   *
   * This is the base class for attributed characters, and as such
   * holds the character and attribute elements.  All attributed
   * character classes inherit from this one.
   */
  template <class _Tc, class _Ta>
  struct _Achar_base
  {

    // Public type definitions.
  public:

    /**
     * @typedef _MyT
     * @brief The type of this templatised structure.
     *
     * @typedef character_type
     * @brief The type of the character element.
     *
     * @typedef attribute_type
     * @brief The type of the attribute.
     *
     * @typedef _TcX
     * @brief The type of the character type sans reference.
     *
     * @typedef _TaX
     * @brief The type of the attribute type sans reference.
     */
    typedef _Achar_base<_Tc, _Ta>                     _MyT;
    typedef _Tc                                       character_type;
    typedef _Ta                                       attribute_type;
    typedef typename std::remove_reference<_Tc>::type _TcX;
    typedef typename std::remove_reference<_Ta>::type _TaX;
    

    // Public member fields.
  public:
    
    character_type character;           //!< Character element.
    attribute_type attribute;           //!< Attribute(s).


    // Public member functions.
  public:

    /**
     * @brief Default constructor function.
     */
    _Achar_base()
      : character(character_type()),
        attribute(attribute_type())

    {}

    /**
     * @brief Copy-constructor function.
     * @param _Other The other object to copy.
     */
    _Achar_base(const _Achar_base<_Tc, _Ta> &_Other)
      : character(_Other.character),
        attribute(_Other.attribute)
    {}

    /**
     * @brief Constructor function.
     * @param _char The initial character.
     * @param _attr The initial attribute(s).
     */
    _Achar_base(const character_type &_char,
                const attribute_type &_attr)
      : character(_char),
        attribute(_attr)
    {}

    /**
     * @brief Constructor function.
     * @param _char The initial character.
     * @param _attr The initial attribute.
     */
    _Achar_base(const _TcX &&_char, const _TaX &&_attr)
      : character(std::move(_char)),
        attribute(std::move(_attr))
    {}

    /**
     * @brief Constructor function.
     * @param _char The initial character.
     * @param _attr The initial attribute.
     */
    _Achar_base(const _TcX &&_char, const _TaX &_attr)
      : character(std::move(_char)),
        attribute(_attr)
    {}

    /**
     * @brief Constructor function.
     * @param _char The initial character.
     * @param _attr The initial attribute.
     */
    _Achar_base(const _TcX &_char, const _TaX &&_attr)
      : character(_char),
        attribute(std::move(_attr))
    {}

    /**
     * @brief Constructor function.
     * @tparam _OC The type of the other character value.
     * @tparam _OA The type of the other attribute value.
     * @param _char The initial character.
     * @param _attr The initial attribute.
     */
    template <class _OC, class _OA>
    _Achar_base(_OC &&_char, _OA &&_attr)
      : character(std::forward<_OC>(_char)),
        attribute(std::forward<_OA>(_attr))
    {}
    
  };                                    // struct _Achar_base


  /**
   * @brief Basic attributed character class.
   * @tparam _Tc The character element type.
   * @tparam _Ta The attribute element type.
   */
  template <class _Tc, class _Ta>
  struct basic_attributed_character
    : public _Achar_base<_Tc, _Ta>
  {

    // Public type definitions.
  public:

    /**
     * @typedef _MyBase
     * @brief The base class of this class.
     *
     * @typedef _MyType
     * @brief A convenience type that references the type of this
     *        class.
     *
     * @typedef character_type
     * @brief The type of character element used by this class.
     *
     * @typedef attribute_type
     * @brief The type of attribute element used by this class.
     *
     * @typedef _TcX
     * @brief The type of the character type with any reference removed.
     *
     * @typedef _TaX
     * @brief The type of the attribute type with any reference removed.
     *
     */
    typedef _Achar_base<_Tc, _Ta>                     _MyBase;
    typedef basic_attributed_character<_Tc, _Ta>      _MyType;
    typedef _Tc                                       character_type;
    typedef _Ta                                       attribute_type;
    typedef typename std::remove_reference<_Tc>::type _TcX;
    typedef typename std::remove_reference<_Ta>::type _TaX;
    

    // Public member functions.
  public:

    /**
     * @brief Default constructor function.
     */
    basic_attributed_character()
      : _MyBase()
    {}

    /**
     * @brief Constructor function.
     * @param _char The initial character.
     * @param _attr The initial attribute(s).
     */
    basic_attributed_character(const _Tc &_char, const _Ta &_attr)
      : _MyBase(_char, _attr)
    {}

    /**
     * @brief Copy constructor function.
     * @tparam _OC The type of the other character value.
     * @tparam _OA The type of the other attribute character.
     * @param _Right The other object.
     */
    template <class _OC, class _OA>
    basic_attributed_character(basic_attributed_character<_OC, _OA> &_Right)
      : _MyBase(_Right.character, _Right.attribute)
    {}

    /**
     * @brief Constructor function.
     * @param _char The initial character.
     * @param _attr The initial attribute(s).
     */
    basic_attributed_character(_TcX &&_char, _TaX &&_attr)
      : _MyBase(std::move(_char), std::move(_attr))
    {}

    /**
     * @brief Constructor function.
     * @param _char The initial character.
     * @param _attr The initial attribute(s).
     */
    basic_attributed_character(const _TcX &_char, _TaX &&_attr)
      : _MyBase(_char, std::move(_attr))
    {}

    /**
     * @brief Constructor function.
     * @param _char The initial character.
     * @param _attr The initial attribute(s).
     */
    basic_attributed_character(_TcX &&_char, const _TaX &_attr)
      : _MyBase(std::move(_char), _attr)
    {}

    /**
     * @brief Constructor function.
     * @tparam _OC The type of the other character value.
     * @tparam _OA The type of the other attribute value.
     * @param _char The initial character.
     * @param _attr The initial attribute(s).
     */
    template <class _OC, class _OA>
    basic_attributed_character(_OC &&_char, _OA &&_attr)
      : _MyBase(std::forward<_OC>(_char),
                std::forward<_OA>(_attr))
    {}

    /**
     * @brief Clear the character and attribute values.
     */
    inline
    void
    clear()
    {
      character = __CAST(character_type, 0);
      attribute = __CAST(attribute_type, 0);
    }

    /**
     * @brief Swap the character and attribute values with those of
     *        another instance.
     * @param _Right The instance to swap values with.
     */
    inline
    void
    swap(_MyType &_Right)
    {
      if (this != &_Right) {
        std::swap(this->character, _Right.character);
        std::swap(this->attribute, _Right.attribute);
      }
    }

    /**
     * @brief Swap the character and attribute values with those of
     *        another instance.
     * @param _Right The instance to swap values with.
     */
    inline
    void
    swap(_MyType &&_Right)
    {
      if (this != &_Right) {
        this->character = std::move(_Right.character);
        this->attribute = std::move(_Right.attribute);
      }
    }

    /**
     * @brief Assignment operator.
     * @param _Right The right-hand side of the expression.
     * @returns This instance after assignment of values from the
     *          right-hand side.
     */
    _MyType &
    operator = (const _MyType &_Right)
    {
      this->character = _Right.character;
      this->attribute = _Right.attribute;

      return *this;
    }

    /**
     * @brief Assignment operator.
     * @param _Right The right-hand side of the expression.
     * @returns This instance after assignment of values from the
     *          right-hand side.
     */
    _MyType &
    operator = (_MyType &&_Right)
    {
      this->character = std::move(_Right.character);
      this->attribute = std::move(_Right.attribute);

      return *this;
    }

    /**
     * @brief Addition operator.
     * @param _Right The right-hand side.
     * @returns A new instance containing the results of the operation.
     */
    _MyType
    operator + (const character_type &_Right)
    {
      _MyType _tmp = *this;

      _tmp.character += _Right;

      return _tmp;
    }

    /**
     * @brief Subtraction operator.
     * @param _Right The right-hand side.
     * @returns A new instance containing the results of the operation.
     */
    _MyType
    operator - (const character_type &_Right)
    {
      _MyType _tmp = *this;

      _tmp.character -= _Right;

      return _tmp;
    }

    /**
     * @brief Compound addition operator.
     * @param _Right The right-hand side.
     * @returns This instance after modifying its values.
     */
    _MyType &
    operator += (const character_type &_Right)
    {
      this->character += _Right;

      return *this;
    }

    /**
     * @brief Compound addition operator.
     * @param _Right The right-hand side.
     * @returns This instance after modifying its values.
     */
    _MyType &
    operator -= (const character_type &_Right)
    {
      this->character -= _Right;

      return *this;
    }

  };                                    // class basic_attributed_character

  
  // =================================================================

  
  /**
   * @brief The standard attributed character data type.
   *
   * The attributes are wide enough to cope with the attributes used
   * by both CURSES and the Windows console.
   */
  typedef basic_attributed_character<char_t, std::bitset<16>> achar;

  /**
   * @var fg_intense
   * @brief Intense foreground bit flag.
   *
   * @var fg_red
   * @brief Red foreground bit flag.
   *
   * @var fg_blue
   * @brief Blue foreground bit flag.
   *
   * @var fg_green
   * @brief Green foreground bit flag.
   *
   * @var fg_magenta
   * @brief Magenta foreground bit flag.
   *
   * @var fg_yellow
   * @brief Yellow foreground bit flag.
   *
   * @var fg_cyan
   * @brief Cyan foreground bit flag.
   *
   * @var fg_grey
   * @brief Grey foreground bit flag.
   *
   * @var fg_black
   * @brief Black foreground bit flag.
   *
   * @var fg_white
   * @brief White foreground bit flag.
   */
  const attr_t fg_intense = FOREGROUND_INTENSITY;
  const attr_t fg_red     = FOREGROUND_RED;
  const attr_t fg_blue    = FOREGROUND_BLUE;
  const attr_t fg_green   = FOREGROUND_GREEN;
  const attr_t fg_magenta = fg_red  | fg_blue;
  const attr_t fg_yellow  = fg_red  | fg_green;
  const attr_t fg_cyan    = fg_blue | fg_green;
  const attr_t fg_grey    = fg_red  | fg_blue | fg_green;
  const attr_t fg_black   = 0;
  const attr_t fg_white   = fg_grey | fg_intense;

  /**
   * @var bg_intense
   * @brief Intense background bit flag.
   *
   * @var bg_red
   * @brief Red background bit flag.
   *
   * @var bg_blue
   * @brief Blue background bit flag.
   *
   * @var bg_green
   * @brief Green background bit flag.
   *
   * @var bg_magenta
   * @brief Magenta background bit flag.
   *
   * @var bg_yellow
   * @brief Yellow background bit flag.
   *
   * @var bg_cyan
   * @brief Cyan background bit flag.
   *
   * @var bg_grey
   * @brief Grey background bit flag.
   *
   * @var bg_black
   * @brief Black background bit flag.
   *
   * @var bg_white
   * @brief White background bit flag.
   */
  const attr_t bg_intense = BACKGROUND_INTENSITY;
  const attr_t bg_red     = BACKGROUND_RED;
  const attr_t bg_blue    = BACKGROUND_BLUE;
  const attr_t bg_green   = BACKGROUND_GREEN;
  const attr_t bg_magenta = bg_red  | bg_blue;
  const attr_t bg_yellow  = bg_red  | bg_green;
  const attr_t bg_cyan    = bg_blue | bg_green;
  const attr_t bg_grey    = bg_red  | bg_blue | bg_green;
  const attr_t bg_black   = 0;
  const attr_t bg_white   = bg_grey | bg_intense;

  /**
   * @brief Default attributes, grey text on a black background.
   */
  const attr_t default_attributes = fg_grey | bg_black;

  
  // =================================================================
  

  /**
   * @brief A naive attributed string.
   */
  class astring
    : public std::vector<achar>
  {

    // Public member functions.
  public:


    /**
     * @brief Assignment operator.
     * @param rhs The right-hand side.
     * @returns The original object with modified values.
     */
    astring &
    operator = (const string_t &rhs)
    {
      std::size_t len = rhs.length();
      std::size_t i   = 0;

      reserve(len);
      resize(len);

      for (i = 0; i < len; ++i) {
        at(i) = achar(rhs[i], default_attributes);
      }

      return *this;
    }

    /**
     * @brief Convert the attributed string to a standard string.
     * @returns An @c std::string or @c std::wstring depending on if
     *          the library was compiled with Unicode support.
     */
    string_t
    to_string() const
    {
      std::size_t len = size();
      std::size_t i   = 0;
      string_t    ret;

      ret.reserve(len);
      ret.resize(len);

      for (i = 0; i < len; ++i) {
        ret.assign(i, at(i).character);
      }

      return ret;
    }

    /**
     * @brief Convert a standard string to an attributed string.
     * @param str The string.
     * @param attr The attribute.
     */
    void
    from_string(const string_t &str, attr_t attr)
    {
      std::size_t len = str.length();
      std::size_t i   = 0;

      clear();
      reserve(len);
      resize(len);

      for (i = 0; i < len; ++i) {
        at(i) = achar(str[i], attr);
      }
    }

    /**
     * @brief Return the attributed string length.
     */
    std::vector<achar>::size_type
    length() const
    {
      return size();
    }

  };                                    // class astring

}                                       // namespace ovision

#endif // !_char_hpp_

// char.hpp ends here
