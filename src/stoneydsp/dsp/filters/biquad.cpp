/**
 * @file biquad.cpp
 * @author StoneyDSP (nathanjhood@googlemail.com)
 * @copyright Copyright (c) 2026
 */

//==============================================================================

#include "stoneydsp/dsp/filters/biquad.h"

//==============================================================================

#include <cassert>
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

template <typename SampleType>
Biquad<SampleType>::Biquad () STONEYDSP_NOEXCEPT
    : _coefficients (),
      _filterType (FilterType::peak),
      _transformType (TransformType::directFormIITransposed),
      _sampleRate (static_cast<SampleType> (0)),
      _frequency (static_cast<SampleType> (1000)),
      _resonance (static_cast<SampleType> (0.5)),
      _gainDecibels (static_cast<SampleType> (0)),
      _w1 (static_cast<SampleType> (0)),
      _w2 (static_cast<SampleType> (0)),
      _x1 (static_cast<SampleType> (0)),
      _x2 (static_cast<SampleType> (0)),
      _y1 (static_cast<SampleType> (0)),
      _y2 (static_cast<SampleType> (0)),
      _prepared (false)
{
}

template <typename SampleType>
void
Biquad<SampleType>::prepare (SampleType sampleRate) STONEYDSP_NOEXCEPT
{
  assert (sampleRate > static_cast<SampleType> (0));
  assert (std::isfinite (sampleRate));

  if (!(sampleRate > static_cast<SampleType> (0))
      || !std::isfinite (sampleRate))
    return;

  this->_sampleRate = sampleRate;
  this->_prepared = true;
  this->updateCoefficients ();
  this->reset ();
}

template <typename SampleType>
void
Biquad<SampleType>::reset (SampleType value) STONEYDSP_NOEXCEPT
{
  this->_w1 = value;
  this->_w2 = value;
  this->_x1 = value;
  this->_x2 = value;
  this->_y1 = value;
  this->_y2 = value;
}

template <typename SampleType>
void
Biquad<SampleType>::snapValueToZero (SampleType &value) STONEYDSP_NOEXCEPT
{
  if (std::fpclassify (value) == FP_SUBNORMAL)
    value = static_cast<SampleType> (0);
}

template <typename SampleType>
void
Biquad<SampleType>::snapToZero () STONEYDSP_NOEXCEPT
{
  this->snapValueToZero (this->_w1);
  this->snapValueToZero (this->_w2);
  this->snapValueToZero (this->_x1);
  this->snapValueToZero (this->_x2);
  this->snapValueToZero (this->_y1);
  this->snapValueToZero (this->_y2);
}

template <typename SampleType>
SampleType
Biquad<SampleType>::processSample (SampleType input) STONEYDSP_NOEXCEPT
{
  switch (this->_transformType)
    {
    case TransformType::directFormI:
      return this->processDirectFormI (input);
    case TransformType::directFormII:
      return this->processDirectFormII (input);
    case TransformType::directFormITransposed:
      return this->processDirectFormITransposed (input);
    case TransformType::directFormIITransposed:
      return this->processDirectFormIITransposed (input);
    }

  return this->processDirectFormIITransposed (input);
}

template <typename SampleType>
void
Biquad<SampleType>::processBlock (SampleType *samples,
                                  ::stoneydsp::core::types::size_t numSamples)
    STONEYDSP_NOEXCEPT
{
  assert (samples != 0 || numSamples == 0);
  for (::stoneydsp::core::types::size_t index = 0; index < numSamples; ++index)
    samples[index] = this->processSample (samples[index]);
}

template <typename SampleType>
SampleType
Biquad<SampleType>::processDirectFormI (SampleType input) STONEYDSP_NOEXCEPT
{
  const SampleType output = (input * this->_coefficients.b0)
                            + (this->_x1 * this->_coefficients.b1)
                            + (this->_x2 * this->_coefficients.b2)
                            + (this->_y1 * this->_coefficients.a1)
                            + (this->_y2 * this->_coefficients.a2);

  this->_x2 = this->_x1;
  this->_x1 = input;
  this->_y2 = this->_y1;
  this->_y1 = output;
  return output;
}

template <typename SampleType>
SampleType
Biquad<SampleType>::processDirectFormII (SampleType input) STONEYDSP_NOEXCEPT
{
  const SampleType w = input + (this->_w1 * this->_coefficients.a1)
                       + (this->_w2 * this->_coefficients.a2);
  const SampleType output = (w * this->_coefficients.b0)
                            + (this->_w1 * this->_coefficients.b1)
                            + (this->_w2 * this->_coefficients.b2);

  this->_w2 = this->_w1;
  this->_w1 = w;
  return output;
}

