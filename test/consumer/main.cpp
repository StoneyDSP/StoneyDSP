#include <stoneydsp/dsp/dsp.h>

int main ()
{
  ::stoneydsp::dsp::widgets::Gain<float, float> gain;
  float sample = 1.0F;
  gain.processSample (&sample);
  return sample == 1.0F ? 0 : 1;
}
