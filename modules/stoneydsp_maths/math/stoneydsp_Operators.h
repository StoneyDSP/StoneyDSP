/*
  ==============================================================================

    Operators.h
    Created: 25 June 2022 12:54:47am
    Author:  Nathan J. Hood

  ==============================================================================
*/

namespace stoneydsp
{
class Operators
{
public:
    //==========================================================================
    template <typename Type>
    static Type add (Type a, Type b)
    {
        return a + b;
    }

    template <typename Type>
    static Type oneDivX (Type x)
    {
        return x != Type (0.0) ? Type (1.0) / x : Type (0.0);
    }

private:
    //==========================================================================
    Operators() = delete;
};
} //namespace stoneydsp
