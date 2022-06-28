/*
  ==============================================================================

    Operators.h
    Created: 25 June 2022 12:54:47am
    Author:  Nathan J. Hood

  ==============================================================================
*/

namespace stoneydsp
{
namespace operators
{
class Unary
{
public:
    //==========================================================================
    template <typename Type>
    static Type operation(Type x, Type(*functocall)(Type))
    {
        Type g;
        g = (*functocall)(x);
        return (g);
    }
private:
    //==========================================================================
    template <typename Type>
    static Type abs(Type x)
    {
        return (std::abs(x));
    }

    template <typename Type>
    static Type inv(Type x)
    {
        return (x * Type(-1.0));
    }

    template <typename Type>
    static Type oneDivX(Type x)
    {
        return (x != Type(0.0) ? Type(1.0) / x : Type(0.0));
    }

    template <typename Type>
    static Type powTwo(Type x)
    {
        return (x * x);
    }
    //==========================================================================
    Unary() = delete;
};
class Binary
{
public:
    //==========================================================================
    template <typename Type>
    static Type operation(Type x, Type y, Type(*functocall)(Type, Type))
    {
        Type g;
        g = (*functocall)(x, y);
        return (g);
    }

private:
    //==========================================================================
    template <typename Type>
    static Type addition(Type a, Type b)
    {
        return (a + b);
    }

    template <typename Type>
    static Type subtraction(Type a, Type b)
    {
        return (a - b);
    }

    template <typename Type>
    static Type multiplication(Type a, Type b)
    {
        return (a * b);
    }

    template <typename Type>
    static Type division(Type a, Type b)
    {
        return (a / b);
    }

    //==========================================================================
    Binary() = delete;
};

} //namespace operators
} //namespace stoneydsp
