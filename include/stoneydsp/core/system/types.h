#pragma once

#ifndef STONEYDSP_CORE_SYSTEM_TYPES_H_INCLUDED
  #define STONEYDSP_CORE_SYSTEM_TYPES_H_INCLUDED

//==============================================================================

  #include "../../../stoneydsp/core/system/platform.h"

  #include "../../../stoneydsp/core/system/languages.h"

  #include "../../../stoneydsp/core/system/compiler.h"

  #include "../../../stoneydsp/core/system/cxx.h"

//==============================================================================

  #ifdef STONEYDSP_CXX
    #include <cfloat>
    #include <cinttypes>
    #include <climits>
    #include <cstdbool>
    #include <cstddef>
    #include <cstdint>
    #include <cuchar>
  #else // !STONEYDSP_CXX
    #include <float.h>
    #include <inttypes.h>
    #include <limits.h>
    #include <stdbool.h>
    #include <stddef.h>
    #include <stdint.h>
    #include <uchar.h>
  #endif // STONEYDSP_CXX

//==============================================================================

// typedef unsigned char stoneydsp_byte_t;

  #define STONEYDSP_CHAR_T char
  #define STONEYDSP_SCHAR_T signed char
  #define STONEYDSP_UCHAR_T unsigned char

  #define STONEYDSP_INT_T signed int
  #define STONEYDSP_UINT_T unsigned int

  #define STONEYDSP_SHRT_T signed short int
  #define STONEYDSP_USHRT_T unsigned short int

  #define STONEYDSP_LONG_T signed long int
  #define STONEYDSP_ULONG_T unsigned long int

  #define STONEYDSP_LLONG_T signed long long int
  #define STONEYDSP_ULLONG_T unsigned long long int

  #define STONEYDSP_DBL_T double
  #define STONEYDSP_LDBL_T long double
  #define STONEYDSP_FLT_T float

  #define STONEYDSP_BOOL_T bool

  #ifndef STONEYDSP_DISABLE_STD_TYPES
    #ifdef STONEYDSP_CXX
    // #define STONEYDSP_CHAR8_T ::std::char8_t
    // #define STONEYDSP_CHAR16_T ::std::char16_t
    // #define STONEYDSP_CHAR32_T ::std::char32_t

      #define STONEYDSP_INT8_T ::std::int8_t
      #define STONEYDSP_INT16_T ::std::int16_t
      #define STONEYDSP_INT32_T ::std::int32_t

      #define STONEYDSP_UINT8_T ::std::uint8_t
      #define STONEYDSP_UINT16_T ::std::uint16_t
      #define STONEYDSP_UINT32_T ::std::uint32_t

      #define STONEYDSP_SIZE_T ::std::size_t
      #define STONEYDSP_PTRDIFF_T ::std::ptrdiff_t
      #define STONEYDSP_NULLPTR_T ::std::nullptr_t
      #define STONEYDSP_MAX_ALIGN_T ::std::max_align_t

    #else // !STONEYDSP_CXX
    // #define STONEYDSP_CHAR8_T char8_t
    // #define STONEYDSP_CHAR16_T char16_t
    // #define STONEYDSP_CHAR32_T char32_t

      #define STONEYDSP_INT8_T int8_t
      #define STONEYDSP_INT16_T int16_t
      #define STONEYDSP_INT32_T int32_t

      #define STONEYDSP_UINT8_T uint8_t
      #define STONEYDSP_UINT16_T uint16_t
      #define STONEYDSP_UINT32_T uint32_t

      #define STONEYDSP_SIZE_T size_t
      #define STONEYDSP_PTRDIFF_T ptrdiff_t
      #define STONEYDSP_NULLPTR_T nullptr_t
      #define STONEYDSP_MAX_ALIGN_T max_align_t

    #endif // STONEYDSP_CXX
  #else    // !STONEYDSP_USE_STD_TYPES

  // #define STONEYDSP_CHAR8_T STONEYDSP_UCHAR_T
  // #define STONEYDSP_CHAR16_T STONEYDSP_USHRT_T
  // #define STONEYDSP_CHAR32_T STONEYDSP_UINT_T

    #define STONEYDSP_INT8_T STONEYDSP_SCHAR_T
    #define STONEYDSP_INT16_T STONEYDSP_SHRT_T
    #define STONEYDSP_INT32_T STONEYDSP_INT_T

    #define STONEYDSP_UINT8_T STONEYDSP_UCHAR_T
    #define STONEYDSP_UINT16_T STONEYDSP_USHRT_T
    #define STONEYDSP_UINT32_T STONEYDSP_UINT_T

    #define STONEYDSP_SIZE_T (decltype (sizeof (void *)))
    #define STONEYDSP_PTRDIFF_T                                               \
      (decltype (static_cast<int *> (nullptr) - static_cast<int *> (nullptr)))
  // #define STONEYDSP_NULLPTR_T  nullptr_t
  // #define STONEYDSP_MAX_ALIGN_T  max_align_t

  #endif // !STONEYDSP_DISABE_STD_TYPES

  #if STONEYDSP_WINDOWS
    #define STONEYDSP_INT64_T STONEYDSP_LLONG_T
    #define STONEYDSP_UINT64_T STONEYDSP_ULLONG_T
  #elif STONEYDSP_LINUX || STONEYDSP_MAC
    #if STONEYDSP_32BIT
      #define STONEYDSP_INT64_T STONEYDSP_LLONG_T
      #define STONEYDSP_UINT64_T STONEYDSP_ULLONG_T
    #elif STONEYDSP_64BIT || STONEYDSP_ARM64
      #define STONEYDSP_INT64_T STONEYDSP_LONG_T
      #define STONEYDSP_UINT64_T STONEYDSP_ULONG_T
    #endif
  #endif

//==============================================================================

  #define STONEYDSP_DBL_LITERAL(n) n
  #define STONEYDSP_LDBL_LITERAL(n) n##L
  #define STONEYDSP_FLT_LITERAL(n) n##F

  #define STONEYDSP_CHAR_LITERAL(n) n
  #define STONEYDSP_SCHAR_LITERAL(n) n
  #define STONEYDSP_UCHAR_LITERAL(n) n

  #define STONEYDSP_INT_LITERAL(n) n
  #define STONEYDSP_UINT_LITERAL(n) n##U

  #define STONEYDSP_SHRT_LITERAL(n) n
  #define STONEYDSP_USHRT_LITERAL(n) n // ##U

  #define STONEYDSP_LONG_LITERAL(n) n##L
  #define STONEYDSP_ULONG_LITERAL(n) n##UL

  #define STONEYDSP_LLONG_LITERAL(n) n##LL
  #define STONEYDSP_ULLONG_LITERAL(n) n##ULL

// #define STONEYDSP_CHAR8_LITERAL(n) n
// #define STONEYDSP_CHAR16_LITERAL(n) n
// #define STONEYDSP_CHAR32_LITERAL(n) n

  #define STONEYDSP_INT8_LITERAL(n) STONEYDSP_SCHAR_LITERAL (n)
  #define STONEYDSP_INT16_LITERAL(n) STONEYDSP_SHRT_LITERAL (n)
  #define STONEYDSP_INT32_LITERAL(n) STONEYDSP_INT_LITERAL (n)
  #define STONEYDSP_INT64_LITERAL(n) n

  #define STONEYDSP_UINT8_LITERAL(n) STONEYDSP_UCHAR_LITERAL (n)
  #define STONEYDSP_UINT16_LITERAL(n) STONEYDSP_USHRT_LITERAL (n)
  #define STONEYDSP_UINT32_LITERAL(n) STONEYDSP_UINT_LITERAL (n)
  #define STONEYDSP_UINT64_LITERAL(n) n

  #define STONEYDSP_SIZE_LITERAL(n) n
  #define STONEYDSP_PTRDIFF_LITERAL(n) n

//==============================================================================

  #ifndef STONEYDSP_CXX

    #define STONEYDSP_BOOL_C(n) ((STONEYDSP_BOOL_T)n)

    #define STONEYDSP_DBL_C(n) ((STONEYDSP_DBL_T)n)
    #define STONEYDSP_LDBL_C(n) ((STONEYDSP_LDBL_T)n)
    #define STONEYDSP_FLT_C(n) ((STONEYDSP_FLT_T)n)

    #define STONEYDSP_CHAR_C(n) ((STONEYDSP_CHAR_T)n)
    #define STONEYDSP_SCHAR_C(n) ((STONEYDSP_SCHAR_T)n)
    #define STONEYDSP_UCHAR_C(n) ((STONEYDSP_UCHAR_T)n)

    #define STONEYDSP_INT_C(n) ((STONEYDSP_INT_T)n)
    #define STONEYDSP_UINT_C(n) ((STONEYDSP_UINT_T)n)

    #define STONEYDSP_SHRT_C(n) ((STONEYDSP_SHRT_T)n)
    #define STONEYDSP_USHRT_C(n) ((STONEYDSP_USHRT_T)n)

    #define STONEYDSP_LONG_C(n) ((STONEYDSP_LONG_T)n)
    #define STONEYDSP_ULONG_C(n) ((STONEYDSP_ULONG_T)n)

    #define STONEYDSP_LLONG_C(n) ((STONEYDSP_LLONG_T)n)
    #define STONEYDSP_ULLONG_C(n) ((STONEYDSP_ULLONG_T)n)

  // #define STONEYDSP_CHAR8_C(n) ((STONEYDSP_CHAR8_T)n)
  // #define STONEYDSP_CHAR16_C(n) ((STONEYDSP_CHAR16_T)n)
  // #define STONEYDSP_CHAR32_C(n) ((STONEYDSP_CHAR32_T)n)

    #define STONEYDSP_INT8_C(n) ((STONEYDSP_INT8_T)n)
    #define STONEYDSP_INT16_C(n) ((STONEYDSP_INT16_T)n)
    #define STONEYDSP_INT32_C(n) ((STONEYDSP_INT32_T)n)
    #define STONEYDSP_INT64_C(n) ((STONEYDSP_INT64_T)n)

    #define STONEYDSP_UINT8_C(n) ((STONEYDSP_UINT8_T)n)
    #define STONEYDSP_UINT16_C(n) ((STONEYDSP_UINT16_T)n)
    #define STONEYDSP_UINT32_C(n) ((STONEYDSP_UINT32_T)n)
    #define STONEYDSP_UINT64_C(n) ((STONEYDSP_UINT64_T)n)

    #define STONEYDSP_SIZE_C(n) ((STONEYDSP_SIZE_T)n)
    #define STONEYDSP_PTRDIFF_C(n) ((STONEYDSP_PTRDIFF_T)n)

  #else
    #define STONEYDSP_BOOL_C(n) (static_cast<STONEYDSP_BOOL_T> (n))

    #define STONEYDSP_DBL_C(n) (static_cast<STONEYDSP_DBL_T> (n))
    #define STONEYDSP_LDBL_C(n) (static_cast<STONEYDSP_LDBL_T> (n))
    #define STONEYDSP_FLT_C(n) (static_cast<STONEYDSP_FLT_T> (n))

    #define STONEYDSP_CHAR_C(n) (static_cast<STONEYDSP_CHAR_T> (n))
    #define STONEYDSP_SCHAR_C(n) (static_cast<STONEYDSP_SCHAR_T> (n))
    #define STONEYDSP_UCHAR_C(n) (static_cast<STONEYDSP_UCHAR_T> (n))

    #define STONEYDSP_INT_C(n) (static_cast<STONEYDSP_INT_T> (n))
    #define STONEYDSP_UINT_C(n) (static_cast<STONEYDSP_UINT_T> (n))

    #define STONEYDSP_SHRT_C(n) (static_cast<STONEYDSP_SHRT_T> (n))
    #define STONEYDSP_USHRT_C(n) (static_cast<STONEYDSP_USHRT_T> (n))

    #define STONEYDSP_LONG_C(n) (static_cast<STONEYDSP_LONG_T> (n))
    #define STONEYDSP_ULONG_C(n) (static_cast<STONEYDSP_ULONG_T> (n))

    #define STONEYDSP_LLONG_C(n) (static_cast<STONEYDSP_LLONG_T> (n))
    #define STONEYDSP_ULLONG_C(n) (static_cast<STONEYDSP_ULLONG_T> (n))

  // #define STONEYDSP_CHAR8_C(n) (static_cast<STONEYDSP_CHAR8_T> (n))
  // #define STONEYDSP_CHAR16_C(n) (static_cast<STONEYDSP_CHAR16_T> (n))
  // #define STONEYDSP_CHAR32_C(n) (static_cast<STONEYDSP_CHAR32_T> (n))

    #define STONEYDSP_INT8_C(n) (static_cast<STONEYDSP_INT8_T> (n))
    #define STONEYDSP_INT16_C(n) (static_cast<STONEYDSP_INT16_T> (n))
    #define STONEYDSP_INT32_C(n) (static_cast<STONEYDSP_INT32_T> (n))
    #define STONEYDSP_INT64_C(n) (static_cast<STONEYDSP_INT64_T> (n))

    #define STONEYDSP_UINT8_C(n) (static_cast<STONEYDSP_UINT8_T> (n))
    #define STONEYDSP_UINT16_C(n) (static_cast<STONEYDSP_UINT16_T> (n))
    #define STONEYDSP_UINT32_C(n) (static_cast<STONEYDSP_UINT32_T> (n))
    #define STONEYDSP_UINT64_C(n) (static_cast<STONEYDSP_UINT64_T> (n))

    #define STONEYDSP_SIZE_C(n) (static_cast<STONEYDSP_SIZE_T> (n))
    #define STONEYDSP_PTRDIFF_C(n) (static_cast<STONEYDSP_PTRDIFF_T> (n))
  #endif // !STONEYDSP_CXX

