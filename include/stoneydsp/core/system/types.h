/**
 *
 */

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

//=====================================================================//DEFINES

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

    #ifdef STONEYDSP_CXX

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
      #define STONEYDSP_PTRDIFF_T                                             \
        (decltype (static_cast<int *> (nullptr)                               \
                   - static_cast<int *> (nullptr)))
    // #define STONEYDSP_NULLPTR_T  nullptr_t
    // #define STONEYDSP_MAX_ALIGN_T  max_align_t

    #else // !STONEYDSP_CXX

      #define STOMEYDSP_SIZE_T typeof (sizeof (0))
      #define STOMEYDSP_PTRDIFF_T typeof ((int *)nullptr - (int *)nullptr)

    #endif // STONEYDSP_CXX

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

//====================================================================//LITERALS

  #define STONEYDSP_DBL_LITERAL(n) n
  #define STONEYDSP_LDBL_LITERAL(n) n##L
  #define STONEYDSP_FLT_LITERAL(n) n##F

  #define STONEYDSP_CHAR_LITERAL(n) n
  #define STONEYDSP_SCHAR_LITERAL(n) n
  #define STONEYDSP_UCHAR_LITERAL(n) n##U

  #define STONEYDSP_INT_LITERAL(n) n
  #define STONEYDSP_UINT_LITERAL(n) n##U

  #define STONEYDSP_SHRT_LITERAL(n) n
  #define STONEYDSP_USHRT_LITERAL(n) n##U

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
  #define STONEYDSP_UINT64_LITERAL(n) n##U

  #define STONEYDSP_SIZE_LITERAL(n) n##U
  #define STONEYDSP_PTRDIFF_LITERAL(n) n

//=================================================================//CONVERSIONS

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

//======================================================================//PRINTF

  #define STONEYDSP_INT8_PRINT_F PRIi8
  #define STONEYDSP_INT16_PRINT_F PRIi16
  #define STONEYDSP_INT32_PRINT_F PRIi32
  #define STONEYDSP_INT64_PRINT_F PRIi64

  #define STONEYDSP_UINT8_PRINT_F PRIu8
  #define STONEYDSP_UINT16_PRINT_F PRIu16
  #define STONEYDSP_UINT32_PRINT_F PRIu32
  #define STONEYDSP_UINT64_PRINT_F PRIu64

//=======================================================================//SCANF

  #define STONEYDSP_INT8_SCAN_F SCNi8
  #define STONEYDSP_INT16_SCAN_F SCNi16
  #define STONEYDSP_INT32_SCAN_F SCNi32
  #define STONEYDSP_INT64_SCAN_F SCNi64

  #define STONEYDSP_UINT8_SCAN_F SCNu8
  #define STONEYDSP_UINT16_SCAN_F SCNu16
  #define STONEYDSP_UINT32_SCAN_F SCNu32
  #define STONEYDSP_UINT64_SCAN_F SCNu64

//======================================================================//LIMITS

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

/**
 * @brief
 * Equivalent to:
 *
 * - dec: `127`
 *
 * - oct: `0177`
 *
 * - hex: `0x7F`
 */
  #define STONEYDSP_INT8_MAX STONEYDSP_INT8_C (STONEYDSP_INT8_LITERAL (0177))

/**
 * @brief
 * Equivalent to:
 *
 * - dec: `32767`
 *
 * - oct: `077777`
 *
 * - hex: `0x7FFF`
 */
  #define STONEYDSP_INT16_MAX                                                 \
    STONEYDSP_INT16_C (STONEYDSP_INT16_LITERAL (0x7FFF))

/**
 * @brief
 * Equivalent to:
 *
 * - dec: `2147483647`
 *
 * - oct: `017777777777`
 *
 * - hex: `0x7FFFFFFF`
 */
  #define STONEYDSP_INT32_MAX                                                 \
    STONEYDSP_INT32_C (STONEYDSP_INT32_LITERAL (2147483647))

/**
 * @brief
 * Equivalent to:
 *
 * - dec: `255`
 *
 * - oct: `0377`
 *
 * - hex: `0xFF`
 */
  #define STONEYDSP_UINT8_MAX                                                 \
    STONEYDSP_UINT8_C (STONEYDSP_UINT8_LITERAL (0377))

/**
 * @brief
 * Equivalent to:
 *
 * - dec: `65535`
 *
 * - oct: `0177777`
 *
 * - hex: `0xFFFF`
 */
  #define STONEYDSP_UINT16_MAX                                                \
    STONEYDSP_UINT16_C (STONEYDSP_UINT16_LITERAL (0xFFFF))

