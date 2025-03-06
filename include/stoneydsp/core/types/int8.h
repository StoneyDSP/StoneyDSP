/**
 * @file int8.h
 * @author StoneyDSP (nathanjhood@googlemail.com)
 * @brief
 * @version @STONEYDSP_CORE_VERSION@
 * @date 2025-01-27
 *
 * @copyright Copyright (c) 2025
 *
 */

#pragma once

#ifndef STONEYDSP_CORE_TYPES_INT8_H_INCLUDED
  #define STONEYDSP_CORE_TYPES_INT8_H_INCLUDED

//==============================================================================

  #include "../../../stoneydsp/core/system/types.h"

//==============================================================================

  #ifndef STONEYDSP_CORE_TYPES_SCHAR_H_INCLUDED
    #include "../../../stoneydsp/core/types/schar.h" // for numerical_limits<schar_t>
  #endif

//==============================================================================

/**
 * @brief
 *
 */
typedef STONEYDSP_INT8_T stoneydsp_int8_t;

//==============================================================================

  /**
   * @brief
   *
   */
  #define stoneydsp_int8 stoneydsp_int8_t

//==============================================================================

typedef stoneydsp_int8 stoneydsp_int8;

//==============================================================================

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_INT8_T
    STONEYDSP_PUBLIC_FUNCTION
    stoneydsp_int8_c (unsigned long long value) STONEYDSP_NOEXCEPT
{
  return STONEYDSP_INT8_C (value);
}

//==============================================================================

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_INT8_T
    STONEYDSP_PUBLIC_FUNCTION
    /**
     * @brief
     *
     * Equivalent to:
     *
     * - dec: `127`
     *
     * - oct: `0177`
     *
     * - hex: `0x7F`
     *
     * @return `stoneydsp_int8_t`
     *
     */
    stoneydsp_int8_max () STONEYDSP_NOEXCEPT
{
  return stoneydsp_int8_c (STONEYDSP_INT8_MAX);
}

//==============================================================================

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_INT8_T
    STONEYDSP_PUBLIC_FUNCTION
    /**
     * @brief
     *
     * Equivalent to:
     *
     * - dec: `-128`
     *
     * - oct: `-0200`
     *
     * - hex: `-0x80`
     *
     * @return `stoneydsp_int8_t`
     *
     */
    stoneydsp_int8_min () STONEYDSP_NOEXCEPT
{
  return stoneydsp_int8_c ((-stoneydsp_int8_max ())
                           - (stoneydsp_int8_c (STONEYDSP_INT8_LITERAL (01))));
}

//==============================================================================

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_INT8_T
    STONEYDSP_PUBLIC_FUNCTION
    /**
     * @brief
     *
     * @return `stoneydsp_int8_t`
     */
    stoneydsp_int8_lowest () STONEYDSP_NOEXCEPT
{
  return stoneydsp_int8_min ();
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
using int8_t = stoneydsp_int8;

//==============================================================================

namespace literals
{
/** @addtogroup literals
 * @{
 */

//==============================================================================

STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_INT8_T STONEYDSP_PUBLIC_FUNCTION
/**
 * @brief
 *
 * @param value
 * @return `stoneydsp::int8_t`
 */
operator"" _int8_t (char value) STONEYDSP_NOEXCEPT
{
  return ::stoneydsp_int8_c (value);
}

//==============================================================================

STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_INT8_T STONEYDSP_PUBLIC_FUNCTION
/**
 * @brief
 *
 * @param value
 * @return `stoneydsp::int8_t`
 */
operator"" _int8_t (unsigned long long value) STONEYDSP_NOEXCEPT
{
  return ::stoneydsp_int8_c (value);
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

#endif // STONEYDSP_CORE_TYPES_INT8_H_INCLUDED

//=========================================================================//EOF
