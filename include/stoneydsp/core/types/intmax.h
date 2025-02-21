/**
 * @file intmax.h
 * @author StoneyDSP (nathanjhood@googlemail.com)
 * @brief
 * @version @STONEYDSP_CORE_VERSION@
 * @date 2025-01-30
 *
 * @copyright Copyright (c) 2025
 *
 */

#pragma once

#ifndef STONEYDSP_CORE_TYPES_INTMAX_H_INCLUDED
  #define STONEYDSP_CORE_TYPES_INTMAX_H_INCLUDED

//====================================================================//INCLUDES

  #ifdef __cplusplus
    #include <cinttypes>
  #else
    #include <inttypes.h>
  #endif // __cplusplus

//=====================================================================//DEFINES

  #ifdef __cplusplus
    /**
     * @brief Integer type with the maximum width supported.
     *
     */
    #define STONEYDSP_INTMAX_T ::std::intmax_t
  #else // !__cplusplus
    /**
     * @brief Integer type with the maximum width supported.
     *
     */
    #define STONEYDSP_INTMAX_T intmax_t
  #endif // __cplusplus

// Minimum constraints

  /**
   * @brief Minimum value of largest signed integral type `stoneydsp_intmax_t`.
   *
   */
  #define STONEYDSP_INTMAX_MIN INTMAX_MIN

// Maximum constraints

  /**
   * @brief Maximum value of largest signed integral type `stoneydsp_intmax_t`.
   *
   */
  #define STONEYDSP_INTMAX_MAX INTMAX_MAX

// Function helpers

  #define STONEYDSP_INTMAX_C INTMAX_C

  #define STONEYDSP_INTMAX_PRINT_F PRIiMAX

  #define STONEYDSP_INTMAX_SCAN_F SCNiMAX

//====================================================================//TYPEDEFS

/**
 * @brief Integer type with the maximum width supported.
 *
 */
typedef STONEYDSP_INTMAX_T stoneydsp_intmax_t;

//===================================================================//CONSTANTS

  #ifdef __cplusplus
/**
 * @brief Minimum value of exact-width signed type `stoneydsp_intmax_t`.
 *
 */
constexpr ::stoneydsp_intmax_t stoneydsp_intmax_min = STONEYDSP_INTMAX_MIN;
/**
 * @brief Maximum value of exact-width signed type `stoneydsp_intmax_t`.
 *
 */
constexpr ::stoneydsp_intmax_t stoneydsp_intmax_max = STONEYDSP_INTMAX_MAX;
  #else  // !__cplusplus
/**
 * @brief Minimum value of exact-width signed type `stoneydsp_intmax_t`.
 *
 */
static const stoneydsp_intmax_t stoneydsp_intmax_min = STONEYDSP_INTMAX_MIN;
/**
 * @brief Maximum value of exact-width signed type `stoneydsp_intmax_t`.
 *
 */
static const stoneydsp_intmax_t stoneydsp_intmax_max = STONEYDSP_INTMAX_MAX;
  #endif // __cplusplus

//==============================================================================

  #ifdef __cplusplus

namespace stoneydsp
{
namespace core
{
namespace types
{
/**
 * @brief Integer type with the maximum width supported.
 *
 */
using intmax_t = ::stoneydsp_intmax_t;
/**
 * @brief Minimum value of exact-width signed type `stoneydsp_intmax_t`.
 *
 */
constexpr ::stoneydsp::core::types::intmax_t intmax_min
    = ::stoneydsp_intmax_min;
/**
 * @brief Maximum value of exact-width signed type `stoneydsp_intmax_t`.
 *
 */
constexpr ::stoneydsp::core::types::intmax_t intmax_max
    = ::stoneydsp_intmax_max;
} // namespace types
} // namespace core
} // namespace stoneydsp

  #endif // __cplusplus

//==============================================================================

  #ifdef __cplusplus

namespace stoneydsp
{
using ::stoneydsp::core::types::intmax_max;
using ::stoneydsp::core::types::intmax_min;
using ::stoneydsp::core::types::intmax_t;
} // namespace stoneydsp

  #endif // __cplusplus

//==============================================================================

#endif // STONEYDSP_CORE_TYPES_INTMAX_H_INCLUDED

//=========================================================================//EOF
