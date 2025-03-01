/**
 * @file int.test.cpp
 * @brief Test suite for stoneydsp::int_t
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

TEST_CASE ("[core][types][int_t][sizeof]", "[core][types][int_t][sizeof]")
{
  REQUIRE (sizeof (::stoneydsp::int_t) == 4UL);
}

//=====================================================================//alignof

TEST_CASE ("[core][types][int_t][alignof]", "[core][types][int_t][alignof]")
{
  REQUIRE (alignof (::stoneydsp::int_t) == 4UL);
}

//=================================================================//type_traits

TEST_CASE ("[core][types][int_t][type_traits][is_signed]",
           "[core][types][int_t][type_traits][is_signed]")
{
  REQUIRE (::std::is_signed< ::stoneydsp::int_t>::value);
}

TEST_CASE ("[core][types][int_t][type_traits][is_trivially_copyable]",
           "[core][types][int_t][type_traits][is_trivially_copyable]")
{
  REQUIRE (::std::is_trivially_copyable< ::stoneydsp::int_t>::value);
}

TEST_CASE ("[core][types][int_t][type_traits][is_standard_layout]",
           "[core][types][int_t][type_traits][is_standard_layout]")
{
  REQUIRE (::std::is_standard_layout< ::stoneydsp::int_t>::value);
}

//==============================================================//numeric_limits

TEST_CASE ("[core][types][int_t][numeric_limits]",
           "[core][types][int_t][numeric_limits]")
{
  // { -2147483648 }
  REQUIRE (::stoneydsp::numeric_limits< ::stoneydsp::int_t>::min ()
           == ::std::numeric_limits< ::stoneydsp::int_t>::min ());
  // { 2147483647 }
  REQUIRE (::stoneydsp::numeric_limits< ::stoneydsp::int_t>::max ()
           == ::std::numeric_limits< ::stoneydsp::int_t>::max ());
  // { -2147483648 }
  REQUIRE (::stoneydsp::numeric_limits< ::stoneydsp::int_t>::lowest ()
           == ::std::numeric_limits< ::stoneydsp::int_t>::lowest ());
}

//==============================================================//special_values

TEST_CASE ("[core][types][int_t][special_values]",
           "[core][types][int_t][special_values]")
{
  ::stoneydsp::int_t min_val
      = ::std::numeric_limits< ::stoneydsp::int_t>::min ();
  ::stoneydsp::int_t max_val
      = ::std::numeric_limits< ::stoneydsp::int_t>::max ();
  REQUIRE (min_val == -2147483648); // Minimum value for int_t
  REQUIRE (max_val == 2147483647);  // Maximum value for int_t
}

//==================================================================//endianness

TEST_CASE ("[core][types][int_t][endianness]",
           "[core][types][int_t][endianness]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::int_t value = 0x12345678_int_t;
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

TEST_CASE ("[core][types][int_t][rounding]", "[core][types][int_t][rounding]")
{
  ::stoneydsp::float_t a = 1.5f;
  ::stoneydsp::int_t b = static_cast< ::stoneydsp::int_t> (::std::round (a));
  REQUIRE (b == 2); // 1.5 rounded to nearest integer and cast to int_t
}

//==================================================================//arithmetic

TEST_CASE ("[core][types][int_t][arithmetic]",
           "[core][types][int_t][arithmetic]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::int_t a = 15000_int_t;
  ::stoneydsp::int_t b = 20000_int_t;

  REQUIRE (a + b == 35000);     // Addition
  REQUIRE (a - b == -5000);     // Subtraction
  REQUIRE (a * b == 300000000); // Multiplication
  REQUIRE (b / a == 1);         // Division
  REQUIRE (b % a == 5000);      // Modulo
}

//=====================================================================//bitwise

TEST_CASE ("[core][types][int_t][bitwise][logic]", "[core][types][int_t][bitwise][logic]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::int_t a = 5_int_t; // 0000 0000 0000 0000 0000 0000 0000 0101
  ::stoneydsp::int_t b = 3_int_t; // 0000 0000 0000 0000 0000 0000 0000 0011

  REQUIRE ((a & b) == 1); // AND: 0000 0000 0000 0000 0000 0000 0000 0001
  REQUIRE ((a | b) == 7); // OR:  0000 0000 0000 0000 0000 0000 0000 0111
  REQUIRE ((a ^ b) == 6); // XOR: 0000 0000 0000 0000 0000 0000 0000 0110
  REQUIRE (~a == -6);     // NOT: considering wrap-around for int_t
}

TEST_CASE ("[core][types][int_t][bitwise][arithmetic]", "[core][types][int_t][bitwise][arithmetic]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::int_t a = 5_int_t; // 0000 0000 0000 0000 0000 0000 0000 0101

  REQUIRE ((a << 1)
           == 10); // Left shift: 0000 0000 0000 0000 0000 0000 0000 1010
  REQUIRE ((a >> 1)
           == 2); // Right shift: 0000 0000 0000 0000 0000 0000 0000 0010
}

//==================================================================//comparison

TEST_CASE ("[core][types][int_t][comparison]",
           "[core][types][int_t][comparison]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::int_t a = 5_int_t;
  ::stoneydsp::int_t b = 3_int_t;

  REQUIRE ((a == b) == false);
  REQUIRE ((a != b) == true);
  REQUIRE ((a > b) == true);
  REQUIRE ((a < b) == false);
  REQUIRE ((a >= b) == true);
  REQUIRE ((a <= b) == false);
}

//===============================================================//serialization

TEST_CASE ("[core][types][int_t][serialization]",
           "[core][types][int_t][serialization]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::std::stringstream ss;
  ::stoneydsp::int_t originalValue = 42_int_t;
  ::stoneydsp::int_t deserializedValue;

  ss.write (reinterpret_cast<const char *> (&originalValue),
            sizeof (originalValue));
  ss.read (reinterpret_cast<char *> (&deserializedValue),
           sizeof (deserializedValue));

  REQUIRE (originalValue == deserializedValue);
}

//=======================================================//boundary_and_overflow

TEST_CASE ("[core][types][int_t][boundary][overflow]",
           "[core][types][int_t][boundary][overflow]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::int_t a = 2147483647_int_t;
  ::stoneydsp::int_t b = 1_int_t;

  REQUIRE (static_cast< ::stoneydsp::int_t> (a + b)
           == -2147483648); // Check overflow wrap-around behaviour
}

//======================================================//boundary_and_underflow

TEST_CASE ("[core][types][int_t][boundary][underflow]",
           "[core][types][int_t][boundary][underflow]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::int_t a = -2147483647_int_t - 1_int_t; // _int;
  ::stoneydsp::int_t b = 1_int_t;

  REQUIRE (static_cast< ::stoneydsp::int_t> (a - b)
           == 2147483647); // Check underflow wrap-around behavior
}

//===============================================================//compatibility

TEST_CASE ("[core][types][int_t][compatibility]",
           "[core][types][int_t][compatibility]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::std::vector< ::stoneydsp::int_t> vec
      = { 5_int_t, 3_int_t, 4_int_t, 1_int_t, 2_int_t };

  // Use std::sort to sort the vector
  ::std::sort (vec.begin (), vec.end ());

  // Verify the vector is sorted
  REQUIRE (vec
           == ::std::vector< ::stoneydsp::int_t>{ 1_int_t, 2_int_t, 3_int_t,
                                                  4_int_t, 5_int_t });

  // Use std::accumulate to sum the elements
  ::stoneydsp::int_t sum = ::std::accumulate (vec.begin (), vec.end (),
                                              ::stoneydsp::int_t (0_int_t));

  // Verify the sum is correct
  REQUIRE (sum == 15);
}

//===================================================================//benchmark

// Benchmark for addition
TEST_CASE ("[core][types][int_t][benchmark][addition]",
           "[core][types][int_t][benchmark][addition]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::int_t a = 1200_int_t;
  ::stoneydsp::int_t b = 3400_int_t;

  BENCHMARK ("Addition") { return a + b; };
}

// Benchmark for subtraction
TEST_CASE ("[core][types][int_t][benchmark][subtraction]",
           "[core][types][int_t][benchmark][subtraction]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::int_t a = 3400_int_t;
  ::stoneydsp::int_t b = 1200_int_t;

  BENCHMARK ("Subtraction") { return a - b; };
}

// Benchmark for multiplication
TEST_CASE ("[core][types][int_t][benchmark][multiplication]",
           "[core][types][int_t][benchmark][multiplication]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::int_t a = 1200_int_t;
  ::stoneydsp::int_t b = 2_int_t;

  BENCHMARK ("Multiplication") { return a * b; };
}

// Benchmark for division
TEST_CASE ("[core][types][int_t][benchmark][division]",
           "[core][types][int_t][benchmark][division]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::int_t a = 1200_int_t;
  ::stoneydsp::int_t b = 2_int_t;

  BENCHMARK ("Division") { return a / b; };
}

// Benchmark for type conversion to int
TEST_CASE ("[core][types][int_t][benchmark][division][conversion][int]",
           "[core][types][int_t][benchmark][division][conversion][int]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::int_t a = 1200_int_t;

  BENCHMARK ("Conversion to int") { return static_cast<int> (a); };
}

// Benchmark for type conversion to float
TEST_CASE ("[core][types][int_t][benchmark][division][conversion][float]",
           "[core][types][int_t][benchmark][division][conversion][float]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::int_t a = 1200_int_t;

  BENCHMARK ("Conversion to float")
  {
    return static_cast< ::stoneydsp::float_t> (a);
  };
}

//============================================================================//

#endif // defined(STONEYDSP_BUILD_TEST)

//=========================================================================//EOF
