/**
 * @file llong.h
 * @author StoneyDSP (nathanjhood@googlemail.com)
 * @brief
 * @version @STONEYDSP_CORE_VERSION@
 * @date 2025-01-27
 *
 * @copyright Copyright (c) 2025
 *
 */

#pragma once

#ifndef STONEYDSP_CORE_TYPES_LLONG_H_INCLUDED
  #define STONEYDSP_CORE_TYPES_LLONG_H_INCLUDED

//==============================================================================

  #include "../../../stoneydsp/core/system/types.h"

//==============================================================================

/**
 * @brief
 *
 */
typedef STONEYDSP_LLONG_T stoneydsp_llong_t;

//==============================================================================

  /**
   * @brief
   *
   */
  #define stoneydsp_llong stoneydsp_llong_t

//==============================================================================

typedef stoneydsp_llong stoneydsp_llong;

//==============================================================================

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_LLONG_T
    STONEYDSP_PUBLIC_FUNCTION
    /**
     * @brief
     *
     * @param value
     * @return `stoneydsp_llong_t`
     */
    stoneydsp_llong_c (unsigned long long value) STONEYDSP_NOEXCEPT
{
  return STONEYDSP_LLONG_C (value);
}

//==============================================================================

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_LLONG_T
    STONEYDSP_PUBLIC_FUNCTION
    /**
     * @brief
     *
     * @return `stoneydsp_llong_t`
     */
    stoneydsp_llong_max () STONEYDSP_NOEXCEPT
{
  return stoneydsp_llong_c (STONEYDSP_LLONG_MAX);
}

//==============================================================================

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_LLONG_T
    STONEYDSP_PUBLIC_FUNCTION
    /**
     * @brief
     *
     * @return `stoneydsp_llong_t`
     */
    stoneydsp_llong_min () STONEYDSP_NOEXCEPT
{
  return stoneydsp_llong_c ((-STONEYDSP_LLONG_MAX)
                            - (STONEYDSP_LLONG_LITERAL (1)));
}

//==============================================================================

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_LLONG_T
    STONEYDSP_PUBLIC_FUNCTION
    /**
     * @brief
     *
     * @return `stoneydsp_llong_t`
     */
    stoneydsp_llong_lowest () STONEYDSP_NOEXCEPT
{
  return stoneydsp_llong_min ();
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
using llong_t = stoneydsp_llong;

//==============================================================================

namespace literals
{
/** @addtogroup literals
 * @{
 */

//==============================================================================

STONEYDSP_INLINE
STONEYDSP_CONSTEXPR STONEYDSP_LLONG_T STONEYDSP_PUBLIC_FUNCTION
/**
 * @brief
 *
 * @param value
 * @return `stoneydsp::llong_t`
 */
operator"" _llong_t (char value) STONEYDSP_NOEXCEPT
{
  return ::stoneydsp_llong_c (value);
}

//==============================================================================

STONEYDSP_INLINE
STONEYDSP_CONSTEXPR STONEYDSP_LLONG_T STONEYDSP_PUBLIC_FUNCTION
/**
 * @brief
 *
 * @param value
 * @return `stoneydsp::llong_t`
 */
operator"" _llong_t (unsigned long long value) STONEYDSP_NOEXCEPT
{
  return ::stoneydsp_llong_c (value);
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
STONEYDSP_ALIGN (alignof (STONEYDSP_LLONG_T)) numeric_limits<STONEYDSP_LLONG_T>
{

  STONEYDSP_INLINE static STONEYDSP_CONSTEXPR STONEYDSP_LLONG_T STONEYDSP_API
  max () STONEYDSP_NOEXCEPT
  {
    return ::stoneydsp_llong_max ();
  }

  STONEYDSP_INLINE static STONEYDSP_CONSTEXPR STONEYDSP_LLONG_T STONEYDSP_API
  min () STONEYDSP_NOEXCEPT
  {
    return ::stoneydsp_llong_min ();
  }

  STONEYDSP_INLINE static STONEYDSP_CONSTEXPR STONEYDSP_LLONG_T STONEYDSP_API
  lowest () STONEYDSP_NOEXCEPT
  {
    return ::stoneydsp_llong_lowest ();
  }

} STONEYDSP_PACKED_STRUCT_END;

//==============================================================================

/// @} group stoneydsp
} //  namespace stoneydsp

  #endif // STONEYDSP_CXX

//==============================================================================

#endif // STONEYDSP_CORE_TYPES_LLONG_H_INCLUDED

//=========================================================================//EOF
