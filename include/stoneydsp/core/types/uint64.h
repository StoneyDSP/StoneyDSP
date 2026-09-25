/**
 * @file uint64.h
 * @author StoneyDSP (nathanjhood@googlemail.com)
 * @brief
 * @version @STONEYDSP_CORE_VERSION@
 * @date 2025-01-27
 *
 * @copyright Copyright (c) 2025
 *
 */

#pragma once

#ifndef STONEYDSP_CORE_TYPES_UINT64_H_INCLUDED
  #define STONEYDSP_CORE_TYPES_UINT64_H_INCLUDED

//==============================================================================

  #include "../../../stoneydsp/core/system/types.h"

//==============================================================================

  #if defined(STONEYDSP_WINDOWS) || defined(STONEYDSP_32BIT)

    #ifndef STONEYDSP_CORE_TYPES_ULLONG_H_INCLUDED
      #include <stoneydsp/core/types/ullong.h> // for numerical_limits<llong_t>
    #endif

  #elif (defined(STONEYDSP_LINUX) || defined(STONEYDSP_MAC))                  \
      && (defined(STONEYDSP_64BIT) || defined(STONEYDSP_ARM))

    #ifndef STONEYDSP_CORE_TYPES_ULONG_H_INCLUDED
      #include <stoneydsp/core/types/ulong.h> // for numerical_limits<long_t>
    #endif

  #else

    #error unable to determine a suitable template for numerical_limits<uint64_t>

  #endif

//==============================================================================

/**
 * @brief
 *
 */
typedef STONEYDSP_UINT64_T stoneydsp_uint64_t;

//==============================================================================

  #define stoneydsp_uint64 stoneydsp_uint64_t

//==============================================================================

typedef stoneydsp_uint64 stoneydsp_uint64;

//==============================================================================

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_UINT64_T
    STONEYDSP_PUBLIC_FUNCTION
    stoneydsp_uint64_c (unsigned long long value) STONEYDSP_NOEXCEPT
{
  return STONEYDSP_UINT64_C (value);
}

//==============================================================================

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_UINT64_T
    STONEYDSP_PUBLIC_FUNCTION
    stoneydsp_uint64_max () STONEYDSP_NOEXCEPT
{
  return stoneydsp_uint64_c (
      (stoneydsp_uint64_c (STONEYDSP_INT64_MAX))
          * (stoneydsp_uint64_c (STONEYDSP_UINT64_LITERAL (2)))
      + (stoneydsp_uint64_c (STONEYDSP_UINT64_LITERAL (1))));
}

//==============================================================================

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_UINT64_T
    STONEYDSP_PUBLIC_FUNCTION
    stoneydsp_uint64_min () STONEYDSP_NOEXCEPT
{
  return stoneydsp_uint64_c (STONEYDSP_UINT64_LITERAL (0));
}

//==============================================================================

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_UINT64_T
    STONEYDSP_PUBLIC_FUNCTION
    stoneydsp_uint64_lowest () STONEYDSP_NOEXCEPT
{
  return stoneydsp_uint64_min ();
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
using uint64_t = stoneydsp_uint64;

//==============================================================================

namespace literals
{
/** @addtogroup literals
 * @{
 */

//==============================================================================

STONEYDSP_INLINE
STONEYDSP_CONSTEXPR STONEYDSP_UINT64_T STONEYDSP_PUBLIC_FUNCTION
/**
 * @brief
 *
 * @param value
 * @return `stoneydsp::uint64_t`
 */
operator"" _uint64_t (char value) STONEYDSP_NOEXCEPT
{
  return ::stoneydsp_uint64_c (value);
}

//==============================================================================

STONEYDSP_INLINE
STONEYDSP_CONSTEXPR STONEYDSP_UINT64_T STONEYDSP_PUBLIC_FUNCTION
/**
 * @brief
 *
 * @param value
 * @return `stoneydsp::uint64_t`
 */
operator"" _uint64_t (unsigned long long value) STONEYDSP_NOEXCEPT
{
  return ::stoneydsp_uint64_c (value);
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

#endif // STONEYDSP_CORE_TYPES_UINT64_H_INCLUDED

//=========================================================================//EOF
