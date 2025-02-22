/**
 * @file uint32.h
 * @author StoneyDSP (nathanjhood@googlemail.com)
 * @brief
 * @version @STONEYDSP_CORE_VERSION@
 * @date 2025-01-30
 *
 * @copyright Copyright (c) 2025
 *
 */

#pragma once

#ifndef STONEYDSP_CORE_TYPES_UINT32_H_INCLUDED
  #define STONEYDSP_CORE_TYPES_UINT32_H_INCLUDED

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
    #define STONEYDSP_UINT32_T ::std::uint32_t

  #else // !__cplusplus

    /**
     * @brief
     *
     */
    #define STONEYDSP_UINT32_T uint32_t

  #endif // __cplusplus

// Maximum constraints

  /**
   * @brief Maximum value of exact-width unsigned type `stoneydsp_uint32_t`.
   *
   */
  #define STONEYDSP_UINT32_MAX UINT32_MAX

// Funtion helpers

/**
 * @brief
 *
 */
  #define STONEYDSP_UINT32_C UINT32_C

/**
 * @brief
 *
 */
  #define STONEYDSP_UINT32_PRINT_F PRIu32

/**
 * @brief
 *
 */
  #define STONEYDSP_UINT32_SCAN_F SCNu32

//====================================================================//TYPEDEFS

/**
 * @brief
 *
 */
typedef STONEYDSP_UINT32_T stoneydsp_uint32_t;

//===================================================================//CONSTANTS

  #ifdef __cplusplus

/**
 * @brief Maximum value of exact-width unsigned type `stoneydsp_uint32_t`.
 *
 * Equivalent to:
 *
 * `(4294967295U)`
 */
constexpr ::stoneydsp_uint32_t stoneydsp_uint32_max = STONEYDSP_UINT32_MAX;

  #else // !__cplusplus

/**
 * @brief Maximum value of exact-width unsigned type `stoneydsp_uint32_t`.
 *
 * Equivalent to:
 *
 * `(4294967295U)`
 */
static const stoneydsp_uint32_t stoneydsp_uint32_max = STONEYDSP_UINT32_MAX;

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
using uint32_t = ::stoneydsp_uint32_t;

/**
 * @brief Maximum value of exact-width unsigned type
 * `stoneydsp::core::types::uint32_t`.
 *
 * Equivalent to:
 *
 * `(4294967295U)`
 */
constexpr ::stoneydsp::core::types::uint32_t uint32_max
    = ::stoneydsp_uint32_max;

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
 * @returns stoneydsp_uint32_t
 *
 */
inline constexpr ::stoneydsp_uint32_t
operator"" _uint32 (unsigned long long value)
{
  return static_cast< ::stoneydsp_uint32_t> (value);
}

/// @} literals
} // namespace literals

/// @} types
} // namespace types

/// @} group core
} //  namespace core

/// @} group stoneydsp

//=====================================================================//ALIASES

using ::stoneydsp::core::types::uint32_t;

using ::stoneydsp::core::types::uint32_max;

} // namespace stoneydsp

  #endif // __cplusplus

//==============================================================================

#endif // STONEYDSP_CORE_TYPES_UINT32_H_INCLUDED

//=========================================================================//EOF
