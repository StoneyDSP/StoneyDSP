/**
 * @file ullong.test.cpp
 * @brief Test suite for stoneydsp::ullong_t
 * @copyright Copyright (c) 2025
 *
 */

//==============================================================================

#include "stoneydsp/core/types/ullong.h"

//==============================================================================

#if defined(STONEYDSP_BUILD_TEST) && defined(STONEYDSP_BUILD_CORE)

//==============================================================================

  #include "../../../utils.test.hpp"

//================================================================//requirements

STONEYDSP_TEST_CASE ("[core][types][ullong_t][requirements]",
                     "[core][types][ullong_t][requirements]")
{
  STONEYDSP_SECTION ("[core][types][ullong_t][requirements][max]")
  {
    bool result = false;
  #if defined(ULLONG_MAX)
    result = true;
  #endif
    STONEYDSP_REQUIRE (result == true);
  }
}

//======================================================================//sizeof

STONEYDSP_TEST_CASE ("[core][types][ullong_t][sizeof]",
                     "[core][types][ullong_t][sizeof]")
{
  STONEYDSP_REQUIRE (sizeof (::stoneydsp::ullong_t) == 8UL);
}

//=====================================================================//alignof

STONEYDSP_TEST_CASE ("[core][types][ullong_t][alignof]",
                     "[core][types][ullong_t][alignof]")
{
  STONEYDSP_REQUIRE (alignof (::stoneydsp::ullong_t) == 8UL);
}

//=================================================================//type_traits

STONEYDSP_TEST_CASE ("[core][types][ullong_t][type_traits][is_integral]",
                     "[core][types][ullong_t][type_traits][is_integral]")
{
  STONEYDSP_REQUIRE (::std::is_integral< ::stoneydsp::ullong_t>::value);
}

STONEYDSP_TEST_CASE ("[core][types][ullong_t][type_traits][is_unsigned]",
                     "[core][types][ullong_t][type_traits][is_unsigned]")
{
  STONEYDSP_REQUIRE (::std::is_unsigned< ::stoneydsp::ullong_t>::value);
}

STONEYDSP_TEST_CASE ("[core][types][ullong_t][type_traits][is_arithmetic]",
                     "[core][types][ullong_t][type_traits][is_arithmetic]")
{
  STONEYDSP_REQUIRE (::std::is_arithmetic< ::stoneydsp::ullong_t>::value);
}

STONEYDSP_TEST_CASE ("[core][types][ullong_t][type_traits][is_pointer]",
                     "[core][types][ullong_t][type_traits][is_pointer]")
{
  STONEYDSP_REQUIRE (!::std::is_pointer< ::stoneydsp::ullong_t>::value);
}

STONEYDSP_TEST_CASE ("[core][types][ullong_t][type_traits][is_const]",
                     "[core][types][ullong_t][type_traits][is_const]")
{
  STONEYDSP_REQUIRE (!::std::is_const< ::stoneydsp::ullong_t>::value);
}

STONEYDSP_TEST_CASE ("[core][types][ullong_t][type_traits][is_empty]",
                     "[core][types][ullong_t][type_traits][is_empty]")
{
  STONEYDSP_REQUIRE (!::std::is_empty< ::stoneydsp::ullong_t>::value);
}

STONEYDSP_TEST_CASE (
    "[core][types][ullong_t][type_traits][is_trivially_copyable]",
    "[core][types][ullong_t][type_traits][is_trivially_copyable]")
{
  STONEYDSP_REQUIRE (
      ::std::is_trivially_copyable< ::stoneydsp::ullong_t>::value);
}

STONEYDSP_TEST_CASE (
    "[core][types][ullong_t][type_traits][is_standard_layout]",
    "[core][types][ullong_t][type_traits][is_standard_layout]")
{
  STONEYDSP_REQUIRE (::std::is_standard_layout< ::stoneydsp::ullong_t>::value);
}

//==============================================================//numeric_limits

STONEYDSP_TEST_CASE ("[core][types][ullong_t][numeric_limits]",
                     "[core][types][ullong_t][numeric_limits]")
{
  // { 0U }
  STONEYDSP_REQUIRE (
      ::stoneydsp::numeric_limits< ::stoneydsp::ullong_t>::min ()
      == ::std::numeric_limits< ::stoneydsp::ullong_t>::min ());

  // { 18446744073709551615UL }
  STONEYDSP_REQUIRE (
      ::stoneydsp::numeric_limits< ::stoneydsp::ullong_t>::max ()
      == ::std::numeric_limits< ::stoneydsp::ullong_t>::max ());

  // { 0U }
  STONEYDSP_REQUIRE (
      ::stoneydsp::numeric_limits< ::stoneydsp::ullong_t>::lowest ()
      == ::std::numeric_limits< ::stoneydsp::ullong_t>::lowest ());
}

