/*
  ==============================================================================

    Constants.h
    Created: 01 July 2022 12:45:47am
    Author:  StoneyDSP

  ==============================================================================
*/

namespace stoneydsp
{
namespace maths
{

template<typename Type>
class Unary
{
public:

    static Type inv(Type x)
    {
        return -x;
    }

    static Type abs(Type x)
    {
        return x >= 0 ? x : -x;
    }
    
private:
    Unary() = delete;
}

template<typename Type>
class Binary
{
public:

    static Type add(Type a, Type b) 
    {
        return a + b;
    }

    static Type sub(Type a, Type b)
    {
        return a - b;
    }

    static Type mul(Type a, Type b)
    {
        return a * b;
    }

    static Type div(Type a, Type b)
    {
        return a / b;
    }

private:
    Binary() = delete;
};

template<typename Type>
class Bit
{
public:
    /* The& (bitwise AND) in C or C++ takes two numbers 
    as operands and does AND on every bit of two numbers. 
    The result of AND is 1 only if both bits are 1. */
    static int bitAnd(int a, int b)
    {
        return a & b;
    }
    
    /* The | (bitwise OR) in C or C++ takes two numbers 
    as operands and does OR on every bit of two numbers. 
    The result of OR is 1 if any of the two bits is 1. */
    static int bitOr(int a, int b)
    {
        return a | b;
    }
    
    /* The ^ (bitwise XOR) in C or C++ takes two numbers 
    as operands and does XOR on every bit of two numbers. 
    The result of XOR is 1 if the two bits are different. */
    static int bitXor(int a, int b)
    {
        return a ^ b;
    }
    
    /* The << (left shift) in C or C++ takes two numbers, 
    left shifts the bits of the first operand, the second 
    operand decides the number of places to shift */
    static int bitLeft(int a, int b)
    {
        return a << b;
    }
    
    /* The >> (right shift) in C or C++ takes two numbers, 
    right shifts the bits of the first operand, the second 
    operand decides the number of places to shift.  */
    static int bitRight(int a, int b)
    {
        return a >> b;
    }
    
    /* The ~ (bitwise NOT) in C or C++ takes one number and 
    inverts all bits of it. */
    static int bitNot(int a)
    {
        return ~a;
    }

private:
    Bit() = delete;
};

template<typename Type>
class Flow
{
public:
    static Type router(bool i, Type x)
    {

    }

    static bool aGTb(Type a, Type b)
    {
        return a > b;
    }

    static bool aGEb(Type a, Type b)
    {
        return a >= b;
    }

    static bool aLTb(Type a, Type b)
    {
        return a < b;
    }

    static bool aLEb(Type a, Type b)
    {
        return a <= b;
    }

    static bool aEQb(Type a, Type b)
    {
        return a == b;
    }

    static bool aNEb(Type a, Type b)
    {
        return a != b;
    }

    static bool boolInv(bool i)
    {
        return x == true ? false : true;
    }
private:
    Flow() = delete;
};

template<typename Type>
struct Constants
{
    /** A predefined value for Zero */
    static constexpr Type zero = static_cast<Type> (0.0L);

    /** A predefined value for One */
    static constexpr Type one = static_cast<Type> (1.0L);

    /** A predefined value for Two */
    static constexpr Type two = static_cast<Type> (2.0L);

    /** A predefined value for minus One */
    static constexpr Type minusOne = static_cast<Type> (-1.0L);

    /** A predefined value for minus Two */
    static constexpr Type minusTwo = static_cast<Type> (-2.0L);

    /** A predefined value for Pi */
    static constexpr Type pi = static_cast<Type> (3.141592653589793238L);

    /** A predefined value for 2 * Pi */
    static constexpr Type twoPi = static_cast<Type> (2 * 3.141592653589793238L);

    /** A predefined value for Pi / 2 */
    static constexpr Type halfPi = static_cast<Type> (3.141592653589793238L / 2);

    /** A predefined value for Euler's number */
    static constexpr Type euler = static_cast<Type> (2.71828182845904523536L);

    /** A predefined value for tau */
    static constexpr Type tau = static_cast<Type> (1 - (1 / 2.71828182845904523536L));

    /** A predefined value for sqrt(2) */
    static constexpr Type sqrt2 = static_cast<Type> (1.4142135623730950488L);

    /** A predefined value for sqrt(2) / 2 */
    static constexpr Type sqrt2Div2 = static_cast<Type> (1.4142135623730950488L / 2);

    /** A predefined value for 2 * sqrt(2) * 2 */
    static constexpr Type sqrt2Mul2 = static_cast<Type> (1.4142135623730950488L * 2);

    /** A predefined value for one third of one */
    static constexpr Type oneThird = static_cast<Type> (1.0L / 3);

    /** A predefined value for two thirds of one */
    static constexpr Type twoThirds = static_cast<Type> (2.0L / 3);
};

} //namespace stoneydsp
} //namespace stoneydsp
