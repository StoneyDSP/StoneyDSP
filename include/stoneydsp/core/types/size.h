/**
 * @file size.h
 * @author StoneyDSP (nathanjhood@googlemail.com)
 * @brief
 * @version @STONEYDSP_CORE_VERSION@
 * @date 2025-01-30
 *
 * @copyright Copyright (c) 2025
 *
 */

#pragma once

#ifndef STONEYDSP_CORE_TYPES_SIZE_H_INCLUDED
  #define STONEYDSP_CORE_TYPES_SIZE_H_INCLUDED

//====================================================================//INCLUDES

  #ifdef __cplusplus
    #include <cstddef>
    #include <cstdint>
  #else
    #include <stddef.h>
    #include <stdint.h>
  #endif // __cplusplus

//=====================================================================//DEFINES

  #ifdef __cplusplus
  /**
   * @brief
   *
   */
    #define STONEYDSP_SIZE_T ::std::size_t
  #else // !__cplusplus
    /**
     * @brief
     *
     */
    #define STONEYDSP_SIZE_T size_t
  #endif // __cplusplus

// Maximum constraints

  /**
   * @brief Maximum value of exact-width unsigned type `stoneydsp_size_t`.
   *
   */
  #define STONEYDSP_SIZE_MAX SIZE_MAX

//====================================================================//TYPEDEFS

/**
 * @brief
 *
 */
typedef STONEYDSP_SIZE_T stoneydsp_size_t;

//===================================================================//CONSTANTS

  #ifdef __cplusplus
/**
 * @brief Maximum value of exact-width unsigned type `stoneydsp_size_t`.
 *
 * On most systems, this is equivalent to:
 *
 * `(18446744073709551615UL)`
 */
constexpr ::stoneydsp_size_t stoneydsp_size_max = STONEYDSP_SIZE_MAX;
  #else  // !__cplusplus
/**
 * @brief Maximum value of exact-width unsigned type `stoneydsp_size_t`.
 *
 * On most systems, this is equivalent to:
 *
 * `(18446744073709551615UL)`
 */
static const stoneydsp_size_t stoneydsp_size_max = STONEYDSP_SIZE_MAX;
  #endif // __cplusplus

//===================================================================//NAMESPACE

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
using size_t = ::stoneydsp_size_t;
/**
 * @brief Maximum value of exact-width unsigned type `stoneydsp_size_t`.
 *
 * On most systems, this is equivalent to:
 *
 * `(18446744073709551615UL)`
 */
constexpr ::stoneydsp::core::types::size_t size_max = ::stoneydsp_size_max;
} // namespace types
} // namespace core
} // namespace stoneydsp

  #endif // __cplusplus

//=====================================================================//ALIASES

  #ifdef __cplusplus

namespace stoneydsp
{
using ::stoneydsp::core::types::size_max;
using ::stoneydsp::core::types::size_t;
} // namespace stoneydsp

  #endif // __cplusplus

//==============================================================================

#endif // STONEYDSP_CORE_TYPES_SIZE_H_INCLUDED

//=========================================================================//EOF