//==============================================================================

  #define STONEYDSP_INT8_PRINT_F PRIi8
  #define STONEYDSP_INT16_PRINT_F PRIi16
  #define STONEYDSP_INT32_PRINT_F PRIi32
  #define STONEYDSP_INT64_PRINT_F PRIi64

  #define STONEYDSP_UINT8_PRINT_F PRIu8
  #define STONEYDSP_UINT16_PRINT_F PRIu16
  #define STONEYDSP_UINT32_PRINT_F PRIu32
  #define STONEYDSP_UINT64_PRINT_F PRIu64

//==============================================================================

  #define STONEYDSP_INT8_SCAN_F SCNi8
  #define STONEYDSP_INT16_SCAN_F SCNi16
  #define STONEYDSP_INT32_SCAN_F SCNi32
  #define STONEYDSP_INT64_SCAN_F SCNi64

  #define STONEYDSP_UINT8_SCAN_F SCNu8
  #define STONEYDSP_UINT16_SCAN_F SCNu16
  #define STONEYDSP_UINT32_SCAN_F SCNu32
  #define STONEYDSP_UINT64_SCAN_F SCNu64

//==============================================================================

/**
 * int8_t_max:
 * - dec: `127`
 * - oct: `0177`
 * - hex: `0x7F`
 *
 * int8_t_min:
 * - dec: `-128`
 * - oct: `-0200`
 * - hex: `-0x80`
 *
 * uint8_t_max:
 * - dec: `255`
 * - oct: `0377`
 * - hex: `0xFF`
 *
 * uint8_t_min:
 * - dec: `0`
 * - oct: `00`
 * - hex: `0x00`
 */

/**
 * int16_t_max:
 * - dec: `32767`
 * - oct: `077777`
 * - hex: `0x7FFF`
 *
 * int16_t_min:
 * - dec: `-32768`
 * - oct: `-0100000`
 * - hex: `-0x8000`
 *
 * uint16_t_max:
 * - dec: `65535`
 * - oct: `0177777`
 * - hex: `0xFFFF`
 *
 * uint16_t_min:
 * - dec: `0`
 * - oct: `00`
 * - hex: `0x0000`
 */

/**
 * int32_t_max:
 * - dec: `2147483647`
 * - oct: `017777777777`
 * - hex: `0x7FFFFFFF`
 *
 * int32_t_min:
 * - dec: `-2147483648`
 * - oct: `-020000000000`
 * - hex: `-0x80000000`
 *
 * uint32_t_max:
 * - dec: `4294967295`
 * - oct: `037777777777`
 * - hex: `0xFFFFFFFF`
 *
 * uint32_t_min:
 * - dec: `0`
 * - oct: `00`
 * - hex: `0x00000000`
 */

/**
 * int64_t_max:
 * - dec: `9223372036854775807`
 * - oct: `0777777777777777777777`
 * - hex: `0x7FFFFFFFFFFFFFFF`
 *
 * int64_t_min:
 * - dec: `-9223372036854775808`
 * - oct: `-01000000000000000000000`
 * - hex: `-0x8000000000000000`
 *
 * uint64_t_max:
 * - dec: `18446744073709551615`
 * - oct: `01777777777777777777777`
 * - hex: `0xFFFFFFFFFFFFFFFF`
 *
 * uint64_t_min:
 * - dec: `0`
 * - oct: `00`
 * - hex: `0x0000000000000000`
 */

  /**
   * @brief Maximum length of any multibyte character in any locale.
   *
   */
  #define STONEYDSP_MB_LEN_MAX MB_LEN_MAX

  /**
   * @brief Number of bits in a char object (byte).
   *
   */
  #define STONEYDSP_CHAR_BIT CHAR_BIT

  #define STONEYDSP_CHAR_MIN CHAR_MIN
  #define STONEYDSP_CHAR_MAX CHAR_MAX

  #define STONEYDSP_SCHAR_MIN SCHAR_MIN
  #define STONEYDSP_SCHAR_MAX SCHAR_MAX

  #define STONEYDSP_UCHAR_MAX UCHAR_MAX

  #define STONEYDSP_INT_MAX INT_MAX
  #define STONEYDSP_INT_MIN INT_MIN

  #define STONEYDSP_UINT_MAX UINT_MAX

  #define STONEYDSP_SHRT_MIN SHRT_MIN
  #define STONEYDSP_SHRT_MAX SHRT_MAX

  #define STONEYDSP_USHRT_MAX USHRT_MAX

  #define STONEYDSP_LONG_MIN LONG_MIN
  #define STONEYDSP_LONG_MAX LONG_MAX

  #define STONEYDSP_ULONG_MAX ULONG_MAX

  #define STONEYDSP_LLONG_MIN LLONG_MIN
  #define STONEYDSP_LLONG_MAX LLONG_MAX

  #define STONEYDSP_ULLONG_MAX ULLONG_MAX

  #define STONEYDSP_DBL_MIN DBL_MIN
  #define STONEYDSP_DBL_MAX DBL_MAX

  #define STONEYDSP_LDBL_MIN LDBL_MIN
  #define STONEYDSP_LDBL_MAX LDBL_MAX

  #define STONEYDSP_FLT_MIN FLT_MIN
  #define STONEYDSP_FLT_MAX FLT_MAX

  #define STONEYDSP_BOOL_MIN false // 0U
  #define STONEYDSP_BOOL_MAX true  // BOOL_MAX = 1U

  #define STONEYDSP_SIZE_MAX SIZE_MAX

  #define STONEYDSP_PTRDIFF_MIN PTRDIFF_MIN
  #define STONEYDSP_PTRDIFF_MAX PTRDIFF_MAX

// #define STONEYDSP_CHAR8_MAX STONEYDSP_UCHAR_MAX
// #define STONEYDSP_CHAR16_MAX STONEYDSP_USHRT_MAX
// #define STONEYDSP_CHAR32_MAX STONEYDSP_UINT_MAX

  #define STONEYDSP_INT8_MAX STONEYDSP_INT8_C (0177)
  #define STONEYDSP_INT16_MAX STONEYDSP_INT16_C (0x7FFF)
  #define STONEYDSP_INT32_MAX STONEYDSP_INT32_C (2147483647)

  #define STONEYDSP_UINT8_MAX STONEYDSP_UINT8_C (0377)
  #define STONEYDSP_UINT16_MAX STONEYDSP_UINT16_C (0xFFFF)
  #define STONEYDSP_UINT32_MAX STONEYDSP_UINT32_C (4294967295)

  // #define STONEYDSP_CHAR8_MIN STONEYDSP_UCHAR_MIN
  // #define STONEYDSP_CHAR16_MIN STONEYDSP_USHRT_MIN
  // #define STONEYDSP_CHAR32_MIN STONEYDSP_UINT_MIN

  // - dec: `(-128)`
  // - oct: `(-0200)`
  #define STONEYDSP_INT8_MIN                                                  \
    STONEYDSP_INT8_C ((-STONEYDSP_INT8_MAX) - STONEYDSP_INT8_C (01))
  // - dec: `(-32767)`
  // - hex: `(-0x8000)`
  #define STONEYDSP_INT16_MIN                                                 \
    STONEYDSP_INT16_C ((-STONEYDSP_INT16_MAX) - STONEYDSP_INT16_C (0x0001))
  // - dec: `(-2147483648)`
  // - hex: `(-0x80000000)`
  #define STONEYDSP_INT32_MIN                                                 \
    STONEYDSP_INT32_C ((-STONEYDSP_INT32_MAX) - STONEYDSP_INT32_C (1))

  #if STONEYDSP_WINDOWS
    #define STONEYDSP_INT64_MIN STONEYDSP_LLONG_MIN
    #define STONEYDSP_INT64_MAX STONEYDSP_LLONG_MAX
    #define STONEYDSP_UINT64_MAX STONEYDSP_ULLONG_MAX
  #elif STONEYDSP_LINUX || STONEYDSP_MAC
    #if STONEYDSP_32BIT
      #define STONEYDSP_INT64_MIN STONEYDSP_LLONG_MIN
      #define STONEYDSP_INT64_MAX STONEYDSP_LLONG_MAX
      #define STONEYDSP_UINT64_MAX STONEYDSP_ULLONG_MAX
    #elif STONEYDSP_64BIT || STONEYDSP_ARM64
      #define STONEYDSP_INT64_MIN STONEYDSP_LONG_MIN
      #define STONEYDSP_INT64_MAX STONEYDSP_LONG_MAX
      #define STONEYDSP_UINT64_MAX STONEYDSP_ULONG_MAX
    #endif
  #endif

//==============================================================================

// typedef unsigned char stoneydsp_byte_t;

/**
 * @brief
 *
 */
typedef STONEYDSP_CHAR_T stoneydsp_char_t;

/**
 * @brief
 *
 */
typedef STONEYDSP_SCHAR_T stoneydsp_schar_t;

/**
 * @brief
 *
 */
typedef STONEYDSP_UCHAR_T stoneydsp_uchar_t;

/**
 * @brief
 *
 */
typedef STONEYDSP_INT_T stoneydsp_int_t;

/**
 * @brief
 *
 */
typedef STONEYDSP_UINT_T stoneydsp_uint_t;

/**
 * @brief
 *
 */
typedef STONEYDSP_SHRT_T stoneydsp_shrt_t;

/**
 * @brief
 *
 */
typedef STONEYDSP_USHRT_T stoneydsp_ushrt_t;

/**
 * @brief
 *
 */
typedef STONEYDSP_LONG_T stoneydsp_long_t;

/**
 * @brief
 *
 */
