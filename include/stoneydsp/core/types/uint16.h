/**
 * @file uint16.h
 * @author StoneyDSP (nathanjhood@googlemail.com)
 * @brief
 * @version @STONEYDSP_CORE_VERSION@
 * @date 2025-01-27
 *
 * @copyright Copyright (c) 2025
 *
 */

#pragma once

#ifndef STONEYDSP_CORE_TYPES_UINT16_H_INCLUDED
  #define STONEYDSP_CORE_TYPES_UINT16_H_INCLUDED

//==============================================================================

  #include "../../../stoneydsp/core/system/types.h"

//==============================================================================

  #ifndef STONEYDSP_CORE_TYPES_USHRT_H_INCLUDED
    #include <stoneydsp/core/types/ushrt.h> // for numerical_limits<ushrt_t>
  #endif

//==============================================================================

/**
 * @brief
 *
 */
typedef STONEYDSP_UINT16_T stoneydsp_uint16_t;

//==============================================================================

/**
 * @brief
 *
 */
  #define stoneydsp_uint16 stoneydsp_uint16_t

//==============================================================================

typedef stoneydsp_uint16 stoneydsp_uint16;

//==============================================================================

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_UINT16_T
    STONEYDSP_PUBLIC_FUNCTION
    stoneydsp_uint16_c (unsigned long long value) STONEYDSP_NOEXCEPT
{
  return STONEYDSP_UINT16_C (value);
}

//==============================================================================

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_UINT16_T
    STONEYDSP_PUBLIC_FUNCTION
    stoneydsp_uint16_max () STONEYDSP_NOEXCEPT
{
  return stoneydsp_uint16_c (
      (stoneydsp_uint16_c (STONEYDSP_INT16_MAX))
          * (stoneydsp_uint16_c (STONEYDSP_UINT16_LITERAL (0x0002)))
      + (stoneydsp_uint16_c (STONEYDSP_UINT16_LITERAL (0x0001))));
}

//==============================================================================

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_UINT16_T
    STONEYDSP_PUBLIC_FUNCTION
    stoneydsp_uint16_min () STONEYDSP_NOEXCEPT
{
  return stoneydsp_uint16_c (STONEYDSP_UINT16_LITERAL (0x0000));
}

//==============================================================================

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_UINT16_T
    STONEYDSP_PUBLIC_FUNCTION
    stoneydsp_uint16_lowest () STONEYDSP_NOEXCEPT
{
  return stoneydsp_uint16_min ();
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
using uint16_t = stoneydsp_uint16;

//==============================================================================

namespace literals
{
/** @addtogroup literals
 * @{
 */

//==============================================================================

STONEYDSP_INLINE
STONEYDSP_CONSTEXPR STONEYDSP_UINT16_T STONEYDSP_PUBLIC_FUNCTION
/**
 * @brief
 *
 * @param value
 *
 * @return `stoneydsp::uint8_t`
 *
 */
operator"" _uint16_t (char value) STONEYDSP_NOEXCEPT
{
  return ::stoneydsp_uint16_c (value);
}

//==============================================================================

STONEYDSP_INLINE
STONEYDSP_CONSTEXPR STONEYDSP_UINT16_T STONEYDSP_PUBLIC_FUNCTION
/**
 * @brief
 *
 */
operator"" _uint16_t (unsigned long long value) STONEYDSP_NOEXCEPT
{
  return ::stoneydsp_uint16_c (value);
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

#endif // STONEYDSP_CORE_TYPES_UINT16_H_INCLUDED

//=========================================================================//EOF
