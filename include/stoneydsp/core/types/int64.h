/**
 * @file int64.h
 * @author StoneyDSP (nathanjhood@googlemail.com)
 * @brief
 * @version @STONEYDSP_CORE_VERSION@
 * @date 2025-01-27
 *
 * @copyright Copyright (c) 2025
 *
 */

#pragma once

#ifndef STONEYDSP_CORE_TYPES_INT64_H_INCLUDED
  #define STONEYDSP_CORE_TYPES_INT64_H_INCLUDED

//==============================================================================

  #include "../../../stoneydsp/core/system/types.h"

//==============================================================================

  #if defined(STONEYDSP_WINDOWS) || defined(STONEYDSP_32BIT)

    #include "../../../stoneydsp/core/types/llong.h" // for numerical_limits<llong_t>

  #elif (defined(STONEYDSP_LINUX) || defined(STONEYDSP_MAC))                  \
      && (defined(STONEYDSP_64BIT) || defined(STONEYDSP_ARM))

    #include "../../../stoneydsp/core/types/long.h" // for numerical_limits<long_t>

  #else

    #error unable to determine a suitable template for numerical_limits<int64_t>

  #endif

//==============================================================================

/**
 * @brief
 *
 */
typedef STONEYDSP_INT64_T stoneydsp_int64_t;

//==============================================================================

  /**
   * @brief
   *
   */
  #define stoneydsp_int64 stoneydsp_int64_t

//==============================================================================

typedef stoneydsp_int64 stoneydsp_int64;

//==============================================================================

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_INT64_T
    STONEYDSP_PUBLIC_FUNCTION
    stoneydsp_int64_c (unsigned long long value) STONEYDSP_NOEXCEPT
{
  return (STONEYDSP_INT64_C (value));
}

//==============================================================================

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_INT64_T
    STONEYDSP_PUBLIC_FUNCTION
    /**
     * @brief
     *
     * @return `stoneydsp_int64_t`
     *
     */
    stoneydsp_int64_max () STONEYDSP_NOEXCEPT
{
  return stoneydsp_int64_c (STONEYDSP_INT64_MAX);
}

//==============================================================================

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_INT64_T
    STONEYDSP_PUBLIC_FUNCTION
    /**
     * @brief
     *
     * @return `stoneydsp_int64_t`
     *
     */
    stoneydsp_int64_min () STONEYDSP_NOEXCEPT
{
  return stoneydsp_int64_c (
      (-stoneydsp_int64_max ())
      - (stoneydsp_int64_c (STONEYDSP_INT64_LITERAL (1))));
}

//==============================================================================

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_INT64_T
    STONEYDSP_PUBLIC_FUNCTION
    stoneydsp_int64_lowest () STONEYDSP_NOEXCEPT
{
  return stoneydsp_int64_min ();
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
using int64_t = stoneydsp_int64;

//==============================================================================

namespace literals
{
/** @addtogroup literals
 * @{
 */

//==============================================================================

STONEYDSP_INLINE
STONEYDSP_CONSTEXPR STONEYDSP_INT64_T STONEYDSP_PUBLIC_FUNCTION
/**
 * @brief
 *
 * @param value
 *
 * @return `stoneydsp::int64_t`
 *
 */
operator"" _int64_t (char value) STONEYDSP_NOEXCEPT
{
  return ::stoneydsp_int64_c (value);
}

//==============================================================================

STONEYDSP_INLINE
STONEYDSP_CONSTEXPR STONEYDSP_INT64_T STONEYDSP_PUBLIC_FUNCTION
/**
 * @brief
 *
 */
operator"" _int64_t (unsigned long long value) STONEYDSP_NOEXCEPT
{
  return ::stoneydsp_int64_c (value);
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

#endif // STONEYDSP_CORE_TYPES_INT64_H_INCLUDED

//=========================================================================//EOF
