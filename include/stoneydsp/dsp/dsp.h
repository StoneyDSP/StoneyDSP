/**
 * @file dsp.h
 * @author StoneyDSP (nathanjhood@googlemail.com)
 * @brief Public umbrella for reusable C++ DSP primitives.
 *
 * The DSP component depends on the portable core surface. Stateful processors
 * own their processing state; stateless coefficient and conversion helpers are
 * provided separately. This header deliberately has no JUCE or product-host
 * dependency.
 * @version @STONEYDSP_DSP_VERSION@
 * @date 2025-02-22
 *
 * @copyright Copyright (c) 2025
 *
 */

#pragma once

#ifndef STONEYDSP_DSP_H_INCLUDED
  #define STONEYDSP_DSP_H_INCLUDED

//============================================================================//

  #include <stoneydsp/core/core.h>

//==============================================================================

  #ifdef __cplusplus

// Forward-declaration of dsp namespaces

namespace stoneydsp
{
/** @addtogroup stoneydsp
 *  @{
 */

/**
 * @brief The `stoneydsp::dsp` namespace.
 * @author Nathan J. Hood (nathanjhood@googlemail.com)
 * @copyright Copyright (c) 2025
 * @version @STONEYDSP_DSP_VERSION@
 *
 */
namespace dsp
{
/** @addtogroup dsp
 *  @{
 */

/// @} group dsp
} //  namespace dsp

/// @} group stoneydsp
} // namespace stoneydsp

  #endif // __cplusplus

//============================================================================//

  #include "stoneydsp/dsp/widgets/gain.h"

  #ifdef __cplusplus
    #include "stoneydsp/dsp/filters/biquad_coefficients.h"

    #include "stoneydsp/dsp/filters/biquad.h"

    #include "stoneydsp/dsp/filters/matched_biquad_coefficients.h"
  #endif

//============================================================================//

#endif // STONEYDSP_DSP_H_INCLUDED

//=========================================================================//EOF
