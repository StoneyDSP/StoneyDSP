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

  #include "utils.test.hpp"

//======================================================================//sizeof

STONEYDSP_TEST_CASE ("[core][types][uchar_t][sizeof]",
                     "[core][types][uchar_t][sizeof]")
{
  STONEYDSP_REQUIRE (sizeof (::stoneydsp::uchar_t) == 1UL);
}

//=====================================================================//alignof

STONEYDSP_TEST_CASE ("[core][types][uchar_t][alignof]",
                     "[core][types][uchar_t][alignof]")
{
  STONEYDSP_REQUIRE (alignof (::stoneydsp::uchar_t) == 1UL);
}

//=================================================================//type_traits

STONEYDSP_TEST_CASE ("[core][types][uchar_t][type_traits][is_integral]",
                     "[core][types][uchar_t][type_traits][is_integral]")
{
  STONEYDSP_REQUIRE (::std::is_integral< ::stoneydsp::uchar_t>::value);
}

STONEYDSP_TEST_CASE ("[core][types][uchar_t][type_traits][is_unsigned]",
                     "[core][types][uchar_t][type_traits][is_unsigned]")
{
  STONEYDSP_REQUIRE (::std::is_unsigned< ::stoneydsp::uchar_t>::value);
}

STONEYDSP_TEST_CASE ("[core][types][uchar_t][type_traits][is_arithmetic]",
                     "[core][types][uchar_t][type_traits][is_arithmetic]")
{
  STONEYDSP_REQUIRE (::std::is_arithmetic< ::stoneydsp::uchar_t>::value);
}

STONEYDSP_TEST_CASE ("[core][types][uchar_t][type_traits][is_pointer]",
                     "[core][types][uchar_t][type_traits][is_pointer]")
{
  STONEYDSP_REQUIRE (!::std::is_pointer< ::stoneydsp::uchar_t>::value);
}

STONEYDSP_TEST_CASE ("[core][types][uchar_t][type_traits][is_const]",
                     "[core][types][uchar_t][type_traits][is_const]")
{
  STONEYDSP_REQUIRE (!::std::is_const< ::stoneydsp::uchar_t>::value);
}

STONEYDSP_TEST_CASE ("[core][types][uchar_t][type_traits][is_empty]",
                     "[core][types][uchar_t][type_traits][is_empty]")
{
  STONEYDSP_REQUIRE (!::std::is_empty< ::stoneydsp::uchar_t>::value);
}

STONEYDSP_TEST_CASE (
    "[core][types][uchar_t][type_traits][is_trivially_copyable]",
    "[core][types][uchar_t][type_traits][is_trivially_copyable]")
{
  STONEYDSP_REQUIRE (
      ::std::is_trivially_copyable< ::stoneydsp::uchar_t>::value);
}

STONEYDSP_TEST_CASE ("[core][types][uchar_t][type_traits][is_standard_layout]",
                     "[core][types][uchar_t][type_traits][is_standard_layout]")
{
  STONEYDSP_REQUIRE (::std::is_standard_layout< ::stoneydsp::uchar_t>::value);
}

//==============================================================//numeric_limits

STONEYDSP_TEST_CASE ("[core][types][uchar_t][numeric_limits]",
                     "[core][types][uchar_t][numeric_limits]")
{
  // { 0U }
  STONEYDSP_REQUIRE (::stoneydsp::numeric_limits< ::stoneydsp::uchar_t>::min ()
                     == ::std::numeric_limits< ::stoneydsp::uchar_t>::min ());
  // { 255 }
  STONEYDSP_REQUIRE (::stoneydsp::numeric_limits< ::stoneydsp::uchar_t>::max ()
                     == ::std::numeric_limits< ::stoneydsp::uchar_t>::max ());
  // { 0U }
  STONEYDSP_REQUIRE (
      ::stoneydsp::numeric_limits< ::stoneydsp::uchar_t>::lowest ()
      == ::std::numeric_limits< ::stoneydsp::uchar_t>::lowest ());
}

//==============================================================//special_values

