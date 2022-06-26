/*/*
  ==============================================================================

    Biquad_Calcs.cpp
    Created: 16 May 2022 2:54:47am
    Author:  StoneyDSP

  ==============================================================================
*/

namespace stoneydsp
{
namespace filters
{

//==============================================================================
template <typename SampleType>
BiquadCalcs<SampleType>::BiquadCalcs()
{
    reset();
}

//==============================================================================
template <typename SampleType>
void BiquadCalcs<SampleType>::setFrequency(SampleType newFreq)
{
    hz = newFreq;
    coefficients();
}

template <typename SampleType>
void BiquadCalcs<SampleType>::setResonance(SampleType newRes)
{
    q = newRes;
    coefficients();
}

template <typename SampleType>
void BiquadCalcs<SampleType>::setGain(SampleType newGain)
{
    g = newGain;
    coefficients();
}

template <typename SampleType>
void BiquadCalcs<SampleType>::setFilterType(FiltShape newFiltType)
{
    if (filtType != newFiltType)
    {
        filtType = newFiltType;
        reset();
    }
}

//==============================================================================
template <typename SampleType>
void BiquadCalcs<SampleType>::prepare(double sampleRate)
{
    currentSampleRate = sampleRate;

    minFreq = static_cast<SampleType>(currentSampleRate / 24576.0);
    maxFreq = static_cast<SampleType>(currentSampleRate / 2.125);

    reset();
}

template <typename SampleType>
void BiquadCalcs<SampleType>::reset()
{
    setFrequency(hz);
    setResonance(q);
    setGain(g);

    coefficients();
}

template <typename SampleType>
void BiquadCalcs<SampleType>::coefficients()
{
    auto omega = (hz * ((pi * two) / static_cast<SampleType>(currentSampleRate)));
    auto cos = (std::cos(omega));
    auto sin = (std::sin(omega));
    //SampleType tan = (sin / cos);
    auto alpha = (sin * (one - q));
    //auto a = (juce::Decibels::decibelsToGain<SampleType>dBtoGain(static_cast<SampleType>(g * static_cast <SampleType>(0.5))));
    auto a = std::pow(SampleType (10), (g * SampleType (0.5))) * SampleType (0.5);

    auto sqrtA = (std::sqrt(a) * two) * alpha;

    switch (filtType)
    {
    case FiltShape::lowPass2:

        b0 = (one - cos) / two;
        b1 = one - cos;
        b2 = (one - cos) / two;
        a0 = one + alpha;
        a1 = minusTwo * cos;
        a2 = one - alpha;

        break;


    case FiltShape::lowPass1:

        b0 = omega / (one + omega);
        b1 = omega / (one + omega);
        b2 = zero;
        a0 = one;
        a1 = minusOne * ((one - omega) / (one + omega));
        a2 = zero;

        break;


    case FiltShape::highPass2:

        b0 = (one + cos) / two;
        b1 = minusOne * (one + cos);
        b2 = (one + cos) / two;
        a0 = one + alpha;
        a1 = minusTwo * cos;
        a2 = one - alpha;

        break;


    case FiltShape::highPass1:

        b0 = one / (one + omega);
        b1 = (one / (one + omega)) * minusOne;
        b2 = zero;
        a0 = one;
        a1 = ((one - omega) / (one + omega)) * minusOne;
        a2 = zero;

        break;


    case FiltShape::bandPass:

        b0 = sin / two;
        b1 = zero;
        b2 = minusOne * (sin / two);
        a0 = one + alpha;
        a1 = minusTwo * cos;
        a2 = one - alpha;

        break;


    case FiltShape::bandPassQ:

        b0 = alpha;
        b1 = zero;
        b2 = minusOne * alpha;
        a0 = one + alpha;
        a1 = minusTwo * cos;
        a2 = one - alpha;

        break;


    case FiltShape::lowShelf2:

        b0 = (((a + one) - ((a - one) * cos)) + sqrtA) * a;
        b1 = (((a - one) - ((a + one) * cos)) * two) * a;
        b2 = (((a + one) - ((a - one) * cos)) - sqrtA) * a;
        a0 = ((a + one) + ((a - one) * cos)) + sqrtA;
        a1 = ((a - one) + ((a + one) * cos)) * minusTwo;
        a2 = ((a + one) + ((a - one) * cos)) - sqrtA;

        break;


    case FiltShape::lowShelf1:

        b0 = one + ((omega / (one + omega)) * (minusOne + (a * a)));
        b1 = (((omega / (one + omega)) * (minusOne + (a * a))) - ((one - omega) / (one + omega)));
        b2 = zero;
        a0 = one;
        a1 = minusOne * ((one - omega) / (one + omega));
        a2 = zero;

        break;


    case FiltShape::lowShelf1C:

        b0 = one + ((omega / a) / (one + (omega / a)) * (minusOne + (a * a)));
        b1 = ((((omega / a) / (one + (omega / a))) * (minusOne + (a * a))) - ((one - (omega / a)) / (one + (omega / a))));
        b2 = zero;
        a0 = one;
        a1 = minusOne * ((one - (omega / a)) / (one + (omega / a)));
        a2 = zero;

        break;


    case FiltShape::highShelf2:

        b0 = (((a + one) + ((a - one) * cos)) + sqrtA) * a;
        b1 = (((a - one) + ((a + one) * cos)) * minusTwo) * a;
        b2 = (((a + one) + ((a - one) * cos)) - sqrtA) * a;
        a0 = ((a + one) - ((a - one) * cos)) + sqrtA;
        a1 = ((a - one) - ((a + one) * cos)) * two;
        a2 = ((a + one) - ((a - one) * cos)) - sqrtA;

        break;


    case FiltShape::highShelf1:

        b0 = one + ((minusOne + (a * a)) / (one + omega));
        b1 = minusOne * (((one - omega) / (one + omega)) + ((minusOne + (a * a)) / (one + omega)));
        b2 = zero;
        a0 = one;
        a1 = minusOne * ((one - omega) / (one + omega));
        a2 = zero;

        break;


    case FiltShape::highShelf1C:

        b0 = one + ((minusOne + (a * a)) / (one + (omega * a)));
        b1 = minusOne * (((one - (omega * a)) / (one + (omega * a))) + ((minusOne + (a * a)) / (one + (omega * a))));
        b2 = zero;
        a0 = one;
        a1 = minusOne * ((one - (omega * a)) / (one + (omega * a)));
        a2 = zero;

        break;


    case FiltShape::peak:

        b0 = one + (alpha * a);
        b1 = minusTwo * cos;
        b2 = one - (alpha * a);
        a0 = one + (alpha / a);
        a1 = minusTwo * cos;
        a2 = one - (alpha / a);

        break;


    case FiltShape::notch:

        b0 = one;
        b1 = minusTwo * cos;
        b2 = one;
        a0 = one + alpha;
        a1 = minusTwo * cos;
        a2 = one - alpha;

        break;


    case FiltShape::allPass:

        b0 = one - alpha;
        b1 = minusTwo * cos;
        b2 = one + alpha;
        a0 = one + alpha;
        a1 = minusTwo * cos;
        a2 = one - alpha;

        break;


    default:

        b0 = one;
        b1 = zero;
        b2 = zero;
        a0 = one;
        a1 = zero;
        a2 = zero;

        break;
    }
}

//==============================================================================
template class BiquadCalcs<float>;
template class BiquadCalcs<double>;

} //namespace stoneydsp
} //
