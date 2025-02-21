/**
 * @file core.c
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

//============================================================================//
