#include <stoneydsp/dsp/dsp.h>

int main ()
{
  ::stoneydsp::dsp::widgets::Gain<float, float> gain;
  ::stoneydsp::dsp::filters::Biquad_float_t biquad;
  float sample = 1.0F;
  gain.processSample (&sample);
  biquad.prepare (48000.0F);
  sample = biquad.processSample (sample);
  return sample == 1.0F ? 0 : 1;
}