typedef STONEYDSP_ULONG_T stoneydsp_ulong_t;

/**
 * @brief
 *
 */
typedef STONEYDSP_LLONG_T stoneydsp_llong_t;

/**
 * @brief
 *
 */
typedef STONEYDSP_ULLONG_T stoneydsp_ullong_t;

// typedef STONEYDSP_CHAR8_T stoneydsp_char8_t;
// typedef STONEYDSP_CHAR16_T stoneydsp_char16_t;
// typedef STONEYDSP_CHAR32_T stoneydsp_char32_t;

/**
 * @brief
 *
 */
typedef STONEYDSP_INT8_T stoneydsp_int8_t;

/**
 * @brief
 *
 */
typedef STONEYDSP_INT16_T stoneydsp_int16_t;

/**
 * @brief
 *
 */
typedef STONEYDSP_INT32_T stoneydsp_int32_t;

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
typedef STONEYDSP_INT64_T stoneydsp_int64_t;

/**
 * @brief
 *
 */
typedef STONEYDSP_UINT64_T stoneydsp_uint64_t;

/**
 * @brief
 *
 */
typedef STONEYDSP_DBL_T stoneydsp_double_t;

/**
 * @brief
 *
 */
typedef STONEYDSP_LDBL_T stoneydsp_ldouble_t;

/**
 * @brief
 *
 */
typedef STONEYDSP_FLT_T stoneydsp_float_t;

/**
 * @brief
 *
 */
typedef STONEYDSP_BOOL_T stoneydsp_bool_t;

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

//=========================================================================//*_c

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_CHAR_T
    STONEYDSP_PUBLIC_FUNCTION
    /**
     * @brief Cast or convert a `value` to a `stoneydsp_char_t`.
     *
     * @param value
     *
     * @return `stoneydsp_char_t`
     */
    stoneydsp_char_c (unsigned long long value) STONEYDSP_NOEXCEPT
{
  return STONEYDSP_CHAR_C (value);
}

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_SCHAR_T
    STONEYDSP_PUBLIC_FUNCTION
    /**
     * @brief Cast or convert a `value` to a `stoneydsp_schar_t`.
     *
     * @param value
     *
     * @return `stoneydsp_schar_t`
     */
    stoneydsp_schar_c (unsigned long long value) STONEYDSP_NOEXCEPT
{
  return STONEYDSP_SCHAR_C (value);
}

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_UCHAR_T
    STONEYDSP_PUBLIC_FUNCTION
    /**
     * @brief Cast or convert a `value` to a `stoneydsp_uchar_t`.
     *
     * @param value
     *
     * @return `stoneydsp_uchar_t`
     */
    stoneydsp_uchar_c (unsigned long long value) STONEYDSP_NOEXCEPT
{
  return STONEYDSP_UCHAR_C (value);
}

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_INT_T
    STONEYDSP_PUBLIC_FUNCTION
    stoneydsp_int_c (unsigned long long value) STONEYDSP_NOEXCEPT
{
  return STONEYDSP_INT_C (value);
}

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_UINT_T
    STONEYDSP_PUBLIC_FUNCTION
    stoneydsp_uint_c (unsigned long long value) STONEYDSP_NOEXCEPT
{
  return STONEYDSP_UINT_C (value);
}

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_SHRT_T
    STONEYDSP_PUBLIC_FUNCTION
    stoneydsp_shrt_c (unsigned long long value) STONEYDSP_NOEXCEPT
{
  return STONEYDSP_SHRT_C (value);
}

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_USHRT_T
    STONEYDSP_PUBLIC_FUNCTION
    stoneydsp_ushrt_c (unsigned long long value) STONEYDSP_NOEXCEPT
{
  return STONEYDSP_USHRT_C (value);
}

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_LONG_T
    STONEYDSP_PUBLIC_FUNCTION
    stoneydsp_long_c (unsigned long long value) STONEYDSP_NOEXCEPT
{
  return STONEYDSP_LONG_C (value);
}

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_ULONG_T
    STONEYDSP_PUBLIC_FUNCTION
    stoneydsp_ulong_c (unsigned long long value) STONEYDSP_NOEXCEPT
{
  return STONEYDSP_ULONG_C (value);
}

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_LLONG_T
    STONEYDSP_PUBLIC_FUNCTION
    stoneydsp_llong_c (unsigned long long value) STONEYDSP_NOEXCEPT
{
  return STONEYDSP_LLONG_C (value);
}

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_ULLONG_T
    STONEYDSP_PUBLIC_FUNCTION
    stoneydsp_ullong_c (unsigned long long value) STONEYDSP_NOEXCEPT
{
  return STONEYDSP_ULLONG_C (value);
}

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_INT8_T
    STONEYDSP_PUBLIC_FUNCTION
    stoneydsp_int8_c (unsigned long long value) STONEYDSP_NOEXCEPT
{
  return STONEYDSP_INT8_C (value);
}

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_INT16_T
    STONEYDSP_PUBLIC_FUNCTION
    stoneydsp_int16_c (unsigned long long value) STONEYDSP_NOEXCEPT
{
  return STONEYDSP_INT16_C (value);
}

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_INT32_T
    STONEYDSP_PUBLIC_FUNCTION
    stoneydsp_int32_c (unsigned long long value) STONEYDSP_NOEXCEPT
{
  return STONEYDSP_INT32_C (value);
}

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_INT64_T
    STONEYDSP_PUBLIC_FUNCTION
    stoneydsp_int64_c (unsigned long long value) STONEYDSP_NOEXCEPT
{
  return (STONEYDSP_INT64_C (value));
}

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_UINT8_T
    STONEYDSP_PUBLIC_FUNCTION
    stoneydsp_uint8_c (unsigned long long value) STONEYDSP_NOEXCEPT
{
  return STONEYDSP_UINT8_C (value);
}

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_UINT16_T
    STONEYDSP_PUBLIC_FUNCTION
    stoneydsp_uint16_c (unsigned long long value) STONEYDSP_NOEXCEPT
{
  return STONEYDSP_UINT16_C (value);
}

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_UINT32_T
    STONEYDSP_PUBLIC_FUNCTION
    stoneydsp_uint32_c (unsigned long long value) STONEYDSP_NOEXCEPT
{
  return STONEYDSP_UINT32_C (value);
}

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_UINT64_T
    STONEYDSP_PUBLIC_FUNCTION
    stoneydsp_uint64_c (unsigned long long value) STONEYDSP_NOEXCEPT
{
  return STONEYDSP_UINT64_C (value);
}

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_DBL_T
    STONEYDSP_PUBLIC_FUNCTION
    stoneydsp_double_c (double value) STONEYDSP_NOEXCEPT
{
  return STONEYDSP_DBL_C (value);
}

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_LDBL_T
    STONEYDSP_PUBLIC_FUNCTION
    stoneydsp_ldouble_c (long double value) STONEYDSP_NOEXCEPT
{
  return STONEYDSP_LDBL_C (value);
}

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_FLT_T
    STONEYDSP_PUBLIC_FUNCTION
    stoneydsp_float_c (float value) STONEYDSP_NOEXCEPT
{
  return STONEYDSP_FLT_C (value);
}

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_BOOL_T
    STONEYDSP_PUBLIC_FUNCTION
    stoneydsp_bool_c (STONEYDSP_BOOL_T value) STONEYDSP_NOEXCEPT
{
  return STONEYDSP_BOOL_C (value);
}

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_SIZE_T
    STONEYDSP_PUBLIC_FUNCTION
    stoneydsp_size_c (unsigned long long value) STONEYDSP_NOEXCEPT
{
  return STONEYDSP_SIZE_C (value);
}

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_PTRDIFF_T
    STONEYDSP_PUBLIC_FUNCTION
    stoneydsp_ptrdiff_c (unsigned long long value) STONEYDSP_NOEXCEPT
{
  return STONEYDSP_PTRDIFF_C (value);
}

//=======================================================================//*_max

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_BOOL_T
    STONEYDSP_PUBLIC_FUNCTION
    /**
     * @brief
     *
     * Equivalent to:
     *
     * - bool: `true`
     *
     * - char: `1U`
     *
     * @return `stoneydsp_bool_t`
     *
     */
    stoneydsp_bool_max () STONEYDSP_NOEXCEPT
{
  return STONEYDSP_BOOL_C (STONEYDSP_BOOL_MAX);
}

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_DBL_T
    STONEYDSP_PUBLIC_FUNCTION
    stoneydsp_double_max () STONEYDSP_NOEXCEPT
{
  return STONEYDSP_DBL_C (STONEYDSP_DBL_MAX);
}

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_LDBL_T
    STONEYDSP_PUBLIC_FUNCTION
    stoneydsp_ldouble_max () STONEYDSP_NOEXCEPT
{
  return STONEYDSP_LDBL_C (STONEYDSP_LDBL_MAX);
}

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_FLT_T
    STONEYDSP_PUBLIC_FUNCTION
    stoneydsp_float_max () STONEYDSP_NOEXCEPT
{
  return STONEYDSP_FLT_C (STONEYDSP_FLT_MAX);
}

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_CHAR_T
    STONEYDSP_PUBLIC_FUNCTION
    /**
     * @brief
     *
     * Typically equivalent to:
     *
     * - dec: `127`
     *
     * - oct: `0177`
     *
     * - hex: `0x7F`
     *
     * @return `stoneydsp_char_t`
     *
     */
    stoneydsp_char_max () STONEYDSP_NOEXCEPT
{
  return STONEYDSP_CHAR_C (STONEYDSP_CHAR_MAX);
}

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_SCHAR_T
    STONEYDSP_PUBLIC_FUNCTION
    /**
     * @brief
     *
     * Typically equivalent to:
     *
     * - dec: `127`
     *
     * - oct: `0177`
     *
     * - hex: `0x7F`
     *
     * @return `stoneydsp_schar_t`
     *
     */
    stoneydsp_schar_max () STONEYDSP_NOEXCEPT
{
  return STONEYDSP_SCHAR_C (STONEYDSP_SCHAR_MAX);
}

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_UCHAR_T
    STONEYDSP_PUBLIC_FUNCTION
    /**
     * @brief
     *
     * Typically equivalent to:
     *
     * - dec: `255u`
     *
     * - oct: `0377u`
     *
     * - hex: `0xFFu`
     *
     * @return `stoneydsp_uchar_t`
     *
     */
    stoneydsp_uchar_max () STONEYDSP_NOEXCEPT
{
  return STONEYDSP_UCHAR_C ((STONEYDSP_UCHAR_C (STONEYDSP_SCHAR_MAX))
                                * (STONEYDSP_UCHAR_C (2U))
                            + (STONEYDSP_UCHAR_C (1U)));
}

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
  return STONEYDSP_SHRT_C (STONEYDSP_SHRT_MAX);
}

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_USHRT_T
    STONEYDSP_PUBLIC_FUNCTION
    /**
     * @brief
     *
     * Guaranteed to be at least:
     *
     * - dec: `65535u`
     *
     * - oct: `0177777u`
     *
     * - hex: `0xFFFFu`
     *
     * @return `stoneydsp_ushrt_t`
     *
     */
    stoneydsp_ushrt_max () STONEYDSP_NOEXCEPT
{
  return STONEYDSP_USHRT_C ((STONEYDSP_USHRT_C (STONEYDSP_SHRT_MAX))
                                * (STONEYDSP_USHRT_C (02U))
                            + (STONEYDSP_USHRT_C (01U)));
}

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
  return STONEYDSP_INT_C (STONEYDSP_INT_MAX);
}

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_UINT_T
    STONEYDSP_PUBLIC_FUNCTION
    /**
     * @brief
     *
     * Guaranteed to be at least:
     *
     * - dec: `4294967295u`
     * - oct: `037777777777u`
     *
     * - hex: `0xFFFFFFFFu`
     *
     * @return `stoneydsp_uint_t`
     *
     */
    stoneydsp_uint_max () STONEYDSP_NOEXCEPT
{
  return STONEYDSP_UINT_C ((STONEYDSP_UINT_C (STONEYDSP_INT_MAX)) * 2U + 1U);
}

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_LONG_T
    STONEYDSP_PUBLIC_FUNCTION
    stoneydsp_long_max () STONEYDSP_NOEXCEPT
{
  return STONEYDSP_LONG_C (STONEYDSP_LONG_MAX);
}

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_ULONG_T
    STONEYDSP_PUBLIC_FUNCTION
    stoneydsp_ulong_max () STONEYDSP_NOEXCEPT
{
  return STONEYDSP_ULONG_C ((STONEYDSP_ULONG_C (STONEYDSP_LONG_MAX)) * 2UL
                            + 1UL);
}

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_LLONG_T
    STONEYDSP_PUBLIC_FUNCTION
    stoneydsp_llong_max () STONEYDSP_NOEXCEPT
{
  return STONEYDSP_LLONG_C (STONEYDSP_LLONG_MAX);
}

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_ULLONG_T
    STONEYDSP_PUBLIC_FUNCTION
    stoneydsp_ullong_max () STONEYDSP_NOEXCEPT
{
  return STONEYDSP_ULLONG_C ((STONEYDSP_ULLONG_C (STONEYDSP_LLONG_MAX)) * 2ULL
                             + 1ULL);
}

