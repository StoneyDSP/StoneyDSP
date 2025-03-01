/**
 * @file compiler.h
 * @author StoneyDSP (nathanjhood@googlemail.com)
 * @brief
 * @version @STONEYDSP_CORE_VERSION@
 * @date 2025-01-27
 *
 * @copyright Copyright (c) 2025
 *
 */

#pragma once

#ifndef STONEYDSP_CORE_SYSTEM_COMPILER_H_INCLUDED
  #define STONEYDSP_CORE_SYSTEM_COMPILER_H_INCLUDED

//==============================================================================

  #include "stoneydsp/core/system/platform.h"

//==============================================================================

  #if defined(__clang__)
    #define STONEYDSP_CLANG 1
    #define STONEYDSP_COMPILER_VERSION STONEYDSP_STRINGIFY (__clang__)
  #elif defined(__GNUC__)
    #define STONEYDSP_GCC 1
    #define STONEYDSP_COMPILER_VERSION STONEYDSP_STRINGIFY (__GNUC__)
  #elif defined(_MSC_VER)
    #define STONEYDSP_MSVC 1
    #define STONEYDSP_COMPILER_VERSION STONEYDSP_STRINGIFY (_MSC_VER)
  #else
    #error unknown compiler
  #endif

//==============================================================================

  #if defined(STONEYDSP_CLANG)
    #define STONEYDSP_COMPILER "Clang"
  #elif defined(STONEYDSP_GCC)
    #define STONEYDSP_COMPILER "GNU"
  #elif defined(STONEYDSP_MSVC)
    #define STONEYDSP_COMPILER "MSVC"
  #else
    #error unknown compiler
  #endif

  //==============================================================================

  /**
   * These macros define the C call type and calling convention definitions
   * used as the standard for StoneyDSP calls.
   */

  /* Define calling conventions based on architecture and compiler */
  #if defined(STONEYDSP_32BIT)
    #if defined(STONEYDSP_MSVC)
      /** @brief Specifies a calling convention where the callee cleans up the
       * stack.
       */
      #define STONEYDSP_CALLTYPE __stdcall
      /** @brief Specifies a calling convention where the caller cleans up the
       * stack.
       */
      #define STONEYDSP_CDECL __cdecl
    #elif defined(STONEYDSP_MINGW) || defined(STONEYDSP_GCC)                  \
        || defined(STONEYDSP_CLANG)
      /** @brief Specifies a calling convention where the callee cleans up the
       * stack.
       */
      #define STONEYDSP_CALLTYPE __attribute__ ((stdcall))
      /** @brief Specifies a calling convention where the caller cleans up the
       * stack.
       */
      #define STONEYDSP_CDECL __attribute__ ((cdecl))
    #else
      #error "Unknown calling convention for 32-bit architecture"
    #endif

  #elif defined(STONEYDSP_64BIT)
    #if defined(STONEYDSP_MSVC)
      /** @brief Uses the default Microsoft x64 calling convention. */
      #define STONEYDSP_CALLTYPE
      /** @brief Specifies a calling convention where the caller cleans up the
       * stack.
       */
      #define STONEYDSP_CDECL __cdecl
    #elif defined(STONEYDSP_MINGW)
      /** @brief Specifies a calling convention compatible with Microsoft x64
       * ABI. */
      #define STONEYDSP_CALLTYPE __attribute__ ((ms_abi))
      /** @brief Specifies a calling convention where the caller cleans up the
       * stack.
       */
      #define STONEYDSP_CDECL __attribute__ ((cdecl))
    #elif defined(STONEYDSP_GCC) || defined(STONEYDSP_CLANG)
      /** @brief Uses the default System V AMD64 ABI calling convention. */
      #define STONEYDSP_CALLTYPE __attribute__ ((sysv_abi))
      /** @brief Specifies a calling convention where the caller cleans up the
       * stack.
       */
      #define STONEYDSP_CDECL __attribute__ ((sysv_abi))
    #else
      #error "Unknown calling convention for 64-bit architecture"
    #endif

  #elif defined(STONEYDSP_ARM)
    #if defined(STONEYDSP_MSVC)
      /** @brief Specifies a calling convention for ARM on MSVC. */
      #define STONEYDSP_CALLTYPE __stdcall
      #define STONEYDSP_CDECL __cdecl
    #elif defined(STONEYDSP_GCC) || defined(STONEYDSP_CLANG)
      #if defined(__arm__)
        /** @brief Specifies the ARM Procedure Call Standard (AAPCS). */
        #define STONEYDSP_CALLTYPE __attribute__ ((pcs ("aapcs")))
        #define STONEYDSP_CDECL
      #elif defined(__aarch64__)
        /** @brief Specifies the ARM Procedure Call Standard with VFP
         * (AAPCS-VFP). */
        #define STONEYDSP_CALLTYPE __attribute__ ((pcs ("aapcs-vfp")))
        #define STONEYDSP_CDECL
      #else
        #error "Unknown ARM architecture"
      #endif
    #else
      #error "Unknown calling convention for ARM architecture"
    #endif

  #else
    #error "Unknown architecture"
  #endif

  /* Fallbacks for unsupported configurations */
  #ifndef STONEYDSP_CALLTYPE
    #define STONEYDSP_CALLTYPE
  #endif

  #ifndef STONEYDSP_CDECL
    #define STONEYDSP_CDECL
  #endif

