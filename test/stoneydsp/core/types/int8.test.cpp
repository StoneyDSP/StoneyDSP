/**
 * @file int8.test.cpp
 * @brief Test suite for stoneydsp::int8_t
 * @copyright Copyright (c) 2025
 *
 */

//==============================================================================

#include "stoneydsp/core/types/int8.h"

//==============================================================================

#if defined(STONEYDSP_BUILD_TEST) && defined(STONEYDSP_BUILD_CORE)

//==============================================================================

  #include "stoneydsp/core/system/compiler.h" // for `STONEYDSP_PUBLIC_FUNCTION`
  #include "stoneydsp/core/types/math.h"      // for `stoneydsp::float_t`
  #include <algorithm>                        // for `std::sort`
  #include <catch2/benchmark/catch_benchmark.hpp> //
  #include <catch2/catch_test_macros.hpp>         //
  #include <limits>                               // for `std::numeric_limits`
  #include <numeric>                              // for `std::accumulate`
  #include <sstream>                              // for serialization tests
  #include <type_traits> // for `is_signed` and `is_unsigned`
  #include <vector>      // for compatibility tests

//======================================================================//sizeof

TEST_CASE ("sizeof stoneydsp::int8_t is 1 byte",
           "[core][types][int8_t][sizeof]")
{
  REQUIRE (sizeof (::stoneydsp::int8_t) == 1UL);
}

//=====================================================================//alignof

TEST_CASE ("alignof stoneydsp::int8_t is 1 byte",
           "[core][types][int8_t][alignof]")
{
  REQUIRE (alignof (::stoneydsp::int8_t) == 1UL);
}

//=================================================================//type_traits

TEST_CASE ("Check if types are signed or unsigned",
           "[core][types][int8_t][type_traits][is_signed]")
{
  REQUIRE (::std::is_signed< ::stoneydsp::int8_t>::value);
}

TEST_CASE ("Is stoneydsp::int8_t trivially copyable",
           "[core][types][int8_t][type_traits][is_trivially_copyable]")
{
  REQUIRE (::std::is_trivially_copyable< ::stoneydsp::int8_t>::value);
}

TEST_CASE ("Is stoneydsp::int8_t standard-layout conforming",
           "[core][types][int8_t][type_traits][is_standard_layout]")
{
  REQUIRE (::std::is_standard_layout< ::stoneydsp::int8_t>::value);
}

//==============================================================//special_values

TEST_CASE ("Numeric limits of stoneydsp::int8_t",
           "[core][types][int8_t][numeric_limits][special_values]")
{
  REQUIRE (::stoneydsp::int8_min // { -128 }
           == ::std::numeric_limits< ::stoneydsp::int8_t>::min ());
  REQUIRE (::stoneydsp::int8_max // { 127 }
           == ::std::numeric_limits< ::stoneydsp::int8_t>::max ());
}

//==============================================================//numeric_limits

TEST_CASE ("Special values of stoneydsp::int8_t",
           "[core][types][int8_t][numeric_limits]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::int8_t min_val
      = ::std::numeric_limits< ::stoneydsp::int8_t>::min ();
  ::stoneydsp::int8_t max_val
      = ::std::numeric_limits< ::stoneydsp::int8_t>::max ();
  REQUIRE (min_val == -128 /**_int8*/); // Minimum value for int8_t
  REQUIRE (max_val == 127_int8);  // Maximum value for int8_t
}

//==================================================================//endianness

TEST_CASE ("Endianness handling for stoneydsp::int8_t",
           "[core][types][int8_t][endianness]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::int8_t value = 0x12_int8;
  ::std::uint8_t *bytePtr = reinterpret_cast< ::std::uint8_t *> (&value);

  if (bytePtr[0] == 0x12)
    {
      REQUIRE (true); // Little-endian and Big-endian will look the same for a
                      // single byte
    }
  else
    {
      REQUIRE (false); // Unknown endianness
    }
}

//====================================================================//rounding

TEST_CASE ("Rounding behavior of stoneydsp::int8_t",
           "[core][types][int8_t][rounding]")
{
  ::stoneydsp::float_t a = 1.5f;
  ::stoneydsp::int8_t b = static_cast< ::stoneydsp::int8_t> (::std::round (a));
  REQUIRE (b == 2); // 1.5 rounded to nearest integer and cast to int8_t
}

//==================================================================//arithmetic

TEST_CASE ("Arithmetic operations with stoneydsp::int8_t",
           "[core][types][int8_t][arithmetic]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::int8_t a = 15_int8;
  ::stoneydsp::int8_t b = 20_int8;

  REQUIRE (a + b == 35);  // Addition
  REQUIRE (a - b == -5);  // Subtraction
  REQUIRE (a * b == 300); // Multiplication
  REQUIRE (b / a == 1);   // Division
  REQUIRE (b % a == 5);   // Modulo
}

//===============================================================//bitwise

TEST_CASE ("Bitwise operations with stoneydsp::int8_t",
           "[core][types][int8_t][bitwise]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::int8_t a = 5_int8; // 0101
  ::stoneydsp::int8_t b = 3_int8; // 0011

  REQUIRE ((a & b) == 1); // AND: 0001
  REQUIRE ((a | b) == 7); // OR:  0111
  REQUIRE ((a ^ b) == 6); // XOR: 0110
  REQUIRE (~a == -6);     // NOT: considering wrap-around for int8_t
}

