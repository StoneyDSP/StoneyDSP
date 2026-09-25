/**
 * @file bool.h
 * @author StoneyDSP (nathanjhood@googlemail.com)
 * @brief
 * @version @STONEYDSP_CORE_VERSION@
 * @date 2025-01-27
 *
 * @copyright Copyright (c) 2025
 *
 */

#pragma once

#ifndef STONEYDSP_CORE_TYPES_BOOL_H_INCLUDED
  #define STONEYDSP_CORE_TYPES_BOOL_H_INCLUDED

//==============================================================================

  #include "../../../stoneydsp/core/system/types.h"

//==============================================================================

/**
 * @brief
 *
 */
typedef STONEYDSP_BOOL_T stoneydsp_bool_t;

//==============================================================================

  /**
   * @brief
   *
   */
  #define stoneydsp_bool stoneydsp_bool_t

//==============================================================================

typedef stoneydsp_bool stoneydsp_bool;

//==============================================================================

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_BOOL_T
    STONEYDSP_PUBLIC_FUNCTION
    stoneydsp_bool_c (STONEYDSP_BOOL_T value) STONEYDSP_NOEXCEPT
{
  return STONEYDSP_BOOL_C (value);
}

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_BOOL_T
    STONEYDSP_PUBLIC_FUNCTION
    /**
     * @brief
     *
     * Equivalent to:
     *
     * - bool: `true`
     *
     * - char: `1U`
     *
     * @return `stoneydsp_bool_t`
     *
     */
    stoneydsp_bool_max () STONEYDSP_NOEXCEPT
{
  return stoneydsp_bool_c (STONEYDSP_BOOL_MAX);
}

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_BOOL_T
    STONEYDSP_PUBLIC_FUNCTION
    stoneydsp_bool_min () STONEYDSP_NOEXCEPT
{
  return stoneydsp_bool_c (STONEYDSP_BOOL_MIN);
}

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_BOOL_T
    STONEYDSP_PUBLIC_FUNCTION
    stoneydsp_bool_lowest () STONEYDSP_NOEXCEPT
{
  return stoneydsp_bool_min ();
}

//==============================================================================

  #ifdef STONEYDSP_CXX

//==============================================================================

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
 * @{
 */

//==============================================================================

/**
 * @brief
 *
 */
using bool_t = stoneydsp_bool;

//==============================================================================

namespace literals
{
/** @addtogroup literals
 * @{
 */

STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_BOOL_T STONEYDSP_PUBLIC_FUNCTION
/**
 * @brief
 *
 * @param value
 * @return `stoneydsp::bool_t`
 */
operator"" _bool_t (char value) STONEYDSP_NOEXCEPT
{
  return ::stoneydsp_bool_c (value);
}

STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_BOOL_T STONEYDSP_PUBLIC_FUNCTION
/**
 * @brief
 *
 * @param value
 * @return `stoneydsp::bool_t`
 */
operator"" _bool_t (unsigned long long value) STONEYDSP_NOEXCEPT
{
  return ::stoneydsp_bool_c (value);
}

/// @} literals
} // namespace literals

/// @} types
} // namespace types

/// @} group core
} //  namespace core

//==============================================================================

template <>
STONEYDSP_PACKED_STRUCT_BEGIN struct STONEYDSP_API
STONEYDSP_ALIGN (alignof (STONEYDSP_BOOL_T)) numeric_limits<STONEYDSP_BOOL_T>
{

  STONEYDSP_INLINE static STONEYDSP_CONSTEXPR STONEYDSP_BOOL_T STONEYDSP_API
  /**
   * @brief
   *
   * Equivalent to:
   *
   * - bool: `true`
   *
   * - char: `1U`
   *
   * @return `stoneydsp::bool_t`
   */
  max () STONEYDSP_NOEXCEPT
  {
    return ::stoneydsp_bool_max ();
  }

  STONEYDSP_INLINE static STONEYDSP_CONSTEXPR STONEYDSP_BOOL_T STONEYDSP_API
  /**
   * @brief
   *
   * Equivalent to:
   *
   * - bool: `false`
   *
   * - char: `0U`
   *
   * @return `stoneydsp::bool_t`
   */
  min () STONEYDSP_NOEXCEPT
  {
    return ::stoneydsp_bool_min ();
  }

  STONEYDSP_INLINE static STONEYDSP_CONSTEXPR STONEYDSP_BOOL_T STONEYDSP_API
  /**
   * @brief
   *
   * Equivalent to:
   *
   * - bool: `false`
   *
   * - char: `0U`
   *
   * @return `stoneydsp::bool_t`
   */
  lowest () STONEYDSP_NOEXCEPT
  {
    return ::stoneydsp_bool_lowest ();
  }

} STONEYDSP_PACKED_STRUCT_END;

//==============================================================================

/// @} group stoneydsp
} //  namespace stoneydsp

  //==============================================================================

  #endif // STONEYDSP_CXX

//==============================================================================

#endif // STONEYDSP_CORE_TYPES_BOOL_H_INCLUDED

//=========================================================================//EOF
