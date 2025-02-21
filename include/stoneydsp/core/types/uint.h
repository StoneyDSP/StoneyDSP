/**
 * @file uint.h
 * @author StoneyDSP (nathanjhood@googlemail.com)
 * @brief
 * @version @STONEYDSP_CORE_VERSION@
 * @date 2025-01-30
 *
 * @copyright Copyright (c) 2025
 *
 */

#pragma once

#ifndef STONEYDSP_CORE_TYPES_UINT_H_INCLUDED
  #define STONEYDSP_CORE_TYPES_UINT_H_INCLUDED

//====================================================================//INCLUDES

  #ifdef __cplusplus
    #include <climits>
  #else // !__cplusplus
    #include <limits.h>
  #endif // __cplusplus

//=====================================================================//DEFINES

  /**
   * @brief
   *
   */
  #define STONEYDSP_UINT_T unsigned int

// Maximum constraints

  #define STONEYDSP_UINT_MAX UINT_MAX

//====================================================================//TYPEDEFS

typedef STONEYDSP_UINT_T stoneydsp_uint_t;

//===================================================================//CONSTANTS

  #ifdef __cplusplus
constexpr ::stoneydsp_uint_t stoneydsp_uint_max = STONEYDSP_UINT_MAX;
  #else  // !__cplusplus
static const stoneydsp_uint_t stoneydsp_uint_max = STONEYDSP_UINT_MAX;
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
using uint_t = ::stoneydsp_uint_t;
constexpr ::stoneydsp::core::types::uint_t uint_max = ::stoneydsp_uint_max;
} // namespace types
} // namespace core
} // namespace stoneydsp

  #endif // __cplusplus

//==============================================================================

  #ifdef __cplusplus

namespace stoneydsp
{
using ::stoneydsp::core::types::uint_max;
using ::stoneydsp::core::types::uint_t;
} // namespace stoneydsp

  #endif // __cplusplus

//==============================================================================

#endif // STONEYDSP_CORE_TYPES_UINT_H_INCLUDED

//=========================================================================//EOF
