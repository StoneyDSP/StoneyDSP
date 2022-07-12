/*/*
  ==============================================================================

    Transforms.cpp
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
Transforms<SampleType>::Transforms() 
    : 
    Wn_1(zero), Wn_2(zero), Xn_1(zero), Xn_2(zero), Yn_1(zero), Yn_2(zero),
    a0(one), b0(one), a1(zero), b1(zero), a2(zero), b2(zero),
    transformType(TransType::directFormIItransposed),
    loop(zero), outputSample(zero)
{
    reset();
}

template <typename SampleType>
void Transforms<SampleType>::seta0(SampleType a0new)
{
    if (a0 != a0new)
    {
        a0 = a0new;
    }
}

template <typename SampleType>
void Transforms<SampleType>::setb0(SampleType b0new)
{
    if (b0 != b0new)
    {
        b0 = b0new;
    }
}

template <typename SampleType>
void Transforms<SampleType>::seta1(SampleType a1new)
{
    if (a1 != a1new)
    {
        a1 = a1new;
    }
}

template <typename SampleType>
void Transforms<SampleType>::setb1(SampleType b1new)
{
    if (b1 != b1new)
    {
        b1 = b1new;
    }
}

template <typename SampleType>
void Transforms<SampleType>::seta2(SampleType a2new)
{
    if (a2 != a2new)
    {
        a2 = a2new;
    }
}

template <typename SampleType>
void Transforms<SampleType>::setb2(SampleType b2new)
{
    if (b2 != b2new)
    {
        b2 = b2new;
    }
}

//==============================================================================
template <typename SampleType>
void Transforms<SampleType>::setTransformType(TransType newTransformType)
{
    if (transformType != newTransformType)
    {
        transformType = newTransformType;
        reset();
    }
}

//==============================================================================
template <typename SampleType>
void Transforms<SampleType>::prepare(int numChannels)
{
    assert(numChannels > 0);

    Wn_1.resize(numChannels);
    Wn_2.resize(numChannels);
    Xn_1.resize(numChannels);
    Xn_2.resize(numChannels);
    Yn_1.resize(numChannels);
    Yn_2.resize(numChannels);

    reset();
}

template <typename SampleType>
void Transforms<SampleType>::reset(SampleType initialValue)
{
    for (auto v : { &Wn_1, &Wn_2, &Xn_1, &Xn_2, &Yn_1, &Yn_2 })
        std::fill(v->begin(), v->end(), initialValue);
}

template <typename SampleType>
SampleType Transforms<SampleType>::processSample(int channel, SampleType inputValue)
{
    assert(channel < Wn_1.size());
    assert(channel < Wn_2.size());
    assert(channel < Xn_1.size());
    assert(channel < Xn_2.size());
    assert(channel < Yn_1.size());
    assert(channel < Yn_2.size());

    switch (transformType)
    {
    case TransType::directFormI:
        inputValue = directFormI(channel, inputValue);
        break;
    case TransType::directFormII:
        inputValue = directFormII(channel, inputValue);
        break;
    case TransType::directFormItransposed:
        inputValue = directFormITransposed(channel, inputValue);
        break;
    case TransType::directFormIItransposed:
        inputValue = directFormIITransposed(channel, inputValue);
        break;
    default:
        inputValue = directFormIITransposed(channel, inputValue);
    }

    return inputValue;
}

template <typename SampleType>
SampleType Transforms<SampleType>::directFormI(int channel, SampleType inputSample)
{
    auto& Xn1 = Xn_1[(size_t)channel];
    auto& Xn2 = Xn_2[(size_t)channel];
    auto& Yn1 = Yn_1[(size_t)channel];
    auto& Yn2 = Yn_2[(size_t)channel];

    auto& Xn = inputSample;
    auto& Yn = outputSample;

    Yn = ((Xn * b0) + (Xn1 * b1) + (Xn2 * b2) + (Yn1 * a1) + (Yn2 * a2));

    Xn2 = Xn1, Yn2 = Yn1;
    Xn1 = Xn, Yn1 = Yn;

    return Yn;
}

template <typename SampleType>
SampleType Transforms<SampleType>::directFormII(int channel, SampleType inputSample)
{
    auto& Wn1 = Wn_1[(size_t)channel];
    auto& Wn2 = Wn_2[(size_t)channel];

    auto& Wn = loop;
    auto& Xn = inputSample;
    auto& Yn = outputSample;

    Wn = (Xn + ((Wn1 * a1) + (Wn2 * a2)));
    Yn = ((Wn * b0) + (Wn1 * b1) + (Wn2 * b2));

    Wn2 = Wn1;
    Wn1 = Wn;

    return Yn;
}

template <typename SampleType>
SampleType Transforms<SampleType>::directFormITransposed(int channel, SampleType inputSample)
{
    auto& Wn1 = Wn_1[(size_t)channel];
    auto& Wn2 = Wn_2[(size_t)channel];
    auto& Xn1 = Xn_1[(size_t)channel];
    auto& Xn2 = Xn_2[(size_t)channel];

    auto& Wn = loop;
    auto& Xn = inputSample;
    auto& Yn = outputSample;

    Wn = (Xn + Wn2);
    Yn = ((Wn * b0) + Xn2);

    Xn2 = ((Wn * b1) + Xn1), Wn2 = ((Wn * a1) + Wn1);
    Xn1 = (Wn * b2), Wn1 = (Wn * a2);

    return Yn;
}

template <typename SampleType>
SampleType Transforms<SampleType>::directFormIITransposed(int channel, SampleType inputSample)
{
    auto& Xn1 = Xn_1[(size_t)channel];
    auto& Xn2 = Xn_2[(size_t)channel];

    auto& Xn = inputSample;
    auto& Yn = outputSample;

    Yn = ((Xn * b0) + (Xn2));

    Xn2 = ((Xn * b1) + (Xn1) + (Yn * a1));
    Xn1 = ((Xn * b2) + (Yn * a2));

    return Yn;
}

//==============================================================================
template class Transforms<float>;
template class Transforms<double>;

} //namespace stoneydsp
} //
