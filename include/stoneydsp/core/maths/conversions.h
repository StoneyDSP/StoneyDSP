/**
 * @file conversions.h
 * @author Nathan J. Hood <nathanjhood@googlemail.com>
 * @brief Gain, decibel, and binary-amplitude conversion functions.
 * @version @STONEYDSP_CORE_VERSION@
 *
 * @copyright Copyright (c) 2024
 */

#pragma once

#ifndef STONEYDSP_CORE_MATHS_CONVERSIONS_H_INCLUDED
  #define STONEYDSP_CORE_MATHS_CONVERSIONS_H_INCLUDED

  #include <math.h>

  #include <stoneydsp/core/core.h>

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_FLT_T STONEYDSP_PUBLIC_FUNCTION
stoneydsp_float_decibels_to_gain (STONEYDSP_FLT_T decibels)
    STONEYDSP_NOEXCEPT
{
  return powf (STONEYDSP_FLT_C (10.0),
               decibels * STONEYDSP_FLT_C (0.05));
}

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_DBL_T STONEYDSP_PUBLIC_FUNCTION
stoneydsp_double_decibels_to_gain (STONEYDSP_DBL_T decibels)
    STONEYDSP_NOEXCEPT
{
  return pow (STONEYDSP_DBL_C (10.0),
              decibels * STONEYDSP_DBL_C (0.05));
}

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_FLT_T STONEYDSP_PUBLIC_FUNCTION
stoneydsp_float_gain_to_decibels (STONEYDSP_FLT_T gain) STONEYDSP_NOEXCEPT
{
  return STONEYDSP_FLT_C (20.0) * log10f (gain);
}

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_DBL_T STONEYDSP_PUBLIC_FUNCTION
stoneydsp_double_gain_to_decibels (STONEYDSP_DBL_T gain) STONEYDSP_NOEXCEPT
{
  return STONEYDSP_DBL_C (20.0) * log10 (gain);
}

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_FLT_T STONEYDSP_PUBLIC_FUNCTION
stoneydsp_float_bits_to_gain (STONEYDSP_FLT_T bits) STONEYDSP_NOEXCEPT
{
  return powf (STONEYDSP_FLT_C (2.0), bits);
}

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_DBL_T STONEYDSP_PUBLIC_FUNCTION
stoneydsp_double_bits_to_gain (STONEYDSP_DBL_T bits) STONEYDSP_NOEXCEPT
{
  return pow (STONEYDSP_DBL_C (2.0), bits);
}

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_FLT_T STONEYDSP_PUBLIC_FUNCTION
stoneydsp_float_gain_to_bits (STONEYDSP_FLT_T gain) STONEYDSP_NOEXCEPT
{
  return log2f (gain);
}

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_DBL_T STONEYDSP_PUBLIC_FUNCTION
stoneydsp_double_gain_to_bits (STONEYDSP_DBL_T gain) STONEYDSP_NOEXCEPT
{
  return log2 (gain);
}

  #ifdef __cplusplus

    #include <cmath>
    #include <type_traits>

namespace stoneydsp
{
namespace core
{
namespace maths
{

/** Convert an amplitude value in decibels to its linear gain. */
template <typename FloatType>
STONEYDSP_INLINE FloatType
decibelsToGain (FloatType decibels) STONEYDSP_NOEXCEPT
{
  static_assert (std::is_floating_point<FloatType>::value,
                 "decibelsToGain requires a floating-point type");

  return std::pow (static_cast<FloatType> (10),
                   decibels * static_cast<FloatType> (0.05L));
}

/** Convert a linear gain to its amplitude value in decibels. */
template <typename FloatType>
STONEYDSP_INLINE FloatType
gainToDecibels (FloatType gain) STONEYDSP_NOEXCEPT
{
  static_assert (std::is_floating_point<FloatType>::value,
                 "gainToDecibels requires a floating-point type");

  return static_cast<FloatType> (20) * std::log10 (gain);
}

/** Convert a binary-amplitude coordinate to linear gain. */
template <typename FloatType>
STONEYDSP_INLINE FloatType
bitsToGain (FloatType bits) STONEYDSP_NOEXCEPT
{
  static_assert (std::is_floating_point<FloatType>::value,
                 "bitsToGain requires a floating-point type");

  return std::pow (static_cast<FloatType> (2), bits);
}

/** Convert a linear gain to its binary-amplitude coordinate. */
template <typename FloatType>
STONEYDSP_INLINE FloatType
gainToBits (FloatType gain) STONEYDSP_NOEXCEPT
{
  static_assert (std::is_floating_point<FloatType>::value,
                 "gainToBits requires a floating-point type");

  return std::log2 (gain);
}

} // namespace maths
} // namespace core
} // namespace stoneydsp

  #endif // __cplusplus

#endif // STONEYDSP_CORE_MATHS_CONVERSIONS_H_INCLUDED
