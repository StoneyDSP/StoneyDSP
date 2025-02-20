/**
 * @file math.h
 * @author StoneyDSP (nathanjhood@googlemail.com)
 * @brief
 * @version @STONEYDSP_CORE_VERSION@
 * @date 2025-01-30
 *
 * @copyright Copyright (c) 2025
 *
 */

#pragma once

#ifndef STONEYDSP_CORE_TYPES_MATH_H_INCLUDED
  #define STONEYDSP_CORE_TYPES_MATH_H_INCLUDED

//====================================================================//INCLUDES

  #ifdef __cplusplus
    #include <cmath>
  #else
    #include <math.h>
  #endif // __cplusplus

//=====================================================================//DEFINES

  #ifdef __cplusplus
    /**
     * @brief
     *
     */
    #define STONEYDSP_FLOAT_T ::std::float_t
    /**
     * @brief
     *
     */
    #define STONEYDSP_DOUBLE_T ::std::double_t
  #else // !__cplusplus
    /**
     * @brief
     *
     */
    #define STONEYDSP_FLOAT_T float_t
    /**
     * @brief
     *
     */
    #define STONEYDSP_DOUBLE_T double_t
  #endif // __cplusplus

//====================================================================//TYPEDEFS

/**
 * @brief
 *
 */
typedef STONEYDSP_FLOAT_T stoneydsp_float_t;

/**
 * @brief
 *
 */
typedef STONEYDSP_DOUBLE_T stoneydsp_double_t;

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
using float_t = ::stoneydsp_float_t;
/**
 * @brief
 *
 */
using double_t = ::stoneydsp_double_t;
} // namespace types
} // namespace core
} // namespace stoneydsp

  #endif // __cplusplus

//==============================================================================

  #ifdef __cplusplus

namespace stoneydsp
{
/**
 * @brief
 *
 */
using float_t = ::stoneydsp::core::types::float_t;
/**
 * @brief
 *
 */
using double_t = ::stoneydsp::core::types::double_t;
} // namespace stoneydsp

  #endif // __cplusplus

//==============================================================================

#endif // STONEYDSP_CORE_TYPES_MATH_H_INCLUDED

//=========================================================================//EOF
