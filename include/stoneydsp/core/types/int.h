/**
 * @file int.h
 * @author StoneyDSP (nathanjhood@googlemail.com)
 * @brief
 * @version @STONEYDSP_CORE_VERSION@
 * @date 2025-01-30
 *
 * @copyright Copyright (c) 2025
 *
 */

#pragma once

#ifndef STONEYDSP_CORE_TYPES_INT_H_INCLUDED
  #define STONEYDSP_CORE_TYPES_INT_H_INCLUDED

//====================================================================//INCLUDES

  #ifdef __cplusplus
    #include <cstdint>
  #else
    #include <stdint.h>
  #endif // __cplusplus

//=====================================================================//DEFINES

  #ifdef __cplusplus
    /**
     * @brief Integer type with a width of exactly 8 bits.
     * No padding.
     *
     */
    #define STONEYDSP_INT8_T ::std::int8_t
    /**
     * @brief Integer type with a width of exactly 16 bits.
     *
     * Negative values are represented using 2's complement.
     *
     * No padding.
     *
     */
    #define STONEYDSP_INT16_T ::std::int16_t
    /**
     * @brief Integer type with a width of exactly 32 bits.
     *
     * Negative values are represented using 2's complement.
     *
     * No padding.
     *
     */
    #define STONEYDSP_INT32_T ::std::int32_t
    /**
     * @brief Integer type with a width of exactly 64 bits.
     *
     * Negative values are represented using 2's complement.
     *
     * No padding.
     *
     */
    #define STONEYDSP_INT64_T ::std::int64_t
    /**
     * @brief Integer type with the maximum width supported.
     *
     */
    #define STONEYDSP_INTMAX_T ::std::intmax_t
    /**
     * @brief Integer type capable of holding a value converted from a `void`
     * pointer and then be converted back to that type with a value that
     * compares equal to the original pointer.
     *
     */
    #define STONEYDSP_INTPTR_T ::std::intptr_t
  #else // !__cplusplus
    /**
     * @brief
     *
     */
    #define STONEYDSP_INT8_T int8_t
    /**
     * @brief
     *
     */
    #define STONEYDSP_INT16_T int16_t
    /**
     * @brief
     *
     */
    #define STONEYDSP_INT32_T int32_t
    /**
     * @brief
     *
     */
    #define STONEYDSP_INT64_T int64_t
    /**
     * @brief Integer type with the maximum width supported.
     *
     */
    #define STONEYDSP_INTMAX_T intmax_t
    /**
     * @brief Integer type capable of holding a value converted from a `void`
     * pointer and then be converted back to that type with a value that
     * compares equal to the original pointer.
     *
     */
    #define STONEYDSP_INTPTR_T intptr_t
  #endif // __cplusplus

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

/**
 * @brief Integer type with a width of exactly 16 bits.
 *
 * Negative values are represented using 2's complement.
 *
 * No padding.
 *
 */
typedef STONEYDSP_INT16_T stoneydsp_int16_t;

/**
 * @brief Integer type with a width of exactly 32 bits.
 *
 * Negative values are represented using 2's complement.
 *
 * No padding.
 *
 */
typedef STONEYDSP_INT32_T stoneydsp_int32_t;

/**
 * @brief Integer type with a width of exactly 64 bits.
 *
 * Negative values are represented using 2's complement.
 *
 * No padding.
 *
 */
typedef STONEYDSP_INT64_T stoneydsp_int64_t;

/**
 * @brief Integer type with the maximum width supported.
 *
 */
typedef STONEYDSP_INTMAX_T stoneydsp_intmax_t;

/**
 * @brief Integer type capable of holding a value converted from a `void`
 * pointer and then be converted back to that type with a value that
 * compares equal to the original pointer.
 *
 */
typedef STONEYDSP_INTPTR_T stoneydsp_intptr_t;

//===================================================================//CONSTANTS

