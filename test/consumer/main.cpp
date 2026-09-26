#include <stoneydsp/dsp/dsp.h>

int main ()
{
  ::stoneydsp::dsp::widgets::Gain<float, float> gain;
  ::stoneydsp::dsp::filters::Biquad_float_t biquad;
  const ::stoneydsp::dsp::filters::BiquadCoefficients<float> matched
      = ::stoneydsp::dsp::filters::calculateMatchedBiquadCoefficients (
          ::stoneydsp::dsp::filters::MatchedBiquadFilterType::lowPass,
          48000.0F, 2400.0F, 1.0F, 0.0F);
  const float binary_gain
      = ::stoneydsp::core::maths::bitsToGain (1.0F);
  const float pi = ::stoneydsp::core::maths::Constants<float>::pi;
  float sample = 1.0F;
  gain.processSample (&sample);
  biquad.prepare (48000.0F);
  sample = biquad.processSample (sample);
  return sample == 1.0F && binary_gain == 2.0F && pi > 3.14F
                 && matched.b0 != 1.0F
             ? 0
             : 1;
}
