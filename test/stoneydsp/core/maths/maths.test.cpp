/**
 * @file maths.test.cpp
 * @author StoneyDSP (nathanjhood@googlemail.com)
 * @copyright Copyright (c) 2026
 */

#include "stoneydsp/core/core.h"

#if defined(STONEYDSP_BUILD_TEST)

  #include "../../../utils.test.hpp"

  #include <cmath>

namespace
{
template <typename ValueType>
bool
approximatelyEqual (ValueType actual, ValueType expected, ValueType tolerance)
{
  return std::abs (actual - expected) <= tolerance;
}
} // namespace

STONEYDSP_TEST_CASE ("[core][maths][constants]",
                     "[core][maths][constants]")
{
  typedef ::stoneydsp::core::maths::Constants<double> Constants;

  const double &pi = Constants::pi;
  STONEYDSP_REQUIRE (
      approximatelyEqual (pi, 3.14159265358979323846, 1.0e-15));
  STONEYDSP_REQUIRE (Constants::tau == Constants::twoPi);
  STONEYDSP_REQUIRE (
      approximatelyEqual (Constants::oneDivSqrtTwo * Constants::sqrtTwo,
                          1.0, 1.0e-15));
}

STONEYDSP_TEST_CASE ("[core][maths][functions]",
                     "[core][maths][functions]")
{
  typedef ::stoneydsp::core::maths::Functions<double> Functions;
  typedef ::stoneydsp::core::maths::IntegerFunctions<int> IntegerFunctions;

  STONEYDSP_REQUIRE (Functions::square (3.0) == 9.0);
  STONEYDSP_REQUIRE (Functions::reciprocal (4.0) == 0.25);
  STONEYDSP_REQUIRE (IntegerFunctions::moduloTwo (5) == 1);
  STONEYDSP_REQUIRE (IntegerFunctions::moduloTwo (6) == 0);
}

STONEYDSP_TEST_CASE ("[core][maths][conversions]",
                     "[core][maths][conversions]")
{
  const double oneBitDecibels = 6.0205999132796239042;

  STONEYDSP_REQUIRE (approximatelyEqual (
      ::stoneydsp::core::maths::decibelsToGain (oneBitDecibels), 2.0,
      1.0e-15));
  STONEYDSP_REQUIRE (approximatelyEqual (
      ::stoneydsp::core::maths::gainToDecibels (2.0), oneBitDecibels,
      1.0e-15));
  STONEYDSP_REQUIRE (
      ::stoneydsp::core::maths::bitsToGain (1.0) == 2.0);
  STONEYDSP_REQUIRE (
      ::stoneydsp::core::maths::gainToBits (0.5) == -1.0);

  STONEYDSP_REQUIRE (approximatelyEqual (
      stoneydsp_double_decibels_to_gain (oneBitDecibels), 2.0, 1.0e-15));
  STONEYDSP_REQUIRE (
      stoneydsp_float_bits_to_gain (1.0F) == 2.0F);

  STONEYDSP_REQUIRE (std::isinf (
      ::stoneydsp::core::maths::gainToDecibels (0.0)));
  STONEYDSP_REQUIRE (
      ::stoneydsp::core::maths::gainToDecibels (0.0) < 0.0);
  STONEYDSP_REQUIRE (std::isnan (
      ::stoneydsp::core::maths::gainToDecibels (-1.0)));
}

#endif // defined(STONEYDSP_BUILD_TEST)
