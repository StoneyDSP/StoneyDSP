/**
 * @file core.h
 * @author StoneyDSP (nathanjhood@googlemail.com)
 * @brief
 * @version @STONEYDSP_CORE_VERSION@
 * @date 2025-01-27
 *
 * @copyright Copyright (c) 2025
 *
 */

#pragma once

#ifndef STONEYDSP_CORE_H_INCLUDED
  #define STONEYDSP_CORE_H_INCLUDED

//==============================================================================

  #ifdef __cplusplus

/**
 * @brief The `stoneydsp` namespace.
 * @author Nathan J. Hood (nathanjhood@googlemail.com)
 * @copyright Copyright (c) 2024
 * @version @STONEYDSP_VERSION@
 *
 */
namespace stoneydsp
{
/** @addtogroup stoneydsp
 *  @{
 */
/**
 * @brief The `stoneydsp::core` namespace.
 * @author Nathan J. Hood (nathanjhood@googlemail.com)
 * @copyright Copyright (c) 2024
 * @version @STONEYDSP_CORE_VERSION@
 *
 */
namespace core
{
/** @addtogroup core
 *  @{
 */
/**
 * @brief The `stoneydsp::core::types` namespace.
 * @author Nathan J. Hood (nathanjhood@googlemail.com)
 * @copyright Copyright (c) 2024
 * @version @STONEYDSP_CORE_VERSION@
 *
 */
namespace types
{
} // namespace types

/// @} group core
} //  namespace core

/// @} group stoneydsp
} // namespace stoneydsp

  #endif // __cplusplus

  //============================================================================//

  /**
   * @brief Internal helper for stringify pre-processor macro.
   * @param n The value to stringify.
   */
  #define __STONEYDSP_STRINGIFY_HELPER(n) #n

  /**
   * @brief Handy stringify pre-processor macro.
   * @param n The value to stringify.
   */
  #define STONEYDSP_STRINGIFY(n) __STONEYDSP_STRINGIFY_HELPER (n)

  /* Convert integer to decimal digit literals.  */
  #define STONEYDSP_DEC(n)                                                    \
    ('0' + (((n) / 10000000) % 10)), ('0' + (((n) / 1000000) % 10)),          \
        ('0' + (((n) / 100000) % 10)), ('0' + (((n) / 10000) % 10)),          \
        ('0' + (((n) / 1000) % 10)), ('0' + (((n) / 100) % 10)),              \
        ('0' + (((n) / 10) % 10)), ('0' + ((n) % 10))

  /* Convert integer to hex digit literals.  */
  #define STONEYDSP_HEX(n)                                                    \
    ('0' + ((n) >> 28 & 0xF)), ('0' + ((n) >> 24 & 0xF)),                     \
        ('0' + ((n) >> 20 & 0xF)), ('0' + ((n) >> 16 & 0xF)),                 \
        ('0' + ((n) >> 12 & 0xF)), ('0' + ((n) >> 8 & 0xF)),                  \
        ('0' + ((n) >> 4 & 0xF)), ('0' + ((n) & 0xF))

//============================================================================//

/* tring literal encoding the version number. */
extern char const *stoneydsp_version;

//====================================================================//INCLUDES

  #include "stoneydsp/core/system/compiler.h"
  #include "stoneydsp/core/system/cxx.h"
  #include "stoneydsp/core/system/languages.h"
  #include "stoneydsp/core/system/platform.h"

//==============================================================================

// for `stoneydsp_int8_t`
  #include "stoneydsp/core/types/int.h"
// for `stoneydsp_uint8_t`
  #include "stoneydsp/core/types/uint.h"
// for `stoneydsp_size_t`
  #include "stoneydsp/core/types/def.h"
// for `stoneydsp_float_t`
  #include "stoneydsp/core/types/math.h"

//==============================================================================

  #ifdef __cplusplus

namespace stoneydsp
{
/** @addtogroup stoneydsp
 *  @{
 */

/**
 * @brief Handy function for avoiding unused variables warning.
 *
 * @tparam Types
 * @return
 */
template <typename... Types>
STONEYDSP_PUBLIC_FUNCTION void
ignoreUnused (Types &&...) noexcept
{
  return;
}

namespace core
{
namespace types
{
/**
 * @brief The `stoneydsp::core::types::literals` namespace.
 *
 * @example
 * ```cpp
 * void fn() {
 *
 *     using namespace stoneydsp::core::types::literals;
 *
 *     stoneydsp::uint64_t uval_64 = 1.0_uint64;
 *
 *     stoneydsp::int64_t val_64 = -1.0_int64;
 * }
 * ```
 *
 */
namespace literals
{

/**
 * @brief
 *
 * @param value The value with which to initialize the 8-bit signed
 integer.
 *
 * @returns `stoneydsp_int8_t` The initialized 8-bit signed integer.
 *
 */
STONEYDSP_PUBLIC_FUNCTION stoneydsp::int8_t
operator"" _int8 (unsigned long long value);

/**
 * @brief
 *
 * @param value The value with which to initialize the 16-bit signed
 integer.
 *
 * @returns `stoneydsp_int16` The initialized 16-bit signed integer.
 *
 */
STONEYDSP_PUBLIC_FUNCTION stoneydsp::int16_t
operator"" _int16 (unsigned long long value);

/**
 * @brief
 *
 * @param value The value with which to initialize the 32-bit signed
 integer.
 *
 * @returns `stoneydsp_int32` The initialized 32-bit signed integer.
 *
 */
STONEYDSP_PUBLIC_FUNCTION stoneydsp::int32_t
operator"" _int32 (unsigned long long value);

/**
 * @brief
 *
 * @param value The value with which to initialize the 64-bit signed
 integer.
 *
 * @returns `stoneydsp_int64` The initialized 64-bit signed integer.
 *
 */
STONEYDSP_PUBLIC_FUNCTION stoneydsp::int64_t
operator"" _int64 (unsigned long long value);

/**
 * @brief
 *
 * @param value The value with which to initialize the 8-bit unsigned
 * integer.
 *
 * @returns `stoneydsp_uint8` The initialized 8-bit unsigned integer.
 *
 */
STONEYDSP_PUBLIC_FUNCTION stoneydsp::uint8_t
operator"" _uint8 (unsigned long long value);

/**
 * @brief
 *
 * @param value The value with which to initialize the 16-bit unsigned
 * integer.
 *
 * @returns `stoneydsp_uint16` The initialized 16-bit unsigned integer.
 *
 */
STONEYDSP_PUBLIC_FUNCTION stoneydsp::uint16_t
operator"" _uint16 (unsigned long long value);

/**
 * @brief
 *
 * @param value The value with which to initialize the 32-bit unsigned
 * integer.
 *
 * @returns `stoneydsp_uint32` The initialized 32-bit unsigned integer.
 *
 */
STONEYDSP_PUBLIC_FUNCTION stoneydsp::uint32_t
operator"" _uint32 (unsigned long long value);

/**
 * @brief
 *
 * @param value The value with which to initialize the 64-bit unsigned
 * integer.
 *
 * @returns `stoneydsp_uint64` The initialized 64-bit unsigned integer.
 *
 */
STONEYDSP_PUBLIC_FUNCTION stoneydsp::uint64_t
operator"" _uint64 (unsigned long long value);
} // namespace literals
} // namespace types
} // namespace core

/// @} group stoneydsp
} // namespace stoneydsp

  #endif // __cplusplus

//==============================================================================

#endif // STONEYDSP_CORE_H_INCLUDED

//=========================================================================//EOF
