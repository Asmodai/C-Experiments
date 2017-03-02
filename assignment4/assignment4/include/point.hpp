//
// point.hpp --- Geometric point/coordinate class.
//
// Copyright (c) 2014 Paul Ward <asmodai@gmail.com>
//
// Time-stamp: <Thursday Sep 25, 2014 19:12:51 asmodai>
// Revision:   8
//
// Author:     Paul Ward <asmodai@gmail.com>
// Maintainer: Paul Ward <asmodai@gmail.com>
// Created:    12 Apr 2014 06:53:10
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
 * @file point.hpp
 * @author Paul Ward
 * @brief Geometric point/coordinate class.
 */

#pragma once
#ifndef _point_hpp_
#define _point_hpp_

#include <cstddef>
#include <utility>

#include <ovision/compiler.h>
#include <ovision/platform.h>
#include <ovision/arch.h>
#include <ovision/standards.h>
#include <ovision/hacks.h>

namespace ovision
{

  // =================================================================
  // Base class:

  /**
   * @brief Base geometric point/coordinate class.
   * @tparam _Ty Type of the coordinate values.
   *
   * This class acts as a 'plain old data' class for future @em point
   * types.  It is responsible for containing the data (coordinates,
   * in this case), and the constructors to build the data.
   *
   * If a more advanced or extended point type is required,
   * @c _Point_base can be derived.
   */
  template <class _Ty>
  struct _Point_base
  {
    
    // Public type definitions.
  public:

    /**
     * @typedef _MyT
     * @brief Template class type.
     *
     * @typedef value_type
     * @brief Point value type.
     *
     * @typedef _TyX
     * @brief Type of template class type should the template be using
     *        a reference.
     */
    typedef _Point_base<_Ty>                          _MyT;
    typedef _Ty                                       value_type;
    typedef typename std::remove_reference<_Ty>::type _TyX;

    
    // Public member fields.
  public:
    
    _Ty x;                              //!< X coordinate.
    _Ty y;                              //!< Y coordinate.

    
    // Public member functions.
  public:

    /**
     * @brief Default constructor function.
     */
    _Point_base()
      : x(_Ty()),
        y(_Ty())
    {}
    
    /**
     * @brief Copy constructor function.
     * @param _Other The object to copy the values from.
     */
    _Point_base(const _Point_base<_Ty> &_Other)
      : x(_Other.x),
        y(_Other.y)
    {}

    /**
     * @brief Constructor function.
     * @param _X The X coordinate.
     * @param _Y The Y coordinate.
     */
    _Point_base(const _Ty &_X, const _Ty &_Y)
      : x(_X),
        y(_Y)
    {}

    /**
     * @brief Constructor function.
     * @param _X The X coordinate.
     * @param _Y The Y coordinate.
     */
    _Point_base(_TyX &&_X, _TyX &&_Y)
      : x(std::move(_X)),
        y(std::move(_Y))
    {}

    /**
     * @brief Constructor function.
     * @param _X The X coordinate.
     * @param _Y The Y coordinate.
     */
    _Point_base(const _TyX &_X, const _TyX &&_Y)
      : x(_X),
        y(std::move(_Y))
    {}

    /**
     * @brief Constructor function.
     * @param _X The X coordinate.
     * @param _Y The Y coordinate.
     */
    _Point_base(const _TyX &&_X, const _TyX &_Y)
      : x(std::move(_X)),
        y(_Y)
    {}

    /**
     * @brief Constructor function.
     * @tparam _Other Type of the initial values.
     * @param _X The X coordinate.
     * @param _Y The Y coordinate.
     */
    template <class _Other>
    _Point_base(_Other &&_X, _Other &&_Y)
      : x(std::forward<_Other>(_X)),
        y(std::forward<_Other>(_Y))
    {}

  };                                    // struct _Point_base

  // End
  // =================================================================


  
  // =================================================================
  // Basic point class:

