/**
 * @file ulong.h
 * @author StoneyDSP (nathanjhood@googlemail.com)
 * @brief
 * @version @STONEYDSP_CORE_VERSION@
 * @date 2025-01-27
 *
 * @copyright Copyright (c) 2025
 *
 */

#pragma once

#ifndef STONEYDSP_CORE_TYPES_ULONG_H_INCLUDED
  #define STONEYDSP_CORE_TYPES_ULONG_H_INCLUDED

//==============================================================================

  #include "../../../stoneydsp/core/system/types.h"

//==============================================================================

/**
 * @brief
 *
 */
typedef STONEYDSP_ULONG_T stoneydsp_ulong_t;

//==============================================================================

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_ULONG_T
    STONEYDSP_PUBLIC_FUNCTION
    /**
     * @brief
     *
     * @param value
     * @return `stoneydsp_ulong_t`
     */
    stoneydsp_ulong_c (unsigned long long value) STONEYDSP_NOEXCEPT
{
  return STONEYDSP_ULONG_C (value);
}

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_ULONG_T
    STONEYDSP_PUBLIC_FUNCTION
    /**
     * @brief
     *
     * @return `stoneydsp_ulong_t`
     */
    stoneydsp_ulong_max () STONEYDSP_NOEXCEPT
{
  return stoneydsp_ulong_c ((stoneydsp_ulong_c (STONEYDSP_LONG_MAX))
                                * (STONEYDSP_ULONG_LITERAL (2))
                            + (STONEYDSP_ULONG_LITERAL (1)));
}

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_ULONG_T
    STONEYDSP_PUBLIC_FUNCTION
    /**
     * @brief
     *
     * @return `stoneydsp_ulong_t`
     */
    stoneydsp_ulong_min () STONEYDSP_NOEXCEPT
{
  return stoneydsp_ulong_c (STONEYDSP_ULONG_LITERAL (0));
}

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_ULONG_T
    STONEYDSP_PUBLIC_FUNCTION
    /**
     * @brief
     *
     * @return `stoneydsp_ulong_t`
     */
    stoneydsp_ulong_lowest () STONEYDSP_NOEXCEPT
{
  return stoneydsp_ulong_min ();
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
using ulong_t = ::stoneydsp_ulong_t;

//==============================================================================

namespace literals
{
/** @addtogroup literals
 * @{
 */

STONEYDSP_INLINE
STONEYDSP_CONSTEXPR STONEYDSP_ULONG_T STONEYDSP_PUBLIC_FUNCTION
/**
 * @brief
 *
 * @param value
 * @return `stoneydsp::ulong_t`
 *
 */
operator"" _ulong_t (char value) STONEYDSP_NOEXCEPT
{
  return ::stoneydsp_ulong_c (value);
}

STONEYDSP_INLINE
STONEYDSP_CONSTEXPR STONEYDSP_ULONG_T STONEYDSP_PUBLIC_FUNCTION
/**
 * @brief
 *
 * @param value
 * @return `stoneydsp::ulong_t`
 *
 */
operator"" _ulong_t (unsigned long long value) STONEYDSP_NOEXCEPT
{
  return ::stoneydsp_ulong_c (value);
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
STONEYDSP_ALIGN (alignof (STONEYDSP_ULONG_T)) numeric_limits<STONEYDSP_ULONG_T>
{

  STONEYDSP_INLINE static STONEYDSP_CONSTEXPR STONEYDSP_ULONG_T STONEYDSP_API
  max () STONEYDSP_NOEXCEPT
  {
    return ::stoneydsp_ulong_max ();
  }

  STONEYDSP_INLINE static STONEYDSP_CONSTEXPR STONEYDSP_ULONG_T STONEYDSP_API
  min () STONEYDSP_NOEXCEPT
  {
    return ::stoneydsp_ulong_min ();
  }

  STONEYDSP_INLINE static STONEYDSP_CONSTEXPR STONEYDSP_ULONG_T STONEYDSP_API
  lowest () STONEYDSP_NOEXCEPT
  {
    return ::stoneydsp_ulong_lowest ();
  }

} STONEYDSP_PACKED_STRUCT_END;

//==============================================================================

/**
 * @brief
 *
 */
using ulong_t = ::stoneydsp::core::types::ulong_t;

//==============================================================================

/// @} group stoneydsp
} //  namespace stoneydsp

  //==============================================================================

  #endif // STONEYDSP_CXX

//==============================================================================

#endif // STONEYDSP_CORE_TYPES_ULONG_H_INCLUDED

//=========================================================================//EOF
