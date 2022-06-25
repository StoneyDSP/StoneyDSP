/*
  ==============================================================================

    Conversion.h
    Created: 25 June 2022 01:55:07am
    Author:  Nathan J. Hood

  ==============================================================================
*/

namespace stoneydsp
{
class Conversion
{
public:
    template <typename Type>
    static Type gainToDb (Type gain)
    {
        return std::log10(gain) * Type (20.0);
    }

    template <typename Type>
    static Type dBtoGain (Type dB)
    {
        return std::pow(Type (10), (dB * Type (0.5)));
    }

private:
    //==========================================================================
    Conversion() = delete;
};

} //namespace stoneydsp
