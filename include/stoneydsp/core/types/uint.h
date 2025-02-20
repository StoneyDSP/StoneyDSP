/**
 * @file uint.h
 * @author StoneyDSP (nathanjhood@googlemail.com)
 * @brief
 * @version @STONEYDSP_CORE_VERSION@
 * @date 2025-01-30
 *
 * @copyright Copyright (c) 2025
 *
 */

#pragma once

#ifndef STONEYDSP_CORE_TYPES_UINT_H_INCLUDED
  #define STONEYDSP_CORE_TYPES_UINT_H_INCLUDED

//====================================================================//INCLUDES

  #ifdef __cplusplus
    #include <cstdint>
  #else
    #include <stdint.h>
  #endif // __cplusplus

//=====================================================================//DEFINES

  #ifdef __cplusplus
    /**
     * @brief
     *
     */
    #define STONEYDSP_UINT8_T ::std::uint8_t
    /**
     * @brief
     *
     */
    #define STONEYDSP_UINT16_T ::std::uint16_t
    /**
     * @brief
     *
     */
    #define STONEYDSP_UINT32_T ::std::uint32_t
    /**
     * @brief
     *
     */
    #define STONEYDSP_UINT64_T ::std::uint64_t
    /**
     * @brief
     *
     */
    #define STONEYDSP_UINTMAX_T ::std::uintmax_t
    /**
     * @brief
     *
     */
    #define STONEYDSP_UINTPTR_T ::std::uintptr_t
  #else // !__cplusplus
    /**
     * @brief
     *
     */
    #define STONEYDSP_UINT8_T uint8_t
    /**
     * @brief
     *
     */
    #define STONEYDSP_UINT16_T uint16_t
    /**
     * @brief
     *
     */
    #define STONEYDSP_UINT32_T uint32_t
    /**
     * @brief
     *
     */
    #define STONEYDSP_UINT64_T uint64_t
    /**
     * @brief
     *
     */
    #define STONEYDSP_UINTMAX_T uintmax_t
    /**
     * @brief
     *
     */
    #define STONEYDSP_UINTPTR_T uintptr_t
  #endif // __cplusplus

  /**
   * @brief Maximum value of largest unsigned integral type
   * `stoneydsp_uintmax_t`.
   *
   */
  #define STONEYDSP_UINTMAX_MAX UINTMAX_MAX

//====================================================================//TYPEDEFS

/**
 * @brief
 *
 */
typedef STONEYDSP_UINT8_T stoneydsp_uint8_t;

/**
 * @brief
 *
 */
typedef STONEYDSP_UINT16_T stoneydsp_uint16_t;

/**
 * @brief
 *
 */
typedef STONEYDSP_UINT32_T stoneydsp_uint32_t;

/**
 * @brief
 *
 */
typedef STONEYDSP_UINT64_T stoneydsp_uint64_t;

/**
 * @brief
 *
 */
typedef STONEYDSP_UINTMAX_T stoneydsp_uintmax_t;

/**
 * @brief
 *
 */
typedef STONEYDSP_UINTPTR_T stoneydsp_uintptr_t;

//===================================================================//CONSTANTS

// Maximum constraints

  /**
   * @brief Maximum value of exact-width unsigned type `stoneydsp_uint8_t`.
   *
   */
  #define STONEYDSP_UINT8_MAX UINT8_MAX

  /**
   * @brief Maximum value of exact-width unsigned type `stoneydsp_uint16_t`.
   *
   */
  #define STONEYDSP_UINT16_MAX UINT16_MAX

  /**
   * @brief Maximum value of exact-width unsigned type `stoneydsp_uint32_t`.
   *
   */
  #define STONEYDSP_UINT32_MAX UINT32_MAX

  /**
   * @brief Maximum value of exact-width unsigned type `stoneydsp_uint64_t`.
   *
   */
  #define STONEYDSP_UINT64_MAX UINT64_MAX

  /**
   * @brief Maximum value of largest unsigned integral type
   * `stoneydsp_uintmax_t`.
   *
   */
  #define STONEYDSP_UINTMAX_MAX UINTMAX_MAX

  /**
   * @brief Maximum value of unsigned integral type `stoneydsp_uintptr_t`.
   *
   */
  #define STONEYDSP_UINTPTR_MAX UINTPTR_MAX

  #ifdef __cplusplus
