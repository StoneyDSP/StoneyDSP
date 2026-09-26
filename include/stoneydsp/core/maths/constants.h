/**
 * @file constants.h
 * @author Nathan J. Hood <nathanjhood@googlemail.com>
 * @brief Common floating-point mathematical constants.
 * @version @STONEYDSP_CORE_VERSION@
 *
 * @copyright Copyright (c) 2024
 */

#pragma once

#ifndef STONEYDSP_CORE_MATHS_CONSTANTS_H_INCLUDED
  #define STONEYDSP_CORE_MATHS_CONSTANTS_H_INCLUDED

  #include <stoneydsp/core/core.h>

  #ifdef __cplusplus

    #include <type_traits>

namespace stoneydsp
{
namespace core
{
namespace maths
{

/** Commonly used floating-point mathematical constants. */
template <typename FloatType>
struct Constants
{
  static_assert (std::is_floating_point<FloatType>::value,
                 "Constants requires a floating-point type");

  static STONEYDSP_CONSTEXPR FloatType oneThird
      = static_cast<FloatType> (1.0L / 3.0L);
  static STONEYDSP_CONSTEXPR FloatType twoThirds
      = static_cast<FloatType> (2.0L / 3.0L);

  static STONEYDSP_CONSTEXPR FloatType pi
      = static_cast<FloatType> (3.14159265358979323846264338327950288L);
  static STONEYDSP_CONSTEXPR FloatType twoPi
      = static_cast<FloatType> (6.28318530717958647692528676655900576L);
  static STONEYDSP_CONSTEXPR FloatType halfPi
      = static_cast<FloatType> (1.57079632679489661923132169163975144L);
  static STONEYDSP_CONSTEXPR FloatType tau
      = static_cast<FloatType> (6.28318530717958647692528676655900576L);
  static STONEYDSP_CONSTEXPR FloatType euler
      = static_cast<FloatType> (2.71828182845904523536028747135266250L);

  static STONEYDSP_CONSTEXPR FloatType sqrtTwo
      = static_cast<FloatType> (1.41421356237309504880168872420969808L);
  static STONEYDSP_CONSTEXPR FloatType oneDivSqrtTwo
      = static_cast<FloatType> (0.70710678118654752440084436210484904L);
  static STONEYDSP_CONSTEXPR FloatType twoSqrtTwo
      = static_cast<FloatType> (2.82842712474619009760337744841939616L);

  static STONEYDSP_CONSTEXPR FloatType oneDivPi
      = static_cast<FloatType> (0.31830988618379067153776752674502872L);
  static STONEYDSP_CONSTEXPR FloatType twoDivPi
      = static_cast<FloatType> (0.63661977236758134307553505349005745L);
  static STONEYDSP_CONSTEXPR FloatType twoDivSqrtPi
      = static_cast<FloatType> (1.12837916709551257389615890312154517L);

  static STONEYDSP_CONSTEXPR FloatType logTwoE
      = static_cast<FloatType> (1.44269504088896340735992468100189214L);
  static STONEYDSP_CONSTEXPR FloatType logTenE
      = static_cast<FloatType> (0.43429448190325182765112891891660508L);
  static STONEYDSP_CONSTEXPR FloatType lnTwo
      = static_cast<FloatType> (0.69314718055994530941723212145817657L);
  static STONEYDSP_CONSTEXPR FloatType lnTen
      = static_cast<FloatType> (2.30258509299404568401799145468436421L);
};

template <typename FloatType>
STONEYDSP_CONSTEXPR FloatType Constants<FloatType>::oneThird;

template <typename FloatType>
STONEYDSP_CONSTEXPR FloatType Constants<FloatType>::twoThirds;

template <typename FloatType>
STONEYDSP_CONSTEXPR FloatType Constants<FloatType>::pi;

template <typename FloatType>
STONEYDSP_CONSTEXPR FloatType Constants<FloatType>::twoPi;

template <typename FloatType>
STONEYDSP_CONSTEXPR FloatType Constants<FloatType>::halfPi;

template <typename FloatType>
STONEYDSP_CONSTEXPR FloatType Constants<FloatType>::tau;

template <typename FloatType>
STONEYDSP_CONSTEXPR FloatType Constants<FloatType>::euler;

template <typename FloatType>
STONEYDSP_CONSTEXPR FloatType Constants<FloatType>::sqrtTwo;

template <typename FloatType>
STONEYDSP_CONSTEXPR FloatType Constants<FloatType>::oneDivSqrtTwo;

template <typename FloatType>
STONEYDSP_CONSTEXPR FloatType Constants<FloatType>::twoSqrtTwo;

template <typename FloatType>
STONEYDSP_CONSTEXPR FloatType Constants<FloatType>::oneDivPi;

template <typename FloatType>
STONEYDSP_CONSTEXPR FloatType Constants<FloatType>::twoDivPi;

template <typename FloatType>
STONEYDSP_CONSTEXPR FloatType Constants<FloatType>::twoDivSqrtPi;

template <typename FloatType>
STONEYDSP_CONSTEXPR FloatType Constants<FloatType>::logTwoE;

template <typename FloatType>
STONEYDSP_CONSTEXPR FloatType Constants<FloatType>::logTenE;

template <typename FloatType>
STONEYDSP_CONSTEXPR FloatType Constants<FloatType>::lnTwo;

template <typename FloatType>
STONEYDSP_CONSTEXPR FloatType Constants<FloatType>::lnTen;

} // namespace maths
} // namespace core
} // namespace stoneydsp

  #endif // __cplusplus

#endif // STONEYDSP_CORE_MATHS_CONSTANTS_H_INCLUDED
