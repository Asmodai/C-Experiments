//
// rect.hpp --- Rectangle class.
//
// Copyright (c) 2014 Paul Ward <asmodai@gmail.com>
//
// Time-stamp: <Friday Apr 18, 2014 00:28:43 asmodai>
// Revision:   11
//
// Author:     Paul Ward <asmodai@gmail.com>
// Maintainer: Paul Ward <asmodai@gmail.com>
// Created:    12 Apr 2014 08:43:20
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
 * @file rect.hpp
 * @author Paul Ward
 * @brief Rectangle class.
 */

#pragma once
#ifndef _rect_hpp_
#define _rect_hpp_

#include <limits>

#include "size.hpp"

namespace ovision
{

  /**
   * @brief Base rectangle class.
   * @tparam _TyP Point type.
   * @tparam _TyS Size type.
   *
   * This class acts as a 'plain old data' class for future @em rect
   * types.  It is responsible for containing the data (coordinates,
   * in this case), and the constructors to build the data.
   *
   * If a more advanced or extended point type is required,
   * @c _Rect_base can be derived.
   */
  template <class _TyP, class _TyS>
  struct _Rect_base
  {

    // Public type definitions.
  public:

    /**
     * @typedef _MyT
     * @brief Type of the base class.
     *
     * @typedef _TyPX
     * @brief Type of the point value sans reference.
     *
     * @typedef _TySX
     * @brief Type of the size value sans reference.
     *
     * @typedef basic_point_type
     * @brief Type of the point class.
     *
     * @typedef basic_size_type
     * @brief Type of the size class.
     *
     * @typedef point_type
     * @brief Type of the point value.
     *
     * @typedef size_type
     * @brief Type of the size value.
     */
    typedef _Rect_base<_TyP, _TyS>               _MyT;
    typedef typename std::remove_reference<_TyP> _TyPX;
    typedef typename std::remove_reference<_TyS> _TySX;
    typedef basic_point<_TyP>                    basic_point_type;
    typedef basic_size<_TyS>                     basic_size_type;
    typedef _TyP                                 point_type;
    typedef _TyS                                 size_type;


    // Public member fields.
  public:
    
    basic_point_type origin;            //!< Rectangle origin.
    basic_size_type  extent;            //!< Rectangle extent.


    // Public member functions.
  public:

    /**
     * @brief Default constructor function.
     */
    _Rect_base()
      : origin(basic_point_type()),
        extent(basic_size_type())
    {}

    /**
     * @brief Copy constructor function.
     * @param _Other The object to copy.
     */
    _Rect_base(const _Rect_base<_TyP, _TyS> &_Other)
      : origin(_Other.origin),
        extent(_Other.extent)
    {}

    /**
     * @brief Constructor function.
     * @param _Origin The initial origin of the rectangle.
     * @param _Extent The extent of the rectangle.
     */
    _Rect_base(const basic_point_type &_Origin,
               const basic_size_type  &_Extent)
      : origin(_Origin),
        extent(_Extent)
    {}

    /**
     * @brief Constructor function.
     * @tparam _Pt The type of the point value.
     * @tparam _St The type of the size value.
     * @param _Origin The initial origin of the rectangle.
     * @param _Extent The extent of the rectangle.
     */
    template <typename                 _Pt, typename _St>
    _Rect_base(const basic_point<_Pt> &_Origin,
               const basic_size<_St>  &_Extent)
      : origin(basic_point_type(static_cast<_TyP>(_Origin.x),
                                static_cast<_TyP>(_Origin.y))),
        extent(basic_size_type(static_cast<_TyS>(_Extent.width),
                               static_cast<_TyS>(_Extent.height)))
    {}

    /**
     * @brief Constructor function.
     * @param _Top The initial top (y) location.
     * @param _Left The initial left (x) location.
     * @param _Width The initial width.
     * @param _Height The initial height.
     */
    _Rect_base(const _TyP &_Top,
               const _TyP &_Left,
               const _TyS &_Width,
               const _TyS &_Height)
      : origin(basic_point_type(_Top, _Left)),
        extent(basic_size_type(_Width, _Height))
    {}

    /**
     * @brief Constructor function.
     * @param _Top The initial top (y) location.
     * @param _Left The initial left (x) location.
     * @param _Width The initial width.
     * @param _Height The initial height.
     */
    _Rect_base(_TyPX &&_Top,
               _TyPX &&_Left,
               _TySX &&_Width,
               _TySX &&_Height)
      : origin(basic_point_type(std::move(_Top), std::move(_Left))),
        extent(basic_size_type(std::move(_Width), std::move(_Height)))
    {}

