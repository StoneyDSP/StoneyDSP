/**
 * @file uint16.test.cpp
 * @brief Test suite for stoneydsp::uint16_t
 * @copyright Copyright (c) 2025
 *
 */

//==============================================================================

#include <stoneydsp/core/types/uint16.h>

//==============================================================================

#if defined(STONEYDSP_BUILD_TEST) && defined(STONEYDSP_BUILD_CORE)

//==============================================================================

namespace stoneydsp
{
using ::stoneydsp::core::types::uint16_t;
}

//==============================================================================

  #include "../../../utils.test.hpp"

//======================================================================//sizeof

STONEYDSP_TEST_CASE ("[core][types][uint16_t][sizeof]",
                     "[core][types][uint16_t][sizeof]")
{
  STONEYDSP_REQUIRE (sizeof (::stoneydsp::uint16_t) == 2UL);
}

//=====================================================================//alignof

STONEYDSP_TEST_CASE ("[core][types][uint16_t][alignof]",
                     "[core][types][uint16_t][alignof]")
{
  STONEYDSP_REQUIRE (alignof (::stoneydsp::uint16_t) == 2UL);
}

//=================================================================//type_traits

STONEYDSP_TEST_CASE ("[core][types][uint16_t][type_traits][is_integral]",
                     "[core][types][uint16_t][type_traits][is_integral]")
{
  STONEYDSP_REQUIRE (::std::is_integral< ::stoneydsp::uint16_t>::value);
}

STONEYDSP_TEST_CASE ("[core][types][uint16_t][type_traits][is_unsigned]",
                     "[core][types][uint16_t][type_traits][is_unsigned]")
{
  STONEYDSP_REQUIRE (::std::is_unsigned< ::stoneydsp::uint16_t>::value);
}

STONEYDSP_TEST_CASE ("[core][types][uint16_t][type_traits][is_arithmetic]",
                     "[core][types][uint16_t][type_traits][is_arithmetic]")
{
  STONEYDSP_REQUIRE (::std::is_arithmetic< ::stoneydsp::uint16_t>::value);
}

STONEYDSP_TEST_CASE ("[core][types][uint16_t][type_traits][is_pointer]",
                     "[core][types][uint16_t][type_traits][is_pointer]")
{
  STONEYDSP_REQUIRE (!::std::is_pointer< ::stoneydsp::uint16_t>::value);
}

STONEYDSP_TEST_CASE ("[core][types][uint16_t][type_traits][is_const]",
                     "[core][types][uint16_t][type_traits][is_const]")
{
  STONEYDSP_REQUIRE (!::std::is_const< ::stoneydsp::uint16_t>::value);
}

STONEYDSP_TEST_CASE ("[core][types][uint16_t][type_traits][is_empty]",
                     "[core][types][uint16_t][type_traits][is_empty]")
{
  STONEYDSP_REQUIRE (!::std::is_empty< ::stoneydsp::uint16_t>::value);
}

STONEYDSP_TEST_CASE (
    "[core][types][uint16_t][type_traits][is_trivially_copyable]",
    "[core][types][uint16_t][type_traits][is_trivially_copyable]")
{
  STONEYDSP_REQUIRE (
      ::std::is_trivially_copyable< ::stoneydsp::uint16_t>::value);
}

STONEYDSP_TEST_CASE (
    "[core][types][uint16_t][type_traits][is_standard_layout]",
    "[core][types][uint16_t][type_traits][is_standard_layout]")
{
  STONEYDSP_REQUIRE (::std::is_standard_layout< ::stoneydsp::uint16_t>::value);
}

//==============================================================//numeric_limits

STONEYDSP_TEST_CASE ("[core][types][uint16_t][numeric_limits]",
                     "[core][types][uint16_t][numeric_limits]")
{
  // { 0U }
  STONEYDSP_REQUIRE (
      ::stoneydsp::numeric_limits< ::stoneydsp::uint16_t>::min ()
      == ::std::numeric_limits< ::stoneydsp::uint16_t>::min ());
  // // { 65535 }
  STONEYDSP_REQUIRE (
      ::stoneydsp::numeric_limits< ::stoneydsp::uint16_t>::max ()
      == ::std::numeric_limits< ::stoneydsp::uint16_t>::max ());
  // { 0U }
  STONEYDSP_REQUIRE (
      ::stoneydsp::numeric_limits< ::stoneydsp::uint16_t>::lowest ()
      == ::std::numeric_limits< ::stoneydsp::uint16_t>::lowest ());
}

//==============================================================//special_values