/**
 * @brief Maximum value of exact-width unsigned type `stoneydsp_uint8_t`.
 *
 * Equivalent to:
 *
 * `(255U)`
 */
constexpr ::stoneydsp_uint8_t stoneydsp_uint8_max = STONEYDSP_UINT8_MAX;
/**
 * @brief Maximum value of exact-width unsigned type `stoneydsp_uint16_t`.
 *
 * Equivalent to:
 *
 * `(65535U)`
 */
constexpr ::stoneydsp_uint16_t stoneydsp_uint16_max = STONEYDSP_UINT16_MAX;
/**
 * @brief Maximum value of exact-width unsigned type `stoneydsp_uint32_t`.
 *
 * Equivalent to:
 *
 * `(4294967295U)`
 */
constexpr ::stoneydsp_uint32_t stoneydsp_uint32_max = STONEYDSP_UINT32_MAX;
/**
 * @brief Maximum value of exact-width unsigned type `stoneydsp_uint64_t`.
 *
 * Equivalent to:
 *
 * `(18446744073709551615UL)`
 */
constexpr ::stoneydsp_uint64_t stoneydsp_uint64_max = STONEYDSP_UINT64_MAX;
/**
 * @brief Maximum value of exact-width unsigned type `stoneydsp_uintmax_t`.
 *
 */
constexpr ::stoneydsp_uintmax_t stoneydsp_uintmax_max = STONEYDSP_UINTMAX_MAX;
/**
 * @brief Maximum value of exact-width unsigned type `stoneydsp_uintptr_t`.
 *
 */
constexpr ::stoneydsp_uintptr_t stoneydsp_uintptr_max = STONEYDSP_UINTPTR_MAX;
  #else  // !__cplusplus
/**
 * @brief Maximum value of exact-width unsigned type `stoneydsp_uint8_t`.
 *
 * Equivalent to:
 *
 * `(255U)`
 */
static const stoneydsp_uint8_t stoneydsp_uint8_max = STONEYDSP_UINT8_MAX;
/**
 * @brief Maximum value of exact-width unsigned type `stoneydsp_uint16_t`.
 *
 * Equivalent to:
 *
 * `(65535U)`
 */
static const stoneydsp_uint16_t stoneydsp_uint16_max = STONEYDSP_UINT16_MAX;
/**
 * @brief Maximum value of exact-width unsigned type `stoneydsp_uint32_t`.
 *
 * Equivalent to:
 *
 * `(4294967295U)`
 */
static const stoneydsp_uint32_t stoneydsp_uint32_max = STONEYDSP_UINT32_MAX;
/**
 * @brief Maximum value of exact-width unsigned type `stoneydsp_uint64_t`.
 *
 * Equivalent to:
 *
 * `(18446744073709551615UL)`
 */
static const stoneydsp_uint64_t stoneydsp_uint64_max = STONEYDSP_UINT64_MAX;
/**
 * @brief Maximum value of exact-width unsigned type `stoneydsp_uintmax_t`.
 *
 */
static const stoneydsp_uintmax_t stoneydsp_uintmax_max = STONEYDSP_UINTMAX_MAX;
/**
 * @brief Maximum value of exact-width unsigned type `stoneydsp_uintptr_t`.
 *
 */
static const stoneydsp_uintptr_t stoneydsp_uintptr_max = STONEYDSPU_INTPTR_MAX;
  #endif // __cplusplus

//===================================================================//FUNCTIONS

#define STONEYDSP_UINT8_C(c) UINT8_C (c)

#define STONEYDSP_UINT16_C(c) UINT16_C (c)

#define STONEYDSP_UINT32_C(c) UINT32_C (c)

#define STONEYDSP_UINT64_C(c) UINT64_C (c)

#define STONEYDSP_UINTMAX_C(c) UINTMAX_C (c)

//==============================================================================

  #ifdef __cplusplus

