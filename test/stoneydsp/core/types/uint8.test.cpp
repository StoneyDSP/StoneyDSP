/**
 * @file uint8.test.cpp
 * @brief Test suite for stoneydsp::uint8_t
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

STONEYDSP_TEST_CASE ("[core][types][uint8_t][sizeof]",
                     "[core][types][uint8_t][sizeof]")
{
  STONEYDSP_REQUIRE (sizeof (::stoneydsp::uint8_t) == 1UL);
}

//=====================================================================//alignof

STONEYDSP_TEST_CASE ("[core][types][uint8_t][alignof]",
                     "[core][types][uint8_t][alignof]")
{
  STONEYDSP_REQUIRE (alignof (::stoneydsp::uint8_t) == 1UL);
}

//=================================================================//type_traits

STONEYDSP_TEST_CASE ("[core][types][uint8_t][type_traits][is_integral]",
                     "[core][types][uint8_t][type_traits][is_integral]")
{
  STONEYDSP_REQUIRE (::std::is_integral< ::stoneydsp::uint8_t>::value);
}

STONEYDSP_TEST_CASE ("[core][types][uint8_t][type_traits][is_unsigned]",
                     "[core][types][uint8_t][type_traits][is_unsigned]")
{
  STONEYDSP_REQUIRE (::std::is_unsigned< ::stoneydsp::uint8_t>::value);
}

STONEYDSP_TEST_CASE ("[core][types][uint8_t][type_traits][is_arithmetic]",
                     "[core][types][uint8_t][type_traits][is_arithmetic]")
{
  STONEYDSP_REQUIRE (::std::is_arithmetic< ::stoneydsp::uint8_t>::value);
}

STONEYDSP_TEST_CASE ("[core][types][uint8_t][type_traits][is_pointer]",
                     "[core][types][uint8_t][type_traits][is_pointer]")
{
  STONEYDSP_REQUIRE (!::std::is_pointer< ::stoneydsp::uint8_t>::value);
}

STONEYDSP_TEST_CASE ("[core][types][uint8_t][type_traits][is_const]",
                     "[core][types][uint8_t][type_traits][is_const]")
{
  STONEYDSP_REQUIRE (!::std::is_const< ::stoneydsp::uint8_t>::value);
}

STONEYDSP_TEST_CASE ("[core][types][uint8_t][type_traits][is_empty]",
                     "[core][types][uint8_t][type_traits][is_empty]")
{
  STONEYDSP_REQUIRE (!::std::is_empty< ::stoneydsp::uint8_t>::value);
}

STONEYDSP_TEST_CASE (
    "[core][types][uint8_t][type_traits][is_trivially_copyable]",
    "[core][types][uint8_t][type_traits][is_trivially_copyable]")
{
  STONEYDSP_REQUIRE (
      ::std::is_trivially_copyable< ::stoneydsp::uint8_t>::value);
}

STONEYDSP_TEST_CASE ("[core][types][uint8_t][type_traits][is_standard_layout]",
                     "[core][types][uint8_t][type_traits][is_standard_layout]")
{
  STONEYDSP_REQUIRE (::std::is_standard_layout< ::stoneydsp::uint8_t>::value);
}

//==============================================================//numeric_limits

STONEYDSP_TEST_CASE ("[core][types][uint8_t][numeric_limits]",
                     "[core][types][uint8_t][numeric_limits]")
{
  // { 0U }
  STONEYDSP_REQUIRE (::stoneydsp::numeric_limits< ::stoneydsp::uint8_t>::min ()
                     == ::std::numeric_limits< ::stoneydsp::uint8_t>::min ());
  // { 255 }
  STONEYDSP_REQUIRE (::stoneydsp::numeric_limits< ::stoneydsp::uint8_t>::max ()
                     == ::std::numeric_limits< ::stoneydsp::uint8_t>::max ());
  // { 0U }
  STONEYDSP_REQUIRE (
      ::stoneydsp::numeric_limits< ::stoneydsp::uint8_t>::lowest ()
      == ::std::numeric_limits< ::stoneydsp::uint8_t>::lowest ());
}

//==============================================================//special_values

STONEYDSP_TEST_CASE ("[core][types][uint8_t][special_values]",
                     "[core][types][uint8_t][special_values]")
{
  ::stoneydsp::uint8_t min_val
      = ::std::numeric_limits< ::stoneydsp::uint8_t>::min ();
  ::stoneydsp::uint8_t max_val
      = ::std::numeric_limits< ::stoneydsp::uint8_t>::max ();
  STONEYDSP_REQUIRE (min_val == 0U);   // Minimum value for uint8_t
  STONEYDSP_REQUIRE (max_val == 255U); // Maximum value for uint8_t
}

//==================================================================//endianness

STONEYDSP_TEST_CASE ("[core][types][uint8_t][endianness]",
                     "[core][types][uint8_t][endianness]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::uint8_t value = 0x12_uint8_t;
  ::std::uint8_t *bytePtr = reinterpret_cast< ::std::uint8_t *> (&value);

  if (bytePtr[0] == 0x12)
    {
      STONEYDSP_REQUIRE (true); // Little-endian and Big-endian will look the
                                // same for a single byte
    }
  else
    {
      STONEYDSP_REQUIRE (false); // Unknown endianness
    }
}

//====================================================================//rounding

STONEYDSP_TEST_CASE ("[core][types][uint8_t][rounding]",
                     "[core][types][uint8_t][rounding]")
{
  ::stoneydsp::float_t a = 1.5f;
  ::stoneydsp::uint8_t b
      = static_cast< ::stoneydsp::uint8_t> (::std::round (a));
  STONEYDSP_REQUIRE (
      b == 2); // 1.5 rounded to nearest integer and cast to uint8_t
}

//==================================================================//arithmetic

STONEYDSP_TEST_CASE ("[core][types][uint8_t][arithmetic]",
                     "[core][types][uint8_t][arithmetic]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::uint8_t a = 15_uint8_t;
  ::stoneydsp::uint8_t b = 20_uint8_t;

  STONEYDSP_REQUIRE (a + b == 35); // Addition
  STONEYDSP_REQUIRE (static_cast<int> (a - b)
                     == static_cast<int> (-5)); // Subtraction (wrap-around)
  STONEYDSP_REQUIRE (a * b == 300);             // Multiplication
  STONEYDSP_REQUIRE (b / a == 1);               // Division
  STONEYDSP_REQUIRE (b % a == 5);               // Modulo
}
//=====================================================================//bitwise

STONEYDSP_TEST_CASE ("[core][types][uint8_t][bitwise][logic]",
                     "[core][types][uint8_t][bitwise][logic]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::uint8_t a = 5_uint8_t; // 0101
  ::stoneydsp::uint8_t b = 3_uint8_t; // 0011

  STONEYDSP_REQUIRE ((a & b) == 1); // AND: 0001
  STONEYDSP_REQUIRE ((a | b) == 7); // OR: 0111
  STONEYDSP_REQUIRE ((a ^ b) == 6); // XOR: 0110
  STONEYDSP_REQUIRE (
      (~a & 0xFF) == 250); // NOT: 1111_1010 (considering uint8_t wrap-around)
}

STONEYDSP_TEST_CASE ("[core][types][uint8_t][bitwise][arithmetic]",
                     "[core][types][uint8_t][bitwise][arithmetic]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::uint8_t a = 5_uint8_t; // 0101
  STONEYDSP_REQUIRE ((a << 1) == 10); // Left shift: 1010
  STONEYDSP_REQUIRE ((a >> 1) == 2);  // Right shift: 0010
}

//==================================================================//comparison

STONEYDSP_TEST_CASE ("[core][types][uint8_t][comparison]",
                     "[core][types][uint8_t][comparison]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::uint8_t a = 5_uint8_t;
  ::stoneydsp::uint8_t b = 3_uint8_t;

  STONEYDSP_REQUIRE ((a == b) == false);
  STONEYDSP_REQUIRE ((a != b) == true);
  STONEYDSP_REQUIRE ((a > b) == true);
  STONEYDSP_REQUIRE ((a < b) == false);
  STONEYDSP_REQUIRE ((a >= b) == true);
  STONEYDSP_REQUIRE ((a <= b) == false);
}

//===============================================================//serialization

STONEYDSP_TEST_CASE ("[core][types][uint8_t][serialization]",
                     "[core][types][uint8_t][serialization]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::std::stringstream ss;

  ::stoneydsp::uint8_t originalValue = 42_uint8_t;
  ::stoneydsp::uint8_t deserializedValue;

  ss.write (reinterpret_cast<const char *> (&originalValue),
            sizeof (originalValue));
  ss.read (reinterpret_cast<char *> (&deserializedValue),
           sizeof (deserializedValue));

  STONEYDSP_REQUIRE (originalValue == deserializedValue);
}

//=======================================================//boundary_and_overflow

STONEYDSP_TEST_CASE ("[core][types][uint8_t][boundary][overflow]",
                     "[core][types][uint8_t][boundary][overflow]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::uint8_t a = 255_uint8_t;
  ::stoneydsp::uint8_t b = 1_uint8_t;

  STONEYDSP_REQUIRE (static_cast< ::stoneydsp::uint8_t> (a + b)
                     == 0); // Check overflow wrap-around behaviour
}

//======================================================//boundary_and_underflow

STONEYDSP_TEST_CASE ("[core][types][uint8_t][boundary][underflow]",
                     "[core][types][uint8_t][boundary][underflow]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::uint8_t a = 0_uint8_t;
  ::stoneydsp::uint8_t b = 1_uint8_t;

  STONEYDSP_REQUIRE (static_cast< ::stoneydsp::uint8_t> (a - b)
                     == 255); // Check underflow wrap-around behavior
}

//===============================================================//compatibility

STONEYDSP_TEST_CASE ("[core][types][uint8_t][compatibility]",
                     "[core][types][uint8_t][compatibility]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::std::vector< ::stoneydsp::uint8_t> vec
      = { 5_uint8_t, 3_uint8_t, 4_uint8_t, 1_uint8_t, 2_uint8_t };

  // Use std::sort to sort the vector
  ::std::sort (vec.begin (), vec.end ());

  // Verify the vector is sorted
  STONEYDSP_REQUIRE (
      vec
      == ::std::vector< ::stoneydsp::uint8_t>{ 1_uint8_t, 2_uint8_t, 3_uint8_t,
                                               4_uint8_t, 5_uint8_t });

  // Use std::accumulate to sum the elements
  ::stoneydsp::uint8_t sum = ::std::accumulate (
      vec.begin (), vec.end (), ::stoneydsp::uint8_t (0_uint8_t));

  // Verify the sum is correct
  STONEYDSP_REQUIRE (sum == 15);
}

//===================================================================//benchmark

// Benchmark for addition
STONEYDSP_TEST_CASE ("[core][types][uint8_t][benchmark][addition]",
                     "[core][types][uint8_t][benchmark][addition]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::uint8_t a = 12_uint8_t;
  ::stoneydsp::uint8_t b = 34_uint8_t;

  STONEYDSP_BENCHMARK ("Addition") { return a + b; };
}

// Benchmark for subtraction
STONEYDSP_TEST_CASE ("[core][types][uint8_t][benchmark][subtraction]",
                     "[core][types][uint8_t][benchmark][subtraction]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::uint8_t a = 34_uint8_t;
  ::stoneydsp::uint8_t b = 12_uint8_t;

  STONEYDSP_BENCHMARK ("Subtraction") { return a - b; };
}

// Benchmark for multiplication
STONEYDSP_TEST_CASE ("[core][types][uint8_t][benchmark][multiplication]",
                     "[core][types][uint8_t][benchmark][multiplication]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::uint8_t a = 12_uint8_t;
  ::stoneydsp::uint8_t b = 2_uint8_t;

  STONEYDSP_BENCHMARK ("Multiplication") { return a * b; };
}

// Benchmark for division
STONEYDSP_TEST_CASE ("[core][types][uint8_t][benchmark][division]",
                     "[core][types][uint8_t][benchmark][division]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::uint8_t a = 12_uint8_t;
  ::stoneydsp::uint8_t b = 2_uint8_t;

  STONEYDSP_BENCHMARK ("Division") { return a / b; };
}

// Benchmark for type conversion to int
STONEYDSP_TEST_CASE ("[core][types][uint8_t][benchmark][conversion][int]",
                     "[core][types][uint8_t][benchmark][conversion][int]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::uint8_t a = 12_uint8_t;

  STONEYDSP_BENCHMARK ("Conversion to int") { return static_cast<int> (a); };
}

// Benchmark for type conversion to float
STONEYDSP_TEST_CASE ("[core][types][uint8_t][benchmark][conversion][float]",
                     "[core][types][uint8_t][benchmark][conversion][float]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::uint8_t a = 12_uint8_t;

  STONEYDSP_BENCHMARK ("Conversion to float")
  {
    return static_cast<float> (a);
  };
}

//============================================================================//

#endif // defined(STONEYDSP_BUILD_TEST)

//=========================================================================//EOF