// Minimum constraints

  /**
   * @brief Minimum value of exact-width signed type `stoneydsp_int8_t`.
   *
   */
  #define STONEYDSP_INT8_MIN INT8_MIN

  /**
   * @brief Minimum value of exact-width signed type `stoneydsp_int16_t`.
   *
   */
  #define STONEYDSP_INT16_MIN INT16_MIN

  /**
   * @brief Minimum value of exact-width signed type `stoneydsp_int32_t`.
   *
   */
  #define STONEYDSP_INT32_MIN INT32_MIN

  /**
   * @brief Minimum value of exact-width signed type `stoneydsp_int64_t`.
   *
   */
  #define STONEYDSP_INT64_MIN INT64_MIN

  /**
   * @brief Minimum value of largest signed integral type `stoneydsp_intmax_t`.
   *
   */
  #define STONEYDSP_INTMAX_MIN INTMAX_MIN

  /**
   * @brief Minimum value of signed integral type `stoneydsp_intptr_t`.
   *
   */
  #define STONEYDSP_INTPTR_MIN INTPTR_MIN

// Maximum constraints

  /**
   * @brief Maximum value of exact-width signed type `stoneydsp_int8_t`.
   *
   */
  #define STONEYDSP_INT8_MAX INT8_MAX

  /**
   * @brief Maximum value of exact-width signed type `stoneydsp_int16_t`.
   *
   */
  #define STONEYDSP_INT16_MAX INT16_MAX

  /**
   * @brief Maximum value of exact-width signed type `stoneydsp_int32_t`.
   *
   */
  #define STONEYDSP_INT32_MAX INT32_MAX

  /**
   * @brief Maximum value of exact-width signed type `stoneydsp_int64_t`.
   *
   */
  #define STONEYDSP_INT64_MAX INT64_MAX

  /**
   * @brief Maximum value of largest signed integral type `stoneydsp_intmax_t`.
   *
   */
  #define STONEYDSP_INTMAX_MAX INTMAX_MAX

  /**
   * @brief Maximum value of signed integral type `stoneydsp_intptr_t`.
   *
   */
  #define STONEYDSP_INTPTR_MAX INTPTR_MAX

  #ifdef __cplusplus
/**
 * @brief Minimum value of exact-width signed type `stoneydsp_int8_t`.
 *
 * Equivalent to:
 *
 * `-(128)`
 */
constexpr ::stoneydsp_int8_t stoneydsp_int8_min = STONEYDSP_INT8_MIN;
/**
 * @brief Minimum value of exact-width signed type `stoneydsp_int16_t`.
 *
 * Equivalent to:
 *
 * `(-32767-1)`
 */
constexpr ::stoneydsp_int16_t stoneydsp_int16_min = STONEYDSP_INT16_MIN;
/**
 * @brief Minimum value of exact-width signed type `stoneydsp_int32_t`.
 *
 * Equivalent to:
 *
 * `(-2147483647-1)`
 */
constexpr ::stoneydsp_int32_t stoneydsp_int32_min = STONEYDSP_INT32_MIN;
/**
 * @brief Minimum value of exact-width signed type `stoneydsp_int64_t`.
 *
 * Equivalent to:
 *
 * `(-9223372036854775807L-1)`
 */
constexpr ::stoneydsp_int64_t stoneydsp_int64_min = STONEYDSP_INT64_MIN;
/**
 * @brief Minimum value of exact-width signed type `stoneydsp_intmax_t`.
 *
 */
constexpr ::stoneydsp_intmax_t stoneydsp_intmax_min = STONEYDSP_INTMAX_MIN;
/**
 * @brief Minimum value of exact-width signed type `stoneydsp_intptr_t`.
 *
 */
constexpr ::stoneydsp_intptr_t stoneydsp_intptr_min = STONEYDSP_INTPTR_MIN;
/**
 * @brief Maximum value of exact-width signed type `stoneydsp_int8_t`.
 *
 * Equivalent to:
 *
 * `(127)`
 */
constexpr ::stoneydsp_int8_t stoneydsp_int8_max = STONEYDSP_INT8_MAX;
/**
 * @brief Maximum value of exact-width signed type `stoneydsp_int16_t`.
 *
 * Equivalent to:
 *
 * `(32767)`
 */
constexpr ::stoneydsp_int16_t stoneydsp_int16_max = STONEYDSP_INT16_MAX;
/**
 * @brief Maximum value of exact-width signed type `stoneydsp_int32_t`.
 *
 * Equivalent to:
 *
 * `(2147483647)`
 */
constexpr ::stoneydsp_int32_t stoneydsp_int32_max = STONEYDSP_INT32_MAX;
/**
 * @brief Maximum value of exact-width signed type `stoneydsp_int64_t`.
 *
 * Equivalent to:
 *
 * `(9223372036854775807L)`
 */