  /**
   * @brief Basic point class.
   * @tparam _Ty The type of the coordinate values.
   *
   * This is the base class for basic @em point data.  It derives from
   * the @c _Point_base structure (which is a POD structure), but has
   * the actual utility methods that make sense for a point in
   * geometric space.
   */
  template <class _Ty>
  struct basic_point
    : public _Point_base<_Ty>
  {

    // Public type definitions.
  public:

    /**
     * @typedef _MyBase
     * @brief Base class type.
     *
     * @typedef _MyType
     * @brief Template class type.
     *
     * @typedef value_type
     * @brief Coordinate value type.
     *
     * @typedef _TyX
     * @brief Template class type without references.
     */
    typedef _Point_base<_Ty>                          _MyBase;
    typedef basic_point<_Ty>                          _MyType;
    typedef _Ty                                       value_type;
    typedef typename std::remove_reference<_Ty>::type _TyX;


    // Public member functions.
  public:

    // ---------------------------------------------------------------
    // Constructors:
    
    /**
     * @brief Default constructor function.
     */
    basic_point()
      : _MyBase()
    {}

    /**
     * @brief Constructor function.
     * @param _X The X coordinate.
     * @param _Y The Y coordinate.
     */
    basic_point(const _Ty &_X, const _Ty &_Y)
      : _MyBase(_X, _Y)
    {}

    /**
     * @brief Copy constructor function.
     * @tparam _Other The type of the other object.
     * @param _Right The object to copy from.
     */
    template <class _Other>
    basic_point(basic_point<_Other> &_Right)
      : _MyBase(_Right.x, _Right.y)
    {}

    /**
     * @brief Constructor function.
     * @param _X The X coordinate.
     * @param _Y The Y coordinate.
     */
    basic_point(_TyX &&_X, _TyX &&_Y)
      : _MyBase(std::move(_X), std::move(_Y))
    {}

    /**
     * @brief Constructor function.
     * @param _X The X coordinate.
     * @param _Y The Y coordinate.
     */
    basic_point(const _TyX &_X, _TyX &&_Y)
      : _MyBase(_X, std::move(_Y))
    {}

    /**
     * @brief Constructor function.
     * @param _X The X coordinate.
     * @param _Y The Y coordinate.
     */
    basic_point(_TyX &&_X, const _TyX &_Y)
      : _MyBase(std::move(_X), _Y)
    {}

    /**
     * @brief Constructor function.
     * @tparam _Other The type of the initial values.
     * @param _X The X coordinate.
     * @param _Y The Y coordinate.
     */
    template <class _Other>
    basic_point(_Other &&_X, _Other &&_Y)
      : _MyBase(std::forward<_Other>(_X),
                std::forward<_Other>(_Y))
    {}

    /**
     * @brief Copy constructor function.
     * @tparam _Other The type of the initial values.
     * @param _Right The object to take a copy of.
     */
    template <class _Other>
    basic_point(basic_point<_Other> &&_Right)
      : _MyBase(std::forward<_Other>(_Right.x),
                std::forward<_Other>(_Right.y))
    {}

    // End
    // ---------------------------------------------------------------

    
    // ---------------------------------------------------------------
    // Functions.

    /**
     * @brief Clear the coordinate data from an instance.
     */
    inline
    void
    clear()
    {
      this->x = 0;
      this->y = 0;
    }

    /**
     * @brief Convert the size to a linear offset.
     * @returns A standard size value representing the offset.
     *
     * This function converts a 2D coordinate to a 1D offset.  This is
     * designed to allow us to represent a 2D buffer as a 1D array,
     * with this function computing the offset of the coordinate into
     * the 1D array for us.
     */
    inline
    std::size_t
    offset() const
    {
      return x * y;
    }

    /**
     * @brief Swap values between two point instances.
     * @param _Right The object to swap values with.
     */
    inline
    void
    swap(_MyType &_Right)
    {
      if (this != &_Right) {
        std::swap(this->x, _Right.x);
        std::swap(this->y, _Right.y);
      }
    }

    /**
     * @brief Swap values between two point instances.
     * @param _Right The object to swap values with.
     */
    inline
    void
    swap(_MyType &&_Right)
    {
      if (this != &_Right) {
        this->x = std::move(_Right.x);
        this->y = std::move(_Right.y);
      }
    }
    
    /**
     * @brief Assignment operator.
     * @param _Other The object to take assignment from.
     * @returns The modified instance.
     */
    _MyType &
    operator = (const _MyType &_Other)
    {
      this->x = _Other.x;
      this->y = _Other.y;
      
      return *this;
    }

    /**
     * @brief Assignment operator.
     * @param _Other The object to take assignment from.
     * @returns The modified instance.
     */
    _MyType &
    operator = (_MyType &&_Other)
    {
      this->x = std::move(_Other.x);
      this->y = std::move(_Other.y);

      return *this;
    }

    // ...............................................................
    // 'value_type' arguments:

    /**
     * @brief Addition operator.
     * @param _Right The right-hand side.
     * @returns A new instance with the new value(s).
     */
    _MyType
    operator + (const value_type &_Right)
    {
      _MyType _tmp = *this;

      _tmp.x += _Right;
      _tmp.y += _Right;

      return _tmp;
    }

    /**
     * @brief Subtraction operator.
     * @param _Right The right-hand side.
     * @returns A new instance with the new value(s).
     */
    _MyType
    operator - (const value_type &_Right)
    {
      _MyType _tmp = *this;

      _tmp.x -= _Right;
      _tmp.y -= _Right;

      return _tmp;
    }

    /**
     * @brief Multiplication operator.
     * @param _Right The right-hand side.
     * @returns A new instance with the new value(s).
     */
    _MyType
    operator * (const value_type &_Right)
    {
      _MyType _tmp = *this;

      _tmp.x *= _Right;
      _tmp.y *= _Right;

      return _tmp;
    }

    /**
     * @brief Division opertor.
     * @param _Right The right-hand side.
     * @returns A new instance with the new value(s).
     */
    _MyType
    operator / (const value_type &_Right)
    {
      _MyType _tmp = *this;

      _tmp.x /= _Right;
      _tmp.y /= _Right;

      return _tmp;
    }

    /**
     * @brief Compound addition operator.
     * @param _Right The right-hand side.
     * @returns The left-hand instance with modified value(s).
     */
    _MyType &
    operator += (const value_type &_Right)
    {
      this->x += _Right;
      this->y += _Right;

      return *this;
    }

    /**
     * @brief Compound subtraction operator.
     * @param _Right The right-hand side.
     * @returns The left-hand instance with modified value(s).
     */
    _MyType &
    operator -= (const value_type &_Right)
    {
      this->x -= _Right;
      this->y -= _Right;

      return *this;
    }

    /**
     * @brief Compound multiplication operator.
     * @param _Right The right-hand side.
     * @returns The left-hand instance with modified value(s).
     */
    _MyType &
    operator *= (const value_type &_Right)
    {
      this->x *= _Right;
      this->y *= _Right;

      return *this;
    }

    /**
     * @brief Compound division operator.
     * @param _Right The right-hand side.
     * @returns The left-hand instance with modified value(s).
     */
    _MyType &
    operator /= (const value_type &_Right)
    {
      this->x /= _Right;
      this->y /= _Right;

      return *this;
    }

    // End
    // ...............................................................

    
    // ...............................................................
    // '_MyType' arguments:

    /**
     * @brief Addition operator.
     * @param _Right The right-hand side.
     * @returns A new instance with the new value(s).
     */
    _MyType
    operator + (const _MyType &_Right)
    {
      _MyType _tmp = *this;

      _tmp.x += _Right.x;
      _tmp.y += _Right.y;

      return _tmp;
    }

    /**
     * @brief Subtraction operator.
     * @param _Right The right-hand side.
     * @returns A new instance with the new value(s).
     */
    _MyType
    operator - (const _MyType &_Right)
    {
      _MyType _tmp = *this;

      _tmp.x -= _Right.x;
      _tmp.y -= _Right.y;

      return _tmp;
    }

    /**
     * @brief Multiplication operator.
     * @param _Right The right-hand side.
     * @returns A new instance with the new value(s).
     */
    _MyType
    operator * (const _MyType &_Right)
    {
      _MyType _tmp = *this;

      this->x *= _Right.x;
      this->y *= _Right.y;

      return _tmp;
    }

    /**
     * @brief Division opertor.
     * @param _Right The right-hand side.
     * @returns A new instance with the new value(s).
     */
    _MyType
    operator / (const _MyType &_Right)
    {
      _MyType _tmp = *this;

      _tmp.x /= _Right.x;
      _tmp.y /= _Right.y;

      return _tmp;
    }

    /**
     * @brief Compound addition operator.
     * @param _Right The right-hand side.
     * @returns The left-hand instance with modified value(s).
     */
    _MyType &
    operator += (const _MyType &_Right)
    {
      this->x += _Right.x;
      this->y += _Right.y;

      return *this;
    }

    /**
     * @brief Compound subtraction operator.
     * @param _Right The right-hand side.
     * @returns The left-hand instance with modified value(s).
     */
    _MyType &
    operator -= (const _MyType &_Right)
    {
      this->x -= _Right.x;
      this->y -= _Right.y;

      return *this;
    }

    /**
     * @brief Compound multiplication operator.
     * @param _Right The right-hand side.
     * @returns The left-hand instance with modified value(s).
     */
    _MyType &
    operator *= (const _MyType &_Right)
    {
      this->x *= _Right.x;
      this->y *= _Right.y;

      return *this;
    }

    /**
     * @brief Compound division operator.
     * @param _Right The right-hand side.
     * @returns The left-hand instance with modified value(s).
     */
    _MyType &
    operator /= (const _MyType &_Right)
    {
      this->x /= _Right.x;
      this->y /= _Right.y;

      return *this;
    }

    /**
     * @brief Lesser-than operator.
     * @param _Right The right-hand side.
     * @returns @c true if the left-hand side is lesser than the
     *          right-hand side; otherwise @c false is returned.
     */
    bool
    operator < (const _MyType &_Right)
    {
      return (this->x < _Right.x || this->y < _Right.y);
    }

    /**
     * @brief Greater-than operator.
     * @param _Right The right-hand side.
     * @returns @c true if the left-hand side is greater than the
     *          right-hand side; otherwise @c false is returned.
     */
    bool
    operator > (const _MyType &_Right)
    {
      return (this->x > _Right.x || this->y > _Right.y);
    }

    /**
     * @brief Lesser-than-or-equal-to operator.
     * @param _Right The right-hand side.
     * @returns @c true if the left-hand side is lesser than or equal
     *          to the right-hand side; otherwise @c false is
     *          returned.
     */
    bool
    operator <= (const _MyType &_Right)
    {
      return (this->x <= _Right.x || this->y <= _Right.y);
    }

    /**
     * @brief Greater-than-or-equal-to operator.
     * @param _Right The right-hand side.
     * @returns @c true if the left-hand side is greater than or equal
     *          to the right-hand side; otherwise @c false is
     *          returned.
     */
    bool
    operator >= (const _MyType &_Right)
    {
      return (this->x >= _Right.x || this->y >= _Right.y);
    }

    // End
    // ...............................................................

    /**
     * @brief Equality operator.
     * @param _Left The left-hand side.
     * @param _Right The right-hand side.
     * @returns @c true if both sides of the expression are equal;
     *          otherwise @c false is returned.
     */
    friend
    bool
    operator == (const _MyType &_Left, const _MyType &_Right)
    {
      return (_Left.x == _Right.x && _Left.y == _Right.y);
    }

    /**
     * @brief Inequality operator.
     * @param _Left The left-hand side.
     * @param _Right The right-hand side.
     * @returns @c true if both sides of the expression are inequal;
     *          otherwise @c false is returned.
     */
    friend
    bool
    operator != (const _MyType &_Left, const _MyType &_Right)
    {
      return !(_Left == _Right);
    }

  };                                    // struct basic_point
  
