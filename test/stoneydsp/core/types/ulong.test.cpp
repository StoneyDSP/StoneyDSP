/**
 * @file ulong.test.cpp
 * @brief Test suite for stoneydsp::ulong_t
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

TEST_CASE ("sizeof stoneydsp::ulong_t is 8 bytes",
           "[core][types][ulong_t][sizeof]")
{
  REQUIRE (sizeof (::stoneydsp::ulong_t) == 8UL);
}

//=====================================================================//alignof

TEST_CASE ("alignof stoneydsp::ulong_t is 8 bytes",
           "[core][types][ulong_t][alignof]")
{
  REQUIRE (alignof (::stoneydsp::ulong_t) == 8UL);
}

//=================================================================//type_traits

TEST_CASE ("Check if types are signed or unsigned",
           "[core][types][ulong_t][type_traits][is_unsigned]")
{
  REQUIRE (::std::is_unsigned< ::stoneydsp::ulong_t>::value);
}

TEST_CASE ("Is stoneydsp::ulong_t trivially copyable",
           "[core][types][ulong_t][type_traits][is_trivially_copyable]")
{
  REQUIRE (::std::is_trivially_copyable< ::stoneydsp::ulong_t>::value);
}

TEST_CASE ("Is stoneydsp::ulong_t standard-layout conforming",
           "[core][types][ulong_t][type_traits][is_standard_layout]")
{
  REQUIRE (::std::is_standard_layout< ::stoneydsp::ulong_t>::value);
}

//==============================================================//special_values

TEST_CASE ("Numeric limits of stoneydsp::ulong_t",
           "[core][types][ulong_t][numeric_limits][special_values]")
{
  // { 0U }
  REQUIRE (::stoneydsp::numeric_limits< ::stoneydsp::ulong_t>::min ()
           == ::std::numeric_limits< ::stoneydsp::ulong_t>::min ());

  // { 18446744073709551615UL }
  REQUIRE (::stoneydsp::numeric_limits< ::stoneydsp::ulong_t>::max ()
           == ::std::numeric_limits< ::stoneydsp::ulong_t>::max ());

  // { 0U }
  REQUIRE (::stoneydsp::numeric_limits< ::stoneydsp::ulong_t>::lowest ()
           == ::std::numeric_limits< ::stoneydsp::ulong_t>::lowest ());
}

//==============================================================//numeric_limits

TEST_CASE ("Special values of stoneydsp::ulong_t",
           "[core][types][ulong_t][numeric_limits]")
{
  ::stoneydsp::ulong_t min_val
      = ::std::numeric_limits< ::stoneydsp::ulong_t>::min ();
  ::stoneydsp::ulong_t max_val
      = ::std::numeric_limits< ::stoneydsp::ulong_t>::max ();
  REQUIRE (min_val == 0U);                     // Minimum value for ulong_t
  REQUIRE (max_val == 18446744073709551615UL); // Maximum value for ulong_t
}

//==================================================================//endianness

TEST_CASE ("Endianness handling for stoneydsp::ulong_t",
           "[core][types][ulong_t][endianness]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::ulong_t value = 0x123456789ABCDEF0_ulong_t;
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

TEST_CASE ("Rounding behavior of stoneydsp::ulong_t",
           "[core][types][ulong_t][rounding]")
{
  ::stoneydsp::float_t a = 1.5f;
  ::stoneydsp::ulong_t b
      = static_cast< ::stoneydsp::ulong_t> (::std::round (a));
  REQUIRE (b == 2); // 1.5 rounded to nearest integer and cast to ulong_t
}

//==================================================================//arithmetic

TEST_CASE ("Arithmetic operations with stoneydsp::ulong_t",
           "[core][types][ulong_t][arithmetic]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::ulong_t a = 1500000000000000000_ulong_t;
  ::stoneydsp::ulong_t b = 2_ulong_t;
  REQUIRE (a + b == 1500000000000000002UL); // Addition
  REQUIRE (a - b == 1499999999999999998UL); // Subtraction
  REQUIRE (a * b == 3000000000000000000UL); // Multiplication
  REQUIRE (b / a == 0);                     // Division
  REQUIRE (b % a == 2UL);                   // Modulo
}

//===============================================================//bitwise

TEST_CASE ("Bitwise operations with stoneydsp::ulong_t",
           "[core][types][ulong_t][bitwise]")
{
  using namespace ::stoneydsp::core::types::literals;

  // clang-format off
  ::stoneydsp::ulong_t a = 5_ulong_t; // 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0101
  ::stoneydsp::ulong_t b = 3_ulong_t; // 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0011

  REQUIRE ((a & b) == 1); // AND: 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0001
  REQUIRE ((a | b) == 7); // OR:  0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0111
  REQUIRE ((a ^ b) == 6); // XOR: 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0110
  REQUIRE (
      (~a & 0xFFFFFFFFFFFFFFFFUL)
      == 18446744073709551610UL); // NOT: 1111 1111 1111 1111 1111 1111 1111 1111 1111 1111 1111 1111 1111 1111 1111 1010 (considering ulong_t wrap-around)
	// clang-format off
}

TEST_CASE ("Shift operations with stoneydsp::ulong_t", "[core][types][ulong_t][bitwise]")
{
	using namespace ::stoneydsp::core::types::literals;

	// clang-format off
  ::stoneydsp::ulong_t a = 5_ulong_t; // 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0101

	REQUIRE ((a << 1) == 10);  // Left shift: 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 1010
  REQUIRE ((a >> 1) == 2);   // Right shift: 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0010
  // clang-format on
}

//===============================================================//comparison

TEST_CASE ("Comparison operations with stoneydsp::ulong_t",
           "[core][types][ulong_t][comparison]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::ulong_t a = 5_ulong_t;
  ::stoneydsp::ulong_t b = 3_ulong_t;

  REQUIRE ((a == b) == false);
  REQUIRE ((a != b) == true);
  REQUIRE ((a > b) == true);
  REQUIRE ((a < b) == false);
  REQUIRE ((a >= b) == true);
  REQUIRE ((a <= b) == false);
}

//===============================================================//serialization

TEST_CASE ("Check serialization and deserialization for stoneydsp::ulong_t",
           "[core][types][ulong_t][serialization]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::std::stringstream ss;
  ::stoneydsp::ulong_t originalValue = 42_ulong_t;
  ::stoneydsp::ulong_t deserializedValue;

  ss.write (reinterpret_cast<const char *> (&originalValue),
            sizeof (originalValue));
  ss.read (reinterpret_cast<char *> (&deserializedValue),
           sizeof (deserializedValue));

  REQUIRE (originalValue == deserializedValue);
}

//=======================================================//boundary_and_overflow

TEST_CASE ("Boundary and overflow behaviour of stoneydsp::ulong_t",
           "[core][types][ulong_t][boundary][overflow]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::ulong_t a = 18446744073709551615_ulong_t;
  ::stoneydsp::ulong_t b = 1_ulong_t;

  REQUIRE (static_cast< ::stoneydsp::ulong_t> (a + b)
           == 0); // Check overflow wrap-around behaviour
}

//======================================================//boundary_and_underflow

TEST_CASE ("Boundary and underflow behavior of stoneydsp::ulong_t",
           "[core][types][ulong_t][boundary][underflow]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::ulong_t a = 0_ulong_t;
  ::stoneydsp::ulong_t b = 1_ulong_t;

  REQUIRE (static_cast< ::stoneydsp::ulong_t> (a - b)
           == 18446744073709551615UL); // Check underflow wrap-around behavior
}

//===============================================================//compatibility

TEST_CASE ("Compatibility of stoneydsp::ulong_t with standard library",
           "[core][types][ulong_t][compatibility]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::std::vector< ::stoneydsp::ulong_t> vec
      = { 5_ulong_t, 3_ulong_t, 4_ulong_t, 1_ulong_t, 2_ulong_t };

  // Use std::sort to sort the vector
  ::std::sort (vec.begin (), vec.end ());

  // Verify the vector is sorted
  REQUIRE (vec
           == ::std::vector< ::stoneydsp::ulong_t>{
               1_ulong_t, 2_ulong_t, 3_ulong_t, 4_ulong_t, 5_ulong_t });

  // Use std::accumulate to sum the elements
  ::stoneydsp::ulong_t sum = ::std::accumulate (
      vec.begin (), vec.end (), ::stoneydsp::ulong_t (0_ulong_t));

  // Verify the sum is correct
  REQUIRE (sum == 15);
}

//===================================================================//benchmark

// Benchmark for addition
TEST_CASE ("Benchmark for stoneydsp::ulong_t addition",
           "[core][types][ulong_t][benchmark]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::ulong_t a = 1200_ulong_t;
  ::stoneydsp::ulong_t b = 3400_ulong_t;

  BENCHMARK ("Addition") { return a + b; };
}

// Benchmark for subtraction
TEST_CASE ("Benchmark for stoneydsp::ulong_t subtraction",
           "[core][types][ulong_t][benchmark]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::ulong_t a = 3400_ulong_t;
  ::stoneydsp::ulong_t b = 1200_ulong_t;

  BENCHMARK ("Subtraction") { return a - b; };
}

// Benchmark for multiplication
TEST_CASE ("Benchmark for stoneydsp::ulong_t multiplication",
           "[core][types][ulong_t][benchmark]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::ulong_t a = 1200_ulong_t;
  ::stoneydsp::ulong_t b = 2_ulong_t;

  BENCHMARK ("Multiplication") { return a * b; };
}

// Benchmark for division
TEST_CASE ("Benchmark for stoneydsp::ulong_t division",
           "[core][types][ulong_t][benchmark]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::ulong_t a = 1200_ulong_t;
  ::stoneydsp::ulong_t b = 2_ulong_t;

  BENCHMARK ("Division") { return a / b; };
}

// Benchmark for type conversion to int
TEST_CASE ("Benchmark for stoneydsp::ulong_t to int conversion",
           "[core][types][ulong_t][benchmark]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::ulong_t a = 1200_ulong_t;

  BENCHMARK ("Conversion to int") { return static_cast<int> (a); };
}

// Benchmark for type conversion to float
TEST_CASE ("Benchmark for stoneydsp::ulong_t to float conversion",
           "[core][types][ulong_t][benchmark]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::ulong_t a = 1200_ulong_t;

  BENCHMARK ("Conversion to float")
  {
    return static_cast< ::stoneydsp::float_t> (a);
  };
}

//============================================================================//

#endif // defined(STONEYDSP_BUILD_TEST)

//=========================================================================//EOF