constexpr ::stoneydsp_int64_t stoneydsp_int64_max = STONEYDSP_INT64_MAX;
/**
 * @brief Maximum value of exact-width signed type `stoneydsp_intmax_t`.
 *
 */
constexpr ::stoneydsp_intmax_t stoneydsp_intmax_max = STONEYDSP_INTMAX_MAX;
/**
 * @brief Maximum value of exact-width signed type `stoneydsp_intptr_t`.
 *
 */
constexpr ::stoneydsp_intptr_t stoneydsp_intptr_max = STONEYDSP_INTPTR_MAX;
  #else  // !__cplusplus
/**
 * @brief Minimum value of exact-width signed type `stoneydsp_int8_t`.
 *
 * Equivalent to:
 *
 * `-(128)`
 */
static const stoneydsp_int8_t stoneydsp_int8_min = STONEYDSP_INT8_MIN;
/**
 * @brief Minimum value of exact-width signed type `stoneydsp_int16_t`.
 *
 * Equivalent to:
 *
 * `(-32767-1)`
 */
static const stoneydsp_int16_t stoneydsp_int16_min = STONEYDSP_INT16_MIN;
/**
 * @brief Minimum value of exact-width signed type `stoneydsp_int32_t`.
 *
 * Equivalent to:
 *
 * `(-2147483647-1)`
 */
static const stoneydsp_int32_t stoneydsp_int32_min = STONEYDSP_INT32_MIN;
/**
 * @brief Minimum value of exact-width signed type `stoneydsp_int64_t`.
 *
 * Equivalent to:
 *
 * `(-9223372036854775807L-1)`
 */
static const stoneydsp_int64_t stoneydsp_int64_min = STONEYDSP_INT64_MIN;
/**
 * @brief Minimum value of exact-width signed type `stoneydsp_intmax_t`.
 *
 */
static const stoneydsp_intmax_t stoneydsp_intmax_min = STONEYDSP_INTMAX_MIN;
/**
 * @brief Minimum value of exact-width signed type `stoneydsp_intptr_t`.
 *
 */
static const stoneydsp_intptr_t stoneydsp_intptr_min = STONEYDSP_INTPTR_MIN;
/**
 * @brief Maximum value of exact-width signed type `stoneydsp_int8_t`.
 *
 * Equivalent to:
 *
 * `(127)`
 */
static const stoneydsp_int8_t stoneydsp_int8_max = STONEYDSP_INT8_MAX;
/**
 * @brief Maximum value of exact-width signed type `stoneydsp_int16_t`.
 *
 * Equivalent to:
 *
 * `(32767)`
 */
static const stoneydsp_int16_t stoneydsp_int16_max = STONEYDSP_INT16_MAX;
/**
 * @brief Maximum value of exact-width signed type `stoneydsp_int32_t`.
 *
 * Equivalent to:
 *
 * `(2147483647)`
 */
static const stoneydsp_int32_t stoneydsp_int32_max = STONEYDSP_INT32_MAX;
/**
 * @brief Maximum value of exact-width signed type `stoneydsp_int64_t`.
 *
 * Equivalent to:
 *
 * `(9223372036854775807L)`
 */
static const stoneydsp_int64_t stoneydsp_int64_max = STONEYDSP_INT64_MAX;
/**
 * @brief Maximum value of exact-width signed type `stoneydsp_intmax_t`.
 *
 */
static const stoneydsp_intmax_t stoneydsp_intmax_max = STONEYDSP_INTMAX_MAX;
/**
 * @brief Maximum value of exact-width signed type `stoneydsp_intptr_t`.
 *
 */
static const stoneydsp_intptr_t stoneydsp_intptr_max = STONEYDSP_INTPTR_MAX;
  #endif // __cplusplus

//===================================================================//FUNCTIONS

  #define STONEYDSP_INT8_C(c) INT8_C (c)

  #define STONEYDSP_INT16_C(c) INT16_C (c)

  #define STONEYDSP_INT32_C(c) INT32_C (c)

  #define STONEYDSP_INT64_C(c) INT64_C (c)

  #define STONEYDSP_INTMAX_C(c) INTMAX_C (c)

//==============================================================================

  #ifdef __cplusplus

