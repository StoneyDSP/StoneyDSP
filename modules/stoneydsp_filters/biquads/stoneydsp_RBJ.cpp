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
    atomicA0(1.0),
    atomicA1(0.0),
    atomicA2(0.0),
    atomicB0(1.0),
    atomicB1(0.0),
    atomicB2(0.0),
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

    if (hz != newFreq)
    {
        hz.store(newFreq);
        coefficients();
    }
}

template <typename SampleType>
void Biquads<SampleType>::setResonance(SampleType newRes)
{
    //static_assert(static_cast<SampleType>(0.0) <= newRes && newRes <= static_cast<SampleType>(1.0));

    if (q != newRes)
    {
        q.store(newRes);
        coefficients();
    }
}

template <typename SampleType>
void Biquads<SampleType>::setGain(SampleType newGain)
{
    if (g != newGain)
    {
        g.store(newGain);
        coefficients();
    }
}

template <typename SampleType>
void Biquads<SampleType>::setFilterType(filterType newFiltType)
{
    if (filtType != newFiltType)
    {
        filtType.store(newFiltType);
        reset();
        coefficients();
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
    auto alpha = (sin * (one - q.load()));
    auto a = std::pow(SampleType(10), (g.load() * SampleType(0.5)));
    auto sqrtA = (std::sqrt(a) * two) * alpha;

    switch (filtType.load())
    {
    case filterType::lowPass2:

        atomicA0.store(one + alpha);
        atomicA1.store(minusTwo * cos);
        atomicA2.store(one - alpha);
        atomicB0.store((one - cos) / two);
        atomicB1.store(one - cos);
        atomicB2.store((one - cos) / two);

        break;


    case filterType::lowPass1:

        atomicA0.store(one);
        atomicA1.store(minusOne * ((one - omega) / (one + omega)));
        atomicA2.store(zero);
        atomicB0.store(omega / (one + omega));
        atomicB1.store(omega / (one + omega));
        atomicB2.store(zero);

        break;


    case filterType::highPass2:

        atomicA0.store(one + alpha);
        atomicA1.store(minusTwo * cos);
        atomicA2.store(one - alpha);
        atomicB0.store((one + cos) / two);
        atomicB1.store(minusOne * (one + cos));
        atomicB2.store((one + cos) / two);

        break;


    case filterType::highPass1:

        atomicA0.store(one);
        atomicA1.store(((one - omega) / (one + omega)) * minusOne);
        atomicA2.store(zero);
        atomicB0.store(one / (one + omega));
        atomicB1.store((one / (one + omega)) * minusOne);
        atomicB2.store(zero);

        break;


    case filterType::bandPass:

        atomicA0.store(one + alpha);
        atomicA1.store(minusTwo * cos);
        atomicA2.store(one - alpha);
        atomicB0.store(sin / two);
        atomicB1.store(zero);
        atomicB2.store(minusOne * (sin / two));

        break;


    case filterType::bandPassQ:

        atomicA0.store(one + alpha);
        atomicA1.store(minusTwo * cos);
        atomicA2.store(one - alpha);
        atomicB0.store(alpha);
        atomicB1.store(zero);
        atomicB2.store(minusOne * alpha);

        break;


    case filterType::lowShelf2:

        atomicA0.store(((a + one) + ((a - one) * cos)) + sqrtA);
        atomicA1.store(((a - one) + ((a + one) * cos)) * minusTwo);
        atomicA2.store(((a + one) + ((a - one) * cos)) - sqrtA);
        atomicB0.store((((a + one) - ((a - one) * cos)) + sqrtA) * a);
        atomicB1.store((((a - one) - ((a + one) * cos)) * two) * a);
        atomicB2.store((((a + one) - ((a - one) * cos)) - sqrtA) * a);

        break;


    case filterType::lowShelf1:

        atomicA0.store(one);
        atomicA1.store(minusOne * ((one - omega) / (one + omega)));
        atomicA2.store(zero);
        atomicB0.store(one + ((omega / (one + omega)) * (minusOne + (a * a))));
        atomicB1.store((((omega / (one + omega)) * (minusOne + (a * a))) - ((one - omega) / (one + omega))));
        atomicB2.store(zero);

        break;


    case filterType::lowShelf1C:

        atomicA0.store(one);
        atomicA1.store(minusOne * ((one - (omega / a)) / (one + (omega / a))));
        atomicA2.store(zero);
        atomicB0.store(one + ((omega / a) / (one + (omega / a)) * (minusOne + (a * a))));
        atomicB1.store(((((omega / a) / (one + (omega / a))) * (minusOne + (a * a))) - ((one - (omega / a)) / (one + (omega / a)))));
        atomicB2.store(zero);

        break;


    case filterType::highShelf2:

        atomicA0.store(((a + one) - ((a - one) * cos)) + sqrtA);
        atomicA1.store(((a - one) - ((a + one) * cos)) * two);
        atomicA2.store(((a + one) - ((a - one) * cos)) - sqrtA);
        atomicB0.store((((a + one) + ((a - one) * cos)) + sqrtA) * a);
        atomicB1.store((((a - one) + ((a + one) * cos)) * minusTwo) * a);
        atomicB2.store((((a + one) + ((a - one) * cos)) - sqrtA) * a);

        break;


    case filterType::highShelf1:

        atomicA0.store(one);
        atomicA1.store(minusOne * ((one - omega) / (one + omega)));
        atomicA2.store(zero);
        atomicB0.store(one + ((minusOne + (a * a)) / (one + omega)));
        atomicB1.store(minusOne * (((one - omega) / (one + omega)) + ((minusOne + (a * a)) / (one + omega))));
        atomicB2.store(zero);

        break;


    case filterType::highShelf1C:

        atomicA0.store(one);
        atomicA1.store(minusOne * ((one - (omega * a)) / (one + (omega * a))));
        atomicA2.store(zero);
        atomicB0.store(one + ((minusOne + (a * a)) / (one + (omega * a))));
        atomicB1.store(minusOne * (((one - (omega * a)) / (one + (omega * a))) + ((minusOne + (a * a)) / (one + (omega * a)))));
        atomicB2.store(zero);

        break;


    case filterType::peak:

        atomicA0.store(one + (alpha / a));
        atomicA1.store(minusTwo * cos);
        atomicA2.store(one - (alpha / a));
        atomicB0.store(one + (alpha * a));
        atomicB1.store(minusTwo * cos);
        atomicB2.store(one - (alpha * a));

        break;


    case filterType::notch:

        atomicB0.store(one);
        atomicB1.store(minusTwo * cos);
        atomicB2.store(one);
        atomicA0.store(one + alpha);
        atomicA1.store(minusTwo * cos);
        atomicA2.store(one - alpha);

        break;


    case filterType::allPass:

        atomicA0.store(one + alpha);
        atomicA1.store(minusTwo * cos);
        atomicA2.store(one - alpha);
        atomicB0.store(one - alpha);
        atomicB1.store(minusTwo * cos);
        atomicB2.store(one + alpha);

        break;


    default:

        atomicA0.store(one);
        atomicA1.store(zero);
        atomicA2.store(zero);
        atomicB0.store(one);
        atomicB1.store(zero);
        atomicB2.store(zero);

        break;
    }
}
//==============================================================================
template class Biquads<float>;
template class Biquads<double>;

} //namespace filters
} //namespace stoneydsp
