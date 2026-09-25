/**
 * @file char.h
 * @author StoneyDSP (nathanjhood@googlemail.com)
 * @brief
 * @version @STONEYDSP_CORE_VERSION@
 * @date 2025-01-27
 *
 * @copyright Copyright (c) 2025
 *
 */

#pragma once

#ifndef STONEYDSP_CORE_TYPES_CHAR_H_INCLUDED
  #define STONEYDSP_CORE_TYPES_CHAR_H_INCLUDED

//==============================================================================

  #include "../../../stoneydsp/core/system/types.h"

//==============================================================================

/**
 * @brief
 *
 */
typedef STONEYDSP_CHAR_T stoneydsp_char_t;

//==============================================================================

  /**
   * @brief
   *
   */
  #define stoneydsp_char stoneydsp_char_t

//==============================================================================

typedef stoneydsp_char stoneydsp_char;

//==============================================================================

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_CHAR_T
    STONEYDSP_PUBLIC_FUNCTION
    /**
     * @brief Cast or convert a `value` to a `stoneydsp_char_t`.
     *
     * @param value
     *
     * @return `stoneydsp_char_t`
     */
    stoneydsp_char_c (unsigned long long value) STONEYDSP_NOEXCEPT
{
  return STONEYDSP_CHAR_C (value);
}

//==============================================================================

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_CHAR_T
    STONEYDSP_PUBLIC_FUNCTION
    /**
     * @brief
     *
     * Typically equivalent to:
     *
     * - dec: `127`
     *
     * - oct: `0177`
     *
     * - hex: `0x7F`
     *
     * @return `stoneydsp_char_t`
     *
     */
    stoneydsp_char_max () STONEYDSP_NOEXCEPT
{
  return stoneydsp_char_c (STONEYDSP_CHAR_MAX);
}

//==============================================================================

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_CHAR_T
    STONEYDSP_PUBLIC_FUNCTION
    stoneydsp_char_min () STONEYDSP_NOEXCEPT
{
  return stoneydsp_char_c (STONEYDSP_CHAR_MIN);
}

//==============================================================================

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_CHAR_T
    STONEYDSP_PUBLIC_FUNCTION
    stoneydsp_char_lowest () STONEYDSP_NOEXCEPT
{
  return stoneydsp_char_min ();
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
using char_t = stoneydsp_char;

//==============================================================================

namespace literals
{
/** @addtogroup literals
 * @{
 */

//==============================================================================

STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_CHAR_T STONEYDSP_PUBLIC_FUNCTION
/**
 * @brief
 *
 * @param value
 *
 * @return `stoneydsp::char_t`
 *
 */
operator"" _char_t (char value) STONEYDSP_NOEXCEPT
{
  return ::stoneydsp_char_c (value);
}

//==============================================================================

STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_CHAR_T STONEYDSP_PUBLIC_FUNCTION
/**
 * @brief
 *
 */
operator"" _char_t (unsigned long long value) STONEYDSP_NOEXCEPT
{
  return ::stoneydsp_char_c (value);
}

//==============================================================================

/// @} literals
} // namespace literals

/// @} types
} // namespace types

/// @} group core
} //  namespace core

//==============================================================================

template <>
STONEYDSP_PACKED_STRUCT_BEGIN struct STONEYDSP_API
STONEYDSP_ALIGN (alignof (STONEYDSP_CHAR_T)) numeric_limits<STONEYDSP_CHAR_T>
{

  STONEYDSP_INLINE static STONEYDSP_CONSTEXPR STONEYDSP_CHAR_T STONEYDSP_API
  /**
   * @brief
   *
   * Typically equivalent to:
   *
   * - dec: `127`
   *
   * - oct: `0177`
   *
   * - hex: `0x7F`
   *
   * @return `stoneydsp::char_t`
   *
   */
  max () STONEYDSP_NOEXCEPT
  {
    return ::stoneydsp_char_max ();
  }

  STONEYDSP_INLINE static STONEYDSP_CONSTEXPR STONEYDSP_CHAR_T STONEYDSP_API
  /**
   * @brief
   *
   * Typically equivalent to:
   *
   * - dec: `-128`
   *
   * - oct: `-0800`
   *
   * - hex: `-0x80`
   *
   * @return `stoneydsp::char_t`
   *
   */
  min () STONEYDSP_NOEXCEPT
  {
    return ::stoneydsp_char_min ();
  }

  STONEYDSP_INLINE static STONEYDSP_CONSTEXPR STONEYDSP_CHAR_T STONEYDSP_API
  lowest () STONEYDSP_NOEXCEPT
  {
    /**
     * @brief
     *
     * Typically equivalent to:
     *
     * - dec: `-128`
     *
     * - oct: `-0800`
     *
     * - hex: `-0x80`
     *
     * @return `stoneydsp::char_t`
     *
     */
    return ::stoneydsp_char_lowest ();
  }

} STONEYDSP_PACKED_STRUCT_END;

//==============================================================================

/// @} group stoneydsp
} //  namespace stoneydsp

  #endif // STONEYDSP_CXX

//==============================================================================

#endif // STONEYDSP_CORE_TYPES_CHAR_H_INCLUDED

//=========================================================================//EOF
