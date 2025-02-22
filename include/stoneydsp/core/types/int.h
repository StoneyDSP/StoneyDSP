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

/**
 * @brief
 *
 */
  #define STONEYDSP_INT_MIN INT_MIN

// Minimum constraints

/**
 * @brief
 *
 */
  #define STONEYDSP_INT_MAX INT_MAX

//====================================================================//TYPEDEFS

/**
 * @brief
 *
 */
typedef STONEYDSP_INT_T stoneydsp_int_t;

//===================================================================//CONSTANTS

  #ifdef __cplusplus

/**
 * @brief
 *
 */
constexpr ::stoneydsp_int_t stoneydsp_int_min = STONEYDSP_INT_MIN;

/**
 * @brief
 *
 */
constexpr ::stoneydsp_int_t stoneydsp_int_max = STONEYDSP_INT_MAX;

  #else // !__cplusplus

/**
 * @brief
 *
 */
static const stoneydsp_int_t stoneydsp_int_min = STONEYDSP_INT_MIN;

/**
 * @brief
 *
 */
static const stoneydsp_int_t stoneydsp_int_max = STONEYDSP_INT_MAX;

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
 * @brief
 *
 */
using int_t = ::stoneydsp_int_t;

/**
 * @brief
 *
 */
constexpr ::stoneydsp::core::types::int_t int_max = ::stoneydsp_int_max;

/**
 * @brief
 *
 */
constexpr ::stoneydsp::core::types::int_t int_min = ::stoneydsp_int_min;

/// @} types
} // namespace types

/// @} group core
} //  namespace core

/// @} group stoneydsp

//=====================================================================//ALIASES

using ::stoneydsp::core::types::int_t;

using ::stoneydsp::core::types::int_min;

using ::stoneydsp::core::types::int_max;

} // namespace stoneydsp

  #endif // __cplusplus

//==============================================================================

#endif // STONEYDSP_CORE_TYPES_INT_H_INCLUDED

//=========================================================================//EOF
