/**
 * @file uint8_t.test.cpp
 * @brief Test suite for stoneydsp::uint8_t
 * @copyright Copyright (c) 2025
 *
 */

//==============================================================================

#include "stoneydsp/core/core.h"

//==============================================================================

#if defined(STONEYDSP_BUILD_TEST) && defined(STONEYDSP_BUILD_CORE)

//==============================================================================

  #include "stoneydsp/core/system/compiler.h" // for `STONEYDSP_PUBLIC_FUNCTION`
  #include "stoneydsp/core/types/math.h"      // for `stoneydsp::float_t`
  #include <algorithm>                        // for `std::sort`
  #include <catch2/benchmark/catch_benchmark.hpp> // for `BENCHMARK`
  #include <catch2/catch_test_macros.hpp>         // for `TEST_CASE
  #include <limits>                               // for `std::numeric_limits`
  #include <numeric>                              // for `std::accumulate`
  #include <sstream>                              // for serialization tests
  #include <type_traits> // for `is_signed` and `is_unsigned`
  #include <vector>      // for compatibility tests

//======================================================================//sizeof

TEST_CASE ("sizeof stoneydsp::uint8_t is 1 byte",
           "[core][types][uint8_t][sizeof]")
{
  REQUIRE (sizeof (::stoneydsp::uint8_t) == 1UL);
}

//=====================================================================//alignof

TEST_CASE ("alignof stoneydsp::uint8_t is 1 byte",
           "[core][types][uint8_t][alignof]")
{
  REQUIRE (alignof (::stoneydsp::uint8_t) == 1UL);
}

//=================================================================//type_traits

TEST_CASE ("Check if types are signed or unsigned",
           "[core][types][uint8_t][type_traits][is_unsigned]")
{
  REQUIRE (::std::is_unsigned< ::stoneydsp::uint8_t>::value);
}

TEST_CASE ("Is stoneydsp::uint8_t trivially copyable",
           "[core][types][uint8_t][type_traits][is_trivially_copyable]")
{
  REQUIRE (::std::is_trivially_copyable< ::stoneydsp::uint8_t>::value);
}

TEST_CASE ("Is stoneydsp::uint8_t standard-layout conforming",
           "[core][types][uint8_t][type_traits][is_standard_layout]")
{
  REQUIRE (::std::is_standard_layout< ::stoneydsp::uint8_t>::value);
}

//==============================================================//special_values

TEST_CASE ("Numeric limits of stoneydsp::uint8_t",
           "[core][types][uint8_t][numeric_limits][special_values]")
{
  REQUIRE (::stoneydsp::uint8_t{ 0U }
           == ::std::numeric_limits< ::stoneydsp::uint8_t>::min ());
  REQUIRE (::stoneydsp::uint8_max // { 255 }
           == ::std::numeric_limits< ::stoneydsp::uint8_t>::max ());
}

//==============================================================//numeric_limits

TEST_CASE ("Special values of stoneydsp::uint8_t",
           "[core][types][uint8_t][numeric_limits]")
{
  ::stoneydsp::uint8_t min_val
      = ::std::numeric_limits< ::stoneydsp::uint8_t>::min ();
  ::stoneydsp::uint8_t max_val
      = ::std::numeric_limits< ::stoneydsp::uint8_t>::max ();
  REQUIRE (min_val == 0U);   // Minimum value for uint8_t
  REQUIRE (max_val == 255U); // Maximum value for uint8_t
}

//==================================================================//endianness