    /**
     * @brief Constructor function.
     * @param _Top The initial top (y) location.
     * @param _Left The initial left (x) location.
     * @param _Width The initial width.
     * @param _Height The initial height.
     */
    _Rect_base(const _TyPX  &_Top,
               _TyPX       &&_Left,
               _TySX       &&_Width,
               _TySX       &&_Height)
      : origin(basic_point_type(std::move(_top), _Left)),
        extent(basic_size_type(_Width, _Height))
    {}

    /**
     * @brief Constructor function.
     * @param _Top The initial top (y) location.
     * @param _Left The initial left (x) location.
     * @param _Width The initial width.
     * @param _Height The initial height.
     */
    _Rect_base(_TyPX       &&_Top,
               const _TyPX  &_Left,
               _TySX       &&_Width,
               _TySX       &&_Height)
      : origin(basic_point_type(_top, std::move(_Left))),
        extent(basic_size_type(_Width, _Height))
    {}

    /**
     * @brief Constructor function.
     * @param _Top The initial top (y) location.
     * @param _Left The initial left (x) location.
     * @param _Width The initial width.
     * @param _Height The initial height.
     */
    _Rect_base(_TyPX       &&_Top,
               _TyPX       &&_Left,
               const _TySX  &_Width,
               _TySX       &&_Height)
      : origin(basic_point_type(_top, _Left)),
        extent(basic_size_type(std::move(_Width), _Height))
    {}

    /**
     * @brief Constructor function.
     * @param _Top The initial top (y) location.
     * @param _Left The initial left (x) location.
     * @param _Width The initial width.
     * @param _Height The initial height.
     */
    _Rect_base(_TyPX       &&_Top,
               _TyPX       &&_Left,
               _TySX       &&_Width,
               const _TySX  &_Height)
      : origin(basic_point_type(_top, _Left)),
        extent(basic_size_type(_Width, std::move(_Height)))
    {}

    /**
     * @brief Constructor function.
     * @param _Top The initial top (y) location.
     * @param _Left The initial left (x) location.
     * @param _Width The initial width.
     * @param _Height The initial height.
     */
    _Rect_base(const _TyPX  &_Top,
               _TyPX       &&_Left,
               _TySX       &&_Width,
               const _TySX  &_Height)
      : origin(basic_point_type(std::move(_top), _Left)),
        extent(basic_size_type(_Width, std::move(_Height)))
    {}

    /**
     * @brief Constructor function.
     * @param _Top The initial top (y) location.
     * @param _Left The initial left (x) location.
     * @param _Width The initial width.
     * @param _Height The initial height.
     */
    _Rect_base(_TyPX       &&_Top,
               const _TyPX  &_Left,
               _TySX       &&_Width,
               const _TySX  &_Height)
      : origin(basic_point_type(_top, std::move(_Left))),
        extent(basic_size_type(_Width, std::move(_Height)))
    {}

    /**
     * @brief Constructor function.
     * @param _Top The initial top (y) location.
     * @param _Left The initial left (x) location.
     * @param _Width The initial width.
     * @param _Height The initial height.
     */
    _Rect_base(_TyPX       &&_Top,
               _TyPX       &&_Left,
               const _TySX  &_Width,
               const _TySX  &_Height)
      : origin(basic_point_type(_top, _Left)),
        extent(basic_size_type(std::move(_Width), std::move(_Height)))
    {}

    /**
     * @brief Constructor function.
     * @param _Top The initial top (y) location.
     * @param _Left The initial left (x) location.
     * @param _Width The initial width.
     * @param _Height The initial height.
     */
    _Rect_base(const _TyPX  &_Top,
               _TyPX       &&_Left,
               const _TySX  &_Width,
               const _TySX  &_Height)
      : origin(basic_point_type(std::move(_top), _Left)),
        extent(basic_size_type(std::move(_Width), std::move(_Height)))
    {}

    /**
     * @brief Constructor function.
     * @param _Top The initial top (y) location.
     * @param _Left The initial left (x) location.
     * @param _Width The initial width.
     * @param _Height The initial height.
     */
    _Rect_base(_TyPX       &&_Top,
               const _TyPX  &_Left,
               const _TySX  &_Width,
               const _TySX  &_Height)
      : origin(basic_point_type(_top, std::move(_Left))),
        extent(basic_size_type(std::move(_Width), std::move(_Height)))
    {}

