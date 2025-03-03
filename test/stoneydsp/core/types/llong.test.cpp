/**
 * @file long.test.cpp
 * @brief Test suite for stoneydsp::llong_t
 * @copyright Copyright (c) 2025
 *
 */

//==============================================================================

#include "stoneydsp/core/system/types.h"

//==============================================================================

#if defined(STONEYDSP_BUILD_TEST) && defined(STONEYDSP_BUILD_CORE)

//==============================================================================

  #include "utils.test.hpp"

//======================================================================//sizeof

STONEYDSP_TEST_CASE ("[core][types][llong_t][sizeof]",
                     "[core][types][llong_t][sizeof]")
{
  STONEYDSP_REQUIRE (sizeof (::stoneydsp::llong_t) == 8UL);
}

//=====================================================================//alignof

STONEYDSP_TEST_CASE ("[core][types][llong_t][alignof]",
                     "[core][types][llong_t][alignof]")
{
  STONEYDSP_REQUIRE (alignof (::stoneydsp::llong_t) == 8UL);
}

//=================================================================//type_traits

STONEYDSP_TEST_CASE ("[core][types][llong_t][type_traits][is_integral]",
                     "[core][types][llong_t][type_traits][is_integral]")
{
  STONEYDSP_REQUIRE (::std::is_integral< ::stoneydsp::llong_t>::value);
}

STONEYDSP_TEST_CASE ("[core][types][llong_t][type_traits][is_unsigned]",
                     "[core][types][llong_t][type_traits][is_unsigned]")
{
  STONEYDSP_REQUIRE (!::std::is_unsigned< ::stoneydsp::llong_t>::value);
}

STONEYDSP_TEST_CASE ("[core][types][llong_t][type_traits][is_arithmetic]",
                     "[core][types][llong_t][type_traits][is_arithmetic]")
{
  STONEYDSP_REQUIRE (::std::is_arithmetic< ::stoneydsp::llong_t>::value);
}

STONEYDSP_TEST_CASE ("[core][types][llong_t][type_traits][is_pointer]",
                     "[core][types][llong_t][type_traits][is_pointer]")
{
  STONEYDSP_REQUIRE (!::std::is_pointer< ::stoneydsp::llong_t>::value);
}

STONEYDSP_TEST_CASE ("[core][types][llong_t][type_traits][is_const]",
                     "[core][types][llong_t][type_traits][is_const]")
{
  STONEYDSP_REQUIRE (!::std::is_const< ::stoneydsp::llong_t>::value);
}

STONEYDSP_TEST_CASE ("[core][types][llong_t][type_traits][is_empty]",
                     "[core][types][llong_t][type_traits][is_empty]")
{
  STONEYDSP_REQUIRE (!::std::is_empty< ::stoneydsp::llong_t>::value);
}

STONEYDSP_TEST_CASE (
    "[core][types][llong_t][type_traits][is_trivially_copyable]",
    "[core][types][llong_t][type_traits][is_trivially_copyable]")
{
  STONEYDSP_REQUIRE (
      ::std::is_trivially_copyable< ::stoneydsp::llong_t>::value);
}

STONEYDSP_TEST_CASE ("[core][types][llong_t][type_traits][is_standard_layout]",
                     "[core][types][llong_t][type_traits][is_standard_layout]")
{
  STONEYDSP_REQUIRE (::std::is_standard_layout< ::stoneydsp::llong_t>::value);
}

//==============================================================//numeric_limits

STONEYDSP_TEST_CASE ("[core][types][llong_t][numeric_limits]",
                     "[core][types][llong_t][numeric_limits]")
{
  // { -9223372036854775807L - 1 }
  STONEYDSP_REQUIRE (::stoneydsp::numeric_limits< ::stoneydsp::llong_t>::min ()
                     == ::std::numeric_limits< ::stoneydsp::llong_t>::min ());
  // { 9223372036854775807L }
  STONEYDSP_REQUIRE (::stoneydsp::numeric_limits< ::stoneydsp::llong_t>::max ()
                     == ::std::numeric_limits< ::stoneydsp::llong_t>::max ());
  // { -9223372036854775807L - 1 }
  STONEYDSP_REQUIRE (
      ::stoneydsp::numeric_limits< ::stoneydsp::llong_t>::lowest ()
      == ::std::numeric_limits< ::stoneydsp::llong_t>::lowest ());
}

//==============================================================//special_values

