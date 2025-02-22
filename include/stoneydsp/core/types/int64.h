/**
 * @file int64.h
 * @author StoneyDSP (nathanjhood@googlemail.com)
 * @brief
 * @version @STONEYDSP_CORE_VERSION@
 * @date 2025-01-30
 *
 * @copyright Copyright (c) 2025
 *
 */

#pragma once

#ifndef STONEYDSP_CORE_TYPES_INT64_H_INCLUDED
  #define STONEYDSP_CORE_TYPES_INT64_H_INCLUDED

//====================================================================//INCLUDES

  #ifdef __cplusplus
    #include <cinttypes>
  #else
    #include <inttypes.h>
  #endif // __cplusplus

//=====================================================================//DEFINES

  #ifdef __cplusplus

    /**
     * @brief Integer type with a width of exactly 64 bits.
     *
     */
    #define STONEYDSP_INT64_T ::std::int64_t

  #else // !__cplusplus

    /**
     * @brief Integer type with a width of exactly 64 bits.
     *
     */
    #define STONEYDSP_INT64_T int64_t

  #endif // __cplusplus

// Function helpers

  /**
   * @brief
   *
   */
  #define STONEYDSP_INT64_C INT64_C

/**
 * @brief
 *
 */
  #define STONEYDSP_INT64_PRINT_F PRIi64

/**
 * @brief
 *
 */
  #define STONEYDSP_INT64_SCAN_F SCNi64

//====================================================================//TYPEDEFS

/**
 * @brief Integer type with a width of exactly 64 bits.
 *
 * Negative values are represented using 2's complement.
 *
 * No padding.
 *
 */
typedef STONEYDSP_INT64_T stoneydsp_int64_t;

//===================================================================//CONSTANTS

// Minimum constraints

  /**
   * @brief Minimum value of exact-width signed type `stoneydsp_int64_t`.
   *
   */
  #define STONEYDSP_INT64_MIN INT64_MIN

// Maximum constraints

  /**
   * @brief Maximum value of exact-width signed type `stoneydsp_int64_t`.
   *
   */
  #define STONEYDSP_INT64_MAX INT64_MAX

  #ifdef __cplusplus

/**
 * @brief Minimum value of exact-width signed type `stoneydsp_int64_t`.
 *
 * Equivalent to:
 *
 * `(-9223372036854775807L-1)`
 */
constexpr ::stoneydsp_int64_t stoneydsp_int64_min = STONEYDSP_INT64_MIN;

/**
 * @brief Maximum value of exact-width signed type `stoneydsp_int64_t`.
 *
 * Equivalent to:
 *
 * `(9223372036854775807L)`
 */
constexpr ::stoneydsp_int64_t stoneydsp_int64_max = STONEYDSP_INT64_MAX;

  #else // !__cplusplus

/**
 * @brief Minimum value of exact-width signed type `stoneydsp_int64_t`.
 *
 * Equivalent to:
 *
 * `(-9223372036854775807L-1)`
 */
static const stoneydsp_int64_t stoneydsp_int64_min = STONEYDSP_INT64_MIN;

/**
 * @brief Maximum value of exact-width signed type `stoneydsp_int64_t`.
 *
 * Equivalent to:
 *
 * `(9223372036854775807L)`
 */
static const stoneydsp_int64_t stoneydsp_int64_max = STONEYDSP_INT64_MAX;

  #endif // __cplusplus

//===================================================================//NAMESPACE

  #ifdef __cplusplus

namespace stoneydsp
{
/** @addtogroup stoneydsp
 *  @{
 */

namespace core
{
/** @addtogroup core
 *  @{
 */

namespace types
{
/** @addtogroup types
 *  @{
 */

/**
 * @brief Integer type with a width of exactly 64 bits.
 *
 * Negative values are represented using 2's complement.
 *
 * No padding.
 *
 */
using int64_t = ::stoneydsp_int64_t;

/**
 * @brief Minimum value of exact-width signed type `stoneydsp_int64_t`.
 *
 * Equivalent to:
 *
 * `(-9223372036854775807L-1)`
 */
constexpr ::stoneydsp::core::types::int64_t int64_min = ::stoneydsp_int64_min;

/**
 * @brief Maximum value of exact-width signed type `stoneydsp_int64_t`.
 *
 * Equivalent to:
 *
 * `(9223372036854775807L)`
 */
constexpr ::stoneydsp::core::types::int64_t int64_max = ::stoneydsp_int64_max;

//====================================================================//LITERALS

namespace literals
{
/** @addtogroup literals
 * @{
 */

/**
 * @brief
 *
 * @param value
 *
 * @returns stoneydsp_int64_t
 *
 * @example
 * ```cpp
 * stoneydsp_int64_t myInt = 5_int64;
 * ```
 *
 */
inline constexpr ::stoneydsp_int64_t
operator"" _int64 (unsigned long long value)
{
  return static_cast< ::stoneydsp_int64_t> (value);
}

/// @} literals
} // namespace literals

/// @} types
} // namespace types

/// @} group core
} //  namespace core

/// @} group stoneydsp

//=====================================================================//ALIASES

using ::stoneydsp::core::types::int64_t;

using ::stoneydsp::core::types::int64_min;

using ::stoneydsp::core::types::int64_max;

} // namespace stoneydsp

  #endif // __cplusplus

//==============================================================================

#endif // STONEYDSP_CORE_TYPES_INT64_H_INCLUDED

//=========================================================================//EOF