STONEYDSP_TEST_CASE ("[core][types][uint16_t][special_values]",
                     "[core][types][uint16_t][special_values]")
{
  ::stoneydsp::uint16_t min_val
      = ::std::numeric_limits< ::stoneydsp::uint16_t>::min ();
  ::stoneydsp::uint16_t max_val
      = ::std::numeric_limits< ::stoneydsp::uint16_t>::max ();
  STONEYDSP_REQUIRE (min_val == 0U);     // Minimum value for uint16_t
  STONEYDSP_REQUIRE (max_val == 65535U); // Maximum value for uint16_t
}

//==================================================================//endianness

STONEYDSP_TEST_CASE ("[core][types][uint16_t][endianness]",
                     "[core][types][uint16_t][endianness]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::uint16_t value = 0x1234_uint16_t;
  ::std::uint8_t *bytePtr = reinterpret_cast< ::std::uint8_t *> (&value);

  if (bytePtr[0] == 0x34)
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

STONEYDSP_TEST_CASE ("[core][types][uint16_t][rounding]",
                     "[core][types][uint16_t][rounding]")
{
  float a = 1.5f;
  ::stoneydsp::uint16_t b
      = static_cast< ::stoneydsp::uint16_t> (::std::round (a));
  STONEYDSP_REQUIRE (
      b == 2); // 1.5 rounded to nearest integer and cast to uint16_t
}

//==================================================================//arithmetic

STONEYDSP_TEST_CASE ("[core][types][uint16_t][arithmetic]",
                     "[core][types][uint16_t][arithmetic]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::uint16_t a = 1500_uint16_t;
  ::stoneydsp::uint16_t b = 2000_uint16_t;

  STONEYDSP_REQUIRE (a + b == 3500); // Addition
  STONEYDSP_REQUIRE (static_cast<int> (a - b)
                     == static_cast<int> (-500)); // Subtraction (wrap-around)
  STONEYDSP_REQUIRE (a * b == 3000000);           // Multiplication
  STONEYDSP_REQUIRE (b / a == 1);                 // Division
  STONEYDSP_REQUIRE (b % a == 500);               // Modulo
}

//=====================================================================//bitwise

STONEYDSP_TEST_CASE ("[core][types][uint16_t][bitwise][logic]",
                     "[core][types][uint16_t][bitwise][logic]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::uint16_t a = 5_uint16_t; // 0000 0000 0000 0101
  ::stoneydsp::uint16_t b = 3_uint16_t; // 0000 0000 0000 0011

  STONEYDSP_REQUIRE ((a & b) == 1); // AND: 0000 0000 0000 0001
  STONEYDSP_REQUIRE ((a | b) == 7); // OR:  0000 0000 0000 0111
  STONEYDSP_REQUIRE ((a ^ b) == 6); // XOR: 0000 0000 0000 0110
  STONEYDSP_REQUIRE (
      (~a & 0xFFFF)
      == 65530); // NOT: 1111 1111 1111 1010 (considering uint16_t wrap-around)
}

STONEYDSP_TEST_CASE ("[core][types][uint16_t][bitwise][arithmetic]",
                     "[core][types][uint16_t][bitwise][arithmetic]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::uint16_t a = 5_uint16_t; // 0000 0000 0000 0101

  STONEYDSP_REQUIRE ((a << 1) == 10); // Left shift: 0000 0000 0000 1010
  STONEYDSP_REQUIRE ((a >> 1) == 2);  // Right shift: 0000 0000 0000 0010
}

//===============================================================//comparison

STONEYDSP_TEST_CASE ("[core][types][uint16_t][comparison]",
                     "[core][types][uint16_t][comparison]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::uint16_t a = 5_uint16_t;
  ::stoneydsp::uint16_t b = 3_uint16_t;

  STONEYDSP_REQUIRE ((a == b) == false);
  STONEYDSP_REQUIRE ((a != b) == true);
  STONEYDSP_REQUIRE ((a > b) == true);
  STONEYDSP_REQUIRE ((a < b) == false);
  STONEYDSP_REQUIRE ((a >= b) == true);
  STONEYDSP_REQUIRE ((a <= b) == false);
}

//===============================================================//serialization

STONEYDSP_TEST_CASE ("[core][types][uint16_t][serialization]",
                     "[core][types][uint16_t][serialization]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::std::stringstream ss;
  ::stoneydsp::uint16_t originalValue = 42_uint16_t;
  ::stoneydsp::uint16_t deserializedValue;

  ss.write (reinterpret_cast<const char *> (&originalValue),
            sizeof (originalValue));
  ss.read (reinterpret_cast<char *> (&deserializedValue),
           sizeof (deserializedValue));

  STONEYDSP_REQUIRE (originalValue == deserializedValue);
}

//=======================================================//boundary_and_overflow

STONEYDSP_TEST_CASE ("[core][types][uint16_t][boundary][overflow]",
                     "[core][types][uint16_t][boundary][overflow]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::uint16_t a = 65535_uint16_t;
  ::stoneydsp::uint16_t b = 1_uint16_t;

  STONEYDSP_REQUIRE (static_cast< ::stoneydsp::uint16_t> (a + b)
                     == 0); // Check overflow wrap-around behaviour
}

//======================================================//boundary_and_underflow

STONEYDSP_TEST_CASE ("[core][types][uint16_t][boundary][underflow]",
                     "[core][types][uint16_t][boundary][underflow]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::uint16_t a = 0_uint16_t;
  ::stoneydsp::uint16_t b = 1_uint16_t;

  STONEYDSP_REQUIRE (static_cast< ::stoneydsp::uint16_t> (a - b)
                     == 65535); // Check underflow wrap-around behavior
}

//===============================================================//compatibility

STONEYDSP_TEST_CASE ("[core][types][uint16_t][compatibility]",
                     "[core][types][uint16_t][compatibility]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::std::vector< ::stoneydsp::uint16_t> vec
      = { 5_uint16_t, 3_uint16_t, 4_uint16_t, 1_uint16_t, 2_uint16_t };

  // Use std::sort to sort the vector
  ::std::sort (vec.begin (), vec.end ());

  // Verify the vector is sorted
  STONEYDSP_REQUIRE (
      vec
      == ::std::vector< ::stoneydsp::uint16_t>{
          1_uint16_t, 2_uint16_t, 3_uint16_t, 4_uint16_t, 5_uint16_t });

  // Use std::accumulate to sum the elements
  ::stoneydsp::uint16_t sum = ::std::accumulate (
      vec.begin (), vec.end (), ::stoneydsp::uint16_t (0_uint16_t));
  // Verify the sum is correct
  STONEYDSP_REQUIRE (sum == 15);
}

//===================================================================//benchmark

// Benchmark for addition
STONEYDSP_TEST_CASE ("[core][types][uint16_t][benchmark][addition]",
                     "[core][types][uint16_t][benchmark][addition]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::uint16_t a = 1200_uint16_t;
  ::stoneydsp::uint16_t b = 3400_uint16_t;

  STONEYDSP_BENCHMARK ("Addition") { return a + b; };
}

// Benchmark for subtraction
STONEYDSP_TEST_CASE ("[core][types][uint16_t][benchmark][subtraction]",
                     "[core][types][uint16_t][benchmark][subtraction]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::uint16_t a = 3400_uint16_t;
  ::stoneydsp::uint16_t b = 1200_uint16_t;

  STONEYDSP_BENCHMARK ("Subtraction") { return a - b; };
}

// Benchmark for multiplication
STONEYDSP_TEST_CASE ("[core][types][uint16_t][benchmark][multiplication]",
                     "[core][types][uint16_t][benchmark][multiplication]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::uint16_t a = 1200_uint16_t;
  ::stoneydsp::uint16_t b = 2_uint16_t;

  STONEYDSP_BENCHMARK ("Multiplication") { return a * b; };
}

// Benchmark for division
STONEYDSP_TEST_CASE ("[core][types][uint16_t][benchmark][division]",
                     "[core][types][uint16_t][benchmark][division]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::uint16_t a = 1200_uint16_t;
  ::stoneydsp::uint16_t b = 2_uint16_t;

  STONEYDSP_BENCHMARK ("Division") { return a / b; };
}

// Benchmark for type conversion to int
STONEYDSP_TEST_CASE ("[core][types][uint16_t][benchmark][conversion][int]",
                     "[core][types][uint16_t][benchmark][conversion][int]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::uint16_t a = 1200_uint16_t;

  STONEYDSP_BENCHMARK ("Conversion to int") { return static_cast<int> (a); };
}

// Benchmark for type conversion to float
STONEYDSP_TEST_CASE ("[core][types][uint16_t][benchmark][conversion][float]",
                     "[core][types][uint16_t][benchmark][conversion][float]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::uint16_t a = 1200_uint16_t;

  STONEYDSP_BENCHMARK ("Conversion to float")
  {
    return static_cast<float> (a);
  };
}

//============================================================================//

#endif // defined(STONEYDSP_BUILD_TEST)

//=========================================================================//EOF