STONEYDSP_TEST_CASE ("[core][types][llong_t][special_values]",
                     "[core][types][llong_t][special_values]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::llong_t min_val
      = ::std::numeric_limits< ::stoneydsp::llong_t>::min ();
  ::stoneydsp::llong_t max_val
      = ::std::numeric_limits< ::stoneydsp::llong_t>::max ();
  STONEYDSP_REQUIRE (min_val
                     == -9223372036854775807_llong_t
                            - 1_llong_t); // Minimum value for llong_t
  STONEYDSP_REQUIRE (
      max_val == 9223372036854775807_llong_t); // Maximum value for llong_t
}

//==================================================================//endianness

STONEYDSP_TEST_CASE ("[core][types][llong_t][endianness]",
                     "[core][types][llong_t][endianness]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::llong_t value = 0x123456789ABCDEF0_llong_t;
  ::std::uint8_t *bytePtr = reinterpret_cast< ::std::uint8_t *> (&value);

  if (bytePtr[0] == 0xF0)
    {
      STONEYDSP_REQUIRE (true); // Little-endian
    }
  else if (bytePtr[0] == 0x12)
    {
      STONEYDSP_REQUIRE (true); // Big-endian
    }
  else
    {
      STONEYDSP_REQUIRE (false); // Unknown endianness
    }
}

//====================================================================//rounding

STONEYDSP_TEST_CASE ("[core][types][llong_t][rounding]",
                     "[core][types][llong_t][rounding]")
{
  ::stoneydsp::float_t a = 1.5f;
  ::stoneydsp::llong_t b
      = static_cast< ::stoneydsp::llong_t> (::std::round (a));
  STONEYDSP_REQUIRE (
      b == 2); // 1.5 rounded to nearest integer and cast to llong_t
}

//==================================================================//arithmetic

STONEYDSP_TEST_CASE ("[core][types][llong_t][arithmetic]",
                     "[core][types][llong_t][arithmetic]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::llong_t a = 1500000000_llong_t;
  ::stoneydsp::llong_t b = 2000000000_llong_t;

  STONEYDSP_REQUIRE (a + b == 3500000000LL);          // Addition
  STONEYDSP_REQUIRE (a - b == -500000000LL);          // Subtraction
  STONEYDSP_REQUIRE (a * b == 3000000000000000000LL); // Multiplication
  STONEYDSP_REQUIRE (b / a == 1LL);                   // Division
  STONEYDSP_REQUIRE (b % a == 500000000LL);           // Modulo
}

//===============================================================//bitwise

STONEYDSP_TEST_CASE ("[core][types][llong_t][bitwise][logic]",
                     "[core][types][llong_t][bitwise][logic]")
{
  using namespace ::stoneydsp::core::types::literals;

  // clang-format off
  ::stoneydsp::llong_t a = 5_llong_t; // 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0101
  ::stoneydsp::llong_t b = 3_llong_t; // 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0011

  STONEYDSP_REQUIRE ((a & b) == 1); // AND: 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0001
  STONEYDSP_REQUIRE ((a | b) == 7); // OR:  0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0111
  STONEYDSP_REQUIRE ((a ^ b) == 6); // XOR: 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0110
  STONEYDSP_REQUIRE (~a == -6); // NOT: considering wrap-around for llong_t
  // clang-format on
}

STONEYDSP_TEST_CASE ("[core][types][llong_t][bitwise][arithmetic]",
                     "[core][types][llong_t][bitwise][arithmetic]")
{
  using namespace ::stoneydsp::core::types::literals;

  // clang-format off

  ::stoneydsp::llong_t a = 5_llong_t; // 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0101

  STONEYDSP_REQUIRE ((a << 1) == 10); // Left shift: 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 1010
  STONEYDSP_REQUIRE ((a >> 1) == 2); // Right shift: 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0010
  // clang-format on
}

//===============================================================//comparison

STONEYDSP_TEST_CASE ("[core][types][llong_t][comparison]",
                     "[core][types][llong_t][comparison]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::llong_t a = 5_llong_t;
  ::stoneydsp::llong_t b = 3_llong_t;
  STONEYDSP_REQUIRE ((a == b) == false);
  STONEYDSP_REQUIRE ((a != b) == true);
  STONEYDSP_REQUIRE ((a > b) == true);
  STONEYDSP_REQUIRE ((a < b) == false);
  STONEYDSP_REQUIRE ((a >= b) == true);
  STONEYDSP_REQUIRE ((a <= b) == false);
}

//===============================================================//serialization

STONEYDSP_TEST_CASE ("[core][types][llong_t][serialization]",
                     "[core][types][llong_t][serialization]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::std::stringstream ss;
  ::stoneydsp::llong_t originalValue = 42_llong_t;
  ::stoneydsp::llong_t deserializedValue;

  ss.write (reinterpret_cast<const char *> (&originalValue),
            sizeof (originalValue));
  ss.read (reinterpret_cast<char *> (&deserializedValue),
           sizeof (deserializedValue));

  STONEYDSP_REQUIRE (originalValue == deserializedValue);
}