//==============================================================================

/**
 * These macros export/import definitions for different platforms.
 *
 * NOTE: `-DSTONEYDSP_EXPORTS` should only be set by StoneyDSP maintainers
 * and contributors.
 *
 * - *we* build StoneyDSP with `-DSTONEYDSP_EXPORTS` so that our library
 * exports its' symbols to consumers.
 *
 * - *you* build your software against StoneyDSP without setting
 * `-DSTONEYDSP_EXPORTS` so that your software imports our symbols.
 *
 * If StoneyDSP is being built from source, i.e., by a package manager and
 * build system, it should set `-DSTONEYDSP_EXPORTS` if compiling the StoneyDSP
 * library as a binary-compiled resource (i.e., a dynamic or static library).
 *
 * If StoneyDSP is being linked with, for example as a pre-built binary in your
 * project's dependency chain, the flag should have already been compiled in,
 * meaning that consumers in this case should *not* be setting it.
 *
 */

  #if STONEYDSP_MSVC
    #ifdef STONEYDSP_EXPORTS
      /** @brief Used to export a function or variable from a DLL. */
      #define STONEYDSP_API __declspec (dllexport)
    #else
      /** @brief Used to import a function or variable from a DLL. */
      #define STONEYDSP_API __declspec (dllimport)
    #endif
  #else
    #ifdef STONEYDSP_EXPORTS
      /** @brief Used to make the symbol visible and available for dynamic
       * linking */
      #define STONEYDSP_API __attribute__ ((visibility ("default")))
    #else
      /** @brief Controls the visibility of symbols at build-time. */
      #define STONEYDSP_API
    #endif
  #endif

  //==============================================================================

  /** This macro is added to all public function declarations. */
  #define STONEYDSP_PUBLIC_FUNCTION STONEYDSP_API STONEYDSP_CALLTYPE

//==============================================================================

/**
 * Alignment and packing macros.
 *
 * - STONEYDSP_ALIGN(n) - Ensures that the structure is aligned to an 8-byte
 * boundary, which can be important for performance and correctness on some
 * platforms. Should be an integer number equal to the `sizeof()` the largest
 * data member (in bits).
 *
 * - STONEYDSP_PACK - Ensures that the structure has no padding added by the
 * compiler, making it packed.
 *
 * @example
 * ```cpp
 * STONEYDSP_PACKED_STRUCT_BEGIN
 * class STONEYDSP_ALIGN(sizeof(stoneydsp::uint_16)) MyClass {
 * public:
 *   MyClass() : smaller(0U), larger(0U) {};
 *   stoneydsp::uint_8 smaller;
 *   stoneydsp::uint_16 larger;
 * } STONEYDSP_PACKED_STRUCT_END;
 * ```
 *
 */

  #if STONEYDSP_MSVC
    #define STONEYDSP_ALIGN(n) __declspec (align (n))
    #define STONEYDSP_PACKED_STRUCT_BEGIN __pragma (pack (push, 1))
    #define STONEYDSP_PACKED_STRUCT_END __pragma (pack (pop))
  #else
    #define STONEYDSP_ALIGN(n) __attribute__ ((aligned (n)))
    #define STONEYDSP_PACKED_STRUCT_BEGIN
    #define STONEYDSP_PACKED_STRUCT_END __attribute__ ((packed))
  #endif

//==============================================================================

  #if STONEYDSP_MSVC
    #define STONEYDSP_MALLOC_ATTR __declspec (restrict)
  #else
    #define STONEYDSP_MALLOC_ATTR __attribute__ ((malloc))
  #endif

//==============================================================================

  #if STONEYDSP_MSVC
    #define STONEYDSP_INLINE_ATTR __forceinline
  #else // STONEYDSP_GCC || STONEYDSP_CLANG
    #define STONEYDSP_INLINE_ATTR __attribute__ ((always_inline))
  #endif

  #define STONEYDSP_INLINE inline STONEYDSP_INLINE_ATTR

//==============================================================================

#endif // STONEYDSP_CORE_SYSTEM_COMPILER_H_INCLUDED

//=========================================================================//EOF