template <typename SampleType>
SampleType
Biquad<SampleType>::processDirectFormITransposed (SampleType input)
    STONEYDSP_NOEXCEPT
{
  const SampleType w = input + this->_w2;
  const SampleType output = (w * this->_coefficients.b0) + this->_x2;

  this->_x2 = (w * this->_coefficients.b1) + this->_x1;
  this->_w2 = (w * this->_coefficients.a1) + this->_w1;
  this->_x1 = w * this->_coefficients.b2;
  this->_w1 = w * this->_coefficients.a2;
  return output;
}

template <typename SampleType>
SampleType
Biquad<SampleType>::processDirectFormIITransposed (SampleType input)
    STONEYDSP_NOEXCEPT
{
  const SampleType output = (input * this->_coefficients.b0) + this->_x2;

  this->_x2 = (input * this->_coefficients.b1) + this->_x1
              + (output * this->_coefficients.a1);
  this->_x1
      = (input * this->_coefficients.b2) + (output * this->_coefficients.a2);
  return output;
}

template <typename SampleType>
void
Biquad<SampleType>::setFrequency (SampleType frequency) STONEYDSP_NOEXCEPT
{
  this->_frequency = frequency;
  this->updateCoefficients ();
}

template <typename SampleType>
void
Biquad<SampleType>::setResonance (SampleType resonance) STONEYDSP_NOEXCEPT
{
  this->_resonance = detail::clampBiquadValue (
      resonance, static_cast<SampleType> (0), static_cast<SampleType> (1));
  this->updateCoefficients ();
}

template <typename SampleType>
void
Biquad<SampleType>::setGainDecibels (SampleType gainDecibels)
    STONEYDSP_NOEXCEPT
{
  this->_gainDecibels = gainDecibels;
  this->updateCoefficients ();
}

template <typename SampleType>
void
Biquad<SampleType>::setFilterType (FilterType filterType) STONEYDSP_NOEXCEPT
{
  if (this->_filterType != filterType)
    {
      this->_filterType = filterType;
      this->updateCoefficients ();
      this->reset ();
    }
}

template <typename SampleType>
void
Biquad<SampleType>::setTransformType (TransformType transformType)
    STONEYDSP_NOEXCEPT
{
  if (this->_transformType != transformType)
    {
      this->_transformType = transformType;
      this->reset ();
    }
}

template <typename SampleType>
void
Biquad<SampleType>::setCoefficients (const Coefficients &coefficients)
    STONEYDSP_NOEXCEPT
{
  this->_coefficients = coefficients;
}

template <typename SampleType>
const typename Biquad<SampleType>::Coefficients &
Biquad<SampleType>::getCoefficients () const STONEYDSP_NOEXCEPT
{
  return this->_coefficients;
}

template <typename SampleType>
SampleType
Biquad<SampleType>::getSampleRate () const STONEYDSP_NOEXCEPT
{
  return this->_sampleRate;
}

template <typename SampleType>
SampleType
Biquad<SampleType>::getFrequency () const STONEYDSP_NOEXCEPT
{
  return this->_frequency;
}

template <typename SampleType>
SampleType
Biquad<SampleType>::getResonance () const STONEYDSP_NOEXCEPT
{
  return this->_resonance;
}

template <typename SampleType>
SampleType
Biquad<SampleType>::getGainDecibels () const STONEYDSP_NOEXCEPT
{
  return this->_gainDecibels;
}

template <typename SampleType>
typename Biquad<SampleType>::FilterType
Biquad<SampleType>::getFilterType () const STONEYDSP_NOEXCEPT
{
  return this->_filterType;
}

template <typename SampleType>
typename Biquad<SampleType>::TransformType
Biquad<SampleType>::getTransformType () const STONEYDSP_NOEXCEPT
{
  return this->_transformType;
}

template <typename SampleType>
bool
Biquad<SampleType>::isPrepared () const STONEYDSP_NOEXCEPT
{
  return this->_prepared;
}

template <typename SampleType>
void
Biquad<SampleType>::updateCoefficients () STONEYDSP_NOEXCEPT
{
  if (!this->_prepared)
    return;

  const SampleType minimumFrequency
      = this->_sampleRate / static_cast<SampleType> (24576.0L);
  const SampleType maximumFrequency
      = this->_sampleRate / static_cast<SampleType> (2.125L);
  this->_frequency = detail::clampBiquadValue (
      this->_frequency, minimumFrequency, maximumFrequency);
  this->_coefficients = calculateBiquadCoefficients (
      this->_filterType, this->_sampleRate, this->_frequency, this->_resonance,
      this->_gainDecibels);
}

//==============================================================================

template class Biquad< ::stoneydsp::core::types::float_t>;
template class Biquad< ::stoneydsp::core::types::double_t>;

//==============================================================================

/// @} group filters
} // namespace filters

//==============================================================================

/// @} group dsp
} // namespace dsp

//==============================================================================

/// @} group stoneydsp
} // namespace stoneydsp
