/**
 * @file main.h
 * @author StoneyDSP (nathanjhood@googlemail.com)
 * @brief
 * @version
 * @date 2025-02-23
 *
 * @copyright Copyright (c) 2025
 *
 */

#pragma once

#ifndef STONEYDSP_MAIN_H_INCLUDED
  #define STONEYDSP_MAIN_H_INCLUDED

  #if defined(STONEYDSP_BUILD_MAIN)
    #include "stoneydsp/stoneydsp.h"

    #ifdef __cplusplus
      #include <iostream>
      #if defined(STONEYDSP_SUPPORTS_WIDECHARS) && defined(UNICODE)
        #include <cwchar>
      #endif
      #include <climits> // for INT_MAX
      #include <cstdlib> // for EXIT_SUCCESS and EXIT_FAILURE
    #else                // !__cplusplus
      #include <stdio.h>
      #if defined(STONEYDSP_SUPPORTS_WIDECHARS) && defined(UNICODE)
        #include <wchar.h>
      #endif
      #include <limits.h> // for INT_MAX
      #include <stdlib.h> // For EXIT_SUCCESS and EXIT_FAILURE
    #endif                // __cplusplus

  #endif // STONEYDSP_BUILD_MAIN

  #ifdef __cplusplus

namespace stoneydsp
{
/**
 * @brief
 *
 * @returns void
 */
void STONEYDSP_PUBLIC_FUNCTION run ();
} // namespace stoneydsp

  #else // !__cplusplus

/**
 * @brief
 *
 * @returns void
 */
void STONEYDSP_PUBLIC_FUNCTION stoneydsp_run ();

  #endif // __cplusplus

/**
 * @brief Standard main entry point logic
 *
 * @param argc
 * @param argv
 * @return int
 */
int main (int argc, char *argv[]);

  #if defined(STONEYDSP_SUPPORTS_WIDECHARS) && defined(UNICODE)

/**
 * @brief UTF-16 to UTF-8 wrapper for Windows with unicode.
 *
 * @param argc
 * @param wargv
 * @return int
 */
int wmain (int argc, wchar_t *wargv[]);

  #endif // defined (STONEYDSP_SUPPORTS_WIDECHARS) && defined (UNICODE)

#endif // STONEYDSP_MAIN_H_INCLUDED
