/*
  ==============================================================================

    Biquad_Calcs.h
    Created: 16 May 2022 2:54:47am
    Author:  StoneyDSP

  ==============================================================================
*/

#pragma once

#ifndef BIQUAD_CALCS_H_INCLUDED
#define BIQUAD_CALCS_H_INCLUDED

#include <cmath>

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

/**
    A handy 2-pole Biquad multi-mode equalizer.
*/

template <typename SampleType>
class Biquads
{
public:

    using filterType = FilterType;

    //==============================================================================
    /** Constructor. */
    Biquads() = default;

    //==============================================================================
    /** Sets the centre Frequency of the filter. Range = 20..20000 */
    void setFrequency(SampleType newFreq);

    /** Sets the resonance of the filter. Range = 0..1 */
    void setResonance(SampleType newRes);

    /** Sets the centre Frequency gain of the filter. Peak and shelf modes only. */
    void setGain(SampleType newGain);

    /** Sets the type of the filter. See enum for availa ble types. */
    void setFilterType(filterType newFiltType);

    //==============================================================================
    /** Initialises the processor. */
    void prepare(int numChannels, double sampleRate);

    /** Resets the internal state variables of the processor. */
    void reset(SampleType initialValue);

private:
    //==============================================================================
    void coefficients();

    //==============================================================================
    SampleType& getb0() { return b0; }
    SampleType& getb1() { return b1; }
    SampleType& getb2() { return b2; }
    SampleType& geta0() { return a0; }
    SampleType& geta1() { return a1; }
    SampleType& geta2() { return a2; }

    //==============================================================================
    /** Initialise the coefficient gains. */
    SampleType b0 = 1.0;
    SampleType b1 = 0.0;
    SampleType b2 = 0.0;
    SampleType a0 = 1.0;
    SampleType a1 = 0.0;
    SampleType a2 = 0.0;

    //==============================================================================
    /** Initialise the parameters. */
    SampleType minFreq = 20.0, maxFreq = 20000.0, hz = 1000.0, q = 0.5, g = 0.0;
    filterType filtType = filterType::lowPass2;

    //==============================================================================
    /** Initialise constants. */
    const SampleType zero = (0.0), one = (1.0), two = (2.0), minusOne = (-1.0), minusTwo = (-2.0);
    const SampleType pi = (3.1415926535897932384626433832795);
    double sampleRate = 44100.0;

    //==============================================================================
};

#endif //BIQUAD_CALCS_H_INCLUDED