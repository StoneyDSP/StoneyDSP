/**
 * @file ushrt.test.cpp
 * @brief Test suite for stoneydsp::ushrt_t
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

TEST_CASE ("sizeof stoneydsp::ushrt_t is 2 bytes",
           "[core][types][ushrt_t][sizeof]")
{
  REQUIRE (sizeof (::stoneydsp::ushrt_t) == 2UL);
}

//=====================================================================//alignof

TEST_CASE ("alignof stoneydsp::ushrt_t is 2 bytes",
           "[core][types][ushrt_t][alignof]")
{
  REQUIRE (alignof (::stoneydsp::ushrt_t) == 2UL);
}

//=================================================================//type_traits

TEST_CASE ("Check if types are signed or unsigned",
           "[core][types][ushrt_t][type_traits][is_unsigned]")
{
  REQUIRE (::std::is_unsigned< ::stoneydsp::ushrt_t>::value);
}

TEST_CASE ("Is stoneydsp::ushrt_t trivially copyable",
           "[core][types][ushrt_t][type_traits][is_trivially_copyable]")
{
  REQUIRE (::std::is_trivially_copyable< ::stoneydsp::ushrt_t>::value);
}

TEST_CASE ("Is stoneydsp::ushrt_t standard-layout conforming",
           "[core][types][ushrt_t][type_traits][is_standard_layout]")
{
  REQUIRE (::std::is_standard_layout< ::stoneydsp::ushrt_t>::value);
}

//==============================================================//special_values

TEST_CASE ("Numeric limits of stoneydsp::ushrt_t",
           "[core][types][ushrt_t][numeric_limits][special_values]")
{
  // { 0U }
  REQUIRE (::stoneydsp::numeric_limits< ::stoneydsp::ushrt_t>::min ()
           == ::std::numeric_limits< ::stoneydsp::ushrt_t>::min ());
  // // { 65535 }
  REQUIRE (::stoneydsp::numeric_limits< ::stoneydsp::ushrt_t>::max ()
           == ::std::numeric_limits< ::stoneydsp::ushrt_t>::max ());
  // { 0U }
  REQUIRE (::stoneydsp::numeric_limits< ::stoneydsp::ushrt_t>::lowest ()
           == ::std::numeric_limits< ::stoneydsp::ushrt_t>::lowest ());
}

//==============================================================//numeric_limits

TEST_CASE ("Special values of stoneydsp::ushrt_t",
           "[core][types][ushrt_t][numeric_limits]")
{
  ::stoneydsp::ushrt_t min_val
      = ::std::numeric_limits< ::stoneydsp::ushrt_t>::min ();
  ::stoneydsp::ushrt_t max_val
      = ::std::numeric_limits< ::stoneydsp::ushrt_t>::max ();
  REQUIRE (min_val == 0U);     // Minimum value for ushrt_t
  REQUIRE (max_val == 65535U); // Maximum value for ushrt_t
}

//==================================================================//endianness

TEST_CASE ("Endianness handling for stoneydsp::ushrt_t",
           "[core][types][ushrt_t][endianness]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::ushrt_t value = 0x1234_ushrt_t;
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

TEST_CASE ("Rounding behavior of stoneydsp::ushrt_t",
           "[core][types][ushrt_t][rounding]")
{
  ::stoneydsp::float_t a = 1.5f;
  ::stoneydsp::ushrt_t b
      = static_cast< ::stoneydsp::ushrt_t> (::std::round (a));
  REQUIRE (b == 2); // 1.5 rounded to nearest integer and cast to ushrt_t
}

//==================================================================//arithmetic

TEST_CASE ("Arithmetic operations with stoneydsp::ushrt_t",
           "[core][types][ushrt_t][arithmetic]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::ushrt_t a = 1500_ushrt_t;
  ::stoneydsp::ushrt_t b = 2000_ushrt_t;

  REQUIRE (a + b == 3500); // Addition
  REQUIRE (static_cast<int> (a - b)
           == static_cast<int> (-500)); // Subtraction (wrap-around)
  REQUIRE (a * b == 3000000);           // Multiplication
  REQUIRE (b / a == 1);                 // Division
  REQUIRE (b % a == 500);               // Modulo
}

//=====================================================================//bitwise

TEST_CASE ("Bitwise operations with stoneydsp::ushrt_t",
           "[core][types][ushrt_t][bitwise]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::ushrt_t a = 5_ushrt_t; // 0000 0000 0000 0101
  ::stoneydsp::ushrt_t b = 3_ushrt_t; // 0000 0000 0000 0011

  REQUIRE ((a & b) == 1); // AND: 0000 0000 0000 0001
  REQUIRE ((a | b) == 7); // OR:  0000 0000 0000 0111
  REQUIRE ((a ^ b) == 6); // XOR: 0000 0000 0000 0110
  REQUIRE (
      (~a & 0xFFFF)
      == 65530); // NOT: 1111 1111 1111 1010 (considering ushrt_t wrap-around)
}

TEST_CASE ("Shift operations with stoneydsp::ushrt_t",
           "[core][types][ushrt_t][bitwise]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::ushrt_t a = 5_ushrt_t; // 0000 0000 0000 0101

  REQUIRE ((a << 1) == 10); // Left shift: 0000 0000 0000 1010
  REQUIRE ((a >> 1) == 2);  // Right shift: 0000 0000 0000 0010
}

//===============================================================//comparison

TEST_CASE ("Comparison operations with stoneydsp::ushrt_t",
           "[core][types][ushrt_t][comparison]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::ushrt_t a = 5_ushrt_t;
  ::stoneydsp::ushrt_t b = 3_ushrt_t;

  REQUIRE ((a == b) == false);
  REQUIRE ((a != b) == true);
  REQUIRE ((a > b) == true);
  REQUIRE ((a < b) == false);
  REQUIRE ((a >= b) == true);
  REQUIRE ((a <= b) == false);
}

//===============================================================//serialization

TEST_CASE ("Check serialization and deserialization for stoneydsp::ushrt_t",
           "[core][types][ushrt_t][serialization]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::std::stringstream ss;
  ::stoneydsp::ushrt_t originalValue = 42_ushrt_t;
  ::stoneydsp::ushrt_t deserializedValue;

  ss.write (reinterpret_cast<const char *> (&originalValue),
            sizeof (originalValue));
  ss.read (reinterpret_cast<char *> (&deserializedValue),
           sizeof (deserializedValue));

  REQUIRE (originalValue == deserializedValue);
}

//=======================================================//boundary_and_overflow

TEST_CASE ("Boundary and overflow behaviour of stoneydsp::ushrt_t",
           "[core][types][ushrt_t][boundary][overflow]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::ushrt_t a = 65535_ushrt_t;
  ::stoneydsp::ushrt_t b = 1_ushrt_t;

  REQUIRE (static_cast< ::stoneydsp::ushrt_t> (a + b)
           == 0); // Check overflow wrap-around behaviour
}

//======================================================//boundary_and_underflow

TEST_CASE ("Boundary and underflow behavior of stoneydsp::ushrt_t",
           "[core][types][ushrt_t][boundary][underflow]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::ushrt_t a = 0_ushrt_t;
  ::stoneydsp::ushrt_t b = 1_ushrt_t;

  REQUIRE (static_cast< ::stoneydsp::ushrt_t> (a - b)
           == 65535); // Check underflow wrap-around behavior
}

//===============================================================//compatibility

TEST_CASE ("Compatibility of stoneydsp::ushrt_t with standard library",
           "[core][types][ushrt_t][compatibility]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::std::vector< ::stoneydsp::ushrt_t> vec
      = { 5_ushrt_t, 3_ushrt_t, 4_ushrt_t, 1_ushrt_t, 2_ushrt_t };

  // Use std::sort to sort the vector
  ::std::sort (vec.begin (), vec.end ());

  // Verify the vector is sorted
  REQUIRE (vec
           == ::std::vector< ::stoneydsp::ushrt_t>{
               1_ushrt_t, 2_ushrt_t, 3_ushrt_t, 4_ushrt_t, 5_ushrt_t });

  // Use std::accumulate to sum the elements
  ::stoneydsp::ushrt_t sum = ::std::accumulate (
      vec.begin (), vec.end (), ::stoneydsp::ushrt_t (0_ushrt_t));
  // Verify the sum is correct
  REQUIRE (sum == 15);
}

//===================================================================//benchmark

// Benchmark for addition
TEST_CASE ("Benchmark for stoneydsp::ushrt_t addition",
           "[core][types][ushrt_t][benchmark]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::ushrt_t a = 1200_ushrt_t;
  ::stoneydsp::ushrt_t b = 3400_ushrt_t;

  BENCHMARK ("Addition") { return a + b; };
}

// Benchmark for subtraction
TEST_CASE ("Benchmark for stoneydsp::ushrt_t subtraction",
           "[core][types][ushrt_t][benchmark]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::ushrt_t a = 3400_ushrt_t;
  ::stoneydsp::ushrt_t b = 1200_ushrt_t;

  BENCHMARK ("Subtraction") { return a - b; };
}

// Benchmark for multiplication
TEST_CASE ("Benchmark for stoneydsp::ushrt_t multiplication",
           "[core][types][ushrt_t][benchmark]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::ushrt_t a = 1200_ushrt_t;
  ::stoneydsp::ushrt_t b = 2_ushrt_t;

  BENCHMARK ("Multiplication") { return a * b; };
}

// Benchmark for division
TEST_CASE ("Benchmark for stoneydsp::ushrt_t division",
           "[core][types][ushrt_t][benchmark]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::ushrt_t a = 1200_ushrt_t;
  ::stoneydsp::ushrt_t b = 2_ushrt_t;

  BENCHMARK ("Division") { return a / b; };
}

// Benchmark for type conversion to int
TEST_CASE ("Benchmark for stoneydsp::ushrt_t to int conversion",
           "[core][types][ushrt_t][benchmark]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::ushrt_t a = 1200_ushrt_t;

  BENCHMARK ("Conversion to int") { return static_cast<int> (a); };
}

// Benchmark for type conversion to float
TEST_CASE ("Benchmark for stoneydsp::ushrt_t to float conversion",
           "[core][types][ushrt_t][benchmark]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::ushrt_t a = 1200_ushrt_t;

  BENCHMARK ("Conversion to float")
  {
    return static_cast< ::stoneydsp::float_t> (a);
  };
}

//============================================================================//

#endif // defined(STONEYDSP_BUILD_TEST)

//=========================================================================//EOF
