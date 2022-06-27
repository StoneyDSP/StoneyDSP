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
    atomicB0(1.0),
    atomicB1(0.0),
    atomicB2(0.0),
    atomicA0(1.0),
    atomicA1(0.0),
    atomicA2(0.0),
    hz(1000.0),
    q(0.5),
    g(0.0),
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

    hz.store(newFreq);
    coefficients();
}

template <typename SampleType>
void Biquads<SampleType>::setResonance(SampleType newRes)
{
    //static_assert(static_cast<SampleType>(0.0) <= newRes && newRes <= static_cast<SampleType>(1.0));

    q.store(newRes);
    coefficients();
}

template <typename SampleType>
void Biquads<SampleType>::setGain(SampleType newGain)
{
    g.store(newGain);
    coefficients();
}

template <typename SampleType>
void Biquads<SampleType>::setFilterType(filterType newFiltType)
{
    if (filtType != newFiltType)
    {
        filtType.store(newFiltType);
        reset();
    }
}

template <typename SampleType>
void Biquads<SampleType>::setTransformType(transformationType newTransformType)
{
    if (transformType != newTransformType)
    {
        transformType.store(newTransformType);
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
    setFrequency(hz.load());
    setResonance(q.load());
    setGain(g.load());

    for (auto v : { &Wn_1, &Wn_2, &Xn_1, &Xn_2, &Yn_1, &Yn_2 })
        std::fill(v->begin(), v->end(), initialValue);
}

template <typename SampleType>
SampleType Biquads<SampleType>::processSample(int channel, SampleType inputValue)
{
    a0 = (one / atomicA0.load());
    a1 = (atomicA1.load() * a0) * minusOne;
    a2 = (atomicA2.load() * a0) * minusOne;
    b0 = (atomicB0.load() * a0);
    b1 = (atomicB1.load() * a0);
    b2 = (atomicB2.load() * a0);

    switch (transformType.load())
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
    auto omega = (hz.load() * ((pi * two) / static_cast<SampleType>(currentSampleRate)));
    auto cos = (std::cos(omega));
    auto sin = (std::sin(omega));
    //SampleType tan = (sin / cos);
    auto alpha = (sin * (one - q.load()));
    //auto a = (juce::Decibels::decibelsToGain<SampleType>dBtoGain(static_cast<SampleType>(g * static_cast <SampleType>(0.5))));
    auto a = std::pow(SampleType(10), (g.load() * SampleType(0.5)));

    auto sqrtA = (std::sqrt(a) * two) * alpha;

    SampleType b_0 = one;
    SampleType b_1 = zero;
    SampleType b_2 = zero;
    SampleType a_0 = one;
    SampleType a_1 = zero;
    SampleType a_2 = zero;

    switch (filtType.load())
    {
    case filterType::lowPass2:

        atomicB0.store((one - cos) / two);
        atomicB1.store(one - cos);
        atomicB2.store((one - cos) / two);
        atomicA0.store(one + alpha);
        atomicA1.store(minusTwo * cos);
        atomicA2.store(one - alpha);

        break;


    case filterType::lowPass1:

        atomicB0.store(omega / (one + omega));
        atomicB1.store(omega / (one + omega));
        atomicB2.store(zero);
        atomicA0.store(one);
        atomicA1.store(minusOne * ((one - omega) / (one + omega)));
        atomicA2.store(zero);

        break;


    case filterType::highPass2:

        atomicB0.store((one + cos) / two);
        atomicB1.store(minusOne * (one + cos));
        atomicB2.store((one + cos) / two);
        atomicA0.store(one + alpha);
        atomicA1.store(minusTwo * cos);
        atomicA2.store(one - alpha);

        break;


    case filterType::highPass1:

        atomicB0.store(one / (one + omega));
        atomicB1.store((one / (one + omega)) * minusOne);
        atomicB2.store(zero);
        atomicA0.store(one);
        atomicA1.store(((one - omega) / (one + omega)) * minusOne);
        atomicA2.store(zero);

        break;


    case filterType::bandPass:

        atomicB0.store(sin / two);
        atomicB1.store(zero);
        atomicB2.store(minusOne * (sin / two));
        atomicA0.store(one + alpha);
        atomicA1.store(minusTwo * cos);
        atomicA2.store(one - alpha);

        break;


    case filterType::bandPassQ:

        atomicB0.store(alpha);
        atomicB1.store(zero);
        atomicB2.store(minusOne * alpha);
        atomicA0.store(one + alpha);
        atomicA1.store(minusTwo * cos);
        atomicA2.store(one - alpha);

        break;


    case filterType::lowShelf2:

        b_0 = (((a + one) - ((a - one) * cos)) + sqrtA) * a;
        b_1 = (((a - one) - ((a + one) * cos)) * two) * a;
        b_2 = (((a + one) - ((a - one) * cos)) - sqrtA) * a;
        a_0 = ((a + one) + ((a - one) * cos)) + sqrtA;
        a_1 = ((a - one) + ((a + one) * cos)) * minusTwo;
        a_2 = ((a + one) + ((a - one) * cos)) - sqrtA;

        break;


    case filterType::lowShelf1:

        b_0 = one + ((omega / (one + omega)) * (minusOne + (a * a)));
        b_1 = (((omega / (one + omega)) * (minusOne + (a * a))) - ((one - omega) / (one + omega)));
        b_2 = zero;
        a_0 = one;
        a_1 = minusOne * ((one - omega) / (one + omega));
        a_2 = zero;

        break;


    case filterType::lowShelf1C:

        b_0 = one + ((omega / a) / (one + (omega / a)) * (minusOne + (a * a)));
        b_1 = ((((omega / a) / (one + (omega / a))) * (minusOne + (a * a))) - ((one - (omega / a)) / (one + (omega / a))));
        b_2 = zero;
        a_0 = one;
        a_1 = minusOne * ((one - (omega / a)) / (one + (omega / a)));
        a_2 = zero;

        break;


    case filterType::highShelf2:

        b_0 = (((a + one) + ((a - one) * cos)) + sqrtA) * a;
        b_1 = (((a - one) + ((a + one) * cos)) * minusTwo) * a;
        b_2 = (((a + one) + ((a - one) * cos)) - sqrtA) * a;
        a_0 = ((a + one) - ((a - one) * cos)) + sqrtA;
        a_1 = ((a - one) - ((a + one) * cos)) * two;
        a_2 = ((a + one) - ((a - one) * cos)) - sqrtA;

        break;


    case filterType::highShelf1:

        b_0 = one + ((minusOne + (a * a)) / (one + omega));
        b_1 = minusOne * (((one - omega) / (one + omega)) + ((minusOne + (a * a)) / (one + omega)));
        b_2 = zero;
        a_0 = one;
        a_1 = minusOne * ((one - omega) / (one + omega));
        a_2 = zero;

        break;


    case filterType::highShelf1C:

        b_0 = one + ((minusOne + (a * a)) / (one + (omega * a)));
        b_1 = minusOne * (((one - (omega * a)) / (one + (omega * a))) + ((minusOne + (a * a)) / (one + (omega * a))));
        b_2 = zero;
        a_0 = one;
        a_1 = minusOne * ((one - (omega * a)) / (one + (omega * a)));
        a_2 = zero;

        break;


    case filterType::peak:

        b_0 = one + (alpha * a);
        b_1 = minusTwo * cos;
        b_2 = one - (alpha * a);
        a_0 = one + (alpha / a);
        a_1 = minusTwo * cos;
        a_2 = one - (alpha / a);

        break;


    case filterType::notch:

        b_0 = one;
        b_1 = minusTwo * cos;
        b_2 = one;
        a_0 = one + alpha;
        a_1 = minusTwo * cos;
        a_2 = one - alpha;

        break;


    case filterType::allPass:

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
}


//==============================================================================
template class Biquads<float>;
template class Biquads<double>;

} //namespace filters
} //namespace stoneydsp
