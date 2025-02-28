/**
 * @file int32.test.cpp
 * @brief Test suite for stoneydsp::int32_t
 * @copyright Copyright (c) 2025
 *
 */

//==============================================================================

#include "stoneydsp/core/system/types.h"

//==============================================================================

#if defined(STONEYDSP_BUILD_TEST) && defined(STONEYDSP_BUILD_CORE)

//==============================================================================

  #include "stoneydsp/core/system/compiler.h" // for `STONEYDSP_PUBLIC_FUNCTION`
  #include <algorithm>                        // for `std::sort`
  #include <catch2/benchmark/catch_benchmark.hpp> //
  #include <catch2/catch_test_macros.hpp>         //
  #include <limits>                               // for `std::numeric_limits`
  #include <numeric>                              // for `std::accumulate`
  #include <sstream>                              // for serialization tests
  #include <type_traits> // for `is_signed` and `is_unsigned`
  #include <vector>      // for compatibility tests

//======================================================================//sizeof

TEST_CASE ("sizeof stoneydsp::int32_t is 4 bytes",
           "[core][types][int32_t][sizeof]")
{
  REQUIRE (sizeof (::stoneydsp::int32_t) == 4UL);
}

//=====================================================================//alignof

TEST_CASE ("alignof stoneydsp::int32_t is 4 bytes",
           "[core][types][int32_t][alignof]")
{
  REQUIRE (alignof (::stoneydsp::int32_t) == 4UL);
}

//=================================================================//type_traits

TEST_CASE ("Check if types are signed or unsigned",
           "[core][types][int32_t][type_traits][is_signed]")
{
  REQUIRE (::std::is_signed< ::stoneydsp::int32_t>::value);
}

TEST_CASE ("Is stoneydsp::int32_t trivially copyable",
           "[core][types][int32_t][type_traits][is_trivially_copyable]")
{
  REQUIRE (::std::is_trivially_copyable< ::stoneydsp::int32_t>::value);
}

TEST_CASE ("Is stoneydsp::int32_t standard-layout conforming",
           "[core][types][int32_t][type_traits][is_standard_layout]")
{
  REQUIRE (::std::is_standard_layout< ::stoneydsp::int32_t>::value);
}

//==============================================================//special_values

TEST_CASE ("Numeric limits of stoneydsp::int32_t",
           "[core][types][int32_t][numeric_limits][special_values]")
{
  // { -2147483648 }
  REQUIRE (::stoneydsp::numeric_limits< ::stoneydsp::int32_t>::min ()
           == ::std::numeric_limits< ::stoneydsp::int32_t>::min ());
  // { 2147483647 }
  REQUIRE (::stoneydsp::numeric_limits< ::stoneydsp::int32_t>::max ()
           == ::std::numeric_limits< ::stoneydsp::int32_t>::max ());
  // { -2147483648 }
  REQUIRE (::stoneydsp::numeric_limits< ::stoneydsp::int32_t>::lowest ()
           == ::std::numeric_limits< ::stoneydsp::int32_t>::lowest ());
}

//==============================================================//numeric_limits

TEST_CASE ("Special values of stoneydsp::int32_t",
           "[core][types][int32_t][numeric_limits]")
{
  ::stoneydsp::int32_t min_val
      = ::std::numeric_limits< ::stoneydsp::int32_t>::min ();
  ::stoneydsp::int32_t max_val
      = ::std::numeric_limits< ::stoneydsp::int32_t>::max ();
  REQUIRE (min_val == -2147483648); // Minimum value for int32_t
  REQUIRE (max_val == 2147483647);  // Maximum value for int32_t
}

//==================================================================//endianness

