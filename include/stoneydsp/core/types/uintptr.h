/**
 * @file uintptr.h
 * @author StoneyDSP (nathanjhood@googlemail.com)
 * @brief
 * @version @STONEYDSP_CORE_VERSION@
 * @date 2025-01-30
 *
 * @copyright Copyright (c) 2025
 *
 */

#pragma once

#ifndef STONEYDSP_CORE_TYPES_UINTPTR_H_INCLUDED
  #define STONEYDSP_CORE_TYPES_UINTPTR_H_INCLUDED

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
    #define STONEYDSP_UINTPTR_T ::std::uintptr_t

  #else // !__cplusplus

    /**
     * @brief
     *
     */
    #define STONEYDSP_UINTPTR_T uintptr_t

  #endif // __cplusplus

// Maximum constraints

  /**
   * @brief Maximum value of unsigned integral type `stoneydsp_uintptr_t`.
   *
   */
  #define STONEYDSP_UINTPTR_MAX UINTPTR_MAX

// Function helpers

/**
 * @brief
 *
 */
  #define STONEYDSP_UINTPTR_PRINT_F PRIuPTR

/**
 * @brief
 *
 */
  #define STONEYDSP_UINTPTR_SCAN_F SCNuPTR

//====================================================================//TYPEDEFS

/**
 * @brief
 *
 */
typedef STONEYDSP_UINTPTR_T stoneydsp_uintptr_t;

//===================================================================//CONSTANTS

  #ifdef __cplusplus

/**
 * @brief Maximum value of exact-width unsigned type `stoneydsp_uintptr_t`.
 *
 */
constexpr ::stoneydsp_uintptr_t stoneydsp_uintptr_max = STONEYDSP_UINTPTR_MAX;

  #else // !__cplusplus

/**
 * @brief Maximum value of exact-width unsigned type `stoneydsp_uintptr_t`.
 *
 */
static const stoneydsp_uintptr_t stoneydsp_uintptr_max = STONEYDSPU_INTPTR_MAX;

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
using uintptr_t = ::stoneydsp_uintptr_t;

/**
 * @brief Maximum value of exact-width unsigned type
 * `stoneydsp::core::types::uintptr_t`.
 *
 */
constexpr ::stoneydsp::core::types::uintptr_t uintptr_max
    = ::stoneydsp_uintptr_max;

/// @} types
} // namespace types

/// @} group core
} //  namespace core

/// @} group stoneydsp

//=====================================================================//ALIASES

using ::stoneydsp::core::types::uintptr_t;

using ::stoneydsp::core::types::uintptr_max;

} // namespace stoneydsp

  #endif // __cplusplus

//==============================================================================

#endif // STONEYDSP_CORE_TYPES_UINTPTR_H_INCLUDED

//=========================================================================//EOF
