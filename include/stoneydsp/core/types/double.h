/**
 * @file double.h
 * @author StoneyDSP (nathanjhood@googlemail.com)
 * @brief
 * @version @STONEYDSP_CORE_VERSION@
 * @date 2025-01-27
 *
 * @copyright Copyright (c) 2025
 *
 */

#pragma once

#ifndef STONEYDSP_CORE_TYPES_DBL_H_INCLUDED
  #define STONEYDSP_CORE_TYPES_DBL_H_INCLUDED

//==============================================================================

  #include "../../../stoneydsp/core/system/types.h"

//==============================================================================

/**
 * @brief
 *
 */
typedef STONEYDSP_DBL_T stoneydsp_double_t;

//==============================================================================

  /**
   * @brief
   *
   */
  #define stoneydsp_double stoneydsp_double_t

//==============================================================================

typedef stoneydsp_double stoneydsp_double;

//==============================================================================

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_DBL_T
    STONEYDSP_PUBLIC_FUNCTION
    stoneydsp_double_c (double value) STONEYDSP_NOEXCEPT
{
  return STONEYDSP_DBL_C (value);
}

//==============================================================================

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_DBL_T
    STONEYDSP_PUBLIC_FUNCTION
    stoneydsp_double_max () STONEYDSP_NOEXCEPT
{
  return stoneydsp_double_c (STONEYDSP_DBL_MAX);
}

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_DBL_T
    STONEYDSP_PUBLIC_FUNCTION
    stoneydsp_double_min () STONEYDSP_NOEXCEPT
{
  return stoneydsp_double_c (STONEYDSP_DBL_MIN);
}

//==============================================================================

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_DBL_T
    STONEYDSP_PUBLIC_FUNCTION
    stoneydsp_double_lowest () STONEYDSP_NOEXCEPT
{
  return stoneydsp_double_c (-STONEYDSP_DBL_MAX);
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
using double_t = stoneydsp_double;

//==============================================================================

namespace literals
{
/** @addtogroup literals
 * @{
 */

//==============================================================================

STONEYDSP_INLINE
STONEYDSP_CONSTEXPR STONEYDSP_DBL_T STONEYDSP_PUBLIC_FUNCTION
/**
 * @brief
 *
 */
operator"" _double_t (long double value) STONEYDSP_NOEXCEPT
{
  return ::stoneydsp_double_c (value);
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
STONEYDSP_ALIGN (alignof (STONEYDSP_DBL_T)) numeric_limits<STONEYDSP_DBL_T>
{

  STONEYDSP_INLINE static STONEYDSP_CONSTEXPR STONEYDSP_DBL_T STONEYDSP_API
  max () STONEYDSP_NOEXCEPT
  {
    return ::stoneydsp_double_max ();
  }

  STONEYDSP_INLINE static STONEYDSP_CONSTEXPR STONEYDSP_DBL_T STONEYDSP_API
  min () STONEYDSP_NOEXCEPT
  {
    return ::stoneydsp_double_min ();
  }

  STONEYDSP_INLINE static STONEYDSP_CONSTEXPR STONEYDSP_DBL_T STONEYDSP_API
  lowest () STONEYDSP_NOEXCEPT
  {
    return ::stoneydsp_double_lowest ();
  }

} STONEYDSP_PACKED_STRUCT_END;

//==============================================================================

/// @} group stoneydsp
} //  namespace stoneydsp

  #endif // STONEYDSP_CXX

//==============================================================================

#endif // STONEYDSP_CORE_TYPES_DBL_H_INCLUDED

//=========================================================================//EOF
