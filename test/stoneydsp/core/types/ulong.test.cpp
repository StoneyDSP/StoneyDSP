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

  #include "utils.test.hpp"

//======================================================================//sizeof

STONEYDSP_TEST_CASE ("[core][types][ulong_t][sizeof]",
                     "[core][types][ulong_t][sizeof]")
{
  STONEYDSP_REQUIRE (sizeof (::stoneydsp::ulong_t) == 8UL);
}

//=====================================================================//alignof

STONEYDSP_TEST_CASE ("[core][types][ulong_t][alignof]",
                     "[core][types][ulong_t][alignof]")
{
  STONEYDSP_REQUIRE (alignof (::stoneydsp::ulong_t) == 8UL);
}

//=================================================================//type_traits

STONEYDSP_TEST_CASE ("[core][types][ulong_t][type_traits][is_integral]",
                     "[core][types][ulong_t][type_traits][is_integral]")
{
  STONEYDSP_REQUIRE (::std::is_integral< ::stoneydsp::ulong_t>::value);
}

STONEYDSP_TEST_CASE ("[core][types][ulong_t][type_traits][is_unsigned]",
                     "[core][types][ulong_t][type_traits][is_unsigned]")
{
  STONEYDSP_REQUIRE (::std::is_unsigned< ::stoneydsp::ulong_t>::value);
}

STONEYDSP_TEST_CASE ("[core][types][ulong_t][type_traits][is_arithmetic]",
                     "[core][types][ulong_t][type_traits][is_arithmetic]")
{
  STONEYDSP_REQUIRE (::std::is_arithmetic< ::stoneydsp::ulong_t>::value);
}

STONEYDSP_TEST_CASE ("[core][types][ulong_t][type_traits][is_pointer]",
                     "[core][types][ulong_t][type_traits][is_pointer]")
{
  STONEYDSP_REQUIRE (!::std::is_pointer< ::stoneydsp::ulong_t>::value);
}

STONEYDSP_TEST_CASE ("[core][types][ulong_t][type_traits][is_const]",
                     "[core][types][ulong_t][type_traits][is_const]")
{
  STONEYDSP_REQUIRE (!::std::is_const< ::stoneydsp::ulong_t>::value);
}

STONEYDSP_TEST_CASE ("[core][types][ulong_t][type_traits][is_empty]",
                     "[core][types][ulong_t][type_traits][is_empty]")
{
  STONEYDSP_REQUIRE (!::std::is_empty< ::stoneydsp::ulong_t>::value);
}

STONEYDSP_TEST_CASE (
    "[core][types][ulong_t][type_traits][is_trivially_copyable]",
    "[core][types][ulong_t][type_traits][is_trivially_copyable]")
{
  STONEYDSP_REQUIRE (
      ::std::is_trivially_copyable< ::stoneydsp::ulong_t>::value);
}

STONEYDSP_TEST_CASE ("[core][types][ulong_t][type_traits][is_standard_layout]",
                     "[core][types][ulong_t][type_traits][is_standard_layout]")
{
  STONEYDSP_REQUIRE (::std::is_standard_layout< ::stoneydsp::ulong_t>::value);
}

//==============================================================//numeric_limits

STONEYDSP_TEST_CASE ("[core][types][ulong_t][numeric_limits]",
                     "[core][types][ulong_t][numeric_limits]")
{
  // { 0U }
  STONEYDSP_REQUIRE (::stoneydsp::numeric_limits< ::stoneydsp::ulong_t>::min ()
                     == ::std::numeric_limits< ::stoneydsp::ulong_t>::min ());

  // { 18446744073709551615UL }
  STONEYDSP_REQUIRE (::stoneydsp::numeric_limits< ::stoneydsp::ulong_t>::max ()
                     == ::std::numeric_limits< ::stoneydsp::ulong_t>::max ());

  // { 0U }
  STONEYDSP_REQUIRE (
      ::stoneydsp::numeric_limits< ::stoneydsp::ulong_t>::lowest ()
      == ::std::numeric_limits< ::stoneydsp::ulong_t>::lowest ());
}

//==============================================================//special_values

STONEYDSP_TEST_CASE ("[core][types][ulong_t][special_values]",
                     "[core][types][ulong_t][special_values]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::ulong_t min_val
      = ::std::numeric_limits< ::stoneydsp::ulong_t>::min ();
  ::stoneydsp::ulong_t max_val
      = ::std::numeric_limits< ::stoneydsp::ulong_t>::max ();
  STONEYDSP_REQUIRE (min_val == 0_ulong_t); // Minimum value for ulong_t
  STONEYDSP_REQUIRE (
      max_val == 18446744073709551615_ulong_t); // Maximum value for ulong_t
}

