/**
 * @file int64.test.cpp
 * @brief Test suite for stoneydsp::int64_t
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

TEST_CASE ("sizeof stoneydsp::int64_t is 8 bytes",
           "[core][types][int64_t][sizeof]")
{
  REQUIRE (sizeof (::stoneydsp::int64_t) == 8UL);
}

//=====================================================================//alignof

TEST_CASE ("alignof stoneydsp::int64_t is 8 bytes",
           "[core][types][int64_t][alignof]")
{
  REQUIRE (alignof (::stoneydsp::int64_t) == 8UL);
}

//=================================================================//type_traits

TEST_CASE ("Check if types are signed or unsigned",
           "[core][types][int64_t][type_traits][is_signed]")
{
  REQUIRE (::std::is_signed< ::stoneydsp::int64_t>::value);
}

TEST_CASE ("Is stoneydsp::int64_t trivially copyable",
           "[core][types][int64_t][type_traits][is_trivially_copyable]")
{
  REQUIRE (::std::is_trivially_copyable< ::stoneydsp::int64_t>::value);
}

TEST_CASE ("Is stoneydsp::int64_t standard-layout conforming",
           "[core][types][int64_t][type_traits][is_standard_layout]")
{
  REQUIRE (::std::is_standard_layout< ::stoneydsp::int64_t>::value);
}

//==============================================================//special_values

TEST_CASE ("Numeric limits of stoneydsp::int64_t",
           "[core][types][int64_t][numeric_limits][special_values]")
{
  // { -9223372036854775807LL - 1 }
  REQUIRE (::stoneydsp::numeric_limits< ::stoneydsp::int64_t>::min ()
           == ::std::numeric_limits< ::stoneydsp::int64_t>::min ());
  // { 9223372036854775807LL }
  REQUIRE (::stoneydsp::numeric_limits< ::stoneydsp::int64_t>::max ()
           == ::std::numeric_limits< ::stoneydsp::int64_t>::max ());
  // { -9223372036854775807LL - 1 }
  REQUIRE (::stoneydsp::numeric_limits< ::stoneydsp::int64_t>::lowest ()
           == ::std::numeric_limits< ::stoneydsp::int64_t>::lowest ());
}

//==============================================================//numeric_limits

TEST_CASE ("Special values of stoneydsp::int64_t",
           "[core][types][int64_t][numeric_limits]")
{
  ::stoneydsp::int64_t min_val
      = ::std::numeric_limits< ::stoneydsp::int64_t>::min ();
  ::stoneydsp::int64_t max_val
      = ::std::numeric_limits< ::stoneydsp::int64_t>::max ();
  REQUIRE (min_val == -9223372036854775807LL - 1); // Minimum value for int64_t
  REQUIRE (max_val == 9223372036854775807LL);      // Maximum value for int64_t
}

//==================================================================//endianness

TEST_CASE ("Endianness handling for stoneydsp::int64_t",
           "[core][types][int64_t][endianness]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::int64_t value = 0x123456789ABCDEF0_int64_t;
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

TEST_CASE ("Rounding behavior of stoneydsp::int64_t",
           "[core][types][int64_t][rounding]")
{
  ::stoneydsp::float_t a = 1.5f;
  ::stoneydsp::int64_t b
      = static_cast< ::stoneydsp::int64_t> (::std::round (a));
  REQUIRE (b == 2); // 1.5 rounded to nearest integer and cast to int64_t
}

//==================================================================//arithmetic

TEST_CASE ("Arithmetic operations with stoneydsp::int64_t",
           "[core][types][int64_t][arithmetic]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::int64_t a = 1500000000_int64_t;
  ::stoneydsp::int64_t b = 2000000000_int64_t;

  REQUIRE (a + b == 3500000000LL);          // Addition
  REQUIRE (a - b == -500000000LL);          // Subtraction
  REQUIRE (a * b == 3000000000000000000LL); // Multiplication
  REQUIRE (b / a == 1);                     // Division
  REQUIRE (b % a == 500000000LL);           // Modulo
}

//===============================================================//bitwise

TEST_CASE ("Bitwise operations with stoneydsp::int64_t",
           "[core][types][int64_t][bitwise]")
{
  using namespace ::stoneydsp::core::types::literals;

  // clang-format off
	// 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0101
  ::stoneydsp::int64_t a = 5_int64_t;
	// 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0011
  ::stoneydsp::int64_t b = 3_int64_t;

	// AND: 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0001
  REQUIRE ((a & b) == 1);
	// OR:  0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0111
  REQUIRE ((a | b) == 7);
	// XOR: 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0110
  REQUIRE ((a ^ b) == 6);
	// NOT: considering wrap-around for int64_t
  REQUIRE (~a == -6);
  // clang-format on
}

TEST_CASE ("Shift operations with stoneydsp::int64_t",
           "[core][types][int64_t][bitwise]")
{
  using namespace ::stoneydsp::core::types::literals;

  // clang-format off
	// 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0101
  ::stoneydsp::int64_t a = 5_int64_t;
	// Left shift: 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 1010
  REQUIRE ((a << 1) == 10);
	// Right shift: 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0010
  REQUIRE ((a >> 1) == 2);
  // clang-format on
}

//===============================================================//comparison

TEST_CASE ("Comparison operations with stoneydsp::int64_t",
           "[core][types][int64_t][comparison]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::int64_t a = 5_int64_t;
  ::stoneydsp::int64_t b = 3_int64_t;
  REQUIRE ((a == b) == false);
  REQUIRE ((a != b) == true);
  REQUIRE ((a > b) == true);
  REQUIRE ((a < b) == false);
  REQUIRE ((a >= b) == true);
  REQUIRE ((a <= b) == false);
}

//===============================================================//serialization

TEST_CASE ("Check serialization and deserialization for stoneydsp::int64_t",
           "[core][types][int64_t][serialization]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::std::stringstream ss;
  ::stoneydsp::int64_t originalValue = 42_int64_t;
  ::stoneydsp::int64_t deserializedValue;

  ss.write (reinterpret_cast<const char *> (&originalValue),
            sizeof (originalValue));
  ss.read (reinterpret_cast<char *> (&deserializedValue),
           sizeof (deserializedValue));

  REQUIRE (originalValue == deserializedValue);
}

//=======================================================//boundary_and_overflow

TEST_CASE ("Boundary and overflow behaviour of stoneydsp::int64_t",
           "[core][types][int64_t][boundary][overflow]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::int64_t a = 9223372036854775807_int64_t;
  ::stoneydsp::int64_t b = 1_int64_t;

  REQUIRE (static_cast< ::stoneydsp::int64_t> (a + b)
           == ::std::numeric_limits< ::stoneydsp::int64_t>::
               min ()); // Check overflow wrap-around behaviour
}

//======================================================//boundary_and_underflow

TEST_CASE ("Boundary and underflow behavior of stoneydsp::int64_t",
           "[core][types][int64_t][boundary][underflow]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::int64_t a = -9223372036854775807_int64_t - 1_int64_t;
  ::stoneydsp::int64_t b = 1_int64_t;
  REQUIRE (static_cast< ::stoneydsp::int64_t> (a - b)
           == 9223372036854775807LL); // Check underflow wrap-around behavior
}

//===============================================================//compatibility

TEST_CASE ("Compatibility of stoneydsp::int64_t with standard library",
           "[core][types][int64_t][compatibility]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::std::vector< ::stoneydsp::int64_t> vec
      = { 5_int64_t, 3_int64_t, 4_int64_t, 1_int64_t, 2_int64_t };

  // Use std::sort to sort the vector
  ::std::sort (vec.begin (), vec.end ());

  // Verify the vector is sorted
  REQUIRE (vec
           == ::std::vector< ::stoneydsp::int64_t>{ 1_int64_t, 2_int64_t, 3_int64_t,
                                                    4_int64_t, 5_int64_t });

  // Use std::accumulate to sum the elements
  ::stoneydsp::int64_t sum = ::std::accumulate (
      vec.begin (), vec.end (), ::stoneydsp::int64_t (0_int64_t));

  // Verify the sum is correct
  REQUIRE (sum == 15);
}

//===================================================================//benchmark

// Benchmark for addition
TEST_CASE ("Benchmark for stoneydsp::int64_t addition",
           "[core][types][int64_t][benchmark]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::int64_t a = 1200_int64_t;
  ::stoneydsp::int64_t b = 3400_int64_t;

  BENCHMARK ("Addition") { return a + b; };
}

// Benchmark for subtraction
TEST_CASE ("Benchmark for stoneydsp::int64_t subtraction",
           "[core][types][int64_t][benchmark]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::int64_t a = 3400_int64_t;
  ::stoneydsp::int64_t b = 1200_int64_t;

  BENCHMARK ("Subtraction") { return a - b; };
}

// Benchmark for multiplication
TEST_CASE ("Benchmark for stoneydsp::int64_t multiplication",
           "[core][types][int64_t][benchmark]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::int64_t a = 1200_int64_t;
  ::stoneydsp::int64_t b = 2_int64_t;

  BENCHMARK ("Multiplication") { return a * b; };
}

// Benchmark for division
TEST_CASE ("Benchmark for stoneydsp::int64_t division",
           "[core][types][int64_t][benchmark]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::int64_t a = 1200_int64_t;
  ::stoneydsp::int64_t b = 2_int64_t;

  BENCHMARK ("Division") { return a / b; };
}

// Benchmark for type conversion to int
TEST_CASE ("Benchmark for stoneydsp::int64_t to int conversion",
           "[core][types][int64_t][benchmark]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::int64_t a = 1200_int64_t;

  BENCHMARK ("Conversion to int") { return static_cast<int> (a); };
}

// Benchmark for type conversion to float
TEST_CASE ("Benchmark for stoneydsp::int64_t to float conversion",
           "[core][types][int64_t][benchmark]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::int64_t a = 1200_int64_t;

  BENCHMARK ("Conversion to float")
  {
    return static_cast< ::stoneydsp::float_t> (a);
  };
}

//============================================================================//

#endif // defined(STONEYDSP_BUILD_TEST)

//=========================================================================//EOF
