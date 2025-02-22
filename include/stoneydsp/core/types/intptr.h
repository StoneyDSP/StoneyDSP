/**
 * @file intptr.h
 * @author StoneyDSP (nathanjhood@googlemail.com)
 * @brief
 * @version @STONEYDSP_CORE_VERSION@
 * @date 2025-01-30
 *
 * @copyright Copyright (c) 2025
 *
 */

#pragma once

#ifndef STONEYDSP_CORE_TYPES_INTPTR_H_INCLUDED
  #define STONEYDSP_CORE_TYPES_INTPTR_H_INCLUDED

//====================================================================//INCLUDES

  #ifdef __cplusplus
    #include <cinttypes>
  #else
    #include <inttypes.h>
  #endif // __cplusplus

//=====================================================================//DEFINES

  #ifdef __cplusplus

    /**
     * @brief Integer type capable of holding a value converted from a `void`
     * pointer and then be converted back to that type with a value that
     * compares equal to the original pointer.
     *
     */
    #define STONEYDSP_INTPTR_T ::std::intptr_t

  #else // !__cplusplus

    /**
     * @brief Integer type capable of holding a value converted from a `void`
     * pointer and then be converted back to that type with a value that
     * compares equal to the original pointer.
     *
     */
    #define STONEYDSP_INTPTR_T intptr_t

  #endif // __cplusplus

// Minimum constraints

  /**
   * @brief Minimum value of signed integral type `stoneydsp_intptr_t`.
   *
   */
  #define STONEYDSP_INTPTR_MIN INTPTR_MIN

// Maximum constraints

  /**
   * @brief Maximum value of signed integral type `stoneydsp_intptr_t`.
   *
   */
  #define STONEYDSP_INTPTR_MAX INTPTR_MAX

// Function helpers

/**
 * @brief
 *
 */
  #define STONEYDSP_INTPTR_PRINT_F PRIiPTR

/**
 * @brief
 *
 */
  #define STONEYDSP_INTPTR_SCAN_F SCNiPTR

//====================================================================//TYPEDEFS

/**
 * @brief Integer type capable of holding a value converted from a `void`
 * pointer and then be converted back to that type with a value that
 * compares equal to the original pointer.
 *
 */
typedef STONEYDSP_INTPTR_T stoneydsp_intptr_t;

//===================================================================//CONSTANTS

  #ifdef __cplusplus

/**
 * @brief Minimum value of exact-width signed type `stoneydsp_intptr_t`.
 *
 */
constexpr ::stoneydsp_intptr_t stoneydsp_intptr_min = STONEYDSP_INTPTR_MIN;

/**
 * @brief Maximum value of exact-width signed type `stoneydsp_intptr_t`.
 *
 */
constexpr ::stoneydsp_intptr_t stoneydsp_intptr_max = STONEYDSP_INTPTR_MAX;

  #else // !__cplusplus

/**
 * @brief Minimum value of exact-width signed type `stoneydsp_intptr_t`.
 *
 */
static const stoneydsp_intptr_t stoneydsp_intptr_min = STONEYDSP_INTPTR_MIN;

/**
 * @brief Maximum value of exact-width signed type `stoneydsp_intptr_t`.
 *
 */
static const stoneydsp_intptr_t stoneydsp_intptr_max = STONEYDSP_INTPTR_MAX;

  #endif // __cplusplus

//==============================================================================

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
 * @brief Integer type capable of holding a value converted from a `void`
 * pointer and then be converted back to that type with a value that
 * compares equal to the original pointer.
 *
 */
using intptr_t = ::stoneydsp_intptr_t;

/**
 * @brief Minimum value of exact-width signed type `stoneydsp_intptr_t`.
 *
 */
constexpr ::stoneydsp::core::types::intptr_t intptr_min
    = ::stoneydsp_intptr_min;

/**
 * @brief Maximum value of exact-width signed type `stoneydsp_intptr_t`.
 *
 */
constexpr ::stoneydsp::core::types::intptr_t intptr_max
    = ::stoneydsp_intptr_max;

/// @} types
} // namespace types

/// @} group core
} //  namespace core

/// @} group stoneydsp

//=====================================================================//ALIASES

using ::stoneydsp::core::types::intptr_t;

using stoneydsp::core::types::intptr_min;

using ::stoneydsp::core::types::intptr_max;

} // namespace stoneydsp

  #endif // __cplusplus

//==============================================================================

#endif // STONEYDSP_CORE_TYPES_INTPTR_H_INCLUDED

//=========================================================================//EOF
