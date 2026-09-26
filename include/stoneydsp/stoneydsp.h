/**
 * @file stoneydsp.h
 * @author StoneyDSP (nathanjhood@googlemail.com)
 * @brief Top-level public StoneyDSP umbrella header.
 *
 * Component headers remain independently usable; consumers that require a
 * specific component may include its component header directly and should link
 * the matching exported CMake target.
 * @version @STONEYDSP_VERSION@
 * @date 2025-01-27
 *
 * @copyright Copyright (c) 2025
 *
 */

#pragma once

#ifndef STONEYDSP_H_INCLUDED
  #define STONEYDSP_H_INCLUDED

//==============================================================================

  #ifdef STONEYDSP_BUILD_CORE
    #include "stoneydsp/core/core.h"
  #endif

//==============================================================================

  #ifdef STONEYDSP_BUILD_SIMD
  // 	#include "stoneydsp/simd/simd.h"
  #endif

//==============================================================================

  #ifdef STONEYDSP_BUILD_DSP
  // #include "stoneydsp/dsp/dsp.h"
  #endif

//==============================================================================

#endif // STONEYDSP_H_INCLUDED

//=========================================================================//EOF
