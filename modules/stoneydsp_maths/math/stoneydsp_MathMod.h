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
    /*template <typename SampleType, typename ValueType>
    static SampleType xAddA(SampleType x, ValueType a)
    {
        value->store(a);
        
        return x + value->load();
    }*/
    /*template <typename SampleType>
    static SampleType xMulA(SampleType x, float a)
    {
        valueF->store(a);

        return x * valueF->load();
    }
    template <typename SampleType>
    static SampleType xMulA(SampleType x, double a)
    {
        valueD->store(a);

        return x * valueD->load();
    }*/

private:
    //==========================================================================
    MathMod() = delete;

    /*static std::atomic<float>* valueF;
    static std::atomic<double>* valueD;*/
};

} //namespace stoneydsp
