/*
  ==============================================================================

    MatchedBiquads.cpp
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

template <typename SampleType>
MatchedBiquad<SampleType>::MatchedBiquad() 
    :
    a{ one, zero, zero }, b{ one, zero, zero },
    a_{ one, zero, zero }, b_{ one, zero, zero },
    f(zero), g(zero), q(zero), loop(zero), outputSample(zero),
    AA(zero), f0(zero), alfa(zero), w(zero),
    AA0(zero), AA1(zero), AA2(zero), phi1(zero), phi0(zero), phi2(zero),
    r1(zero), r2(zero), BB0(zero), BB1(zero), BB2(zero),
    _test(zero), minFreq(zero), maxFreq(zero),
    type(FilterType::MLowPass),
    transformType(TransformationType::directFormIItransposed)
{
    reset();
}

template <typename SampleType>
void MatchedBiquad<SampleType>::setFrequency(SampleType newFreq)
{
    jassert(minFreq <= newFreq && newFreq <= maxFreq);

    if (f != newFreq)
    {
        f = juce::jlimit(minFreq, maxFreq, newFreq);
        coeffs();
    }
}

template <typename SampleType>
void MatchedBiquad<SampleType>::setGain(SampleType newGain)
{
    if (g != newGain)
    {
        g = newGain;
        coeffs();
    }
}

template <typename SampleType>
void MatchedBiquad<SampleType>::setResonance(SampleType newRes)
{
    jassert(zero <= newRes && newRes <= one);

    if (q != newRes)
    {
        q = one / juce::jlimit(SampleType(0.01), SampleType(1.0), newRes);
        coeffs();
    }
}

template <typename SampleType>
void MatchedBiquad<SampleType>::setFilterType(FilterType newType)
{
    if (type != newType)
    {
        type = newType;
        reset();
        coeffs();
    }
}

template <typename SampleType>
void MatchedBiquad<SampleType>::setTransformType(TransformationType newTransformType)
{
    if (transformType != newTransformType)
    {
        transformType = newTransformType;
        reset();
        coeffs();
    }
}

template <typename SampleType>
void MatchedBiquad<SampleType>::prepare(juce::dsp::ProcessSpec spec)
{
    jassert(spec.sampleRate > 0);
    jassert(spec.numChannels > 0);

    sampleRate = spec.sampleRate;

    Wn_1.resize(spec.numChannels);
    Wn_2.resize(spec.numChannels);
    Xn_1.resize(spec.numChannels);
    Xn_2.resize(spec.numChannels);
    Yn_1.resize(spec.numChannels);
    Yn_2.resize(spec.numChannels);

    minFreq = static_cast <SampleType> (sampleRate / 24576.0);
    maxFreq = static_cast <SampleType> (sampleRate / 2.125);

    jassert(static_cast <SampleType> (sampleRate / 24576.0) >= minFreq && minFreq <= static_cast <SampleType> (sampleRate / 2.125));
    jassert(static_cast <SampleType> (sampleRate / 24576.0) <= maxFreq && maxFreq >= static_cast <SampleType> (sampleRate / 2.125));

    coeffs();
}

template <typename SampleType>
void MatchedBiquad<SampleType>::reset(SampleType initValue)
{
    for (auto v : { &Wn_1, &Wn_2, &Xn_1, &Xn_2, &Yn_1, &Yn_2 })
        std::fill(v->begin(), v->end(), initValue);
}

template <typename SampleType>
SampleType MatchedBiquad<SampleType>::processSample(int channel, SampleType inputValue)
{
    jassert(juce::isPositiveAndBelow(channel, Wn_1.size()));
    jassert(juce::isPositiveAndBelow(channel, Wn_2.size()));
    jassert(juce::isPositiveAndBelow(channel, Xn_1.size()));
    jassert(juce::isPositiveAndBelow(channel, Xn_2.size()));
    jassert(juce::isPositiveAndBelow(channel, Yn_1.size()));
    jassert(juce::isPositiveAndBelow(channel, Yn_1.size()));


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
SampleType MatchedBiquad<SampleType>::directFormI(int channel, SampleType inputSample)
{
    auto& Xn1 = Xn_1[(size_t)channel];
    auto& Xn2 = Xn_2[(size_t)channel];
    auto& Yn1 = Yn_1[(size_t)channel];
    auto& Yn2 = Yn_2[(size_t)channel];

    auto& Xn = inputSample;
    auto& Yn = outputSample;

    Yn = ((Xn * b[0]) + (Xn1 * b[1]) + (Xn2 * b[2]) + (Yn1 * a[1]) + (Yn2 * a[2]));

    Xn2 = Xn1;
    Yn2 = Yn1;
    Xn1 = Xn;
    Yn1 = Yn;

    return Yn;
}

template <typename SampleType>
SampleType MatchedBiquad<SampleType>::directFormII(int channel, SampleType inputSample)
{
    auto& Wn1 = Wn_1[(size_t)channel];
    auto& Wn2 = Wn_2[(size_t)channel];

    auto& Wn = loop;
    auto& Xn = inputSample;
    auto& Yn = outputSample;

    Wn = (Xn + ((Wn1 * a[1]) + (Wn2 * a[2])));
    Yn = ((Wn * b[0]) + (Wn1 * b[1]) + (Wn2 * b[2]));

    Wn2 = Wn1;
    Wn1 = Wn;

    return Yn;
}

template <typename SampleType>
SampleType MatchedBiquad<SampleType>::directFormITransposed(int channel, SampleType inputSample)
{
    auto& Wn1 = Wn_1[(size_t)channel];
    auto& Wn2 = Wn_2[(size_t)channel];
    auto& Xn1 = Xn_1[(size_t)channel];
    auto& Xn2 = Xn_2[(size_t)channel];

    auto& Wn = loop;
    auto& Xn = inputSample;
    auto& Yn = outputSample;

    Wn = (Xn + Wn2);
    Yn = ((Wn * b[0]) + Xn2);

    Xn2 = ((Wn * b[1]) + Xn1);
    Wn2 = ((Wn * a[1]) + Wn1);
    Xn1 = (Wn * b[2]);
    Wn1 = (Wn * a[2]);

    return Yn;
}

template <typename SampleType>
SampleType MatchedBiquad<SampleType>::directFormIITransposed(int channel, SampleType inputSample)
{
    auto& Xn1 = Xn_1[(size_t)channel];
    auto& Xn2 = Xn_2[(size_t)channel];

    auto& Xn = inputSample;
    auto& Yn = outputSample;

    Yn = ((Xn * b[0]) + (Xn2));

    Xn2 = ((Xn * b[1]) + (Xn1)+(Yn * a[1]));
    Xn1 = ((Xn * b[2]) + (Yn * a[2]));

    return Yn;
}

template <typename SampleType>
void MatchedBiquad<SampleType>::coeffs()
{
    const auto div = [&](SampleType a, SampleType b) { return a / b; };
    const auto powTwo = [&](SampleType x) { return x * x; };
    const auto powXY = [&](SampleType x, SampleType y) { return std::pow(x, y); };
    const auto sin = [&](SampleType x) { return std::sin(x); };
    const auto cos = [&](SampleType x) { return std::cos(x); };
    const auto sqrt = [&](SampleType a) { return std::sqrt(a); };
    const auto exp = [&](SampleType x) { return std::exp(x); };
    const auto cosh = [&](SampleType z) { return (exp(z) + exp(-z)) * zeroFive; };

    f0 = f / (static_cast<SampleType>(sampleRate) / two);
    AA = powXY(ten, div(g, twenty));
    const auto& pifo = pi * f0;

    switch (type)
    {

    case FilterType::MPeakEQ:


        // Poles
        a_[0] = one;
        a_[2] = exp((-zeroFive) * pifo / (sqrt(AA) * q));
        _test = four * AA * q * q;

        if ((_test > one) == true)
        {
            // complex conjugate poles
            a_[1] = minusTwo * a_[2] * cos(sqrt(one - one / (four * AA * q * q)) * pifo);
        }
        else
        {
            // real poles
            a_[1] = minusTwo * a_[2] * cosh(sqrt(one / (four * AA * q * q) - one) * pifo);
        }

        a_[2] = powXY(a_[2], two);

        // Zeros
        AA0 = powXY(one + a_[1] + a_[2], two);
        AA1 = powXY(one - a_[1] + a_[2], two);
        AA2 = (-four) * a_[2];

        phi1 = powXY(sin(zeroFive * pifo), two);
        phi0 = one - phi1;
        phi2 = four * phi0 * phi1;

        r1 = (phi0 * AA0 + phi1 * AA1 + phi2 * AA2) * powXY(AA, two);
        r2 = (AA1 - AA0 + four * (phi0 - phi1) * AA2) * powXY(AA, two);

        BB0 = AA0;
        BB2 = div((r1 - phi1 * r2 - BB0), (four * powXY(phi1, two)));
        BB1 = r2 + BB0 + four * (phi1 - phi0) * BB2;

        b_[1] = zeroFive * (one + a_[1] + a_[2] - sqrt(BB1));
        w = one + a_[1] + a_[2] - b_[1];
        b_[0] = zeroFive * (w + sqrt(powXY(w, two) + BB2));
        b_[2] = div((-BB2), (four * b_[0]));

        break;

    case FilterType::MHighPass:

        // Poles
        a_[0] = one;
        a_[2] = exp((-zeroFive) * div(pifo, q));
        _test = two * q;

        if ((_test > one) == true)
        {
            // Complex conjugate poles
            a_[1] = minusTwo * a_[2] * cos(sqrt(one - one / (four * q * q)) * pifo);
        }
        else
        {
            // Real poles
            a_[1] = minusTwo * a_[2] * cosh(sqrt(one / (four * q * q) - 1) * pifo);
        }

        a_[2] = powXY(a_[2], two);

        //Zeros
        AA0 = powXY((one + a_[1] + a_[2]), two);
        AA1 = powXY((one - a_[1] + a_[2]), two);
        AA2 = (-four) * a_[2];

        phi1 = powXY(sin(zeroFive * pifo), two);
        phi0 = one - phi1;
        phi2 = four * phi0 * phi1;

        b_[0] = q * sqrt(phi0 * AA0 + phi1 * AA1 + phi2 * AA2) / (four * phi1);
        b_[1] = minusTwo * (q * sqrt(phi0 * AA0 + phi1 * AA1 + phi2 * AA2) / (four * phi1));
        b_[2] = q * sqrt(phi0 * AA0 + phi1 * AA1 + phi2 * AA2) / (four * phi1);

        break;

    case FilterType::MLowPass:

        // Poles
        a_[0] = one;
        a_[2] = exp((-zeroFive) * div(pifo, q));

        _test = two * q;

        if ((_test > one) == true)
        {
            // Complex conjugate poles
            a_[1] = minusTwo * a_[2] * cos(sqrt(one - one / (four * q * q)) * pifo);
        }
        else
        {
            a_[1] = minusTwo * a_[2] * cosh(sqrt(one / (four * q * q) - one) * pifo);
        }
        a_[2] = powXY(a_[2], two);

        // Zeros
        AA0 = powXY((one + a_[1] + a_[2]), two);
        AA1 = powXY((one - a_[1] + a_[2]), two);
        AA2 = (-four) * a_[2];

        phi1 = powXY(sin(zeroFive * pifo), two);
        phi0 = one - phi1;
        phi2 = four * phi0 * phi1;

        r1 = (AA0 * phi0 + AA1 * phi1 + AA2 * phi2) * powXY(q, two);

        BB1 = div((r1 - AA0 * phi0), phi1);

        b_[0] = zeroFive * (sqrt(BB1) + one + a_[1] + a_[2]);
        b_[1] = (one + a_[1] + a_[2] - b_[0]);
        b_[2] = zero;

        break;

    case FilterType::MBandPass:

        // Poles
        a_[0] = one;
        a_[2] = exp((-zeroFive) * div(pifo, q));
        _test = two * q;

        if ((_test > 1) == true)
        {
            // Complex conjugate poles
            a_[1] = minusTwo * a_[2] * cos(sqrt(one - one / (four * q * q)) * pifo);
        }

        else
        {
            a_[1] = minusTwo * a_[2] * cosh(sqrt(one / (four * q * q) - one) * pifo);
        }
        a_[2] = powXY(a_[2], two);

        // Zeros
        AA0 = powXY((one + a_[1] + a_[2]), two);
        AA1 = powXY((one - a_[1] + a_[2]), two);
        AA2 = (-four) * a_[2];

        phi1 = powXY(sin(zeroFive * pifo), two);
        phi0 = one - phi1;
        phi2 = four * phi0 * phi1;

        r1 = phi0 * AA0 + phi1 * AA1 + phi2 * AA2;
        r2 = AA1 - AA0 + four * (phi0 - phi1) * AA2;

        BB2 = div((r1 - phi1 * r2), (four * phi1 * phi1));
        BB1 = r2 + four * (phi1 - phi0) * BB2;

        b_[1] = (-zeroFive) * sqrt(BB1);
        b_[0] = zeroFive * (sqrt(b_[1] * b_[1] + BB2) - b_[1]);
        b_[2] = -b_[0] - b_[1];

        break;

    case FilterType::PeakEQ:

        alfa = sin(pifo) / (two * sqrt(AA) * q);

        // Poles

        a_[0] = one;
        a_[1] = minusTwo * cos(pifo) / (one + alfa);
        a_[2] = (one - alfa) / (one + alfa);

        // Zeros
        b_[0] = (one + AA * alfa) / (one + alfa);
        b_[1] = minusTwo * cos(pifo) / (one + alfa);
        b_[2] = (one - AA * alfa) / (one + alfa);

        break;

    case FilterType::HighPass:

        alfa = sin(pifo) / (two * q);

        // Poles
        a_[0] = one;
        a_[1] = minusTwo * cos(pifo) / (one + alfa);
        a_[2] = (one - alfa) / (one + alfa);

        // Zeros
        b_[0] = ((one - a_[1] + a_[2]) / four);
        b_[1] = minusTwo * ((one - a_[1] + a_[2]) / four);
        b_[2] = (one - a_[1] + a_[2]) / four;

        break;

    case FilterType::LowPass:

        alfa = sin(pifo) / (two * q);

        // Poles
        a_[0] = one;
        a_[1] = minusTwo * cos(pifo) / (one + alfa);
        a_[2] = (one - alfa) / (one + alfa);

        // # Zeros
        b_[0] = (one + a_[1] + a_[2]) / four;
        b_[1] = two * ((one + a_[1] + a_[2]) / four);
        b_[2] = (one + a_[1] + a_[2]) / four;

        break;

    case FilterType::BandPass:

        alfa = sin(pifo) / (two * q);

        // Poles
        a_[0] = one;
        a_[1] = minusTwo * cos(pifo) / (one + alfa);
        a_[2] = (one - alfa) / (one + alfa);

        // Zeros
        b_[0] = (one - a_[2]) / two;
        b_[1] = zero;
        b_[2] = -((one - a_[2]) / two);

        break;
    }

    a[0] = (one / a_[0]);
    a[1] = ((-a_[1]) * a[0]);
    a[2] = ((-a_[2]) * a[0]);
    b[0] = (b_[0] * a[0]);
    b[1] = (b_[1] * a[0]);
    b[2] = (b_[2] * a[0]);
}

template <typename SampleType>
void MatchedBiquad<SampleType>::snapToZero() noexcept
{
    for (auto v : { &Wn_1, &Wn_2, &Xn_1, &Xn_2, &Yn_1, &Yn_2 })
        for (auto& element : *v)
            juce::dsp::util::snapToZero(element);
}

//==============================================================================
template class MatchedBiquad<float>;
template class MatchedBiquad<double>;

} //namespace filters
} //namespace stoneydsp
