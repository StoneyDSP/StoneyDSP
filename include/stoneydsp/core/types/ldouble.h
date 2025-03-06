/**
 * @file ldouble.h
 * @author StoneyDSP (nathanjhood@googlemail.com)
 * @brief
 * @version @STONEYDSP_CORE_VERSION@
 * @date 2025-01-27
 *
 * @copyright Copyright (c) 2025
 *
 */

#pragma once

#ifndef STONEYDSP_CORE_TYPES_LDBL_H_INCLUDED
  #define STONEYDSP_CORE_TYPES_LDBL_H_INCLUDED

//==============================================================================

  #include "../../../stoneydsp/core/system/types.h"

//==============================================================================

/**
 * @brief
 *
 */
typedef STONEYDSP_LDBL_T stoneydsp_ldouble_t;

//==============================================================================

  /**
   * @brief
   *
   */
  #define stoneydsp_ldouble stoneydsp_ldouble_t

//==============================================================================

typedef stoneydsp_ldouble stoneydsp_ldouble;

//==============================================================================

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_LDBL_T
    STONEYDSP_PUBLIC_FUNCTION
    /**
     * @brief
     *
     * @param value
     * @return `stoneydsp_ldouble_t`
     */
    stoneydsp_ldouble_c (long double value) STONEYDSP_NOEXCEPT
{
  return STONEYDSP_LDBL_C (value);
}

//==============================================================================

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_LDBL_T
    STONEYDSP_PUBLIC_FUNCTION
    /**
     * @brief
     *
     * @return `stoneydsp_ldouble_t`
     */
    stoneydsp_ldouble_max () STONEYDSP_NOEXCEPT
{
  return stoneydsp_ldouble_c (STONEYDSP_LDBL_MAX);
}

//==============================================================================

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_LDBL_T
    STONEYDSP_PUBLIC_FUNCTION
    /**
     * @brief
     *
     * @return `stoneydsp_ldouble_t`
     */
    stoneydsp_ldouble_min () STONEYDSP_NOEXCEPT
{
  return stoneydsp_ldouble_c (STONEYDSP_LDBL_MIN);
}

//==============================================================================

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_LDBL_T
    STONEYDSP_PUBLIC_FUNCTION
    /**
     * @brief
     *
     * @return `stoneydsp_ldouble_t`
     */
    stoneydsp_ldouble_lowest () STONEYDSP_NOEXCEPT
{
  return stoneydsp_ldouble_c (-STONEYDSP_LDBL_MAX);
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
using ldouble_t = stoneydsp_ldouble;

//==============================================================================

namespace literals
{
/** @addtogroup literals
 * @{
 */

//==============================================================================

STONEYDSP_INLINE
STONEYDSP_CONSTEXPR STONEYDSP_LDBL_T STONEYDSP_PUBLIC_FUNCTION
/**
 * @brief
 *
 * @param value
 * @return `stoneydsp::ldouble_t`
 */
operator"" _ldouble_t (long double value) STONEYDSP_NOEXCEPT
{
  return ::stoneydsp_ldouble_c (value);
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
STONEYDSP_ALIGN (alignof (STONEYDSP_LDBL_T)) numeric_limits<STONEYDSP_LDBL_T>
{

  STONEYDSP_INLINE static STONEYDSP_CONSTEXPR STONEYDSP_LDBL_T STONEYDSP_API
  max () STONEYDSP_NOEXCEPT
  {
    return ::stoneydsp_ldouble_max ();
  }

  STONEYDSP_INLINE static STONEYDSP_CONSTEXPR STONEYDSP_LDBL_T STONEYDSP_API
  min () STONEYDSP_NOEXCEPT
  {
    return ::stoneydsp_ldouble_min ();
  }

  STONEYDSP_INLINE static STONEYDSP_CONSTEXPR STONEYDSP_LDBL_T STONEYDSP_API
  lowest () STONEYDSP_NOEXCEPT
  {
    return ::stoneydsp_ldouble_lowest ();
  }

} STONEYDSP_PACKED_STRUCT_END;

//==============================================================================

/// @} group stoneydsp
} //  namespace stoneydsp

  #endif // STONEYDSP_CXX

//==============================================================================

#endif // STONEYDSP_CORE_TYPES_LDBL_H_INCLUDED

//=========================================================================//EOF