//==================================================================//endianness

STONEYDSP_TEST_CASE ("[core][types][ulong_t][endianness]",
                     "[core][types][ulong_t][endianness]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::ulong_t value = 0x123456789ABCDEF0_ulong_t;
  ::std::uint8_t *bytePtr = reinterpret_cast< ::std::uint8_t *> (&value);

  if (bytePtr[0] == 0xF0)
    {
      STONEYDSP_REQUIRE (true); // Little-endian
    }
  else if (bytePtr[0] == 0x12)
    {
      STONEYDSP_REQUIRE (true); // Big-endian
    }
  else
    {
      STONEYDSP_REQUIRE (false); // Unknown endianness
    }
}

//====================================================================//rounding

STONEYDSP_TEST_CASE ("[core][types][ulong_t][rounding]",
                     "[core][types][ulong_t][rounding]")
{
  ::stoneydsp::float_t a = 1.5f;
  ::stoneydsp::ulong_t b
      = static_cast< ::stoneydsp::ulong_t> (::std::round (a));
  STONEYDSP_REQUIRE (
      b == 2); // 1.5 rounded to nearest integer and cast to ulong_t
}

//==================================================================//arithmetic

STONEYDSP_TEST_CASE ("[core][types][ulong_t][arithmetic]",
                     "[core][types][ulong_t][arithmetic]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::ulong_t a = 1500000000000000000_ulong_t;
  ::stoneydsp::ulong_t b = 2_ulong_t;

  STONEYDSP_REQUIRE (a + b == 1500000000000000002); // Addition
  STONEYDSP_REQUIRE (a - b == 1499999999999999998); // Subtraction
  STONEYDSP_REQUIRE (a * b == 3000000000000000000); // Multiplication
  STONEYDSP_REQUIRE (b / a == 0);                   // Division
  STONEYDSP_REQUIRE (b % a == 2);                   // Modulo
}

//=====================================================================//bitwise

STONEYDSP_TEST_CASE ("[core][types][ulong_t][bitwise][logic]",
                     "[core][types][ulong_t][bitwise][logic]")
{
  using namespace ::stoneydsp::core::types::literals;

  // clang-format off
  ::stoneydsp::ulong_t a = 5_ulong_t; // 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0101
  ::stoneydsp::ulong_t b = 3_ulong_t; // 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0011

  STONEYDSP_REQUIRE ((a & b) == 1); // AND: 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0001
  STONEYDSP_REQUIRE ((a | b) == 7); // OR:  0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0111
  STONEYDSP_REQUIRE ((a ^ b) == 6); // XOR: 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0110
  STONEYDSP_REQUIRE (
      (~a & 0xFFFFFFFFFFFFFFFFUL)
      == 18446744073709551610UL); // NOT: 1111 1111 1111 1111 1111 1111 1111 1111 1111 1111 1111 1111 1111 1111 1111 1010 (considering ulong_t wrap-around)
	// clang-format off
}

STONEYDSP_TEST_CASE ("[core][types][ulong_t][bitwise][arithmetic]", "[core][types][ulong_t][bitwise][arithmetic]")
{
	using namespace ::stoneydsp::core::types::literals;

	// clang-format off
  ::stoneydsp::ulong_t a = 5_ulong_t; // 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0101

	STONEYDSP_REQUIRE ((a << 1) == 10);  // Left shift: 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 1010
  STONEYDSP_REQUIRE ((a >> 1) == 2);   // Right shift: 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0010
  // clang-format on
}

//===============================================================//comparison

STONEYDSP_TEST_CASE ("[core][types][ulong_t][comparison]",
                     "[core][types][ulong_t][comparison]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::ulong_t a = 5_ulong_t;
  ::stoneydsp::ulong_t b = 3_ulong_t;

  STONEYDSP_REQUIRE ((a == b) == false);
  STONEYDSP_REQUIRE ((a != b) == true);
  STONEYDSP_REQUIRE ((a > b) == true);
  STONEYDSP_REQUIRE ((a < b) == false);
  STONEYDSP_REQUIRE ((a >= b) == true);
  STONEYDSP_REQUIRE ((a <= b) == false);
}

//===============================================================//serialization

STONEYDSP_TEST_CASE ("[core][types][ulong_t][serialization]",
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

  STONEYDSP_REQUIRE (originalValue == deserializedValue);
}

