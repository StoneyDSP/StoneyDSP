/**
 * @file size.h
 * @author StoneyDSP (nathanjhood@googlemail.com)
 * @brief
 * @version @STONEYDSP_CORE_VERSION@
 * @date 2025-01-27
 *
 * @copyright Copyright (c) 2025
 *
 */

#pragma once

#ifndef STONEYDSP_CORE_TYPES_SIZE_H_INCLUDED
  #define STONEYDSP_CORE_TYPES_SIZE_H_INCLUDED

//==============================================================================

  #include "../../../stoneydsp/core/system/types.h"

//==============================================================================

/**
 * @brief
 *
 */
typedef STONEYDSP_SIZE_T stoneydsp_size_t;

//==============================================================================

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_SIZE_T
    STONEYDSP_PUBLIC_FUNCTION
    /**
     * @brief
     *
     * @param value
     * @return `stoneydsp_size_t`
     */
    stoneydsp_size_c (unsigned long long value) STONEYDSP_NOEXCEPT
{
  return STONEYDSP_SIZE_C (value);
}

//==============================================================================

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_SIZE_T
    STONEYDSP_PUBLIC_FUNCTION
    /**
     * @brief
     *
     * @return `stoneydsp_size_t`
     */
    stoneydsp_size_max () STONEYDSP_NOEXCEPT
{
  return stoneydsp_size_c ((stoneydsp_size_c (STONEYDSP_SIZE_MAX))
                               * (stoneydsp_size_c (2UL))
                           + (stoneydsp_size_c (1UL)));
}

//==============================================================================

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_SIZE_T
    STONEYDSP_PUBLIC_FUNCTION
    /**
     * @brief
     *
     * @return `stoneydsp_size_t`
     */
    stoneydsp_size_min () STONEYDSP_NOEXCEPT
{
  return stoneydsp_size_c (STONEYDSP_SIZE_LITERAL (0));
}

//==============================================================================

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_SIZE_T
    STONEYDSP_PUBLIC_FUNCTION
    /**
     * @brief
     *
     * @return `stoneydsp_size_t`
     */
    stoneydsp_size_lowest () STONEYDSP_NOEXCEPT
{
  return stoneydsp_size_c (0U);
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
using size_t = ::stoneydsp_size_t;

//==============================================================================

namespace literals
{
/** @addtogroup literals
 * @{
 */

//==============================================================================

STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_SIZE_T STONEYDSP_PUBLIC_FUNCTION
/**
 * @brief
 *
 * @param value
 * @return `stoneydsp::size_t`
 */
operator"" _size_t (char value) STONEYDSP_NOEXCEPT
{
  return ::stoneydsp_size_c (value);
}

//==============================================================================

STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_SIZE_T STONEYDSP_PUBLIC_FUNCTION
/**
 * @brief
 *
 * @param value
 * @return `stoneydsp::size_t`
 */
operator"" _size_t (unsigned long long value) STONEYDSP_NOEXCEPT
{
  return ::stoneydsp_size_c (value);
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

#endif // STONEYDSP_CORE_TYPES_SIZE_H_INCLUDED

//=========================================================================//EOF
