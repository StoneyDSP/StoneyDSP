/**
 * @file core.cpp
 * @author StoneyDSP (nathanjhood@googlemail.com)
 * @copyright Copyright (c) 2025
 *
 */

//==============================================================================

#ifdef STONEYDSP_CORE_H_INCLUDED
  #error wrong inclusion of stoneydsp/core/core.h
#endif

#include "stoneydsp/core/core.h"

//==============================================================================

/* Construct a string literal encoding the version number. */
#ifdef STONEYDSP_VERSION
char const *stoneydsp_version
    = "INFO"
      ":"
      "StoneyDSP version [" STONEYDSP_STRINGIFY (STONEYDSP_VERSION) "]";

/* Construct a string literal encoding the version number components. */
#elif defined(STONEYDSP_VERSION_MAJOR)
char const stoneydsp_version[]
    = { 'I',
        'N',
        'F',
        'O',
        ':',
        'S',
        't',
        'o',
        'n',
        'e',
        'y',
        'D',
        'S',
        'P',
        '_',
        'v',
        'e',
        'r',
        's',
        'i',
        'o',
        'n',
        '_',
        '[',
        STONEYDSP_STRINGIFY (STONEYDSP_VERSION_MAJOR),
  #ifdef STONEYDSP_VERSION_MINOR
        '.',
        STONEYDSP_STRINGIFY (STONEYDSP_VERSION_MINOR),
    #ifdef STONEYDSP_VERSION_PATCH
        '.',
        STONEYDSP_STRINGIFY (STONEYDSP_VERSION_PATCH),
      #ifdef STONEYDSP_VERSION_TWEAK
        '.',
        STONEYDSP_STRINGIFY (STONEYDSP_VERSION_TWEAK),
      #endif
    #endif
  #endif
        ']',
        '\0' };
#else
char const *stoneydsp_version = "INFO"
                                ":"
                                "StoneyDSP version [UNKNOWN]";
#endif

//==============================================================================

namespace stoneydsp
{
namespace core
{
namespace types
{
namespace literals
{

STONEYDSP_PUBLIC_FUNCTION
stoneydsp::int8_t
operator"" _int8 (unsigned long long value)
{
  return static_cast< ::stoneydsp::int8_t> (INT8_C (value));
}

STONEYDSP_PUBLIC_FUNCTION
stoneydsp::int16_t
operator"" _int16 (unsigned long long value)
{
  return static_cast< ::stoneydsp::int16_t> (INT16_C (value));
}

STONEYDSP_PUBLIC_FUNCTION stoneydsp::int32_t
operator"" _int32 (unsigned long long value)
{
  return static_cast< ::stoneydsp::int32_t> (INT32_C (value));
}

STONEYDSP_PUBLIC_FUNCTION stoneydsp::int64_t
operator"" _int64 (unsigned long long value)
{
  return static_cast< ::stoneydsp::int64_t> (INT64_C(value));
}

STONEYDSP_PUBLIC_FUNCTION stoneydsp::uint8_t
operator"" _uint8 (unsigned long long value)
{
  return static_cast< ::stoneydsp::uint8_t> (UINT8_C (value));
}

STONEYDSP_PUBLIC_FUNCTION stoneydsp::uint16_t
operator"" _uint16 (unsigned long long value)
{
  return static_cast< ::stoneydsp::uint16_t> (UINT16_C(value));
}

STONEYDSP_PUBLIC_FUNCTION stoneydsp::uint32_t
operator"" _uint32 (unsigned long long value)
{
  return static_cast< ::stoneydsp::uint32_t> (UINT32_C(value));
}

STONEYDSP_PUBLIC_FUNCTION stoneydsp::uint64_t
operator"" _uint64 (unsigned long long value)
{
  return static_cast< ::stoneydsp::uint64_t> (UINT64_C(value));
}

} // namespace literals
} // namespace types
} // namespace core
} // namespace stoneydsp

//============================================================================//