namespace stoneydsp
{
namespace core
{
namespace types
{
/**
 * @brief
 *
 */
using uint8_t = ::stoneydsp_uint8_t;
/**
 * @brief
 *
 */
using uint16_t = ::stoneydsp_uint16_t;
/**
 * @brief
 *
 */
using uint32_t = ::stoneydsp_uint32_t;
/**
 * @brief
 *
 */
using uint64_t = ::stoneydsp_uint64_t;
/**
 * @brief
 *
 */
using uintmax_t = ::stoneydsp_uintmax_t;
/**
 * @brief
 *
 */
using uintptr_t = ::stoneydsp_uintptr_t;
/**
 * @brief Maximum value of exact-width unsigned type
 * `stoneydsp::core::types::uint8_t`.
 *
 * Equivalent to:
 *
 * `(127)`
 */
constexpr ::stoneydsp::core::types::uint8_t uint8_max = ::stoneydsp_uint8_max;
/**
 * @brief Maximum value of exact-width unsigned type
 * `stoneydsp::core::types::uint16_t`.
 *
 * Equivalent to:
 *
 * `(32767)`
 */
constexpr ::stoneydsp::core::types::uint16_t uint16_max
    = ::stoneydsp_uint16_max;
/**
 * @brief Maximum value of exact-width unsigned type
 * `stoneydsp::core::types::uint32_t`.
 *
 * Equivalent to:
 *
 * `(2147483647)`
 */
constexpr ::stoneydsp::core::types::uint32_t uint32_max
    = ::stoneydsp_uint32_max;
/**
 * @brief Maximum value of exact-width unsigned type
 * `stoneydsp::core::types::uint64_t`.
 *
 * Equivalent to:
 *
 * `(9223372036854775807L)`
 */
constexpr ::stoneydsp::core::types::uint64_t uint64_max
    = ::stoneydsp_uint64_max;
/**
 * @brief Maximum value of exact-width unsigned type
 * `stoneydsp::core::types::uintmax_t`.
 *
 */
constexpr ::stoneydsp::core::types::uintmax_t uintmax_max
    = ::stoneydsp_uintmax_max;
/**
 * @brief Maximum value of exact-width unsigned type
 * `stoneydsp::core::types::uintptr_t`.
 *
 */
constexpr ::stoneydsp::core::types::uintptr_t uintptr_max
    = ::stoneydsp_uintptr_max;

} // namespace types
} // namespace core
} // namespace stoneydsp

  #endif // __cplusplus

//==============================================================================

  #ifdef __cplusplus

namespace stoneydsp
{
/**
 * @brief
 *
 */
using uint8_t = ::stoneydsp::core::types::uint8_t;
/**
 * @brief
 *
 */
using uint16_t = ::stoneydsp::core::types::uint16_t;
/**
 * @brief
 *
 */
using uint32_t = ::stoneydsp::core::types::uint32_t;
/**
 * @brief
 *
 */
using uint64_t = ::stoneydsp::core::types::uint64_t;
/**
 * @brief
 *
 */
using uintmax_t = ::stoneydsp::core::types::uintmax_t;
/**
 * @brief
 *
 */
using uintptr_t = ::stoneydsp::core::types::uintptr_t;
/**
 * @brief Maximum value of exact-width unsigned type `stoneydsp::uint8_t`.
 *
 * Equivalent to:
 *
 * `(127)`
 */
constexpr ::stoneydsp::uint8_t uint8_max = ::stoneydsp::core::types::uint8_max;
/**
 * @brief Maximum value of exact-width unsigned type `stoneydsp::uint16_t`.
 *
 * Equivalent to:
 *
 * `(32767)`
 */
constexpr ::stoneydsp::uint16_t uint16_max = ::stoneydsp::core::types::uint16_max;
/**
 * @brief Maximum value of exact-width unsigned type `stoneydsp::uint32_t`.
 *
 * Equivalent to:
 *
 * `(2147483647)`
 */
constexpr ::stoneydsp::uint32_t uint32_max = ::stoneydsp::core::types::uint32_max;
/**
 * @brief Maximum value of exact-width unsigned type `stoneydsp::uint64_t`.
 *
 * Equivalent to:
 *
 * `(9223372036854775807L)`
 */
constexpr ::stoneydsp::uint64_t uint64_max = ::stoneydsp::core::types::uint64_max;
/**
 * @brief Maximum value of exact-width unsigned type `stoneydsp::uintmax_t`.
 *
 */
constexpr ::stoneydsp::uintmax_t uintmax_max
    = ::stoneydsp::core::types::uintmax_max;
/**
 * @brief Maximum value of exact-width unsigned type `stoneydsp::uintptr_t`.
 *
 */
constexpr ::stoneydsp::uintptr_t uintptr_max
    = ::stoneydsp::core::types::uintptr_max;

} // namespace stoneydsp

  #endif // __cplusplus

//==============================================================================

#endif // STONEYDSP_CORE_TYPES_UINT_H_INCLUDED

//=========================================================================//EOF
