/**
 * @file matched_biquad_coefficients.h
 * @author StoneyDSP (nathanjhood@googlemail.com)
 * @brief Analogue-matched second-order filter coefficient calculations.
 * @version @STONEYDSP_DSP_VERSION@
 * @date 2026-09-26
 *
 * @copyright Copyright (c) 2026
 *
 * The coefficient design follows Martin Vicanek, "Matched Second Order
 * Digital Filters" (2016): https://vicanek.de/articles/BiquadFits.pdf
 */

#pragma once

#ifndef STONEYDSP_DSP_FILTERS_MATCHED_BIQUAD_COEFFICIENTS_H_INCLUDED
  #define STONEYDSP_DSP_FILTERS_MATCHED_BIQUAD_COEFFICIENTS_H_INCLUDED

//==============================================================================

  #include "stoneydsp/dsp/filters/biquad_coefficients.h"

//==============================================================================

  #include <cmath>

//==============================================================================

namespace stoneydsp
{
/** @addtogroup stoneydsp
 * @{
 */

//==============================================================================

namespace dsp
{
/** @addtogroup dsp
 * @{
 */

//==============================================================================

namespace filters
{
/** @addtogroup filters
 * @{
 */

//==============================================================================

/** Analogue-matched responses from Vicanek's second-order filter design. */
enum class MatchedBiquadFilterType
{
  lowPass = 0,
  highPass,
  bandPass,
  peak
};

//==============================================================================

namespace detail
{
/** @addtogroup detail
 * @{
 */

//==============================================================================

template <typename SampleType>
STONEYDSP_INLINE BiquadCoefficients<SampleType>
makeMatchedBiquadCoefficients (
    ::stoneydsp::core::types::double_t b0,
    ::stoneydsp::core::types::double_t b1,
    ::stoneydsp::core::types::double_t b2,
    ::stoneydsp::core::types::double_t a1,
    ::stoneydsp::core::types::double_t a2) STONEYDSP_NOEXCEPT
{
  typedef ::stoneydsp::core::types::double_t WorkingType;
  const WorkingType one = static_cast<WorkingType> (1);
  const WorkingType two = static_cast<WorkingType> (2);

  if (!std::isfinite (b0) || !std::isfinite (b1) || !std::isfinite (b2)
      || !std::isfinite (a1) || !std::isfinite (a2)
      || !(std::abs (a1) < two) || !(std::abs (a1) - one < a2)
      || !(a2 < one))
    return BiquadCoefficients<SampleType> ();

  const BiquadCoefficients<SampleType> coefficients (
      static_cast<SampleType> (b0), static_cast<SampleType> (b1),
      static_cast<SampleType> (b2), static_cast<SampleType> (-a1),
      static_cast<SampleType> (-a2));

  const WorkingType storedB0 = static_cast<WorkingType> (coefficients.b0);
  const WorkingType storedB1 = static_cast<WorkingType> (coefficients.b1);
  const WorkingType storedB2 = static_cast<WorkingType> (coefficients.b2);
  const WorkingType storedA1 = -static_cast<WorkingType> (coefficients.a1);
  const WorkingType storedA2 = -static_cast<WorkingType> (coefficients.a2);

  if (!std::isfinite (storedB0) || !std::isfinite (storedB1)
      || !std::isfinite (storedB2) || !std::isfinite (storedA1)
      || !std::isfinite (storedA2)
      || !(std::abs (storedA1) < two)
      || !(std::abs (storedA1) - one < storedA2) || !(storedA2 < one))
    return BiquadCoefficients<SampleType> ();

  return coefficients;
}

/// @} group detail
} // namespace detail

//==============================================================================

/**
 * Calculates an analogue-matched second-order coefficient set.
 *
 * `qualityFactor` is the Q of the analogue prototype and must be positive.
 * The characteristic frequency must lie strictly between DC and Nyquist.
 * Invalid or non-finite input, an invalid intermediate result, or coefficients
 * which become unstable after conversion to `SampleType` produce the identity
 * coefficient set.
 *
 * All intermediate calculations use double precision, including when the
 * requested coefficient type is float. This follows the numerical guidance in
 * the source paper; only the final five coefficients are converted.
 */
template <typename SampleType>
STONEYDSP_INLINE BiquadCoefficients<SampleType>
calculateMatchedBiquadCoefficients (
    MatchedBiquadFilterType type, SampleType sampleRate, SampleType frequency,
    SampleType qualityFactor, SampleType gainDecibels) STONEYDSP_NOEXCEPT
{
  typedef ::stoneydsp::core::types::double_t WorkingType;
  typedef ::stoneydsp::core::maths::Constants<WorkingType> Constants;
  typedef ::stoneydsp::core::maths::Functions<WorkingType> Functions;

  const WorkingType workingSampleRate
      = static_cast<WorkingType> (sampleRate);
  const WorkingType workingFrequency = static_cast<WorkingType> (frequency);
  const WorkingType q = static_cast<WorkingType> (qualityFactor);
  const WorkingType workingGainDecibels
      = static_cast<WorkingType> (gainDecibels);
  const WorkingType zero = static_cast<WorkingType> (0);
  const WorkingType one = static_cast<WorkingType> (1);
  const WorkingType two = static_cast<WorkingType> (2);
  const WorkingType four = two * two;
  const WorkingType half = one / two;

  if (!std::isfinite (workingSampleRate)
      || !std::isfinite (workingFrequency) || !std::isfinite (q)
      || !std::isfinite (workingGainDecibels)
      || !(workingSampleRate > zero) || !(workingFrequency > zero)
      || !(workingFrequency < workingSampleRate * half) || !(q > zero))
    return BiquadCoefficients<SampleType> ();

  if (type == MatchedBiquadFilterType::peak
      && workingGainDecibels == zero)
    return BiquadCoefficients<SampleType> ();

  const WorkingType omega
      = (Constants::twoPi * workingFrequency) / workingSampleRate;
  const WorkingType phi1 = Functions::square (std::sin (half * omega));
  const WorkingType phi0 = one - phi1;
  const WorkingType phi2 = four * phi0 * phi1;
  const WorkingType amplitude
      = ::stoneydsp::core::maths::decibelsToGain (workingGainDecibels);

  WorkingType poleAmplitude = one;
  if (type == MatchedBiquadFilterType::peak)
    poleAmplitude = amplitude;

  if (!(poleAmplitude > zero) || !std::isfinite (poleAmplitude))
    return BiquadCoefficients<SampleType> ();

  const WorkingType poleScale = std::sqrt (poleAmplitude) * q;
  if (!(poleScale > zero) || !std::isfinite (poleScale))
    return BiquadCoefficients<SampleType> ();

  const WorkingType decay = std::exp ((-half * omega) / poleScale);
  const WorkingType poleTest = four * poleAmplitude * q * q;
  WorkingType a1 = zero;

  if (poleTest > one)
    {
      const WorkingType argument = one - (one / poleTest);
      if (!(argument >= zero))
        return BiquadCoefficients<SampleType> ();
      a1 = -two * decay * std::cos (std::sqrt (argument) * omega);
    }
  else
    {
      const WorkingType argument = (one / poleTest) - one;
      if (!(argument >= zero))
        return BiquadCoefficients<SampleType> ();
      a1 = -two * decay * std::cosh (std::sqrt (argument) * omega);
    }

  const WorkingType a2 = Functions::square (decay);
  const WorkingType A0 = Functions::square (one + a1 + a2);
  const WorkingType A1 = Functions::square (one - a1 + a2);
  const WorkingType A2 = -four * a2;
  const WorkingType responseAtFrequency
      = (phi0 * A0) + (phi1 * A1) + (phi2 * A2);

  if (!std::isfinite (responseAtFrequency)
      || !(responseAtFrequency >= zero) || !(phi1 > zero))
    return BiquadCoefficients<SampleType> ();

  WorkingType b0 = zero;
  WorkingType b1 = zero;
  WorkingType b2 = zero;

  switch (type)
    {
    case MatchedBiquadFilterType::lowPass:
      {
        const WorkingType B1
            = ((responseAtFrequency * q * q) - (A0 * phi0)) / phi1;
        if (!(B1 >= zero))
          return BiquadCoefficients<SampleType> ();

        const WorkingType rootB0 = std::sqrt (A0);
        b0 = half * (rootB0 + std::sqrt (B1));
        b1 = rootB0 - b0;
      }
      break;

    case MatchedBiquadFilterType::highPass:
      b0 = (q * std::sqrt (responseAtFrequency)) / (four * phi1);
      b1 = -two * b0;
      b2 = b0;
      break;

    case MatchedBiquadFilterType::bandPass:
      {
        const WorkingType R2
            = A1 - A0 + (four * (phi0 - phi1) * A2);
        const WorkingType B2
            = (responseAtFrequency - (phi1 * R2))
              / (four * phi1 * phi1);
        const WorkingType B1 = R2 + (four * (phi1 - phi0) * B2);
        if (!(B1 >= zero))
          return BiquadCoefficients<SampleType> ();

        b1 = -half * std::sqrt (B1);
        const WorkingType b0Argument = (b1 * b1) + B2;
        if (!(b0Argument >= zero))
          return BiquadCoefficients<SampleType> ();
        b0 = half * (std::sqrt (b0Argument) - b1);
        b2 = -b0 - b1;
      }
      break;

    case MatchedBiquadFilterType::peak:
      {
        const WorkingType gainSquared = amplitude * amplitude;
        const WorkingType R1 = responseAtFrequency * gainSquared;
        const WorkingType R2
            = (A1 - A0 + (four * (phi0 - phi1) * A2)) * gainSquared;
        const WorkingType B0 = A0;
        const WorkingType B2
            = (R1 - (phi1 * R2) - B0) / (four * phi1 * phi1);
        const WorkingType B1
            = R2 + B0 + (four * (phi1 - phi0) * B2);
        if (!(B0 >= zero) || !(B1 >= zero))
          return BiquadCoefficients<SampleType> ();

        b1 = half * (std::sqrt (B0) - std::sqrt (B1));
        const WorkingType W
            = half * (std::sqrt (B0) + std::sqrt (B1));
        const WorkingType b0Argument = (W * W) + B2;
        if (!(b0Argument >= zero))
          return BiquadCoefficients<SampleType> ();

        b0 = half * (W + std::sqrt (b0Argument));
        if (!(b0 != zero))
          return BiquadCoefficients<SampleType> ();
        b2 = -B2 / (four * b0);
      }
      break;

    default:
      return BiquadCoefficients<SampleType> ();
    }

  return detail::makeMatchedBiquadCoefficients<SampleType> (b0, b1, b2, a1,
                                                            a2);
}

//==============================================================================

/// @} group filters
} // namespace filters

//==============================================================================

/// @} group dsp
} // namespace dsp

//==============================================================================

/// @} group stoneydsp
} // namespace stoneydsp

//==============================================================================

#endif // STONEYDSP_DSP_FILTERS_MATCHED_BIQUAD_COEFFICIENTS_H_INCLUDED
