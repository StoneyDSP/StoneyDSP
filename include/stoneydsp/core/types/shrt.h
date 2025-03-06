/**
 * @file shrt.h
 * @author StoneyDSP (nathanjhood@googlemail.com)
 * @brief
 * @version @STONEYDSP_CORE_VERSION@
 * @date 2025-01-27
 *
 * @copyright Copyright (c) 2025
 *
 */

#pragma once

#ifndef STONEYDSP_CORE_TYPES_SHRT_H_INCLUDED
  #define STONEYDSP_CORE_TYPES_SHRT_H_INCLUDED

//==============================================================================

  #include "../../../stoneydsp/core/system/types.h"

//==============================================================================

/**
 * @brief
 *
 */
typedef STONEYDSP_SHRT_T stoneydsp_shrt_t;

//==============================================================================

  /**
   * @brief
   *
   */
  #define stoneydsp_shrt stoneydsp_shrt_t

//==============================================================================

typedef stoneydsp_shrt stoneydsp_shrt;

//==============================================================================

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_SHRT_T
    STONEYDSP_PUBLIC_FUNCTION
    /**
     * @brief
     *
     * @param value
     * @return `stoneydsp_shrt_t`
     */
    stoneydsp_shrt_c (unsigned long long value) STONEYDSP_NOEXCEPT
{
  return STONEYDSP_SHRT_C (value);
}

//==============================================================================

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_SHRT_T
    STONEYDSP_PUBLIC_FUNCTION
    /**
     * @brief
     *
     * Guaranteed to be at least:
     *
     * - dec: `32767`
     *
     * - oct: `077777`
     *
     * - hex: `0x7FFF`
     *
     * @return `stoneydsp_shrt_t`
     *
     */
    stoneydsp_shrt_max () STONEYDSP_NOEXCEPT
{
  return stoneydsp_shrt_c (STONEYDSP_SHRT_MAX);
}

//==============================================================================

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_SHRT_T
    STONEYDSP_PUBLIC_FUNCTION
    /**
     * @brief
     *
     * @return `stoneydsp_shrt_t`
     */
    stoneydsp_shrt_min () STONEYDSP_NOEXCEPT
{
  return stoneydsp_shrt_c ((STONEYDSP_SHRT_C (-STONEYDSP_SHRT_MAX))
                           - (STONEYDSP_SHRT_LITERAL (1)));
}

//==============================================================================

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_SHRT_T
    STONEYDSP_PUBLIC_FUNCTION
    /**
     * @brief
     *
     * @return `stoneydsp_shrt_t`
     */
    stoneydsp_shrt_lowest () STONEYDSP_NOEXCEPT
{
  return stoneydsp_shrt_min ();
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

using shrt_t = stoneydsp_shrt;

//==============================================================================

namespace literals
{
/** @addtogroup literals
 * @{
 */

//==============================================================================

STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_SHRT_T STONEYDSP_PUBLIC_FUNCTION
/**
 * @brief
 *
 * @param value
 * @return `stoneydsp::shrt_t`
 */
operator"" _shrt_t (char value) STONEYDSP_NOEXCEPT
{
  return ::stoneydsp_shrt_c (value);
}

//==============================================================================

STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_SHRT_T STONEYDSP_PUBLIC_FUNCTION
/**
 * @brief
 *
 * @param value
 * @return `stoneydsp::shrt_t`
 */
operator"" _shrt_t (unsigned long long value) STONEYDSP_NOEXCEPT
{
  return ::stoneydsp_shrt_c (value);
}

//==============================================================================

/// @} literals
} // namespace literals

/// @} types
} // namespace types

/// @} group core
} //  namespace core

//==============================================================================

template <>
STONEYDSP_PACKED_STRUCT_BEGIN struct STONEYDSP_API
STONEYDSP_ALIGN (alignof (STONEYDSP_SHRT_T)) numeric_limits<STONEYDSP_SHRT_T>
{

  STONEYDSP_INLINE static STONEYDSP_CONSTEXPR STONEYDSP_SHRT_T STONEYDSP_API
  max () STONEYDSP_NOEXCEPT
  {
    return ::stoneydsp_shrt_max ();
  }

  STONEYDSP_INLINE static STONEYDSP_CONSTEXPR STONEYDSP_SHRT_T STONEYDSP_API
  min () STONEYDSP_NOEXCEPT
  {
    return ::stoneydsp_shrt_min ();
  }

  STONEYDSP_INLINE static STONEYDSP_CONSTEXPR STONEYDSP_SHRT_T STONEYDSP_API
  lowest () STONEYDSP_NOEXCEPT
  {
    return ::stoneydsp_shrt_lowest ();
  }

} STONEYDSP_PACKED_STRUCT_END;

//==============================================================================

/// @} group stoneydsp
} //  namespace stoneydsp

  #endif // STONEYDSP_CXX

//==============================================================================

#endif // STONEYDSP_CORE_TYPES_SHRT_H_INCLUDED

//=========================================================================//EOF
