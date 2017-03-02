//
// size.hpp --- Geometric size class.
//
// Copyright (c) 2014 Paul Ward <asmodai@gmail.com>
//
// Time-stamp: <Friday Apr 18, 2014 00:27:20 asmodai>
// Revision:   11
//
// Author:     Paul Ward <asmodai@gmail.com>
// Maintainer: Paul Ward <asmodai@gmail.com>
// Created:    12 Apr 2014 07:33:12
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
//
// This is a header-only implementation, comments are inline.
//
// }}}

/**
 * @file size.hpp
 * @author Paul Ward
 * @brief Geometric size class.
 */

#pragma once
#ifndef _size_hpp_
#define _size_hpp_

#include "point.hpp"

namespace ovision
{

  /**
   * @brief Base size class.
   * @tparam _Ty The type of the width and height members.
   *
   * This class acts as a 'plain old data' class for future @em size
   * types.  It is responsible for containing the data (coordinates,
   * in this case), and the constructors to build the data.
   *
   * If a more advanced or extended size type is required,
   * @c _Size_base can be derived.
   */
  template <class _Ty>
  struct _Size_base
  {

    // Public type definitions.
  public:

    /**
     * @typedef _MyT
     * @brief The type of the base class.
     *
     * @typedef value_type
     * @brief The type of the width and height values.
     *
     * @typedef _TyX
     * @brief Type of the value type sans reference.
     */
    typedef _Size_base<_Ty>                     _MyT;
    typedef _Ty                                 value_type;
    typedef typename std::remove_reference<_Ty> _TyX;

    
    // Public member fields.
  public:

    _Ty width;                          //!< Width.
    _Ty height;                         //!< Height.

    
    // Public member functions.
  public:

    /**
     * @brief Default constructor function.
     */
    _Size_base()
      : width(_Ty()),
        height(_Ty())
    {}

    /**
     * @brief Copy constructor function.
     * @param _Other The object to copy.
     */
    _Size_base(const _Size_base<_Ty> &_Other)
      : width(_Other.width),
        height(_Other.height)
    {}

    /**
     * @brief Constructor function.
     * @param _Width The initial width.
     * @param _Height The initial height.
     */
    _Size_base(const _Ty &_Width, const _Ty &_Height)
      : width(_Width),
        height(_Height)
    {}

    /**
     * @brief Constructor function.
     * @param _Width The initial width.
     * @param _Height The initial height.
     */
    _Size_base(_TyX &&_Width, _TyX &&_Height)
      : width(std::move(_Width)),
        height(std::move(_Height))
    {}

    /**
     * @brief Constructor function.
     * @param _Width The initial width.
     * @param _Height The initial height.
     */
    _Size_base(const _TyX &_Width, const _TyX &&_Height)
      : width(_Width),
        height(std::move(_Height))
    {}

    /**
     * @brief Constructor function.
     * @param _Width The initial width.
     * @param _Height The initial height.
     */
    _Size_base(const _TyX &&_Width, const _TyX &_Height)
      : width(std::move(_Width)),
        height(_Height)
    {}