//==============================================================//special_values

STONEYDSP_TEST_CASE ("[core][types][ullong_t][special_values]",
                     "[core][types][ullong_t][special_values]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::ullong_t min_val
      = ::std::numeric_limits< ::stoneydsp::ullong_t>::min ();
  ::stoneydsp::ullong_t max_val
      = ::std::numeric_limits< ::stoneydsp::ullong_t>::max ();
  STONEYDSP_REQUIRE (min_val == 0_ullong_t); // Minimum value for ullong_t
  STONEYDSP_REQUIRE (
      max_val == 18446744073709551615_ullong_t); // Maximum value for ullong_t
}

//==================================================================//endianness

STONEYDSP_TEST_CASE ("[core][types][ullong_t][endianness]",
                     "[core][types][ullong_t][endianness]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::ullong_t value = 0x123456789ABCDEF0_ullong_t;
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

STONEYDSP_TEST_CASE ("[core][types][ullong_t][rounding]",
                     "[core][types][ullong_t][rounding]")
{
  float a = 1.5f;
  ::stoneydsp::ullong_t b
      = static_cast< ::stoneydsp::ullong_t> (::std::round (a));
  STONEYDSP_REQUIRE (
      b == 2); // 1.5 rounded to nearest integer and cast to ullong_t
}

//==================================================================//arithmetic

STONEYDSP_TEST_CASE ("[core][types][ullong_t][arithmetic]",
                     "[core][types][ullong_t][arithmetic]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::ullong_t a = 1500000000000000000_ullong_t;
  ::stoneydsp::ullong_t b = 2_ullong_t;

  STONEYDSP_REQUIRE (a + b == 1500000000000000002); // Addition
  STONEYDSP_REQUIRE (a - b == 1499999999999999998); // Subtraction
  STONEYDSP_REQUIRE (a * b == 3000000000000000000); // Multiplication
  STONEYDSP_REQUIRE (b / a == 0);                   // Division
  STONEYDSP_REQUIRE (b % a == 2);                   // Modulo
}

//===============================================================//bitwise

STONEYDSP_TEST_CASE ("[core][types][ullong_t][bitwise][logic]",
                     "[core][types][ullong_t][bitwise][logic]")
{
  using namespace ::stoneydsp::core::types::literals;

  // clang-format off
  ::stoneydsp::ullong_t a = 5_ullong_t; // 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0101
  ::stoneydsp::ullong_t b = 3_ullong_t; // 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0011

  STONEYDSP_REQUIRE ((a & b) == 1); // AND: 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0001
  STONEYDSP_REQUIRE ((a | b) == 7); // OR:  0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0111
  STONEYDSP_REQUIRE ((a ^ b) == 6); // XOR: 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0110
  STONEYDSP_REQUIRE (
      (~a & 0xFFFFFFFFFFFFFFFFUL)
      == 18446744073709551610UL); // NOT: 1111 1111 1111 1111 1111 1111 1111 1111 1111 1111 1111 1111 1111 1111 1111 1010 (considering ullong_t wrap-around)
	// clang-format off
}

STONEYDSP_TEST_CASE ("[core][types][ullong_t][bitwise][arithmetic]", "[core][types][ullong_t][bitwise][arithmetic]")
{
	using namespace ::stoneydsp::core::types::literals;

	// clang-format off
  ::stoneydsp::ullong_t a = 5_ullong_t; // 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0101

	STONEYDSP_REQUIRE ((a << 1) == 10);  // Left shift: 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 1010
  STONEYDSP_REQUIRE ((a >> 1) == 2);   // Right shift: 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0010
  // clang-format on
}

//===============================================================//comparison

STONEYDSP_TEST_CASE ("[core][types][ullong_t][comparison]",
                     "[core][types][ullong_t][comparison]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::ullong_t a = 5_ullong_t;
  ::stoneydsp::ullong_t b = 3_ullong_t;

  STONEYDSP_REQUIRE ((a == b) == false);
  STONEYDSP_REQUIRE ((a != b) == true);
  STONEYDSP_REQUIRE ((a > b) == true);
  STONEYDSP_REQUIRE ((a < b) == false);
  STONEYDSP_REQUIRE ((a >= b) == true);
  STONEYDSP_REQUIRE ((a <= b) == false);
}

//===============================================================//serialization

STONEYDSP_TEST_CASE ("[core][types][ullong_t][serialization]",
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

  STONEYDSP_REQUIRE (originalValue == deserializedValue);
}

//=======================================================//boundary_and_overflow

STONEYDSP_TEST_CASE ("[core][types][ullong_t][boundary][overflow]",
                     "[core][types][ullong_t][boundary][overflow]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::ullong_t a = 18446744073709551615_ullong_t;
  ::stoneydsp::ullong_t b = 1_ullong_t;

  STONEYDSP_REQUIRE (static_cast< ::stoneydsp::ullong_t> (a + b)
                     == 0_ullong_t); // Check overflow wrap-around behaviour
}

//======================================================//boundary_and_underflow

STONEYDSP_TEST_CASE ("[core][types][ullong_t][boundary][underflow]",
                     "[core][types][ullong_t][boundary][underflow]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::ullong_t a = 0_ullong_t;
  ::stoneydsp::ullong_t b = 1_ullong_t;

  STONEYDSP_REQUIRE (static_cast< ::stoneydsp::ullong_t> (a - b)
                     == 18446744073709551615_ullong_t); // Check underflow
                                                        // wrap-around behavior
}

//===============================================================//compatibility

STONEYDSP_TEST_CASE ("[core][types][ullong_t][compatibility]",
                     "[core][types][ullong_t][compatibility]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::std::vector< ::stoneydsp::ullong_t> vec
      = { 5_ullong_t, 3_ullong_t, 4_ullong_t, 1_ullong_t, 2_ullong_t };

  // Use std::sort to sort the vector
  ::std::sort (vec.begin (), vec.end ());

  // Verify the vector is sorted
  STONEYDSP_REQUIRE (
      vec
      == ::std::vector< ::stoneydsp::ullong_t>{
          1_ullong_t, 2_ullong_t, 3_ullong_t, 4_ullong_t, 5_ullong_t });

  // Use std::accumulate to sum the elements
  ::stoneydsp::ullong_t sum = ::std::accumulate (
      vec.begin (), vec.end (), ::stoneydsp::ullong_t (0_ullong_t));

  // Verify the sum is correct
  STONEYDSP_REQUIRE (sum == 15_ullong_t);
}

//===================================================================//benchmark

// Benchmark for addition
STONEYDSP_TEST_CASE ("[core][types][ullong_t][benchmark][addition]",
                     "[core][types][ullong_t][benchmark][addition]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::ullong_t a = 1200_ullong_t;
  ::stoneydsp::ullong_t b = 3400_ullong_t;

  STONEYDSP_BENCHMARK ("Addition") { return a + b; };
}

// Benchmark for subtraction
STONEYDSP_TEST_CASE ("[core][types][ullong_t][benchmark][subtraction]",
                     "[core][types][ullong_t][benchmark][subtraction]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::ullong_t a = 3400_ullong_t;
  ::stoneydsp::ullong_t b = 1200_ullong_t;

  STONEYDSP_BENCHMARK ("Subtraction") { return a - b; };
}

// Benchmark for multiplication
STONEYDSP_TEST_CASE ("[core][types][ullong_t][benchmark][multiplication]",
                     "[core][types][ullong_t][benchmark][multiplication]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::ullong_t a = 1200_ullong_t;
  ::stoneydsp::ullong_t b = 2_ullong_t;

  STONEYDSP_BENCHMARK ("Multiplication") { return a * b; };
}

// Benchmark for division
STONEYDSP_TEST_CASE ("[core][types][ullong_t][benchmark][division]",
                     "[core][types][ullong_t][benchmark][division]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::ullong_t a = 1200_ullong_t;
  ::stoneydsp::ullong_t b = 2_ullong_t;

  STONEYDSP_BENCHMARK ("Division") { return a / b; };
}

// Benchmark for type conversion to int
STONEYDSP_TEST_CASE ("[core][types][ullong_t][benchmark][conversion][int]",
                     "[core][types][ullong_t][benchmark][conversion][int]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::ullong_t a = 1200_ullong_t;

  STONEYDSP_BENCHMARK ("Conversion to int") { return static_cast<int> (a); };
}

// Benchmark for type conversion to float
STONEYDSP_TEST_CASE ("[core][types][ullong_t][benchmark][conversion][float]",
                     "[core][types][ullong_t][benchmark][conversion][float]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::ullong_t a = 1200_ullong_t;

  STONEYDSP_BENCHMARK ("Conversion to float")
  {
    return static_cast<float> (a);
  };
}

//============================================================================//

#endif // defined(STONEYDSP_BUILD_TEST)

//=========================================================================//EOF
