/**
 * @file int32.h
 * @author StoneyDSP (nathanjhood@googlemail.com)
 * @brief
 * @version @STONEYDSP_CORE_VERSION@
 * @date 2025-01-30
 *
 * @copyright Copyright (c) 2025
 *
 */

#pragma once

#ifndef STONEYDSP_CORE_TYPES_INT32_H_INCLUDED
  #define STONEYDSP_CORE_TYPES_INT32_H_INCLUDED

//====================================================================//INCLUDES

  #ifdef __cplusplus
    #include <cinttypes>
  #else
    #include <inttypes.h>
  #endif // __cplusplus

//=====================================================================//DEFINES

  #ifdef __cplusplus

    /**
     * @brief Integer type with a width of exactly 32 bits.
     *
     */
    #define STONEYDSP_INT32_T ::std::int32_t

  #else // !__cplusplus

    /**
     * @brief Integer type with a width of exactly 32 bits.
     *
     */
    #define STONEYDSP_INT32_T int32_t

  #endif // __cplusplus

// Minimum constraints

  /**
   * @brief Minimum value of exact-width signed type `stoneydsp_int32_t`.
   *
   */
  #define STONEYDSP_INT32_MIN INT32_MIN

// Maximum constraints

  /**
   * @brief Maximum value of exact-width signed type `stoneydsp_int32_t`.
   *
   */
  #define STONEYDSP_INT32_MAX INT32_MAX

// Function helpers

/**
 * @brief
 *
 */
  #define STONEYDSP_INT32_C INT32_C

/**
 * @brief
 *
 */
  #define STONEYDSP_INT32_PRINT_F PRIi32

/**
 * @brief
 *
 */
  #define STONEYDSP_INT32_SCAN_F SCNi32

//====================================================================//TYPEDEFS

/**
 * @brief Integer type with a width of exactly 32 bits.
 *
 * Negative values are represented using 2's complement.
 *
 * No padding.
 *
 */
typedef STONEYDSP_INT32_T stoneydsp_int32_t;

//===================================================================//CONSTANTS

  #ifdef __cplusplus

/**
 * @brief Minimum value of exact-width signed type `stoneydsp_int32_t`.
 *
 * Equivalent to:
 *
 * `(-2147483647-1)`
 */
constexpr ::stoneydsp_int32_t stoneydsp_int32_min = STONEYDSP_INT32_MIN;

/**
 * @brief Maximum value of exact-width signed type `stoneydsp_int32_t`.
 *
 * Equivalent to:
 *
 * `(2147483647)`
 */
constexpr ::stoneydsp_int32_t stoneydsp_int32_max = STONEYDSP_INT32_MAX;

  #else // !__cplusplus

/**
 * @brief Minimum value of exact-width signed type `stoneydsp_int32_t`.
 *
 * Equivalent to:
 *
 * `(-2147483647-1)`
 */
static const stoneydsp_int32_t stoneydsp_int32_min = STONEYDSP_INT32_MIN;

/**
 * @brief Maximum value of exact-width signed type `stoneydsp_int32_t`.
 *
 * Equivalent to:
 *
 * `(2147483647)`
 */
static const stoneydsp_int32_t stoneydsp_int32_max = STONEYDSP_INT32_MAX;

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
 * @brief Integer type with a width of exactly 32 bits.
 *
 * Negative values are represented using 2's complement.
 *
 * No padding.
 *
 */
using int32_t = ::stoneydsp_int32_t;

/**
 * @brief Minimum value of exact-width signed type `stoneydsp_int32_t`.
 *
 * Equivalent to:
 *
 * `(-2147483647-1)`
 */
constexpr ::stoneydsp::core::types::int32_t int32_min = ::stoneydsp_int32_min;

/**
 * @brief Maximum value of exact-width signed type `stoneydsp_int32_t`.
 *
 * Equivalent to:
 *
 * `(2147483647)`
 */
constexpr ::stoneydsp::core::types::int32_t int32_max = ::stoneydsp_int32_max;

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
 * @returns stoneydsp_int32_t
 *
 * @example
 * ```cpp
 * stoneydsp_int32_t myInt = 5_int32;
 * ```
 *
 */
inline constexpr ::stoneydsp_int32_t
operator"" _int32 (unsigned long long value)
{
  return static_cast< ::stoneydsp_int32_t> (value);
}

/// @} literals
} // namespace literals

/// @} types
} // namespace types

/// @} group core
} //  namespace core

/// @} group stoneydsp

//=====================================================================//ALIASES

using ::stoneydsp::core::types::int32_t;

using ::stoneydsp::core::types::int32_min;

using ::stoneydsp::core::types::int32_max;

} // namespace stoneydsp

  #endif // __cplusplus

//==============================================================================

#endif // STONEYDSP_CORE_TYPES_INT32_H_INCLUDED

//=========================================================================//EOF
