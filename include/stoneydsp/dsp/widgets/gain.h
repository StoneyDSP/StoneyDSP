#pragma once

#ifndef STONEYDSP_DSP_WIDGETS_GAIN_H_INCLUDED
  #define STONEYDSP_DSP_WIDGETS_GAIN_H_INCLUDED

  #include <stoneydsp/core/core.h>

namespace stoneydsp
{
namespace dsp
{
namespace widgets
{
template <typename TSamples = ::stoneydsp::core::types::double_t,
          typename TGain = ::stoneydsp::core::types::double_t>
STONEYDSP_PACKED_STRUCT_BEGIN class STONEYDSP_ALIGN (alignof (TGain)) Gain
{
public:
  Gain () noexcept = default;

  /**
   * @brief Function to apply gain adjustment to audio samples.
   *
   * @param samples
   * @param numSamples
   * @param gain
   */
  inline void STONEYDSP_API
  applyGain (TSamples *samples, ::stoneydsp::core::types::size_t numSamples,
             TGain gain) const
  {
    for (::stoneydsp::core::types::size_t i = 0U; i < numSamples; i++)
      {
        samples[i] = (TSamples)(samples[i] * gain);
      }
  }

  inline void STONEYDSP_API
  processSample (TSamples *sample)
  {

    const TGain gain = this->getGain ();

    this->applyGain (sample, 1U, gain);
  }

  inline TGain STONEYDSP_API
  getGain () const noexcept
  {
    return this->_gain;
  }

  inline void STONEYDSP_API
  setGain (const TGain &newGain)
  {
    this->_gain = newGain;
  }

private:
  TGain _gain = static_cast<TGain> (1);
  STONEYDSP_DECLARE_NON_COPYABLE (Gain)
  STONEYDSP_DECLARE_NON_MOVEABLE (Gain)
} STONEYDSP_PACKED_STRUCT_END;

} // namespace widgets
} // namespace dsp
} // namespace stoneydsp

template class ::stoneydsp::dsp::widgets::Gain<
    ::stoneydsp::core::types::double_t,
    ::stoneydsp::core::types::double_t>;
template class ::stoneydsp::dsp::widgets::Gain<
    ::stoneydsp::core::types::float_t,
    ::stoneydsp::core::types::double_t>;
template class ::stoneydsp::dsp::widgets::Gain<
    ::stoneydsp::core::types::int8_t,
    ::stoneydsp::core::types::double_t>;
template class ::stoneydsp::dsp::widgets::Gain<
    ::stoneydsp::core::types::int16_t,
    ::stoneydsp::core::types::double_t>;
template class ::stoneydsp::dsp::widgets::Gain<
    ::stoneydsp::core::types::uint8_t,
    ::stoneydsp::core::types::double_t>;
template class ::stoneydsp::dsp::widgets::Gain<
    ::stoneydsp::core::types::uint16_t,
    ::stoneydsp::core::types::double_t>;

template class ::stoneydsp::dsp::widgets::Gain<
    ::stoneydsp::core::types::double_t,
    ::stoneydsp::core::types::float_t>;
template class ::stoneydsp::dsp::widgets::Gain<
    ::stoneydsp::core::types::float_t,
    ::stoneydsp::core::types::float_t>;
template class ::stoneydsp::dsp::widgets::Gain<
    ::stoneydsp::core::types::int8_t,
    ::stoneydsp::core::types::float_t>;
template class ::stoneydsp::dsp::widgets::Gain<
    ::stoneydsp::core::types::int16_t,
    ::stoneydsp::core::types::float_t>;
template class ::stoneydsp::dsp::widgets::Gain<
    ::stoneydsp::core::types::uint8_t,
    ::stoneydsp::core::types::float_t>;
template class ::stoneydsp::dsp::widgets::Gain<
    ::stoneydsp::core::types::uint16_t,
    ::stoneydsp::core::types::float_t>;

  #define STONEYDSP_GAIN_DOUBLE_T                                           \
    ::stoneydsp::dsp::widgets::Gain<                                       \
        ::stoneydsp::core::types::double_t,                                \
        ::stoneydsp::core::types::double_t>
  #define STONEYDSP_GAIN_FLOAT_T                                            \
    ::stoneydsp::dsp::widgets::Gain<                                       \
        ::stoneydsp::core::types::float_t,                                 \
        ::stoneydsp::core::types::float_t>

typedef STONEYDSP_GAIN_DOUBLE_T stoneydsp_gain_double_t;
typedef STONEYDSP_GAIN_FLOAT_T stoneydsp_gain_float_t;



namespace stoneydsp
{
namespace dsp
{
namespace widgets
{
using Gain_double_t = ::stoneydsp_gain_double_t;
using Gain_float_t = ::stoneydsp_gain_float_t;
} // namespace widgets
} // namespace dsp
} // namespace stoneydsp

#endif // STONEYDSP_DSP_WIDGETS_GAIN_H_INCLUDED
