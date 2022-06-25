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
    //==============================================================================
    /** Constructor. */
    Transforms();

    //==============================================================================
    /** Sets the BiLinear Transform for the filter to use. See enum for availa ble types. */
    void setTransformType(TransType newTransformType);

    //==============================================================================
    /** Initialises the processor. */
    void prepare(int numChannels);

    /** Resets the internal state variables of the processor. */
    void reset(SampleType initialValue = (SampleType) (0.0));

    //==============================================================================
    /** Processes one sample at a time on a given channel. */
    SampleType processSample(int channel, SampleType inputValue);

    //==============================================================================
    SampleType directFormI(int channel, SampleType inputValue);
    SampleType directFormII(int channel, SampleType inputValue);
    SampleType directFormITransposed(int channel, SampleType inputValue);
    SampleType directFormIITransposed(int channel, SampleType inputValue);

    //==============================================================================
    SampleType& getb0() { return b0; }
    SampleType& getb1() { return b1; }
    SampleType& getb2() { return b2; }
    SampleType& geta0() { return a0; }
    SampleType& geta1() { return a1; }
    SampleType& geta2() { return a2; }

private:
    //==============================================================================
    /** Unit-delay objects. */
    std::vector<SampleType> Wn_1, Wn_2, Xn_1, Xn_2, Yn_1, Yn_2;
    
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
    TransType transformType = TransType::directFormIItransposed;

    //==============================================================================
    /** Initialise constants. */
    const SampleType zero = (0.0), one = (1.0);
};

} //namespace stoneydsp
} //