    /**
     * @brief Constructor function.
     * @tparam _OW The type of the width value.
     * @tparam _OH The type of the height value.
     * @param _Width The initial width.
     * @param _Height The initial height.
     */
    template <class _OW, class _OH>
    _Size_base(_OW &&_Width, _OH &&_Height)
      : width(std::forward<_OW>(_Width)),
        height(std::forward<_OH>(_Height))
    {}
    
  };                                    // struct _Size_base

  
  /**
   * @brief Basic size class.
   * @tparam _Ty The type of the width/height values.
   *
   * This is the base class for basic @em size data.  It derives from
   * the @c _Size_base structure (which is a POD structure), but has
   * the actual utility methods that make sense for a size.
   */
  template <class _Ty>
  struct basic_size
    : public _Size_base<_Ty>
  {

    // Public type definitions.
  public:

    /**
     * @typedef _MyBase
     * @brief Type of the base class for this class.
     *
     * @typedef _MyType
     * @brief Convenience type for the type of this class.
     *
     * @typedef value_type
     * @brief Type of the height/width values.
     *
     * @typedef _TyX
     * @brief Type of the value type sans reference.
     */
    typedef _Size_base<_Ty>                           _MyBase;
    typedef basic_size<_Ty>                           _MyType;
    typedef _Ty                                       value_type;
    typedef typename std::remove_reference<_Ty>::type _TyX;

    
    // Public member functions.
  public:

    /**
     * @brief Default constructor function.
     */
    basic_size()
      : _MyBase()
    {}

    /**
     * @brief Constructor function
     * @param _Width The initial width.
     * @param _Height The initial width.
     */
    basic_size(const _Ty &_Width, const _Ty &_Height)
      : _MyBase(_Width, _Height)
    {}

    /**
     * @brief Copy constructor function
     * @tparam _Other the type of the object to copy from.
     * @param _Right The other object.
     */
    template <class _Other>
    basic_size(basic_size<_Other> &_Right)
      : _MyBase(_Right.width, _Right.height)
    {}

    /**
     * @brief Constructor function
     * @param _Width The initial width.
     * @param _Height The initial width.
     */
    basic_size(_TyX &&_Width, _TyX &&_Height)
      : _MyBase(std::move(_Width), std::move(_Height))
    {}

    /**
     * @brief Constructor function
     * @param _Width The initial width.
     * @param _Height The initial width.
     */
    basic_size(const _TyX &_Width, _TyX &&_Height)
      : _MyBase(_Width, std::move(_Height))
    {}

    /**
     * @brief Constructor function
     * @param _Width The initial width.
     * @param _Height The initial width.
     */
    basic_size(_TyX &&_Width, const  _TyX &_Height)
      : _MyBase(std::move(_Width), _Height)
    {}

    /**
     * @brief Constructor function
     * @tparam _Other The type of the other object.
     * @param _Width The initial width.
     * @param _Height The initial width.
     */
    template <class _Other>
    basic_size(_Other &&_Width, _Other &&_Height)
      : _MyBase(std::forward<_Other>(_Width),
                std::forward<_Other>(_Height))
    {}

    /**
     * @brief Clear the width and height values.
     */
    inline
    void
    clear()
    {
      width = 0;
      height = 0;
    }

    /**
     * @brief Convert the size to a linear offset.
     * @returns A standard size value representing the offset.
     *
     * This function converts a 2D coordinate to a 1D offset.  This is
     * designed to allow us to represent a 2D buffer as a 1D array,
     * with this function computing the offset of the coordinate into
     * the 1D array for us.
     *
     * Any offset computed from a @c basic_size object ought to be
     * added to an origin point (such as a @c basic_point) for it to
     * make sense.
     */
    inline
    std::size_t
    offset() const
    {
      return width * height;
    }

    /**
     * @brief Swap the values with that of another instance.
     * @param _Right The other object.
     */
    inline
    void
    swap(_MyType &_Right)
    {
      if (this != &_Right) {
        std::swap(this->width, _Right.width);
        std::swap(this->height, _Right.height);
      }
    }

    /**
     * @brief Swap the values with that of another instance.
     * @param _Right The other object.
     */
    inline
    void
    swap(_MyType &&_Right)
    {
      if (this != &_Right) {
        this->width = std::move(_Right.width);
        this->height = std::move(_Right.height);
      }
    }

    /**
     * @brief Assignment operator.
     * @param _Right The right-hand side.
     * @returns This instance with values assigned.
     */
    _MyType &
    operator = (const _MyType &_Right)
    {
      this->width = _Right.width;
      this->height = _Right.height;
      
      return *this;
    }

    /**
     * @brief Assignment operator.
     * @param _Right The right-hand side.
     * @returns This instance with values assigned.
     */
    _MyType &
    operator = (_MyType &&_Right)
    {
      this->width = std::move(_Right.width);
      this->height = std::move(_Right.height);

      return *this;
    }

    /**
     * @brief Addition operator.
     * @param _Right The right-hand side.
     * @returns Returns a new object containing the result of the
     *          operation.
     */
    _MyType
    operator + (const value_type &_Right)
    {
      _MyType _tmp = *this;

      _tmp.width  += _Right;
      _tmp.height += _Right;

      return _tmp;
    }

    /**
     * @brief Subtraction operator.
     * @param _Right The right-hand side.
     * @returns Returns a new object containing the result of the
     *          operation.
     */
    _MyType
    operator - (const value_type &_Right)
    {
      _MyType _tmp = *this;

      _tmp.width  -= _Right;
      _tmp.height -= _Right;

      return _tmp;
    }

    /**
     * @brief Multiplication operator.
     * @param _Right The right-hand side.
     * @returns Returns a new object containing the result of the
     *          operation.
     */
    _MyType
    operator * (const value_type &_Right)
    {
      _MyType _tmp = *this;

      _tmp.width  *= _Right;
      _tmp.height *= _Right;

      return _tmp;
    }

    /**
     * @brief Division operator.
     * @param _Right The right-hand side.
     * @returns Returns a new object containing the result of the
     *          operation.
     */
    _MyType
    operator / (const value_type &_Right)
    {
      _MyType _tmp = *this;

      _tmp.width  /= _Right;
      _tmp.height /= _Right;

      return _tmp;
    }

    /**
     * @brief Addition operator.
     * @param _Right The right-hand side.
     * @returns Returns a new object containing the result of the
     *          operation.
     */
    _MyType
    operator + (const _MyType &_Right)
    {
      _MyType _tmp = *this;

      _tmp.width  += _Right.width;
      _tmp.height += _Right.height;

      return _tmp;
    }

    /**
     * @brief Subtraction operator.
     * @param _Right The right-hand side.
     * @returns Returns a new object containing the result of the
     *          operation.
     */
    _MyType
    operator - (const _MyType &_Right)
    {
      _MyType _tmp = *this;

      _tmp.width  -= _Right.width;
      _tmp.height -= _Right.height;

      return _tmp;
    }

    /**
     * @brief Multiplication operator.
     * @param _Right The right-hand side.
     * @returns Returns a new object containing the result of the
     *          operation.
     */
    _MyType
    operator * (const _MyType &_Right)
    {
      _MyType _tmp = *this;

      _tmp.width  *= _Right.width;
      _tmp.height *= _Right.height;

      return _tmp;
    }

    /**
     * @brief Division operator.
     * @param _Right The right-hand side.
     * @returns Returns a new object containing the result of the
     *          operation.
     */
    _MyType
    operator / (const _MyType &_Right)
    {
      _MyType _tmp = *this;

      _tmp.width  /= _Right.width;
      _tmp.height /= _Right.height;

      return _tmp;
    }

    /**
     * @brief Compound addition operator.
     * @param _Right The right-hand side.
     * @returns Returns this object after applying the operation.
     */
    _MyType &
    operator += (const _MyType &_Right)
    {
      this->width  += _Right.width;
      this->height += _Right.height;

      return *this;
    }

    /**
     * @brief Compound subtraction operator.
     * @param _Right The right-hand side.
     * @returns Returns this object after applying the operation.
     */
    _MyType &
    operator -= (const _MyType &_Right)
    {
      this->width  -= _Right.width;
      this->height -= _Right.height;

      return *this;
    }

    /**
     * @brief Compound multiplication operator.
     * @param _Right The right-hand side.
     * @returns Returns this object after applying the operation.
     */
    _MyType &
    operator *= (const _MyType &_Right)
    {
      this->width  *= _Right.width;
      this->height *= _Right.height;

      return *this;
    }

    /**
     * @brief Compound division operator.
     * @param _Right The right-hand side.
     * @returns Returns this object after applying the operation.
     */
    _MyType &
    operator /= (const _MyType &_Right)
    {
      this->width  /= _Right.width;
      this->height /= _Right.height;

      return *this;
    }

    /**
     * @brief Compound addition operator.
     * @param _Right The right-hand side.
     * @returns Returns this object after applying the operation.
     */
    _MyType &
    operator += (const value_type &_Right)
    {
      this->width  += _Right;
      this->height += _Right;

      return *this;
    }

    /**
     * @brief Compound subtraction operator.
     * @param _Right The right-hand side.
     * @returns Returns this object after applying the operation.
     */
    _MyType &
    operator -= (const value_type &_Right)
    {
      this->width  -= _Right;
      this->height -= _Right;

      return *this;
    }

    /**
     * @brief Compound multiplication operator.
     * @param _Right The right-hand side.
     * @returns Returns this object after applying the operation.
     */
    _MyType &
    operator *= (const value_type &_Right)
    {
      this->width  *= _Right;
      this->height *= _Right;

      return *this;
    }

    /**
     * @brief Compound division operator.
     * @param _Right The right-hand side.
     * @returns Returns this object after applying the operation.
     */
    _MyType &
    operator /= (const value_type &_Right)
    {
      this->width  /= _Right;
      this->height /= _Right;
      
      return *this;
    }

    /**
     * @brief Lesser-than operator.
     * @param _Right The right-hand side.
     * @returns @c true if the object is lesser than the right-hand
     *          side; otherwise @c false is returned.
     */
    bool
    operator < (const _MyType &_Right)
    {
      return (this->width < _Right.width || this->height < _Right.height);
    }

    /**
     * @brief Greater-than operator.
     * @param _Right The right-hand side.
     * @returns @c true if the object is greater than the right-hand
     *          side; otherwise @c false is returned.
     */
    bool
    operator > (const _MyType &_Right)
    {
      return (this->width > _Right.width || this->height > _Right.height);
    }

    /**
     * @brief Lesser-than-or-equal-to operator.
     * @param _Right The right-hand side.
     * @returns @c true if the object is lesser than or equal to the
     *          right-hand side; otherwise @c false is returned.
     */
    bool
    operator <= (const _MyType &_Right)
    {
      return (this->width <= _Right.width || this->height <= _Right.height);
    }

    /**
     * @brief Greater-than-or-equal-to operator.
     * @param _Right The right-hand side.
     * @returns @c true if the object is greater than or equal to the
     *          right-hand side; otherwise @c false is returned.
     */
    bool
    operator >= (const _MyType &_Right)
    {
      return (this->width >= _Right.width || this->height >= _Right.height);
    }

    /**
     * @brief Equality operator.
     * @param _Left The left-hand side.
     * @param _Right The right-hand side.
     * @returns @c true if both sides are equal; otherwise @c false is
     *          returned.
     */
    friend
    bool
    operator == (const _MyType &_Left, const _MyType &_Right)
    {
      return (_Left.width == _Right.width && _Left.height == _Right.height);
    }

    /**
     * @brief Inequality operator.
     * @param _Left The left-hand side.
     * @param _Right The right-hand side.
     * @returns @c true if both sides are inequal; otherwise @c false is
     *          returned.
     */
    friend
    bool
    operator != (const _MyType &_Left, const _MyType &_Right)
    {
      return !(_Left == _Right);
    }


    /**
     * @brief Addition operation.
     * @tparam _PT The type of the point object.
     * @param _Left The left-hand side.
     * @param _Right The right-hand side.
     * @returns A new object that contains the result of the
     *          operation.
     */
    template <typename _PT>
    friend
    basic_point<_PT>
    operator + (basic_point<_PT> &_Left, const _MyType &_Right)
    {
      return _MyBase(_Left.x + __CAST(basic_point<_PT>::value_type,
                                      _Right.width),
                     _Left.y + __CAST(basic_point<_PT>::value_type,
                                      _Right.height));
    }

    /**
     * @brief Subtraction operation.
     * @tparam _PT The type of the point object.
     * @param _Left The left-hand side.
     * @param _Right The right-hand side.
     * @returns A new object that contains the result of the
     *          operation.
     */
    template <typename _PT>
    friend
    basic_point<_PT>
    operator - (basic_point<_PT> &_Left, const _MyType &_Right)
    {
      return _MyBase(_Left.x - __CAST(basic_point<_PT>::value_type,
                                      _Right.width),
                     _Left.y - __CAST(basic_point<_PT>::value_type,
                                      _Right.height));
    }

    /**
     * @brief Multiplication operation.
     * @tparam _PT The type of the point object.
     * @param _Left The left-hand side.
     * @param _Right The right-hand side.
     * @returns A new object that contains the result of the
     *          operation.
     */
    template <typename _PT>
    friend
    basic_point<_PT>
    operator * (basic_point<_PT> &_Left, const _MyType &_Right)
    {
      return _MyBase(_Left.x * __CAST(basic_point<_PT>::value_type,
                                      _Right.width),
                     _Left.y * __CAST(basic_point<_PT>::value_type,
                                      _Right.height));
    }

    /**
     * @brief Division operation.
     * @tparam _PT The type of the point object.
     * @param _Left The left-hand side.
     * @param _Right The right-hand side.
     * @returns A new object that contains the result of the
     *          operation.
     */
    template <typename _PT>
    friend
    basic_point<_PT>
    operator / (basic_point<_PT> &_Left, const _MyType &_Right)
    {
      return _MyBase(_Left.x / __CAST(basic_point<_PT>::value_type,
                                      _Right.width),
                     _Left.y / __CAST(basic_point<_PT>::value_type,
                                      _Right.height));
    }

    /**
     * @brief Compound addition operation.
     * @tparam _PT The type of the point object.
     * @param _Left The left-hand side.
     * @param _Right The right-hand side.
     * @returns The object after the operation has taken place.
     */
    template <typename _PT>
    friend
    basic_point<_PT>
    operator += (basic_point<_PT> &_Left, const _MyType &_Right)
    {
      return _Left += _Right;
    }

    /**
     * @brief Compound subtraction operation.
     * @tparam _PT The type of the point object.
     * @param _Left The left-hand side.
     * @param _Right The right-hand side.
     * @returns The object after the operation has taken place.
     */
    template <typename _PT>
    friend
    basic_point<_PT>
    operator -= (basic_point<_PT> &_Left, const _MyType &_Right)
    {
      return _Left -= _Right;
    }

    /**
     * @brief Compound multiplication operation.
     * @tparam _PT The type of the point object.
     * @param _Left The left-hand side.
     * @param _Right The right-hand side.
     * @returns The object after the operation has taken place.
     */
    template <typename _PT>
    friend
    basic_point<_PT>
    operator *= (basic_point<_PT> &_Left, const _MyType &_Right)
    {
      return _Left *= _Right;
    }

    /**
     * @brief Compound division operation.
     * @tparam _PT The type of the point object.
     * @param _Left The left-hand side.
     * @param _Right The right-hand side.
     * @returns The object after the operation has taken place.
     */
    template <typename _PT>
    friend
    basic_point<_PT>
    operator /= (basic_point<_PT> &_Left, const _MyType &_Right)
    {
      return _Left /= _Right;
    }

    /**
     * @brief Addition operation.
     * @tparam _PT The type of the point object.
     * @param _Left The left-hand side.
     * @param _Right The right-hand side.
     * @returns A new object that contains the result of the
     *          operation.
     */
    template <typename _PT>
    friend
    basic_point<_PT>
    operator + (_MyType &_Left, const basic_point<_PT> &_Right)
    {
      return _MyType(_Left.width + __CAST(value_type, _Right.x),
                     _Left.height + __CAST(value_type, _Right.y));
    }

    /**
     * @brief Subtraction operation.
     * @tparam _PT The type of the point object.
     * @param _Left The left-hand side.
     * @param _Right The right-hand side.
     * @returns A new object that contains the result of the
     *          operation.
     */
    template <typename _PT>
    friend
    basic_point<_PT>
    operator - (_MyType &_Left, const basic_point<_PT> &_Right)
    {
      return _MyType(_Left.width - __CAST(value_type, _Right.x),
                     _Left.height - __CAST(value_type, _Right.y));
    }

    /**
     * @brief Multiplication operation.
     * @tparam _PT The type of the point object.
     * @param _Left The left-hand side.
     * @param _Right The right-hand side.
     * @returns A new object that contains the result of the
     *          operation.
     */
    template <typename _PT>
    friend
    basic_point<_PT>
    operator * (_MyType &_Left, const basic_point<_PT> &_Right)
    {
      return _MyType(_Left.width * __CAST(value_type, _Right.x),
                     _Left.height * __CAST(value_type, _Right.y));
    }

    /**
     * @brief Division operation.
     * @tparam _PT The type of the point object.
     * @param _Left The left-hand side.
     * @param _Right The right-hand side.
     * @returns A new object that contains the result of the
     *          operation.
     */
    template <typename _PT>
    friend
    basic_point<_PT>
    operator / (_MyType &_Left, const basic_point<_PT> &_Right)
    {
      return _MyType(_Left.width / __CAST(value_type, _Right.x),
                     _Left.height / __CAST(value_type, _Right.y));
    }

    /**
     * @brief Compound addition operation.
     * @tparam _PT The type of the point object.
     * @param _Left The left-hand side.
     * @param _Right The right-hand side.
     * @returns The object after the operation has taken place.
     */
    template <typename _PT>
    friend
    basic_point<_PT>
    operator += (_MyType &_Left, const basic_point<_PT> &_Right)
    {
      return _Left += _Right;
    }

    /**
     * @brief Compound subtraction operation.
     * @tparam _PT The type of the point object.
     * @param _Left The left-hand side.
     * @param _Right The right-hand side.
     * @returns The object after the operation has taken place.
     */
    template <typename _PT>
    friend
    basic_point<_PT>
    operator -= (_MyType &_Left, const basic_point<_PT> &_Right)
    {
      return _Left -= _Right;
    }

    /**
     * @brief Compound multiplication operation.
     * @tparam _PT The type of the point object.
     * @param _Left The left-hand side.
     * @param _Right The right-hand side.
     * @returns The object after the operation has taken place.
     */
    template <typename _PT>
    friend
    basic_point<_PT>
    operator *= (_MyType &_Left, const basic_point<_PT> &_Right)
    {
      return _Left *= _Right;
    }

    /**
     * @brief Compound division operation.
     * @tparam _PT The type of the point object.
     * @param _Left The left-hand side.
     * @param _Right The right-hand side.
     * @returns The object after the operation has taken place.
     */
    template <typename _PT>
    friend
    basic_point<_PT>
    operator /= (_MyType &_Left, const basic_point<_PT> &_Right)
    {
      return _Left /= _Right;
    }
     
  };                                    // struct basic_size

  
  // =================================================================
  

