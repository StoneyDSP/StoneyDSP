/**
 * @file uint64.test.cpp
 * @brief Test suite for stoneydsp::uint64_t
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

TEST_CASE ("sizeof stoneydsp::uint64_t is 8 bytes",
           "[core][types][uint64_t][sizeof]")
{
  REQUIRE (sizeof (::stoneydsp::uint64_t) == 8UL);
}

//=====================================================================//alignof

TEST_CASE ("alignof stoneydsp::uint64_t is 8 bytes",
           "[core][types][uint64_t][alignof]")
{
  REQUIRE (alignof (::stoneydsp::uint64_t) == 8UL);
}

//=================================================================//type_traits

TEST_CASE ("Check if types are signed or unsigned",
           "[core][types][uint64_t][type_traits][is_unsigned]")
{
  REQUIRE (::std::is_unsigned< ::stoneydsp::uint64_t>::value);
}

TEST_CASE ("Is stoneydsp::uint64_t trivially copyable",
           "[core][types][uint64_t][type_traits][is_trivially_copyable]")
{
  REQUIRE (::std::is_trivially_copyable< ::stoneydsp::uint64_t>::value);
}

TEST_CASE ("Is stoneydsp::uint64_t standard-layout conforming",
           "[core][types][uint64_t][type_traits][is_standard_layout]")
{
  REQUIRE (::std::is_standard_layout< ::stoneydsp::uint64_t>::value);
}

//==============================================================//special_values

TEST_CASE ("Numeric limits of stoneydsp::uint64_t",
           "[core][types][uint64_t][numeric_limits][special_values]")
{
  // { 0U }
  REQUIRE (::stoneydsp::numeric_limits< ::stoneydsp::uint64_t>::min ()
           == ::std::numeric_limits< ::stoneydsp::uint64_t>::min ());

  // { 18446744073709551615ULL }
  REQUIRE (::stoneydsp::numeric_limits< ::stoneydsp::uint64_t>::max ()
           == ::std::numeric_limits< ::stoneydsp::uint64_t>::max ());
					 
  // { 0U }
  REQUIRE (::stoneydsp::numeric_limits< ::stoneydsp::uint64_t>::lowest ()
           == ::std::numeric_limits< ::stoneydsp::uint64_t>::lowest ());
}

//==============================================================//numeric_limits

TEST_CASE ("Special values of stoneydsp::uint64_t",
           "[core][types][uint64_t][numeric_limits]")
{
  ::stoneydsp::uint64_t min_val
      = ::std::numeric_limits< ::stoneydsp::uint64_t>::min ();
  ::stoneydsp::uint64_t max_val
      = ::std::numeric_limits< ::stoneydsp::uint64_t>::max ();
  REQUIRE (min_val == 0U);                      // Minimum value for uint64_t
  REQUIRE (max_val == 18446744073709551615ULL); // Maximum value for uint64_t
}

//==================================================================//endianness

TEST_CASE ("Endianness handling for stoneydsp::uint64_t",
           "[core][types][uint64_t][endianness]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::uint64_t value = 0x123456789ABCDEF0_uint64_t;
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

TEST_CASE ("Rounding behavior of stoneydsp::uint64_t",
           "[core][types][uint64_t][rounding]")
{
  ::stoneydsp::float_t a = 1.5f;
  ::stoneydsp::uint64_t b
      = static_cast< ::stoneydsp::uint64_t> (::std::round (a));
  REQUIRE (b == 2); // 1.5 rounded to nearest integer and cast to uint64_t
}

//==================================================================//arithmetic

TEST_CASE ("Arithmetic operations with stoneydsp::uint64_t",
           "[core][types][uint64_t][arithmetic]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::uint64_t a = 1500000000000000000_uint64_t;
  ::stoneydsp::uint64_t b = 2_uint64_t;
  REQUIRE (a + b == 1500000000000000002ULL); // Addition
  REQUIRE (a - b == 1499999999999999998ULL); // Subtraction
  REQUIRE (a * b == 3000000000000000000ULL); // Multiplication
  REQUIRE (b / a == 0);                      // Division
  REQUIRE (b % a == 2ULL);                   // Modulo
}

//===============================================================//bitwise

TEST_CASE ("Bitwise operations with stoneydsp::uint64_t",
           "[core][types][uint64_t][bitwise]")
{
  using namespace ::stoneydsp::core::types::literals;

  // clang-format off
  ::stoneydsp::uint64_t a = 5_uint64_t; // 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0101
  ::stoneydsp::uint64_t b = 3_uint64_t; // 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0011

  REQUIRE ((a & b) == 1); // AND: 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0001
  REQUIRE ((a | b) == 7); // OR:  0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0111
  REQUIRE ((a ^ b) == 6); // XOR: 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0110
  REQUIRE (
      (~a & 0xFFFFFFFFFFFFFFFFULL)
      == 18446744073709551610ULL); // NOT: 1111 1111 1111 1111 1111 1111 1111 1111 1111 1111 1111 1111 1111 1111 1111 1010 (considering uint64_t wrap-around)
	// clang-format off
}

TEST_CASE ("Shift operations with stoneydsp::uint64_t", "[core][types][uint64_t][bitwise]")
{
	using namespace ::stoneydsp::core::types::literals;

	// clang-format off
  ::stoneydsp::uint64_t a = 5_uint64_t; // 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0101

	REQUIRE ((a << 1) == 10);  // Left shift: 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 1010
  REQUIRE ((a >> 1) == 2);   // Right shift: 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0010
  // clang-format on
}

//===============================================================//comparison

TEST_CASE ("Comparison operations with stoneydsp::uint64_t",
           "[core][types][uint64_t][comparison]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::uint64_t a = 5_uint64_t;
  ::stoneydsp::uint64_t b = 3_uint64_t;

  REQUIRE ((a == b) == false);
  REQUIRE ((a != b) == true);
  REQUIRE ((a > b) == true);
  REQUIRE ((a < b) == false);
  REQUIRE ((a >= b) == true);
  REQUIRE ((a <= b) == false);
}

//===============================================================//serialization

TEST_CASE ("Check serialization and deserialization for stoneydsp::uint64_t",
           "[core][types][uint64_t][serialization]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::std::stringstream ss;
  ::stoneydsp::uint64_t originalValue = 42_uint64_t;
  ::stoneydsp::uint64_t deserializedValue;

  ss.write (reinterpret_cast<const char *> (&originalValue),
            sizeof (originalValue));
  ss.read (reinterpret_cast<char *> (&deserializedValue),
           sizeof (deserializedValue));

  REQUIRE (originalValue == deserializedValue);
}

//=======================================================//boundary_and_overflow

TEST_CASE ("Boundary and overflow behaviour of stoneydsp::uint64_t",
           "[core][types][uint64_t][boundary][overflow]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::uint64_t a = 18446744073709551615_uint64_t;
  ::stoneydsp::uint64_t b = 1_uint64_t;

  REQUIRE (static_cast< ::stoneydsp::uint64_t> (a + b)
           == 0); // Check overflow wrap-around behaviour
}

//======================================================//boundary_and_underflow

TEST_CASE ("Boundary and underflow behavior of stoneydsp::uint64_t",
           "[core][types][uint64_t][boundary][underflow]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::uint64_t a = 0_uint64_t;
  ::stoneydsp::uint64_t b = 1_uint64_t;

  REQUIRE (static_cast< ::stoneydsp::uint64_t> (a - b)
           == 18446744073709551615ULL); // Check underflow wrap-around behavior
}

//===============================================================//compatibility

TEST_CASE ("Compatibility of stoneydsp::uint64_t with standard library",
           "[core][types][uint64_t][compatibility]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::std::vector< ::stoneydsp::uint64_t> vec
      = { 5_uint64_t, 3_uint64_t, 4_uint64_t, 1_uint64_t, 2_uint64_t };

  // Use std::sort to sort the vector
  ::std::sort (vec.begin (), vec.end ());

  // Verify the vector is sorted
  REQUIRE (vec
           == ::std::vector< ::stoneydsp::uint64_t>{
               1_uint64_t, 2_uint64_t, 3_uint64_t, 4_uint64_t, 5_uint64_t });

  // Use std::accumulate to sum the elements
  ::stoneydsp::uint64_t sum = ::std::accumulate (
      vec.begin (), vec.end (), ::stoneydsp::uint64_t (0_uint64_t));

  // Verify the sum is correct
  REQUIRE (sum == 15);
}

//===================================================================//benchmark

// Benchmark for addition
TEST_CASE ("Benchmark for stoneydsp::uint64_t addition",
           "[core][types][uint64_t][benchmark]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::uint64_t a = 1200_uint64_t;
  ::stoneydsp::uint64_t b = 3400_uint64_t;

  BENCHMARK ("Addition") { return a + b; };
}

// Benchmark for subtraction
TEST_CASE ("Benchmark for stoneydsp::uint64_t subtraction",
           "[core][types][uint64_t][benchmark]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::uint64_t a = 3400_uint64_t;
  ::stoneydsp::uint64_t b = 1200_uint64_t;

  BENCHMARK ("Subtraction") { return a - b; };
}

// Benchmark for multiplication
TEST_CASE ("Benchmark for stoneydsp::uint64_t multiplication",
           "[core][types][uint64_t][benchmark]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::uint64_t a = 1200_uint64_t;
  ::stoneydsp::uint64_t b = 2_uint64_t;

  BENCHMARK ("Multiplication") { return a * b; };
}

// Benchmark for division
TEST_CASE ("Benchmark for stoneydsp::uint64_t division",
           "[core][types][uint64_t][benchmark]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::uint64_t a = 1200_uint64_t;
  ::stoneydsp::uint64_t b = 2_uint64_t;

  BENCHMARK ("Division") { return a / b; };
}

// Benchmark for type conversion to int
TEST_CASE ("Benchmark for stoneydsp::uint64_t to int conversion",
           "[core][types][uint64_t][benchmark]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::uint64_t a = 1200_uint64_t;

  BENCHMARK ("Conversion to int") { return static_cast<int> (a); };
}

// Benchmark for type conversion to float
TEST_CASE ("Benchmark for stoneydsp::uint64_t to float conversion",
           "[core][types][uint64_t][benchmark]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::uint64_t a = 1200_uint64_t;

  BENCHMARK ("Conversion to float")
  {
    return static_cast< ::stoneydsp::float_t> (a);
  };
}

//============================================================================//

#endif // defined(STONEYDSP_BUILD_TEST)

//=========================================================================//EOF
