/*
  ==============================================================================

    Transforms.h
    Created: 16 May 2022 2:54:47am
    Author:  StoneyDSP

  ==============================================================================
*/

namespace stoneydsp
{
namespace filters
{

enum class TransformType
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
    void setb1(SampleType b1new);
    void setb2(SampleType b2new);
    void seta0(SampleType a0new);
    void seta1(SampleType a1new);
    void seta2(SampleType a2new);

    /** Sets the BiLinear Transform for the filter to use. See enum for available types. */
    void setTransformType(TransType newTransformType);

    //==========================================================================
    /** Initialises the processor. */
    void prepare(int numChannels);

    /** Resets the internal state variables of the processor. */
    void reset(SampleType initialValue = (SampleType) (0.0));

    //==========================================================================
    /** Processes one sample at a time on a given channel. */
    SampleType processSample(int channel, SampleType inputValue);

private:
    void coefficients();

  //==============================================================================
    SampleType directFormI(int channel, SampleType inputValue);
    SampleType directFormII(int channel, SampleType inputValue);
    SampleType directFormITransposed(int channel, SampleType inputValue);
    SampleType directFormIITransposed(int channel, SampleType inputValue);

    //==========================================================================
    /** Unit-delay object */
    std::vector<SampleType> Wn_1, Wn_2, Xn_1, Xn_2, Yn_1, Yn_2;
    
    //==========================================================================
    /** Coefficient gain */
    SampleType b0, b1, b2, a0, a1, a2;

    std::atomic<SampleType> b_0;
    std::atomic<SampleType> b_1;
    std::atomic<SampleType> b_2;
    std::atomic<SampleType> a_0;
    std::atomic<SampleType> a_1;
    std::atomic<SampleType> a_2;

    //==============================================================================
    /** Initialise the parameters. */
    TransType transformType = TransType::directFormIItransposed;

    //==============================================================================
    /** Initialise constants. */
    const SampleType zero = (0.0), one = (1.0), minusOne = (-1.0);
};

} //namespace stoneydsp
} //