// STONEYDSP_EXTERN_C inline STONEYDSP_CONSTEXPR STONEYDSP_CHAR8_T
// STONEYDSP_PUBLIC_FUNCTION
// stoneydsp_char8_max () STONEYDSP_NOEXCEPT
// {
//   return (stoneydsp_uchar_max ());
// }

// STONEYDSP_EXTERN_C inline STONEYDSP_CONSTEXPR STONEYDSP_CHAR16_T
// STONEYDSP_PUBLIC_FUNCTION
// stoneydsp_char16_max () STONEYDSP_NOEXCEPT
// {
//   return ::stoneydsp::numeric_limits<stoneydsp_char16_t>::max ();
// }

// STONEYDSP_EXTERN_C inline STONEYDSP_CONSTEXPR STONEYDSP_CHAR32_T
// STONEYDSP_PUBLIC_FUNCTION
// stoneydsp_char32_max () STONEYDSP_NOEXCEPT
// {
//   return ::stoneydsp::numeric_limits<stoneydsp_char32_t>::max ();
// }

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
  return STONEYDSP_INT8_C (STONEYDSP_INT8_MAX);
}

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
  return STONEYDSP_INT16_C (STONEYDSP_INT16_MAX);
}

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_INT32_T
    STONEYDSP_PUBLIC_FUNCTION
    /**
     * @brief
     *
     * Equivalent to:
     *
     * - dec: `2147483647`
     *
     * - oct: `017777777777`
     *
     * - hex: `0x7FFFFFFF`
     *
     * @return `stoneydsp_int32_t`
     *
     */
    stoneydsp_int32_max () STONEYDSP_NOEXCEPT
{
  return STONEYDSP_INT32_C (STONEYDSP_INT32_MAX);
}

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
  return STONEYDSP_INT64_C (STONEYDSP_INT64_MAX);
}

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_UINT8_T
    STONEYDSP_PUBLIC_FUNCTION
    /**
     * @brief
     *
     * Equivalent to:
     *
     * - dec: `255`
     *
     * - oct: `0377`
     *
     * - hex: `0xFF`
     *
     * @return `stoneydsp_uint8_t`
     *
     */
    stoneydsp_uint8_max () STONEYDSP_NOEXCEPT
{
  return STONEYDSP_UINT8_C ((STONEYDSP_UINT8_C (STONEYDSP_INT8_MAX))
                                * (STONEYDSP_UINT8_C (02U))
                            + (STONEYDSP_UINT8_C (01U)));
}

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_UINT16_T
    STONEYDSP_PUBLIC_FUNCTION
    stoneydsp_uint16_max () STONEYDSP_NOEXCEPT
{
  return STONEYDSP_UINT16_C ((STONEYDSP_UINT16_C (STONEYDSP_INT16_MAX))
                                 * (STONEYDSP_UINT16_C (0x0002U))
                             + (STONEYDSP_UINT16_C (0x0001U)));
}

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_UINT32_T
    STONEYDSP_PUBLIC_FUNCTION
    stoneydsp_uint32_max () STONEYDSP_NOEXCEPT
{
  return STONEYDSP_UINT32_C ((STONEYDSP_UINT32_C (STONEYDSP_INT32_MAX))
                                 * (STONEYDSP_UINT32_C (2U))
                             + (STONEYDSP_UINT32_C (1U)));
}

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_UINT64_T
    STONEYDSP_PUBLIC_FUNCTION
    stoneydsp_uint64_max () STONEYDSP_NOEXCEPT
{
  return STONEYDSP_UINT64_C ((STONEYDSP_UINT64_C (STONEYDSP_INT64_MAX))
                                 * (STONEYDSP_UINT64_C (2U))
                             + (STONEYDSP_UINT64_C (1U)));
}

// STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR
//     STONEYDSP_SIZE_T STONEYDSP_PUBLIC_FUNCTION
//     stoneydsp_size_max () STONEYDSP_NOEXCEPT
// {
//   return STONEYDSP_SIZE_C ((STONEYDSP_SIZE_C (STONEYDSP_SIZE_MAX))
//                                 * (STONEYDSP_SIZE_C (2UL))
//                             + (STONEYDSP_SIZE_C (1UL)));
// }

// STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR
//     STONEYDSP_PTRDIFF_T STONEYDSP_PUBLIC_FUNCTION
//     stoneydsp_ptrdiff_max () STONEYDSP_NOEXCEPT
// {
//   return STONEYDSP_PTRDIFF_C ((STONEYDSP_PTRDIFF_C (STONEYDSP_PTRDIFF_MAX))
//                                    * (STONEYDSP_PTRDIFF_C (2UL))
//                                + (STONEYDSP_PTRDIFF_C (1UL)));
// }

//=======================================================================//*_min

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_BOOL_T
    STONEYDSP_PUBLIC_FUNCTION
    stoneydsp_bool_min () STONEYDSP_NOEXCEPT
{
  return STONEYDSP_BOOL_C (STONEYDSP_BOOL_MIN);
}

// stoneydsp_char_t

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_CHAR_T
    STONEYDSP_PUBLIC_FUNCTION
    stoneydsp_char_min () STONEYDSP_NOEXCEPT
{
  return STONEYDSP_CHAR_C (STONEYDSP_CHAR_MIN);
}

// stoneydsp_schar_t

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_SCHAR_T
    STONEYDSP_PUBLIC_FUNCTION
    stoneydsp_schar_min () STONEYDSP_NOEXCEPT
{
  return STONEYDSP_SCHAR_C (-STONEYDSP_SCHAR_MAX - 1);
}

// stoneydsp_uchar_t

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_UCHAR_T
    STONEYDSP_PUBLIC_FUNCTION
    stoneydsp_uchar_min () STONEYDSP_NOEXCEPT
{
  return STONEYDSP_UCHAR_C (0);
}

// stoneydsp_shrt_t

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_SHRT_T
    STONEYDSP_PUBLIC_FUNCTION
    /**
     * @brief
     *
     * @return `stoneydsp_shrt_t`
     *
     */
    stoneydsp_shrt_min () STONEYDSP_NOEXCEPT
{
  return STONEYDSP_SHRT_C ((STONEYDSP_SHRT_C (-STONEYDSP_SHRT_MAX))
                           - (STONEYDSP_SHRT_C (1)));
}

// stoneydsp_ushrt_t

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_USHRT_T
    STONEYDSP_PUBLIC_FUNCTION
    /**
     * @brief
     *
     * Equivalent to:
     *
     * - hex: `0`
     *
     * - oct: `000000`
     *
     */
    stoneydsp_ushrt_min () STONEYDSP_NOEXCEPT
{
  return STONEYDSP_USHRT_C (00U);
}

// stoneydsp_int_t

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_INT_T
    STONEYDSP_PUBLIC_FUNCTION
    /**
     * @brief
     *
     * Equivalent to:
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
  return STONEYDSP_INT_C (STONEYDSP_INT_C (-STONEYDSP_INT_MAX))
         - (STONEYDSP_INT_C (1));
}

// stoneydsp_uint_t

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_UINT_T
    STONEYDSP_PUBLIC_FUNCTION
    stoneydsp_uint_min () STONEYDSP_NOEXCEPT
{
  return STONEYDSP_UINT_C (0U);
}

// stoneydsp_long_t

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_LONG_T
    STONEYDSP_PUBLIC_FUNCTION
    stoneydsp_long_min () STONEYDSP_NOEXCEPT
{
  return STONEYDSP_LONG_C (-STONEYDSP_LONG_MAX - 1);
}

// stoneydsp_ulong_t

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_ULONG_T
    STONEYDSP_PUBLIC_FUNCTION
    stoneydsp_ulong_min () STONEYDSP_NOEXCEPT
{
  return STONEYDSP_ULONG_C (0UL);
}

// stoneydsp_llong_t

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_LLONG_T
    STONEYDSP_PUBLIC_FUNCTION
    stoneydsp_llong_min () STONEYDSP_NOEXCEPT
{
  return STONEYDSP_LLONG_C (-STONEYDSP_LLONG_MAX - 1);
}

// stoneydsp_ullong_t

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_ULLONG_T
    STONEYDSP_PUBLIC_FUNCTION
    stoneydsp_ullong_min () STONEYDSP_NOEXCEPT
{
  return STONEYDSP_ULLONG_C (0ULL);
}

// // stoneydsp_char8_t

// STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_CHAR8_T
// STONEYDSP_PUBLIC_FUNCTION
// stoneydsp_char8_min () STONEYDSP_NOEXCEPT
// {
//   return (stoneydsp_uchar_min ());
// }

// // stoneydsp_char16_t

// STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_CHAR16_T
// STONEYDSP_PUBLIC_FUNCTION
// stoneydsp_char16_min () STONEYDSP_NOEXCEPT
// {
//   return ::stoneydsp::numeric_limits<stoneydsp_char16_t>::min ();
// }

// // stoneydsp_char32_t

// STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_CHAR32_T
// STONEYDSP_PUBLIC_FUNCTION
// stoneydsp_char32_min () STONEYDSP_NOEXCEPT
// {
//   return ::stoneydsp::numeric_limits<stoneydsp_char32_t>::min ();
// }

// stoneydsp_int8_t

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
  return STONEYDSP_INT8_C ((-STONEYDSP_INT8_MAX) - STONEYDSP_INT8_C (01));
}

// stoneydsp_int16_t

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
  return STONEYDSP_INT16_C ((-STONEYDSP_INT16_MAX)
                            - STONEYDSP_INT16_C (0x0001));
}

// stoneydsp_int32_t

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_INT32_T
    STONEYDSP_PUBLIC_FUNCTION
    /**
     * @brief
     *
     * Equivalent to:
     *
     * - dec: `-2147483648`
     *
     * - oct: `-020000000000`
     *
     * - hex: `-0x80000000`
     *
     * @return `stoneydsp_int32_t`
     *
     */
    stoneydsp_int32_min () STONEYDSP_NOEXCEPT
{
  return STONEYDSP_INT32_C ((-STONEYDSP_INT32_MAX) - STONEYDSP_INT32_C (1));
}

