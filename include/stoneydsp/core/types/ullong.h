/**
 * @file ullong.h
 * @author StoneyDSP (nathanjhood@googlemail.com)
 * @brief
 * @version @STONEYDSP_CORE_VERSION@
 * @date 2025-01-27
 *
 * @copyright Copyright (c) 2025
 *
 */

#pragma once

#ifndef STONEYDSP_CORE_TYPES_ULLONG_H_INCLUDED
  #define STONEYDSP_CORE_TYPES_ULLONG_H_INCLUDED

//==============================================================================

  #include "../../../stoneydsp/core/system/types.h"

//==============================================================================

/**
 * @brief
 *
 */
typedef STONEYDSP_ULLONG_T stoneydsp_ullong_t;

//==============================================================================

  /**
   * @brief
   *
   */
  #define stoneydsp_ullong stoneydsp_ullong_t

//==============================================================================

typedef stoneydsp_ullong stoneydsp_ullong;

//==============================================================================

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_ULLONG_T
    STONEYDSP_PUBLIC_FUNCTION
    /**
     * @brief
     *
     * @param value
     * @return `stoneydsp_ullong_t`
     */
    stoneydsp_ullong_c (unsigned long long value) STONEYDSP_NOEXCEPT
{
  return STONEYDSP_ULLONG_C (value);
}

//==============================================================================

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_ULLONG_T
    STONEYDSP_PUBLIC_FUNCTION
    /**
     * @brief
     *
     * @return `stoneydsp_ullong_t`
     */
    stoneydsp_ullong_max () STONEYDSP_NOEXCEPT
{
  return stoneydsp_ullong_c (
      (stoneydsp_ullong_c (STONEYDSP_LLONG_MAX))
          * (stoneydsp_ullong_c (STONEYDSP_ULLONG_LITERAL (2)))
      + (stoneydsp_ullong_c (STONEYDSP_ULLONG_LITERAL (1))));
}

//==============================================================================

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_ULLONG_T
    STONEYDSP_PUBLIC_FUNCTION
    /**
     * @brief
     *
     * @return `stoneydsp_ullong_t`
     */
    stoneydsp_ullong_min () STONEYDSP_NOEXCEPT
{
  return stoneydsp_ullong_c (STONEYDSP_ULLONG_LITERAL (0));
}

//==============================================================================

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_ULLONG_T
    STONEYDSP_PUBLIC_FUNCTION
    /**
     * @brief
     *
     * @return `stoneydsp_ullong_t`
     */
    stoneydsp_ullong_lowest () STONEYDSP_NOEXCEPT
{
  return stoneydsp_ullong_min ();
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
using ullong_t = stoneydsp_ullong;

//==============================================================================

namespace literals
{
/** @addtogroup literals
 * @{
 */

//==============================================================================

STONEYDSP_INLINE
STONEYDSP_CONSTEXPR STONEYDSP_ULLONG_T STONEYDSP_PUBLIC_FUNCTION
/**
 * @brief
 *
 * @param value
 * @return `stoneydsp::ullong_t`
 */
operator"" _ullong_t (char value) STONEYDSP_NOEXCEPT
{
  return ::stoneydsp_ullong_c (value);
}

//==============================================================================

STONEYDSP_INLINE
STONEYDSP_CONSTEXPR STONEYDSP_ULLONG_T STONEYDSP_PUBLIC_FUNCTION
/**
 * @brief
 *
 * @param value
 * @return `stoneydsp::ullong_t`
 */
operator"" _ullong_t (unsigned long long value) STONEYDSP_NOEXCEPT
{
  return ::stoneydsp_ullong_c (value);
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
STONEYDSP_ALIGN (alignof (STONEYDSP_ULLONG_T))
    numeric_limits<STONEYDSP_ULLONG_T>
{

  STONEYDSP_INLINE static STONEYDSP_CONSTEXPR STONEYDSP_ULLONG_T STONEYDSP_API
  max () STONEYDSP_NOEXCEPT
  {
    return ::stoneydsp_ullong_max ();
  }

  STONEYDSP_INLINE static STONEYDSP_CONSTEXPR STONEYDSP_ULLONG_T STONEYDSP_API
  min () STONEYDSP_NOEXCEPT
  {
    return ::stoneydsp_ullong_min ();
  }

  STONEYDSP_INLINE static STONEYDSP_CONSTEXPR STONEYDSP_ULLONG_T STONEYDSP_API
  lowest () STONEYDSP_NOEXCEPT
  {
    return ::stoneydsp_ullong_lowest ();
  }

} STONEYDSP_PACKED_STRUCT_END;

//==============================================================================

/// @} group stoneydsp
} //  namespace stoneydsp

  #endif // STONEYDSP_CXX

//==============================================================================

#endif // STONEYDSP_CORE_TYPES_ULLONG_H_INCLUDED

//=========================================================================//EOF
