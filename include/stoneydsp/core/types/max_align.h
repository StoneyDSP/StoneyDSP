/**
 * @file max_align.h
 * @author StoneyDSP (nathanjhood@googlemail.com)
 * @brief
 * @version @STONEYDSP_CORE_VERSION@
 * @date 2025-01-30
 *
 * @copyright Copyright (c) 2025
 *
 */

#pragma once

#ifndef STONEYDSP_CORE_TYPES_MAX_ALIGN_H_INCLUDED
  #define STONEYDSP_CORE_TYPES_MAX_ALIGN_H_INCLUDED

//====================================================================//INCLUDES

  #ifdef __cplusplus
    #include <cstddef>
    #include <cstdint>
  #else
    #include <stddef.h>
    #include <stdint.h>
  #endif

//=====================================================================//DEFINES

  #ifdef __cplusplus

    /**
     * @brief Trivial type with alignment requirement as great as any other.
     * scalar type.
     *
     * @see https://en.cppreference.com/w/cpp/types/max_align_t
     *
     */
    #define STONEYDSP_MAX_ALIGN_T ::std::max_align_t

  #else // !__cplusplus

    /**
     * @brief Trivial type with alignment requirement as great as any other.
     * scalar type.
     *
     * @see https://en.cppreference.com/w/c/types/max_align_t
     *
     */
    #define STONEYDSP_MAX_ALIGN_T max_align_t

  #endif // __cplusplus

//====================================================================//TYPEDEFS

/**
 * @brief Trivial type with alignment requirement as great as any other
 * scalar type.
 *
 */
typedef STONEYDSP_MAX_ALIGN_T stoneydsp_max_align_t;

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
using max_align_t = ::stoneydsp_max_align_t;

/// @} types
} // namespace types

/// @} group core
} //  namespace core

/// @} group stoneydsp

//=====================================================================//ALIASES

using ::stoneydsp::core::types::max_align_t;

} // namespace stoneydsp

  #endif // __cplusplus

//==============================================================================

#endif // STONEYDSP_CORE_TYPES_MAX_ALIGN_H_INCLUDED

//=========================================================================//EOF
