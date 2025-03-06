/**
 * @file uint.h
 * @author StoneyDSP (nathanjhood@googlemail.com)
 * @brief
 * @version @STONEYDSP_CORE_VERSION@
 * @date 2025-01-27
 *
 * @copyright Copyright (c) 2025
 *
 */

#pragma once

#ifndef STONEYDSP_CORE_TYPES_UINT_H_INCLUDED
  #define STONEYDSP_CORE_TYPES_UINT_H_INCLUDED

//==============================================================================

  #include "../../../stoneydsp/core/system/types.h"

//==============================================================================

/**
 * @brief
 *
 */
typedef STONEYDSP_UINT_T stoneydsp_uint_t;

//==============================================================================

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_UINT_T
    STONEYDSP_PUBLIC_FUNCTION
    /**
     * @brief
     *
     * @param value
     * @return `stoneydsp_uint_t`
     */
    stoneydsp_uint_c (unsigned long long value) STONEYDSP_NOEXCEPT
{
  return STONEYDSP_UINT_C (value);
}

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_UINT_T
    STONEYDSP_PUBLIC_FUNCTION
    /**
     * @brief
     *
     * Guaranteed to be at least:
     *
     * - dec: `4294967295u`
     *
     * - oct: `037777777777u`
     *
     * - hex: `0xFFFFFFFFu`
     *
     * @return `stoneydsp_uint_t`
     *
     */
    stoneydsp_uint_max () STONEYDSP_NOEXCEPT
{
  return stoneydsp_uint_c ((stoneydsp_uint_c (STONEYDSP_INT_MAX))
                               * (STONEYDSP_UINT_LITERAL (2))
                           + (STONEYDSP_INT_LITERAL (1)));
}

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_UINT_T
    STONEYDSP_PUBLIC_FUNCTION
    /**
     * @brief
     *
     * @return `stoneydsp_uint_t`
     */
    stoneydsp_uint_min () STONEYDSP_NOEXCEPT
{
  return stoneydsp_uint_c (0U);
}

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_UINT_T
    STONEYDSP_PUBLIC_FUNCTION
    /**
     * @brief
     *
     * @return `stoneydsp_uint_t`
     */
    stoneydsp_uint_lowest () STONEYDSP_NOEXCEPT
{
  return stoneydsp_uint_min ();
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
using uint_t = ::stoneydsp_uint_t;

//==============================================================================

namespace literals
{
/** @addtogroup literals
 * @{
 */

STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_UINT_T STONEYDSP_PUBLIC_FUNCTION
/**
 * @brief
 *
 * @param value
 * @return `stoneydsp::uint_t`
 */
operator"" _uint_t (char value) STONEYDSP_NOEXCEPT
{
  return ::stoneydsp_uint_c (value);
}

STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_UINT_T STONEYDSP_PUBLIC_FUNCTION
/**
 * @brief
 *
 * @param value
 * @return `stoneydsp::uint_t`
 */
operator"" _uint_t (unsigned long long value) STONEYDSP_NOEXCEPT
{
  return ::stoneydsp_uint_c (value);
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
STONEYDSP_ALIGN (alignof (STONEYDSP_UINT_T)) numeric_limits<STONEYDSP_UINT_T>
{
  STONEYDSP_INLINE static STONEYDSP_CONSTEXPR STONEYDSP_UINT_T STONEYDSP_API
  max () STONEYDSP_NOEXCEPT
  {
    return ::stoneydsp_uint_max ();
  }

  STONEYDSP_INLINE static STONEYDSP_CONSTEXPR STONEYDSP_UINT_T STONEYDSP_API
  min () STONEYDSP_NOEXCEPT
  {
    return ::stoneydsp_uint_min ();
  }

  STONEYDSP_INLINE static STONEYDSP_CONSTEXPR STONEYDSP_UINT_T STONEYDSP_API
  lowest () STONEYDSP_NOEXCEPT
  {
    return ::stoneydsp_uint_lowest ();
  }

} STONEYDSP_PACKED_STRUCT_END;

//==============================================================================

/**
 * @brief
 *
 */
using uint_t = ::stoneydsp::core::types::uint_t;

//==============================================================================

/// @} group stoneydsp
} //  namespace stoneydsp

  //==============================================================================

  #endif // STONEYDSP_CXX

//==============================================================================

#endif // STONEYDSP_CORE_TYPES_UINT_H_INCLUDED

//=========================================================================//EOF
