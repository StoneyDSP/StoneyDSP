/**
 * @file schar.test.cpp
 * @brief Test suite for stoneydsp::schar_t
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

TEST_CASE ("sizeof stoneydsp::schar_t is 1 byte",
           "[core][types][schar_t][sizeof]")
{
  REQUIRE (sizeof (::stoneydsp::schar_t) == 1UL);
}

//=====================================================================//alignof

TEST_CASE ("alignof stoneydsp::schar_t is 1 byte",
           "[core][types][schar_t][alignof]")
{
  REQUIRE (alignof (::stoneydsp::schar_t) == 1UL);
}

//=================================================================//type_traits

TEST_CASE ("Check if types are signed or unsigned",
           "[core][types][schar_t][type_traits][is_signed]")
{
  REQUIRE (::std::is_signed< ::stoneydsp::schar_t>::value);
}

TEST_CASE ("Is stoneydsp::schar_t trivially copyable",
           "[core][types][schar_t][type_traits][is_trivially_copyable]")
{
  REQUIRE (::std::is_trivially_copyable< ::stoneydsp::schar_t>::value);
}

TEST_CASE ("Is stoneydsp::schar_t standard-layout conforming",
           "[core][types][schar_t][type_traits][is_standard_layout]")
{
  REQUIRE (::std::is_standard_layout< ::stoneydsp::schar_t>::value);
}

//==============================================================//special_values

TEST_CASE ("Numeric limits of stoneydsp::schar_t",
           "[core][types][schar_t][numeric_limits][special_values]")
{
  // { -128 }
  REQUIRE (::stoneydsp::numeric_limits< ::stoneydsp::schar_t>::min ()
           == ::std::numeric_limits< ::stoneydsp::schar_t>::min ());
  // { 127 }
  REQUIRE (::stoneydsp::numeric_limits< ::stoneydsp::schar_t>::max ()
           == ::std::numeric_limits< ::stoneydsp::schar_t>::max ());
  // { -128 }
  REQUIRE (::stoneydsp::numeric_limits< ::stoneydsp::schar_t>::lowest ()
           == ::std::numeric_limits< ::stoneydsp::schar_t>::lowest ());
}

//==============================================================//numeric_limits

TEST_CASE ("Special values of stoneydsp::schar_t",
           "[core][types][schar_t][numeric_limits]")
{
  ::stoneydsp::schar_t min_val
      = ::std::numeric_limits< ::stoneydsp::schar_t>::min ();
  ::stoneydsp::schar_t max_val
      = ::std::numeric_limits< ::stoneydsp::schar_t>::max ();
  REQUIRE (min_val == -128); // Minimum value for schar_t
  REQUIRE (max_val == 127);  // Maximum value for schar_t
}

//==================================================================//endianness

TEST_CASE ("Endianness handling for stoneydsp::schar_t",
           "[core][types][schar_t][endianness]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::schar_t value = 0x12_schar_t;
  ::std::uint8_t *bytePtr = reinterpret_cast< ::std::uint8_t *> (&value);

  if (bytePtr[0] == 0x12)
    {
      REQUIRE (true); // Little-endian and Big-endian will look the same for a
                      // single byte
    }
  else
    {
      REQUIRE (false); // Unknown endianness
    }
}

//====================================================================//rounding

TEST_CASE ("Rounding behavior of stoneydsp::schar_t",
           "[core][types][schar_t][rounding]")
{
  ::stoneydsp::float_t a = 1.5f;
  ::stoneydsp::schar_t b
      = static_cast< ::stoneydsp::schar_t> (::std::round (a));
  REQUIRE (b == 2); // 1.5 rounded to nearest integer and cast to schar_t
}

//==================================================================//arithmetic

TEST_CASE ("Arithmetic operations with stoneydsp::schar_t",
           "[core][types][schar_t][arithmetic]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::schar_t a = 15_schar_t;
  ::stoneydsp::schar_t b = 20_schar_t;

  REQUIRE (a + b == 35);  // Addition
  REQUIRE (a - b == -5);  // Subtraction
  REQUIRE (a * b == 300); // Multiplication
  REQUIRE (b / a == 1);   // Division
  REQUIRE (b % a == 5);   // Modulo
}

//===============================================================//bitwise

TEST_CASE ("Bitwise operations with stoneydsp::schar_t",
           "[core][types][schar_t][bitwise]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::schar_t a = 5_schar_t; // 0101
  ::stoneydsp::schar_t b = 3_schar_t; // 0011

  REQUIRE ((a & b) == 1); // AND: 0001
  REQUIRE ((a | b) == 7); // OR:  0111
  REQUIRE ((a ^ b) == 6); // XOR: 0110
  REQUIRE (~a == -6);     // NOT: considering wrap-around for schar_t
}

TEST_CASE ("Shift operations with stoneydsp::schar_t",
           "[core][types][schar_t][bitwise]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::schar_t a = 5_schar_t; // 0101

  REQUIRE ((a << 1) == 10); // Left shift: 1010
  REQUIRE ((a >> 1) == 2);  // Right shift: 0010
}

//===============================================================//comparison

TEST_CASE ("Comparison operations with stoneydsp::schar_t",
           "[core][types][schar_t][comparison]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::schar_t a = 5_schar_t;
  ::stoneydsp::schar_t b = 3_schar_t;

  REQUIRE ((a == b) == false);
  REQUIRE ((a != b) == true);
  REQUIRE ((a > b) == true);
  REQUIRE ((a < b) == false);
  REQUIRE ((a >= b) == true);
  REQUIRE ((a <= b) == false);
}

//===============================================================//serialization

TEST_CASE ("Check serialization and deserialization for stoneydsp::schar_t",
           "[core][types][schar_t][serialization]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::std::stringstream ss;

  ::stoneydsp::schar_t originalValue = 42_schar_t;
  ::stoneydsp::schar_t deserializedValue;

  ss.write (reinterpret_cast<const char *> (&originalValue),
            sizeof (originalValue));
  ss.read (reinterpret_cast<char *> (&deserializedValue),
           sizeof (deserializedValue));

  REQUIRE (originalValue == deserializedValue);
}

//=======================================================//boundary_and_overflow

TEST_CASE ("Boundary and overflow behaviour of stoneydsp::schar_t",
           "[core][types][schar_t][boundary][overflow]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::schar_t a = 127_schar_t;
  ::stoneydsp::schar_t b = 1_schar_t;

  REQUIRE (static_cast< ::stoneydsp::schar_t> (a + b)
           == -128); // Check overflow wrap-around behaviour
}

//======================================================//boundary_and_underflow

TEST_CASE ("Boundary and underflow behavior of stoneydsp::schar_t",
           "[core][types][schar_t][boundary][underflow]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::schar_t a = -127_schar_t;
  ::stoneydsp::schar_t b = 2_schar_t;

  REQUIRE (static_cast< ::stoneydsp::schar_t> (a - b)
           == 127); // Check underflow wrap-around behavior
}

//===============================================================//compatibility

TEST_CASE ("Compatibility of stoneydsp::schar_t with standard library",
           "[core][types][schar_t][compatibility]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::std::vector< ::stoneydsp::schar_t> vec
      = { 5_schar_t, 3_schar_t, 4_schar_t, 1_schar_t, 2_schar_t };

  // Use std::sort to sort the vector
  ::std::sort (vec.begin (), vec.end ());

  // Verify the vector is sorted
  REQUIRE (vec
           == ::std::vector< ::stoneydsp::schar_t>{
               1_schar_t, 2_schar_t, 3_schar_t, 4_schar_t, 5_schar_t });

  // Use std::accumulate to sum the elements
  ::stoneydsp::schar_t sum = ::std::accumulate (
      vec.begin (), vec.end (), ::stoneydsp::schar_t (0_schar_t));

  // Verify the sum is correct
  REQUIRE (sum == 15);
}

//===================================================================//benchmark

// Benchmark for addition
TEST_CASE ("Benchmark for stoneydsp::schar_t addition",
           "[core][types][schar_t][benchmark]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::schar_t a = 12_schar_t;
  ::stoneydsp::schar_t b = 34_schar_t;

  BENCHMARK ("Addition") { return a + b; };
}

// Benchmark for subtraction
TEST_CASE ("Benchmark for stoneydsp::schar_t subtraction",
           "[core][types][schar_t][benchmark]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::schar_t a = 34_schar_t;
  ::stoneydsp::schar_t b = 12_schar_t;

  BENCHMARK ("Subtraction") { return a - b; };
}

// Benchmark for multiplication
TEST_CASE ("Benchmark for stoneydsp::schar_t multiplication",
           "[core][types][schar_t][benchmark]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::schar_t a = 12_schar_t;
  ::stoneydsp::schar_t b = 2_schar_t;

  BENCHMARK ("Multiplication") { return a * b; };
}

// Benchmark for division
TEST_CASE ("Benchmark for stoneydsp::schar_t division",
           "[core][types][schar_t][benchmark]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::schar_t a = 12_schar_t;
  ::stoneydsp::schar_t b = 2_schar_t;

  BENCHMARK ("Division") { return a / b; };
}

// Benchmark for type conversion to int
TEST_CASE ("Benchmark for stoneydsp::schar_t to int conversion",
           "[core][types][schar_t][benchmark]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::schar_t a = 12_schar_t;

  BENCHMARK ("Conversion to int") { return static_cast<int> (a); };
}

// Benchmark for type conversion to float
TEST_CASE ("Benchmark for stoneydsp::schar_t to float conversion",
           "[core][types][schar_t][benchmark]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::schar_t a = 12_schar_t;

  BENCHMARK ("Conversion to float")
  {
    return static_cast< ::stoneydsp::float_t> (a);
  };
}

//============================================================================//

#endif // defined(STONEYDSP_BUILD_TEST)

//=========================================================================//EOF
