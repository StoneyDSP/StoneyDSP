/**
 * @file schar.h
 * @author StoneyDSP (nathanjhood@googlemail.com)
 * @brief
 * @version @STONEYDSP_CORE_VERSION@
 * @date 2025-01-27
 *
 * @copyright Copyright (c) 2025
 *
 */

#pragma once

#ifndef STONEYDSP_CORE_TYPES_SCHAR_H_INCLUDED
  #define STONEYDSP_CORE_TYPES_SCHAR_H_INCLUDED

//==============================================================================

  #include "../../../stoneydsp/core/system/types.h"

//==============================================================================

/**
 * @brief
 *
 */
typedef STONEYDSP_SCHAR_T stoneydsp_schar_t;

//==============================================================================

  /**
   * @brief
   *
   */
  #define stoneydsp_schar stoneydsp_schar_t

//==============================================================================

typedef stoneydsp_schar stoneydsp_schar;

//==============================================================================

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_SCHAR_T
    STONEYDSP_PUBLIC_FUNCTION
    /**
     * @brief Cast or convert a `value` to a `stoneydsp_schar_t`.
     *
     * @param value
     * @return `stoneydsp_schar_t`
     */
    stoneydsp_schar_c (unsigned long long value) STONEYDSP_NOEXCEPT
{
  return STONEYDSP_SCHAR_C (value);
}

//==============================================================================

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_SCHAR_T
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
     * @return `stoneydsp_schar_t`
     *
     */
    stoneydsp_schar_max () STONEYDSP_NOEXCEPT
{
  return stoneydsp_schar_c (STONEYDSP_SCHAR_MAX);
}

//==============================================================================

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_SCHAR_T
    STONEYDSP_PUBLIC_FUNCTION
    /**
     * @brief
     *
     * @return `stoneydsp_schar_t`
     */
    stoneydsp_schar_min () STONEYDSP_NOEXCEPT
{
  return stoneydsp_schar_c ((-STONEYDSP_SCHAR_MAX)
                            - (STONEYDSP_SCHAR_LITERAL (1)));
}

//==============================================================================

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_SCHAR_T
    STONEYDSP_PUBLIC_FUNCTION
    /**
     * @brief
     *
     * @return `stoneydsp_schar_t`
     */
    stoneydsp_schar_lowest () STONEYDSP_NOEXCEPT
{
  return stoneydsp_schar_min ();
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
using schar_t = stoneydsp_schar;

//==============================================================================

namespace literals
{
/** @addtogroup literals
 * @{
 */

//==============================================================================

STONEYDSP_INLINE
STONEYDSP_CONSTEXPR STONEYDSP_SCHAR_T STONEYDSP_PUBLIC_FUNCTION
/**
 * @brief
 *
 * @param value
 *
 * @return `stoneydsp::schar_t`
 */
operator"" _schar_t (char value) STONEYDSP_NOEXCEPT
{
  return ::stoneydsp_schar_c (value);
}

//==============================================================================

STONEYDSP_INLINE
STONEYDSP_CONSTEXPR STONEYDSP_SCHAR_T STONEYDSP_PUBLIC_FUNCTION
/**
 * @brief
 *
 */
operator"" _schar_t (unsigned long long value) STONEYDSP_NOEXCEPT
{
  return ::stoneydsp_schar_c (value);
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
STONEYDSP_ALIGN (alignof (STONEYDSP_SCHAR_T)) numeric_limits<STONEYDSP_SCHAR_T>
{

  STONEYDSP_INLINE static STONEYDSP_CONSTEXPR STONEYDSP_SCHAR_T STONEYDSP_API
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
    return ::stoneydsp_schar_max ();
  }

  STONEYDSP_INLINE static STONEYDSP_CONSTEXPR STONEYDSP_SCHAR_T STONEYDSP_API
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
   * @return `stoneydsp::schar_t`
   *
   */
  min () STONEYDSP_NOEXCEPT
  {
    return ::stoneydsp_schar_min ();
  }

  STONEYDSP_INLINE static STONEYDSP_CONSTEXPR STONEYDSP_SCHAR_T STONEYDSP_API
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
   * @return `stoneydsp::schar_t`
   *
   */
  lowest () STONEYDSP_NOEXCEPT
  {
    return ::stoneydsp_schar_lowest ();
  }

} STONEYDSP_PACKED_STRUCT_END;

//==============================================================================

/// @} group stoneydsp
} //  namespace stoneydsp

  #endif // STONEYDSP_CXX

//==============================================================================

#endif // STONEYDSP_CORE_TYPES_SCHAR_H_INCLUDED

//=========================================================================//EOF
