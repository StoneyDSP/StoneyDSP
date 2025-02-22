/**
 * @file uintmax.h
 * @author StoneyDSP (nathanjhood@googlemail.com)
 * @brief
 * @version @STONEYDSP_CORE_VERSION@
 * @date 2025-01-30
 *
 * @copyright Copyright (c) 2025
 *
 */

#pragma once

#ifndef STONEYDSP_CORE_TYPES_UINTMAX_H_INCLUDED
  #define STONEYDSP_CORE_TYPES_UINTMAX_H_INCLUDED

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
    #define STONEYDSP_UINTMAX_T ::std::uintmax_t

  #else // !__cplusplus

    /**
     * @brief
     *
     */
    #define STONEYDSP_UINTMAX_T uintmax_t

  #endif // __cplusplus

// Maximum constraints

  /**
   * @brief Maximum value of largest unsigned integral type
   * `stoneydsp_uintmax_t`.
   *
   */
  #define STONEYDSP_UINTMAX_MAX UINTMAX_MAX

// Function helpers

/**
 * @brief
 *
 */
  #define STONEYDSP_UINTMAX_C UINTMAX_C

/**
 * @brief
 *
 */
  #define STONEYDSP_UINTMAX_PRINT_F PRIuMAX

/**
 * @brief
 *
 */
  #define STONEYDSP_UINTMAX_SCAN_F SCNuMAX

//====================================================================//TYPEDEFS

/**
 * @brief
 *
 */
typedef STONEYDSP_UINTMAX_T stoneydsp_uintmax_t;

//===================================================================//CONSTANTS

  #ifdef __cplusplus

/**
 * @brief Maximum value of exact-width unsigned type `stoneydsp_uintmax_t`.
 *
 */
constexpr ::stoneydsp_uintmax_t stoneydsp_uintmax_max = STONEYDSP_UINTMAX_MAX;

  #else // !__cplusplus

/**
 * @brief Maximum value of exact-width unsigned type `stoneydsp_uintmax_t`.
 *
 */
static const stoneydsp_uintmax_t stoneydsp_uintmax_max = STONEYDSP_UINTMAX_MAX;

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
using uintmax_t = ::stoneydsp_uintmax_t;

/**
 * @brief Maximum value of exact-width unsigned type
 * `stoneydsp::core::types::uintmax_t`.
 *
 */
constexpr ::stoneydsp::core::types::uintmax_t uintmax_max
    = ::stoneydsp_uintmax_max;

/// @} types
} // namespace types

/// @} group core
} //  namespace core

/// @} group stoneydsp

//=====================================================================//ALIASES

using ::stoneydsp::core::types::uintmax_t;

using ::stoneydsp::core::types::uintmax_max;

} // namespace stoneydsp

  #endif // __cplusplus

//==============================================================================

#endif // STONEYDSP_CORE_TYPES_UINTMAX_H_INCLUDED

//=========================================================================//EOF