namespace stoneydsp
{
namespace core
{
namespace types
{
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
 * @brief Integer type with a width of exactly 16 bits.
 *
 * Negative values are represented using 2's complement.
 *
 * No padding.
 *
 */
using int16_t = ::stoneydsp_int16_t;
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
 * @brief Integer type with a width of exactly 64 bits.
 *
 * Negative values are represented using 2's complement.
 *
 * No padding.
 *
 */
using int64_t = ::stoneydsp_int64_t;
/**
 * @brief Integer type with the maximum width supported.
 *
 */
using intmax_t = ::stoneydsp_intmax_t;
/**
 * @brief Integer type capable of holding a value converted from a `void`
 * pointer and then be converted back to that type with a value that
 * compares equal to the original pointer.
 *
 */
using intptr_t = ::stoneydsp_intptr_t;
/**
 * @brief Minimum value of exact-width signed type `stoneydsp_int8_t`.
 *
 * Equivalent to:
 *
 * `-(128)`
 */
constexpr ::stoneydsp::core::types::int8_t int8_min = ::stoneydsp_int8_min;
/**
 * @brief Minimum value of exact-width signed type `stoneydsp_int16_t`.
 *
 * Equivalent to:
 *
 * `(-32767-1)`
 */
constexpr ::stoneydsp::core::types::int16_t int16_min = ::stoneydsp_int16_min;
/**
 * @brief Minimum value of exact-width signed type `stoneydsp_int32_t`.
 *
 * Equivalent to:
 *
 * `(-2147483647-1)`
 */
constexpr ::stoneydsp::core::types::int32_t int32_min = ::stoneydsp_int32_min;
/**
 * @brief Minimum value of exact-width signed type `stoneydsp_int64_t`.
 *
 * Equivalent to:
 *
 * `(-9223372036854775807L-1)`
 */
constexpr ::stoneydsp::core::types::int64_t int64_min = ::stoneydsp_int64_min;
/**
 * @brief Minimum value of exact-width signed type `stoneydsp_intmax_t`.
 *
 */
constexpr ::stoneydsp::core::types::intmax_t intmax_min
    = ::stoneydsp_intmax_min;
/**
 * @brief Minimum value of exact-width signed type `stoneydsp_intptr_t`.
 *
 */
constexpr ::stoneydsp::core::types::intptr_t intptr_min
    = ::stoneydsp_intptr_min;
/**
 * @brief Maximum value of exact-width signed type `stoneydsp_int8_t`.
 *
 * Equivalent to:
 *
 * `(127)`
 */
constexpr ::stoneydsp::core::types::int8_t int8_max = ::stoneydsp_int8_max;
/**
 * @brief Maximum value of exact-width signed type `stoneydsp_int16_t`.
 *
 * Equivalent to:
 *
 * `(32767)`
 */
constexpr ::stoneydsp::core::types::int16_t int16_max = ::stoneydsp_int16_max;
/**
 * @brief Maximum value of exact-width signed type `stoneydsp_int32_t`.
 *
 * Equivalent to:
 *
 * `(2147483647)`
 */
constexpr ::stoneydsp::core::types::int32_t int32_max = ::stoneydsp_int32_max;
/**
 * @brief Maximum value of exact-width signed type `stoneydsp_int64_t`.
 *
 * Equivalent to:
 *
 * `(9223372036854775807L)`
 */
constexpr ::stoneydsp::core::types::int64_t int64_max = ::stoneydsp_int64_max;
/**
 * @brief Maximum value of exact-width signed type `stoneydsp_intmax_t`.
 *
 */
constexpr ::stoneydsp::core::types::intmax_t intmax_max
    = ::stoneydsp_intmax_max;
/**
 * @brief Maximum value of exact-width signed type `stoneydsp_intptr_t`.
 *
 */
constexpr ::stoneydsp::core::types::intptr_t intptr_max
    = ::stoneydsp_intptr_max;
} // namespace types
} // namespace core
} // namespace stoneydsp

  #endif // __cplusplus

//==============================================================================

  #ifdef __cplusplus