    /**
     * @brief Constructor function.
     * @param _Top The initial top (y) location.
     * @param _Left The initial left (x) location.
     * @param _Width The initial width.
     * @param _Height The initial height.
     */
    _Rect_base(const _TyPX &_Top,
               const _TyPX &_Left,
               const _TySX &_Width,
               const _TySX &_Height)
      : origin(basic_point_type(std::move(_top), std::move(_Left))),
        extent(basic_size_type(std::move(_Width), std::move(_Height)))
    {}

    /**
     * @brief Constructor function.
     * @param _Top The initial top (y) location.
     * @param _Left The initial left (x) location.
     * @param _Width The initial width.
     * @param _Height The initial height.
     */
    _Rect_base(const _TyPX  &_Top,
               const _TyPX  &_Left,
               _TySX       &&_Width,
               _TySX       &&_Height)
      : origin(basic_point_type(std::move(_top), std::move(_Left))),
        extent(basic_size_type(_Width, _Height))
    {}

    /**
     * @brief Constructor function.
     * @param _Top The initial top (y) location.
     * @param _Left The initial left (x) location.
     * @param _Width The initial width.
     * @param _Height The initial height.
     */
    _Rect_base(const _TyPX  &_Top,
               const _TyPX  &_Left,
               _TySX       &&_Width,
               const _TySX  &_Height)
      : origin(basic_point_type(std::move(_top), std::move(_Left))),
        extent(basic_size_type(_Width, std::move(_Height)))
    {}

    /**
     * @brief Constructor function.
     * @param _Top The initial top (y) location.
     * @param _Left The initial left (x) location.
     * @param _Width The initial width.
     * @param _Height The initial height.
     */
    _Rect_base(_TyPX       &&_Top,
               const _TyPX  &_Left,
               const _TySX  &_Width,
               _TySX       &&_Height)
      : origin(basic_point_type(_top, std::move(_Left))),
        extent(basic_size_type(std::move(_Width), _Height))
    {}

    /**
     * @brief Constructor function.
     * @param _Top The initial top (y) location.
     * @param _Left The initial left (x) location.
     * @param _Width The initial width.
     * @param _Height The initial height.
     */
    _Rect_base(const _TyPX  &_Top,
               const _TyPX  &_Left,
               const _TySX  &_Width,
               _TySX       &&_Height)
      : origin(basic_point_type(std::move(_top), std::move(_Left))),
        extent(basic_size_type(std::move(_Width), _Height))
    {}

    /**
     * @brief Constructor function.
     * @tparam _OT The type of the top value.
     * @tparam _OL The type of the left value.
     * @tparam _OW The type of the width value.
     * @tparam _OH The type of the height value.
     * @param _Top The initial top (y) location.
     * @param _Left The initial left (x) location.
     * @param _Width The initial width.
     * @param _Height The initial height.
     */
    template <class   _OT, class _OL, class _OW, class _OH>
    _Rect_base(_OT  &&_Top,
               _OL  &&_Left,
               _OW  &&_Width,
               _OH  &&_Height)
      : origin(basic_point_type(std::forward<_OT>(_Top),
                                std::forward<_OL>(_Left))),
        extent(basic_size_type(std::forward<_OW>(_Width),
                               std::forward<_OH>(_Height)))
    {}

  };                                    // struct _Rect_base


