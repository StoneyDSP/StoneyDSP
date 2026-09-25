/**
 * @file float.h
 * @author StoneyDSP (nathanjhood@googlemail.com)
 * @brief
 * @version @STONEYDSP_CORE_VERSION@
 * @date 2025-01-27
 *
 * @copyright Copyright (c) 2025
 *
 */

#pragma once

#ifndef STONEYDSP_CORE_TYPES_FLT_H_INCLUDED
  #define STONEYDSP_CORE_TYPES_FLT_H_INCLUDED

//==============================================================================

  #include "../../../stoneydsp/core/system/types.h"

//==============================================================================

/**
 * @brief
 *
 */
typedef STONEYDSP_FLT_T stoneydsp_float_t;

//==============================================================================

  /**
   * @brief
   *
   */
  #define stoneydsp_float stoneydsp_float_t

//==============================================================================

typedef stoneydsp_float stoneydsp_float;

//==============================================================================

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_FLT_T
    STONEYDSP_PUBLIC_FUNCTION
    stoneydsp_float_c (float value) STONEYDSP_NOEXCEPT
{
  return STONEYDSP_FLT_C (value);
}

//==============================================================================

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_FLT_T
    STONEYDSP_PUBLIC_FUNCTION
    stoneydsp_float_max () STONEYDSP_NOEXCEPT
{
  return stoneydsp_float_c (STONEYDSP_FLT_MAX);
}

//==============================================================================

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_FLT_T
    STONEYDSP_PUBLIC_FUNCTION
    stoneydsp_float_min () STONEYDSP_NOEXCEPT
{
  return stoneydsp_float_c (STONEYDSP_FLT_MIN);
}

//==============================================================================

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_FLT_T
    STONEYDSP_PUBLIC_FUNCTION
    stoneydsp_float_lowest () STONEYDSP_NOEXCEPT
{
  return stoneydsp_float_c (-STONEYDSP_FLT_MAX);
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
using float_t = stoneydsp_float;

//==============================================================================

namespace literals
{
/** @addtogroup literals
 * @{
 */

//==============================================================================

STONEYDSP_INLINE
STONEYDSP_CONSTEXPR STONEYDSP_FLT_T STONEYDSP_PUBLIC_FUNCTION
/**
 * @brief
 *
 */
operator"" _float_t (long double value) STONEYDSP_NOEXCEPT
{
  return ::stoneydsp_float_c (value);
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
STONEYDSP_ALIGN (alignof (STONEYDSP_FLT_T)) numeric_limits<STONEYDSP_FLT_T>
{

  STONEYDSP_INLINE static STONEYDSP_CONSTEXPR STONEYDSP_FLT_T STONEYDSP_API
  max () STONEYDSP_NOEXCEPT
  {
    return ::stoneydsp_float_max ();
  }

  STONEYDSP_INLINE static STONEYDSP_CONSTEXPR STONEYDSP_FLT_T STONEYDSP_API
  min () STONEYDSP_NOEXCEPT
  {
    return ::stoneydsp_float_min ();
  }

  STONEYDSP_INLINE static STONEYDSP_CONSTEXPR STONEYDSP_FLT_T STONEYDSP_API
  lowest () STONEYDSP_NOEXCEPT
  {
    return ::stoneydsp_float_lowest ();
  }

} STONEYDSP_PACKED_STRUCT_END;

//==============================================================================

/// @} group stoneydsp
} //  namespace stoneydsp

  #endif // STONEYDSP_CXX

//==============================================================================

#endif // STONEYDSP_CORE_TYPES_FLT_H_INCLUDED

//=========================================================================//EOF
