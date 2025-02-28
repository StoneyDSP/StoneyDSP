/**
 * @file uint16.test.cpp
 * @brief Test suite for stoneydsp::uint16_t
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

TEST_CASE ("sizeof stoneydsp::uint16_t is 2 bytes",
           "[core][types][uint16_t][sizeof]")
{
  REQUIRE (sizeof (::stoneydsp::uint16_t) == 2UL);
}

//=====================================================================//alignof

TEST_CASE ("alignof stoneydsp::uint16_t is 2 bytes",
           "[core][types][uint16_t][alignof]")
{
  REQUIRE (alignof (::stoneydsp::uint16_t) == 2UL);
}

//=================================================================//type_traits

TEST_CASE ("Check if types are signed or unsigned",
           "[core][types][uint16_t][type_traits][is_unsigned]")
{
  REQUIRE (::std::is_unsigned< ::stoneydsp::uint16_t>::value);
}

TEST_CASE ("Is stoneydsp::uint16_t trivially copyable",
           "[core][types][uint16_t][type_traits][is_trivially_copyable]")
{
  REQUIRE (::std::is_trivially_copyable< ::stoneydsp::uint16_t>::value);
}

TEST_CASE ("Is stoneydsp::uint16_t standard-layout conforming",
           "[core][types][uint16_t][type_traits][is_standard_layout]")
{
  REQUIRE (::std::is_standard_layout< ::stoneydsp::uint16_t>::value);
}

//==============================================================//special_values

TEST_CASE ("Numeric limits of stoneydsp::uint16_t",
           "[core][types][uint16_t][numeric_limits][special_values]")
{
  // { 0U }
  REQUIRE (::stoneydsp::numeric_limits< ::stoneydsp::uint16_t>::min ()
           == ::std::numeric_limits< ::stoneydsp::uint16_t>::min ());
  // // { 65535 }
  REQUIRE (::stoneydsp::numeric_limits< ::stoneydsp::uint16_t>::max ()
           == ::std::numeric_limits< ::stoneydsp::uint16_t>::max ());
  // { 0U }
  REQUIRE (::stoneydsp::numeric_limits< ::stoneydsp::uint16_t>::lowest ()
           == ::std::numeric_limits< ::stoneydsp::uint16_t>::lowest ());
}

//==============================================================//numeric_limits

TEST_CASE ("Special values of stoneydsp::uint16_t",
           "[core][types][uint16_t][numeric_limits]")
{
  ::stoneydsp::uint16_t min_val
      = ::std::numeric_limits< ::stoneydsp::uint16_t>::min ();
  ::stoneydsp::uint16_t max_val
      = ::std::numeric_limits< ::stoneydsp::uint16_t>::max ();
  REQUIRE (min_val == 0U);     // Minimum value for uint16_t
  REQUIRE (max_val == 65535U); // Maximum value for uint16_t
}

//==================================================================//endianness

TEST_CASE ("Endianness handling for stoneydsp::uint16_t",
           "[core][types][uint16_t][endianness]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::uint16_t value = 0x1234_uint16_t;
  ::std::uint8_t *bytePtr = reinterpret_cast< ::std::uint8_t *> (&value);

  if (bytePtr[0] == 0x34)
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

TEST_CASE ("Rounding behavior of stoneydsp::uint16_t",
           "[core][types][uint16_t][rounding]")
{
  ::stoneydsp::float_t a = 1.5f;
  ::stoneydsp::uint16_t b
      = static_cast< ::stoneydsp::uint16_t> (::std::round (a));
  REQUIRE (b == 2); // 1.5 rounded to nearest integer and cast to uint16_t
}

//==================================================================//arithmetic

TEST_CASE ("Arithmetic operations with stoneydsp::uint16_t",
           "[core][types][uint16_t][arithmetic]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::uint16_t a = 1500_uint16_t;
  ::stoneydsp::uint16_t b = 2000_uint16_t;

  REQUIRE (a + b == 3500); // Addition
  REQUIRE (static_cast<int> (a - b)
           == static_cast<int> (-500)); // Subtraction (wrap-around)
  REQUIRE (a * b == 3000000);           // Multiplication
  REQUIRE (b / a == 1);                 // Division
  REQUIRE (b % a == 500);               // Modulo
}

//=====================================================================//bitwise

TEST_CASE ("Bitwise operations with stoneydsp::uint16_t",
           "[core][types][uint16_t][bitwise]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::uint16_t a = 5_uint16_t; // 0000 0000 0000 0101
  ::stoneydsp::uint16_t b = 3_uint16_t; // 0000 0000 0000 0011

  REQUIRE ((a & b) == 1); // AND: 0000 0000 0000 0001
  REQUIRE ((a | b) == 7); // OR:  0000 0000 0000 0111
  REQUIRE ((a ^ b) == 6); // XOR: 0000 0000 0000 0110
  REQUIRE (
      (~a & 0xFFFF)
      == 65530); // NOT: 1111 1111 1111 1010 (considering uint16_t wrap-around)
}

TEST_CASE ("Shift operations with stoneydsp::uint16_t",
           "[core][types][uint16_t][bitwise]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::uint16_t a = 5_uint16_t; // 0000 0000 0000 0101

  REQUIRE ((a << 1) == 10); // Left shift: 0000 0000 0000 1010
  REQUIRE ((a >> 1) == 2);  // Right shift: 0000 0000 0000 0010
}

//===============================================================//comparison

TEST_CASE ("Comparison operations with stoneydsp::uint16_t",
           "[core][types][uint16_t][comparison]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::uint16_t a = 5_uint16_t;
  ::stoneydsp::uint16_t b = 3_uint16_t;

  REQUIRE ((a == b) == false);
  REQUIRE ((a != b) == true);
  REQUIRE ((a > b) == true);
  REQUIRE ((a < b) == false);
  REQUIRE ((a >= b) == true);
  REQUIRE ((a <= b) == false);
}

//===============================================================//serialization

TEST_CASE ("Check serialization and deserialization for stoneydsp::uint16_t",
           "[core][types][uint16_t][serialization]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::std::stringstream ss;
  ::stoneydsp::uint16_t originalValue = 42_uint16_t;
  ::stoneydsp::uint16_t deserializedValue;

  ss.write (reinterpret_cast<const char *> (&originalValue),
            sizeof (originalValue));
  ss.read (reinterpret_cast<char *> (&deserializedValue),
           sizeof (deserializedValue));

  REQUIRE (originalValue == deserializedValue);
}

//=======================================================//boundary_and_overflow

TEST_CASE ("Boundary and overflow behaviour of stoneydsp::uint16_t",
           "[core][types][uint16_t][boundary][overflow]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::uint16_t a = 65535_uint16_t;
  ::stoneydsp::uint16_t b = 1_uint16_t;

  REQUIRE (static_cast< ::stoneydsp::uint16_t> (a + b)
           == 0); // Check overflow wrap-around behaviour
}

//======================================================//boundary_and_underflow

TEST_CASE ("Boundary and underflow behavior of stoneydsp::uint16_t",
           "[core][types][uint16_t][boundary][underflow]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::uint16_t a = 0_uint16_t;
  ::stoneydsp::uint16_t b = 1_uint16_t;

  REQUIRE (static_cast< ::stoneydsp::uint16_t> (a - b)
           == 65535); // Check underflow wrap-around behavior
}

//===============================================================//compatibility

TEST_CASE ("Compatibility of stoneydsp::uint16_t with standard library",
           "[core][types][uint16_t][compatibility]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::std::vector< ::stoneydsp::uint16_t> vec
      = { 5_uint16_t, 3_uint16_t, 4_uint16_t, 1_uint16_t, 2_uint16_t };

  // Use std::sort to sort the vector
  ::std::sort (vec.begin (), vec.end ());

  // Verify the vector is sorted
  REQUIRE (vec
           == ::std::vector< ::stoneydsp::uint16_t>{
               1_uint16_t, 2_uint16_t, 3_uint16_t, 4_uint16_t, 5_uint16_t });

  // Use std::accumulate to sum the elements
  ::stoneydsp::uint16_t sum = ::std::accumulate (
      vec.begin (), vec.end (), ::stoneydsp::uint16_t (0_uint16_t));
  // Verify the sum is correct
  REQUIRE (sum == 15);
}

//===================================================================//benchmark

// Benchmark for addition
TEST_CASE ("Benchmark for stoneydsp::uint16_t addition",
           "[core][types][uint16_t][benchmark]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::uint16_t a = 1200_uint16_t;
  ::stoneydsp::uint16_t b = 3400_uint16_t;

  BENCHMARK ("Addition") { return a + b; };
}

// Benchmark for subtraction
TEST_CASE ("Benchmark for stoneydsp::uint16_t subtraction",
           "[core][types][uint16_t][benchmark]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::uint16_t a = 3400_uint16_t;
  ::stoneydsp::uint16_t b = 1200_uint16_t;

  BENCHMARK ("Subtraction") { return a - b; };
}

// Benchmark for multiplication
TEST_CASE ("Benchmark for stoneydsp::uint16_t multiplication",
           "[core][types][uint16_t][benchmark]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::uint16_t a = 1200_uint16_t;
  ::stoneydsp::uint16_t b = 2_uint16_t;

  BENCHMARK ("Multiplication") { return a * b; };
}

// Benchmark for division
TEST_CASE ("Benchmark for stoneydsp::uint16_t division",
           "[core][types][uint16_t][benchmark]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::uint16_t a = 1200_uint16_t;
  ::stoneydsp::uint16_t b = 2_uint16_t;

  BENCHMARK ("Division") { return a / b; };
}

// Benchmark for type conversion to int
TEST_CASE ("Benchmark for stoneydsp::uint16_t to int conversion",
           "[core][types][uint16_t][benchmark]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::uint16_t a = 1200_uint16_t;

  BENCHMARK ("Conversion to int") { return static_cast<int> (a); };
}

// Benchmark for type conversion to float
TEST_CASE ("Benchmark for stoneydsp::uint16_t to float conversion",
           "[core][types][uint16_t][benchmark]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::uint16_t a = 1200_uint16_t;

  BENCHMARK ("Conversion to float")
  {
    return static_cast< ::stoneydsp::float_t> (a);
  };
}

//============================================================================//

#endif // defined(STONEYDSP_BUILD_TEST)

//=========================================================================//EOF
