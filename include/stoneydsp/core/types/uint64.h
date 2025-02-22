/**
 * @file uint64.h
 * @author StoneyDSP (nathanjhood@googlemail.com)
 * @brief
 * @version @STONEYDSP_CORE_VERSION@
 * @date 2025-01-30
 *
 * @copyright Copyright (c) 2025
 *
 */

#pragma once

#ifndef STONEYDSP_CORE_TYPES_UINT64_H_INCLUDED
  #define STONEYDSP_CORE_TYPES_UINT64_H_INCLUDED

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
    #define STONEYDSP_UINT64_T ::std::uint64_t

  #else // !__cplusplus

    /**
     * @brief
     *
     */
    #define STONEYDSP_UINT64_T uint64_t

  #endif // __cplusplus

// Maximum constraints

  /**
   * @brief Maximum value of exact-width unsigned type `stoneydsp_uint64_t`.
   *
   */
  #define STONEYDSP_UINT64_MAX UINT64_MAX

// Function helpers

/**
 * @brief
 *
 */
  #define STONEYDSP_UINT64_C UINT64_C

/**
 * @brief
 *
 */
  #define STONEYDSP_UINT64_PRINT_F PRIu64

/**
 * @brief
 *
 */
  #define STONEYDSP_UINT64_SCAN_F SCNu64

//====================================================================//TYPEDEFS

/**
 * @brief
 *
 */
typedef STONEYDSP_UINT64_T stoneydsp_uint64_t;

//===================================================================//CONSTANTS

  #ifdef __cplusplus

/**
 * @brief Maximum value of exact-width unsigned type `stoneydsp_uint64_t`.
 *
 * Equivalent to:
 *
 * `(18446744073709551615UL)`
 */
constexpr ::stoneydsp_uint64_t stoneydsp_uint64_max = STONEYDSP_UINT64_MAX;

  #else // !__cplusplus

/**
 * @brief Maximum value of exact-width unsigned type `stoneydsp_uint64_t`.
 *
 * Equivalent to:
 *
 * `(18446744073709551615UL)`
 */
static const stoneydsp_uint64_t stoneydsp_uint64_max = STONEYDSP_UINT64_MAX;

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
using uint64_t = ::stoneydsp_uint64_t;

/**
 * @brief Maximum value of exact-width unsigned type
 * `stoneydsp::core::types::uint64_t`.
 *
 * Equivalent to:
 *
 * `(18446744073709551615UL)`
 */
constexpr ::stoneydsp::core::types::uint64_t uint64_max
    = ::stoneydsp_uint64_max;

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
 * @returns stoneydsp_uint64_t
 *
 */
inline constexpr ::stoneydsp_uint64_t
operator"" _uint64 (unsigned long long value)
{
  return static_cast< ::stoneydsp_uint64_t> (value);
}

/// @} literals
} // namespace literals

/// @} types
} // namespace types

/// @} group core
} //  namespace core

/// @} group stoneydsp

//=====================================================================//ALIASES

using ::stoneydsp::core::types::uint64_t;

using ::stoneydsp::core::types::uint64_max;

} // namespace stoneydsp

  #endif // __cplusplus

//==============================================================================

#endif // STONEYDSP_CORE_TYPES_UINT64_H_INCLUDED

//=========================================================================//EOF
