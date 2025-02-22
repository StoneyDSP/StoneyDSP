/**
 * @file int16.h
 * @author StoneyDSP (nathanjhood@googlemail.com)
 * @brief
 * @version @STONEYDSP_CORE_VERSION@
 * @date 2025-01-30
 *
 * @copyright Copyright (c) 2025
 *
 */

#pragma once

#ifndef STONEYDSP_CORE_TYPES_INT16_H_INCLUDED
  #define STONEYDSP_CORE_TYPES_INT16_H_INCLUDED

//====================================================================//INCLUDES

  #ifdef __cplusplus
    #include <cinttypes>
  #else
    #include <inttypes.h>
  #endif // __cplusplus

//=====================================================================//DEFINES

  #ifdef __cplusplus

    /**
     * @brief Integer type with a width of exactly 16 bits.
     *
     */
    #define STONEYDSP_INT16_T ::std::int16_t

  #else // !__cplusplus

    /**
     * @brief Integer type with a width of exactly 16 bits.
     *
     */
    #define STONEYDSP_INT16_T int16_t

  #endif // __cplusplus

// Minimum constraints

  /**
   * @brief Minimum value of exact-width signed type `stoneydsp_int16_t`.
   *
   */
  #define STONEYDSP_INT16_MIN INT16_MIN

// Maximum constraints

  /**
   * @brief Maximum value of exact-width signed type `stoneydsp_int16_t`.
   *
   */
  #define STONEYDSP_INT16_MAX INT16_MAX

// Function helpers

/**
 * @brief
 *
 */
  #define STONEYDSP_INT16_C INT16_C

/**
 * @brief
 *
 */
  #define STONEYDSP_INT16_PRINT_F PRIi16

/**
 * @brief
 *
 */
  #define STONEYDSP_INT16_SCAN_F SCNi16

//====================================================================//TYPEDEFS

/**
 * @brief Integer type with a width of exactly 16 bits.
 *
 * Negative values are represented using 2's complement.
 *
 * No padding.
 *
 */
typedef STONEYDSP_INT16_T stoneydsp_int16_t;

//===================================================================//CONSTANTS

  #ifdef __cplusplus

/**
 * @brief Minimum value of exact-width signed type `stoneydsp_int16_t`.
 *
 * Equivalent to:
 *
 * `(-32767-1)`
 */
constexpr ::stoneydsp_int16_t stoneydsp_int16_min = STONEYDSP_INT16_MIN;

/**
 * @brief Maximum value of exact-width signed type `stoneydsp_int16_t`.
 *
 * Equivalent to:
 *
 * `(32767)`
 */
constexpr ::stoneydsp_int16_t stoneydsp_int16_max = STONEYDSP_INT16_MAX;

  #else // !__cplusplus

/**
 * @brief Minimum value of exact-width signed type `stoneydsp_int16_t`.
 *
 * Equivalent to:
 *
 * `(-32767-1)`
 */
static const stoneydsp_int16_t stoneydsp_int16_min = STONEYDSP_INT16_MIN;

/**
 * @brief Maximum value of exact-width signed type `stoneydsp_int16_t`.
 *
 * Equivalent to:
 *
 * `(32767)`
 */
static const stoneydsp_int16_t stoneydsp_int16_max = STONEYDSP_INT16_MAX;

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
 * @brief Integer type with a width of exactly 16 bits.
 *
 * Negative values are represented using 2's complement.
 *
 * No padding.
 *
 */
using int16_t = ::stoneydsp_int16_t;

/**
 * @brief Minimum value of exact-width signed type `stoneydsp_int16_t`.
 *
 * Equivalent to:
 *
 * `(-32767-1)`
 */
constexpr ::stoneydsp::core::types::int16_t int16_min = ::stoneydsp_int16_min;

/**
 * @brief Maximum value of exact-width signed type `stoneydsp_int16_t`.
 *
 * Equivalent to:
 *
 * `(32767)`
 */
constexpr ::stoneydsp::core::types::int16_t int16_max = ::stoneydsp_int16_max;

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
 * @returns stoneydsp_int16_t
 *
 * @example
 * ```cpp
 * stoneydsp_int16_t myInt = 5_int16;
 * ```
 *
 */
inline constexpr ::stoneydsp_int16_t
operator"" _int16 (unsigned long long value)
{
  return static_cast< ::stoneydsp_int16_t> (value);
}

/// @} literals
} // namespace literals

/// @} types
} // namespace types

/// @} group core
} //  namespace core

/// @} group stoneydsp

//=====================================================================//ALIASES

using ::stoneydsp::core::types::int16_t;

using ::stoneydsp::core::types::int16_min;

using ::stoneydsp::core::types::int16_max;

} // namespace stoneydsp

  #endif // __cplusplus

//==============================================================================

#endif // STONEYDSP_CORE_TYPES_INT16_H_INCLUDED

//=========================================================================//EOF
