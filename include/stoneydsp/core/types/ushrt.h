/**
 * @file ushrt.h
 * @author StoneyDSP (nathanjhood@googlemail.com)
 * @brief
 * @version @STONEYDSP_CORE_VERSION@
 * @date 2025-01-27
 *
 * @copyright Copyright (c) 2025
 *
 */

#pragma once

#ifndef STONEYDSP_CORE_TYPES_USHRT_H_INCLUDED
  #define STONEYDSP_CORE_TYPES_USHRT_H_INCLUDED

//==============================================================================

  #include "../../../stoneydsp/core/system/types.h"

//==============================================================================

/**
 * @brief
 *
 */
typedef STONEYDSP_USHRT_T stoneydsp_ushrt_t;

//==============================================================================

  /**
   * @brief
   *
   */
  #define stoneydsp_ushrt stoneydsp_ushrt_t

//==============================================================================

typedef stoneydsp_ushrt stoneydsp_ushrt;

//==============================================================================

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_USHRT_T
    STONEYDSP_PUBLIC_FUNCTION
    stoneydsp_ushrt_c (unsigned long long value) STONEYDSP_NOEXCEPT
{
  return STONEYDSP_USHRT_C (value);
}

//==============================================================================

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_USHRT_T
    STONEYDSP_PUBLIC_FUNCTION
    /**
     * @brief
     *
     * Guaranteed to be at least:
     *
     * - dec: `65535u`
     *
     * - oct: `0177777u`
     *
     * - hex: `0xFFFFu`
     *
     * @return `stoneydsp_ushrt_t`
     *
     */
    stoneydsp_ushrt_max () STONEYDSP_NOEXCEPT
{
  return stoneydsp_ushrt_c (
      (stoneydsp_ushrt_c (STONEYDSP_SHRT_MAX))
          * (stoneydsp_ushrt_c (STONEYDSP_USHRT_LITERAL (02)))
      + (stoneydsp_ushrt_c (STONEYDSP_USHRT_LITERAL (01))));
}

//==============================================================================

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_USHRT_T
    STONEYDSP_PUBLIC_FUNCTION
    /**
     * @brief
     *
     * Equivalent to:
     *
     * - hex: `0`
     *
     * - oct: `000000`
     *
     */
    stoneydsp_ushrt_min () STONEYDSP_NOEXCEPT
{
  return stoneydsp_ushrt_c (STONEYDSP_USHRT_LITERAL (00));
}

//==============================================================================

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_USHRT_T
    STONEYDSP_PUBLIC_FUNCTION
    stoneydsp_ushrt_lowest () STONEYDSP_NOEXCEPT
{
  return stoneydsp_ushrt_min ();
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
using ushrt_t = stoneydsp_ushrt;

//==============================================================================

namespace literals
{
/** @addtogroup literals
 * @{
 */

//==============================================================================

STONEYDSP_INLINE
STONEYDSP_CONSTEXPR STONEYDSP_USHRT_T STONEYDSP_PUBLIC_FUNCTION
/**
 * @brief
 *
 * @param value
 * @return `stoneydsp::ushrt_t`
 */
operator"" _ushrt_t (char value) STONEYDSP_NOEXCEPT
{
  return ::stoneydsp_ushrt_c (value);
}

//==============================================================================

STONEYDSP_INLINE
STONEYDSP_CONSTEXPR STONEYDSP_USHRT_T STONEYDSP_PUBLIC_FUNCTION
/**
 * @brief
 *
 * @param value
 * @return `stoneydsp::ushrt_t`
 */
operator"" _ushrt_t (unsigned long long value) STONEYDSP_NOEXCEPT
{
  return ::stoneydsp_ushrt_c (value);
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
STONEYDSP_ALIGN (alignof (STONEYDSP_USHRT_T)) numeric_limits<STONEYDSP_USHRT_T>
{

  STONEYDSP_INLINE static STONEYDSP_CONSTEXPR STONEYDSP_USHRT_T STONEYDSP_API
  min () STONEYDSP_NOEXCEPT
  {
    return ::stoneydsp_ushrt_min ();
  }

  STONEYDSP_INLINE static STONEYDSP_CONSTEXPR STONEYDSP_USHRT_T STONEYDSP_API
  max () STONEYDSP_NOEXCEPT
  {
    return ::stoneydsp_ushrt_max ();
  }

  STONEYDSP_INLINE static STONEYDSP_CONSTEXPR STONEYDSP_USHRT_T STONEYDSP_API
  lowest () STONEYDSP_NOEXCEPT
  {
    return ::stoneydsp_ushrt_lowest ();
  }

} STONEYDSP_PACKED_STRUCT_END;

//==============================================================================

/// @} group stoneydsp
} //  namespace stoneydsp

  #endif // STONEYDSP_CXX

//==============================================================================

#endif // STONEYDSP_CORE_TYPES_USHRT_H_INCLUDED

//=========================================================================//EOF
