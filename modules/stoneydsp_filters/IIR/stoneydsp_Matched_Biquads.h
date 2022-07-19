/*
  ==============================================================================

    MatchedBiquads.h
    Author:  Martin Vicanek 2016
    https://www.vicanek.de/articles/BiquadFits.pdf
    C++ by StoneyDSP
    Created: 14 Jul 2022 8:13:32pm

  ==============================================================================
*/

namespace stoneydsp
{
namespace filters
{

enum struct FilterType
{
    MPeakEQ,
    MHighPass,
    MLowPass,
    MBandPass,
    PeakEQ, 
    HighPass, 
    LowPass,
    BandPass
};

enum struct TransformationType
{
    directFormI = 0,
    directFormII = 1,
    directFormItransposed = 2,
    directFormIItransposed = 3
};

template <typename SampleType>
class MatchedBiquad
{
public:
    MatchedBiquad();

    //==========================================================================
    /** Sets the centre Frequency of the filter. Range = 20..20000 */
    void setFrequency(SampleType newFreq);

    /** Sets the resonance of the filter. Range = 0..1 */
    void setResonance(SampleType newRes);

    /** Sets the centre Frequency gain of the filter. Peak and shelf modes only. */
    void setGain(SampleType newGain);

    /** Sets the BiLinear Transform for the filter to use. See enum for available types. */
    void setFilterType(FilterType newType);

    /** Sets the BiLinear Transform for the filter to use. See enum for available types. */
    void setTransformType(TransformationType newTransformType);

    //==========================================================================
    /** Initialises the processor. */
    void prepare(juce::dsp::ProcessSpec spec);

    /** Resets the internal state variables of the processor. */
    void reset(SampleType initialValue = { 0.0 });

    /** Ensure that the state variables are rounded to zero if the state
    variables are denormals. This is only needed if you are doing sample
    by sample processing.*/
    void snapToZero() noexcept;

    //==========================================================================
    /** Processes the input and output samples supplied in the processing context. */
    template <typename ProcessContext>
    void process(const ProcessContext& context) noexcept
    {
        const auto& inputBlock = context.getInputBlock();
        auto& outputBlock = context.getOutputBlock();
        const auto numChannels = outputBlock.getNumChannels();
        const auto numSamples = outputBlock.getNumSamples();

        jassert(inputBlock.getNumChannels() == numChannels);
        jassert(inputBlock.getNumSamples() == numSamples);

        if (context.isBypassed)
        {
            outputBlock.copyFrom(inputBlock);
            return;
        }

        for (size_t channel = 0; channel < numChannels; ++channel)
        {
            auto* inputSamples = inputBlock.getChannelPointer(channel);
            auto* outputSamples = outputBlock.getChannelPointer(channel);

            for (size_t i = 0; i < numSamples; ++i)
                outputSamples[i] = processSample((int)channel, inputSamples[i]);
        }

#if JUCE_DSP_ENABLE_SNAP_TO_ZERO
        snapToZero();
#endif
    }

private:
    //==========================================================================
    void coeffs();

    //==========================================================================
    /** Processes one sample at a time on a given channel. */
    SampleType processSample(int channel, SampleType inputSample);

    SampleType directFormI(int channel, SampleType inputValue);
    SampleType directFormII(int channel, SampleType inputValue);
    SampleType directFormITransposed(int channel, SampleType inputValue);
    SampleType directFormIITransposed(int channel, SampleType inputValue);

    //==========================================================================
    /** Coefficient gain */
    Coefficient<SampleType> a[3], b[3];

    /** Coefficient calculation */
    Coefficient<SampleType> a_[3], b_[3];

    std::vector<SampleType> Wn_1, Wn_2, Xn_1, Xn_2, Yn_1, Yn_2;

    SampleType f, g, q, loop, outputSample, AA, f0, alfa, w, AA0, AA1, AA2, phi1, phi0, phi2, r1, r2, BB0, BB1, BB2, _test, minFreq, maxFreq;
    FilterType type;
    TransformationType transformType;

    //==========================================================================
    /** Initialised constant */
    const SampleType zero = 0.0, one = 1.0, two = 2.0, minusOne = -1.0, minusTwo = -2.0, zeroFive = 0.5, four = 4.0, ten = 10.0, twenty = 20.0;
    const SampleType pi = juce::MathConstants<SampleType>::pi;
    const SampleType root2 = juce::MathConstants<SampleType>::sqrt2;
    double sampleRate = 44100.0;
};

} //namespace filters
} //namespace stoneydsp