TEST_CASE ("Endianness handling for stoneydsp::int32_t",
           "[core][types][int32_t][endianness]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::int32_t value = 0x12345678_int32_t;
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

TEST_CASE ("Rounding behavior of stoneydsp::int32_t",
           "[core][types][int32_t][rounding]")
{
  ::stoneydsp::float_t a = 1.5f;
  ::stoneydsp::int32_t b
      = static_cast< ::stoneydsp::int32_t> (::std::round (a));
  REQUIRE (b == 2); // 1.5 rounded to nearest integer and cast to int32_t
}

//==================================================================//arithmetic

TEST_CASE ("Arithmetic operations with stoneydsp::int32_t",
           "[core][types][int32_t][arithmetic]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::int32_t a = 15000_int32_t;
  ::stoneydsp::int32_t b = 20000_int32_t;

  REQUIRE (a + b == 35000);     // Addition
  REQUIRE (a - b == -5000);     // Subtraction
  REQUIRE (a * b == 300000000); // Multiplication
  REQUIRE (b / a == 1);         // Division
  REQUIRE (b % a == 5000);      // Modulo
}

//=====================================================================//bitwise

TEST_CASE ("Bitwise operations with stoneydsp::int32_t",
           "[core][types][int32_t][bitwise]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::int32_t a
      = 5_int32_t; // 0000 0000 0000 0000 0000 0000 0000 0101
  ::stoneydsp::int32_t b
      = 3_int32_t; // 0000 0000 0000 0000 0000 0000 0000 0011

  REQUIRE ((a & b) == 1); // AND: 0000 0000 0000 0000 0000 0000 0000 0001
  REQUIRE ((a | b) == 7); // OR:  0000 0000 0000 0000 0000 0000 0000 0111
  REQUIRE ((a ^ b) == 6); // XOR: 0000 0000 0000 0000 0000 0000 0000 0110
  REQUIRE (~a == -6);     // NOT: considering wrap-around for int32_t
}

TEST_CASE ("Shift operations with stoneydsp::int32_t",
           "[core][types][int32_t][bitwise]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::int32_t a
      = 5_int32_t; // 0000 0000 0000 0000 0000 0000 0000 0101

  REQUIRE ((a << 1)
           == 10); // Left shift: 0000 0000 0000 0000 0000 0000 0000 1010
  REQUIRE ((a >> 1)
           == 2); // Right shift: 0000 0000 0000 0000 0000 0000 0000 0010
}

//==================================================================//comparison

TEST_CASE ("Comparison operations with stoneydsp::int32_t",
           "[core][types][int32_t][comparison]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::int32_t a = 5_int32_t;
  ::stoneydsp::int32_t b = 3_int32_t;

  REQUIRE ((a == b) == false);
  REQUIRE ((a != b) == true);
  REQUIRE ((a > b) == true);
  REQUIRE ((a < b) == false);
  REQUIRE ((a >= b) == true);
  REQUIRE ((a <= b) == false);
}

//===============================================================//serialization

TEST_CASE ("Check serialization and deserialization for stoneydsp::int32_t",
           "[core][types][int32_t][serialization]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::std::stringstream ss;
  ::stoneydsp::int32_t originalValue = 42_int32_t;
  ::stoneydsp::int32_t deserializedValue;

  ss.write (reinterpret_cast<const char *> (&originalValue),
            sizeof (originalValue));
  ss.read (reinterpret_cast<char *> (&deserializedValue),
           sizeof (deserializedValue));

  REQUIRE (originalValue == deserializedValue);
}

//=======================================================//boundary_and_overflow

TEST_CASE ("Boundary and overflow behaviour of stoneydsp::int32_t",
           "[core][types][int32_t][boundary][overflow]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::int32_t a = 2147483647_int32_t;
  ::stoneydsp::int32_t b = 1_int32_t;

  REQUIRE (static_cast< ::stoneydsp::int32_t> (a + b)
           == -2147483648); // Check overflow wrap-around behaviour
}

//======================================================//boundary_and_underflow

TEST_CASE ("Boundary and underflow behavior of stoneydsp::int32_t",
           "[core][types][int32_t][boundary][underflow]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::int32_t a = -2147483647_int32_t - 1_int32_t; // _int32;
  ::stoneydsp::int32_t b = 1_int32_t;

  REQUIRE (static_cast< ::stoneydsp::int32_t> (a - b)
           == 2147483647); // Check underflow wrap-around behavior
}

//===============================================================//compatibility

TEST_CASE ("Compatibility of stoneydsp::int32_t with standard library",
           "[core][types][int32_t][compatibility]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::std::vector< ::stoneydsp::int32_t> vec
      = { 5_int32_t, 3_int32_t, 4_int32_t, 1_int32_t, 2_int32_t };

  // Use std::sort to sort the vector
  ::std::sort (vec.begin (), vec.end ());

  // Verify the vector is sorted
  REQUIRE (vec
           == ::std::vector< ::stoneydsp::int32_t>{
               1_int32_t, 2_int32_t, 3_int32_t, 4_int32_t, 5_int32_t });

  // Use std::accumulate to sum the elements
  ::stoneydsp::int32_t sum = ::std::accumulate (
      vec.begin (), vec.end (), ::stoneydsp::int32_t (0_int32_t));

  // Verify the sum is correct
  REQUIRE (sum == 15);
}

//===================================================================//benchmark

// Benchmark for addition
TEST_CASE ("Benchmark for stoneydsp::int32_t addition",
           "[core][types][int32_t][benchmark]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::int32_t a = 1200_int32_t;
  ::stoneydsp::int32_t b = 3400_int32_t;

  BENCHMARK ("Addition") { return a + b; };
}

// Benchmark for subtraction
TEST_CASE ("Benchmark for stoneydsp::int32_t subtraction",
           "[core][types][int32_t][benchmark]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::int32_t a = 3400_int32_t;
  ::stoneydsp::int32_t b = 1200_int32_t;

  BENCHMARK ("Subtraction") { return a - b; };
}

// Benchmark for multiplication
TEST_CASE ("Benchmark for stoneydsp::int32_t multiplication",
           "[core][types][int32_t][benchmark]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::int32_t a = 1200_int32_t;
  ::stoneydsp::int32_t b = 2_int32_t;

  BENCHMARK ("Multiplication") { return a * b; };
}

// Benchmark for division
TEST_CASE ("Benchmark for stoneydsp::int32_t division",
           "[core][types][int32_t][benchmark]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::int32_t a = 1200_int32_t;
  ::stoneydsp::int32_t b = 2_int32_t;

  BENCHMARK ("Division") { return a / b; };
}

// Benchmark for type conversion to int
TEST_CASE ("Benchmark for stoneydsp::int32_t to int conversion",
           "[core][types][int32_t][benchmark]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::int32_t a = 1200_int32_t;

  BENCHMARK ("Conversion to int") { return static_cast<int> (a); };
}

// Benchmark for type conversion to float
TEST_CASE ("Benchmark for stoneydsp::int32_t to float conversion",
           "[core][types][int32_t][benchmark]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::int32_t a = 1200_int32_t;

  BENCHMARK ("Conversion to float")
  {
    return static_cast< ::stoneydsp::float_t> (a);
  };
}

//============================================================================//

#endif // defined(STONEYDSP_BUILD_TEST)

//=========================================================================//EOF