  /**
   * @brief Make a size.
   * @tparam _Ty The type of the size values.
   * @param _Width The width value.
   * @param _Height The height value.
   * @returns A new instance of @c size with the given values.
   */
  template <class _Ty>
  inline
  basic_size<typename std::remove_reference<_Ty>::type>
  make_size(_Ty &&_Width, _Ty &&_Height)
  {
    typedef basic_size<typename std::remove_reference<_Ty>::type> _MySize;

    return _MySize(std::forward<_Ty>(_Width),
                   std::forward<_Ty>(_Height));
  }

  /**
   * @brief Make a size.
   * @tparam _Ty The type of the size values.
   * @param _Width The width value.
   * @param _Height The height value.
   * @returns A new instance of @c size with the given values.
   */
  template <class _Ty>
  inline
  basic_size<typename std::remove_reference<_Ty>::type>
  make_size(_Ty &&_Width, const _Ty &_Height)
  {
    typedef basic_size<typename std::remove_reference<_Ty>::type> _MySize;

    return _MySize((typename std::remove_reference<_Ty>::type)_Width,
                   std::forward<_Ty>(_Height));
  }

  /**
   * @brief Make a size.
   * @tparam _Ty The type of the size values.
   * @param _Width The width value.
   * @param _Height The height value.
   * @returns A new instance of @c size with the given values.
   */
  template <class _Ty>
  inline
  basic_size<typename std::remove_reference<_Ty>::type>
  make_size(const _Ty &_Width, _Ty &&_Height)
  {
    typedef basic_size<typename std::remove_reference<_Ty>::type> _MySize;

    return _MySize(std::forward<_Ty>(_Width),
                   (typename std::remove_reference<_Ty>::type)_Height);
  }

  /**
   * @brief Make a size.
   * @tparam _Ty The type of the size values.
   * @param _Width The width value.
   * @param _Height The height value.
   * @returns A new instance of @c size with the given values.
   */
  template <class _Ty>
  inline
  basic_size<typename std::remove_reference<_Ty>::type>
  make_size(const _Ty &_Width, const _Ty &_Height)
  {
    typedef basic_size<typename std::remove_reference<_Ty>::type> _MySize;

    return _MySize((typename std::remove_reference<_Ty>::type)_Width,
                   (typename std::remove_reference<_Ty>::type)_Height);
  }

  /**
   * @typedef size
   * @brief Basic size type which specialises on @em signed values.
   *
   * @typedef size_type
   * @brief The type of values used with the basic size type.
   */
  typedef basic_size<signed> size;
  typedef size::value_type   size_type;

  /**
   * @typedef screen_size
   * @brief Basic size type which specialises on @em unsigned values.
   *
   * @typedef screen_size_type
   * @brief The type of values used with the screen size type.
   */
  typedef basic_size<std::size_t> screen_size;
  typedef screen_size::value_type screen_size_type;
  
}                                       // namespace ovision

#endif // !_size_hpp_

// size.hpp ends here