// stoneydsp_int64_t

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
  return STONEYDSP_INT64_C ((-STONEYDSP_INT64_MAX) - STONEYDSP_INT64_C (1));
}

// stoneydsp_uint8_t

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_UINT8_T
    STONEYDSP_PUBLIC_FUNCTION
    /**
     * @brief
     *
     * Equivalent to:
     *
     * - dec: `0`
     *
     * - oct: `00`
     *
     * - hex: `0x00`
     *
     * @return `stoneydsp_uint8_t`
     *
     */
    stoneydsp_uint8_min () STONEYDSP_NOEXCEPT
{
  return STONEYDSP_UINT8_C (00U);
}

// stoneydsp_uint16_t

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_UINT16_T
    STONEYDSP_PUBLIC_FUNCTION
    stoneydsp_uint16_min () STONEYDSP_NOEXCEPT
{
  return STONEYDSP_UINT16_C (0x0000U);
}

// stoneydsp_uint32_t

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_UINT32_T
    STONEYDSP_PUBLIC_FUNCTION
    stoneydsp_uint32_min () STONEYDSP_NOEXCEPT
{
  return STONEYDSP_UINT32_C (0U);
}

// stoneydsp_uint64_t

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_UINT64_T
    STONEYDSP_PUBLIC_FUNCTION
    stoneydsp_uint64_min () STONEYDSP_NOEXCEPT
{
  return STONEYDSP_UINT64_C (0U);
}

// stoneydsp_double_t

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_DBL_T
    STONEYDSP_PUBLIC_FUNCTION
    stoneydsp_double_min () STONEYDSP_NOEXCEPT
{
  return STONEYDSP_DBL_C (STONEYDSP_DBL_MIN);
}

// stoneydsp_ldouble_t

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_LDBL_T
    STONEYDSP_PUBLIC_FUNCTION
    stoneydsp_ldouble_min () STONEYDSP_NOEXCEPT
{
  return STONEYDSP_LDBL_C (STONEYDSP_LDBL_MIN);
}

// stoneydsp_float_t

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_FLT_T
    STONEYDSP_PUBLIC_FUNCTION
    stoneydsp_float_min () STONEYDSP_NOEXCEPT
{
  return STONEYDSP_FLT_C (STONEYDSP_FLT_MIN);
}

// stoneydsp_size_t

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_SIZE_T
    STONEYDSP_PUBLIC_FUNCTION
    stoneydsp_size_min () STONEYDSP_NOEXCEPT
{
  return STONEYDSP_SIZE_C (0U);
}

// stoneydsp_ptrdiff_t

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_PTRDIFF_T
    STONEYDSP_PUBLIC_FUNCTION
    stoneydsp_ptrdiff_min () STONEYDSP_NOEXCEPT
{
  return STONEYDSP_PTRDIFF_C (STONEYDSP_PTRDIFF_MIN);
}

//====================================================================//*_lowest

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_BOOL_T
    STONEYDSP_PUBLIC_FUNCTION
    stoneydsp_bool_lowest () STONEYDSP_NOEXCEPT
{
  return stoneydsp_bool_min ();
}

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_CHAR_T
    STONEYDSP_PUBLIC_FUNCTION
    stoneydsp_char_lowest () STONEYDSP_NOEXCEPT
{
  return stoneydsp_char_min ();
}

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_SCHAR_T
    STONEYDSP_PUBLIC_FUNCTION
    stoneydsp_schar_lowest () STONEYDSP_NOEXCEPT
{
  return stoneydsp_schar_min ();
}

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_UCHAR_T
    STONEYDSP_PUBLIC_FUNCTION
    stoneydsp_uchar_lowest () STONEYDSP_NOEXCEPT
{
  return stoneydsp_uchar_min ();
}

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_SHRT_T
    STONEYDSP_PUBLIC_FUNCTION
    stoneydsp_shrt_lowest () STONEYDSP_NOEXCEPT
{
  return stoneydsp_shrt_min ();
}

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_USHRT_T
    STONEYDSP_PUBLIC_FUNCTION
    stoneydsp_ushrt_lowest () STONEYDSP_NOEXCEPT
{
  return stoneydsp_ushrt_min ();
}

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_INT_T
    STONEYDSP_PUBLIC_FUNCTION
    stoneydsp_int_lowest () STONEYDSP_NOEXCEPT
{
  return stoneydsp_int_min ();
}

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_UINT_T
    STONEYDSP_PUBLIC_FUNCTION
    stoneydsp_uint_lowest () STONEYDSP_NOEXCEPT
{
  return stoneydsp_uint_min ();
}

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_LONG_T
    STONEYDSP_PUBLIC_FUNCTION
    stoneydsp_long_lowest () STONEYDSP_NOEXCEPT
{
  return stoneydsp_long_min ();
}

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_ULONG_T
    STONEYDSP_PUBLIC_FUNCTION
    stoneydsp_ulong_lowest () STONEYDSP_NOEXCEPT
{
  return stoneydsp_ulong_min ();
}

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_LLONG_T
    STONEYDSP_PUBLIC_FUNCTION
    stoneydsp_llong_lowest () STONEYDSP_NOEXCEPT
{
  return stoneydsp_llong_min ();
}

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_ULLONG_T
    STONEYDSP_PUBLIC_FUNCTION
    stoneydsp_ullong_lowest () STONEYDSP_NOEXCEPT
{
  return stoneydsp_ullong_min ();
}

// STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_CHAR8_T
// STONEYDSP_PUBLIC_FUNCTION
// stoneydsp_char8_lowest () STONEYDSP_NOEXCEPT
// {
//   return stoneydsp_uchar_lowest ();
// }

// STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_CHAR16_T
// STONEYDSP_PUBLIC_FUNCTION
// stoneydsp_char16_lowest () STONEYDSP_NOEXCEPT
// {
//   return ::stoneydsp::numeric_limits<stoneydsp_char16_t>::lowest ();
// }

// STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_CHAR32_T
// STONEYDSP_PUBLIC_FUNCTION
// stoneydsp_char32_lowest () STONEYDSP_NOEXCEPT
// {
//   return ::stoneydsp::numeric_limits<stoneydsp_char32_t>::lowest ();
// }

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_INT8_T
    STONEYDSP_PUBLIC_FUNCTION
    stoneydsp_int8_lowest () STONEYDSP_NOEXCEPT
{
  return stoneydsp_int8_min ();
}

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_INT16_T
    STONEYDSP_PUBLIC_FUNCTION
    stoneydsp_int16_lowest () STONEYDSP_NOEXCEPT
{
  return stoneydsp_int16_min ();
}

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_INT32_T
    STONEYDSP_PUBLIC_FUNCTION
    stoneydsp_int32_lowest () STONEYDSP_NOEXCEPT
{
  return stoneydsp_int32_min ();
}

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_INT64_T
    STONEYDSP_PUBLIC_FUNCTION
    stoneydsp_int64_lowest () STONEYDSP_NOEXCEPT
{
  return stoneydsp_int64_min ();
}

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_UINT8_T
    STONEYDSP_PUBLIC_FUNCTION
    stoneydsp_uint8_lowest () STONEYDSP_NOEXCEPT
{
  return stoneydsp_uint8_min ();
}

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_UINT16_T
    STONEYDSP_PUBLIC_FUNCTION
    stoneydsp_uint16_lowest () STONEYDSP_NOEXCEPT
{
  return stoneydsp_uint16_min ();
}

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_UINT32_T
    STONEYDSP_PUBLIC_FUNCTION
    stoneydsp_uint32_lowest () STONEYDSP_NOEXCEPT
{
  return stoneydsp_uint32_min ();
}

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_UINT64_T
    STONEYDSP_PUBLIC_FUNCTION
    stoneydsp_uint64_lowest () STONEYDSP_NOEXCEPT
{
  return stoneydsp_uint64_min ();
}

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_DBL_T
    STONEYDSP_PUBLIC_FUNCTION
    stoneydsp_double_lowest () STONEYDSP_NOEXCEPT
{
  return STONEYDSP_DBL_C (-STONEYDSP_DBL_MAX);
}

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_LDBL_T
    STONEYDSP_PUBLIC_FUNCTION
    stoneydsp_ldouble_lowest () STONEYDSP_NOEXCEPT
{
  return STONEYDSP_LDBL_C (-STONEYDSP_LDBL_MAX);
}

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_FLT_T
    STONEYDSP_PUBLIC_FUNCTION
    stoneydsp_float_lowest () STONEYDSP_NOEXCEPT
{
  return STONEYDSP_FLT_C (-STONEYDSP_FLT_MAX);
}

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_SIZE_T
    STONEYDSP_PUBLIC_FUNCTION
    stoneydsp_size_lowest () STONEYDSP_NOEXCEPT
{
  return STONEYDSP_SIZE_C (0U);
}

// stoneydsp_ptrdiff_t

STONEYDSP_EXTERN_C STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_PTRDIFF_T
    STONEYDSP_PUBLIC_FUNCTION
    stoneydsp_ptrdiff_lowest () STONEYDSP_NOEXCEPT
{
  return STONEYDSP_PTRDIFF_C (STONEYDSP_PTRDIFF_MIN);
}

//==============================================================================

  #ifdef __cplusplus

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

/**
 * @brief
 *
 */
using char_t = ::stoneydsp_char_t;

/**
 * @brief
 *
 */
using schar_t = ::stoneydsp_schar_t;

/**
 * @brief
 *
 */
using uchar_t = ::stoneydsp_uchar_t;

/**
 * @brief
 *
 */
using shrt_t = ::stoneydsp_shrt_t;

/**
 * @brief
 *
 */
using ushrt_t = ::stoneydsp_ushrt_t;

/**
 * @brief
 *
 */
using int_t = ::stoneydsp_int_t;

/**
 * @brief
 *
 */
using uint_t = ::stoneydsp_uint_t;

/**
 * @brief
 *
 */
using long_t = ::stoneydsp_long_t;

/**
 * @brief
 *
 */
using ulong_t = ::stoneydsp_ulong_t;

/**
 * @brief
 *
 */
using llong_t = ::stoneydsp_llong_t;

/**
 * @brief
 *
 */
using ullong_t = ::stoneydsp_ullong_t;

/**
 * @brief
 *
 */
using double_t = ::stoneydsp_double_t;

/**
 * @brief
 *
 */
using ldouble_t = ::stoneydsp_ldouble_t;

/**
 * @brief
 *
 */
using float_t = ::stoneydsp_float_t;

/**
 * @brief
 *
 */
using bool_t = ::stoneydsp_bool_t;

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

// using char8_t = ::stoneydsp_char8_t;
// using char16_t = ::stoneydsp_char16_t;
// using char32_t = ::stoneydsp_char32_t;

/**
 * @brief
 *
 */
using int8_t = ::stoneydsp_int8_t;

/**
 * @brief
 *
 */
using int16_t = ::stoneydsp_int16_t;

/**
 * @brief
 *
 */
using int32_t = ::stoneydsp_int32_t;

/**
 * @brief
 *
 */
using int64_t = ::stoneydsp_int64_t;

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

/// @} types
} // namespace types

/// @} group core
} //  namespace core

using ::stoneydsp::core::types::bool_t;
using ::stoneydsp::core::types::char_t;
using ::stoneydsp::core::types::double_t;
using ::stoneydsp::core::types::float_t;
using ::stoneydsp::core::types::int_t;
using ::stoneydsp::core::types::ldouble_t;
using ::stoneydsp::core::types::llong_t;
using ::stoneydsp::core::types::long_t;
using ::stoneydsp::core::types::schar_t;
using ::stoneydsp::core::types::shrt_t;
using ::stoneydsp::core::types::uchar_t;
using ::stoneydsp::core::types::uint_t;
using ::stoneydsp::core::types::ullong_t;
using ::stoneydsp::core::types::ulong_t;
using ::stoneydsp::core::types::ushrt_t;

