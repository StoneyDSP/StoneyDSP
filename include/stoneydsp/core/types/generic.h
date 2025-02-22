/**
 * @file generic.h
 * @author StoneyDSP (nathanjhood@googlemail.com)
 * @brief
 * @version @STONEYDSP_CORE_VERSION@
 * @date 2025-01-30
 *
 * @copyright Copyright (c) 2025
 *
 */

#pragma once

#ifndef STONEYDSP_CORE_TYPES_GENERIC_H_INCLUDED
  #define STONEYDSP_CORE_TYPES_GENERIC_H_INCLUDED

//==============================================================================

  #ifdef __cplusplus
    #include <climits>
  #else // !__cplusplus
    #include <limits.h>
  #endif // __cplusplus

//=====================================================================//DEFINES

/**
 * @brief Number of bits in a char object (byte).
 *
 */
  #define STONEYDSP_CHAR_BIT CHAR_BIT

  /**
   * @brief Minimum value for an object of type char.
   *
   */
  #define STONEYDSP_CHAR_MIN CHAR_MIN

  /**
   * @brief Maximum value for an object of type char.
   *
   */
  #define STONEYDSP_CHAR_MAX CHAR_MAX

/**
 * @brief Minimum value for an object of type signed char.
 *
 */
  #define STONEYDSP_SCHAR_MIN SCHAR_MIN

  /**
   * @brief Maximum value for an object of type signed char.
   *
   */
  #define STONEYDSP_SCHAR_MAX SCHAR_MAX

/**
 * @brief Minimum value for an object of type unsigned char.
 *
 */
  #define STONEYDSP_UCHAR_MIN UCHAR_MIN

  /**
   * @brief Maximum value for an object of type unsigned char.
   *
   */
  #define STONEYDSP_UCHAR_MAX UCHAR_MAX

  #define STONEYDSP_SHRT_MIN SHRT_MIN

  #define STONEYDSP_SHRT_MAX SHRT_MAX

  #define STONEYDSP_USHRT_MAX USHRT_MAX

  #define STONEYDSP_LONG_MIN LONG_MIN

  #define STONEYDSP_LONG_MAX LONG_MAX

  #define STONEYDSP_ULONG_MAX ULONG_MAX

  #define STONEYDSP_LLONG_MIN LLONG_MIN

  #define STONEYDSP_LLONG_MAX LLONG_MAX

  #define STONEYDSP_ULLONG_MAX ULLONG_MAX

/**
 * @brief Maximum length of any multibyte character in any locale.
 *
 */
  #define STONEYDSP_MB_LEN_MAX MB_LEN_MAX

//====================================================================//TYPEDEFS

// typedef unsigned char stoneydsp_byte_t;

typedef char stoneydsp_char_t;

typedef signed char stoneydsp_schar_t;

typedef unsigned char stoneydsp_uchar_t;

typedef short stoneydsp_shrt_t;

typedef unsigned short stoneydsp_ushrt_t;

typedef long stoneydsp_long_t;

typedef unsigned long stoneydsp_ulong_t;

typedef long long stoneydsp_llong_t;

typedef unsigned long long stoneydsp_ullong_t;

//===================================================================//CONSTANTS

  #ifdef __cplusplus
/**
 * @brief Number of bits in a char object (byte).
 *
 */
constexpr int stoneydsp_char_bit = STONEYDSP_CHAR_BIT;
  #else  // !__cplusplus
static const int stoneydsp_char_bit = STONEYDSP_CHAR_BIT;
  #endif // __cplusplus

//==============================================================================

  #ifdef __cplusplus
namespace stoneydsp
{
namespace core
{
namespace types
{
/**
 * @brief Number of bits in a char object (byte).
 *
 */
constexpr int char_bit = ::stoneydsp_char_bit;
}
}
}
  #endif // __cplusplus

//==============================================================================

  #ifdef __cplusplus
namespace stoneydsp
{
/**
 * @brief Number of bits in a char object (byte).
 *
 */
constexpr int char_bit = ::stoneydsp::core::types::char_bit;
}
  #endif // __cplusplus

//==============================================================================

#endif // STONEYDSP_CORE_TYPES_GENERIC_H_INCLUDED

//=========================================================================//EOF
