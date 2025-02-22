/**
 * @file size_t.test.cpp
 * @brief Test suite for stoneydsp::size_t
 * @copyright Copyright (c) 2025
 *
 */

//==============================================================================

#include "stoneydsp/core/types/size.h"

//==============================================================================

#if defined(STONEYDSP_BUILD_TEST) && defined(STONEYDSP_BUILD_CORE)

//==============================================================================

  #include "stoneydsp/core/system/compiler.h" // for `STONEYDSP_PUBLIC_FUNCTION`
  #include "stoneydsp/core/types/math.h"      // for `stoneydsp::float_t`
  #include <algorithm>                        // for `std::sort`
  #include <catch2/benchmark/catch_benchmark.hpp>
  #include <catch2/catch_test_macros.hpp>
  #include <limits>      // for `std::numeric_limits`
  #include <numeric>     // for `std::accumulate`
  #include <sstream>     // for serialization tests
  #include <type_traits> // for `is_signed` and `is_unsigned`
  #include <vector>      // for compatibility tests

//======================================================================//sizeof

TEST_CASE ("sizeof stoneydsp::size_t is same as std::size_t",
           "[sizeof][size_t]")
{
  REQUIRE (sizeof (::stoneydsp::size_t) == sizeof (std::size_t));
}

//=====================================================================//alignof

TEST_CASE ("alignof stoneydsp::size_t is same as std::size_t",
           "[alignof][size_t]")
{
  REQUIRE (alignof (::stoneydsp::size_t) == alignof (std::size_t));
}

//=================================================================//type_traits

TEST_CASE ("Check if types have the correct type traits",
           "[type_traits][size_t]")
{
  REQUIRE (::std::is_integral< ::stoneydsp::size_t>::value);
  REQUIRE (::std::is_unsigned< ::stoneydsp::size_t>::value);
  REQUIRE (::std::is_standard_layout< ::stoneydsp::size_t>::value);
  REQUIRE (::std::is_trivially_copyable< ::stoneydsp::size_t>::value);
}

//==============================================================//numeric_limits

TEST_CASE ("Numeric limits of stoneydsp::size_t", "[numeric_limits][size_t]")
{
  REQUIRE (::stoneydsp::size_t{ 0 }
           == ::std::numeric_limits< ::stoneydsp::size_t>::min ());
  REQUIRE (::stoneydsp::size_t{ std::numeric_limits<std::size_t>::max () }
           == ::std::numeric_limits< ::stoneydsp::size_t>::max ());
}

//==============================================================//special_values

TEST_CASE ("Special values of stoneydsp::size_t",
           "[numeric_limits][special_values][size_t]")
{
  ::stoneydsp::size_t min_val
      = ::std::numeric_limits< ::stoneydsp::size_t>::min ();
  ::stoneydsp::size_t max_val = ::stoneydsp::size_max;
  REQUIRE (min_val == 0); // Minimum value for size_t
  REQUIRE (
      max_val
      == std::numeric_limits<std::size_t>::max ()); // Maximum value for size_t
}

//==================================================================//endianness

TEST_CASE ("Endianness handling for stoneydsp::size_t", "[endianness][size_t]")
{
  ::stoneydsp::size_t value = 0x12345678;
  ::std::uint8_t *bytePtr = reinterpret_cast< ::std::uint8_t *> (&value);

  if (bytePtr[0] == 0x78)
    {
      REQUIRE (true); // Little-endian
    }
  else if (bytePtr[0] == 0x12)
    {
      REQUIRE (true); // Big-endian
    }
  else
    {
      REQUIRE (false); // Unknown endianness
    }
}

//====================================================================//rounding

TEST_CASE ("Rounding behavior of stoneydsp::size_t", "[rounding][size_t]")
{
  ::stoneydsp::float_t a = 1.5f;
  ::stoneydsp::size_t b = static_cast< ::stoneydsp::size_t> (::std::round (a));
  REQUIRE (b == 2); // 1.5 rounded to nearest integer and cast to size_t
}

//==================================================================//arithmetic

TEST_CASE ("Arithmetic operations with stoneydsp::size_t",
           "[arithmetic][size_t]")
{
  ::stoneydsp::size_t a = 15;
  ::stoneydsp::size_t b = 20;
  REQUIRE (a + b == 35); // Addition
  REQUIRE (
      a - b
      == static_cast< ::stoneydsp::size_t> (-5)); // Subtraction (wrap-around)
  REQUIRE (a * b == 300);                         // Multiplication
  REQUIRE (b / a == 1);                           // Division
  REQUIRE (b % a == 5);                           // Modulo
}

//===============================================================//bitwise

TEST_CASE ("Bitwise operations with stoneydsp::size_t", "[bitwise][size_t]")
{
  ::stoneydsp::size_t a = 5; // 0101
  ::stoneydsp::size_t b = 3; // 0011

  REQUIRE ((a & b) == 1); // AND: 0001
  REQUIRE ((a | b) == 7); // OR:  0111
  REQUIRE ((a ^ b) == 6); // XOR: 0110
  REQUIRE ((~a & std::numeric_limits< ::stoneydsp::size_t>::max ())
           == ~static_cast< ::stoneydsp::size_t> (5)); // NOT
}