namespace stoneydsp
{
/**
 * @brief Integer type with a width of exactly 8 bits.
 *
 * Negative values are represented using 2's complement.
 *
 * No padding.
 *
 */
using int8_t = ::stoneydsp::core::types::int8_t;
/**
 * @brief Integer type with a width of exactly 16 bits.
 *
 * Negative values are represented using 2's complement.
 *
 * No padding.
 *
 */
using int16_t = ::stoneydsp::core::types::int16_t;
/**
 * @brief Integer type with a width of exactly 32 bits.
 *
 * Negative values are represented using 2's complement.
 *
 * No padding.
 *
 */
using int32_t = ::stoneydsp::core::types::int32_t;
/**
 * @brief Integer type with a width of exactly 64 bits.
 *
 * Negative values are represented using 2's complement.
 *
 * No padding.
 *
 */
using int64_t = ::stoneydsp::core::types::int64_t;
/**
 * @brief Integer type with the maximum width supported.
 *
 */
using intmax_t = ::stoneydsp::core::types::intmax_t;
/**
 * @brief Integer type capable of holding a value converted from a `void`
 * pointer and then be converted back to that type with a value that
 * compares equal to the original pointer.
 *
 */
using intptr_t = ::stoneydsp::core::types::intptr_t;
/**
 * @brief Minimum value of exact-width signed type `stoneydsp::int8_t`.
 *
 * Equivalent to:
 *
 * `-(128)`
 */
constexpr ::stoneydsp::int8_t int8_min = ::stoneydsp::core::types::int8_min;
/**
 * @brief Minimum value of exact-width signed type `stoneydsp::int16_t`.
 *
 * Equivalent to:
 *
 * `(-32767-1)`
 */
constexpr ::stoneydsp::int16_t int16_min = ::stoneydsp::core::types::int16_min;
/**
 * @brief Minimum value of exact-width signed type `stoneydsp::int32_t`.
 *
 * Equivalent to:
 *
 * `(-2147483647-1)`
 */
constexpr ::stoneydsp::int32_t int32_min = ::stoneydsp::core::types::int32_min;
/**
 * @brief Minimum value of exact-width signed type `stoneydsp::int64_t`.
 *
 * Equivalent to:
 *
 * `(-9223372036854775807L-1)`
 */
constexpr ::stoneydsp::int64_t int64_min = ::stoneydsp::core::types::int64_min;
/**
 * @brief Minimum value of exact-width signed type `stoneydsp::intmax_t`.
 *
 */
constexpr ::stoneydsp::intmax_t intmax_min
    = ::stoneydsp::core::types::intmax_min;
/**
 * @brief Minimum value of exact-width signed type `stoneydsp::intptr_t`.
 *
 */
constexpr ::stoneydsp::intptr_t intptr_min
    = stoneydsp::core::types::intptr_min;
/**
 * @brief Maximum value of exact-width signed type `stoneydsp::int8_t`.
 *
 * Equivalent to:
 *
 * `(127)`
 */
constexpr ::stoneydsp::int8_t int8_max = ::stoneydsp::core::types::int8_max;
/**
 * @brief Maximum value of exact-width signed type `stoneydsp::int16_t`.
 *
 * Equivalent to:
 *
 * `(32767)`
 */
constexpr ::stoneydsp::int16_t int16_max = ::stoneydsp::core::types::int16_max;
/**
 * @brief Maximum value of exact-width signed type `stoneydsp::int32_t`.
 *
 * Equivalent to:
 *
 * `(2147483647)`
 */
constexpr ::stoneydsp::int32_t int32_max = ::stoneydsp::core::types::int32_max;
/**
 * @brief Maximum value of exact-width signed type `stoneydsp::int64_t`.
 *
 * Equivalent to:
 *
 * `(9223372036854775807L)`
 */
constexpr ::stoneydsp::int64_t int64_max = ::stoneydsp::core::types::int64_max;
/**
 * @brief Maximum value of exact-width signed type `stoneydsp::intmax_t`.
 *
 */
constexpr ::stoneydsp::intmax_t intmax_max
    = ::stoneydsp::core::types::intmax_max;
/**
 * @brief Maximum value of exact-width signed type `stoneydsp::intptr_t`.
 *
 */
constexpr ::stoneydsp::intptr_t intptr_max
    = ::stoneydsp::core::types::intptr_max;
} // namespace stoneydsp

  #endif // __cplusplus

//==============================================================================

#endif // STONEYDSP_CORE_TYPES_INT_H_INCLUDED

//=========================================================================//EOF