  /**
   * @brief Basic rectangle class.
   * @tparam _TyP The type of the point values.
   * @tparam _TyS The type of the size values.
   *
   * This is the base class for basic @em rectangle data.  It derives from
   * the @c _Rect_base structure (which is a POD structure), but has
   * the actual utility methods that make sense for a point in
   * geometric space.
   */
  template <class _TyP, class _TyS>
  struct basic_rect
    : public _Rect_base<_TyP, _TyS>
  {

    // Public type definitions.
  public:

    /**
     * @typedef _MyBase
     * @brief The type for the base rectangle class.
     *
     * @typedef _MyType
     * @brief A convenience type for the type of this class.
     *
     * @typedef basic_point_type
     * @brief Type of the basic_point<> class used in this class.
     *
     * @typedef basic_size_type
     * @brief Type of the basic_size<> class used in this class.
     *
     * @typedef point_type
     * @brief Type of the point values.
     *
     * @typedef size_type
     * @brief Type of the size values
     *
     * @typedef _TyPX
     * @brief Type of the point class sans reference.
     *
     * @typedef _TySX
     * @brief Type of the size class sans reference.
     */
    typedef _Rect_base<_TyP, _TyS>                     _MyBase;
    typedef basic_rect<_TyP, _TyS>                     _MyType;
    typedef basic_point<_TyP>                          basic_point_type;
    typedef basic_size<_TyS>                           basic_size_type;
    typedef _TyP                                       point_type;
    typedef _TyS                                       size_type;
    typedef typename std::remove_reference<_TyP>::type _TyPX;
    typedef typename std::remove_reference<_TyS>::type _TySX;


    // Public member functions.
  public:

    /**
     * @brief Default constructor function.
     */
    basic_rect()
      : _MyBase()
    {}

    /**
     * @brief Constructor function
     * @param _Top The initial top (y) value.
     * @param _Left The initial left (x) value.
     * @param _Width The initial width value.
     * @param _Height The initial height value.
     */
    basic_rect(const _TyP &_Top,
               const _TyP &_Left,
               const _TyS &_Width,
               const _TyS &_Height)
      : _MyBase(_Top, _Left, _Width, _Height)
    {}

    /**
     * @brief Constructor function
     * @param _Origin The initial origin values.
     * @param _Extent The initial extent values.
     */
    basic_rect(const basic_point_type &_Origin,
               const basic_size_type  &_Extent)
      : _MyBase(_Origin, _Extent)
    {}

    /**
     * @brief Copy constructor function.
     * @tparam _OTyP Point type of the other object.
     * @tparam _OTyS Size type of the other object.
     * @param _Right The other object.
     */
    template <class _OTyP, class _OTyS>
    basic_rect(basic_rect<_OTyP, _OTyS> &_Right)
      : _MyBase(_Right)
    {}

    /**
     * @brief Constructor function
     * @param _Top The initial top (y) value.
     * @param _Left The initial left (x) value.
     * @param _Width The initial width value.
     * @param _Height The initial height value.
     */
    basic_rect(_TyPX &&_Top,
               _TyPX &&_Left,
               _TySX &&_Width,
               _TySX &&_Height)
      : _MyBase(std::move(_Top),
                std::move(_Left),
                std::move(_Width),
                std::move(_Height))
    {}

    /**
     * @brief Constructor function
     * @param _Top The initial top (y) value.
     * @param _Left The initial left (x) value.
     * @param _Width The initial width value.
     * @param _Height The initial height value.
     */
    basic_rect(_TyPX       &&_Top,
               _TyPX       &&_Left,
               _TySX       &&_Width,
               const _TySX  &_Height)
      : _MyBase(std::move(_Top),
                std::move(_Left),
                std::move(_Width),
                _Height)
    {}

    /**
     * @brief Constructor function
     * @param _Top The initial top (y) value.
     * @param _Left The initial left (x) value.
     * @param _Width The initial width value.
     * @param _Height The initial height value.
     */
    basic_rect(_TyPX       &&_Top,
               _TyPX       &&_Left,
               const _TySX  &_Width,
               _TySX       &&_Height)
      : _MyBase(std::move(_Top),
                std::move(_Left),
                _Width,
                std::move(_Height))
    {}

    /**
     * @brief Constructor function
     * @param _Top The initial top (y) value.
     * @param _Left The initial left (x) value.
     * @param _Width The initial width value.
     * @param _Height The initial height value.
     */
    basic_rect(_TyPX       &&_Top,
               const _TyPX  &_Left,
               _TySX       &&_Width,
               _TySX       &&_Height)
      : _MyBase(std::move(_Top),
                _Left,
                std::move(_Width),
                std::move(_Height))
    {}

    /**
     * @brief Constructor function
     * @param _Top The initial top (y) value.
     * @param _Left The initial left (x) value.
     * @param _Width The initial width value.
     * @param _Height The initial height value.
     */
    basic_rect(const _TyPX  &_Top,
               _TyPX       &&_Left,
               _TySX       &&_Width,
               _TySX       &&_Height)
      : _MyBase(_Top,
                std::move(_Left),
                std::move(_Width),
                std::move(_Height))
    {}

    /**
     * @brief Constructor function
     * @param _Top The initial top (y) value.
     * @param _Left The initial left (x) value.
     * @param _Width The initial width value.
     * @param _Height The initial height value.
     */
    basic_rect(const _TyPX  &_Top,
               _TyPX       &&_Left,
               _TySX       &&_Width,
               const _TySX  &_Height)
      : _MyBase(_Top,
                std::move(_Left),
                std::move(_Width),
                _Height)
    {}

    /**
     * @brief Constructor function
     * @param _Top The initial top (y) value.
     * @param _Left The initial left (x) value.
     * @param _Width The initial width value.
     * @param _Height The initial height value.
     */
    basic_rect(const _TyPX  &_Top,
               _TyPX       &&_Left,
               const _TySX  &_Width,
               _TySX       &&_Height)
      : _MyBase(_Top,
                std::move(_Left),
                _Width,
                std::move(_Height))
    {}

    /**
     * @brief Constructor function
     * @param _Top The initial top (y) value.
     * @param _Left The initial left (x) value.
     * @param _Width The initial width value.
     * @param _Height The initial height value.
     */
    basic_rect(const _TyPX  &_Top,
               const _TyPX  &_Left,
               _TySX       &&_Width,
               _TySX       &&_Height)
      : _MyBase(_Top,
                _Left,
                std::move(_Width),
                std::move(_Height))
    {}

    /**
     * @brief Constructor function
     * @param _Top The initial top (y) value.
     * @param _Left The initial left (x) value.
     * @param _Width The initial width value.
     * @param _Height The initial height value.
     */
    basic_rect(const _TyPX  &_Top,
               const _TyPX  &_Left,
               _TySX       &&_Width,
               const _TySX  &_Height)
      : _MyBase(_Top,
                _Left,
                std::move(_Width),
                _Height)
    {}

    /**
     * @brief Constructor function
     * @param _Top The initial top (y) value.
     * @param _Left The initial left (x) value.
     * @param _Width The initial width value.
     * @param _Height The initial height value.
     */
    basic_rect(const _TyPX  &_Top,
               const _TyPX  &_Left,
               const _TySX  &_Width,
               _TySX       &&_Height)
      : _MyBase(_Top,
                _Left,
                _Width,
                std::move(_Height))
    {}

    /**
     * @brief Constructor function
     * @param _Top The initial top (y) value.
     * @param _Left The initial left (x) value.
     * @param _Width The initial width value.
     * @param _Height The initial height value.
     */
    basic_rect(const _TyPX  &_Top,
               _TyPX       &&_Left,
               const _TySX  &_Width,
               const _TySX  &_Height)
      : _MyBase(_Top,
                std::move(_Left),
                _Width,
                _Height)
    {}

    /**
     * @brief Constructor function
     * @param _Top The initial top (y) value.
     * @param _Left The initial left (x) value.
     * @param _Width The initial width value.
     * @param _Height The initial height value.
     */
    basic_rect(_TyPX       &&_Top,
               _TyPX       &&_Left,
               const _TySX  &_Width,
               const _TySX  &_Height)
      : _MyBase(std::move(_Top),
                std::move(_Left),
                _Width,
                _Height)
    {}

    /**
     * @brief Constructor function
     * @param _Top The initial top (y) value.
     * @param _Left The initial left (x) value.
     * @param _Width The initial width value.
     * @param _Height The initial height value.
     */
    basic_rect(_TyPX       &&_Top,
               const _TyPX  &_Left,
               const _TySX  &_Width,
               _TySX       &&_Height)
      : _MyBase(std::move(_Top),
                _Left,
                _Width,
                std::move(_Height))
    {}

    /**
     * @brief Constructor function
     * @tparam _OTop The type of the top value.
     * @tparam _OLeft The type of the left value.
     * @tparam _OWidth The type of the width value.
     * @tparam _OHeight The type of the height value.
     * @param _Top The initial top (y) value.
     * @param _Left The initial left (x) value.
     * @param _Width The initial width value.
     * @param _Height The initial height value.
     */
    template <class       _OTop,
              class       _OLeft,
              class       _OWidth,
              class       _OHeight>
    basic_rect(_OTop    &&_Top,
               _OLeft   &&_Left,
               _OWidth  &&_Width,
               _OHeight &&_Height)
      : _MyBase(std::forward<_OTop>(_Top),
                std::forward<_OLeft>(_Left),
                std::forward<_OWidth>(_Width),
                std::forward<_OHeight>(_Height))
    {}

    /**
     * @brief Clear the rect origin and extent.
     */
    inline
    void
    clear()
    {
      origin.empty();
      extent.empty();
    }

    /**
     * @brief Return the origin y coordinate.
     * @returns A value of @c point_type.
     */
    inline
    point_type
    top() const
    {
      return origin.y;
    }

    /**
     * @brief Return the origin x coordinate.
     * @returns A value of @c point_type.
     */
    inline
    point_type
    left() const
    {
      return origin.x;
    }

    /**
     * @brief Return the extent x coordinate.
     * @returns A value of @c point_type.
     */
    inline
    point_type
    right() const
    {
      return origin.x + __CAST(point_type, extent.width);
    }

    /**
     * @brief Return the extent y coordinate.
     * @returns A value of @c point_type.
     */
    inline
    point_type
    bottom() const
    {
      return origin.y + __CAST(point_type, extent.height);
    }

    /**
     * @brief Return the area of the rectangle.
     * @returns A value of @c size_type representing the area.
     */
    inline
    size_type
    area() const
    {
      return size_type(extent.width * extent.height);
    }

    /**
     * @brief Is the rectangle empty?
     * @returns @c true if the rectangle is empty (of zero size);
     *          otherwise @c false is returned.
     */
    inline
    bool
    empty() const
    {
      return (origin.x >= extent.width || origin.y >= extent.height);
    }

    /**
     * @brief Does this rectangle contain another?
     * @param _Other Another rectangle to test with.
     * @returns @c true if the other rectangle is contained within
     *          this rectangle; otherwise @c false is returned.
     */
    inline
    bool
    contains(const _MyType &_Other) const
    {
      return (_Other.origin.x      >= origin.x     &&
              _Other.origin.y      >= origin.y     &&
              _Other.extent.width  <= extent.width &&
              _Other.extent.height <= extent.height);
    }

    /**
     * @brief Does this rectangle touch another?
     * @param _Other Another rectangle to test with.
     * @returns @c true if the other rectangle touches the edges of
     *          this rectangle; otherwise @c false is returned.
     */
    inline
    bool
    touches(const _MyType &_Other) const
    {
      return (_Other.right()  > left()  &&
              _Other.left()   < right() &&
              _Other.bottom() > top()   &&
              _Other.top()    < bottom());
    }

    /**
     * @brief Move the rectangle to new coordinates.
     * @param dx The new X coordinate.
     * @param dy The new Y coordinate.
     */
    inline
    void
    move(const point_type dx, const point_type dy)
    {
      origin.x += dx;
      origin.y += dy;
    }

    /**
     * @brief Move the rectangle to new coordinates.
     * @param pt The new point.
     */
    inline
    void
    move(const basic_point_type pt)
    {
      origin += pt;
    }

    /**
     * @brief Copy this rectangle and then move the copy.
     * @param dx The new X coordinate.
     * @param dy The new Y coordinate.
     * @returns A copy of this rectangle with new coordinates.
     */
    inline
    _MyType
    move_copy(const point_type dx, const point_type dy) const
    {
      return _MyType(origin.x + dx,
                     origin.y + dy,
                     extent.width,
                     extent.height);
    }

    /**
     * @brief Copy this rectangle and then move the copy.
     * @param pt The new point.
     * @returns A copy of this rectangle with new coordinates.
     */
    inline
    _MyType
    move_copy(const basic_point_type pt) const
    {
      return _MyType(origin + pt,
                     extent);
    }

    /**
     * @brief Expand the edges of this rectangle.
     * @param dx The amount to expand the X points.
     * @param dy The amount to expand the Y points.
     */
    inline
    void
    expand(const point_type dx, const point_type dy)
    {
      origin.x     -= dx;
      origin.y     -= dy;
      extent.width += (dx * 2);
      extent.width += (dy * 2);
    }

    /**
     * @brief Expand the edges of this rectangle.
     * @param st The amount to expand by.
     */
    inline
    void
    expand(const basic_size_type st)
    {
      origin -= st;
      extent += (st * 2);
    }

    /**
     * @brief Copy this rectangle and then expand its edges.
     * @param dx The amount to expand the X points.
     * @param dy The amount to expand the Y points.
     * @returns A copy of this rectangle with modified points.
     */
    inline
    _MyType
    expand_copy(const point_type dx, const point_type dy) const
    {
      return _MyType(origin.x - dx,
                     origin.y - dy,
                     extent.width + (dx * 2),
                     extent.height + (dy * 2));
    }

    /**
     * @brief Copy this rectangle and then expand its edges.
     * @param st The amount to expand by.
     * @returns A copy of this rectangle with modified points.
     */
    inline
    _MyType
    expand_copy(const basic_size_type st) const
    {
      return _MyType(origin - st,
                     extent + (st * 2));
    }

    /**
     * @brief Contract the edges of this rectangle.
     * @param dx The amount to expand the X points.
     * @param dy The amount to expand the Y points.
     */
    inline
    void
    contract(const point_type dx, const point_type dy)
    {
      origin.x     += dx;
      origin.y     += dy;
      extent.width -= (dx * 2);
      extent.width -= (dy * 2);
    }

    /**
     * @brief Contract the edges of this rectangle.
     * @param st The amount to expand by.
     */
    inline
    void
    contract(const basic_size_type st)
    {
      origin += st;
      extent -= (st * 2);
    }

    /**
     * @brief Copy this rectangle and then contract its edges.
     * @param dx The amount to expand the X points.
     * @param dy The amount to expand the Y points.
     * @returns A copy of this rectangle with modified points.
     */
    inline
    _MyType
    contract_copy(const point_type dx, const point_type dy) const
    {
      return _MyType(origin.x + dx,
                     origin.y + dy,
                     extent.width - (dx * 2),
                     extent.height - (dy * 2));
    }

    /**
     * @brief Copy this rectangle and then contract its edges.
     * @param st The amount to expand by.
     * @returns A copy of this rectangle with modified points.
     */
    inline
    _MyType
    contract_copy(const basic_size_type st) const
    {
      return _MyType(origin + st,
                     extent - (st * 2));
    }

    /**
     * @brief Normalise the points of this rectangle.
     */
    inline
    void
    normalize()
    {
      point_type x = __CAST(point_type, std::min(origin.x, extent.width));
      point_type y = __CAST(point_type, std::min(origin.y, extent.height));
      size_type  w = __CAST(size_type, std::max(origin.x, extent.width));
      size_type  h = __CAST(size_type, std::max(origin.y, extent.height));

      origin.x      = x;
      origin.y      = y;
      extent.width  = w;
      extent.height = h
    }

    /**
     * @brief Copy this rectangle and then normalise it.
     * @returns A copy of this rectangle with modified points.
     */
    inline
    _MyType
    normalize_copy() const
    {
      return _MyType(__CAST(point_type, std::min(origin.x, extent.width)),
                     __CAST(point_type, std::min(origin.y, extent.height)),
                     __CAST(size_type, std::max(origin.x, extent.width)),
                     __CAST(size_type, std::max(origin.y, extent.height)));
    }

    /**
     * @brief Swap the points of this rectangle with that of another.
     * @param _Right The other object.
     */
    inline
    void
    swap(_MyType &_Right)
    {
      if (this != &_Right) {
        std::swap(this->origin, _Right.origin);
        std::swap(this->extent, _Right.extent);
      }
    }

    /**
     * @brief Swap the points of this rectangle with that of another.
     * @param _Right The other object.
     */
    inline
    void
    swap(_MyType &&_Right)
    {
      if (this != &_Right) {
        this->origin = std::move(_Right.origin);
        this->extent = std::move(_Right.extent);
      }
    }

    /**
     * @brief Perform an intersection.
     * @param _Other The object to intersect with.
     * @returns A new object that is the result of the intersection.
     */
    inline
    _MyType &
    operator & (const _MyType &_Other) const
    {
      if (touches(_Other)) {
        return _MyType(std::max(origin.x, _Other.origin.x),
                       std::max(origin.y, _Other.origin.y),
                       std::min(extent.width, _Other.extent.width),
                       std::min(extent.height, _Other.extent.height));
      }

      return _MyType();
    }

    /**
     * @brief Perform a union.
     * @param _Other The object to union with.
     * @returns A new object that is the result of the union.
     */
    inline
    _MyType &
    operator | (const _MyType &_Other) const
    {
      return _MyType(std::min(origin.x, _Other.origin.x),
                     std::min(origin.y, _Other.origin.y),
                     std::max(extent.width, _Other.extent.width),
                     std::max(extent.height, _Other.extent.height));
    }

    /**
     * @brief Cast operator.
     * @returns The origin as type @c const @c basic_point_type.
     */
    inline
    operator const basic_point_type * () const
    {
      return static_cast<const basic_point_type *>this.origin;
    }

    /**
     * @brief Cast operator.
     * @returns The origin as type @c basic_point_type.
     */
    inline
    operator basic_point_type * ()
    {
      return static_cast<basic_point_type *>this.origin;
    }

    /**
     * @brief Cast operator.
     * @returns The size as type @c const @c basic_size_type.
     */
    inline
    operator const basic_size_type * () const
    {
      return static_cast<const basic_size_type *>this.extent;
    }

    /**
     * @brief Cast operator.
     * @returns The size as type @c basic_size_type.
     */
    inline
    operator basic_size_type * ()
    {
      return static_cast<basic_size_type *>this.extent;
    }

    /**
     * @brief Assignment operator.
     * @param _Right The right-hand side.
     * @returns This object with assigned values from the other object.
     */
    inline
    _MyType &
    operator = (const _MyType &_Right)
    {
      this->origin = _Right.origin;
      this->extent = _Right.extent;

      return *this;
    }

    /**
     * @brief Assignment operator.
     * @param _Right The right-hand side.
     * @returns This object with assigned values from the other object.
     */
    inline
    _MyType &
    operator = (_MyType &&_Right)
    {
      this->origin = std::move(_Right.origin);
      this->extent = std::move(_Right.extent);

      return *this;
    }

    /**
     * @brief Subtraction operator.
     * @param _Right The right-hand side.
     * @returns A copy of the rect with modified values.
     */
    inline
    _MyType
    operator - (const basic_size_type &_Right) const
    {
      return move_copy(-(__CAST(point_type, _Right.width)),
                       -(__CAST(point_type, _Right.height)));
    }

    /**
     * @brief Compound addition operator.
     * @param _Other The right-hand side.
     * @returns This object with modified values.
     */
    inline
    _MyType &
    operator += (const basic_size_type &_Other)
    {
      move(__CAST(point_type, _Other.x),
           __CAST(point_type, _Other.y));

      return *this;
    }

    /**
     * @brief Compound addition operator.
     * @param _Other The right-hand side.
     * @returns This object with modified values.
     */
    inline
    _MyType &
    operator += (const size_type &_Other)
    {
      point_type val = __CAST(point_type, _Other);

      move(val, val);

      return *this;
    }

    /**
     * @brief Equality operator.
     * @param _Left The left-hand side.
     * @param _Right The right-hand side.
     * @returns @c true if the left-hand and right-hand objects are equal;
     *          otherwise @c false is returned.
     */
    friend
    bool
    operator == (const _MyType &_Left, const _MyType &_Right)
    {
      return (_Left.origin == _Right.origin &&
              _Left.extent == _Right.extent);
    }

    /**
     * @brief Inequality operator.
     * @param _Left The left-hand side.
     * @param _Right The right-hand side.
     * @returns @c true if the left-hand and right-hand objects are inequal;
     *          otherwise @c false is returned.
     */
    friend
    bool
    operator != (const _MyType &_Left, const _MyType &_Right)
    {
      return !(_Left == _Right);
    }
    
  };                                    // struct basic_rect