STONEYDSP_TEST_CASE ("[core][types][uchar_t][special_values]",
                     "[core][types][uchar_t][special_values]")
{
  ::stoneydsp::uchar_t min_val
      = ::std::numeric_limits< ::stoneydsp::uchar_t>::min ();
  ::stoneydsp::uchar_t max_val
      = ::std::numeric_limits< ::stoneydsp::uchar_t>::max ();
  STONEYDSP_REQUIRE (min_val == 0U);   // Minimum value for uchar_t
  STONEYDSP_REQUIRE (max_val == 255U); // Maximum value for uchar_t
}

//==================================================================//endianness

STONEYDSP_TEST_CASE ("[core][types][uchar_t][endianness]",
                     "[core][types][uchar_t][endianness]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::uchar_t value = 0x12_uchar_t;
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

STONEYDSP_TEST_CASE ("[core][types][uchar_t][rounding]",
                     "[core][types][uchar_t][rounding]")
{
  ::stoneydsp::float_t a = 1.5f;
  ::stoneydsp::uchar_t b
      = static_cast< ::stoneydsp::uchar_t> (::std::round (a));
  STONEYDSP_REQUIRE (
      b == 2); // 1.5 rounded to nearest integer and cast to uchar_t
}

//==================================================================//arithmetic

STONEYDSP_TEST_CASE ("[core][types][uchar_t][arithmetic]",
                     "[core][types][uchar_t][arithmetic]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::uchar_t a = 15_uchar_t;
  ::stoneydsp::uchar_t b = 20_uchar_t;

  STONEYDSP_REQUIRE (a + b == 35); // Addition
  STONEYDSP_REQUIRE (static_cast<int> (a - b)
                     == static_cast<int> (-5)); // Subtraction (wrap-around)
  STONEYDSP_REQUIRE (a * b == 300);             // Multiplication
  STONEYDSP_REQUIRE (b / a == 1);               // Division
  STONEYDSP_REQUIRE (b % a == 5);               // Modulo
}
//=====================================================================//bitwise

STONEYDSP_TEST_CASE ("[core][types][uchar_t][bitwise][logic]",
                     "[core][types][uchar_t][bitwise][logic]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::uchar_t a = 5_uchar_t; // 0101
  ::stoneydsp::uchar_t b = 3_uchar_t; // 0011

  STONEYDSP_REQUIRE ((a & b) == 1); // AND: 0001
  STONEYDSP_REQUIRE ((a | b) == 7); // OR: 0111
  STONEYDSP_REQUIRE ((a ^ b) == 6); // XOR: 0110
  STONEYDSP_REQUIRE (
      (~a & 0xFF) == 250); // NOT: 1111_1010 (considering uchar_t wrap-around)
}

STONEYDSP_TEST_CASE ("[core][types][uchar_t][bitwise][arithmetic]",
                     "[core][types][uchar_t][bitwise][arithmetic]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::uchar_t a = 5_uchar_t; // 0101
  STONEYDSP_REQUIRE ((a << 1) == 10); // Left shift: 1010
  STONEYDSP_REQUIRE ((a >> 1) == 2);  // Right shift: 0010
}

//==================================================================//comparison

STONEYDSP_TEST_CASE ("[core][types][uchar_t][comparison]",
                     "[core][types][uchar_t][comparison]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::uchar_t a = 5_uchar_t;
  ::stoneydsp::uchar_t b = 3_uchar_t;

  STONEYDSP_REQUIRE ((a == b) == false);
  STONEYDSP_REQUIRE ((a != b) == true);
  STONEYDSP_REQUIRE ((a > b) == true);
  STONEYDSP_REQUIRE ((a < b) == false);
  STONEYDSP_REQUIRE ((a >= b) == true);
  STONEYDSP_REQUIRE ((a <= b) == false);
}

//===============================================================//serialization

STONEYDSP_TEST_CASE ("[core][types][uchar_t][serialization]",
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

  STONEYDSP_REQUIRE (originalValue == deserializedValue);
}

//=======================================================//boundary_and_overflow

STONEYDSP_TEST_CASE ("[core][types][uchar_t][boundary][overflow]",
                     "[core][types][uchar_t][boundary][overflow]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::uchar_t a = 255_uchar_t;
  ::stoneydsp::uchar_t b = 1_uchar_t;

  STONEYDSP_REQUIRE (static_cast< ::stoneydsp::uchar_t> (a + b)
                     == 0); // Check overflow wrap-around behaviour
}

//======================================================//boundary_and_underflow

STONEYDSP_TEST_CASE ("[core][types][uchar_t][boundary][underflow]",
                     "[core][types][uchar_t][boundary][underflow]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::uchar_t a = 0_uchar_t;
  ::stoneydsp::uchar_t b = 1_uchar_t;

  STONEYDSP_REQUIRE (static_cast< ::stoneydsp::uchar_t> (a - b)
                     == 255); // Check underflow wrap-around behavior
}

//===============================================================//compatibility

STONEYDSP_TEST_CASE ("[core][types][uchar_t][compatibility]",
                     "[core][types][uchar_t][compatibility]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::std::vector< ::stoneydsp::uchar_t> vec
      = { 5_uchar_t, 3_uchar_t, 4_uchar_t, 1_uchar_t, 2_uchar_t };

  // Use std::sort to sort the vector
  ::std::sort (vec.begin (), vec.end ());

  // Verify the vector is sorted
  STONEYDSP_REQUIRE (
      vec
      == ::std::vector< ::stoneydsp::uchar_t>{ 1_uchar_t, 2_uchar_t, 3_uchar_t,
                                               4_uchar_t, 5_uchar_t });

  // Use std::accumulate to sum the elements
  ::stoneydsp::uchar_t sum = ::std::accumulate (
      vec.begin (), vec.end (), ::stoneydsp::uchar_t (0_uchar_t));

  // Verify the sum is correct
  STONEYDSP_REQUIRE (sum == 15);
}

//===================================================================//benchmark

// Benchmark for addition
STONEYDSP_TEST_CASE ("[core][types][uchar_t][benchmark][addition]",
                     "[core][types][uchar_t][benchmark][addition]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::uchar_t a = 12_uchar_t;
  ::stoneydsp::uchar_t b = 34_uchar_t;

  STONEYDSP_BENCHMARK ("Addition") { return a + b; };
}

// Benchmark for subtraction
STONEYDSP_TEST_CASE ("[core][types][uchar_t][benchmark][subtraction]",
                     "[core][types][uchar_t][benchmark][subtraction]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::uchar_t a = 34_uchar_t;
  ::stoneydsp::uchar_t b = 12_uchar_t;

  STONEYDSP_BENCHMARK ("Subtraction") { return a - b; };
}

// Benchmark for multiplication
STONEYDSP_TEST_CASE ("[core][types][uchar_t][benchmark][multiplication]",
                     "[core][types][uchar_t][benchmark][multiplication]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::uchar_t a = 12_uchar_t;
  ::stoneydsp::uchar_t b = 2_uchar_t;

  STONEYDSP_BENCHMARK ("Multiplication") { return a * b; };
}

// Benchmark for division
STONEYDSP_TEST_CASE ("[core][types][uchar_t][benchmark][division]",
                     "[core][types][uchar_t][benchmark][division]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::uchar_t a = 12_uchar_t;
  ::stoneydsp::uchar_t b = 2_uchar_t;

  STONEYDSP_BENCHMARK ("Division") { return a / b; };
}

// Benchmark for type conversion to int
STONEYDSP_TEST_CASE ("[core][types][uchar_t][benchmark][conversion][int]",
                     "[core][types][uchar_t][benchmark][conversion][int]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::uchar_t a = 12_uchar_t;

  STONEYDSP_BENCHMARK ("Conversion to int") { return static_cast<int> (a); };
}

// Benchmark for type conversion to float
STONEYDSP_TEST_CASE ("[core][types][uchar_t][benchmark][conversion][float]",
                     "[core][types][uchar_t][benchmark][conversion][float]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::uchar_t a = 12_uchar_t;

  STONEYDSP_BENCHMARK ("Conversion to float")
  {
    return static_cast<float> (a);
  };
}

//============================================================================//

#endif // defined(STONEYDSP_BUILD_TEST)

//=========================================================================//EOF