/**
 * @brief
 * Equivalent to:
 *
 * - dec: `4294967295`
 *
 * - oct: `037777777777`
 *
 * - hex: `0xFFFFFFFF`
 */
  #define STONEYDSP_UINT32_MAX                                                \
    STONEYDSP_UINT32_C (STONEYDSP_UINT32_LITERAL (4294967295))

// #define STONEYDSP_CHAR8_MIN STONEYDSP_UCHAR_MIN
// #define STONEYDSP_CHAR16_MIN STONEYDSP_USHRT_MIN
// #define STONEYDSP_CHAR32_MIN STONEYDSP_UINT_MIN

/**
 * @brief
 * Equivalent to:
 *
 * - dec: `-128`
 *
 * - oct: `-0200`
 *
 * - hex: `-0x80`
 */
  #define STONEYDSP_INT8_MIN                                                  \
    STONEYDSP_INT8_C ((-STONEYDSP_INT8_MAX)                                   \
                      - STONEYDSP_INT8_C (STONEYDSP_INT8_LITERAL (01)))

/**
 * @brief
 * Equivalent to:
 *
 * - dec: `-32768`
 *
 * - oct: `-0100000`
 *
 * - hex: `-0x8000`
 */
  #define STONEYDSP_INT16_MIN                                                 \
    STONEYDSP_INT16_C (                                                       \
        (-STONEYDSP_INT16_MAX)                                                \
        - STONEYDSP_INT16_C (STONEYDSP_INT16_LITERAL (0x0001)))

/**
 * @brief
 * Equivalent to:
 *
 * - dec: `-2147483648`
 *
 * - oct: `-020000000000`
 *
 * - hex: `-0x80000000`
 */
  #define STONEYDSP_INT32_MIN                                                 \
    STONEYDSP_INT32_C ((-STONEYDSP_INT32_MAX)                                 \
                       - STONEYDSP_INT32_C (STONEYDSP_INT32_LITERAL (1)))

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

  #ifdef __cplusplus

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
STONEYDSP_PACKED_STRUCT_BEGIN struct STONEYDSP_INTERNAL
STONEYDSP_ALIGN (alignof (T)) __numeric_limits_base
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
STONEYDSP_PACKED_STRUCT_BEGIN struct STONEYDSP_API
STONEYDSP_ALIGN (alignof (T)) numeric_limits
    : public ::stoneydsp::core::types::__numeric_limits_base<T>
{
private:
  STONEYDSP_DECLARE_NON_COPYABLE (numeric_limits)
  STONEYDSP_DECLARE_NON_MOVEABLE (numeric_limits)
  STONEYDSP_DECLARE_NON_CONSTRUCTABLE (numeric_limits)

public:
  STONEYDSP_INLINE static STONEYDSP_CONSTEXPR T STONEYDSP_API
  lowest () STONEYDSP_NOEXCEPT
  {
    return T ();
  }

  /**
   * The minimum finite value, or for floating types with
   *  denormalization, the minimum positive normalized value.
   */
  STONEYDSP_INLINE static STONEYDSP_CONSTEXPR T STONEYDSP_API
  min () STONEYDSP_NOEXCEPT
  {
    return T ();
  }

  /** The maximum finite value.  */
  STONEYDSP_INLINE static STONEYDSP_CONSTEXPR T STONEYDSP_API
  max () STONEYDSP_NOEXCEPT
  {
    return T ();
  }

} STONEYDSP_PACKED_STRUCT_END;

template <typename T>
STONEYDSP_PACKED_STRUCT_BEGIN struct STONEYDSP_API
STONEYDSP_ALIGN (alignof (T)) numeric_limits<const T>
    : public numeric_limits<T>
{
} STONEYDSP_PACKED_STRUCT_END;

template <typename T>
STONEYDSP_PACKED_STRUCT_BEGIN struct STONEYDSP_API
STONEYDSP_ALIGN (alignof (T)) numeric_limits<volatile T>
    : public numeric_limits<T>
{
} STONEYDSP_PACKED_STRUCT_END;

template <typename T>
STONEYDSP_PACKED_STRUCT_BEGIN struct STONEYDSP_API
STONEYDSP_ALIGN (alignof (T)) numeric_limits<const volatile T>
    : public numeric_limits<T>
{
} STONEYDSP_PACKED_STRUCT_END;

/// @} group stoneydsp
} // namespace stoneydsp

  #endif //_cplusplus

//============================================================================//

#endif // STONEYDSP_CORE_SYSTEM_TYPES_H_INCLUDED

//=========================================================================//EOF
