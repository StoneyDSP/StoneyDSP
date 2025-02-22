/**
 * @file uint8.h
 * @author StoneyDSP (nathanjhood@googlemail.com)
 * @brief
 * @version @STONEYDSP_CORE_VERSION@
 * @date 2025-01-30
 *
 * @copyright Copyright (c) 2025
 *
 */

#pragma once

#ifndef STONEYDSP_CORE_TYPES_UINT8_H_INCLUDED
  #define STONEYDSP_CORE_TYPES_UINT8_H_INCLUDED

//====================================================================//INCLUDES

  #ifdef __cplusplus
    #include <cinttypes>
  #else
    #include <inttypes.h>
  #endif // __cplusplus

//=====================================================================//DEFINES

  #ifdef __cplusplus

  /**
   * @brief Integer type with a wdith of exactly 8 bits.
   *
   */
    #define STONEYDSP_UINT8_T ::std::uint8_t

  #else // !__cplusplus

    /**
     * @brief
     *
     */
    #define STONEYDSP_UINT8_T uint8_t

  #endif // __cplusplus

// Maximum constraints

  /**
   * @brief Maximum value of exact-width unsigned type `stoneydsp_uint8_t`.
   *
   */
  #define STONEYDSP_UINT8_MAX UINT8_MAX

// Function helpers

  /**
   * @brief
   *
   */
  #define STONEYDSP_UINT8_C UINT8_C

  /**
   * @brief
   *
   */
  #define STONEYDSP_UINT8_PRINT_F PRIu8

/**
 * @brief
 *
 */
  #define STONEYDSP_UINT8_SCAN_F SCNu8

//====================================================================//TYPEDEFS

/**
 * @brief
 *
 */
typedef STONEYDSP_UINT8_T stoneydsp_uint8_t;

//===================================================================//CONSTANTS

  #ifdef __cplusplus

/**
 * @brief Maximum value of exact-width unsigned type `stoneydsp_uint8_t`.
 *
 * Equivalent to:
 *
 * `(255U)`
 */
constexpr ::stoneydsp_uint8_t stoneydsp_uint8_max = STONEYDSP_UINT8_MAX;

  #else // !__cplusplus

/**
 * @brief Maximum value of exact-width unsigned type `stoneydsp_uint8_t`.
 *
 * Equivalent to:
 *
 * `(255U)`
 */
static const stoneydsp_uint8_t stoneydsp_uint8_max = STONEYDSP_UINT8_MAX;

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
 * @brief
 *
 */
using uint8_t = ::stoneydsp_uint8_t;

/**
 * @brief Maximum value of exact-width unsigned type
 * `stoneydsp::core::types::uint8_t`.
 *
 * Equivalent to:
 *
 * `(255U)`
 */
constexpr ::stoneydsp::core::types::uint8_t uint8_max = ::stoneydsp_uint8_max;

//====================================================================//LITERALS

namespace literals
{
/** @addtogroup literals
 *  @{
 */

/**
 * @brief
 *
 * @param value
 *
 * @returns stoneydsp_uint8_t
 *
 */
inline constexpr ::stoneydsp_uint8_t
operator"" _uint8 (unsigned long long value)
{
  return static_cast< ::stoneydsp_uint8_t> (value);
}

/// @} literals
} // namespace literals

/// @} types
} // namespace types

/// @} group core
} //  namespace core

/// @} group stoneydsp

//=====================================================================//ALIASES

using ::stoneydsp::core::types::uint8_t;

using ::stoneydsp::core::types::uint8_max;

} // namespace stoneydsp

  #endif // __cplusplus

//==============================================================================

#endif // STONEYDSP_CORE_TYPES_UINT8_H_INCLUDED

//=========================================================================//EOF
