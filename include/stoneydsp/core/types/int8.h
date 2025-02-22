/**
 * @file int8.h
 * @author StoneyDSP (nathanjhood@googlemail.com)
 * @brief
 * @version @STONEYDSP_CORE_VERSION@
 * @date 2025-01-30
 *
 * @copyright Copyright (c) 2025
 *
 */

#pragma once

#ifndef STONEYDSP_CORE_TYPES_INT8_H_INCLUDED
  #define STONEYDSP_CORE_TYPES_INT8_H_INCLUDED

//====================================================================//INCLUDES

  #ifdef __cplusplus
    #include <cinttypes>
  #else
    #include <inttypes.h>
  #endif // __cplusplus

//=====================================================================//DEFINES

  #ifdef __cplusplus

    /**
     * @brief Integer type with a width of exactly 8 bits.
     *
     */
    #define STONEYDSP_INT8_T ::std::int8_t

  #else // !__cplusplus

    /**
     * @brief
     *
     */
    #define STONEYDSP_INT8_T int8_t

  #endif // __cplusplus

// Minimum constraints

  /**
   * @brief Minimum value of exact-width signed type `stoneydsp_int8_t`.
   *
   */
  #define STONEYDSP_INT8_MIN INT8_MIN

// Maximum constraints

  /**
   * @brief Maximum value of exact-width signed type `stoneydsp_int8_t`.
   *
   */
  #define STONEYDSP_INT8_MAX INT8_MAX

// Function helpers

/**
 * @brief
 *
 */
  #define STONEYDSP_INT8_C INT8_C

/**
 * @brief
 *
 */
  #define STONEYDSP_INT8_PRINT_F PRIi8

/**
 * @brief
 *
 */
  #define STONEYDSP_INT8_SCAN_F SCNi8

//====================================================================//TYPEDEFS

/**
 * @brief Integer type with a width of exactly 8 bits.
 *
 * Negative values are represented using 2's complement.
 *
 * No padding.
 *
 */
typedef STONEYDSP_INT8_T stoneydsp_int8_t;

//===================================================================//CONSTANTS

  #ifdef __cplusplus

/**
 * @brief Minimum value of exact-width signed type `stoneydsp_int8_t`.
 *
 * Equivalent to:
 *
 * `(-128)`
 */
constexpr ::stoneydsp_int8_t stoneydsp_int8_min = STONEYDSP_INT8_MIN;

/**
 * @brief Maximum value of exact-width signed type `stoneydsp_int8_t`.
 *
 * Equivalent to:
 *
 * `(127)`
 */
constexpr ::stoneydsp_int8_t stoneydsp_int8_max = STONEYDSP_INT8_MAX;

  #else // !__cplusplus

/**
 * @brief Minimum value of exact-width signed type `stoneydsp_int8_t`.
 *
 * Equivalent to:
 *
 * `(-128)`
 */
static const stoneydsp_int8_t stoneydsp_int8_min = STONEYDSP_INT8_MIN;

/**
 * @brief Maximum value of exact-width signed type `stoneydsp_int8_t`.
 *
 * Equivalent to:
 *
 * `(127)`
 */
static const stoneydsp_int8_t stoneydsp_int8_max = STONEYDSP_INT8_MAX;

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
 * @brief Integer type with a width of exactly 8 bits.
 *
 * Negative values are represented using 2's complement.
 *
 * No padding.
 *
 */
using int8_t = ::stoneydsp_int8_t;

/**
 * @brief Minimum value of exact-width signed type `stoneydsp_int8_t`.
 *
 * Equivalent to:
 *
 * `(-128)`
 */
constexpr ::stoneydsp::core::types::int8_t int8_min = ::stoneydsp_int8_min;

/**
 * @brief Maximum value of exact-width signed type `stoneydsp_int8_t`.
 *
 * Equivalent to:
 *
 * `(127)`
 */
constexpr ::stoneydsp::core::types::int8_t int8_max = ::stoneydsp_int8_max;

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
 * @returns stoneydsp_int8_t
 *
 * @example
 * ```cpp
 * stoneydsp_int8_t myInt = 5_int8;
 * ```
 *
 */
inline constexpr ::stoneydsp_int8_t
operator"" _int8 (unsigned long long value)
{
  return static_cast< ::stoneydsp_int8_t> (value);
}

/// @} literals
} // namespace literals

/// @} types
} // namespace types

/// @} group core
} //  namespace core

/// @} group stoneydsp

//=====================================================================//ALIASES

using ::stoneydsp::core::types::int8_t;

using ::stoneydsp::core::types::int8_min;

using ::stoneydsp::core::types::int8_max;

} // namespace stoneydsp

  #endif // __cplusplus

//==============================================================================

#endif // STONEYDSP_CORE_TYPES_INT8_H_INCLUDED

//=========================================================================//EOF
