/**
 * @file int.h
 * @author StoneyDSP (nathanjhood@googlemail.com)
 * @brief
 * @version @STONEYDSP_CORE_VERSION@
 * @date 2025-01-27
 *
 * @copyright Copyright (c) 2025
 *
 */

#pragma once

#ifndef STONEYDSP_CORE_TYPES_INT_H_INCLUDED
  #define STONEYDSP_CORE_TYPES_INT_H_INCLUDED

//==============================================================================

  #include "../../../stoneydsp/core/system/types.h"

//==============================================================================

/**
 * @brief
 *
 */
typedef STONEYDSP_INT_T stoneydsp_int_t;

//==============================================================================

  /**
   * @brief
   *
   */
  #define stoneydsp_int stoneydsp_int_t

//==============================================================================

typedef stoneydsp_int stoneydsp_int;

//==============================================================================

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_INT_T
    STONEYDSP_PUBLIC_FUNCTION
    /**
     * @brief
     *
     * @param value
     * @return `stoneydsp_int_t`
     */
    stoneydsp_int_c (unsigned long long value) STONEYDSP_NOEXCEPT
{
  return STONEYDSP_INT_C (value);
}

//==============================================================================

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_INT_T
    STONEYDSP_PUBLIC_FUNCTION
    /**
     * @brief
     *
     * Guaranteed to be at least:
     *
     * - dec: `2147483647`
     *
     * - oct: `017777777777`
     *
     * - hex: `0x7FFFFFFF`
     *
     * @return `stoneydsp_int_t`
     */
    stoneydsp_int_max () STONEYDSP_NOEXCEPT
{
  return stoneydsp_int_c (STONEYDSP_INT_MAX);
}

//==============================================================================

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_INT_T
    STONEYDSP_PUBLIC_FUNCTION
    /**
     * @brief
     *
     * Guaranteed to be at least:
     *
     * - dec: `-2147483648`
     *
     * - oct: `-080000000000`
     *
     * - hex: `-0x80000000`
     *
     * @return `stoneydsp_int_t`
     */
    stoneydsp_int_min () STONEYDSP_NOEXCEPT
{
  return stoneydsp_int_c (stoneydsp_int_c (-stoneydsp_int_max ()))
         - (stoneydsp_int_c (1));
}

//==============================================================================

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_INT_T
    STONEYDSP_PUBLIC_FUNCTION
    /**
     * @brief
     *
     * Guaranteed to be at least:
     *
     * - dec: `-2147483648`
     *
     * - oct: `-080000000000`
     *
     * - hex: `-0x80000000`
     *
     * @return `stoneydsp_int_t`
     */
    stoneydsp_int_lowest () STONEYDSP_NOEXCEPT
{
  return stoneydsp_int_min ();
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
using int_t = stoneydsp_int;

//==============================================================================

namespace literals
{
/** @addtogroup literals
 * @{
 */

//==============================================================================

STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_INT_T STONEYDSP_PUBLIC_FUNCTION
/**
 * @brief
 *
 * @param value
 * @return `stoneydsp::int_t`
 *
 */
operator"" _int_t (char value) STONEYDSP_NOEXCEPT
{
  return ::stoneydsp_int_c (value);
}

//==============================================================================

STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_INT_T STONEYDSP_PUBLIC_FUNCTION
/**
 * @brief
 *
 * @param value
 * @return `stoneydsp::int_t`
 */
operator"" _int_t (unsigned long long value) STONEYDSP_NOEXCEPT
{
  return ::stoneydsp_int_c (value);
}

//==============================================================================

/// @} literals
} // namespace literals

/// @} types
} // namespace types

/// @} group core
} //  namespace core

//==============================================================================

/**
 * @brief
 *
 */
template <>
STONEYDSP_PACKED_STRUCT_BEGIN struct STONEYDSP_API
STONEYDSP_ALIGN (alignof (STONEYDSP_INT_T)) numeric_limits<STONEYDSP_INT_T>
{
public:
  /** True if the type is of type `signed`.  */
  static STONEYDSP_CONSTEXPR STONEYDSP_BOOL_T is_signed = true;

  /** True if the type is of type `integer`.  */
  static STONEYDSP_CONSTEXPR STONEYDSP_BOOL_T is_integer = true;

  STONEYDSP_INLINE static STONEYDSP_CONSTEXPR STONEYDSP_INT_T STONEYDSP_API
  /**
   * @brief
   *
   * Guaranteed to be at least:
   *
   * - dec: `2147483647`
   *
   * - oct: `017777777777`
   *
   * - hex: `0x7FFFFFFF`
   *
   * @return `stoneydsp::int_t`
   */
  max () STONEYDSP_NOEXCEPT
  {
    return ::stoneydsp_int_max ();
  }

  STONEYDSP_INLINE static STONEYDSP_CONSTEXPR STONEYDSP_INT_T STONEYDSP_API
  /**
   * @brief
   *
   * Guaranteed to be at least:
   *
   * - dec: `-2147483648`
   *
   * - oct: `-080000000000`
   *
   * - hex: `-0x80000000`
   *
   * @return `stoneydsp::int_t`
   */
  min () STONEYDSP_NOEXCEPT
  {
    return ::stoneydsp_int_min ();
  }

  STONEYDSP_INLINE static STONEYDSP_CONSTEXPR STONEYDSP_INT_T STONEYDSP_API
  /**
   * @brief
   *
   * Guaranteed to be at least:
   *
   * - dec: `-2147483648`
   *
   * - oct: `-080000000000`
   *
   * - hex: `-0x80000000`
   *
   * @return `stoneydsp::int_t`
   */
  lowest () STONEYDSP_NOEXCEPT
  {
    return ::stoneydsp_int_lowest ();
  }

} STONEYDSP_PACKED_STRUCT_END;

//==============================================================================

/// @} group stoneydsp
} //  namespace stoneydsp

  #endif // STONEYDSP_CXX

//==============================================================================

#endif // STONEYDSP_CORE_TYPES_INT_H_INCLUDED

//=========================================================================//EOF
