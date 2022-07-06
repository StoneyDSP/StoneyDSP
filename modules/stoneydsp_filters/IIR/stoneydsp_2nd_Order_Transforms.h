
/*
  ==============================================================================

    Transforms.h
    Created: 6 Jul 2022 05:53:03am
    Author:  Nathan J. Hood
    Website: github.com/StoneyDSP
    email:   nathanjhood@googlemail.com

  ==============================================================================
*/

namespace stoneydsp
{
namespace filters
{

enum struct TransformType
{
    directFormI = 0,
    directFormII = 1,
    directFormItransposed = 2,
    directFormIItransposed = 3
};

/**
    A handy set of transforms.
*/

template <typename SampleType>
class Transforms
{
public:
    using TransType = TransformType;
    //==========================================================================
    /** Constructor. */
    Transforms();

    //==========================================================================
    void setb0(SampleType b0new);
    void seta0(SampleType a0new);
    void seta1(SampleType a1new);
    void setb1(SampleType b1new);
    void seta2(SampleType a2new);
    void setb2(SampleType b2new);

    /** Sets the BiLinear Transform for the filter to use. See enum for available types. */
    void setTransformType(TransType newTransformType);

    //==========================================================================
    /** Initialises the processor. */
    void prepare(int numChannels);

    /** Resets the internal state variables of the processor. */
    void reset(SampleType initialValue = { 0.0 });

    //==========================================================================
    /** Processes one sample at a time on a given channel. */
    SampleType processSample(int channel, SampleType inputValue);

private:
    //==========================================================================
    SampleType directFormI(int channel, SampleType inputValue);
    SampleType directFormII(int channel, SampleType inputValue);
    SampleType directFormITransposed(int channel, SampleType inputValue);
    SampleType directFormIITransposed(int channel, SampleType inputValue);

    //==========================================================================
    /** Unit-delay object */
    std::vector<SampleType> Wn_1, Wn_2, Xn_1, Xn_2, Yn_1, Yn_2;
    
    //==========================================================================
    /** Coefficient gain */
    stoneydsp::filters::Coefficient<SampleType> a0, b0, a1, b1, a2, b2;

    //==========================================================================
    /** Initialise the parameters. */
    std::atomic<TransType> transformType;

    SampleType loop, outputSample;

    //==========================================================================
    /** Initialise constants. */
    const SampleType zero = (0.0), one = (+1.0), minusOne = (-1.0);
};

} //namespace stoneydsp
} //
