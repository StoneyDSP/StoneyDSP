

namespace stoneydsp
{

class Bit
{
public:
    /** The & (bitwise AND) takes two numbers as operands and does AND on every bit of two numbers. The result of AND is 1 only if both bits are 1. */
    static int bitAnd(int a, int b)
    {
        return a & b;
    }

    /** The | (bitwise OR) takes two numbers as operands and does OR on every bit of two numbers. The result of OR is 1 if any of the two bits is 1. */
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

    /** The << (left shift) takes two numbers, left shifts the bits of the first operand, the second operand decides the number of places to shift */
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

} //namespace stoneydsp