//=======================================================//boundary_and_overflow

STONEYDSP_TEST_CASE ("[core][types][llong_t][boundary][overflow]",
                     "[core][types][llong_t][boundary][overflow]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::llong_t a = 9223372036854775807_llong_t;
  ::stoneydsp::llong_t b = 1_llong_t;

  STONEYDSP_REQUIRE (static_cast< ::stoneydsp::llong_t> (a + b)
                     == ::std::numeric_limits< ::stoneydsp::llong_t>::
                         min ()); // Check overflow wrap-around behaviour
}

//======================================================//boundary_and_underflow

STONEYDSP_TEST_CASE ("[core][types][llong_t][boundary][underflow]",
                     "[core][types][llong_t][boundary][underflow]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::llong_t a = -9223372036854775807_llong_t - 1_llong_t;
  ::stoneydsp::llong_t b = 1_llong_t;
  STONEYDSP_REQUIRE (
      static_cast< ::stoneydsp::llong_t> (a - b)
      == 9223372036854775807_llong_t); // Check underflow wrap-around behavior
}

//===============================================================//compatibility

STONEYDSP_TEST_CASE ("[core][types][llong_t][compatibility]",
                     "[core][types][llong_t][compatibility]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::std::vector< ::stoneydsp::llong_t> vec
      = { 5_llong_t, 3_llong_t, 4_llong_t, 1_llong_t, 2_llong_t };

  // Use std::sort to sort the vector
  ::std::sort (vec.begin (), vec.end ());

  // Verify the vector is sorted
  STONEYDSP_REQUIRE (
      vec
      == ::std::vector< ::stoneydsp::llong_t>{ 1_llong_t, 2_llong_t, 3_llong_t,
                                               4_llong_t, 5_llong_t });

  // Use std::accumulate to sum the elements
  ::stoneydsp::llong_t sum = ::std::accumulate (
      vec.begin (), vec.end (), ::stoneydsp::llong_t (0_llong_t));

  // Verify the sum is correct
  STONEYDSP_REQUIRE (sum == 15);
}

//===================================================================//STONEYDSP_benchmark

// STONEYDSP_Benchmark for addition
STONEYDSP_TEST_CASE ("[core][types][llong_t][benchmark][addition]",
                     "[core][types][llong_t][benchmark][addition]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::llong_t a = 1200_llong_t;
  ::stoneydsp::llong_t b = 3400_llong_t;

  STONEYDSP_BENCHMARK ("Addition") { return a + b; };
}

// STONEYDSP_Benchmark for subtraction
STONEYDSP_TEST_CASE ("[core][types][llong_t][benchmark][subtraction]",
                     "[core][types][llong_t][benchmark][subtraction]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::llong_t a = 3400_llong_t;
  ::stoneydsp::llong_t b = 1200_llong_t;

  STONEYDSP_BENCHMARK ("Subtraction") { return a - b; };
}

// STONEYDSP_Benchmark for multiplication
STONEYDSP_TEST_CASE ("[core][types][llong_t][benchmark][multiplication]",
                     "[core][types][llong_t][benchmark][multiplication]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::llong_t a = 1200_llong_t;
  ::stoneydsp::llong_t b = 2_llong_t;

  STONEYDSP_BENCHMARK ("Multiplication") { return a * b; };
}

// STONEYDSP_Benchmark for division
STONEYDSP_TEST_CASE ("[core][types][llong_t][benchmark][division]",
                     "[core][types][llong_t][benchmark][division]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::llong_t a = 1200_llong_t;
  ::stoneydsp::llong_t b = 2_llong_t;

  STONEYDSP_BENCHMARK ("Division") { return a / b; };
}

// STONEYDSP_Benchmark for type conversion to int
STONEYDSP_TEST_CASE ("[core][types][llong_t][benchmark][conversion][int]",
                     "[core][types][llong_t][benchmark][conversion][int]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::llong_t a = 1200_llong_t;

  STONEYDSP_BENCHMARK ("Conversion to int") { return static_cast<int> (a); };
}

// STONEYDSP_Benchmark for type conversion to float
STONEYDSP_TEST_CASE ("[core][types][llong_t][benchmark][conversion][float]",
                     "[core][types][llong_t][benchmark][conversion][float]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::llong_t a = 1200_llong_t;

  STONEYDSP_BENCHMARK ("Conversion to float")
  {
    return static_cast<float> (a);
  };
}

//============================================================================//

#endif // defined(STONEYDSP_BUILD_TEST)

//=========================================================================//EOF
