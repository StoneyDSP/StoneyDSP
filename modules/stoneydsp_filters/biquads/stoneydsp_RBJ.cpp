 /*
 /*==============================================================================

    Biquads.cpp
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
Biquads<SampleType>::Biquads() 
    : 
    a0(1.0), a1(0.0), a2(0.0), b0(1.0), b1(0.0), b2(0.0),
    hz(1000.0), q(0.5), g(0.0),
    filtType(filterType::lowPass2),
    transformType(transformationType::directFormIItransposed)
{
    reset();
}

//==============================================================================
template <typename SampleType>
void Biquads<SampleType>::setFrequency(SampleType newFreq)
{
    //static_assert(static_cast<SampleType>(20.0) <= newFreq && newFreq <= static_cast<SampleType>(20000.0));

    if (hz != newFreq)
    {
        hz = newFreq;
        coefficients();
    }
}

template <typename SampleType>
void Biquads<SampleType>::setResonance(SampleType newRes)
{
    //static_assert(static_cast<SampleType>(0.0) <= newRes && newRes <= static_cast<SampleType>(1.0));

    if (q != newRes)
    {
        q = newRes;
        coefficients();
    }
}

template <typename SampleType>
void Biquads<SampleType>::setGain(SampleType newGain)
{
    if (g != newGain)
    {
        g = newGain;
        coefficients();
    }
}

template <typename SampleType>
void Biquads<SampleType>::setFilterType(filterType newFiltType)
{
    if (filtType != newFiltType)
    {
        filtType = newFiltType;
        reset();
        coefficients();
    }
}

template <typename SampleType>
void Biquads<SampleType>::setTransformType(transformationType newTransformType)
{
    if (transformType != newTransformType)
    {
        transformType = newTransformType;
        reset();
    }
}

//==============================================================================
template <typename SampleType>
void Biquads<SampleType>::prepare(int numChannels, double sampleRate)
{
    currentSampleRate = sampleRate;

    Wn_1.resize(numChannels);
    Wn_2.resize(numChannels);
    Xn_1.resize(numChannels);
    Xn_2.resize(numChannels);
    Yn_1.resize(numChannels);
    Yn_2.resize(numChannels);

    minFreq = static_cast <SampleType>(currentSampleRate / 24576.0);
    maxFreq = static_cast <SampleType>(currentSampleRate / 2.125);

    reset();
}

template <typename SampleType>
void Biquads<SampleType>::reset(SampleType initialValue)
{
    setFrequency(hz);
    setResonance(q);
    setGain(g);

    for (auto v : { &Wn_1, &Wn_2, &Xn_1, &Xn_2, &Yn_1, &Yn_2 })
        std::fill(v->begin(), v->end(), initialValue);
}

template <typename SampleType>
SampleType Biquads<SampleType>::processSample(int channel, SampleType inputValue)
{
    switch (transformType)
    {
    case TransformationType::directFormI:
        inputValue = directFormI(channel, inputValue);
        break;
    case TransformationType::directFormII:
        inputValue = directFormII(channel, inputValue);
        break;
    case TransformationType::directFormItransposed:
        inputValue = directFormITransposed(channel, inputValue);
        break;
    case TransformationType::directFormIItransposed:
        inputValue = directFormIITransposed(channel, inputValue);
        break;
    default:
        inputValue = directFormIITransposed(channel, inputValue);
    }

    return inputValue;
}

template <typename SampleType>
SampleType Biquads<SampleType>::directFormI(int channel, SampleType inputValue)
{
    auto& Xn1 = Xn_1[(size_t)channel];
    auto& Xn2 = Xn_2[(size_t)channel];
    auto& Yn1 = Yn_1[(size_t)channel];
    auto& Yn2 = Yn_2[(size_t)channel];

    auto& Xn = inputValue;

    SampleType Yn = ((Xn * b0) + (Xn1 * b1) + (Xn2 * b2) + (Yn1 * a1) + (Yn2 * a2));

    Xn2 = Xn1, Yn2 = Yn1;
    Xn1 = Xn, Yn1 = Yn;

    return Yn;
}

template <typename SampleType>
SampleType Biquads<SampleType>::directFormII(int channel, SampleType inputValue)
{
    auto& Wn1 = Wn_1[(size_t)channel];
    auto& Wn2 = Wn_2[(size_t)channel];

    auto& Xn = inputValue;

    SampleType Wn = (Xn + ((Wn1 * a1) + (Wn2 * a2)));
    SampleType Yn = ((Wn * b0) + (Wn1 * b1) + (Wn2 * b2));

    Wn2 = Wn1;
    Wn1 = Wn;

    return Yn;
}

template <typename SampleType>
SampleType Biquads<SampleType>::directFormITransposed(int channel, SampleType inputValue)
{
    auto& Wn1 = Wn_1[(size_t)channel];
    auto& Wn2 = Wn_2[(size_t)channel];
    auto& Xn1 = Xn_1[(size_t)channel];
    auto& Xn2 = Xn_2[(size_t)channel];

    auto& Xn = inputValue;

    SampleType Wn = (Xn + Wn2);
    SampleType Yn = ((Wn * b0) + Xn2);

    Xn2 = ((Wn * b1) + Xn1), Wn2 = ((Wn * a1) + Wn1);
    Xn1 = (Wn * b2), Wn1 = (Wn * a2);

    return Yn;
}

template <typename SampleType>
SampleType Biquads<SampleType>::directFormIITransposed(int channel, SampleType inputValue)
{
    auto& Xn1 = Xn_1[(size_t)channel];
    auto& Xn2 = Xn_2[(size_t)channel];

    auto& Xn = inputValue;

    SampleType Yn = ((Xn * b0) + (Xn2));

    Xn2 = ((Xn * b1) + (Xn1)+(Yn * a1));
    Xn1 = ((Xn * b2) + (Yn * a2));

    return Yn;
}

template <typename SampleType>
void Biquads<SampleType>::coefficients()
{
    auto omega = (hz * ((pi * two) / static_cast<SampleType>(currentSampleRate)));
    auto cos = (std::cos(omega));
    auto sin = (std::sin(omega));
    auto alpha = (sin * (one - q));
    auto a = std::pow(SampleType(10), (g * SampleType(0.5)));
    auto sqrtA = (std::sqrt(a) * two) * alpha;

    switch (filtType)
    {
    case filterType::lowPass2:

        a0 = one / (one + alpha);
        a1 = a0 * ((minusTwo * cos) * minusOne);
        a2 = a0 * ((one - alpha) * minusOne);
        b0 = a0 * ((one - cos) / two);
        b1 = a0 * (one - cos);
        b2 = a0 * ((one - cos) / two);

        break;


    case filterType::lowPass1:

        a0 = one / (one / (one));
        a1 = a0 * ((minusOne * ((one - omega) / (one + omega))) * minusOne);
        a2 = a0 * ((zero) * minusOne);
        b0 = a0 * (omega / (one + omega));
        b1 = a0 * (omega / (one + omega));
        b2 = a0 * (zero);

        break;


    case filterType::highPass2:

        a0 = one / (one + alpha);
        a1 = a0 * ((minusTwo * cos) * minusOne);
        a2 = a0 * ((one - alpha) * minusOne);
        b0 = a0 * ((one + cos) / two);
        b1 = a0 * (minusOne * (one + cos));
        b2 = a0 * ((one + cos) / two);

        break;


    case filterType::highPass1:

        a0 = one / (one);
        a1 = a0 * ((((one - omega) / (one + omega)) * minusOne) * minusOne);
        a2 = a0 * (zero * minusOne);
        b0 = a0 * (one / (one + omega));
        b1 = a0 * ((one / (one + omega)) * minusOne);
        b2 = a0 * zero;

        break;


    case filterType::bandPass:

        a0 = one / (one + alpha);
        a1 = a0 * ((minusTwo * cos) * minusOne);
        a2 = a0 * ((one - alpha) * minusOne);
        b0 = a0 * (sin / two);
        b1 = a0 * zero;
        b2 = a0 * (minusOne * (sin / two));

        break;


    case filterType::bandPassQ:

        a0 = one / (one + alpha);
        a1 = a0 * ((minusTwo * cos) * minusOne);
        a2 = a0 * ((one - alpha) * minusOne);
        b0 = a0 * alpha;
        b1 = a0 * zero;
        b2 = a0 * (minusOne * alpha);

        break;


    case filterType::lowShelf2:

        a0 = one / (((a + one) + ((a - one) * cos)) + sqrtA);
        a1 = a0 * ((((a - one) + ((a + one) * cos)) * minusTwo) * minusOne);
        a2 = a0 * ((((a + one) + ((a - one) * cos)) - sqrtA) * minusOne);
        b0 = a0 * ((((a + one) - ((a - one) * cos)) + sqrtA) * a);
        b1 = a0 * ((((a - one) - ((a + one) * cos)) * two) * a);
        b2 = a0 * ((((a + one) - ((a - one) * cos)) - sqrtA) * a);

        break;


    case filterType::lowShelf1:

        a0 = one / (one);
        a1 = a0 * ((minusOne * ((one - omega) / (one + omega))) * minusOne);
        a2 = a0 * (zero * minusOne);
        b0 = a0 * (one + ((omega / (one + omega)) * (minusOne + (a * a))));
        b1 = a0 * ((((omega / (one + omega)) * (minusOne + (a * a))) - ((one - omega) / (one + omega))));
        b2 = a0 * zero;

        break;


    case filterType::lowShelf1C:

        a0 = one / (one);
        a1 = a0 * ((minusOne * ((one - (omega / a)) / (one + (omega / a)))) * minusOne);
        a2 = a0 * (zero * minusOne);
        b0 = a0 * (one + ((omega / a) / (one + (omega / a)) * (minusOne + (a * a))));
        b1 = a0 * ((((omega / a) / (one + (omega / a))) * (minusOne + (a * a))) - ((one - (omega / a)) / (one + (omega / a))));
        b2 = a0 * zero;

        break;


    case filterType::highShelf2:

        a0 = one / (((a + one) - ((a - one) * cos)) + sqrtA);
        a1 = a0 * ((((a - one) - ((a + one) * cos)) * two) * minusOne);
        a2 = a0 * ((((a + one) - ((a - one) * cos)) - sqrtA) * minusOne);
        b0 = a0 * ((((a + one) + ((a - one) * cos)) + sqrtA) * a);
        b1 = a0 * ((((a - one) + ((a + one) * cos)) * minusTwo) * a);
        b2 = a0 * ((((a + one) + ((a - one) * cos)) - sqrtA) * a);

        break;


    case filterType::highShelf1:

        a0 = one / (one);
        a1 = a0 * ((minusOne * ((one - omega) / (one + omega))) * minusOne);
        a2 = a0 * (zero * minusOne);
        b0 = a0 * (one + ((minusOne + (a * a)) / (one + omega)));
        b1 = a0 * (minusOne * (((one - omega) / (one + omega)) + ((minusOne + (a * a)) / (one + omega))));
        b2 = a0 * zero;

        break;


    case filterType::highShelf1C:

        a0 = one / (one);
        a1 = a0 * ((minusOne * ((one - (omega * a)) / (one + (omega * a)))) * minusOne);
        a2 = a0 * (zero * minusOne);
        b0 = a0 * (one + ((minusOne + (a * a)) / (one + (omega * a))));
        b1 = a0 * (minusOne * (((one - (omega * a)) / (one + (omega * a))) + ((minusOne + (a * a)) / (one + (omega * a)))));
        b2 = a0 * zero;

        break;


    case filterType::peak:

        a0 = one / (one + (alpha / a));
        a1 = a0 * ((minusTwo * cos) * minusOne);
        a2 = a0 * ((one - (alpha / a)) * minusOne);
        b0 = a0 * (one + (alpha * a));
        b1 = a0 * (minusTwo * cos);
        b2 = a0 * (one - (alpha * a));

        break;


    case filterType::notch:

        a0 = one / (one + alpha);
        a1 = a0 * ((minusTwo * cos) * minusOne);
        a2 = a0 * ((one - alpha) * minusOne);
        b0 = a0 * one;
        b1 = a0 * (minusTwo * cos);
        b2 = a0 * (one);

        break;


    case filterType::allPass:

        a0 = one / (one + alpha);
        a1 = a0 * ((minusTwo * cos) * minusOne);
        a2 = a0 * ((one - alpha) * minusOne);
        b0 = a0 * (one - alpha);
        b1 = a0 * (minusTwo * cos);
        b2 = a0 * (one + alpha);

        break;


    default:

        a0 = one / (one);
        a1 = a0 * (zero * minusOne);
        a2 = a0 * (zero * minusOne);
        b0 = a0 * one;
        b1 = a0 * zero;
        b2 = a0 * zero;

        break;
    }
}
//==============================================================================
template class Biquads<float>;
template class Biquads<double>;

} //namespace filters
} //namespace stoneydsp
