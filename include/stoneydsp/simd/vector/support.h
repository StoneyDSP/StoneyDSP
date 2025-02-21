/**
 * @file support.h
 * @author StoneyDSP (nathanjhood@googlemail.com)
 * @brief
 * @version 0.1
 * @date 2025-02-12
 *
 * @copyright Copyright (c) 2025
 *
 */

#pragma once

#ifndef STONEYDSP_SIMD_VECTOR_SUPPORT_H_INCLUDED
  #define STONEYDSP_SIMD_VECTOR_SUPPORT_H_INCLUDED

  #include <stoneydsp/core/core.h>

  /**
   * Native headers:
   *
   * <mmintrin.h>  MMX
   * <xmmintrin.h> SSE
   * <emmintrin.h> SSE2
   * <pmmintrin.h> SSE3
   * <tmmintrin.h> SSSE3
   * <smmintrin.h> SSE4.1
   * <nmmintrin.h> SSE4.2
   * <ammintrin.h> SSE4A
   * <wmmintrin.h> AES
   * <immintrin.h> AVX, AVX2, FMA
   * <arm_neon.h>
   *
   * SIMDe Headers:
   *
   * <simde/x86/mmx.h> MMX
   * <simde/x86/sse.h> SSE
   * <simde/x86/sse2.h> SSE2
   * <simde/x86/sse3.h> SSE3
   * <simde/x86/ssse3.h> SSSE3
   * <simde/x86/sse4.1.h> SSE4.1
   * <simde/x86/sse4.2.h> SSE4.2
   * <simde/x86/sse4a.h> SSE4A
   * <simde/x86/aes.h> AES
   * <simde/x86/avx.h> AVX
   * <simde/x86/avx2.h> AVX2
   * <simde/x86/fma.h> FMA
   * <simde/x86/avx512.h> AVX-512
   * <simde/arm/neon.h>
   *
   */

  // Detect compiler and platform, and include necessary headers accordingly
  #if defined(_MSC_VER)
    // Microsoft Visual Studio
    #include <ammintrin.h> // SSE4A
    #include <emmintrin.h> // SSE2
    #include <immintrin.h> // AVX, AVX2, FMA
    #include <intrin.h>
    #include <mmintrin.h>  // MMX
    #include <nmmintrin.h> // SSE4.2
    #include <pmmintrin.h> // SSE3
    #include <smmintrin.h> // SSE4.1
    #include <tmmintrin.h> // SSSE3
    #include <wmmintrin.h> // AES
    #include <xmmintrin.h> // SSE
  #elif defined(__GNUC__) || defined(__clang__)
    // GCC or Clang
    #if defined(__x86_64__) || defined(__i386__)
      // x86 or x64
      #if defined(__AVX2__)
        #include <immintrin.h>
      #elif defined(__AVX__)
        #include <immintrin.h>
      #elif defined(__AES__)
        #include <wmmintrin.h>
      #elif defined(__SSE4A__)
        #include <ammintrin.h>
      #elif defined(__SSE4_2__)
        #include <nmmintrin.h>
      #elif defined(__SSE4_1__)
        #include <smmintrin.h>
      #elif defined(__SSSE3__)
        #include <tmmintrin.h>
      #elif defined(__SSE3__)
        #include <pmmintrin.h>
      #elif defined(__SSE2__)
        #include <emmintrin.h>
      #elif defined(__SSE__)
        #include <xmmintrin.h>
      #elif defined(__MMX__)
        #include <mmintrin.h>
      #else
        #include <simde/x86/aes.h>
        #include <simde/x86/avx.h>
        #include <simde/x86/avx2.h>
        #include <simde/x86/avx512.h>
        #include <simde/x86/mmx.h>
        #include <simde/x86/sse.h>
        #include <simde/x86/sse2.h>
        #include <simde/x86/sse3.h>
        #include <simde/x86/sse4.1.h>
        #include <simde/x86/sse4.2.h>
        #include <simde/x86/sse4a.h>
        #include <simde/x86/ssse3.h>
      #endif
    #elif defined(__aarch64__) || defined(__arm__)
      // ARM64 or ARM
      #if defined(__ARM_NEON)
        #include <arm_neon.h>
      #else
        #include <simde/arm/neon.h>
      #endif
    #else
      // Unsupported platform
      #error "Unsupported platform for SIMD"
    #endif
  #else
    // Other compilers or unsupported platforms
    #error "Unsupported compiler or platform"
  #endif

#endif // STONEYDSP_SIMD_VECTOR_SUPPORT_H_INCLUDED