TEST_CASE ("Shift operations with stoneydsp::int8_t",
           "[core][types][int8_t][bitwise]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::int8_t a = 5_int8; // 0101

  REQUIRE ((a << 1) == 10); // Left shift: 1010
  REQUIRE ((a >> 1) == 2);  // Right shift: 0010
}

//===============================================================//comparison

TEST_CASE ("Comparison operations with stoneydsp::int8_t",
           "[core][types][int8_t][comparison]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::int8_t a = 5_int8;
  ::stoneydsp::int8_t b = 3_int8;

  REQUIRE ((a == b) == false);
  REQUIRE ((a != b) == true);
  REQUIRE ((a > b) == true);
  REQUIRE ((a < b) == false);
  REQUIRE ((a >= b) == true);
  REQUIRE ((a <= b) == false);
}

//===============================================================//serialization

TEST_CASE ("Check serialization and deserialization for stoneydsp::int8_t",
           "[core][types][int8_t][serialization]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::std::stringstream ss;

  ::stoneydsp::int8_t originalValue = 42_int8;
  ::stoneydsp::int8_t deserializedValue;

  ss.write (reinterpret_cast<const char *> (&originalValue),
            sizeof (originalValue));
  ss.read (reinterpret_cast<char *> (&deserializedValue),
           sizeof (deserializedValue));

  REQUIRE (originalValue == deserializedValue);
}

//=======================================================//boundary_and_overflow

TEST_CASE ("Boundary and overflow behaviour of stoneydsp::int8_t",
           "[core][types][int8_t][boundary][overflow]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::int8_t a = 127_int8;
  ::stoneydsp::int8_t b = 1_int8;

  REQUIRE (static_cast< ::stoneydsp::int8_t> (a + b)
           == -128); // Check overflow wrap-around behaviour
}

//======================================================//boundary_and_underflow

TEST_CASE ("Boundary and underflow behavior of stoneydsp::int8_t",
           "[core][types][int8_t][boundary][underflow]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::int8_t a = -127_int8;
  ::stoneydsp::int8_t b = 2_int8;

  REQUIRE (static_cast< ::stoneydsp::int8_t> (a - b)
           == 127); // Check underflow wrap-around behavior
}

//===============================================================//compatibility

TEST_CASE ("Compatibility of stoneydsp::int8_t with standard library",
           "[core][types][int8_t][compatibility]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::std::vector< ::stoneydsp::int8_t> vec
      = { 5_int8, 3_int8, 4_int8, 1_int8, 2_int8 };

  // Use std::sort to sort the vector
  ::std::sort (vec.begin (), vec.end ());

  // Verify the vector is sorted
  REQUIRE (vec
           == ::std::vector< ::stoneydsp::int8_t>{ 1_int8, 2_int8, 3_int8,
                                                   4_int8, 5_int8 });

  // Use std::accumulate to sum the elements
  ::stoneydsp::int8_t sum = ::std::accumulate (vec.begin (), vec.end (),
                                               ::stoneydsp::int8_t (0_int8));

  // Verify the sum is correct
  REQUIRE (sum == 15);
}

//===================================================================//benchmark

// Benchmark for addition
TEST_CASE ("Benchmark for stoneydsp::int8_t addition",
           "[core][types][int8_t][benchmark]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::int8_t a = 12_int8;
  ::stoneydsp::int8_t b = 34_int8;

  BENCHMARK ("Addition") { return a + b; };
}

// Benchmark for subtraction
TEST_CASE ("Benchmark for stoneydsp::int8_t subtraction",
           "[core][types][int8_t][benchmark]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::int8_t a = 34_int8;
  ::stoneydsp::int8_t b = 12_int8;

  BENCHMARK ("Subtraction") { return a - b; };
}

// Benchmark for multiplication
TEST_CASE ("Benchmark for stoneydsp::int8_t multiplication",
           "[core][types][int8_t][benchmark]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::int8_t a = 12_int8;
  ::stoneydsp::int8_t b = 2_int8;

  BENCHMARK ("Multiplication") { return a * b; };
}

// Benchmark for division
TEST_CASE ("Benchmark for stoneydsp::int8_t division",
           "[core][types][int8_t][benchmark]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::int8_t a = 12_int8;
  ::stoneydsp::int8_t b = 2_int8;

  BENCHMARK ("Division") { return a / b; };
}

// Benchmark for type conversion to int
TEST_CASE ("Benchmark for stoneydsp::int8_t to int conversion",
           "[core][types][int8_t][benchmark]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::int8_t a = 12_int8;

  BENCHMARK ("Conversion to int") { return static_cast<int> (a); };
}

// Benchmark for type conversion to float
TEST_CASE ("Benchmark for stoneydsp::int8_t to float conversion",
           "[core][types][int8_t][benchmark]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::int8_t a = 12_int8;

  BENCHMARK ("Conversion to float")
  {
    return static_cast< ::stoneydsp::float_t> (a);
  };
}

//============================================================================//

#endif // defined(STONEYDSP_BUILD_TEST)

//=========================================================================//EOF
