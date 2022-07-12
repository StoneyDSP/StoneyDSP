namespace stoneydsp
{

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
