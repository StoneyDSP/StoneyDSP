/**
 * @file long.test.cpp
 * @brief Test suite for stoneydsp::long_t
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

TEST_CASE ("sizeof stoneydsp::long_t is 8 bytes",
           "[core][types][long_t][sizeof]")
{
  REQUIRE (sizeof (::stoneydsp::long_t) == 8UL);
}

//=====================================================================//alignof

TEST_CASE ("alignof stoneydsp::long_t is 8 bytes",
           "[core][types][long_t][alignof]")
{
  REQUIRE (alignof (::stoneydsp::long_t) == 8UL);
}

//=================================================================//type_traits

TEST_CASE ("Check if types are signed or unsigned",
           "[core][types][long_t][type_traits][is_signed]")
{
  REQUIRE (::std::is_signed< ::stoneydsp::long_t>::value);
}

TEST_CASE ("Is stoneydsp::long_t trivially copyable",
           "[core][types][long_t][type_traits][is_trivially_copyable]")
{
  REQUIRE (::std::is_trivially_copyable< ::stoneydsp::long_t>::value);
}

TEST_CASE ("Is stoneydsp::long_t standard-layout conforming",
           "[core][types][long_t][type_traits][is_standard_layout]")
{
  REQUIRE (::std::is_standard_layout< ::stoneydsp::long_t>::value);
}

//==============================================================//special_values

TEST_CASE ("Numeric limits of stoneydsp::long_t",
           "[core][types][long_t][numeric_limits][special_values]")
{
  // { -9223372036854775807L - 1 }
  REQUIRE (::stoneydsp::numeric_limits< ::stoneydsp::long_t>::min ()
           == ::std::numeric_limits< ::stoneydsp::long_t>::min ());
  // { 9223372036854775807L }
  REQUIRE (::stoneydsp::numeric_limits< ::stoneydsp::long_t>::max ()
           == ::std::numeric_limits< ::stoneydsp::long_t>::max ());
  // { -9223372036854775807L - 1 }
  REQUIRE (::stoneydsp::numeric_limits< ::stoneydsp::long_t>::lowest ()
           == ::std::numeric_limits< ::stoneydsp::long_t>::lowest ());
}

//==============================================================//numeric_limits

TEST_CASE ("Special values of stoneydsp::long_t",
           "[core][types][long_t][numeric_limits]")
{
  ::stoneydsp::long_t min_val
      = ::std::numeric_limits< ::stoneydsp::long_t>::min ();
  ::stoneydsp::long_t max_val
      = ::std::numeric_limits< ::stoneydsp::long_t>::max ();
  REQUIRE (min_val == -9223372036854775807L - 1); // Minimum value for long_t
  REQUIRE (max_val == 9223372036854775807L);      // Maximum value for long_t
}

//==================================================================//endianness

TEST_CASE ("Endianness handling for stoneydsp::long_t",
           "[core][types][long_t][endianness]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::long_t value = 0x123456789ABCDEF0_long_t;
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

TEST_CASE ("Rounding behavior of stoneydsp::long_t",
           "[core][types][long_t][rounding]")
{
  ::stoneydsp::float_t a = 1.5f;
  ::stoneydsp::long_t b = static_cast< ::stoneydsp::long_t> (::std::round (a));
  REQUIRE (b == 2); // 1.5 rounded to nearest integer and cast to long_t
}

//==================================================================//arithmetic

TEST_CASE ("Arithmetic operations with stoneydsp::long_t",
           "[core][types][long_t][arithmetic]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::long_t a = 1500000000_long_t;
  ::stoneydsp::long_t b = 2000000000_long_t;

  REQUIRE (a + b == 3500000000L);          // Addition
  REQUIRE (a - b == -500000000L);          // Subtraction
  REQUIRE (a * b == 3000000000000000000L); // Multiplication
  REQUIRE (b / a == 1);                    // Division
  REQUIRE (b % a == 500000000L);           // Modulo
}

//===============================================================//bitwise

TEST_CASE ("Bitwise operations with stoneydsp::long_t",
           "[core][types][long_t][bitwise]")
{
  using namespace ::stoneydsp::core::types::literals;

  // clang-format off
	// 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0101
  ::stoneydsp::long_t a = 5_long_t;
	// 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0011
  ::stoneydsp::long_t b = 3_long_t;

	// AND: 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0001
  REQUIRE ((a & b) == 1);
	// OR:  0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0111
  REQUIRE ((a | b) == 7);
	// XOR: 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0110
  REQUIRE ((a ^ b) == 6);
	// NOT: considering wrap-around for long_t
  REQUIRE (~a == -6);
  // clang-format on
}

TEST_CASE ("Shift operations with stoneydsp::long_t",
           "[core][types][long_t][bitwise]")
{
  using namespace ::stoneydsp::core::types::literals;

  // clang-format off
	// 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0101
  ::stoneydsp::long_t a = 5_long_t;
	// Left shift: 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 1010
  REQUIRE ((a << 1) == 10);
	// Right shift: 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0010
  REQUIRE ((a >> 1) == 2);
  // clang-format on
}

//===============================================================//comparison

TEST_CASE ("Comparison operations with stoneydsp::long_t",
           "[core][types][long_t][comparison]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::long_t a = 5_long_t;
  ::stoneydsp::long_t b = 3_long_t;
  REQUIRE ((a == b) == false);
  REQUIRE ((a != b) == true);
  REQUIRE ((a > b) == true);
  REQUIRE ((a < b) == false);
  REQUIRE ((a >= b) == true);
  REQUIRE ((a <= b) == false);
}

//===============================================================//serialization

TEST_CASE ("Check serialization and deserialization for stoneydsp::long_t",
           "[core][types][long_t][serialization]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::std::stringstream ss;
  ::stoneydsp::long_t originalValue = 42_long_t;
  ::stoneydsp::long_t deserializedValue;

  ss.write (reinterpret_cast<const char *> (&originalValue),
            sizeof (originalValue));
  ss.read (reinterpret_cast<char *> (&deserializedValue),
           sizeof (deserializedValue));

  REQUIRE (originalValue == deserializedValue);
}

//=======================================================//boundary_and_overflow

TEST_CASE ("Boundary and overflow behaviour of stoneydsp::long_t",
           "[core][types][long_t][boundary][overflow]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::long_t a = 9223372036854775807_long_t;
  ::stoneydsp::long_t b = 1_long_t;

  REQUIRE (static_cast< ::stoneydsp::long_t> (a + b)
           == ::std::numeric_limits< ::stoneydsp::long_t>::
               min ()); // Check overflow wrap-around behaviour
}

//======================================================//boundary_and_underflow

TEST_CASE ("Boundary and underflow behavior of stoneydsp::long_t",
           "[core][types][long_t][boundary][underflow]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::long_t a = -9223372036854775807_long_t - 1_long_t;
  ::stoneydsp::long_t b = 1_long_t;
  REQUIRE (static_cast< ::stoneydsp::long_t> (a - b)
           == 9223372036854775807L); // Check underflow wrap-around behavior
}

//===============================================================//compatibility

TEST_CASE ("Compatibility of stoneydsp::long_t with standard library",
           "[core][types][long_t][compatibility]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::std::vector< ::stoneydsp::long_t> vec
      = { 5_long_t, 3_long_t, 4_long_t, 1_long_t, 2_long_t };

  // Use std::sort to sort the vector
  ::std::sort (vec.begin (), vec.end ());

  // Verify the vector is sorted
  REQUIRE (vec
           == ::std::vector< ::stoneydsp::long_t>{
               1_long_t, 2_long_t, 3_long_t, 4_long_t, 5_long_t });

  // Use std::accumulate to sum the elements
  ::stoneydsp::long_t sum = ::std::accumulate (vec.begin (), vec.end (),
                                               ::stoneydsp::long_t (0_long_t));

  // Verify the sum is correct
  REQUIRE (sum == 15);
}

//===================================================================//benchmark

// Benchmark for addition
TEST_CASE ("Benchmark for stoneydsp::long_t addition",
           "[core][types][long_t][benchmark]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::long_t a = 1200_long_t;
  ::stoneydsp::long_t b = 3400_long_t;

  BENCHMARK ("Addition") { return a + b; };
}

// Benchmark for subtraction
TEST_CASE ("Benchmark for stoneydsp::long_t subtraction",
           "[core][types][long_t][benchmark]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::long_t a = 3400_long_t;
  ::stoneydsp::long_t b = 1200_long_t;

  BENCHMARK ("Subtraction") { return a - b; };
}

// Benchmark for multiplication
TEST_CASE ("Benchmark for stoneydsp::long_t multiplication",
           "[core][types][long_t][benchmark]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::long_t a = 1200_long_t;
  ::stoneydsp::long_t b = 2_long_t;

  BENCHMARK ("Multiplication") { return a * b; };
}

// Benchmark for division
TEST_CASE ("Benchmark for stoneydsp::long_t division",
           "[core][types][long_t][benchmark]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::long_t a = 1200_long_t;
  ::stoneydsp::long_t b = 2_long_t;

  BENCHMARK ("Division") { return a / b; };
}

// Benchmark for type conversion to int
TEST_CASE ("Benchmark for stoneydsp::long_t to int conversion",
           "[core][types][long_t][benchmark]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::long_t a = 1200_long_t;

  BENCHMARK ("Conversion to int") { return static_cast<int> (a); };
}

// Benchmark for type conversion to float
TEST_CASE ("Benchmark for stoneydsp::long_t to float conversion",
           "[core][types][long_t][benchmark]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::long_t a = 1200_long_t;

  BENCHMARK ("Conversion to float")
  {
    return static_cast< ::stoneydsp::float_t> (a);
  };
}

//============================================================================//

#endif // defined(STONEYDSP_BUILD_TEST)

//=========================================================================//EOF
