/**
 * @file languages.h
 * @author StoneyDSP (nathanjhood@googlemail.com)
 * @brief
 * @version @STONEYDSP_CORE_VERSION@
 * @date 2025-01-27
 *
 * @copyright Copyright (c) 2025
 *
 */

#pragma once

#ifndef STONEYDSP_CORE_SYSTEM_LANGUAGES_H_INCLUDED
  #define STONEYDSP_CORE_SYSTEM_LANGUAGES_H_INCLUDED

//==============================================================================

/**
 * Language-specific code, as inferred by the compiler from the file extension,
 * and possibly other build-time configurations.
 */

//==============================================================================

  #ifdef __STDC__
    #define STONEYDSP_CC __STDC__
  #endif

//==============================================================================

  #ifdef __cplusplus
    #define STONEYDSP_CXX __cplusplus
  #endif

//==============================================================================

  #ifdef __OBJC__
    #ifdef __cplusplus
      #define STONEYDSP_OBJCXX __OBJC__
    #else // !_cplusplus
      #define STONEYDSP_OBJC __OBJC__
    #endif // _cplusplus
  #endif

//==============================================================================

  #ifdef STONEYDSP_CXX
    // Standard namespace macros
    #define STONEYDSP_NAMESPACE_BEGIN(name)                                   \
      namespace name                                                          \
      {
    #define STONEYDSP_NAMESPACE_END }
    // Fully-qualified namespace macros
    #define STONEYDSP_NAMESPACE_QUAL(qual_name) qual_name::
  #else
    // Standard namespace macros
    #define STONEYDSP_NAMESPACE_BEGIN(name)
    #define STONEYDSP_NAMESPACE_END
    // Fully-qualified namespace macros
    #define STONEYDSP_NAMESPACE_QUAL(qual_name) qual_name
  #endif

//==============================================================================

  #ifdef STONEYDSP_CXX
    #define STONEYDSP_EXTERN_C extern "C"
    #define STONEYDSP_EXTERN_C_BEGIN                                          \
      extern "C"                                                              \
      {
    #define STONEYDSP_EXTERN_C_END }
  #else
    #define STONEYDSP_EXTERN_C
    #define STONEYDSP_EXTERN_C_BEGIN
    #define STONEYDSP_EXTERN_C_END
  #endif

//==============================================================================

  #ifdef STONEYDSP_CXX
    #define STONEYDSP_CONSTEXPR constexpr
  #else
    #define STONEYDSP_CONSTEXPR const
  #endif

//==============================================================================

#ifdef STONEYDSP_CXX
  #ifdef _NOEXCEPT
    #define STONEYDSP_NOEXCEPT _NOEXCEPT
  #else
    #define STONEYDSP_NOEXCEPT noexcept
  #endif
#else
  #define STONEYDSP_NOEXCEPT
#endif

//==============================================================================

#endif // STONEYDSP_CORE_SYSTEM_LANGUAGES_H_INCLUDED

//=========================================================================//EOF
