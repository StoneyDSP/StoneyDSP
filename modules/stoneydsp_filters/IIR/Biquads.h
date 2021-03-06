/*
  ==============================================================================

    Biquads.h
    Created: 16 May 2022 2:54:47am
    Author:  StoneyDSP

  ==============================================================================
*/

#pragma once

#ifndef BIQUADS_H_INCLUDED
#define BIQUADS_H_INCLUDED

#include <JuceHeader.h>

enum class FilterType
{
    lowPass2 = 0,
    lowPass1 = 1,
    highPass2 = 2,
    highPass1 = 3,
    bandPass = 4,
    bandPassQ = 5,
    lowShelf2 = 6,
    lowShelf1 = 7,
    lowShelf1C = 8,
    highShelf2 = 9,
    highShelf1 = 10,
    highShelf1C = 11,
    peak = 12,
    notch = 13,
    allPass = 14
};

enum class TransformationType
{
    directFormI = 0,
    directFormII = 1,
    directFormItransposed = 2,
    directFormIItransposed = 3
};

/**
    A handy 2-pole Biquad multi-mode equalizer.
*/

template <typename SampleType>
class Biquads
{
public:

    using filterType = FilterType;
    using transformationType = TransformationType;

    //==============================================================================
    /** Constructor. */
    Biquads();

    //==============================================================================
    /** Sets the centre Frequency of the filter. Range = 20..20000 */
    void setFrequency(SampleType newFreq);

    /** Sets the resonance of the filter. Range = 0..1 */
    void setResonance(SampleType newRes);

    /** Sets the centre Frequency gain of the filter. Peak and shelf modes only. */
    void setGain(SampleType newGain);

    /** Sets the type of the filter. See enum for availa ble types. */
    void setFilterType(filterType newFiltType);

    /** Sets the BiLinear Transform for the filter to use. See enum for availa ble types. */
    void setTransformType(transformationType newTransformType);

    //==============================================================================
    /** Sets the length of the ramp used for smoothing parameter changes. */
    void setRampDurationSeconds(double newDurationSeconds) noexcept;

    /** Returns the ramp duration in seconds. */
    double getRampDurationSeconds() const noexcept;

    /** Returns true if the current value is currently being interpolated. */
    bool isSmoothing() const noexcept;

    //==============================================================================
    /** Initialises the processor. */
    void prepare(juce::dsp::ProcessSpec& spec);

    /** Resets the internal state variables of the processor. */
    void reset(SampleType initialValue = {0.0});

    /** Ensure that the state variables are rounded to zero if the state
    variables are denormals. This is only needed if you are doing sample
    by sample processing.*/
    void snapToZero() noexcept;

    //==============================================================================
    /** Processes the input and output samples supplied in the processing context. */
    template <typename ProcessContext>
    void process(const ProcessContext& context) noexcept
    {
        const auto& inputBlock = context.getInputBlock();
        auto& outputBlock = context.getOutputBlock();
        const auto numChannels = outputBlock.getNumChannels();
        const auto numSamples = outputBlock.getNumSamples();
        const auto len = inputBlock.getNumSamples();

        jassert(inputBlock.getNumChannels() == numChannels);
        jassert(inputBlock.getNumSamples() == numSamples);

        if (context.isBypassed)
        {
            frq.skip(static_cast<int> (len));
            res.skip(static_cast<int> (len));
            lev.skip(static_cast<int> (len));

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

    //==============================================================================
    /** Processes one sample at a time on a given channel. */
    SampleType processSample(int channel, SampleType inputValue);

    //==============================================================================
    SampleType& geta0() { return a_0; }
    SampleType& getb0() { return b_0; }
    SampleType& geta1() { return a_1; }
    SampleType& getb1() { return b_1; }
    SampleType& geta2() { return a_2; }
    SampleType& getb2() { return b_2; }

private:
    //==============================================================================
    void calculateCoefficients();
    void updateCoefficients();

    SampleType directFormI(int channel, SampleType inputValue);
    SampleType directFormII(int channel, SampleType inputValue);
    SampleType directFormITransposed(int channel, SampleType inputValue);
    SampleType directFormIITransposed(int channel, SampleType inputValue);

    //==============================================================================
    /** Unit-delay object */
    std::vector<SampleType> Wn_1, Wn_2, Xn_1, Xn_2, Yn_1, Yn_2;

    //==============================================================================
    /** Initialised coefficient gain */
    std::atomic<SampleType> a0, b0, a1, b1, a2, b2;
    std::atomic<SampleType> a_0, b_0, a_1, b_1, a_2, b_2;

    //==============================================================================
    /** Parameter Smoothers. */
    juce::SmoothedValue<SampleType, juce::ValueSmoothingTypes::Multiplicative> frq;
    juce::SmoothedValue<SampleType, juce::ValueSmoothingTypes::Linear> res;
    juce::SmoothedValue<SampleType, juce::ValueSmoothingTypes::Linear> lev;

    //==============================================================================
    /** Initialised parameter */
    SampleType minFreq, maxFreq, loop, outputSample, hz, q, g;
    std::atomic<filterType> filtType;
    std::atomic<transformationType> transformType;

    //==============================================================================
    /** Initialised constant */
    const SampleType zero = (0.0), one = (1.0), two = (2.0), minusOne = (-1.0), minusTwo = (-2.0);
    const SampleType pi = static_cast<SampleType>(3.1415926535897932384626433832795);

    //==============================================================================
    double sampleRate = 44100.0, rampDurationSeconds = 0.00005;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Biquads)
};

#endif //BIQUADS_H_INCLUDED
