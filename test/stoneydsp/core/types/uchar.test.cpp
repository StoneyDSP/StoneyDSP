/**
 * @file uint8.test.cpp
 * @brief Test suite for stoneydsp::uchar_t
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
  #include <catch2/benchmark/catch_benchmark.hpp> // for `BENCHMARK`
  #include <catch2/catch_test_macros.hpp>         // for `TEST_CASE
  #include <limits>                               // for `std::numeric_limits`
  #include <numeric>                              // for `std::accumulate`
  #include <sstream>                              // for serialization tests
  #include <type_traits> // for `is_signed` and `is_unsigned`
  #include <vector>      // for compatibility tests

//======================================================================//sizeof

TEST_CASE ("sizeof stoneydsp::uchar_t is 1 byte",
           "[core][types][uchar_t][sizeof]")
{
  REQUIRE (sizeof (::stoneydsp::uchar_t) == 1UL);
}

//=====================================================================//alignof

TEST_CASE ("alignof stoneydsp::uchar_t is 1 byte",
           "[core][types][uchar_t][alignof]")
{
  REQUIRE (alignof (::stoneydsp::uchar_t) == 1UL);
}

//=================================================================//type_traits

TEST_CASE ("Check if types are signed or unsigned",
           "[core][types][uchar_t][type_traits][is_unsigned]")
{
  REQUIRE (::std::is_unsigned< ::stoneydsp::uchar_t>::value);
}

TEST_CASE ("Is stoneydsp::uchar_t trivially copyable",
           "[core][types][uchar_t][type_traits][is_trivially_copyable]")
{
  REQUIRE (::std::is_trivially_copyable< ::stoneydsp::uchar_t>::value);
}

TEST_CASE ("Is stoneydsp::uchar_t standard-layout conforming",
           "[core][types][uchar_t][type_traits][is_standard_layout]")
{
  REQUIRE (::std::is_standard_layout< ::stoneydsp::uchar_t>::value);
}

//==============================================================//special_values

TEST_CASE ("Numeric limits of stoneydsp::uchar_t",
           "[core][types][uchar_t][numeric_limits][special_values]")
{
  // { 0U }
  REQUIRE (::stoneydsp::numeric_limits< ::stoneydsp::uchar_t>::min ()
           == ::std::numeric_limits< ::stoneydsp::uchar_t>::min ());
  // { 255 }
  REQUIRE (::stoneydsp::numeric_limits< ::stoneydsp::uchar_t>::max ()
           == ::std::numeric_limits< ::stoneydsp::uchar_t>::max ());
  // { 0U }
  REQUIRE (::stoneydsp::numeric_limits< ::stoneydsp::uchar_t>::lowest ()
           == ::std::numeric_limits< ::stoneydsp::uchar_t>::lowest ());
}

//==============================================================//numeric_limits

TEST_CASE ("Special values of stoneydsp::uchar_t",
           "[core][types][uchar_t][numeric_limits]")
{
  ::stoneydsp::uchar_t min_val
      = ::std::numeric_limits< ::stoneydsp::uchar_t>::min ();
  ::stoneydsp::uchar_t max_val
      = ::std::numeric_limits< ::stoneydsp::uchar_t>::max ();
  REQUIRE (min_val == 0U);   // Minimum value for uchar_t
  REQUIRE (max_val == 255U); // Maximum value for uchar_t
}

//==================================================================//endianness

TEST_CASE ("Endianness handling for stoneydsp::uchar_t",
           "[core][types][uchar_t][endianness]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::uchar_t value = 0x12_uchar_t;
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

TEST_CASE ("Rounding behavior of stoneydsp::uchar_t",
           "[core][types][uchar_t][rounding]")
{
  ::stoneydsp::float_t a = 1.5f;
  ::stoneydsp::uchar_t b
      = static_cast< ::stoneydsp::uchar_t> (::std::round (a));
  REQUIRE (b == 2); // 1.5 rounded to nearest integer and cast to uchar_t
}

//==================================================================//arithmetic

TEST_CASE ("Arithmetic operations with stoneydsp::uchar_t",
           "[core][types][uchar_t][arithmetic]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::uchar_t a = 15_uchar_t;
  ::stoneydsp::uchar_t b = 20_uchar_t;
  REQUIRE (a + b == 35); // Addition
  REQUIRE (static_cast<int> (a - b)
           == static_cast<int> (-5)); // Subtraction (wrap-around)
  REQUIRE (a * b == 300);             // Multiplication
  REQUIRE (b / a == 1);               // Division
  REQUIRE (b % a == 5);               // Modulo
}
//=====================================================================//bitwise

TEST_CASE ("Bitwise operations with stoneydsp::uchar_t",
           "[core][types][uchar_t][bitwise]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::uchar_t a = 5_uchar_t; // 0101
  ::stoneydsp::uchar_t b = 3_uchar_t; // 0011

  REQUIRE ((a & b) == 1); // AND: 0001
  REQUIRE ((a | b) == 7); // OR: 0111
  REQUIRE ((a ^ b) == 6); // XOR: 0110
  REQUIRE ((~a & 0xFF)
           == 250); // NOT: 1111_1010 (considering uchar_t wrap-around)
}

TEST_CASE ("Shift operations with stoneydsp::uchar_t",
           "[core][types][uchar_t][bitwise]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::uchar_t a = 5_uchar_t; // 0101
  REQUIRE ((a << 1) == 10);           // Left shift: 1010
  REQUIRE ((a >> 1) == 2);            // Right shift: 0010
}

//==================================================================//comparison

TEST_CASE ("Comparison operations with stoneydsp::uchar_t",
           "[core][types][uchar_t][comparison]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::uchar_t a = 5_uchar_t;
  ::stoneydsp::uchar_t b = 3_uchar_t;

  REQUIRE ((a == b) == false);
  REQUIRE ((a != b) == true);
  REQUIRE ((a > b) == true);
  REQUIRE ((a < b) == false);
  REQUIRE ((a >= b) == true);
  REQUIRE ((a <= b) == false);
}

//===============================================================//serialization

TEST_CASE ("Check serialization and deserialization for stoneydsp::uchar_t",
           "[core][types][uchar_t][serialization]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::std::stringstream ss;

  ::stoneydsp::uchar_t originalValue = 42_uchar_t;
  ::stoneydsp::uchar_t deserializedValue;

  ss.write (reinterpret_cast<const char *> (&originalValue),
            sizeof (originalValue));
  ss.read (reinterpret_cast<char *> (&deserializedValue),
           sizeof (deserializedValue));

  REQUIRE (originalValue == deserializedValue);
}

//=======================================================//boundary_and_overflow

TEST_CASE ("Boundary and overflow behaviour of stoneydsp::uchar_t",
           "[core][types][uchar_t][boundary][overflow]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::uchar_t a = 255_uchar_t;
  ::stoneydsp::uchar_t b = 1_uchar_t;

  REQUIRE (static_cast< ::stoneydsp::uchar_t> (a + b)
           == 0); // Check overflow wrap-around behaviour
}

//======================================================//boundary_and_underflow

TEST_CASE ("Boundary and underflow behavior of stoneydsp::uchar_t",
           "[core][types][uchar_t][boundary][underflow]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::uchar_t a = 0_uchar_t;
  ::stoneydsp::uchar_t b = 1_uchar_t;

  REQUIRE (static_cast< ::stoneydsp::uchar_t> (a - b)
           == 255); // Check underflow wrap-around behavior
}

//===============================================================//compatibility

TEST_CASE ("Compatibility of stoneydsp::uchar_t with standard library",
           "[core][types][uchar_t][compatibility]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::std::vector< ::stoneydsp::uchar_t> vec
      = { 5_uchar_t, 3_uchar_t, 4_uchar_t, 1_uchar_t, 2_uchar_t };

  // Use std::sort to sort the vector
  ::std::sort (vec.begin (), vec.end ());

  // Verify the vector is sorted
  REQUIRE (vec
           == ::std::vector< ::stoneydsp::uchar_t>{
               1_uchar_t, 2_uchar_t, 3_uchar_t, 4_uchar_t, 5_uchar_t });

  // Use std::accumulate to sum the elements
  ::stoneydsp::uchar_t sum = ::std::accumulate (
      vec.begin (), vec.end (), ::stoneydsp::uchar_t (0_uchar_t));

  // Verify the sum is correct
  REQUIRE (sum == 15);
}

//===================================================================//benchmark

// Benchmark for addition
TEST_CASE ("Benchmark for stoneydsp::uchar_t addition",
           "[core][types][uchar_t][benchmark]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::uchar_t a = 12_uchar_t;
  ::stoneydsp::uchar_t b = 34_uchar_t;

  BENCHMARK ("Addition") { return a + b; };
}

// Benchmark for subtraction
TEST_CASE ("Benchmark for stoneydsp::uchar_t subtraction",
           "[core][types][uchar_t][benchmark]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::uchar_t a = 34_uchar_t;
  ::stoneydsp::uchar_t b = 12_uchar_t;

  BENCHMARK ("Subtraction") { return a - b; };
}

// Benchmark for multiplication
TEST_CASE ("Benchmark for stoneydsp::uchar_t multiplication",
           "[core][types][uchar_t][benchmark]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::uchar_t a = 12_uchar_t;
  ::stoneydsp::uchar_t b = 2_uchar_t;

  BENCHMARK ("Multiplication") { return a * b; };
}

// Benchmark for division
TEST_CASE ("Benchmark for stoneydsp::uchar_t division",
           "[core][types][uchar_t][benchmark]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::uchar_t a = 12_uchar_t;
  ::stoneydsp::uchar_t b = 2_uchar_t;

  BENCHMARK ("Division") { return a / b; };
}

// Benchmark for type conversion to int
TEST_CASE ("Benchmark for stoneydsp::uchar_t to int conversion",
           "[core][types][uchar_t][benchmark]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::uchar_t a = 12_uchar_t;

  BENCHMARK ("Conversion to int") { return static_cast<int> (a); };
}

// Benchmark for type conversion to float
TEST_CASE ("Benchmark for stoneydsp::uchar_t to float conversion",
           "[core][types][uchar_t][benchmark]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::uchar_t a = 12_uchar_t;

  BENCHMARK ("Conversion to float")
  {
    return static_cast< ::stoneydsp::float_t> (a);
  };
}

//============================================================================//

#endif // defined(STONEYDSP_BUILD_TEST)

//=========================================================================//EOF
