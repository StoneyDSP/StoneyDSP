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

  #if 0
/**
 * BEGIN_JUCE_MODULE_DECLARATION
 *
 * ID:               stoneydsp_core
 * vendor:           stoneydsp
 * version:          @STONEYDSP_CORE_VERSION@
 * name:             core
 * description:      Core module
 * website:          http://github.com/StoneyDSP/StoneyDSP
 * license:          MIT
 *
 * END_JUCE_MODULE_DECLARATION
 */
  #endif

//==============================================================================

  #ifdef __cplusplus

// Forward-declaration of core namespaces

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
/** @addtogroup types
 * @{
 */

/**
 * @brief The `stoneydsp::core::types::literals` namespace.
 * @author Nathan J. Hood (nathanjhood@googlemail.com)
 * @copyright Copyright (c) 2024
 * @version @STONEYDSP_CORE_VERSION@
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
 */
namespace literals
{
}
/// @} types
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

/* string literal encoding the version number. */
extern char const *stoneydsp_version;

//====================================================================//INCLUDES

  #include "stoneydsp/core/system/platform.h"

  #include "stoneydsp/core/system/compiler.h"

  #include "stoneydsp/core/system/languages.h"

  #include "stoneydsp/core/system/cxx.h"

  #include "stoneydsp/core/system/types.h"

//==============================================================================

  #include "stoneydsp/core/types/char.h"

  #include "stoneydsp/core/types/schar.h"

  #include "stoneydsp/core/types/uchar.h"

  #include "stoneydsp/core/types/shrt.h"

  #include "stoneydsp/core/types/ushrt.h"

  #include "stoneydsp/core/types/int.h"

  #include "stoneydsp/core/types/uint.h"

  #include "stoneydsp/core/types/long.h"

  #include "stoneydsp/core/types/ulong.h"

  #include "stoneydsp/core/types/llong.h"

  #include "stoneydsp/core/types/ullong.h"

  #include "stoneydsp/core/types/double.h"

  #include "stoneydsp/core/types/ldouble.h"

  #include "stoneydsp/core/types/float.h"

  #include "stoneydsp/core/types/bool.h"

  #include "stoneydsp/core/types/size.h"

  #include "stoneydsp/core/types/ptrdiff.h"

//==============================================================================

  #include "stoneydsp/core/types/int8.h"

  #include "stoneydsp/core/types/int16.h"

  #include "stoneydsp/core/types/int32.h"

  #include "stoneydsp/core/types/int64.h"

//==============================================================================

  #include "stoneydsp/core/types/uint8.h"

  #include "stoneydsp/core/types/uint16.h"

  #include "stoneydsp/core/types/uint32.h"

  #include "stoneydsp/core/types/uint64.h"

//==============================================================================

  #ifndef STONEYDSP_CORE_NS_USE_GENERIC_TYPE_ALIASES
    #define STONEYDSP_CORE_NS_USE_GENERIC_TYPE_ALIASES 0
  #endif

  #ifndef STONEYDSP_CORE_NS_USE_FIXED_TYPE_ALIASES
    #define STONEYDSP_CORE_NS_USE_FIXED_TYPE_ALIASES 1
  #endif

//==============================================================================

  #ifdef STONEYDSP_CXX

namespace stoneydsp
{
/** @addtogroup stoneydsp
 *  @{
 */

template <typename... Types>
void STONEYDSP_PUBLIC_FUNCTION
/**
 * @brief Handy function for avoiding unused variables warning.
 *
 * @tparam Types
 */
ignoreUnused (Types &&...) STONEYDSP_NOEXCEPT
{
  return;
}

  //=====================================================================//ALIASES

    #if STONEYDSP_CORE_NS_USE_GENERIC_TYPE_ALIASES

/** @brief */
using ::stoneydsp::core::types::bool_t;

/** @brief */
using ::stoneydsp::core::types::double_t;

/** @brief */
using ::stoneydsp::core::types::float_t;

/** @brief */
using ::stoneydsp::core::types::char_t;

/** @brief */
using ::stoneydsp::core::types::schar_t;

/** @brief */
using ::stoneydsp::core::types::uchar_t;

/** @brief */
using ::stoneydsp::core::types::shrt_t;

/** @brief */
using ::stoneydsp::core::types::ushrt_t;

/** @brief */
using ::stoneydsp::core::types::int_t;

/** @brief */
using ::stoneydsp::core::types::uint_t;

/** @brief */
using ::stoneydsp::core::types::long_t;

/** @brief */
using ::stoneydsp::core::types::ulong_t;

/** @brief */
using ::stoneydsp::core::types::llong_t;

/** @brief */
using ::stoneydsp::core::types::ullong_t;

    #endif // STONEYDSP_CORE_NS_USE_GENERIC_TYPE_ALIASES

  //==============================================================================

    #if STONEYDSP_CORE_NS_USE_FIXED_TYPE_ALIASES

/** @brief */
using ::stoneydsp::core::types::int8_t;

/** @brief */
using ::stoneydsp::core::types::int16_t;

/** @brief */
using ::stoneydsp::core::types::int32_t;

/** @brief */
using ::stoneydsp::core::types::int64_t;

//==============================================================================

/** @brief */
using ::stoneydsp::core::types::uint8_t;

/** @brief */
using ::stoneydsp::core::types::uint16_t;

/** @brief */
using ::stoneydsp::core::types::uint32_t;

/** @brief */
using ::stoneydsp::core::types::uint64_t;

    #endif // STONEYDSP_CORE_NS_USE_FIXED_TYPE_ALIASES

//==============================================================================

/// @} group stoneydsp
} // namespace stoneydsp

  #endif // STONEYDSP_CXX

//==============================================================================

#endif // STONEYDSP_CORE_H_INCLUDED

//=========================================================================//EOF
