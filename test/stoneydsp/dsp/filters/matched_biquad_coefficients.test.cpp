/**
 * @file matched_biquad_coefficients.test.cpp
 * @author StoneyDSP (nathanjhood@googlemail.com)
 * @copyright Copyright (c) 2026
 */

#include "stoneydsp/dsp/filters/matched_biquad_coefficients.h"

#if defined(STONEYDSP_BUILD_TEST)

  #include "../../../utils.test.hpp"

  #include <cmath>
  #include <complex>

namespace
{
typedef ::stoneydsp::dsp::filters::BiquadCoefficients<double> Coefficients;
typedef ::stoneydsp::dsp::filters::MatchedBiquadFilterType FilterType;
typedef ::stoneydsp::core::maths::Constants<double> Constants;

double
magnitudeAt (const Coefficients &coefficients, double omega)
{
  const std::complex<double> z1
      = std::exp (std::complex<double> (0.0, -omega));
  const std::complex<double> z2 = z1 * z1;
  const std::complex<double> numerator
      = coefficients.b0 + (coefficients.b1 * z1)
        + (coefficients.b2 * z2);
  const std::complex<double> denominator
      = 1.0 - (coefficients.a1 * z1) - (coefficients.a2 * z2);
  return std::abs (numerator / denominator);
}

bool
approximatelyEqual (double actual, double expected, double tolerance)
{
  return std::abs (actual - expected) <= tolerance;
}

bool
isIdentity (const Coefficients &coefficients)
{
  return coefficients.b0 == 1.0 && coefficients.b1 == 0.0
         && coefficients.b2 == 0.0 && coefficients.a1 == 0.0
         && coefficients.a2 == 0.0;
}
} // namespace

STONEYDSP_TEST_CASE ("[dsp][matched-biquad][reference-constraints]",
                     "[dsp][matched-biquad][reference-constraints]")
{
  const double sampleRate = 48000.0;
  const double frequencies[] = { 240.0, 2400.0, 9600.0, 19200.0 };
  const double qualityFactors[] = { 0.5, Constants::oneDivSqrtTwo, 1.0, 3.0,
                                    10.0 };

  for (std::size_t frequencyIndex = 0;
       frequencyIndex < sizeof (frequencies) / sizeof (frequencies[0]);
       ++frequencyIndex)
    for (std::size_t qIndex = 0;
         qIndex < sizeof (qualityFactors) / sizeof (qualityFactors[0]);
         ++qIndex)
      {
        const double frequency = frequencies[frequencyIndex];
        const double qualityFactor = qualityFactors[qIndex];
        const double omega
            = (Constants::twoPi * frequency) / sampleRate;

        const Coefficients lowPass
            = ::stoneydsp::dsp::filters::calculateMatchedBiquadCoefficients (
                FilterType::lowPass, sampleRate, frequency, qualityFactor,
                0.0);
        const Coefficients highPass
            = ::stoneydsp::dsp::filters::calculateMatchedBiquadCoefficients (
                FilterType::highPass, sampleRate, frequency, qualityFactor,
                0.0);
        const Coefficients bandPass
            = ::stoneydsp::dsp::filters::calculateMatchedBiquadCoefficients (
                FilterType::bandPass, sampleRate, frequency, qualityFactor,
                0.0);

        STONEYDSP_REQUIRE (
            approximatelyEqual (magnitudeAt (lowPass, 0.0), 1.0, 1.0e-9));
        STONEYDSP_REQUIRE (approximatelyEqual (
            magnitudeAt (lowPass, omega), qualityFactor, 1.0e-9));
        STONEYDSP_REQUIRE (
            approximatelyEqual (magnitudeAt (highPass, 0.0), 0.0, 1.0e-9));
        STONEYDSP_REQUIRE (approximatelyEqual (
            magnitudeAt (highPass, omega), qualityFactor, 1.0e-9));
        STONEYDSP_REQUIRE (
            approximatelyEqual (magnitudeAt (bandPass, 0.0), 0.0, 1.0e-9));
        STONEYDSP_REQUIRE (
            approximatelyEqual (magnitudeAt (bandPass, omega), 1.0, 1.0e-9));
      }
}

STONEYDSP_TEST_CASE ("[dsp][matched-biquad][peaking-response]",
                     "[dsp][matched-biquad][peaking-response]")
{
  const double sampleRate = 48000.0;
  const double frequency = 9600.0;
  const double qualityFactor = 1.0;
  const double omega = (Constants::twoPi * frequency) / sampleRate;
  const double gains[] = { -20.0, -6.0, 6.0, 20.0 };

  for (std::size_t gainIndex = 0;
       gainIndex < sizeof (gains) / sizeof (gains[0]); ++gainIndex)
    {
      const double gain = gains[gainIndex];
      const Coefficients coefficients
          = ::stoneydsp::dsp::filters::calculateMatchedBiquadCoefficients (
              FilterType::peak, sampleRate, frequency, qualityFactor, gain);

      STONEYDSP_REQUIRE (approximatelyEqual (
          magnitudeAt (coefficients, 0.0), 1.0, 1.0e-8));
      STONEYDSP_REQUIRE (approximatelyEqual (
          magnitudeAt (coefficients, omega), std::pow (10.0, gain / 20.0),
          1.0e-7));
    }

  STONEYDSP_REQUIRE (isIdentity (
      ::stoneydsp::dsp::filters::calculateMatchedBiquadCoefficients (
          FilterType::peak, sampleRate, frequency, qualityFactor, 0.0)));
}

STONEYDSP_TEST_CASE ("[dsp][matched-biquad][domain-and-float]",
                     "[dsp][matched-biquad][domain-and-float]")
{
  const double sampleRate = 48000.0;

  STONEYDSP_REQUIRE (isIdentity (
      ::stoneydsp::dsp::filters::calculateMatchedBiquadCoefficients (
          FilterType::lowPass, 0.0, 1000.0, 1.0, 0.0)));
  STONEYDSP_REQUIRE (isIdentity (
      ::stoneydsp::dsp::filters::calculateMatchedBiquadCoefficients (
          FilterType::lowPass, sampleRate, 0.0, 1.0, 0.0)));
  STONEYDSP_REQUIRE (isIdentity (
      ::stoneydsp::dsp::filters::calculateMatchedBiquadCoefficients (
          FilterType::lowPass, sampleRate, sampleRate * 0.5, 1.0, 0.0)));
  STONEYDSP_REQUIRE (isIdentity (
      ::stoneydsp::dsp::filters::calculateMatchedBiquadCoefficients (
          FilterType::lowPass, sampleRate, 1000.0, 0.0, 0.0)));

  const ::stoneydsp::dsp::filters::BiquadCoefficients<float> coefficients
      = ::stoneydsp::dsp::filters::calculateMatchedBiquadCoefficients (
          FilterType::lowPass, 48000.0F, 2400.0F, 3.0F, 0.0F);
  STONEYDSP_REQUIRE (std::isfinite (coefficients.b0));
  STONEYDSP_REQUIRE (std::isfinite (coefficients.b1));
  STONEYDSP_REQUIRE (std::isfinite (coefficients.b2));
  STONEYDSP_REQUIRE (std::isfinite (coefficients.a1));
  STONEYDSP_REQUIRE (std::isfinite (coefficients.a2));
}

#endif // defined(STONEYDSP_BUILD_TEST)
