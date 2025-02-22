/**
 * @file ptrdiff.h
 * @author StoneyDSP (nathanjhood@googlemail.com)
 * @brief
 * @version @STONEYDSP_CORE_VERSION@
 * @date 2025-01-30
 *
 * @copyright Copyright (c) 2025
 *
 */

#pragma once

#ifndef STONEYDSP_CORE_TYPES_PTRDIFF_H_INCLUDED
  #define STONEYDSP_CORE_TYPES_PTRDIFF_H_INCLUDED

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
     * @brief Signed integer type returned when subtracting two pointers.
     *
     * @see https://en.cppreference.com/w/cpp/types/ptrdiff_t
     *
     */
    #define STONEYDSP_PTRDIFF_T ::std::ptrdiff_t

  #else // !__cplusplus

    /**
     * @brief Signed integer type returned when subtracting two pointers.
     *
     * @see https://en.cppreference.com/w/c/types/ptrdiff_t
     *
     */
    #define STONEYDSP_PTRDIFF_T ptrdiff_t

  #endif // __cplusplus

/**
 * @brief Minimum value of `stoneydsp_ptr_t`.
 *
 */
  #define STONEYDSP_PTRDIFF_MIN PTRDIFF_MIN

/**
 * @brief Maximum value of `stoneydsp_ptr_t`.
 *
 */
  #define STONEYDSP_PTRDIFF_MAX PTRDIFF_MAX

//====================================================================//TYPEDEFS

/**
 * @brief Signed integer type returned when subtracting two pointers.
 *
 */
typedef STONEYDSP_PTRDIFF_T stoneydsp_ptrdiff_t;

//===================================================================//CONSTANTS

  #ifdef __cplusplus

/**
 * @brief Minimum value of `stoneydsp::ptrdiff_t`.
 *
 * Expands to:
 *
 * `(-9223372036854775807L-1)`
 */
constexpr ::stoneydsp_ptrdiff_t stoneydsp_ptrdiff_min = STONEYDSP_PTRDIFF_MIN;

/**
 * @brief Maximum value of `stoneydsp::ptrdiff_t`.
 *
 * Expands to:
 *
 * `(9223372036854775807L)`
 */
constexpr ::stoneydsp_ptrdiff_t stoneydsp_ptrdiff_max = STONEYDSP_PTRDIFF_MAX;

  #else // !__cplusplus

/**
 * @brief Minimum value of `stoneydsp_ptrdiff_t`.
 *
 * Expands to:
 *
 * `(-9223372036854775807L-1)`
 */
static const stoneydsp_ptrdiff_t stoneydsp_ptrdiff_min = STONEYDSP_PTRDIFF_MIN;

/**
 * @brief Maximum value of `stoneydsp_ptrdiff_t`.
 *
 * Expands to:
 *
 * `(9223372036854775807L)`
 */
static const stoneydsp_ptrdiff_t stoneydsp_ptrdiff_max = STONEYDSP_PTRDIFF_MAX;

  #endif //  __cplusplus

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
 * @brief Signed integer type returned when subtracting two pointers.
 *
 */
using ptrdiff_t = ::stoneydsp_ptrdiff_t;

/**
 * @brief Minimum value of `stoneydsp::ptrdiff_t`.
 *
 * Expands to:
 *
 * `(-9223372036854775807L-1)`
 */
constexpr ::stoneydsp::core::types::ptrdiff_t ptrdiff_min
    = ::stoneydsp_ptrdiff_min;

/**
 * @brief Maximum value of `stoneydsp::ptrdiff_t`.
 *
 * Expands to:
 *
 * `(9223372036854775807L)`
 */
constexpr ::stoneydsp::core::types::ptrdiff_t ptrdiff_max
    = ::stoneydsp_ptrdiff_max;

/// @} types
} // namespace types

/// @} group core
} //  namespace core

/// @} group stoneydsp

//=====================================================================//ALIASES

using ::stoneydsp::core::types::ptrdiff_t;

using ::stoneydsp::core::types::ptrdiff_min;

using ::stoneydsp::core::types::ptrdiff_max;

} // namespace stoneydsp

  #endif // __cplusplus

//==============================================================================

#endif // STONEYDSP_CORE_TYPES_PTRDIFF_H_INCLUDED

//=========================================================================//EOF