  // =================================================================


  /**
   * @brief Make a rect.
   * @tparam _TyP The type of the point values.
   * @tparam _TyS The type of the size values.
   * @param _Top The initial top value.
   * @param _Left The initial left value.
   * @param _Width The initial width value.
   * @param _Height The initial height value.
   * @returns A new instance of @c size with the given values.
   */
  template <class   _TyP, class _TyS>
  inline
  basic_rect<typename std::remove_reference<_TyP>::type,
             typename std::remove_reference<_TyS>::type>
  make_rect(_TyP  &&_Top,
            _TyP  &&_Left,
            _TyS  &&_Width,
            _TyS  &&_Height)
  {
    typedef basic_rect<typename std::remove_reference<_TyP>::type,
                       typename std::remove_reference<_TyS>::type> _MyRect;

    return _MyRect(std::forward<_TyP>(_Top),
                   std::forward<_TyP>(_Left),
                   std::forward<_TyS>(_Width),
                   std::forward<_TyS>(_Height));
  }

  /**
   * @brief Make a rect.
   * @tparam _TyP The type of the point values.
   * @tparam _TyS The type of the size values.
   * @param _Origin The initial origin.
   * @param _Extent The initial size.
   * @returns A new instance of @c size with the given values.
   */
  template <class _TyP, class _TyS>
  inline
  basic_rect<typename std::remove_reference<_TyP>::type,
             typename std::remove_reference<_TyS>::type>
  make_rect(basic_point<_TyP> &&_Origin, basic_size<_TyS> &&_Extent)
  {
    typedef basic_rect<typename std::remove_reference<_TyP>::type,
                       typename std::remove_reference<_TyS>::type> _MyRect;

    return _MyRect(std::forward<_TyP>(_Origin),
                   std::forward<_TyS>(_Extent));
  }

  /**
   * @brief Make a rect.
   * @tparam _TyP The type of the point values.
   * @tparam _TyS The type of the size values.
   * @param _Origin The initial origin.
   * @param _Extent The initial extent.
   * @returns A new instance of @c size with the given values.
   */
  template <class _TyP, class _TyS>
  inline
    basic_rect<typename std::remove_reference<_TyP>::type,
    typename std::remove_reference<_TyS>::type>
    make_rect(const basic_point<_TyP> &_Origin,
              const basic_size<_TyS>  &_Extent)
  {
    typedef basic_rect<typename std::remove_reference<_TyP>::type,
                       typename std::remove_reference<_TyS>::type> _MyRect;

    return _MyRect(_Origin, _Extent);
  }

  /**
   * @typedef screen_rect
   * @brief A rect that represents a screen or similar, i.e. it has
   *        non-negative origin coordinates.
   *
   * @typedef rect
   * @brief A basic rectangle that can have negative origin coordinates.
   */
  typedef basic_rect<screen_point_type, size_type> screen_rect;
  typedef basic_rect<point_type, size_type>        rect;
  
}                                       // namespace ovision

#endif // !_rect_hpp_

// rect.hpp ends here
