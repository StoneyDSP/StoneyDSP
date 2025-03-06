/**
 * @file long.h
 * @author StoneyDSP (nathanjhood@googlemail.com)
 * @brief
 * @version @STONEYDSP_CORE_VERSION@
 * @date 2025-01-27
 *
 * @copyright Copyright (c) 2025
 *
 */

#pragma once

#ifndef STONEYDSP_CORE_TYPES_LONG_H_INCLUDED
  #define STONEYDSP_CORE_TYPES_LONG_H_INCLUDED

//==============================================================================

  #include "../../../stoneydsp/core/system/types.h"

//==============================================================================

/**
 * @brief
 *
 */
typedef STONEYDSP_LONG_T stoneydsp_long_t;

//==============================================================================

  /**
   * @brief
   *
   */
  #define stoneydsp_long stoneydsp_long_t

//==============================================================================

typedef stoneydsp_long stoneydsp_long;

//==============================================================================

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_LONG_T
    STONEYDSP_PUBLIC_FUNCTION
    /**
     * @brief
     *
     * @param value
     * @return `stoneydsp_long_t`
     */
    stoneydsp_long_c (unsigned long long value) STONEYDSP_NOEXCEPT
{
  return STONEYDSP_LONG_C (value);
}

//==============================================================================

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_LONG_T
    STONEYDSP_PUBLIC_FUNCTION
    /**
     * @brief
     *
     * @return `stoneydsp_long_t`
     */
    stoneydsp_long_max () STONEYDSP_NOEXCEPT
{
  return stoneydsp_long_c (STONEYDSP_LONG_MAX);
}

//==============================================================================

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_LONG_T
    STONEYDSP_PUBLIC_FUNCTION
    /**
     * @brief
     *
     * @return `stoneydsp_long_t`
     */
    stoneydsp_long_min () STONEYDSP_NOEXCEPT
{
  return stoneydsp_long_c ((-stoneydsp_long_max ())
                           - (STONEYDSP_LONG_LITERAL (1)));
}

//==============================================================================

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_LONG_T
    STONEYDSP_PUBLIC_FUNCTION
    /**
     * @brief
     *
     * @return `stoneydsp_long_t`
     */
    stoneydsp_long_lowest () STONEYDSP_NOEXCEPT
{
  return stoneydsp_long_min ();
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
using long_t = stoneydsp_long;

//==============================================================================

namespace literals
{
/** @addtogroup literals
 * @{
 */

//==============================================================================

STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_LONG_T STONEYDSP_PUBLIC_FUNCTION
/**
 * @brief
 *
 * @param value
 * @return `stoneydsp::long_t`
 */
operator"" _long_t (char value) STONEYDSP_NOEXCEPT
{
  return ::stoneydsp_long_c (value);
}

//==============================================================================

STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_LONG_T STONEYDSP_PUBLIC_FUNCTION
/**
 * @brief
 *
 * @param value
 * @return `stoneydsp::long_t`
 */
operator"" _long_t (unsigned long long value) STONEYDSP_NOEXCEPT
{
  return ::stoneydsp_long_c (value);
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
STONEYDSP_ALIGN (alignof (STONEYDSP_LONG_T)) numeric_limits<STONEYDSP_LONG_T>
{

  STONEYDSP_INLINE static STONEYDSP_CONSTEXPR STONEYDSP_LONG_T STONEYDSP_API
  max () STONEYDSP_NOEXCEPT
  {
    return ::stoneydsp_long_max ();
  }

  STONEYDSP_INLINE static STONEYDSP_CONSTEXPR STONEYDSP_LONG_T STONEYDSP_API
  min () STONEYDSP_NOEXCEPT
  {
    return ::stoneydsp_long_min ();
  }

  STONEYDSP_INLINE static STONEYDSP_CONSTEXPR STONEYDSP_LONG_T STONEYDSP_API
  lowest () STONEYDSP_NOEXCEPT
  {
    return ::stoneydsp_long_lowest ();
  }

} STONEYDSP_PACKED_STRUCT_END;

//==============================================================================

/// @} group stoneydsp
} //  namespace stoneydsp

  #endif // STONEYDSP_CXX

//==============================================================================

#endif // STONEYDSP_CORE_TYPES_LONG_H_INCLUDED

//=========================================================================//EOF
