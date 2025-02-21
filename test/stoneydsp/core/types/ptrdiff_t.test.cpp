/**
 * @file ptrdiff_t.test.cpp
 * @brief Test suite for stoneydsp::ptrdiff_t
 * @copyright Copyright (c) 2025
 *
 */

//==============================================================================

#include "stoneydsp/core/types/def.h"

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

TEST_CASE ("sizeof stoneydsp::ptrdiff_t is same as std::ptrdiff_t",
           "[sizeof][ptrdiff_t]")
{
  REQUIRE (sizeof (::stoneydsp::ptrdiff_t) == sizeof (std::ptrdiff_t));
}

//=====================================================================//alignof

TEST_CASE ("alignof stoneydsp::ptrdiff_t is same as std::ptrdiff_t",
           "[alignof][ptrdiff_t]")
{
  REQUIRE (alignof (::stoneydsp::ptrdiff_t) == alignof (std::ptrdiff_t));
}

//=================================================================//type_traits

TEST_CASE ("Check if types have the correct type traits",
           "[type_traits][ptrdiff_t]")
{
  REQUIRE (::std::is_integral< ::stoneydsp::ptrdiff_t>::value);
  REQUIRE (::std::is_signed< ::stoneydsp::ptrdiff_t>::value);
  REQUIRE (::std::is_standard_layout< ::stoneydsp::ptrdiff_t>::value);
  REQUIRE (::std::is_trivially_copyable< ::stoneydsp::ptrdiff_t>::value);
}

//==============================================================//special_values

TEST_CASE ("Special values of stoneydsp::ptrdiff_t",
           "[numeric_limits][special_values][ptrdiff_t]")
{
  REQUIRE (::stoneydsp::ptrdiff_min
           == std::numeric_limits<std::ptrdiff_t>::min ()); // Minimum value
                                                            // for ptrdiff_t
  REQUIRE (::stoneydsp::ptrdiff_max
           == std::numeric_limits<std::ptrdiff_t>::max ()); // Maximum value
                                                            // for ptrdiff_t
}

//==============================================================//numeric_limits

TEST_CASE ("Numeric limits of stoneydsp::ptrdiff_t",
           "[numeric_limits][ptrdiff_t]")
{
  REQUIRE (::stoneydsp::ptrdiff_t{ ::stoneydsp::ptrdiff_min }
           == ::std::numeric_limits< ::stoneydsp::ptrdiff_t>::min ());
  REQUIRE (::stoneydsp::ptrdiff_t{ ::stoneydsp::ptrdiff_max }
           == ::std::numeric_limits< ::stoneydsp::ptrdiff_t>::max ());
}

//==================================================================//endianness

