/**
 * @file biquad.h
 * @author StoneyDSP (nathanjhood@googlemail.com)
 * @brief
 * @version @STONEYDSP_CORE_VERSION@
 * @date 2025-01-27
 *
 * @copyright Copyright (c) 2025
 *
 */

#pragma once

#ifndef STONEYDSP_DSP_FILTERS_BIQUAD_H_INCLUDED
  #define STONEYDSP_DSP_FILTERS_BIQUAD_H_INCLUDED

//==============================================================================

  #include "stoneydsp/dsp/filters/biquad_coefficients.h"

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

/** Available direct-form realisations of a biquad transfer function. */
enum class BiquadTransformType
{
  directFormI = 0,
  directFormII,
  directFormITransposed,
  directFormIITransposed
};

//==============================================================================

/**
 * A single-channel, allocation-free realisation of the StoneyDSP Biquads
 * filter design.
 *
 * The processor owns its coefficients and delay state. Instantiate one
 * processor per audio channel. Parameter updates are expected to be made by
 * the processing thread; the class does not pretend that independently atomic
 * coefficient values form one coherent realtime-safe update.
 *
 * The library provides compiled float and double specialisations, exposed by
 * the Biquad_float_t and Biquad_double_t aliases below.
 */
template <typename SampleType = ::stoneydsp::core::types::double_t>
class Biquad
{

  //============================================================================

public:
  typedef BiquadCoefficients<SampleType> Coefficients;
  typedef BiquadFilterType FilterType;
  typedef BiquadTransformType TransformType;

  STONEYDSP_API Biquad () STONEYDSP_NOEXCEPT;

  void STONEYDSP_API prepare (SampleType sampleRate) STONEYDSP_NOEXCEPT;

  void STONEYDSP_API reset (SampleType value
                            = static_cast<SampleType> (0)) STONEYDSP_NOEXCEPT;

  void STONEYDSP_API snapToZero () STONEYDSP_NOEXCEPT;

  SampleType STONEYDSP_API processSample (SampleType input) STONEYDSP_NOEXCEPT;

  void STONEYDSP_API processBlock (SampleType *samples,
                                   ::stoneydsp::core::types::size_t numSamples)
      STONEYDSP_NOEXCEPT;

  void STONEYDSP_API setFrequency (SampleType frequency) STONEYDSP_NOEXCEPT;

  void STONEYDSP_API setResonance (SampleType resonance) STONEYDSP_NOEXCEPT;

  void STONEYDSP_API setGainDecibels (SampleType gainDecibels)
      STONEYDSP_NOEXCEPT;

  void STONEYDSP_API setFilterType (FilterType filterType) STONEYDSP_NOEXCEPT;

  void STONEYDSP_API setTransformType (TransformType transformType)
      STONEYDSP_NOEXCEPT;

  void STONEYDSP_API setCoefficients (const Coefficients &coefficients)
      STONEYDSP_NOEXCEPT;

  STONEYDSP_API const Coefficients &
  getCoefficients () const STONEYDSP_NOEXCEPT;

  SampleType STONEYDSP_API getSampleRate () const STONEYDSP_NOEXCEPT;

  SampleType STONEYDSP_API getFrequency () const STONEYDSP_NOEXCEPT;

  SampleType STONEYDSP_API getResonance () const STONEYDSP_NOEXCEPT;

  SampleType STONEYDSP_API getGainDecibels () const STONEYDSP_NOEXCEPT;

  FilterType STONEYDSP_API getFilterType () const STONEYDSP_NOEXCEPT;

  TransformType STONEYDSP_API getTransformType () const STONEYDSP_NOEXCEPT;

  bool STONEYDSP_API isPrepared () const STONEYDSP_NOEXCEPT;

  //============================================================================

private:
  //============================================================================

  SampleType processDirectFormI (SampleType input) STONEYDSP_NOEXCEPT;
  SampleType processDirectFormII (SampleType input) STONEYDSP_NOEXCEPT;
  SampleType
  processDirectFormITransposed (SampleType input) STONEYDSP_NOEXCEPT;
  SampleType
  processDirectFormIITransposed (SampleType input) STONEYDSP_NOEXCEPT;

  static void snapValueToZero (SampleType &value) STONEYDSP_NOEXCEPT;
  void updateCoefficients () STONEYDSP_NOEXCEPT;

  Coefficients _coefficients;
  FilterType _filterType;
  TransformType _transformType;
  SampleType _sampleRate;
  SampleType _frequency;
  SampleType _resonance;
  SampleType _gainDecibels;
  SampleType _w1;
  SampleType _w2;
  SampleType _x1;
  SampleType _x2;
  SampleType _y1;
  SampleType _y2;
  bool _prepared;

  //============================================================================

  STONEYDSP_DECLARE_NON_COPYABLE (Biquad)
  STONEYDSP_DECLARE_NON_MOVEABLE (Biquad)
};

//==============================================================================

using Biquad_float_t = Biquad< ::stoneydsp::core::types::float_t>;
using Biquad_double_t = Biquad< ::stoneydsp::core::types::double_t>;

//==============================================================================

/// @} group filters
} // namespace filters

//==============================================================================

/// @} group dsp
} // namespace dsp

//==============================================================================

/// @} group stoneydsp
} //  namespace stoneydsp

//==============================================================================

#endif // STONEYDSP_DSP_FILTERS_BIQUAD_H_INCLUDED
