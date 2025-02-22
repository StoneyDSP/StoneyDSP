/**
 * @file nullptr.h
 * @author StoneyDSP (nathanjhood@googlemail.com)
 * @brief
 * @version @STONEYDSP_CORE_VERSION@
 * @date 2025-01-30
 *
 * @copyright Copyright (c) 2025
 *
 */

#pragma once

#ifndef STONEYDSP_CORE_TYPES_NULLPTR_H_INCLUDED
  #define STONEYDSP_CORE_TYPES_NULLPTR_H_INCLUDED

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
     * @brief The type of the null pointer literal `nullptr`.
     *
     * @see https://en.cppreference.com/w/cpp/types/nullptr_t
     *
     */
    #define STONEYDSP_NULLPTR_T ::std::nullptr_t

  #else // !__cplusplus

    /**
     * @brief The type of the null pointer literal `nullptr`.
     *
     * @see https://en.cppreference.com/w/c/types/nullptr_t
     *
     */
    #define STONEYDSP_NULLPTR_T nullptr_t

  #endif // __cplusplus

  /**
   * @brief A null-pointer constant is either an integral constant expression
   * that evaluates to zero (such as `0` or `0L`), or a value of type
   * `nullptr_t` (such as `nullptr`).
   *
   */
  #define STONEYDSP_NULL NULL

//====================================================================//TYPEDEFS

/**
 * @brief The type of the null pointer literal `nullptr`.
 *
 */
typedef STONEYDSP_NULLPTR_T stoneydsp_nullptr_t;

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
using nullptr_t = ::stoneydsp_nullptr_t;

/// @} types
} // namespace types

/// @} group core
} //  namespace core

/// @} group stoneydsp

//=====================================================================//ALIASES

using ::stoneydsp::core::types::nullptr_t;

} // namespace stoneydsp

  #endif // __cplusplus

//==============================================================================

#endif // STONEYDSP_CORE_TYPES_NULLPTR_H_INCLUDED

//=========================================================================//EOF
