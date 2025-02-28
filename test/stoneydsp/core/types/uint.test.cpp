/**
 * @file uint.test.cpp
 * @brief Test suite for stoneydsp::uint_t
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

TEST_CASE ("sizeof stoneydsp::uint_t is 4 bytes",
           "[core][types][uint_t][sizeof]")
{
  REQUIRE (sizeof (::stoneydsp::uint_t) == 4UL);
}

//=====================================================================//alignof

TEST_CASE ("alignof stoneydsp::uint_t is 4 bytes",
           "[core][types][uint_t][alignof]")
{
  REQUIRE (alignof (::stoneydsp::uint_t) == 4UL);
}

//=================================================================//type_traits

TEST_CASE ("Check if types are signed or unsigned",
           "[core][types][uint_t][type_traits][is_unsigned]")
{
  REQUIRE (::std::is_unsigned< ::stoneydsp::uint_t>::value);
}

TEST_CASE ("Is stoneydsp::uint_t trivially copyable",
           "[core][types][uint_t][type_traits][is_trivially_copyable]")
{
  REQUIRE (::std::is_trivially_copyable< ::stoneydsp::uint_t>::value);
}

TEST_CASE ("Is stoneydsp::uint_t standard-layout conforming",
           "[core][types][uint_t][type_traits][is_standard_layout]")
{
  REQUIRE (::std::is_standard_layout< ::stoneydsp::uint_t>::value);
}

//==============================================================//special_values

TEST_CASE ("Numeric limits of stoneydsp::uint_t",
           "[core][types][uint_t][numeric_limits][special_values]")
{
  // { 0U }
  REQUIRE (::stoneydsp::numeric_limits< ::stoneydsp::uint_t>::min ()
           == ::std::numeric_limits< ::stoneydsp::uint_t>::min ());
  // { 4294967295UL }
  REQUIRE (::stoneydsp::numeric_limits< ::stoneydsp::uint_t>::max ()
           == ::std::numeric_limits< ::stoneydsp::uint_t>::max ());
  // { 0U }
  REQUIRE (::stoneydsp::numeric_limits< ::stoneydsp::uint_t>::lowest ()
           == ::std::numeric_limits< ::stoneydsp::uint_t>::lowest ());
}

//==============================================================//numeric_limits

TEST_CASE ("Special values of stoneydsp::uint_t",
           "[core][types][uint_t][numeric_limits]")
{
  ::stoneydsp::uint_t min_val
      = ::std::numeric_limits< ::stoneydsp::uint_t>::min ();
  ::stoneydsp::uint_t max_val
      = ::std::numeric_limits< ::stoneydsp::uint_t>::max ();
  REQUIRE (min_val == 0U);           // Minimum value for uint_t
  REQUIRE (max_val == 4294967295UL); // Maximum value for uint_t
}

//==================================================================//endianness

TEST_CASE ("Endianness handling for stoneydsp::uint_t",
           "[core][types][uint_t][endianness]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::uint_t value = 0x12345678_uint_t;
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

TEST_CASE ("Rounding behavior of stoneydsp::uint_t",
           "[core][types][uint_t][rounding]")
{
  ::stoneydsp::float_t a = 1.5f;
  ::stoneydsp::uint_t b = static_cast< ::stoneydsp::uint_t> (::std::round (a));
  REQUIRE (b == 2); // 1.5 rounded to nearest integer and cast to uint_t
}

//==================================================================//arithmetic

TEST_CASE ("Arithmetic operations with stoneydsp::uint_t",
           "[core][types][uint_t][arithmetic]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::uint_t a = 1500000000_uint_t;
  ::stoneydsp::uint_t b = 2_uint_t;

  REQUIRE (a + b == 1500000002UL); // Addition
  REQUIRE (a - b == 1499999998UL); // Subtraction
  REQUIRE (a * b == 3000000000UL); // Multiplication
  REQUIRE (b / a == 0);            // Division
  REQUIRE (b % a == 2UL);          // Modulo
}

//===============================================================//bitwise

TEST_CASE ("Bitwise operations with stoneydsp::uint_t",
           "[core][types][uint_t][bitwise]")
{
  using namespace ::stoneydsp::core::types::literals;

  // clang-format off
  ::stoneydsp::uint_t a = 5_uint_t; // 0000 0000 0000 0000 0000 0000 0000 0101
  ::stoneydsp::uint_t b = 3_uint_t; // 0000 0000 0000 0000 0000 0000 0000 0011

  REQUIRE ((a & b) == 1); // AND: 0000 0000 0000 0000 0000 0000 0000 0001
  REQUIRE ((a | b) == 7); // OR:  0000 0000 0000 0000 0000 0000 0000 0111
  REQUIRE ((a ^ b) == 6); // XOR: 0000 0000 0000 0000 0000 0000 0000 0110
  REQUIRE ((~a & 0xFFFFFFFF)
           == 4294967290UL); // NOT: 1111 1111 1111 1111 1111 1111 1111 1010
                             // (considering uint_t wrap-around)
  // clang-format on
}

TEST_CASE ("Shift operations with stoneydsp::uint_t",
           "[core][types][uint_t][bitwise]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::uint_t a = 5_uint_t; // 0000 0000 0000 0000 0000 0000 0000 0101
  REQUIRE ((a << 1)
           == 10); // Left shift: 0000 0000 0000 0000 0000 0000 0000 1010
  REQUIRE ((a >> 1)
           == 2); // Right shift: 0000 0000 0000 0000 0000 0000 0000 0010
}

//===============================================================//comparison

TEST_CASE ("Comparison operations with stoneydsp::uint_t",
           "[core][types][uint_t][comparison]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::uint_t a = 5_uint_t;
  ::stoneydsp::uint_t b = 3_uint_t;

  REQUIRE ((a == b) == false);
  REQUIRE ((a != b) == true);
  REQUIRE ((a > b) == true);
  REQUIRE ((a < b) == false);
  REQUIRE ((a >= b) == true);
  REQUIRE ((a <= b) == false);
}

//===============================================================//serialization

TEST_CASE ("Check serialization and deserialization for stoneydsp::uint_t",
           "[core][types][uint_t][serialization]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::std::stringstream ss;
  ::stoneydsp::uint_t originalValue = 42_uint_t;
  ::stoneydsp::uint_t deserializedValue;

  ss.write (reinterpret_cast<const char *> (&originalValue),
            sizeof (originalValue));
  ss.read (reinterpret_cast<char *> (&deserializedValue),
           sizeof (deserializedValue));

  REQUIRE (originalValue == deserializedValue);
}

//=======================================================//boundary_and_overflow

TEST_CASE ("Boundary and overflow behaviour of stoneydsp::uint_t",
           "[core][types][uint_t][boundary][overflow]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::uint_t a = 4294967295_uint_t;
  ::stoneydsp::uint_t b = 1_uint_t;

  REQUIRE (static_cast< ::stoneydsp::uint_t> (a + b)
           == 0); // Check overflow wrap-around behaviour
}

//======================================================//boundary_and_underflow

TEST_CASE ("Boundary and underflow behavior of stoneydsp::uint_t",
           "[core][types][uint_t][boundary][underflow]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::uint_t a = 0_uint_t;
  ::stoneydsp::uint_t b = 1_uint_t;

  REQUIRE (static_cast< ::stoneydsp::uint_t> (a - b)
           == 4294967295UL); // Check underflow wrap-around behavior
}

//===============================================================//compatibility

TEST_CASE ("Compatibility of stoneydsp::uint_t with standard library",
           "[core][types][uint_t][compatibility]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::std::vector< ::stoneydsp::uint_t> vec
      = { 5_uint_t, 3_uint_t, 4_uint_t, 1_uint_t, 2_uint_t };

  // Use std::sort to sort the vector
  ::std::sort (vec.begin (), vec.end ());

  // Verify the vector is sorted
  REQUIRE (vec
           == ::std::vector< ::stoneydsp::uint_t>{
               1_uint_t, 2_uint_t, 3_uint_t, 4_uint_t, 5_uint_t });

  // Use std::accumulate to sum the elements
  ::stoneydsp::uint_t sum = ::std::accumulate (vec.begin (), vec.end (),
                                               ::stoneydsp::uint_t (0_uint_t));

  // Verify the sum is correct
  REQUIRE (sum == 15);
}

//===================================================================//benchmark

// Benchmark for addition
TEST_CASE ("Benchmark for stoneydsp::uint_t addition",
           "[core][types][uint_t][benchmark]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::uint_t a = 1200_uint_t;
  ::stoneydsp::uint_t b = 3400_uint_t;

  BENCHMARK ("Addition") { return a + b; };
}

// Benchmark for subtraction
TEST_CASE ("Benchmark for stoneydsp::uint_t subtraction",
           "[core][types][uint_t][benchmark]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::uint_t a = 3400_uint_t;
  ::stoneydsp::uint_t b = 1200_uint_t;

  BENCHMARK ("Subtraction") { return a - b; };
}

// Benchmark for multiplication
TEST_CASE ("Benchmark for stoneydsp::uint_t multiplication",
           "[core][types][uint_t][benchmark]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::uint_t a = 1200_uint_t;
  ::stoneydsp::uint_t b = 2_uint_t;

  BENCHMARK ("Multiplication") { return a * b; };
}

// Benchmark for division
TEST_CASE ("Benchmark for stoneydsp::uint_t division",
           "[core][types][uint_t][benchmark]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::uint_t a = 1200_uint_t;
  ::stoneydsp::uint_t b = 2_uint_t;

  BENCHMARK ("Division") { return a / b; };
}

// Benchmark for type conversion to int
TEST_CASE ("Benchmark for stoneydsp::uint_t to int conversion",
           "[core][types][uint_t][benchmark]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::uint_t a = 1200_uint_t;

  BENCHMARK ("Conversion to int") { return static_cast<int> (a); };
}

// Benchmark for type conversion to float
TEST_CASE ("Benchmark for stoneydsp::uint_t to float conversion",
           "[core][types][uint_t][benchmark]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::uint_t a = 1200_uint_t;

  BENCHMARK ("Conversion to float")
  {
    return static_cast< ::stoneydsp::float_t> (a);
  };
}

//============================================================================//

#endif // defined(STONEYDSP_BUILD_TEST)

//=========================================================================//EOF
