/**
 * @file ullong.test.cpp
 * @brief Test suite for stoneydsp::ullong_t
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

TEST_CASE ("sizeof stoneydsp::ullong_t is 8 bytes",
           "[core][types][ullong_t][sizeof]")
{
  REQUIRE (sizeof (::stoneydsp::ullong_t) == 8UL);
}

//=====================================================================//alignof

TEST_CASE ("alignof stoneydsp::ullong_t is 8 bytes",
           "[core][types][ullong_t][alignof]")
{
  REQUIRE (alignof (::stoneydsp::ullong_t) == 8UL);
}

//=================================================================//type_traits

TEST_CASE ("Check if types are signed or unsigned",
           "[core][types][ullong_t][type_traits][is_unsigned]")
{
  REQUIRE (::std::is_unsigned< ::stoneydsp::ullong_t>::value);
}

TEST_CASE ("Is stoneydsp::ullong_t trivially copyable",
           "[core][types][ullong_t][type_traits][is_trivially_copyable]")
{
  REQUIRE (::std::is_trivially_copyable< ::stoneydsp::ullong_t>::value);
}

TEST_CASE ("Is stoneydsp::ullong_t standard-layout conforming",
           "[core][types][ullong_t][type_traits][is_standard_layout]")
{
  REQUIRE (::std::is_standard_layout< ::stoneydsp::ullong_t>::value);
}

//==============================================================//special_values

TEST_CASE ("Numeric limits of stoneydsp::ullong_t",
           "[core][types][ullong_t][numeric_limits][special_values]")
{
  // { 0U }
  REQUIRE (::stoneydsp::numeric_limits< ::stoneydsp::ullong_t>::min ()
           == ::std::numeric_limits< ::stoneydsp::ullong_t>::min ());

  // { 18446744073709551615UL }
  REQUIRE (::stoneydsp::numeric_limits< ::stoneydsp::ullong_t>::max ()
           == ::std::numeric_limits< ::stoneydsp::ullong_t>::max ());

  // { 0U }
  REQUIRE (::stoneydsp::numeric_limits< ::stoneydsp::ullong_t>::lowest ()
           == ::std::numeric_limits< ::stoneydsp::ullong_t>::lowest ());
}

//==============================================================//numeric_limits

TEST_CASE ("Special values of stoneydsp::ullong_t",
           "[core][types][ullong_t][numeric_limits]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::ullong_t min_val
      = ::std::numeric_limits< ::stoneydsp::ullong_t>::min ();
  ::stoneydsp::ullong_t max_val
      = ::std::numeric_limits< ::stoneydsp::ullong_t>::max ();
  REQUIRE (min_val == 0_ullong_t); // Minimum value for ullong_t
  REQUIRE (max_val
           == 18446744073709551615_ullong_t); // Maximum value for ullong_t
}

//==================================================================//endianness

TEST_CASE ("Endianness handling for stoneydsp::ullong_t",
           "[core][types][ullong_t][endianness]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::ullong_t value = 0x123456789ABCDEF0_ullong_t;
  ::std::uint8_t *bytePtr = reinterpret_cast< ::std::uint8_t *> (&value);

  if (bytePtr[0] == 0xF0)
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

TEST_CASE ("Rounding behavior of stoneydsp::ullong_t",
           "[core][types][ullong_t][rounding]")
{
  ::stoneydsp::float_t a = 1.5f;
  ::stoneydsp::ullong_t b
      = static_cast< ::stoneydsp::ullong_t> (::std::round (a));
  REQUIRE (b == 2); // 1.5 rounded to nearest integer and cast to ullong_t
}

//==================================================================//arithmetic

TEST_CASE ("Arithmetic operations with stoneydsp::ullong_t",
           "[core][types][ullong_t][arithmetic]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::ullong_t a = 1500000000000000000_ullong_t;
  ::stoneydsp::ullong_t b = 2_ullong_t;
  REQUIRE (a + b == 1500000000000000002_ullong_t); // Addition
  REQUIRE (a - b == 1499999999999999998_ullong_t); // Subtraction
  REQUIRE (a * b == 3000000000000000000_ullong_t); // Multiplication
  REQUIRE (b / a == 0_ullong_t);                   // Division
  REQUIRE (b % a == 2_ullong_t);                   // Modulo
}

//===============================================================//bitwise

TEST_CASE ("Bitwise operations with stoneydsp::ullong_t",
           "[core][types][ullong_t][bitwise]")
{
  using namespace ::stoneydsp::core::types::literals;

  // clang-format off
  ::stoneydsp::ullong_t a = 5_ullong_t; // 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0101
  ::stoneydsp::ullong_t b = 3_ullong_t; // 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0011

  REQUIRE ((a & b) == 1); // AND: 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0001
  REQUIRE ((a | b) == 7); // OR:  0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0111
  REQUIRE ((a ^ b) == 6); // XOR: 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0110
  REQUIRE (
      (~a & 0xFFFFFFFFFFFFFFFFUL)
      == 18446744073709551610UL); // NOT: 1111 1111 1111 1111 1111 1111 1111 1111 1111 1111 1111 1111 1111 1111 1111 1010 (considering ullong_t wrap-around)
	// clang-format off
}

TEST_CASE ("Shift operations with stoneydsp::ullong_t", "[core][types][ullong_t][bitwise]")
{
	using namespace ::stoneydsp::core::types::literals;

	// clang-format off
  ::stoneydsp::ullong_t a = 5_ullong_t; // 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0101

	REQUIRE ((a << 1) == 10);  // Left shift: 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 1010
  REQUIRE ((a >> 1) == 2);   // Right shift: 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0010
  // clang-format on
}

//===============================================================//comparison

TEST_CASE ("Comparison operations with stoneydsp::ullong_t",
           "[core][types][ullong_t][comparison]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::ullong_t a = 5_ullong_t;
  ::stoneydsp::ullong_t b = 3_ullong_t;

  REQUIRE ((a == b) == false);
  REQUIRE ((a != b) == true);
  REQUIRE ((a > b) == true);
  REQUIRE ((a < b) == false);
  REQUIRE ((a >= b) == true);
  REQUIRE ((a <= b) == false);
}

//===============================================================//serialization

TEST_CASE ("Check serialization and deserialization for stoneydsp::ullong_t",
           "[core][types][ullong_t][serialization]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::std::stringstream ss;
  ::stoneydsp::ullong_t originalValue = 42_ullong_t;
  ::stoneydsp::ullong_t deserializedValue;

  ss.write (reinterpret_cast<const char *> (&originalValue),
            sizeof (originalValue));
  ss.read (reinterpret_cast<char *> (&deserializedValue),
           sizeof (deserializedValue));

  REQUIRE (originalValue == deserializedValue);
}

//=======================================================//boundary_and_overflow

TEST_CASE ("Boundary and overflow behaviour of stoneydsp::ullong_t",
           "[core][types][ullong_t][boundary][overflow]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::ullong_t a = 18446744073709551615_ullong_t;
  ::stoneydsp::ullong_t b = 1_ullong_t;

  REQUIRE (static_cast< ::stoneydsp::ullong_t> (a + b)
           == 0_ullong_t); // Check overflow wrap-around behaviour
}

//======================================================//boundary_and_underflow

TEST_CASE ("Boundary and underflow behavior of stoneydsp::ullong_t",
           "[core][types][ullong_t][boundary][underflow]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::ullong_t a = 0_ullong_t;
  ::stoneydsp::ullong_t b = 1_ullong_t;

  REQUIRE (static_cast< ::stoneydsp::ullong_t> (a - b)
           == 18446744073709551615_ullong_t); // Check underflow wrap-around
                                              // behavior
}

//===============================================================//compatibility

TEST_CASE ("Compatibility of stoneydsp::ullong_t with standard library",
           "[core][types][ullong_t][compatibility]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::std::vector< ::stoneydsp::ullong_t> vec
      = { 5_ullong_t, 3_ullong_t, 4_ullong_t, 1_ullong_t, 2_ullong_t };

  // Use std::sort to sort the vector
  ::std::sort (vec.begin (), vec.end ());

  // Verify the vector is sorted
  REQUIRE (vec
           == ::std::vector< ::stoneydsp::ullong_t>{
               1_ullong_t, 2_ullong_t, 3_ullong_t, 4_ullong_t, 5_ullong_t });

  // Use std::accumulate to sum the elements
  ::stoneydsp::ullong_t sum = ::std::accumulate (
      vec.begin (), vec.end (), ::stoneydsp::ullong_t (0_ullong_t));

  // Verify the sum is correct
  REQUIRE (sum == 15_ullong_t);
}

//===================================================================//benchmark

// Benchmark for addition
TEST_CASE ("Benchmark for stoneydsp::ullong_t addition",
           "[core][types][ullong_t][benchmark]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::ullong_t a = 1200_ullong_t;
  ::stoneydsp::ullong_t b = 3400_ullong_t;

  BENCHMARK ("Addition") { return a + b; };
}

// Benchmark for subtraction
TEST_CASE ("Benchmark for stoneydsp::ullong_t subtraction",
           "[core][types][ullong_t][benchmark]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::ullong_t a = 3400_ullong_t;
  ::stoneydsp::ullong_t b = 1200_ullong_t;

  BENCHMARK ("Subtraction") { return a - b; };
}

// Benchmark for multiplication
TEST_CASE ("Benchmark for stoneydsp::ullong_t multiplication",
           "[core][types][ullong_t][benchmark]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::ullong_t a = 1200_ullong_t;
  ::stoneydsp::ullong_t b = 2_ullong_t;

  BENCHMARK ("Multiplication") { return a * b; };
}

// Benchmark for division
TEST_CASE ("Benchmark for stoneydsp::ullong_t division",
           "[core][types][ullong_t][benchmark]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::ullong_t a = 1200_ullong_t;
  ::stoneydsp::ullong_t b = 2_ullong_t;

  BENCHMARK ("Division") { return a / b; };
}

// Benchmark for type conversion to int
TEST_CASE ("Benchmark for stoneydsp::ullong_t to int conversion",
           "[core][types][ullong_t][benchmark]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::ullong_t a = 1200_ullong_t;

  BENCHMARK ("Conversion to int") { return static_cast<int> (a); };
}

// Benchmark for type conversion to float
TEST_CASE ("Benchmark for stoneydsp::ullong_t to float conversion",
           "[core][types][ullong_t][benchmark]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::ullong_t a = 1200_ullong_t;

  BENCHMARK ("Conversion to float")
  {
    return static_cast< ::stoneydsp::float_t> (a);
  };
}

//============================================================================//

#endif // defined(STONEYDSP_BUILD_TEST)

//=========================================================================//EOF