TEST_CASE ("Endianness handling for stoneydsp::uint8_t",
           "[core][types][uint8_t][endianness]")
{
  ::stoneydsp::uint8_t value = 0x12;
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

TEST_CASE ("Rounding behavior of stoneydsp::uint8_t",
           "[core][types][uint8_t][rounding]")
{
  ::stoneydsp::float_t a = 1.5f;
  ::stoneydsp::uint8_t b
      = static_cast< ::stoneydsp::uint8_t> (::std::round (a));
  REQUIRE (b == 2); // 1.5 rounded to nearest integer and cast to uint8_t
}

//==================================================================//arithmetic

TEST_CASE ("Arithmetic operations with stoneydsp::uint8_t",
           "[core][types][uint8_t][arithmetic]")
{
  ::stoneydsp::uint8_t a = 15;
  ::stoneydsp::uint8_t b = 20;
  REQUIRE (a + b == 35); // Addition
  REQUIRE (static_cast<int> (a - b)
           == static_cast<int> (-5)); // Subtraction (wrap-around)
  REQUIRE (a * b == 300);             // Multiplication
  REQUIRE (b / a == 1);               // Division
  REQUIRE (b % a == 5);               // Modulo
}
//=====================================================================//bitwise

TEST_CASE ("Bitwise operations with stoneydsp::uint8_t",
           "[core][types][uint8_t][bitwise]")
{
  ::stoneydsp::uint8_t a = 5; // 0101
  ::stoneydsp::uint8_t b = 3; // 0011

  REQUIRE ((a & b) == 1); // AND: 0001
  REQUIRE ((a | b) == 7); // OR: 0111
  REQUIRE ((a ^ b) == 6); // XOR: 0110
  REQUIRE ((~a & 0xFF)
           == 250); // NOT: 1111_1010 (considering uint8_t wrap-around)
}

TEST_CASE ("Shift operations with stoneydsp::uint8_t",
           "[core][types][uint8_t][bitwise]")
{
  ::stoneydsp::uint8_t a = 5; // 0101
  REQUIRE ((a << 1) == 10);   // Left shift: 1010
  REQUIRE ((a >> 1) == 2);    // Right shift: 0010
}

//==================================================================//comparison

TEST_CASE ("Comparison operations with stoneydsp::uint8_t",
           "[core][types][uint8_t][comparison]")
{
  ::stoneydsp::uint8_t a = 5;
  ::stoneydsp::uint8_t b = 3;
  REQUIRE ((a == b) == false);
  REQUIRE ((a != b) == true);
  REQUIRE ((a > b) == true);
  REQUIRE ((a < b) == false);
  REQUIRE ((a >= b) == true);
  REQUIRE ((a <= b) == false);
}

//===============================================================//serialization

TEST_CASE ("Check serialization and deserialization for stoneydsp::uint8_t",
           "[core][types][uint8_t][serialization]")
{
  ::std::stringstream ss;
  ::stoneydsp::uint8_t originalValue = 42;
  ::stoneydsp::uint8_t deserializedValue;

  ss.write (reinterpret_cast<const char *> (&originalValue),
            sizeof (originalValue));
  ss.read (reinterpret_cast<char *> (&deserializedValue),
           sizeof (deserializedValue));

  REQUIRE (originalValue == deserializedValue);
}

//=======================================================//boundary_and_overflow

TEST_CASE ("Boundary and overflow behaviour of stoneydsp::uint8_t",
           "[core][types][uint8_t][boundary][overflow]")
{
  ::stoneydsp::uint8_t a = 255;
  ::stoneydsp::uint8_t b = 1;
  REQUIRE (static_cast< ::stoneydsp::uint8_t> (a + b)
           == 0); // Check overflow wrap-around behaviour
}

//======================================================//boundary_and_underflow

TEST_CASE ("Boundary and underflow behavior of stoneydsp::uint8_t",
           "[core][types][uint8_t][boundary][underflow]")
{
  ::stoneydsp::uint8_t a = 0;
  ::stoneydsp::uint8_t b = 1;
  REQUIRE (static_cast< ::stoneydsp::uint8_t> (a - b)
           == 255); // Check underflow wrap-around behavior
}

//===============================================================//compatibility

TEST_CASE ("Compatibility of stoneydsp::uint8_t with standard library",
           "[core][types][uint8_t][compatibility]")
{
  ::std::vector< ::stoneydsp::uint8_t> vec = { 5, 3, 4, 1, 2 };

  // Use std::sort to sort the vector
  ::std::sort (vec.begin (), vec.end ());

  // Verify the vector is sorted
  REQUIRE (vec == ::std::vector< ::stoneydsp::uint8_t>{ 1, 2, 3, 4, 5 });

  // Use std::accumulate to sum the elements
  ::stoneydsp::uint8_t sum
      = ::std::accumulate (vec.begin (), vec.end (), ::stoneydsp::uint8_t (0));

  // Verify the sum is correct
  REQUIRE (sum == 15);
}

//===================================================================//benchmark

// Benchmark for addition
TEST_CASE ("Benchmark for stoneydsp::uint8_t addition",
           "[core][types][uint8_t][benchmark]")
{
  ::stoneydsp::uint8_t a = 12;
  ::stoneydsp::uint8_t b = 34;

  BENCHMARK ("Addition") { return a + b; };
}

// Benchmark for subtraction
TEST_CASE ("Benchmark for stoneydsp::uint8_t subtraction",
           "[core][types][uint8_t][benchmark]")
{
  ::stoneydsp::uint8_t a = 34;
  ::stoneydsp::uint8_t b = 12;

  BENCHMARK ("Subtraction") { return a - b; };
}

// Benchmark for multiplication
TEST_CASE ("Benchmark for stoneydsp::uint8_t multiplication",
           "[core][types][uint8_t][benchmark]")
{
  ::stoneydsp::uint8_t a = 12;
  ::stoneydsp::uint8_t b = 2;

  BENCHMARK ("Multiplication") { return a * b; };
}

// Benchmark for division
TEST_CASE ("Benchmark for stoneydsp::uint8_t division",
           "[core][types][uint8_t][benchmark]")
{
  ::stoneydsp::uint8_t a = 12;
  ::stoneydsp::uint8_t b = 2;

  BENCHMARK ("Division") { return a / b; };
}

// Benchmark for type conversion to int
TEST_CASE ("Benchmark for stoneydsp::uint8_t to int conversion",
           "[core][types][uint8_t][benchmark]")
{
  ::stoneydsp::uint8_t a = 12;

  BENCHMARK ("Conversion to int") { return static_cast<int> (a); };
}

// Benchmark for type conversion to float
TEST_CASE ("Benchmark for stoneydsp::uint8_t to float conversion",
           "[core][types][uint8_t][benchmark]")
{
  ::stoneydsp::uint8_t a = 12;

  BENCHMARK ("Conversion to float")
  {
    return static_cast< ::stoneydsp::float_t> (a);
  };
}

//============================================================================//

#endif // defined(STONEYDSP_BUILD_TEST)

//=========================================================================//EOF
