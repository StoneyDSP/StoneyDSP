/*
  ==============================================================================

    MathMod.h
    Created: 26 June 2022 07:11:53am
    Author:  Nathan J. Hood

  ==============================================================================
*/

namespace stoneydsp
{
class MathMod
{
public:
    //==========================================================================
    template <typename SampleType>
    static SampleType xAddA(SampleType x, float a)
    {
        value.store(a);
        
        return x += value.load();
    }


private:
    //==========================================================================
    MathMod() = delete;

    std::atomic<float> value;
};
} //namespace stoneydsp
