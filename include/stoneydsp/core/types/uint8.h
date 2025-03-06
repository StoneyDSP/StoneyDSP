/**
 * @file uint8.h
 * @author StoneyDSP (nathanjhood@googlemail.com)
 * @brief
 * @version @STONEYDSP_CORE_VERSION@
 * @date 2025-01-27
 *
 * @copyright Copyright (c) 2025
 *
 */

#pragma once

#ifndef STONEYDSP_CORE_TYPES_UINT8_H_INCLUDED
  #define STONEYDSP_CORE_TYPES_UINT8_H_INCLUDED

//==============================================================================

  #include "../../../stoneydsp/core/system/types.h"

//==============================================================================

  #ifndef STONEYDSP_CORE_TYPES_UCHAR_H_INCLUDED
    #include "../../../stoneydsp/core/types/uchar.h" // for numerical_limits<uchar_t>
  #endif

//==============================================================================

/**
 * @brief
 *
 */
typedef STONEYDSP_UINT8_T stoneydsp_uint8_t;

//==============================================================================

/**
 * @brief
 *
 */
  #define stoneydsp_uint8 stoneydsp_uint8_t

//==============================================================================

typedef stoneydsp_uint8 stoneydsp_uint8;

//==============================================================================

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_UINT8_T
    STONEYDSP_PUBLIC_FUNCTION
    stoneydsp_uint8_c (unsigned long long value) STONEYDSP_NOEXCEPT
{
  return STONEYDSP_UINT8_C (value);
}

//==============================================================================

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_UINT8_T
    STONEYDSP_PUBLIC_FUNCTION
    /**
     * @brief
     *
     * Equivalent to:
     *
     * - dec: `255`
     *
     * - oct: `0377`
     *
     * - hex: `0xFF`
     *
     * @return `stoneydsp_uint8_t`
     *
     */
    stoneydsp_uint8_max () STONEYDSP_NOEXCEPT
{
  return stoneydsp_uint8_c (
      stoneydsp_uint8_c (STONEYDSP_INT8_MAX)
          * (stoneydsp_uint8_c (STONEYDSP_UINT8_LITERAL (02)))
      + (stoneydsp_uint8_c (STONEYDSP_UINT8_LITERAL (01))));
}

//==============================================================================

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_UINT8_T
    STONEYDSP_PUBLIC_FUNCTION
    /**
     * @brief
     *
     * Equivalent to:
     *
     * - dec: `0`
     *
     * - oct: `00`
     *
     * - hex: `0x00`
     *
     * @return `stoneydsp_uint8_t`
     *
     */
    stoneydsp_uint8_min () STONEYDSP_NOEXCEPT
{
  return stoneydsp_uint8_c (STONEYDSP_UINT8_LITERAL (00));
}

//==============================================================================

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_UINT8_T
    STONEYDSP_PUBLIC_FUNCTION
    stoneydsp_uint8_lowest () STONEYDSP_NOEXCEPT
{
  return stoneydsp_uint8_min ();
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
using uint8_t = stoneydsp_uint8;

//==============================================================================

namespace literals
{
/** @addtogroup literals
 * @{
 */

STONEYDSP_INLINE
STONEYDSP_CONSTEXPR STONEYDSP_UINT8_T STONEYDSP_PUBLIC_FUNCTION
/**
 * @brief
 *
 * @param value
 *
 * @return `stoneydsp::uint8_t`
 *
 */
operator"" _uint8_t (char value) STONEYDSP_NOEXCEPT
{
  return ::stoneydsp_uint8_c (value);
}

//==============================================================================

STONEYDSP_INLINE
STONEYDSP_CONSTEXPR STONEYDSP_UINT8_T STONEYDSP_PUBLIC_FUNCTION
/**
 * @brief
 *
 */
operator"" _uint8_t (unsigned long long value) STONEYDSP_NOEXCEPT
{
  return ::stoneydsp_uint8_c (value);
}

//==============================================================================

/// @} literals
} // namespace literals

/// @} types
} // namespace types

/// @} group core
} //  namespace core

/// @} group stoneydsp
} // namespace stoneydsp

  #endif // STONEYDSP_CXX

//==============================================================================

#endif // STONEYDSP_CORE_TYPES_UINT8_H_INCLUDED

//=========================================================================//EOF