// using ::stoneydsp::core::types::char8_t;
// using ::stoneydsp::core::types::char16_t;
// using ::stoneydsp::core::types::char32_t;

using ::stoneydsp::core::types::int16_t;
using ::stoneydsp::core::types::int32_t;
using ::stoneydsp::core::types::int64_t;
using ::stoneydsp::core::types::int8_t;

using ::stoneydsp::core::types::uint16_t;
using ::stoneydsp::core::types::uint32_t;
using ::stoneydsp::core::types::uint64_t;
using ::stoneydsp::core::types::uint8_t;

using ::stoneydsp::core::types::ptrdiff_t;
using ::stoneydsp::core::types::size_t;

/// @} group stoneydsp
} // namespace stoneydsp

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

namespace literals
{
/** @addtogroup literals
 * @{
 */

STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_CHAR_T STONEYDSP_PUBLIC_FUNCTION
/**
 * @brief
 *
 * @param value
 *
 * @return `stoneydsp::char_t`
 *
 */
operator"" _char_t (char value) STONEYDSP_NOEXCEPT
{
  return static_cast<STONEYDSP_CHAR_T> (value);
}

STONEYDSP_INLINE
STONEYDSP_CONSTEXPR STONEYDSP_SCHAR_T STONEYDSP_PUBLIC_FUNCTION
/**
 * @brief
 *
 * @param value
 *
 * @return `stoneydsp::schar_t`
 */
operator"" _schar_t (char value) STONEYDSP_NOEXCEPT
{
  return static_cast<STONEYDSP_SCHAR_T> (value);
}

STONEYDSP_INLINE
STONEYDSP_CONSTEXPR STONEYDSP_UCHAR_T STONEYDSP_PUBLIC_FUNCTION
/**
 * @brief
 *
 * @param value
 *
 * @return `stoneydsp::uchar_t`
 */
operator"" _uchar_t (char value) STONEYDSP_NOEXCEPT
{
  return static_cast<STONEYDSP_UCHAR_T> (value);
}

STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_SHRT_T STONEYDSP_PUBLIC_FUNCTION
/**
 * @brief
 *
 * @param value
 *
 * @return `stoneydsp::shrt_t`
 *
 */
operator"" _shrt_t (char value) STONEYDSP_NOEXCEPT
{
  return static_cast<STONEYDSP_SHRT_T> (value);
}

STONEYDSP_INLINE
STONEYDSP_CONSTEXPR STONEYDSP_USHRT_T STONEYDSP_PUBLIC_FUNCTION
/**
 * @brief
 *
 * @param value
 *
 * @return `stoneydsp::ushrt_t`
 *
 */
operator"" _ushrt_t (char value) STONEYDSP_NOEXCEPT
{
  return static_cast<STONEYDSP_USHRT_T> (value);
}

STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_INT_T STONEYDSP_PUBLIC_FUNCTION
/**
 * @brief
 *
 * @param value
 *
 * @return `stoneydsp::int_t`
 *
 */
operator"" _int_t (char value) STONEYDSP_NOEXCEPT
{
  return static_cast<STONEYDSP_INT_T> (value);
}

STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_UINT_T STONEYDSP_PUBLIC_FUNCTION
/**
 * @brief
 *
 * @param value
 *
 * @return `stoneydsp::uint_t`
 *
 */
operator"" _uint_t (char value) STONEYDSP_NOEXCEPT
{
  return static_cast<STONEYDSP_UINT_T> (value);
}

STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_LONG_T STONEYDSP_PUBLIC_FUNCTION
/**
 * @brief
 *
 * @param value
 *
 * @return `stoneydsp::long_t`
 *
 */
operator"" _long_t (char value) STONEYDSP_NOEXCEPT
{
  return static_cast<STONEYDSP_LONG_T> (value);
}

STONEYDSP_INLINE
STONEYDSP_CONSTEXPR STONEYDSP_ULONG_T STONEYDSP_PUBLIC_FUNCTION
/**
 * @brief
 *
 * @param value
 *
 * @return `stoneydsp::ulong_t`
 *
 */
operator"" _ulong_t (char value) STONEYDSP_NOEXCEPT
{
  return static_cast<STONEYDSP_ULONG_T> (value);
}

STONEYDSP_INLINE
STONEYDSP_CONSTEXPR STONEYDSP_LLONG_T STONEYDSP_PUBLIC_FUNCTION
/**
 * @brief
 *
 * @param value
 *
 * @return `stoneydsp::llong_t`
 *
 */
operator"" _llong_t (char value) STONEYDSP_NOEXCEPT
{
  return static_cast<STONEYDSP_LLONG_T> (value);
}

STONEYDSP_INLINE
STONEYDSP_CONSTEXPR STONEYDSP_ULLONG_T STONEYDSP_PUBLIC_FUNCTION
/**
 * @brief
 *
 * @param value
 *
 * @return `stoneydsp::ullong_t`
 *
 */
operator"" _ullong_t (char value) STONEYDSP_NOEXCEPT
{
  return static_cast<STONEYDSP_ULLONG_T> (value);
}

STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_INT8_T STONEYDSP_PUBLIC_FUNCTION
/**
 * @brief
 *
 * @param value
 *
 * @return `stoneydsp::int8_t`
 *
 */
operator"" _int8_t (char value) STONEYDSP_NOEXCEPT
{
  return static_cast<STONEYDSP_INT8_T> (value);
}

STONEYDSP_INLINE
STONEYDSP_CONSTEXPR STONEYDSP_UINT8_T STONEYDSP_PUBLIC_FUNCTION
/**
 * @brief
 *
 * @param value
 *
 * @return `stoneydsp::uint8_t`
 *
 */
operator"" _uint8_t (char value) STONEYDSP_NOEXCEPT
{
  return static_cast<STONEYDSP_UINT8_T> (value);
}

STONEYDSP_INLINE
STONEYDSP_CONSTEXPR STONEYDSP_INT16_T STONEYDSP_PUBLIC_FUNCTION
/**
 * @brief
 *
 * @param value
 *
 * @return `stoneydsp::int16_t`
 *
 */
operator"" _int16_t (char value) STONEYDSP_NOEXCEPT
{
  return static_cast<STONEYDSP_INT16_T> (value);
}

STONEYDSP_INLINE
STONEYDSP_CONSTEXPR STONEYDSP_UINT16_T STONEYDSP_PUBLIC_FUNCTION
/**
 * @brief
 *
 * @param value
 *
 * @return `stoneydsp::uint8_t`
 *
 */
operator"" _uint16_t (char value) STONEYDSP_NOEXCEPT
{
  return static_cast<STONEYDSP_UINT16_T> (value);
}

STONEYDSP_INLINE
STONEYDSP_CONSTEXPR STONEYDSP_INT32_T STONEYDSP_PUBLIC_FUNCTION
/**
 * @brief
 *
 * @param value
 *
 * @return `stoneydsp::int32_t`
 *
 */
operator"" _int32_t (char value) STONEYDSP_NOEXCEPT
{
  return static_cast<STONEYDSP_INT32_T> (value);
}

STONEYDSP_INLINE
STONEYDSP_CONSTEXPR STONEYDSP_UINT32_T STONEYDSP_PUBLIC_FUNCTION
/**
 * @brief
 *
 * @param value
 *
 * @return `stoneydsp::uint32_t`
 *
 */
operator"" _uint32_t (char value) STONEYDSP_NOEXCEPT
{
  return static_cast<STONEYDSP_UINT32_T> (value);
}

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
  return static_cast<STONEYDSP_INT64_T> (value);
}

STONEYDSP_INLINE
STONEYDSP_CONSTEXPR STONEYDSP_UINT64_T STONEYDSP_PUBLIC_FUNCTION
/**
 * @brief
 *
 * @param value
 *
 * @return `stoneydsp::uint64_t`
 *
 */
operator"" _uint64_t (char value) STONEYDSP_NOEXCEPT
{
  return static_cast<STONEYDSP_UINT64_T> (value);
}

STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_SIZE_T STONEYDSP_PUBLIC_FUNCTION
/**
 * @brief
 *
 * @param value
 *
 * @return `stoneydsp::size_t`
 *
 */
operator"" _size_t (char value) STONEYDSP_NOEXCEPT
{
  return static_cast<STONEYDSP_SIZE_T> (value);
}

STONEYDSP_INLINE
STONEYDSP_CONSTEXPR STONEYDSP_PTRDIFF_T STONEYDSP_PUBLIC_FUNCTION
/**
 * @brief
 *
 * @param value
 *
 * @return `stoneydsp::ptrdiff_t`
 *
 */
operator"" _ptrdiff_t (char value) STONEYDSP_NOEXCEPT
{
  return static_cast<STONEYDSP_PTRDIFF_T> (value);
}

//==============================================================================

STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_CHAR_T STONEYDSP_PUBLIC_FUNCTION
/**
 * @brief
 *
 */
operator"" _char_t (unsigned long long value) STONEYDSP_NOEXCEPT
{
  return ::stoneydsp_char_c (value);
}

STONEYDSP_INLINE
STONEYDSP_CONSTEXPR STONEYDSP_SCHAR_T STONEYDSP_PUBLIC_FUNCTION
/**
 * @brief
 *
 */
operator"" _schar_t (unsigned long long value) STONEYDSP_NOEXCEPT
{
  return ::stoneydsp_schar_c (value);
}

STONEYDSP_INLINE
STONEYDSP_CONSTEXPR STONEYDSP_UCHAR_T STONEYDSP_PUBLIC_FUNCTION
/**
 * @brief
 *
 */
operator"" _uchar_t (unsigned long long value) STONEYDSP_NOEXCEPT
{
  return ::stoneydsp_uchar_c (value);
}

STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_SHRT_T STONEYDSP_PUBLIC_FUNCTION
/**
 * @brief
 *
 */
operator"" _shrt_t (unsigned long long value) STONEYDSP_NOEXCEPT
{
  return ::stoneydsp_shrt_c (value);
}

STONEYDSP_INLINE
STONEYDSP_CONSTEXPR STONEYDSP_USHRT_T STONEYDSP_PUBLIC_FUNCTION
/**
 * @brief
 *
 */
operator"" _ushrt_t (unsigned long long value) STONEYDSP_NOEXCEPT
{
  return ::stoneydsp_ushrt_c (value);
}

STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_INT_T STONEYDSP_PUBLIC_FUNCTION
/**
 * @brief
 *
 */
operator"" _int_t (unsigned long long value) STONEYDSP_NOEXCEPT
{
  return ::stoneydsp_int_c (value);
}

STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_UINT_T STONEYDSP_PUBLIC_FUNCTION
/**
 * @brief
 *
 */
operator"" _uint_t (unsigned long long value) STONEYDSP_NOEXCEPT
{
  return ::stoneydsp_uint_c (value);
}

STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_LONG_T STONEYDSP_PUBLIC_FUNCTION
/**
 * @brief
 *
 */
operator"" _long_t (unsigned long long value) STONEYDSP_NOEXCEPT
{
  return ::stoneydsp_long_c (value);
}

STONEYDSP_INLINE
STONEYDSP_CONSTEXPR STONEYDSP_ULONG_T STONEYDSP_PUBLIC_FUNCTION
/**
 * @brief
 *
 */
operator"" _ulong_t (unsigned long long value) STONEYDSP_NOEXCEPT
{
  return ::stoneydsp_ulong_c (value);
}

