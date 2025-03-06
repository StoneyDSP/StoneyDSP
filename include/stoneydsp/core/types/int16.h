/**
 * @file int16.h
 * @author StoneyDSP (nathanjhood@googlemail.com)
 * @brief
 * @version @STONEYDSP_CORE_VERSION@
 * @date 2025-01-27
 *
 * @copyright Copyright (c) 2025
 *
 */

#pragma once

#ifndef STONEYDSP_CORE_TYPES_INT16_H_INCLUDED
  #define STONEYDSP_CORE_TYPES_INT16_H_INCLUDED

//==============================================================================

  #include "../../../stoneydsp/core/system/types.h"

//==============================================================================

  #ifndef STONEYDSP_CORE_TYPES_SHRT_H_INCLUDED
    #include "../../../stoneydsp/core/types/shrt.h" // for numerical_limits<shrt_t>
  #endif

//==============================================================================

/**
 * @brief
 *
 */
typedef STONEYDSP_INT16_T stoneydsp_int16_t;

//==============================================================================

  /**
   * @brief
   *
   */
  #define stoneydsp_int16 stoneydsp_int16_t

//==============================================================================

typedef stoneydsp_int16 stoneydsp_int16;

//==============================================================================

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_INT16_T
    STONEYDSP_PUBLIC_FUNCTION
    stoneydsp_int16_c (unsigned long long value) STONEYDSP_NOEXCEPT
{
  return STONEYDSP_INT16_C (value);
}

//==============================================================================

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_INT16_T
    STONEYDSP_PUBLIC_FUNCTION
    /**
     * @brief
     *
     * Equivalent to:
     *
     * - dec: `32767`
     *
     * - oct: `077777`
     *
     * - hex: `0x7FFF`
     *
     * @return `stoneydsp_int16_t`
     *
     */
    stoneydsp_int16_max () STONEYDSP_NOEXCEPT
{
  return stoneydsp_int16_c (STONEYDSP_INT16_MAX);
}

//==============================================================================

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_INT16_T
    STONEYDSP_PUBLIC_FUNCTION
    /**
     * @brief
     *
     * Equivalent to:
     *
     * - dec: `-32768`
     *
     * - oct: `-0100000`
     *
     * - hex: `-0x8000`
     *
     * @return `stoneydsp_int16_t`
     *
     */
    stoneydsp_int16_min () STONEYDSP_NOEXCEPT
{
  return stoneydsp_int16_c (
      (-stoneydsp_int16_max ())
      - (stoneydsp_int16_c (STONEYDSP_INT16_LITERAL (0x0001))));
}

//==============================================================================

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_INT16_T
    STONEYDSP_PUBLIC_FUNCTION
    stoneydsp_int16_lowest () STONEYDSP_NOEXCEPT
{
  return stoneydsp_int16_min ();
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
using int16_t = stoneydsp_int16;

//==============================================================================

namespace literals
{
/** @addtogroup literals
 * @{
 */

//==============================================================================

STONEYDSP_INLINE
STONEYDSP_CONSTEXPR STONEYDSP_INT16_T STONEYDSP_PUBLIC_FUNCTION
/**
 * @brief
 *
 * @param value
 * @return `stoneydsp::int16_t`
 */
operator"" _int16_t (char value) STONEYDSP_NOEXCEPT
{
  return ::stoneydsp_int16_c (value);
}

//==============================================================================

STONEYDSP_INLINE
STONEYDSP_CONSTEXPR STONEYDSP_INT16_T STONEYDSP_PUBLIC_FUNCTION
/**
 * @brief
 *
 * @param value
 * @return `stoneydsp::int16_t`
 */
operator"" _int16_t (unsigned long long value) STONEYDSP_NOEXCEPT
{
  return ::stoneydsp_int16_c (value);
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

#endif // STONEYDSP_CORE_TYPES_INT16_H_INCLUDED

//=========================================================================//EOF