TEST_CASE ("Endianness handling for stoneydsp::ptrdiff_t",
           "[endianness][ptrdiff_t]")
{
  ::stoneydsp::ptrdiff_t value = 0x12345678;
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

TEST_CASE ("Rounding behavior of stoneydsp::ptrdiff_t",
           "[rounding][ptrdiff_t]")
{
  ::stoneydsp::float_t a = 1.5f;
  ::stoneydsp::ptrdiff_t b
      = static_cast< ::stoneydsp::ptrdiff_t> (::std::round (a));
  REQUIRE (b == 2); // 1.5 rounded to nearest integer and cast to ptrdiff_t
}

//==================================================================//arithmetic

TEST_CASE ("Arithmetic operations with stoneydsp::ptrdiff_t",
           "[arithmetic][ptrdiff_t]")
{
  ::stoneydsp::ptrdiff_t a = 15;
  ::stoneydsp::ptrdiff_t b = 20;
  REQUIRE (a + b == 35);  // Addition
  REQUIRE (a - b == -5);  // Subtraction
  REQUIRE (a * b == 300); // Multiplication
  REQUIRE (b / a == 1);   // Division
  REQUIRE (b % a == 5);   // Modulo
}

//=====================================================================//bitwise

TEST_CASE ("Bitwise operations with stoneydsp::ptrdiff_t",
           "[bitwise][ptrdiff_t]")
{
  ::stoneydsp::ptrdiff_t a = 5; // 0101
  ::stoneydsp::ptrdiff_t b = 3; // 0011

  REQUIRE ((a & b) == 1); // AND: 0001
  REQUIRE ((a | b) == 7); // OR:  0111
  REQUIRE ((a ^ b) == 6); // XOR: 0110
  REQUIRE (~a == -6);     // NOT:  1111 1111 1111 1010 (two's complement)
}

TEST_CASE ("Shift operations with stoneydsp::ptrdiff_t",
           "[bitwise][ptrdiff_t]")
{
  ::stoneydsp::ptrdiff_t a = 5; // 0101
  REQUIRE ((a << 1) == 10);     // Left shift: 1010
  REQUIRE ((a >> 1) == 2);      // Right shift: 0010
}

//===============================================================//comparison

TEST_CASE ("Comparison operations with stoneydsp::ptrdiff_t",
           "[comparison][ptrdiff_t]")
{
  ::stoneydsp::ptrdiff_t a = 5;
  ::stoneydsp::ptrdiff_t b = 3;
  REQUIRE ((a == b) == false);
  REQUIRE ((a != b) == true);
  REQUIRE ((a > b) == true);
  REQUIRE ((a < b) == false);
  REQUIRE ((a >= b) == true);
  REQUIRE ((a <= b) == false);
}

//===============================================================//serialization

TEST_CASE ("Check serialization and deserialization for stoneydsp::ptrdiff_t",
           "[serialization][ptrdiff_t]")
{
  ::std::stringstream ss;
  ::stoneydsp::ptrdiff_t originalValue = 42;
  ::stoneydsp::ptrdiff_t deserializedValue;

  ss.write (reinterpret_cast<const char *> (&originalValue),
            sizeof (originalValue));
  ss.read (reinterpret_cast<char *> (&deserializedValue),
           sizeof (deserializedValue));

  REQUIRE (originalValue == deserializedValue);
}

//=======================================================//boundary_and_overflow

TEST_CASE ("Boundary and overflow behaviour of stoneydsp::ptrdiff_t",
           "[boundary][overflow][ptrdiff_t]")
{
  ::stoneydsp::ptrdiff_t a
      = std::numeric_limits< ::stoneydsp::ptrdiff_t>::max ();
  ::stoneydsp::ptrdiff_t b = 1;
  REQUIRE (static_cast< ::stoneydsp::ptrdiff_t> (a + b)
           == std::numeric_limits< ::stoneydsp::ptrdiff_t>::
               min ()); // Check overflow wrap-around behaviour
}

//======================================================//boundary_and_underflow

TEST_CASE ("Boundary and underflow behavior of stoneydsp::ptrdiff_t",
           "[boundary][underflow][ptrdiff_t]")
{
  ::stoneydsp::ptrdiff_t a
      = std::numeric_limits< ::stoneydsp::ptrdiff_t>::min ();
  ::stoneydsp::ptrdiff_t b = 1;
  REQUIRE (static_cast< ::stoneydsp::ptrdiff_t> (a - b)
           == std::numeric_limits< ::stoneydsp::ptrdiff_t>::
               max ()); // Check underflow wrap-around behavior
}

//===============================================================//compatibility

TEST_CASE ("Compatibility of stoneydsp::ptrdiff_t with standard library",
           "[compatibility][ptrdiff_t]")
{
  ::std::vector< ::stoneydsp::ptrdiff_t> vec = { 5, 3, 4, 1, 2 };

  // Use std::sort to sort the vector
  ::std::sort (vec.begin (), vec.end ());

  // Verify the vector is sorted
  REQUIRE (vec == ::std::vector< ::stoneydsp::ptrdiff_t>{ 1, 2, 3, 4, 5 });

  // Use std::accumulate to sum the elements
  ::stoneydsp::ptrdiff_t sum = ::std::accumulate (vec.begin (), vec.end (),
                                                  ::stoneydsp::ptrdiff_t (0));

  // Verify the sum is correct
  REQUIRE (sum == 15);
}

//===================================================================//benchmark

// Benchmark for addition
TEST_CASE ("Benchmark for stoneydsp::ptrdiff_t addition",
           "[benchmark][ptrdiff_t]")
{
  ::stoneydsp::ptrdiff_t a = 1200;
  ::stoneydsp::ptrdiff_t b = 3400;

  BENCHMARK ("Addition") { return a + b; };
}

// Benchmark for subtraction
TEST_CASE ("Benchmark for stoneydsp::ptrdiff_t subtraction",
           "[benchmark][ptrdiff_t]")
{
  ::stoneydsp::ptrdiff_t a = 3400;
  ::stoneydsp::ptrdiff_t b = 1200;

  BENCHMARK ("Subtraction") { return a - b; };
}

// Benchmark for multiplication
TEST_CASE ("Benchmark for stoneydsp::ptrdiff_t multiplication",
           "[benchmark][ptrdiff_t]")
{
  ::stoneydsp::ptrdiff_t a = 1200;
  ::stoneydsp::ptrdiff_t b = 2;

  BENCHMARK ("Multiplication") { return a * b; };
}

// Benchmark for division
TEST_CASE ("Benchmark for stoneydsp::ptrdiff_t division",
           "[benchmark][ptrdiff_t]")
{
  ::stoneydsp::ptrdiff_t a = 1200;
  ::stoneydsp::ptrdiff_t b = 2;

  BENCHMARK ("Division") { return a / b; };
}

// Benchmark for type conversion to int
TEST_CASE ("Benchmark for stoneydsp::ptrdiff_t to int conversion",
           "[benchmark][ptrdiff_t]")
{
  ::stoneydsp::ptrdiff_t a = 1200;

  BENCHMARK ("Conversion to int") { return static_cast<int> (a); };
}

// Benchmark for type conversion to float
TEST_CASE ("Benchmark for stoneydsp::ptrdiff_t to float conversion",
           "[benchmark][ptrdiff_t]")
{
  ::stoneydsp::ptrdiff_t a = 1200;

  BENCHMARK ("Conversion to float")
  {
    return static_cast< ::stoneydsp::float_t> (a);
  };
}

//============================================================================//

#endif // defined(STONEYDSP_BUILD_TEST)

//=========================================================================//EOF
