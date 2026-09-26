/**
 * @file biquad_coefficients.h
 * @author StoneyDSP (nathanjhood@googlemail.com)
 * @brief
 * @version @STONEYDSP_CORE_VERSION@
 * @date 2025-01-27
 *
 * @copyright Copyright (c) 2025
 *
 */

#pragma once

#ifndef STONEYDSP_DSP_FILTERS_BIQUAD_COEFFICIENTS_H_INCLUDED
  #define STONEYDSP_DSP_FILTERS_BIQUAD_COEFFICIENTS_H_INCLUDED

//==============================================================================

  #include <stoneydsp/core/core.h>

//==============================================================================

  #include <cmath>
  #include <type_traits>

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

/** Filter responses implemented by the original StoneyDSP Biquads design. */
enum class BiquadFilterType
{
  lowPass2 = 0,
  lowPass1,
  highPass2,
  highPass1,
  bandPass,
  bandPassQ,
  lowShelf2,
  lowShelf1,
  lowShelf1C,
  highShelf2,
  highShelf1,
  highShelf1C,
  peak,
  notch,
  allPass
};

//==============================================================================

/**
 * Normalised coefficients for a first- or second-order IIR section.
 *
 * The denominator is normalised to a0 = 1. The feedback coefficients stored
 * here already include the sign used by the processing recurrences:
 *
 *     y[n] = b0*x[n] + b1*x[n-1] + b2*x[n-2]
 *                       + a1*y[n-1] + a2*y[n-2]
 */
template <typename SampleType = ::stoneydsp::core::types::double_t>
struct BiquadCoefficients
{
  static_assert (std::is_floating_point<SampleType>::value,
                 "Biquad coefficients require a floating-point sample type");

  SampleType b0;
  SampleType b1;
  SampleType b2;
  SampleType a1;
  SampleType a2;

  STONEYDSP_CONSTEXPR
  BiquadCoefficients () STONEYDSP_NOEXCEPT : b0 (static_cast<SampleType> (1)),
                                             b1 (static_cast<SampleType> (0)),
                                             b2 (static_cast<SampleType> (0)),
                                             a1 (static_cast<SampleType> (0)),
                                             a2 (static_cast<SampleType> (0))
  {
  }

  STONEYDSP_CONSTEXPR
  BiquadCoefficients (SampleType newB0, SampleType newB1, SampleType newB2,
                      SampleType newA1, SampleType newA2) STONEYDSP_NOEXCEPT
      : b0 (newB0),
        b1 (newB1),
        b2 (newB2),
        a1 (newA1),
        a2 (newA2)
  {
  }
};

//==============================================================================

namespace detail
{
/** @addtogroup detail
 * @{
 */

//==============================================================================

template <typename ValueType>
STONEYDSP_INLINE ValueType
clampBiquadValue (ValueType value, ValueType minimum,
                  ValueType maximum) STONEYDSP_NOEXCEPT
{
  return value < minimum ? minimum : (value > maximum ? maximum : value);
}

/// @} group detail
} // namespace detail

//==============================================================================

/**
 * Calculates the coefficient set used by the Biquads plugin.
 *
 * `resonance` retains the authored 0..1 control law: alpha is
 * `sin(omega) * (1 - resonance)`. `gainDecibels` retains the original gain
 * mapping. Frequencies are limited to the original operating interval of
 * `sampleRate / 24576` through `sampleRate / 2.125`.
 */