STONEYDSP_INLINE
STONEYDSP_CONSTEXPR STONEYDSP_LLONG_T STONEYDSP_PUBLIC_FUNCTION
/**
 * @brief
 *
 */
operator"" _llong_t (unsigned long long value) STONEYDSP_NOEXCEPT
{
  return ::stoneydsp_llong_c (value);
}

STONEYDSP_INLINE
STONEYDSP_CONSTEXPR STONEYDSP_ULLONG_T STONEYDSP_PUBLIC_FUNCTION
/**
 * @brief
 *
 */
operator"" _ullong_t (unsigned long long value) STONEYDSP_NOEXCEPT
{
  return ::stoneydsp_ullong_c (value);
}

STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_SIZE_T STONEYDSP_PUBLIC_FUNCTION
/**
 * @brief
 *
 */
operator"" _size_t (unsigned long long value) STONEYDSP_NOEXCEPT
{
  return ::stoneydsp_size_c (value);
}

STONEYDSP_INLINE
STONEYDSP_CONSTEXPR STONEYDSP_PTRDIFF_T STONEYDSP_PUBLIC_FUNCTION
/**
 * @brief
 *
 */
operator"" _ptrdiff_t (unsigned long long value) STONEYDSP_NOEXCEPT
{
  return ::stoneydsp_ptrdiff_c (value);
}

//==============================================================================

STONEYDSP_INLINE STONEYDSP_CONSTEXPR STONEYDSP_INT8_T STONEYDSP_PUBLIC_FUNCTION
/**
 * @brief
 *
 */
operator"" _int8_t (unsigned long long value) STONEYDSP_NOEXCEPT
{
  return static_cast<STONEYDSP_INT8_T> (value);
}

STONEYDSP_INLINE
STONEYDSP_CONSTEXPR STONEYDSP_UINT8_T STONEYDSP_PUBLIC_FUNCTION
/**
 * @brief
 *
 */
operator"" _uint8_t (unsigned long long value) STONEYDSP_NOEXCEPT
{
  return static_cast<STONEYDSP_UINT8_T> (value);
}

STONEYDSP_INLINE
STONEYDSP_CONSTEXPR STONEYDSP_INT16_T STONEYDSP_PUBLIC_FUNCTION
/**
 * @brief
 *
 */
operator"" _int16_t (unsigned long long value) STONEYDSP_NOEXCEPT
{
  return static_cast<STONEYDSP_INT16_T> (value);
}

STONEYDSP_INLINE
STONEYDSP_CONSTEXPR STONEYDSP_UINT16_T STONEYDSP_PUBLIC_FUNCTION
/**
 * @brief
 *
 */
operator"" _uint16_t (unsigned long long value) STONEYDSP_NOEXCEPT
{
  return static_cast<STONEYDSP_UINT16_T> (value);
}

STONEYDSP_INLINE
STONEYDSP_CONSTEXPR STONEYDSP_INT32_T STONEYDSP_PUBLIC_FUNCTION
/**
 * @brief
 *
 */
operator"" _int32_t (unsigned long long value) STONEYDSP_NOEXCEPT
{
  return static_cast<STONEYDSP_INT32_T> (value);
}

STONEYDSP_INLINE
STONEYDSP_CONSTEXPR STONEYDSP_UINT32_T STONEYDSP_PUBLIC_FUNCTION
/**
 * @brief
 *
 */
operator"" _uint32_t (unsigned long long value) STONEYDSP_NOEXCEPT
{
  return static_cast<STONEYDSP_UINT32_T> (value);
}

STONEYDSP_INLINE
STONEYDSP_CONSTEXPR STONEYDSP_INT64_T STONEYDSP_PUBLIC_FUNCTION
/**
 * @brief
 *
 */
operator"" _int64_t (unsigned long long value) STONEYDSP_NOEXCEPT
{
  return STONEYDSP_INT64_C (value);
}

STONEYDSP_INLINE
STONEYDSP_CONSTEXPR STONEYDSP_UINT64_T STONEYDSP_PUBLIC_FUNCTION
/**
 * @brief
 *
 */
operator"" _uint64_t (unsigned long long value) STONEYDSP_NOEXCEPT
{
  return STONEYDSP_UINT64_C (value);
}

/// @} literals
} // namespace literals

/// @} types
} // namespace types

/// @} group core
} //  namespace core

/// @} group stoneydsp
} // namespace stoneydsp

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

template <typename T>
/**
 * @brief the `__numeric_limits_base` struct,
 *
 * @tparam T
 *
 */
STONEYDSP_PACKED_STRUCT_BEGIN struct STONEYDSP_ALIGN (alignof (T))
    __numeric_limits_base
{
private:
  STONEYDSP_DECLARE_NON_CONSTRUCTABLE (__numeric_limits_base)
  STONEYDSP_DECLARE_NON_COPYABLE (__numeric_limits_base)
  STONEYDSP_DECLARE_NON_MOVEABLE (__numeric_limits_base)
public:
  /** True if the type is signed.  */
  static STONEYDSP_CONSTEXPR STONEYDSP_BOOL_T is_signed = false;

  /** True if the type is integer.  */
  static STONEYDSP_CONSTEXPR STONEYDSP_BOOL_T is_integer = false;

} STONEYDSP_PACKED_STRUCT_END;

/// @} types
} // namespace types

/// @} group core
} //  namespace core

template <typename T>
STONEYDSP_PACKED_STRUCT_BEGIN struct STONEYDSP_ALIGN (alignof (T))
    numeric_limits : public ::stoneydsp::core::types::__numeric_limits_base<T>
{
private:
  STONEYDSP_DECLARE_NON_COPYABLE (numeric_limits)
  STONEYDSP_DECLARE_NON_MOVEABLE (numeric_limits)
  STONEYDSP_DECLARE_NON_CONSTRUCTABLE (numeric_limits)
public:
  static STONEYDSP_CONSTEXPR T STONEYDSP_API
  lowest () STONEYDSP_NOEXCEPT
  {
    return T ();
  }

  /**
   * The minimum finite value, or for floating types with
   *  denormalization, the minimum positive normalized value.
   */
  static STONEYDSP_CONSTEXPR T STONEYDSP_API
  min () STONEYDSP_NOEXCEPT
  {
    return T ();
  }

  /** The maximum finite value.  */
  static STONEYDSP_CONSTEXPR T STONEYDSP_API
  max () STONEYDSP_NOEXCEPT
  {
    return T ();
  }

} STONEYDSP_PACKED_STRUCT_END;

template <typename T>
STONEYDSP_PACKED_STRUCT_BEGIN struct STONEYDSP_ALIGN (alignof (T))
    numeric_limits<const T> : public numeric_limits<T>
{
} STONEYDSP_PACKED_STRUCT_END;

template <typename T>
STONEYDSP_PACKED_STRUCT_BEGIN struct STONEYDSP_ALIGN (alignof (T))
    numeric_limits<volatile T> : public numeric_limits<T>
{
} STONEYDSP_PACKED_STRUCT_END;

template <typename T>
STONEYDSP_PACKED_STRUCT_BEGIN struct STONEYDSP_ALIGN (alignof (T))
    numeric_limits<const volatile T> : public numeric_limits<T>
{
} STONEYDSP_PACKED_STRUCT_END;

template <>
STONEYDSP_PACKED_STRUCT_BEGIN struct STONEYDSP_ALIGN (
    alignof (STONEYDSP_BOOL_T)) numeric_limits<STONEYDSP_BOOL_T>
{

  static STONEYDSP_CONSTEXPR STONEYDSP_BOOL_T STONEYDSP_API
  /**
   * @brief
   *
   * Equivalent to:
   *
   * - bool: `true`
   *
   * - char: `1U`
   *
   * @return `stoneydsp::bool_t`
   */
  max () STONEYDSP_NOEXCEPT
  {
    return ::stoneydsp_bool_max ();
  }

  static STONEYDSP_CONSTEXPR STONEYDSP_BOOL_T STONEYDSP_API
  /**
   * @brief
   *
   * Equivalent to:
   *
   * - bool: `false`
   *
   * - char: `0U`
   *
   * @return `stoneydsp::bool_t`
   */
  min () STONEYDSP_NOEXCEPT
  {
    return ::stoneydsp_bool_min ();
  }

  static STONEYDSP_CONSTEXPR STONEYDSP_BOOL_T STONEYDSP_API
  /**
   * @brief
   *
   * Equivalent to:
   *
   * - bool: `false`
   *
   * - char: `0U`
   *
   * @return `stoneydsp::bool_t`
   */
  lowest () STONEYDSP_NOEXCEPT
  {
    return ::stoneydsp_bool_lowest ();
  }

} STONEYDSP_PACKED_STRUCT_END;

template <>
STONEYDSP_PACKED_STRUCT_BEGIN struct STONEYDSP_ALIGN (
    alignof (STONEYDSP_CHAR_T)) numeric_limits<STONEYDSP_CHAR_T>
{

  static STONEYDSP_CONSTEXPR STONEYDSP_CHAR_T STONEYDSP_API
  /**
   * @brief
   *
   * Typically equivalent to:
   *
   * - dec: `127`
   *
   * - oct: `0177`
   *
   * - hex: `0x7F`
   *
   * @return `stoneydsp::char_t`
   *
   */
  max () STONEYDSP_NOEXCEPT
  {
    return ::stoneydsp_char_max ();
  }

  static STONEYDSP_CONSTEXPR STONEYDSP_CHAR_T STONEYDSP_API
  /**
   * @brief
   *
   * Typically equivalent to:
   *
   * - dec: `-128`
   *
   * - oct: `-0800`
   *
   * - hex: `-0x80`
   *
   * @return `stoneydsp::char_t`
   *
   */
  min () STONEYDSP_NOEXCEPT
  {
    return ::stoneydsp_char_min ();
  }

  static STONEYDSP_CONSTEXPR STONEYDSP_CHAR_T STONEYDSP_API
  lowest () STONEYDSP_NOEXCEPT
  {
    /**
     * @brief
     *
     * Typically equivalent to:
     *
     * - dec: `-128`
     *
     * - oct: `-0800`
     *
     * - hex: `-0x80`
     *
     * @return `stoneydsp::char_t`
     *
     */
    return ::stoneydsp_char_lowest ();
  }

} STONEYDSP_PACKED_STRUCT_END;

template <>
STONEYDSP_PACKED_STRUCT_BEGIN struct STONEYDSP_ALIGN (
    alignof (STONEYDSP_SCHAR_T)) numeric_limits<STONEYDSP_SCHAR_T>
{

  static STONEYDSP_CONSTEXPR STONEYDSP_SCHAR_T STONEYDSP_API
  /**
   * @brief
   *
   * Typically equivalent to:
   *
   * - dec: `127`
   *
   * - oct: `0177`
   *
   * - hex: `0x7F`
   *
   * @return `stoneydsp::char_t`
   *
   */
  max () STONEYDSP_NOEXCEPT
  {
    return ::stoneydsp_schar_max ();
  }

  static STONEYDSP_CONSTEXPR STONEYDSP_SCHAR_T STONEYDSP_API
  /**
   * @brief
   *
   * Typically equivalent to:
   *
   * - dec: `-128`
   *
   * - oct: `-0800`
   *
   * - hex: `-0x80`
   *
   * @return `stoneydsp::schar_t`
   *
   */
  min () STONEYDSP_NOEXCEPT
  {
    return ::stoneydsp_schar_min ();
  }

  static STONEYDSP_CONSTEXPR STONEYDSP_SCHAR_T STONEYDSP_API
  /**
   * @brief
   *
   * Typically equivalent to:
   *
   * - dec: `-128`
   *
   * - oct: `-0800`
   *
   * - hex: `-0x80`
   *
   * @return `stoneydsp::schar_t`
   *
   */
  lowest () STONEYDSP_NOEXCEPT
  {
    return ::stoneydsp_schar_lowest ();
  }

} STONEYDSP_PACKED_STRUCT_END;

