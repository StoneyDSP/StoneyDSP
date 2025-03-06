/**
 * @file uchar.h
 * @author StoneyDSP (nathanjhood@googlemail.com)
 * @brief
 * @version @STONEYDSP_CORE_VERSION@
 * @date 2025-01-27
 *
 * @copyright Copyright (c) 2025
 *
 */

#pragma once

#ifndef STONEYDSP_CORE_TYPES_UCHAR_H_INCLUDED
  #define STONEYDSP_CORE_TYPES_UCHAR_H_INCLUDED

//==============================================================================

  #include "../../../stoneydsp/core/system/types.h"

//==============================================================================

/**
 * @brief
 *
 */
typedef STONEYDSP_UCHAR_T stoneydsp_uchar_t;

//==============================================================================

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_UCHAR_T
    STONEYDSP_PUBLIC_FUNCTION
    /**
     * @brief Cast or convert a `value` to a `stoneydsp_uchar_t`.
     *
     * @param value
     * @return `stoneydsp_uchar_t`
     */
    stoneydsp_uchar_c (unsigned long long value) STONEYDSP_NOEXCEPT
{
  return STONEYDSP_UCHAR_C (value);
}

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_UCHAR_T
    STONEYDSP_PUBLIC_FUNCTION
    /**
     * @brief
     *
     * Typically equivalent to:
     *
     * - dec: `255u`
     *
     * - oct: `0377u`
     *
     * - hex: `0xFFu`
     *
     * @return `stoneydsp_uchar_t`
     */
    stoneydsp_uchar_max () STONEYDSP_NOEXCEPT
{
  return stoneydsp_uchar_c ((STONEYDSP_UCHAR_C (STONEYDSP_SCHAR_MAX))
                                * (STONEYDSP_UCHAR_LITERAL (2))
                            + (STONEYDSP_UCHAR_LITERAL (1)));
}

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_UCHAR_T
    STONEYDSP_PUBLIC_FUNCTION
    /**
     * @brief
     *
     * @return `stoneydsp_uchar_t`
     */
    stoneydsp_uchar_min () STONEYDSP_NOEXCEPT
{
  return stoneydsp_uchar_c (STONEYDSP_UCHAR_LITERAL (0));
}

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_UCHAR_T
    STONEYDSP_PUBLIC_FUNCTION
    /**
     * @brief
     *
     * @return `stoneydsp_uchar_t`
     */
    stoneydsp_uchar_lowest () STONEYDSP_NOEXCEPT
{
  return stoneydsp_uchar_min ();
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
using uchar_t = ::stoneydsp_uchar_t;

//==============================================================================

namespace literals
{
/** @addtogroup literals
 * @{
 */

STONEYDSP_INLINE
STONEYDSP_CONSTEXPR STONEYDSP_UCHAR_T STONEYDSP_PUBLIC_FUNCTION
/**
 * @brief
 *
 * @param value
 *
 * @return `stoneydsp::uchar_t`
 */
operator"" _uchar_t (char value) STONEYDSP_NOEXCEPT
{
  return ::stoneydsp_uchar_c (value);
}

STONEYDSP_INLINE
STONEYDSP_CONSTEXPR STONEYDSP_UCHAR_T STONEYDSP_PUBLIC_FUNCTION
/**
 * @brief
 *
 */
operator"" _uchar_t (unsigned long long value) STONEYDSP_NOEXCEPT
{
  return ::stoneydsp_uchar_c (value);
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
STONEYDSP_ALIGN (alignof (STONEYDSP_UCHAR_T)) numeric_limits<STONEYDSP_UCHAR_T>
{

  STONEYDSP_INLINE static STONEYDSP_CONSTEXPR STONEYDSP_UCHAR_T STONEYDSP_API
  max () STONEYDSP_NOEXCEPT
  {
    return ::stoneydsp_uchar_max ();
  }

  STONEYDSP_INLINE static STONEYDSP_CONSTEXPR STONEYDSP_UCHAR_T STONEYDSP_API
  min () STONEYDSP_NOEXCEPT
  {
    return ::stoneydsp_uchar_min ();
  }

  STONEYDSP_INLINE static STONEYDSP_CONSTEXPR STONEYDSP_UCHAR_T STONEYDSP_API
  lowest () STONEYDSP_NOEXCEPT
  {
    return ::stoneydsp_uchar_lowest ();
  }

} STONEYDSP_PACKED_STRUCT_END;

//==============================================================================

/**
 * @brief
 *
 */
using uchar_t = ::stoneydsp::core::types::uchar_t;

//==============================================================================

/// @} group stoneydsp
} //  namespace stoneydsp

  //==============================================================================

  #endif // STONEYDSP_CXX

//==============================================================================

#endif // STONEYDSP_CORE_TYPES_UCHAR_H_INCLUDED

//=========================================================================//EOF
