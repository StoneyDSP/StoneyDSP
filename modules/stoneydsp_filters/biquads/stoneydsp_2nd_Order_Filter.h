/*
  ==============================================================================

    Biquads.h
    Created: 16 May 2022 2:54:47am
    Author:  StoneyDSP

  ==============================================================================
*/

namespace stoneydsp
{
namespace filters
{

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
    //==============================================================================
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
    /** Initialises the processor. */
    void prepare(int numChannels, double sampleRate);

    /** Resets the internal state variables of the processor. */
    void reset(SampleType initialValue = {0.0});

    //==============================================================================
    /** Processes one sample at a time on a given channel. */
    SampleType processSample(int channel, SampleType inputValue);

    //==============================================================================
    SampleType geta0() { return a0; }
    SampleType getb0() { return b0; }
    SampleType geta1() { return a1; }
    SampleType getb1() { return b1; }
    SampleType geta2() { return a2; }
    SampleType getb2() { return b2; }

private:
    //==============================================================================
    void coefficients();

    //==============================================================================
    SampleType directFormI(int channel, SampleType inputValue);
    SampleType directFormII(int channel, SampleType inputValue);
    SampleType directFormITransposed(int channel, SampleType inputValue);
    SampleType directFormIITransposed(int channel, SampleType inputValue);

    //==============================================================================
    /** Unit-delay object */
    std::vector<SampleType> Wn_1, Wn_2, Xn_1, Xn_2, Yn_1, Yn_2;
    //std::vector<std::atomic<SampleType>> coeffs[6];

    //==============================================================================
    /** Atomic coefficient gain */
    std::atomic<SampleType> a0, b0, a1, b1, a2, b2, hz, q, g;
    std::atomic<filterType> filtType;
    std::atomic<transformationType> transformType;

    //==============================================================================
    /** Initialised parameter */
    SampleType minFreq, maxFreq, loop, outputSample;

    //==============================================================================
    /** Initialised constant */
    const SampleType zero = (0.0), one = (1.0), two = (2.0), minusOne = (-1.0), minusTwo = (-2.0);
    const SampleType pi = static_cast<SampleType>(3.1415926535897932384626433832795);
    double currentSampleRate = 0.0;
};

} //namespace filters
} //namespace stoneydsp
