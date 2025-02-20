/**
 * @file def.h
 * @author StoneyDSP (nathanjhood@googlemail.com)
 * @brief
 * @version @STONEYDSP_CORE_VERSION@
 * @date 2025-01-30
 *
 * @copyright Copyright (c) 2025
 *
 */

#pragma once

#ifndef STONEYDSP_CORE_TYPES_DEF_H_INCLUDED
  #define STONEYDSP_CORE_TYPES_DEF_H_INCLUDED

//====================================================================//INCLUDES

  #ifdef __cplusplus
    #include <cstddef>
    #include <cstdint>
  #else
    #include <stddef.h>
    #include <stdint.h>
  #endif

//=====================================================================//DEFINES

/**
 * @brief A null-pointer constant is either an integral constant expression
 * that evaluates to zero (such as `0` or `0L`), or a value of type `nullptr_t`
 * (such as `nullptr`).
 *
 */
  #define STONEYDSP_NULL NULL

/**
 * @brief Maximum value of `stoneydsp_size_t`.
 *
 */
  #define STONEYDSP_SIZE_MAX SIZE_MAX

/**
 * @brief Minimum value of `stoneydsp_ptr_t`.
 *
 */
  #define STONEYDSP_PTRDIFF_MIN PTRDIFF_MIN

/**
 * @brief Maximum value of `stoneydsp_ptr_t`.
 *
 */
  #define STONEYDSP_PTRDIFF_MAX PTRDIFF_MAX

  #ifdef __cplusplus
    /**
     * @brief
     *
     */
    #define STONEYDSP_SIZE_T ::std::size_t
    /**
     * @brief
     *
     */
    #define STONEYDSP_PTRDIFF_T ::std::ptrdiff_t
    /**
     * @brief
     *
     */
    #define STONEYDSP_NULLPTR_T ::std::nullptr_t
    /**
     * @brief
     *
     */
    #define STONEYDSP_MAX_ALIGN_T ::std::max_align_t
  #else // !__cplusplus
    /**
     * @brief
     *
     */
    #define STONEYDSP_SIZE_T size_t
    /**
     * @brief
     *
     */
    #define STONEYDSP_PTRDIFF_T ptrdiff_t
    /**
     * @brief
     *
     */
    #define STONEYDSP_NULLPTR_T nullptr_t
    /**
     * @brief
     *
     */
    #define STONEYDSP_MAX_ALIGN_T max_align_t
  #endif // __cplusplus

//====================================================================//TYPEDEFS

/**
 * @brief
 *
 */
typedef STONEYDSP_SIZE_T stoneydsp_size_t;

/**
 * @brief
 *
 */
typedef STONEYDSP_PTRDIFF_T stoneydsp_ptrdiff_t;

/**
 * @brief
 *
 */
typedef STONEYDSP_NULLPTR_T stoneydsp_nullptr_t;

/**
 * @brief
 *
 */
typedef STONEYDSP_MAX_ALIGN_T stoneydsp_max_align_t;

//===================================================================//CONSTANTS

  #ifdef __cplusplus
/**
 * @brief Maximum value of `stoneydsp::size_t`.
 *
 * Expands to:
 *
 * `(18446744073709551615UL)`
 */
constexpr ::stoneydsp_size_t stoneydsp_size_max = STONEYDSP_SIZE_MAX;
/**
 * @brief Minimum value of `stoneydsp::ptrdiff_t`.
 *
 * Expands to:
 *
 * `(-9223372036854775807L-1)`
 */
constexpr ::stoneydsp_ptrdiff_t stoneydsp_ptrdiff_min = STONEYDSP_PTRDIFF_MIN;
/**
 * @brief Maximum value of `stoneydsp::ptrdiff_t`.
 *
 * Expands to:
 *
 * `(9223372036854775807L)`
 */
constexpr ::stoneydsp_ptrdiff_t stoneydsp_ptrdiff_max = STONEYDSP_PTRDIFF_MAX;
  #else  // !__cplusplus
/**
 * @brief Maximum value of `stoneydsp_size_t`.
 *
 * Expands to:
 *
 * `(18446744073709551615UL)`
 */
static const stoneydsp_size_t stoneydsp_size_max = STONEYDSP_SIZE_MAX;
/**
 * @brief Minimum value of `stoneydsp_ptrdiff_t`.
 *
 * Expands to:
 *
 * `(-9223372036854775807L-1)`
 */
static const stoneydsp_ptrdiff_t stoneydsp_ptrdiff_min = STONEYDSP_PTRDIFF_MIN;
/**
 * @brief Maximum value of `stoneydsp_ptrdiff_t`.
 *
 * Expands to:
 *
 * `(9223372036854775807L)`
 */
static const stoneydsp_ptrdiff_t stoneydsp_ptrdiff_max = STONEYDSP_PTRDIFF_MAX;
  #endif //  __cplusplus

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
using size_t = ::stoneydsp_size_t;
/**
 * @brief
 *
 */
using ptrdiff_t = ::stoneydsp_ptrdiff_t;
/**
 * @brief
 *
 */
using nullptr_t = ::stoneydsp_nullptr_t;
/**
 * @brief
 *
 */
using max_align_t = ::stoneydsp_max_align_t;
/**
 * @brief Maximum value of `stoneydsp::size_t`.
 *
 * Expands to:
 *
 * `(18446744073709551615UL)`
 */
constexpr ::stoneydsp::core::types::size_t size_max = ::stoneydsp_size_max;
/**
 * @brief Minimum value of `stoneydsp::ptrdiff_t`.
 *
 * Expands to:
 *
 * `(-9223372036854775807L-1)`
 */
constexpr ::stoneydsp::core::types::ptrdiff_t ptrdiff_min
    = ::stoneydsp_ptrdiff_min;
/**
 * @brief Maximum value of `stoneydsp::ptrdiff_t`.
 *
 * Expands to:
 *
 * `(9223372036854775807L)`
 */
constexpr ::stoneydsp::core::types::ptrdiff_t ptrdiff_max
    = ::stoneydsp_ptrdiff_max;
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
using size_t = ::stoneydsp::core::types::size_t;
/**
 * @brief
 *
 */
using ptrdiff_t = ::stoneydsp::core::types::ptrdiff_t;
/**
 * @brief
 *
 */
using nullptr_t = ::stoneydsp::core::types::nullptr_t;
/**
 * @brief
 *
 */
using max_align_t = ::stoneydsp::core::types::max_align_t;
/**
 * @brief Maximum value of `stoneydsp::size_t`.
 *
 * Expands to:
 *
 * `(18446744073709551615UL)`
 */
constexpr ::stoneydsp::size_t size_max = ::stoneydsp::core::types::size_max;
/**
 * @brief Minimum value of `stoneydsp::ptrdiff_t`.
 *
 * Expands to:
 *
 * `(-9223372036854775807L-1)`
 */
constexpr ::stoneydsp::ptrdiff_t ptrdiff_min
    = ::stoneydsp::core::types::ptrdiff_min;
/**
 * @brief Maximum value of `stoneydsp::ptrdiff_t`.
 *
 * Expands to:
 *
 * `(9223372036854775807L)`
 */
constexpr ::stoneydsp::ptrdiff_t ptrdiff_max
    = ::stoneydsp::core::types::ptrdiff_max;
} // namespace stoneydsp

  #endif // __cplusplus

//==============================================================================

#endif // STONEYDSP_CORE_TYPES_DEF_H_INCLUDED

//=========================================================================//EOF
