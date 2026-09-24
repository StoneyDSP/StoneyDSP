/**
 * @file dsp.test.cpp
 * @author StoneyDSP (nathanjhood@googlemail.com)
 * @copyright Copyright (c) 2025
 *
 */

//==============================================================================

#include "stoneydsp/dsp/dsp.h"

//==============================================================================

#if defined(STONEYDSP_BUILD_TEST)

//==============================================================================

  #include "../../utils.test.hpp"

//==============================================================================

STONEYDSP_TEST_CASE ("[dsp][gain][default-unity]",
                     "[dsp][gain][default-unity]")
{
  ::stoneydsp::dsp::widgets::Gain<float, float> gain;
  float sample = 0.25F;

  gain.processSample (&sample);

  STONEYDSP_REQUIRE (gain.getGain () == 1.0F);
  STONEYDSP_REQUIRE (sample == 0.25F);
}

STONEYDSP_TEST_CASE ("[dsp][gain][sample-and-block]",
                     "[dsp][gain][sample-and-block]")
{
  ::stoneydsp::dsp::widgets::Gain<float, float> gain;
  float sample = 0.5F;
  float block[] = { 1.0F, -1.0F, 0.25F, 0.0F };

  gain.setGain (0.5F);
  gain.processSample (&sample);
  gain.applyGain (block, 4U, gain.getGain ());

  STONEYDSP_REQUIRE (sample == 0.25F);
  STONEYDSP_REQUIRE (block[0] == 0.5F);
  STONEYDSP_REQUIRE (block[1] == -0.5F);
  STONEYDSP_REQUIRE (block[2] == 0.125F);
  STONEYDSP_REQUIRE (block[3] == 0.0F);
}

#endif // defined(STONEYDSP_BUILD_TEST)

//=========================================================================//EOF
