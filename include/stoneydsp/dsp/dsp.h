/**
 * @file dsp.h
 * @author StoneyDSP (nathanjhood@googlemail.com)
 * @brief
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

//============================================================================//

#endif // STONEYDSP_DSP_H_INCLUDED

//=========================================================================//EOF