  // End
  // =================================================================

  
  /**
   * @brief Make a point.
   * @tparam _Ty The type of the point coordinate values.
   * @param _X The X coordinate.
   * @param _Y The Y coordinate.
   * @returns A new instance of @c point with the given values.
   */
  template <class _Ty>
  inline
  basic_point<typename std::remove_reference<_Ty>::type>
  make_point(_Ty &&_X, _Ty &&_Y)
  {
    typedef basic_point<typename std::remove_reference<_Ty>::type> _MyPoint;

    return _MyPoint(std::forward<_Ty>(_X),
                    std::forward<_Ty>(_Y));
  }

  /**
   * @brief Make a point.
   * @tparam _Ty The type of the point coordinate values.
   * @param _X The X coordinate.
   * @param _Y The Y coordinate.
   * @returns A new instance of @c point with the given values.
   */
  template <class _Ty>
  inline
  basic_point<typename std::remove_reference<_Ty>::type>
  make_point(const _Ty &_X, _Ty &&_Y)
  {
    typedef basic_point<typename std::remove_reference<_Ty>::type> _MyPoint;

    return _MyPoint((typename std::remove_reference<_Ty>::type)_X,
                    std::forward<_Ty>(_Y));
  }

  /**
   * @brief Make a point.
   * @tparam _Ty The type of the point coordinate values.
   * @param _X The X coordinate.
   * @param _Y The Y coordinate.
   * @returns A new instance of @c point with the given values.
   */
  template <class _Ty>
  inline
  basic_point<typename std::remove_reference<_Ty>::type>
  make_point(_Ty &&_X, const _Ty &_Y)
  {
    typedef basic_point<typename std::remove_reference<_Ty>::type> _MyPoint;

    return _MyPoint(std::forward<_Ty>(_X),
                    (typename std::remove_reference<_Ty>::type)_Y);
  }

