/**
 * @file integer_functions.h
 * @author Nathan J. Hood <nathanjhood@googlemail.com>
 * @brief Common integer mathematical functions.
 * @version @STONEYDSP_CORE_VERSION@
 *
 * @copyright Copyright (c) 2024
 */

#pragma once

#ifndef STONEYDSP_CORE_MATHS_INTEGER_FUNCTIONS_H_INCLUDED
  #define STONEYDSP_CORE_MATHS_INTEGER_FUNCTIONS_H_INCLUDED

  #include <stoneydsp/core/core.h>

  #ifdef __cplusplus

    #include <type_traits>

namespace stoneydsp
{
namespace core
{
namespace maths
{

/** Commonly used integer mathematical functions. */
template <typename IntType>
struct IntegerFunctions
{
  static_assert (std::is_integral<IntType>::value,
                 "IntegerFunctions requires an integer type");

  /** Return the remainder of `x` divided by two. */
  static STONEYDSP_INLINE IntType
  moduloTwo (const IntType &x) STONEYDSP_NOEXCEPT
  {
    return static_cast<IntType> (x % static_cast<IntType> (2));
  }
};

} // namespace maths
} // namespace core
} // namespace stoneydsp

  #endif // __cplusplus

#endif // STONEYDSP_CORE_MATHS_INTEGER_FUNCTIONS_H_INCLUDED
