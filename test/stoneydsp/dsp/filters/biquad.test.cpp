/**
 * @file biquad.test.cpp
 * @author StoneyDSP (nathanjhood@googlemail.com)
 * @copyright Copyright (c) 2026
 */

#include "stoneydsp/dsp/filters/biquad.h"

#if defined(STONEYDSP_BUILD_TEST)

  #include "../../../utils.test.hpp"

namespace
{
template <typename SampleType>
bool
approximatelyEqual (SampleType actual, SampleType expected,
                    SampleType tolerance)
{
  return std::abs (actual - expected) <= tolerance;
}

template <typename SampleType>
std::vector<SampleType>
renderImpulse (::stoneydsp::dsp::filters::BiquadTransformType transform)
{
  ::stoneydsp::dsp::filters::Biquad<SampleType> filter;
  filter.prepare (static_cast<SampleType> (48000));
  filter.setFilterType (
      ::stoneydsp::dsp::filters::BiquadFilterType::lowPass2);
  filter.setFrequency (static_cast<SampleType> (2500));
  filter.setResonance (static_cast<SampleType> (0.35));
  filter.setTransformType (transform);

  std::vector<SampleType> response (128, static_cast<SampleType> (0));
  response[0] = static_cast<SampleType> (1);
  filter.processBlock (&response[0], response.size ());
  return response;
}
} // namespace

STONEYDSP_TEST_CASE ("[dsp][biquad][coefficients][dc-response]",
                     "[dsp][biquad][coefficients][dc-response]")
{
  typedef ::stoneydsp::dsp::filters::BiquadFilterType FilterType;
  const double sampleRate = 48000.0;
  const double frequency = 1000.0;
  const double resonance = 0.5;

  const ::stoneydsp::dsp::filters::BiquadCoefficients<double> lowPass
      = ::stoneydsp::dsp::filters::calculateBiquadCoefficients (
          FilterType::lowPass2, sampleRate, frequency, resonance, 0.0);
  const ::stoneydsp::dsp::filters::BiquadCoefficients<double> highPass
      = ::stoneydsp::dsp::filters::calculateBiquadCoefficients (
          FilterType::highPass2, sampleRate, frequency, resonance, 0.0);

  const double lowPassDc
      = (lowPass.b0 + lowPass.b1 + lowPass.b2)
        / (1.0 - lowPass.a1 - lowPass.a2);
  const double highPassDc
      = (highPass.b0 + highPass.b1 + highPass.b2)
        / (1.0 - highPass.a1 - highPass.a2);

  STONEYDSP_REQUIRE (approximatelyEqual (lowPassDc, 1.0, 1.0e-12));
  STONEYDSP_REQUIRE (approximatelyEqual (highPassDc, 0.0, 1.0e-12));
}

STONEYDSP_TEST_CASE ("[dsp][biquad][transforms][equivalent-impulse]",
                     "[dsp][biquad][transforms][equivalent-impulse]")
{
  typedef ::stoneydsp::dsp::filters::BiquadTransformType TransformType;
  const std::vector<double> reference
      = renderImpulse<double> (TransformType::directFormI);
  const TransformType transforms[] = {
    TransformType::directFormII,
    TransformType::directFormITransposed,
    TransformType::directFormIITransposed
  };

  for (std::size_t transformIndex = 0;
       transformIndex < sizeof (transforms) / sizeof (transforms[0]);
       ++transformIndex)
    {
      const std::vector<double> response
          = renderImpulse<double> (transforms[transformIndex]);
      for (std::size_t sampleIndex = 0; sampleIndex < reference.size ();
           ++sampleIndex)
        STONEYDSP_REQUIRE (approximatelyEqual (
            response[sampleIndex], reference[sampleIndex], 1.0e-12));
    }
}

STONEYDSP_TEST_CASE ("[dsp][biquad][processor][identity-and-reset]",
                     "[dsp][biquad][processor][identity-and-reset]")
{
  ::stoneydsp::dsp::filters::Biquad_float_t filter;
  STONEYDSP_REQUIRE_FALSE (filter.isPrepared ());

  filter.prepare (48000.0F);
  STONEYDSP_REQUIRE (filter.isPrepared ());
  STONEYDSP_REQUIRE (filter.processSample (0.25F) == 0.25F);

  filter.setFilterType (
      ::stoneydsp::dsp::filters::BiquadFilterType::lowPass2);
  filter.setFrequency (1000.0F);
  const float firstOutput = filter.processSample (1.0F);
  filter.processSample (0.0F);
  filter.reset ();
  STONEYDSP_REQUIRE (
      approximatelyEqual (filter.processSample (1.0F), firstOutput, 1.0e-7F));
}

STONEYDSP_TEST_CASE ("[dsp][biquad][processor][all-modes-remain-finite]",
                     "[dsp][biquad][processor][all-modes-remain-finite]")
{
  typedef ::stoneydsp::dsp::filters::BiquadFilterType FilterType;
  typedef ::stoneydsp::dsp::filters::BiquadTransformType TransformType;

  const FilterType filterTypes[] = {
    FilterType::lowPass2,
    FilterType::lowPass1,
    FilterType::highPass2,
    FilterType::highPass1,
    FilterType::bandPass,
    FilterType::bandPassQ,
    FilterType::lowShelf2,
    FilterType::lowShelf1,
    FilterType::lowShelf1C,
    FilterType::highShelf2,
    FilterType::highShelf1,
    FilterType::highShelf1C,
    FilterType::peak,
    FilterType::notch,
    FilterType::allPass
  };
  const TransformType transforms[] = {
    TransformType::directFormI,
    TransformType::directFormII,
    TransformType::directFormITransposed,
    TransformType::directFormIITransposed
  };

  for (std::size_t typeIndex = 0;
       typeIndex < sizeof (filterTypes) / sizeof (filterTypes[0]); ++typeIndex)
    for (std::size_t transformIndex = 0;
         transformIndex < sizeof (transforms) / sizeof (transforms[0]);
         ++transformIndex)
      {
        ::stoneydsp::dsp::filters::Biquad_double_t filter;
        filter.prepare (96000.0);
        filter.setFrequency (12000.0);
        filter.setResonance (0.25);
        filter.setGainDecibels (6.0);
        filter.setFilterType (filterTypes[typeIndex]);
        filter.setTransformType (transforms[transformIndex]);

        for (std::size_t sampleIndex = 0; sampleIndex < 2048; ++sampleIndex)
          {
            const double input = sampleIndex == 0 ? 1.0 : 0.0;
            STONEYDSP_REQUIRE (std::isfinite (filter.processSample (input)));
          }
      }
}

#endif // defined(STONEYDSP_BUILD_TEST)
