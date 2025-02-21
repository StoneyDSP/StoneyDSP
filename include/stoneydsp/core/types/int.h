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
    #include <climits>
  #else // !__cplusplus
    #include <limits.h>
  #endif // __cplusplus

//=====================================================================//DEFINES

  /**
   * @brief Integer type with a width of exactly 8 bits.
   * No padding.
   *
   */
  #define STONEYDSP_INT_T int

// Maximum constraints

  #define STONEYDSP_INT_MIN INT_MIN

// Minimum constraints

  #define STONEYDSP_INT_MAX INT_MAX

//====================================================================//TYPEDEFS

typedef STONEYDSP_INT_T stoneydsp_int_t;

//===================================================================//CONSTANTS

  #ifdef __cplusplus
constexpr ::stoneydsp_int_t stoneydsp_int_min = STONEYDSP_INT_MIN;
constexpr ::stoneydsp_int_t stoneydsp_int_max = STONEYDSP_INT_MAX;
  #else  // !__cplusplus
static const stoneydsp_int_t stoneydsp_int_min = STONEYDSP_INT_MIN;
static const stoneydsp_int_t stoneydsp_int_max = STONEYDSP_INT_MAX;
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
 * @brief
 *
 */
using int_t = ::stoneydsp_int_t;
constexpr ::stoneydsp::core::types::int_t int_max = ::stoneydsp_int_max;
constexpr ::stoneydsp::core::types::int_t int_min = ::stoneydsp_int_min;
} // namespace types
} // namespace core
} // namespace stoneydsp

  #endif // __cplusplus

//==============================================================================

  #ifdef __cplusplus

namespace stoneydsp
{
using ::stoneydsp::core::types::int_t;
using ::stoneydsp::core::types::int_max;
using ::stoneydsp::core::types::int_min;
} // namespace stoneydsp

  #endif // __cplusplus

//==============================================================================

#endif // STONEYDSP_CORE_TYPES_INT_H_INCLUDED

//=========================================================================//EOF
