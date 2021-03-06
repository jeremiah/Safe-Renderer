#ifndef POPULUSSC_PSCTYPES_H
#define POPULUSSC_PSCTYPES_H

/******************************************************************************
**
**   File:        PscTypes.h
**   Description:
**
**   Copyright (C) 2017 Luxoft GmbH
**
**   This file is part of Safe Renderer.
**
**   Safe Renderer is free software: you can redistribute it and/or
**   modify it under the terms of the GNU Lesser General Public
**   License as published by the Free Software Foundation.
**
**   Safe Renderer is distributed in the hope that it will be useful,
**   but WITHOUT ANY WARRANTY; without even the implied warranty of
**   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
**   Lesser General Public License for more details.
**
**   You should have received a copy of the GNU Lesser General Public
**   License along with Safe Renderer.  If not, see
**   <http://www.gnu.org/licenses/>.
**
**   SPDX-License-Identifier: LGPL-3.0
**
******************************************************************************/

#include <stdint.h>
#include <cstring>

#if(_MSC_VER >= 1800 || __cplusplus >= 201103L)
// allow some c++-11 features in a backward compatible way
#define P_OVERRIDE override ///< override modifier (C++-11)
#define P_FINAL final       ///< final modifier (C++-11)
#define P_STATIC_ASSERT(condition, name) static_assert(condition, name); ///< static_assert (C++-11)
#elif defined(__GNUC__) && ((__GNUC__ > 4) || ((__GNUC__ == 4) && (__GNUC_MINOR__ >= 7)))
#define P_OVERRIDE
#define P_FINAL
#define P_STATIC_ASSERT(condition, name) \
    typedef const char p_static_assert_failed[(condition) ? 1 : -1] __attribute__((unused));
#else
#define P_OVERRIDE
#define P_FINAL
#define P_STATIC_ASSERT(condition, name) \
    typedef const char p_static_assert_failed[(condition) ? 1 : -1];
#endif // _MSC_VER >= 1800 || __cplusplus >= 201103L

// P_DEPRECATED flag to issue compiler warnings for deprecated methods
#ifdef __GNUC__
#define P_DEPRECATED __attribute__((deprecated))
#elif defined(_MSC_VER)
#define P_DEPRECATED __declspec(deprecated)
#else
#define P_DEPRECATED
#endif

/*
 * P_GCC44_SET_OPTIMIZATION(OPTION) is used to mark function to be compiled
 * with specific optimization options from here https://gcc.gnu.org/onlinedocs/gcc-4.4.0/gcc/Optimize-Options.html
 * Works for GCC >= 4.4. Usage example:
 * void foo() P_GCC44_SET_OPTIMIZATION(-O0);
 */
#if defined(__GNUC__) && ((__GNUC__ > 4) || ((__GNUC__ == 4) && (__GNUC_MINOR__ >= 4)))
#define P_GCC44_SET_OPTIMIZATION(OPTION) __attribute__((optimize(#OPTION)))
#else
#define P_GCC44_SET_OPTIMIZATION(OPTION)
#endif

/*! @file
* Common defines and types used everywhere in Populus
* This file contains the common types used in all parts of Populus as
* well as some types with global reach.
*/
/*!
* @defgroup PscTypes PscTypes
* This group contains the basic types and definitions used for the PopulusSC,
* as well as basic target independent type definitions.
*
* @addtogroup PscTypes
* @{
*/

typedef int8_t I8;
typedef uint8_t U8;
typedef unsigned short C16;
typedef int16_t I16;
typedef uint16_t U16;
typedef int32_t I32;
typedef uint32_t U32;
typedef uint64_t U64;
typedef int64_t I64;

typedef float F32;
typedef double F64;

typedef U16 DataId; ///< The numerical ID for a dynamic data type in a FU
typedef U16 FUClassId; ///< The numerical ID for a FU Class.
typedef U16 EventId; ///< The numerical ID for a event from a FU
typedef U8 IndicationId; ///< The numerical ID for an indication

/** Max Align type */
#if(_MSC_VER >= 1800 || __cplusplus >= 201103L)
#include <cstddef>
typedef std::max_align_t P_MAX_ALIGN;
#else
 /**
  * According to http://en.cppreference.com/w/cpp/types/max_align_t
  * this value should be equal to long double value,
  * but as sizeof(long double) can be equal to 12 on i386 cpu
  * (https://en.wikipedia.org/wiki/Long_double:
  * On the x86 architecture, most C compilers implement long double as
  * the 80-bit extended precision type supported by x86 hardware
  * (sometimes stored as 12 or 16 bytes to maintain data structure alignment))
  * it will violate alignment requirements:
  * http://en.cppreference.com/w/cpp/language/object#Alignment
  * (Every object type has the property called alignment requirement,
  * which is an integer value (of type std::size_t, always a power of 2))
  * That's why we place simple double value here.
  */
typedef double P_MAX_ALIGN;
#endif

/** An unsigned 8-bit integer with a range from 0 to 255. */
#define U8_MIN (0) ///< The smallest possible value for a ::U8.
#define U8_MAX (255) ///< The largest possible value for a ::U8.

/*! @} */

#endif // POPULUSSC_PSCTYPES_H