template <>
STONEYDSP_PACKED_STRUCT_BEGIN struct STONEYDSP_ALIGN (
    alignof (STONEYDSP_UCHAR_T)) numeric_limits<STONEYDSP_UCHAR_T>
{

  static STONEYDSP_CONSTEXPR STONEYDSP_UCHAR_T STONEYDSP_API
  max () STONEYDSP_NOEXCEPT
  {
    return ::stoneydsp_uchar_max ();
  }

  static STONEYDSP_CONSTEXPR STONEYDSP_UCHAR_T STONEYDSP_API
  min () STONEYDSP_NOEXCEPT
  {
    return ::stoneydsp_uchar_min ();
  }

  static STONEYDSP_CONSTEXPR STONEYDSP_UCHAR_T STONEYDSP_API
  lowest () STONEYDSP_NOEXCEPT
  {
    return ::stoneydsp_uchar_lowest ();
  }

} STONEYDSP_PACKED_STRUCT_END;

template <>
STONEYDSP_PACKED_STRUCT_BEGIN struct STONEYDSP_ALIGN (
    alignof (STONEYDSP_SHRT_T)) numeric_limits<STONEYDSP_SHRT_T>
{

  static STONEYDSP_CONSTEXPR STONEYDSP_SHRT_T STONEYDSP_API
  max () STONEYDSP_NOEXCEPT
  {
    return ::stoneydsp_shrt_max ();
  }

  static STONEYDSP_CONSTEXPR STONEYDSP_SHRT_T STONEYDSP_API
  min () STONEYDSP_NOEXCEPT
  {
    return ::stoneydsp_shrt_min ();
  }

  static STONEYDSP_CONSTEXPR STONEYDSP_SHRT_T STONEYDSP_API
  lowest () STONEYDSP_NOEXCEPT
  {
    return ::stoneydsp_shrt_lowest ();
  }

} STONEYDSP_PACKED_STRUCT_END;

template <>
STONEYDSP_PACKED_STRUCT_BEGIN struct STONEYDSP_ALIGN (
    alignof (STONEYDSP_USHRT_T)) numeric_limits<STONEYDSP_USHRT_T>
{

  static STONEYDSP_CONSTEXPR STONEYDSP_USHRT_T STONEYDSP_API
  min () STONEYDSP_NOEXCEPT
  {
    return ::stoneydsp_ushrt_min ();
  }

  static STONEYDSP_CONSTEXPR STONEYDSP_USHRT_T STONEYDSP_API
  max () STONEYDSP_NOEXCEPT
  {
    return ::stoneydsp_ushrt_max ();
  }

  static STONEYDSP_CONSTEXPR STONEYDSP_USHRT_T STONEYDSP_API
  lowest () STONEYDSP_NOEXCEPT
  {
    return ::stoneydsp_ushrt_lowest ();
  }

} STONEYDSP_PACKED_STRUCT_END;

template <>
STONEYDSP_PACKED_STRUCT_BEGIN struct STONEYDSP_ALIGN (
    alignof (STONEYDSP_INT_T)) numeric_limits<STONEYDSP_INT_T>
{

  static STONEYDSP_CONSTEXPR STONEYDSP_INT_T STONEYDSP_API
  max () STONEYDSP_NOEXCEPT
  {
    return ::stoneydsp_int_max ();
  }

  static STONEYDSP_CONSTEXPR STONEYDSP_INT_T STONEYDSP_API
  min () STONEYDSP_NOEXCEPT
  {
    return ::stoneydsp_int_min ();
  }

  static STONEYDSP_CONSTEXPR STONEYDSP_INT_T STONEYDSP_API
  lowest () STONEYDSP_NOEXCEPT
  {
    return ::stoneydsp_int_lowest ();
  }

} STONEYDSP_PACKED_STRUCT_END;

template <>
STONEYDSP_PACKED_STRUCT_BEGIN struct STONEYDSP_ALIGN (
    alignof (STONEYDSP_UINT_T)) numeric_limits<STONEYDSP_UINT_T>
{
  static STONEYDSP_CONSTEXPR STONEYDSP_UINT_T STONEYDSP_API
  max () STONEYDSP_NOEXCEPT
  {
    return ::stoneydsp_uint_max ();
  }

  static STONEYDSP_CONSTEXPR STONEYDSP_UINT_T STONEYDSP_API
  min () STONEYDSP_NOEXCEPT
  {
    return ::stoneydsp_uint_min ();
  }

  static STONEYDSP_CONSTEXPR STONEYDSP_UINT_T STONEYDSP_API
  lowest () STONEYDSP_NOEXCEPT
  {
    return ::stoneydsp_uint_lowest ();
  }

} STONEYDSP_PACKED_STRUCT_END;

template <>
STONEYDSP_PACKED_STRUCT_BEGIN struct STONEYDSP_ALIGN (
    alignof (STONEYDSP_LONG_T)) numeric_limits<STONEYDSP_LONG_T>
{

  static STONEYDSP_CONSTEXPR STONEYDSP_LONG_T STONEYDSP_API
  max () STONEYDSP_NOEXCEPT
  {
    return ::stoneydsp_long_max ();
  }

  static STONEYDSP_CONSTEXPR STONEYDSP_LONG_T STONEYDSP_API
  min () STONEYDSP_NOEXCEPT
  {
    return ::stoneydsp_long_min ();
  }

  static STONEYDSP_CONSTEXPR STONEYDSP_LONG_T STONEYDSP_API
  lowest () STONEYDSP_NOEXCEPT
  {
    return ::stoneydsp_long_lowest ();
  }

} STONEYDSP_PACKED_STRUCT_END;

template <>
STONEYDSP_PACKED_STRUCT_BEGIN struct STONEYDSP_ALIGN (
    alignof (STONEYDSP_ULONG_T)) numeric_limits<STONEYDSP_ULONG_T>
{

  static STONEYDSP_CONSTEXPR STONEYDSP_ULONG_T STONEYDSP_API
  max () STONEYDSP_NOEXCEPT
  {
    return ::stoneydsp_ulong_max ();
  }

  static STONEYDSP_CONSTEXPR STONEYDSP_ULONG_T STONEYDSP_API
  min () STONEYDSP_NOEXCEPT
  {
    return ::stoneydsp_ulong_min ();
  }

  static STONEYDSP_CONSTEXPR STONEYDSP_ULONG_T STONEYDSP_API
  lowest () STONEYDSP_NOEXCEPT
  {
    return ::stoneydsp_ulong_lowest ();
  }

} STONEYDSP_PACKED_STRUCT_END;

template <>
STONEYDSP_PACKED_STRUCT_BEGIN struct STONEYDSP_ALIGN (
    alignof (STONEYDSP_LLONG_T)) numeric_limits<STONEYDSP_LLONG_T>
{

  static STONEYDSP_CONSTEXPR STONEYDSP_LLONG_T STONEYDSP_API
  max () STONEYDSP_NOEXCEPT
  {
    return ::stoneydsp_llong_max ();
  }

  static STONEYDSP_CONSTEXPR STONEYDSP_LLONG_T STONEYDSP_API
  min () STONEYDSP_NOEXCEPT
  {
    // TODO: check and fix this value
    return ::stoneydsp_llong_min ();
  }

  static STONEYDSP_CONSTEXPR STONEYDSP_LLONG_T STONEYDSP_API
  lowest () STONEYDSP_NOEXCEPT
  {
    return ::stoneydsp_llong_lowest ();
  }

} STONEYDSP_PACKED_STRUCT_END;

template <>
STONEYDSP_PACKED_STRUCT_BEGIN struct STONEYDSP_ALIGN (
    alignof (STONEYDSP_ULLONG_T)) numeric_limits<STONEYDSP_ULLONG_T>
{

  static STONEYDSP_CONSTEXPR STONEYDSP_ULLONG_T STONEYDSP_API
  max () STONEYDSP_NOEXCEPT
  {
    return ::stoneydsp_ullong_max ();
  }

  static STONEYDSP_CONSTEXPR STONEYDSP_ULLONG_T STONEYDSP_API
  min () STONEYDSP_NOEXCEPT
  {
    return ::stoneydsp_ullong_min ();
  }

  static STONEYDSP_CONSTEXPR STONEYDSP_ULLONG_T STONEYDSP_API
  lowest () STONEYDSP_NOEXCEPT
  {
    return ::stoneydsp_ullong_lowest ();
  }

} STONEYDSP_PACKED_STRUCT_END;

template <>
STONEYDSP_PACKED_STRUCT_BEGIN struct STONEYDSP_ALIGN (
    alignof (STONEYDSP_DBL_T)) numeric_limits<STONEYDSP_DBL_T>
{

  static STONEYDSP_CONSTEXPR STONEYDSP_DBL_T STONEYDSP_API
  max () STONEYDSP_NOEXCEPT
  {
    return ::stoneydsp_double_max ();
  }

  static STONEYDSP_CONSTEXPR STONEYDSP_DBL_T STONEYDSP_API
  min () STONEYDSP_NOEXCEPT
  {
    return ::stoneydsp_double_min ();
  }

  static STONEYDSP_CONSTEXPR STONEYDSP_DBL_T STONEYDSP_API
  lowest () STONEYDSP_NOEXCEPT
  {
    return ::stoneydsp_double_lowest ();
  }

} STONEYDSP_PACKED_STRUCT_END;

template <>
STONEYDSP_PACKED_STRUCT_BEGIN struct STONEYDSP_ALIGN (
    alignof (STONEYDSP_LDBL_T)) numeric_limits<STONEYDSP_LDBL_T>
{

  static STONEYDSP_CONSTEXPR STONEYDSP_LDBL_T STONEYDSP_API
  max () STONEYDSP_NOEXCEPT
  {
    return ::stoneydsp_ldouble_max ();
  }

  static STONEYDSP_CONSTEXPR STONEYDSP_LDBL_T STONEYDSP_API
  min () STONEYDSP_NOEXCEPT
  {
    return ::stoneydsp_ldouble_min ();
  }

  static STONEYDSP_CONSTEXPR STONEYDSP_LDBL_T STONEYDSP_API
  lowest () STONEYDSP_NOEXCEPT
  {
    return ::stoneydsp_ldouble_lowest ();
  }

} STONEYDSP_PACKED_STRUCT_END;

template <>
STONEYDSP_PACKED_STRUCT_BEGIN struct STONEYDSP_ALIGN (
    alignof (STONEYDSP_FLT_T)) numeric_limits<STONEYDSP_FLT_T>
{

  static STONEYDSP_CONSTEXPR STONEYDSP_FLT_T STONEYDSP_API
  max () STONEYDSP_NOEXCEPT
  {
    return ::stoneydsp_float_max ();
  }

  static STONEYDSP_CONSTEXPR STONEYDSP_FLT_T STONEYDSP_API
  min () STONEYDSP_NOEXCEPT
  {
    return ::stoneydsp_float_min ();
  }

  static STONEYDSP_CONSTEXPR STONEYDSP_FLT_T STONEYDSP_API
  lowest () STONEYDSP_NOEXCEPT
  {
    return ::stoneydsp_float_lowest ();
  }

} STONEYDSP_PACKED_STRUCT_END;

/// @} group stoneydsp
} // namespace stoneydsp

  #endif //_cplusplus

//============================================================================//

#endif // STONEYDSP_CORE_SYSTEM_TYPES_H_INCLUDED

//=========================================================================//EOF
