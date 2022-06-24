/*/*
  ==============================================================================

    Biquad_Calcs.cpp
    Created: 16 May 2022 2:54:47am
    Author:  StoneyDSP

  ==============================================================================
*/

#include "stoneydsp_Biquad_Calcs.h"

namespace stoneydsp
{
namespace filters
{

//==============================================================================
template <typename SampleType>
Biquads<SampleType>::Biquads()
{
    reset();
}

//==============================================================================
template <typename SampleType>
void Biquads<SampleType>::setFrequency(SampleType newFreq)
{
    hz = static_cast<SampleType>(newFreq);
    coefficients();
}

template <typename SampleType>
void Biquads<SampleType>::setResonance(SampleType newRes)
{
    q = static_cast<SampleType>(newRes);
    coefficients();
}

template <typename SampleType>
void Biquads<SampleType>::setGain(SampleType newGain)
{
    g = static_cast<SampleType>(newGain);
    coefficients();
}

template <typename SampleType>
void Biquads<SampleType>::setFilterType(FiltShape newFiltType)
{
    if (filtType != newFiltType)
    {
        filtType = newFiltType;
        reset();
        coefficients();
    }
}

//==============================================================================
template <typename SampleType>
void Biquads<SampleType>::prepare(double sampleRate)
{
    reset();

    minFreq = static_cast <SampleType>(sampleRate) / static_cast <SampleType>(24576.0);
    maxFreq = static_cast <SampleType>(sampleRate) / static_cast <SampleType>(2.125);

    setFrequency(hz);
    setResonance(q);
    setGain(g);

    coefficients();
}

template <typename SampleType>
void Biquads<SampleType>::reset()
{
    setFrequency(hz);
    setResonance(q);
    setGain(g);

    coefficients();
}

template <typename SampleType>
void Biquads<SampleType>::coefficients()
{
    SampleType omega = (hz * ((pi * two) / sampleRate));
    SampleType cos = (std::cos(omega));
    SampleType sin = (std::sin(omega));
    //SampleType tan = (sin / cos);
    SampleType alpha = (sin * (one - q));
    SampleType a = (juce::Decibels::decibelsToGain(static_cast<SampleType>(g * static_cast <SampleType>(0.5))));

    auto sqrtA = (std::sqrt(a) * two) * alpha;

    SampleType b_0 = one;
    SampleType b_1 = zero;
    SampleType b_2 = zero;
    SampleType a_0 = one;
    SampleType a_1 = zero;
    SampleType a_2 = zero;

    switch (filtType)
    {
    case FilterShape::lowPass2:

        b_0 = (one - cos) / two;
        b_1 = one - cos;
        b_2 = (one - cos) / two;
        a_0 = one + alpha;
        a_1 = minusTwo * cos;
        a_2 = one - alpha;

        break;


    case FilterShape::lowPass1:

        b_0 = omega / (one + omega);
        b_1 = omega / (one + omega);
        b_2 = zero;
        a_0 = one;
        a_1 = minusOne * ((one - omega) / (one + omega));
        a_2 = zero;

        break;


    case FilterShape::highPass2:

        b_0 = (one + cos) / two;
        b_1 = minusOne * (one + cos);
        b_2 = (one + cos) / two;
        a_0 = one + alpha;
        a_1 = minusTwo * cos;
        a_2 = one - alpha;

        break;


    case FilterShape::highPass1:

        b_0 = one / (one + omega);
        b_1 = (one / (one + omega)) * minusOne;
        b_2 = zero;
        a_0 = one;
        a_1 = ((one - omega) / (one + omega)) * minusOne;
        a_2 = zero;

        break;


    case FilterShape::bandPass:

        b_0 = sin / two;
        b_1 = zero;
        b_2 = minusOne * (sin / two);
        a_0 = one + alpha;
        a_1 = minusTwo * cos;
        a_2 = one - alpha;

        break;


    case FilterShape::bandPassQ:

        b_0 = alpha;
        b_1 = zero;
        b_2 = minusOne * alpha;
        a_0 = one + alpha;
        a_1 = minusTwo * cos;
        a_2 = one - alpha;

        break;


    case FilterShape::lowShelf2:

        b_0 = (((a + one) - ((a - one) * cos)) + sqrtA) * a;
        b_1 = (((a - one) - ((a + one) * cos)) * two) * a;
        b_2 = (((a + one) - ((a - one) * cos)) - sqrtA) * a;
        a_0 = ((a + one) + ((a - one) * cos)) + sqrtA;
        a_1 = ((a - one) + ((a + one) * cos)) * minusTwo;
        a_2 = ((a + one) + ((a - one) * cos)) - sqrtA;

        break;


    case FilterShape::lowShelf1:

        b_0 = one + ((omega / (one + omega)) * (minusOne + (a * a)));
        b_1 = (((omega / (one + omega)) * (minusOne + (a * a))) - ((one - omega) / (one + omega)));
        b_2 = zero;
        a_0 = one;
        a_1 = minusOne * ((one - omega) / (one + omega));
        a_2 = zero;

        break;


    case FilterShape::lowShelf1C:

        b_0 = one + ((omega / a) / (one + (omega / a)) * (minusOne + (a * a)));
        b_1 = ((((omega / a) / (one + (omega / a))) * (minusOne + (a * a))) - ((one - (omega / a)) / (one + (omega / a))));
        b_2 = zero;
        a_0 = one;
        a_1 = minusOne * ((one - (omega / a)) / (one + (omega / a)));
        a_2 = zero;

        break;


    case FilterShape::highShelf2:

        b_0 = (((a + one) + ((a - one) * cos)) + sqrtA) * a;
        b_1 = (((a - one) + ((a + one) * cos)) * minusTwo) * a;
        b_2 = (((a + one) + ((a - one) * cos)) - sqrtA) * a;
        a_0 = ((a + one) - ((a - one) * cos)) + sqrtA;
        a_1 = ((a - one) - ((a + one) * cos)) * two;
        a_2 = ((a + one) - ((a - one) * cos)) - sqrtA;

        break;


    case FilterShape::highShelf1:

        b_0 = one + ((minusOne + (a * a)) / (one + omega));
        b_1 = minusOne * (((one - omega) / (one + omega)) + ((minusOne + (a * a)) / (one + omega)));
        b_2 = zero;
        a_0 = one;
        a_1 = minusOne * ((one - omega) / (one + omega));
        a_2 = zero;

        break;


    case FilterShape::highShelf1C:

        b_0 = one + ((minusOne + (a * a)) / (one + (omega * a)));
        b_1 = minusOne * (((one - (omega * a)) / (one + (omega * a))) + ((minusOne + (a * a)) / (one + (omega * a))));
        b_2 = zero;
        a_0 = one;
        a_1 = minusOne * ((one - (omega * a)) / (one + (omega * a)));
        a_2 = zero;

        break;


    case FilterShape::peak:

        b_0 = one + (alpha * a);
        b_1 = minusTwo * cos;
        b_2 = one - (alpha * a);
        a_0 = one + (alpha / a);
        a_1 = minusTwo * cos;
        a_2 = one - (alpha / a);

        break;


    case FilterShape::notch:

        b_0 = one;
        b_1 = minusTwo * cos;
        b_2 = one;
        a_0 = one + alpha;
        a_1 = minusTwo * cos;
        a_2 = one - alpha;

        break;


    case FilterShape::allPass:

        b_0 = one - alpha;
        b_1 = minusTwo * cos;
        b_2 = one + alpha;
        a_0 = one + alpha;
        a_1 = minusTwo * cos;
        a_2 = one - alpha;

        break;


    default:

        b_0 = one;
        b_1 = zero;
        b_2 = zero;
        a_0 = one;
        a_1 = zero;
        a_2 = zero;

        break;
    }

    a0 = (one / a_0);
    b0 = (b_0 * a0);
    b1 = (b_1 * a0);
    b2 = (b_2 * a0);
    a1 = ((a_1 * a0) * minusOne);
    a2 = ((a_2 * a0) * minusOne);
}

//==============================================================================
template class Biquads<float>;
template class Biquads<double>;

} //namespace stoneydsp
} //
