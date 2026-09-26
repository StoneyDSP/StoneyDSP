/**
 * @file functions.h
 * @author Nathan J. Hood <nathanjhood@googlemail.com>
 * @brief Common floating-point mathematical functions.
 * @version @STONEYDSP_CORE_VERSION@
 *
 * @copyright Copyright (c) 2024
 */

#pragma once

#ifndef STONEYDSP_CORE_MATHS_FUNCTIONS_H_INCLUDED
  #define STONEYDSP_CORE_MATHS_FUNCTIONS_H_INCLUDED

  #include <stoneydsp/core/core.h>

  #ifdef __cplusplus

    #include <type_traits>

namespace stoneydsp
{
namespace core
{
namespace maths
{

/** Commonly used floating-point mathematical functions. */
template <typename FloatType> struct Functions
{
  static_assert (std::is_floating_point<FloatType>::value,
                 "Functions requires a floating-point type");

  /** Return the reciprocal of `x`. */
  static STONEYDSP_INLINE FloatType
  reciprocal (const FloatType &x) STONEYDSP_NOEXCEPT
  {
    return static_cast<FloatType> (1) / x;
  }

  /** Return `x` multiplied by itself. */
  static STONEYDSP_INLINE STONEYDSP_CONSTEXPR FloatType
  square (const FloatType &x) STONEYDSP_NOEXCEPT
  {
    return x * x;
  }
};

} // namespace maths
} // namespace core
} // namespace stoneydsp

  #endif // __cplusplus

#endif // STONEYDSP_CORE_MATHS_FUNCTIONS_H_INCLUDED