TEST_CASE ("Shift operations with stoneydsp::size_t", "[bitwise][size_t]")
{
  ::stoneydsp::size_t a = 5; // 0101
  REQUIRE ((a << 1) == 10);  // Left shift: 1010
  REQUIRE ((a >> 1) == 2);   // Right shift: 0010
}

//===============================================================//comparison

TEST_CASE ("Comparison operations with stoneydsp::size_t",
           "[comparison][size_t]")
{
  ::stoneydsp::size_t a = 5;
  ::stoneydsp::size_t b = 3;
  REQUIRE ((a == b) == false);
  REQUIRE ((a != b) == true);
  REQUIRE ((a > b) == true);
  REQUIRE ((a < b) == false);
  REQUIRE ((a >= b) == true);
  REQUIRE ((a <= b) == false);
}

//===============================================================//serialization

TEST_CASE ("Check serialization and deserialization for stoneydsp::size_t",
           "[serialization][size_t]")
{
  ::std::stringstream ss;
  ::stoneydsp::size_t originalValue = 42;
  ::stoneydsp::size_t deserializedValue;

  ss.write (reinterpret_cast<const char *> (&originalValue),
            sizeof (originalValue));
  ss.read (reinterpret_cast<char *> (&deserializedValue),
           sizeof (deserializedValue));

  REQUIRE (originalValue == deserializedValue);
}

//=======================================================//boundary_and_overflow

TEST_CASE ("Boundary and overflow behaviour of stoneydsp::size_t",
           "[boundary][overflow][size_t]")
{
  ::stoneydsp::size_t a = std::numeric_limits< ::stoneydsp::size_t>::max ();
  ::stoneydsp::size_t b = 1;
  REQUIRE (static_cast< ::stoneydsp::size_t> (a + b)
           == 0); // Check overflow wrap-around behaviour
}

//======================================================//boundary_and_underflow

TEST_CASE ("Boundary and underflow behavior of stoneydsp::size_t",
           "[boundary][underflow][size_t]")
{
  ::stoneydsp::size_t a = 0;
  ::stoneydsp::size_t b = 1;
  REQUIRE (static_cast< ::stoneydsp::size_t> (a - b)
           == std::numeric_limits< ::stoneydsp::size_t>::
               max ()); // Check underflow wrap-around behavior
}

//===============================================================//compatibility

TEST_CASE ("Compatibility of stoneydsp::size_t with standard library",
           "[compatibility][size_t]")
{
  ::std::vector< ::stoneydsp::size_t> vec = { 5, 3, 4, 1, 2 };

  // Use std::sort to sort the vector
  ::std::sort (vec.begin (), vec.end ());

  // Verify the vector is sorted
  REQUIRE (vec == ::std::vector< ::stoneydsp::size_t>{ 1, 2, 3, 4, 5 });

  // Use std::accumulate to sum the elements
  ::stoneydsp::size_t sum
      = ::std::accumulate (vec.begin (), vec.end (), ::stoneydsp::size_t (0));

  // Verify the sum is correct
  REQUIRE (sum == 15);
}

//===================================================================//benchmark

// Benchmark for addition
TEST_CASE ("Benchmark for stoneydsp::size_t addition", "[benchmark][size_t]")
{
  ::stoneydsp::size_t a = 1200;
  ::stoneydsp::size_t b = 3400;

  BENCHMARK ("Addition") { return a + b; };
}

// Benchmark for subtraction
TEST_CASE ("Benchmark for stoneydsp::size_t subtraction",
           "[benchmark][size_t]")
{
  ::stoneydsp::size_t a = 3400;
  ::stoneydsp::size_t b = 1200;

  BENCHMARK ("Subtraction") { return a - b; };
}

// Benchmark for multiplication
TEST_CASE ("Benchmark for stoneydsp::size_t multiplication",
           "[benchmark][size_t]")
{
  ::stoneydsp::size_t a = 1200;
  ::stoneydsp::size_t b = 2;

  BENCHMARK ("Multiplication") { return a * b; };
}

// Benchmark for division
TEST_CASE ("Benchmark for stoneydsp::size_t division", "[benchmark][size_t]")
{
  ::stoneydsp::size_t a = 1200;
  ::stoneydsp::size_t b = 2;

  BENCHMARK ("Division") { return a / b; };
}

// Benchmark for type conversion to int
TEST_CASE ("Benchmark for stoneydsp::size_t to int conversion",
           "[benchmark][size_t]")
{
  ::stoneydsp::size_t a = 1200;

  BENCHMARK ("Conversion to int") { return static_cast<int> (a); };
}

// Benchmark for type conversion to float
TEST_CASE ("Benchmark for stoneydsp::size_t to float conversion",
           "[benchmark][size_t]")
{
  ::stoneydsp::size_t a = 1200;

  BENCHMARK ("Conversion to float")
  {
    return static_cast< ::stoneydsp::float_t> (a);
  };
}

//============================================================================//

#endif // defined(STONEYDSP_BUILD_TEST)

//=========================================================================//EOF