template <typename SampleType>
STONEYDSP_INLINE BiquadCoefficients<SampleType>
calculateBiquadCoefficients (BiquadFilterType type, SampleType sampleRate,
                             SampleType frequency, SampleType resonance,
                             SampleType gainDecibels) STONEYDSP_NOEXCEPT
{
  typedef ::stoneydsp::core::maths::Constants<SampleType> Constants;

  const SampleType zero = static_cast<SampleType> (0);
  const SampleType one = static_cast<SampleType> (1);
  const SampleType two = static_cast<SampleType> (2);

  if (!(sampleRate > zero) || !std::isfinite (sampleRate))
    return BiquadCoefficients<SampleType> ();

  const SampleType minimumFrequency
      = sampleRate / static_cast<SampleType> (24576.0L);
  const SampleType maximumFrequency
      = sampleRate / static_cast<SampleType> (2.125L);
  const SampleType limitedFrequency = detail::clampBiquadValue (
      frequency, minimumFrequency, maximumFrequency);
  const SampleType limitedResonance
      = detail::clampBiquadValue (resonance, zero, one);
  const SampleType omega
      = limitedFrequency * (Constants::twoPi / sampleRate);
  const SampleType cosine = std::cos (omega);
  const SampleType sine = std::sin (omega);
  const SampleType alpha = sine * (one - limitedResonance);
  const SampleType amplitude
      = ::stoneydsp::core::maths::decibelsToGain (gainDecibels);
  const SampleType shelfAlpha = (std::sqrt (amplitude) * two) * alpha;

  SampleType b0 = one;
  SampleType b1 = zero;
  SampleType b2 = zero;
  SampleType a0 = one;
  SampleType a1 = zero;
  SampleType a2 = zero;

  switch (type)
    {
    case BiquadFilterType::lowPass2:
      b0 = (one - cosine) / two;
      b1 = one - cosine;
      b2 = (one - cosine) / two;
      a0 = one + alpha;
      a1 = -two * cosine;
      a2 = one - alpha;
      break;

    case BiquadFilterType::lowPass1:
      b0 = omega / (one + omega);
      b1 = b0;
      b2 = zero;
      a0 = one;
      a1 = -(one - omega) / (one + omega);
      a2 = zero;
      break;

    case BiquadFilterType::highPass2:
      b0 = (one + cosine) / two;
      b1 = -(one + cosine);
      b2 = (one + cosine) / two;
      a0 = one + alpha;
      a1 = -two * cosine;
      a2 = one - alpha;
      break;

    case BiquadFilterType::highPass1:
      b0 = one / (one + omega);
      b1 = -b0;
      b2 = zero;
      a0 = one;
      a1 = -(one - omega) / (one + omega);
      a2 = zero;
      break;

    case BiquadFilterType::bandPass:
      b0 = sine / two;
      b1 = zero;
      b2 = -sine / two;
      a0 = one + alpha;
      a1 = -two * cosine;
      a2 = one - alpha;
      break;

    case BiquadFilterType::bandPassQ:
      b0 = alpha;
      b1 = zero;
      b2 = -alpha;
      a0 = one + alpha;
      a1 = -two * cosine;
      a2 = one - alpha;
      break;

    case BiquadFilterType::lowShelf2:
      b0 = (((amplitude + one) - ((amplitude - one) * cosine) + shelfAlpha)
            * amplitude);
      b1 = (((amplitude - one) - ((amplitude + one) * cosine)) * two
            * amplitude);
      b2 = (((amplitude + one) - ((amplitude - one) * cosine) - shelfAlpha)
            * amplitude);
      a0 = (amplitude + one) + ((amplitude - one) * cosine) + shelfAlpha;
      a1 = -two * ((amplitude - one) + ((amplitude + one) * cosine));
      a2 = (amplitude + one) + ((amplitude - one) * cosine) - shelfAlpha;
      break;

    case BiquadFilterType::lowShelf1:
      b0 = one + ((omega / (one + omega)) * (-one + (amplitude * amplitude)));
      b1 = ((omega / (one + omega)) * (-one + (amplitude * amplitude)))
           - ((one - omega) / (one + omega));
      b2 = zero;
      a0 = one;
      a1 = -(one - omega) / (one + omega);
      a2 = zero;
      break;

    case BiquadFilterType::lowShelf1C:
      {
        const SampleType warpedOmega = omega / amplitude;
        b0 = one
             + ((warpedOmega / (one + warpedOmega))
                * (-one + (amplitude * amplitude)));
        b1 = ((warpedOmega / (one + warpedOmega))
              * (-one + (amplitude * amplitude)))
             - ((one - warpedOmega) / (one + warpedOmega));
        b2 = zero;
        a0 = one;
        a1 = -(one - warpedOmega) / (one + warpedOmega);
        a2 = zero;
      }
      break;

    case BiquadFilterType::highShelf2:
      b0 = (((amplitude + one) + ((amplitude - one) * cosine) + shelfAlpha)
            * amplitude);
      b1 = (-two * ((amplitude - one) + ((amplitude + one) * cosine))
            * amplitude);
      b2 = (((amplitude + one) + ((amplitude - one) * cosine) - shelfAlpha)
            * amplitude);
      a0 = (amplitude + one) - ((amplitude - one) * cosine) + shelfAlpha;
      a1 = two * ((amplitude - one) - ((amplitude + one) * cosine));
      a2 = (amplitude + one) - ((amplitude - one) * cosine) - shelfAlpha;
      break;

    case BiquadFilterType::highShelf1:
      b0 = one + ((-one + (amplitude * amplitude)) / (one + omega));
      b1 = -(((one - omega) / (one + omega))
             + ((-one + (amplitude * amplitude)) / (one + omega)));
      b2 = zero;
      a0 = one;
      a1 = -(one - omega) / (one + omega);
      a2 = zero;
      break;

    case BiquadFilterType::highShelf1C:
      {
        const SampleType warpedOmega = omega * amplitude;
        b0 = one + ((-one + (amplitude * amplitude)) / (one + warpedOmega));
        b1 = -(((one - warpedOmega) / (one + warpedOmega))
               + ((-one + (amplitude * amplitude)) / (one + warpedOmega)));
        b2 = zero;
        a0 = one;
        a1 = -(one - warpedOmega) / (one + warpedOmega);
        a2 = zero;
      }
      break;

    case BiquadFilterType::peak:
      b0 = one + (alpha * amplitude);
      b1 = -two * cosine;
      b2 = one - (alpha * amplitude);
      a0 = one + (alpha / amplitude);
      a1 = -two * cosine;
      a2 = one - (alpha / amplitude);
      break;

    case BiquadFilterType::notch:
      b0 = one;
      b1 = -two * cosine;
      b2 = one;
      a0 = one + alpha;
      a1 = -two * cosine;
      a2 = one - alpha;
      break;

    case BiquadFilterType::allPass:
      b0 = one - alpha;
      b1 = -two * cosine;
      b2 = one + alpha;
      a0 = one + alpha;
      a1 = -two * cosine;
      a2 = one - alpha;
      break;
    }

  const SampleType inverseA0 = one / a0;
  return BiquadCoefficients<SampleType> (b0 * inverseA0, b1 * inverseA0,
                                         b2 * inverseA0, -a1 * inverseA0,
                                         -a2 * inverseA0);
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

#endif // STONEYDSP_DSP_FILTERS_BIQUAD_COEFFICIENTS_H_INCLUDED
