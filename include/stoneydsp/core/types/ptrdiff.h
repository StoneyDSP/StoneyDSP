/**
 * @file ptrdiff.h
 * @author StoneyDSP (nathanjhood@googlemail.com)
 * @brief
 * @version @STONEYDSP_CORE_VERSION@
 * @date 2025-01-27
 *
 * @copyright Copyright (c) 2025
 *
 */

#pragma once

#ifndef STONEYDSP_CORE_TYPES_PTRDIFF_H_INCLUDED
  #define STONEYDSP_CORE_TYPES_PTRDIFF_H_INCLUDED

//==============================================================================

  #include "../../../stoneydsp/core/system/types.h"

//==============================================================================

/**
 * @brief
 *
 */
typedef STONEYDSP_PTRDIFF_T stoneydsp_ptrdiff_t;

//==============================================================================

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_PTRDIFF_T
    STONEYDSP_PUBLIC_FUNCTION
    /**
     * @brief
     *
     * @param value
     * @return `stoneydsp_ptrdiff_t`
     */
    stoneydsp_ptrdiff_c (unsigned long long value) STONEYDSP_NOEXCEPT
{
  return STONEYDSP_PTRDIFF_C (value);
}

//==============================================================================

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_PTRDIFF_T
    STONEYDSP_PUBLIC_FUNCTION
    /**
     * @brief
     *
     * @return `stoneydsp_ptrdiff_t`
     */
    stoneydsp_ptrdiff_min () STONEYDSP_NOEXCEPT
{
  return stoneydsp_ptrdiff_c (STONEYDSP_PTRDIFF_MIN);
}

//==============================================================================

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_PTRDIFF_T
    STONEYDSP_PUBLIC_FUNCTION
    /**
     * @brief
     *
     * @return `stoneydsp_ptrdiff_t`
     */
    stoneydsp_ptrdiff_lowest () STONEYDSP_NOEXCEPT
{
  return stoneydsp_ptrdiff_c (STONEYDSP_PTRDIFF_MIN);
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
using ptrdiff_t = ::stoneydsp_ptrdiff_t;

//==============================================================================

namespace literals
{
/** @addtogroup literals
 * @{
 */

//==============================================================================

STONEYDSP_INLINE
STONEYDSP_CONSTEXPR STONEYDSP_PTRDIFF_T STONEYDSP_PUBLIC_FUNCTION
/**
 * @brief
 *
 * @param value
 * @return `stoneydsp::ptrdiff_t`
 *
 */
operator"" _ptrdiff_t (char value) STONEYDSP_NOEXCEPT
{
  return ::stoneydsp_ptrdiff_c (value);
}

//==============================================================================

STONEYDSP_INLINE
STONEYDSP_CONSTEXPR STONEYDSP_PTRDIFF_T STONEYDSP_PUBLIC_FUNCTION
/**
 * @brief
 *
 * @param value
 * @return `stoneydsp::ptrdiff_t`
 *
 */
operator"" _ptrdiff_t (unsigned long long value) STONEYDSP_NOEXCEPT
{
  return ::stoneydsp_ptrdiff_c (value);
}

//==============================================================================

/// @} literals
} // namespace literals

/// @} types
} // namespace types

/// @} group core
} //  namespace core

/// @} group stoneydsp
} //  namespace stoneydsp

  #endif // STONEYDSP_CXX

//==============================================================================

#endif // STONEYDSP_CORE_TYPES_PTRDIFF_H_INCLUDED

//=========================================================================//EOF
