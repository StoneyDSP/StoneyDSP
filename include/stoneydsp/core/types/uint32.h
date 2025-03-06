/**
 * @file uint32.h
 * @author StoneyDSP (nathanjhood@googlemail.com)
 * @brief
 * @version @STONEYDSP_CORE_VERSION@
 * @date 2025-01-27
 *
 * @copyright Copyright (c) 2025
 *
 */

#pragma once

#ifndef STONEYDSP_CORE_TYPES_UINT32_H_INCLUDED
  #define STONEYDSP_CORE_TYPES_UINT32_H_INCLUDED

//==============================================================================

  #include "../../../stoneydsp/core/system/types.h"

//==============================================================================

  #ifndef STONEYDSP_CORE_TYPES_UINT_H_INCLUDED
    #include <stoneydsp/core/types/uint.h> // for numerical_limits<uint_t>
  #endif

//==============================================================================

/**
 * @brief
 *
 */
typedef STONEYDSP_UINT32_T stoneydsp_uint32_t;

//==============================================================================

/**
 * @brief
 *
 */
  #define stoneydsp_uint32 stoneydsp_uint32_t

//==============================================================================

typedef stoneydsp_uint32 stoneydsp_uint32;

//==============================================================================

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_UINT32_T
    STONEYDSP_PUBLIC_FUNCTION
    stoneydsp_uint32_c (unsigned long long value) STONEYDSP_NOEXCEPT
{
  return STONEYDSP_UINT32_C (value);
}

//==============================================================================

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_UINT32_T
    STONEYDSP_PUBLIC_FUNCTION
    stoneydsp_uint32_max () STONEYDSP_NOEXCEPT
{
  return stoneydsp_uint32_c (
      (stoneydsp_uint32_c (STONEYDSP_INT32_MAX))
          * (stoneydsp_uint32_c (STONEYDSP_UINT32_LITERAL (2)))
      + (stoneydsp_uint32_c (STONEYDSP_UINT32_LITERAL (1))));
}

//==============================================================================

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_UINT32_T
    STONEYDSP_PUBLIC_FUNCTION
    stoneydsp_uint32_min () STONEYDSP_NOEXCEPT
{
  return stoneydsp_uint32_c (STONEYDSP_UINT32_LITERAL (0));
}

//==============================================================================

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_UINT32_T
    STONEYDSP_PUBLIC_FUNCTION
    stoneydsp_uint32_lowest () STONEYDSP_NOEXCEPT
{
  return stoneydsp_uint32_min ();
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
using uint32_t = stoneydsp_uint32;

//==============================================================================

namespace literals
{
/** @addtogroup literals
 * @{
 */

//==============================================================================

STONEYDSP_INLINE
STONEYDSP_CONSTEXPR STONEYDSP_UINT32_T STONEYDSP_PUBLIC_FUNCTION
/**
 * @brief
 *
 * @param value
 *
 * @return `stoneydsp::uint32_t`
 *
 */
operator"" _uint32_t (char value) STONEYDSP_NOEXCEPT
{
  return ::stoneydsp_uint32_c (value);
}

//==============================================================================

STONEYDSP_INLINE
STONEYDSP_CONSTEXPR STONEYDSP_UINT32_T STONEYDSP_PUBLIC_FUNCTION
/**
 * @brief
 *
 */
operator"" _uint32_t (unsigned long long value) STONEYDSP_NOEXCEPT
{
  return ::stoneydsp_uint32_c (value);
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

#endif // STONEYDSP_CORE_TYPES_UINT32_H_INCLUDED

//=========================================================================//EOF
