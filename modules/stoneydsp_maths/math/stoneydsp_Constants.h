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
struct Constants
{
    /** A predefined value for Pi */
    static constexpr Type pi = static_cast<Type> (3.141592653589793238L);

    /** A predefined value for 2 * Pi */
    static constexpr Type twoPi = static_cast<Type> (2 * 3.141592653589793238L);

    /** A predefined value for Pi / 2 */
    static constexpr Type halfPi = static_cast<Type> (3.141592653589793238L / 2);

    /** A predefined value for Euler's number */
    static constexpr Type euler = static_cast<Type> (2.71828182845904523536L);

    /** A predefined value for sqrt(2) */
    static constexpr Type sqrt2 = static_cast<Type> (1.4142135623730950488L);

    /** A predefined value for tau */
    static constexpr Type tau = static_cast<Type> (1 - (1 / 2.71828182845904523536L));
};

} //namespace stoneydsp
} //namespace stoneydsp