  /**
   * @brief Make a point.
   * @tparam _Ty The type of the point coordinate values.
   * @param _X The X coordinate.
   * @param _Y The Y coordinate.
   * @returns A new instance of @c point with the given values.
   */
  template <class _Ty>
  inline
  basic_point<typename std::remove_reference<_Ty>::type>
  make_point(const _Ty &_X, const _Ty &_Y)
  {
    typedef basic_point<typename std::remove_reference<_Ty>::type> _MyPoint;
    
    return _MyPoint((typename std::remove_reference<_Ty>::type)_X,
                    (typename std::remove_reference<_Ty>::type)_Y);
  }

  /**
   * @typedef point
   * @brief Standard point data type.
   * @details This class specialises on coordinate values of type
   *          @c unsigned @c int.
   *
   * @typedef screen_point
   * @brief Screen-specific point data type.
   * @details This class specialises on coordinate values of type
   *          @c std::size_t.
   */
  typedef basic_point<signed>      point;
  typedef basic_point<std::size_t> screen_point;

  /**
   * @typedef screen_point_type
   * @brief Screen point value type.
   * @details The type of the coordinate values used by the
   *          @c screen_point class.
   *
   * @typedef point_type
   * @brief Point value type.
   * @details The type of the coordinate values used by the
   *          @c point class.
   */
  typedef screen_point::value_type screen_point_type;
  typedef point::value_type        point_type;

}                                       // namespace ovision

#endif // !_point_hpp_

// point.hpp ends here
