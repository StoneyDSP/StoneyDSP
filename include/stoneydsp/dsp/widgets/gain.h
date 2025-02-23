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
template <typename TSamples = ::stoneydsp::double_t,
          typename TGain = ::stoneydsp::double_t>
STONEYDSP_PACKED_STRUCT_BEGIN class STONEYDSP_ALIGN (alignof (TGain)) Gain
{
public:
  /**
   * @brief Function to apply gain adjustment to audio samples.
   *
   * @param samples
   * @param numSamples
   * @param gain
   */
  inline void STONEYDSP_API
  applyGain (TSamples *samples, ::stoneydsp::size_t numSamples,
             TGain gain) const
  {
    for (::stoneydsp::size_t i = 0U; i < numSamples; i++)
      {
        samples[i] = (TSamples)(samples[i] * gain);
      }
  }

  inline void STONEYDSP_API
  processSample (TSamples *sample)
  {

    const auto &gain = this->getGain ();

    this->applyGain (sample, 1U, gain);
  }

  inline const TGain &STONEYDSP_API
  getGain () const noexcept
  {
    return this->_gain;
  }

  inline void STONEYDSP_API
  setGain (const TGain &newGain)
  {
    if (&this->_gain == &newGain)
      return;

    this->_gain = newGain;
  }

private:
  TGain _gain = TGain{};
  STONEYDSP_DECLARE_NON_COPYABLE (Gain)
  STONEYDSP_DECLARE_NON_MOVEABLE (Gain)
} STONEYDSP_PACKED_STRUCT_END;

} // namespace widgets
} // namespace dsp
} // namespace stoneydsp

template class ::stoneydsp::dsp::widgets::Gain< ::stoneydsp::double_t,
                                                ::stoneydsp::double_t>;
template class ::stoneydsp::dsp::widgets::Gain< ::stoneydsp::float_t,
                                                ::stoneydsp::double_t>;
template class ::stoneydsp::dsp::widgets::Gain< ::stoneydsp::int8_t,
                                                ::stoneydsp::double_t>;
template class ::stoneydsp::dsp::widgets::Gain< ::stoneydsp::int16_t,
                                                ::stoneydsp::double_t>;
template class ::stoneydsp::dsp::widgets::Gain< ::stoneydsp::uint8_t,
                                                ::stoneydsp::double_t>;
template class ::stoneydsp::dsp::widgets::Gain< ::stoneydsp::uint16_t,
                                                ::stoneydsp::double_t>;

template class ::stoneydsp::dsp::widgets::Gain< ::stoneydsp::double_t,
                                                ::stoneydsp::float_t>;
template class ::stoneydsp::dsp::widgets::Gain< ::stoneydsp::float_t,
                                                ::stoneydsp::float_t>;
template class ::stoneydsp::dsp::widgets::Gain< ::stoneydsp::int8_t,
                                                ::stoneydsp::float_t>;
template class ::stoneydsp::dsp::widgets::Gain< ::stoneydsp::int16_t,
                                                ::stoneydsp::float_t>;
template class ::stoneydsp::dsp::widgets::Gain< ::stoneydsp::uint8_t,
                                                ::stoneydsp::float_t>;
template class ::stoneydsp::dsp::widgets::Gain< ::stoneydsp::uint16_t,
                                                ::stoneydsp::float_t>;

  #define STONEYDSP_GAIN_DOUBLE_T ::stoneydsp::dsp::widgets::Gain < ::stoneydsp::double_t, ::stoneydsp::double_t >
  #define STONEYDSP_GAIN_FLOAT_T ::stoneydsp::dsp::widgets::Gain < ::stoneydsp::float_t, ::stoneydsp::float_t >

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
