/**
 * @file int32.h
 * @author StoneyDSP (nathanjhood@googlemail.com)
 * @brief
 * @version @STONEYDSP_CORE_VERSION@
 * @date 2025-01-27
 *
 * @copyright Copyright (c) 2025
 *
 */

#pragma once

#ifndef STONEYDSP_CORE_TYPES_INT32_H_INCLUDED
  #define STONEYDSP_CORE_TYPES_INT32_H_INCLUDED

//==============================================================================

  #include "../../../stoneydsp/core/system/types.h"

//==============================================================================

  #ifndef STONEYDSP_CORE_TYPES_INT_H_INCLUDED
    #include "../../../stoneydsp/core/types/int.h" // for numerical_limits<int_t>
  #endif

//==============================================================================

/**
 * @brief
 *
 */
typedef STONEYDSP_INT32_T stoneydsp_int32_t;

//==============================================================================

/**
 * @brief
 *
 */
  #define stoneydsp_int32 stoneydsp_int32_t

//==============================================================================

typedef stoneydsp_int32 stoneydsp_int32;

//==============================================================================

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_INT32_T
    STONEYDSP_PUBLIC_FUNCTION
    stoneydsp_int32_c (unsigned long long value) STONEYDSP_NOEXCEPT
{
  return STONEYDSP_INT32_C (value);
}

//============================================================================//

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_INT32_T
    STONEYDSP_PUBLIC_FUNCTION
    /**
     * @brief
     *
     * Equivalent to:
     *
     * - dec: `2147483647`
     *
     * - oct: `017777777777`
     *
     * - hex: `0x7FFFFFFF`
     *
     * @return `stoneydsp_int32_t`
     *
     */
    stoneydsp_int32_max () STONEYDSP_NOEXCEPT
{
  return stoneydsp_int32_c (STONEYDSP_INT32_MAX);
}

//============================================================================//

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_INT32_T
    STONEYDSP_PUBLIC_FUNCTION
    /**
     * @brief
     *
     * Equivalent to:
     *
     * - dec: `-2147483648`
     *
     * - oct: `-020000000000`
     *
     * - hex: `-0x80000000`
     *
     * @return `stoneydsp_int32_t`
     *
     */
    stoneydsp_int32_min () STONEYDSP_NOEXCEPT
{
  return stoneydsp_int32_c (
      (-stoneydsp_int32_max ())
      - (stoneydsp_int32_c (STONEYDSP_INT32_LITERAL (1))));
}

//============================================================================//

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_INT32_T
    STONEYDSP_PUBLIC_FUNCTION
    stoneydsp_int32_lowest () STONEYDSP_NOEXCEPT
{
  return stoneydsp_int32_min ();
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
using int32_t = stoneydsp_int32;

//==============================================================================

namespace literals
{
/** @addtogroup literals
 * @{
 */

//==============================================================================

STONEYDSP_INLINE
STONEYDSP_CONSTEXPR STONEYDSP_INT32_T STONEYDSP_PUBLIC_FUNCTION
/**
 * @brief
 *
 * @param value
 * @return `stoneydsp::int32_t`
 */
operator"" _int32_t (char value) STONEYDSP_NOEXCEPT
{
  return ::stoneydsp_int32_c (value);
}

//==============================================================================

STONEYDSP_INLINE
STONEYDSP_CONSTEXPR STONEYDSP_INT32_T STONEYDSP_PUBLIC_FUNCTION
/**
 * @brief
 *
 * @param value
 * @return `stoneydsp::int32_t`
 */
operator"" _int32_t (unsigned long long value) STONEYDSP_NOEXCEPT
{
  return ::stoneydsp_int32_c (value);
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

#endif // STONEYDSP_CORE_TYPES_INT32_H_INCLUDED

//=========================================================================//EOF
