/**
 * @file uint16.h
 * @author StoneyDSP (nathanjhood@googlemail.com)
 * @brief
 * @version @STONEYDSP_CORE_VERSION@
 * @date 2025-01-30
 *
 * @copyright Copyright (c) 2025
 *
 */

#pragma once

#ifndef STONEYDSP_CORE_TYPES_UINT16_H_INCLUDED
  #define STONEYDSP_CORE_TYPES_UINT16_H_INCLUDED

//====================================================================//INCLUDES

  #ifdef __cplusplus
    #include <cinttypes>
  #else
    #include <inttypes.h>
  #endif // __cplusplus

//=====================================================================//DEFINES

  #ifdef __cplusplus

    /**
     * @brief
     *
     */
    #define STONEYDSP_UINT16_T ::std::uint16_t

  #else // !__cplusplus

    /**
     * @brief
     *
     */
    #define STONEYDSP_UINT16_T uint16_t

  #endif // __cplusplus

// Maximum constraints

  /**
   * @brief Maximum value of exact-width unsigned type `stoneydsp_uint16_t`.
   *
   */
  #define STONEYDSP_UINT16_MAX UINT16_MAX

// Function helpers

/**
 * @brief
 *
 */
  #define STONEYDSP_UINT16_C UINT16_C

/**
 * @brief
 *
 */
  #define STONEYDSP_UINT16_PRINT_F PRIu16

/**
 * @brief
 *
 */
  #define STONEYDSP_UINT16_SCAN_F SCNu16

//====================================================================//TYPEDEFS

/**
 * @brief
 *
 */
typedef STONEYDSP_UINT16_T stoneydsp_uint16_t;

//===================================================================//CONSTANTS

  #ifdef __cplusplus

/**
 * @brief Maximum value of exact-width unsigned type `stoneydsp_uint16_t`.
 *
 * Equivalent to:
 *
 * `(65535U)`
 */
constexpr ::stoneydsp_uint16_t stoneydsp_uint16_max = STONEYDSP_UINT16_MAX;

  #else // !__cplusplus

/**
 * @brief Maximum value of exact-width unsigned type `stoneydsp_uint16_t`.
 *
 * Equivalent to:
 *
 * `(65535U)`
 */
static const stoneydsp_uint16_t stoneydsp_uint16_max = STONEYDSP_UINT16_MAX;

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
using uint16_t = ::stoneydsp_uint16_t;

/**
 * @brief Maximum value of exact-width unsigned type
 * `stoneydsp::core::types::uint16_t`.
 *
 * Equivalent to:
 *
 * `(65535U)`
 */
constexpr ::stoneydsp::core::types::uint16_t uint16_max
    = ::stoneydsp_uint16_max;

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
 * @returns stoneydsp_uint16_t
 *
 */
inline constexpr ::stoneydsp_uint16_t
operator"" _uint16 (unsigned long long value)
{
  return static_cast< ::stoneydsp_uint16_t> (value);
}

/// @} literals
} // namespace literals

/// @} types
} // namespace types

/// @} group core
} //  namespace core

/// @} group stoneydsp

//=====================================================================//ALIASES

using ::stoneydsp::core::types::uint16_t;

using ::stoneydsp::core::types::uint16_max;

} // namespace stoneydsp

  #endif // __cplusplus

//==============================================================================

#endif // STONEYDSP_CORE_TYPES_UINT16_H_INCLUDED

//=========================================================================//EOF