//=======================================================//boundary_and_overflow

STONEYDSP_TEST_CASE ("[core][types][ulong_t][boundary][overflow]",
                     "[core][types][ulong_t][boundary][overflow]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::ulong_t a = 18446744073709551615_ulong_t;
  ::stoneydsp::ulong_t b = 1_ulong_t;

  STONEYDSP_REQUIRE (static_cast< ::stoneydsp::ulong_t> (a + b)
                     == 0_ulong_t); // Check overflow wrap-around behaviour
}

//======================================================//boundary_and_underflow

STONEYDSP_TEST_CASE ("[core][types][ulong_t][boundary][underflow]",
                     "[core][types][ulong_t][boundary][underflow]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::ulong_t a = 0_ulong_t;
  ::stoneydsp::ulong_t b = 1_ulong_t;

  STONEYDSP_REQUIRE (
      static_cast< ::stoneydsp::ulong_t> (a - b)
      == 18446744073709551615_ulong_t); // Check underflow wrap-around behavior
}

//===============================================================//compatibility

STONEYDSP_TEST_CASE ("[core][types][ulong_t][compatibility]",
                     "[core][types][ulong_t][compatibility]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::std::vector< ::stoneydsp::ulong_t> vec
      = { 5_ulong_t, 3_ulong_t, 4_ulong_t, 1_ulong_t, 2_ulong_t };

  // Use std::sort to sort the vector
  ::std::sort (vec.begin (), vec.end ());

  // Verify the vector is sorted
  STONEYDSP_REQUIRE (
      vec
      == ::std::vector< ::stoneydsp::ulong_t>{ 1_ulong_t, 2_ulong_t, 3_ulong_t,
                                               4_ulong_t, 5_ulong_t });

  // Use std::accumulate to sum the elements
  ::stoneydsp::ulong_t sum = ::std::accumulate (
      vec.begin (), vec.end (), ::stoneydsp::ulong_t (0_ulong_t));

  // Verify the sum is correct
  STONEYDSP_REQUIRE (sum == 15_ulong_t);
}

//===================================================================//benchmark

// Benchmark for addition
STONEYDSP_TEST_CASE ("[core][types][ulong_t][benchmark][addition]",
                     "[core][types][ulong_t][benchmark][addition]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::ulong_t a = 1200_ulong_t;
  ::stoneydsp::ulong_t b = 3400_ulong_t;

  STONEYDSP_BENCHMARK ("Addition") { return a + b; };
}

// Benchmark for subtraction
STONEYDSP_TEST_CASE ("[core][types][ulong_t][benchmark][subtraction]",
                     "[core][types][ulong_t][benchmark][subtraction]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::ulong_t a = 3400_ulong_t;
  ::stoneydsp::ulong_t b = 1200_ulong_t;

  STONEYDSP_BENCHMARK ("Subtraction") { return a - b; };
}

// Benchmark for multiplication
STONEYDSP_TEST_CASE ("[core][types][ulong_t][benchmark][multiplication]",
                     "[core][types][ulong_t][benchmark][multiplication]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::ulong_t a = 1200_ulong_t;
  ::stoneydsp::ulong_t b = 2_ulong_t;

  STONEYDSP_BENCHMARK ("Multiplication") { return a * b; };
}

// Benchmark for division
STONEYDSP_TEST_CASE ("[core][types][ulong_t][benchmark][division]",
                     "[core][types][ulong_t][benchmark][division]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::ulong_t a = 1200_ulong_t;
  ::stoneydsp::ulong_t b = 2_ulong_t;

  STONEYDSP_BENCHMARK ("Division") { return a / b; };
}

// Benchmark for type conversion to int
STONEYDSP_TEST_CASE ("[core][types][ulong_t][benchmark][conversion][int]",
                     "[core][types][ulong_t][benchmark][conversion][int]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::ulong_t a = 1200_ulong_t;

  STONEYDSP_BENCHMARK ("Conversion to int") { return static_cast<int> (a); };
}

// Benchmark for type conversion to float
STONEYDSP_TEST_CASE ("[core][types][ulong_t][benchmark][conversion][float]",
                     "[core][types][ulong_t][benchmark][conversion][float]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::ulong_t a = 1200_ulong_t;

  STONEYDSP_BENCHMARK ("Conversion to float")
  {
    return static_cast<float> (a);
  };
}

//============================================================================//

#endif // defined(STONEYDSP_BUILD_TEST)

//=========================================================================//EOF
