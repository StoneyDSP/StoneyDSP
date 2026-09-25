/**
 * @file schar.test.cpp
 * @brief Test suite for stoneydsp::char_t
 * @copyright Copyright (c) 2025
 *
 */

//==============================================================================

#include "stoneydsp/core/types/char.h"

//==============================================================================

#if defined(STONEYDSP_BUILD_TEST) && defined(STONEYDSP_BUILD_CORE)

//==============================================================================

namespace stoneydsp
{
using ::stoneydsp::core::types::char_t;
}

//==============================================================================

  #include "../../../utils.test.hpp"

//================================================================//requirements

STONEYDSP_TEST_CASE ("[core][types][char_t][requirements]",
                     "[core][types][char_t][requirements]")
{
  STONEYDSP_SECTION ("[core][types][char_t][requirements][min]")
  {
    bool result = false;
  #if defined(CHAR_MIN)
    result = true;
  #endif
    STONEYDSP_REQUIRE (result == true);
  }
  STONEYDSP_SECTION ("[core][types][char_t][requirements][max]")
  {
    bool result = false;
  #if defined(CHAR_MAX)
    result = true;
  #endif
    STONEYDSP_REQUIRE (result == true);
  }
  STONEYDSP_SECTION ("[core][types][char_t][requirements][bit]")
  {
    bool result = false;
  #if defined(CHAR_BIT)
    result = true;
  #endif
    STONEYDSP_REQUIRE (result == true);
  }
}

//======================================================================//sizeof

STONEYDSP_TEST_CASE ("[core][types][char_t][sizeof]",
                     "[core][types][char_t][sizeof]")
{
  STONEYDSP_REQUIRE (sizeof (::stoneydsp::char_t) == 1UL);
}

//=====================================================================//alignof

STONEYDSP_TEST_CASE ("[core][types][char_t][alignof]",
                     "[core][types][char_t][alignof]")
{
  STONEYDSP_REQUIRE (alignof (::stoneydsp::char_t) == 1UL);
}

//=================================================================//type_traits

STONEYDSP_TEST_CASE ("[core][types][char_t][type_traits][is_integral]",
                     "[core][types][char_t][type_traits][is_integral]")
{
  STONEYDSP_REQUIRE (::std::is_integral< ::stoneydsp::char_t>::value);
}

STONEYDSP_TEST_CASE ("[core][types][char_t][type_traits][is_unsigned]",
                     "[core][types][char_t][type_traits][is_unsigned]")
{
  STONEYDSP_REQUIRE (!::std::is_unsigned< ::stoneydsp::char_t>::value);
}

STONEYDSP_TEST_CASE ("[core][types][char_t][type_traits][is_arithmetic]",
                     "[core][types][char_t][type_traits][is_arithmetic]")
{
  STONEYDSP_REQUIRE (::std::is_arithmetic< ::stoneydsp::char_t>::value);
}

STONEYDSP_TEST_CASE ("[core][types][char_t][type_traits][is_pointer]",
                     "[core][types][char_t][type_traits][is_pointer]")
{
  STONEYDSP_REQUIRE (!::std::is_pointer< ::stoneydsp::char_t>::value);
}

STONEYDSP_TEST_CASE ("[core][types][char_t][type_traits][is_const]",
                     "[core][types][char_t][type_traits][is_const]")
{
  STONEYDSP_REQUIRE (!::std::is_const< ::stoneydsp::char_t>::value);
}

STONEYDSP_TEST_CASE ("[core][types][char_t][type_traits][is_empty]",
                     "[core][types][char_t][type_traits][is_empty]")
{
  STONEYDSP_REQUIRE (!::std::is_empty< ::stoneydsp::char_t>::value);
}

STONEYDSP_TEST_CASE (
    "[core][types][char_t][type_traits][is_trivially_copyable]",
    "[core][types][char_t][type_traits][is_trivially_copyable]")
{
  STONEYDSP_REQUIRE (
      ::std::is_trivially_copyable< ::stoneydsp::char_t>::value);
}

STONEYDSP_TEST_CASE ("[core][types][char_t][type_traits][is_standard_layout]",
                     "[core][types][char_t][type_traits][is_standard_layout]")
{
  STONEYDSP_REQUIRE (::std::is_standard_layout< ::stoneydsp::char_t>::value);
}

//==============================================================//numeric_limits

STONEYDSP_TEST_CASE ("[core][types][char_t][numeric_limits]",
                     "[core][types][char_t][numeric_limits]")
{
  // { -128 }
  STONEYDSP_REQUIRE (::stoneydsp::numeric_limits< ::stoneydsp::char_t>::min ()
                     == ::std::numeric_limits< ::stoneydsp::char_t>::min ());
  // { 127 }
  STONEYDSP_REQUIRE (::stoneydsp::numeric_limits< ::stoneydsp::char_t>::max ()
                     == ::std::numeric_limits< ::stoneydsp::char_t>::max ());
  // { -128 }
  STONEYDSP_REQUIRE (
      ::stoneydsp::numeric_limits< ::stoneydsp::char_t>::lowest ()
      == ::std::numeric_limits< ::stoneydsp::char_t>::lowest ());
}

//==============================================================//special_values

STONEYDSP_TEST_CASE ("[core][types][char_t][special_values]",
                     "[core][types][char_t][special_values]")
{
  ::stoneydsp::char_t min_val
      = ::std::numeric_limits< ::stoneydsp::char_t>::min ();
  ::stoneydsp::char_t max_val
      = ::std::numeric_limits< ::stoneydsp::char_t>::max ();
  STONEYDSP_REQUIRE (min_val == -128); // Minimum value for char_t
  STONEYDSP_REQUIRE (max_val == 127);  // Maximum value for char_t
}

//==================================================================//endianness

STONEYDSP_TEST_CASE ("[core][types][char_t][endianness]",
                     "[core][types][char_t][endianness]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::char_t value = 0x12_char_t;
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

STONEYDSP_TEST_CASE ("[core][types][char_t][rounding]",
                     "[core][types][char_t][rounding]")
{
  float a = 1.5f;
  ::stoneydsp::char_t b = static_cast< ::stoneydsp::char_t> (::std::round (a));
  STONEYDSP_REQUIRE (
      b == 2); // 1.5 rounded to nearest integer and cast to char_t
}

//==================================================================//arithmetic

STONEYDSP_TEST_CASE ("[core][types][char_t][arithmetic]",
                     "[core][types][char_t][arithmetic]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::char_t a = 15_char_t;
  ::stoneydsp::char_t b = 20_char_t;

  STONEYDSP_REQUIRE (a + b == 35);  // Addition
  STONEYDSP_REQUIRE (a - b == -5);  // Subtraction
  STONEYDSP_REQUIRE (a * b == 300); // Multiplication
  STONEYDSP_REQUIRE (b / a == 1);   // Division
  STONEYDSP_REQUIRE (b % a == 5);   // Modulo
}

//=====================================================================//bitwise

STONEYDSP_TEST_CASE ("[core][types][char_t][bitwise][logic]",
                     "[core][types][char_t][bitwise][logic]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::char_t a = 5_char_t; // 0101
  ::stoneydsp::char_t b = 3_char_t; // 0011

  STONEYDSP_REQUIRE ((a & b) == 1); // AND: 0001
  STONEYDSP_REQUIRE ((a | b) == 7); // OR:  0111
  STONEYDSP_REQUIRE ((a ^ b) == 6); // XOR: 0110
  STONEYDSP_REQUIRE (~a == -6);     // NOT: considering wrap-around for char_t
}

STONEYDSP_TEST_CASE ("[core][types][char_t][bitwise][arithmetic]",
                     "[core][types][char_t][bitwise][arithmetic]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::char_t a = 5_char_t; // 0101

  STONEYDSP_REQUIRE ((a << 1) == 10); // Left shift: 1010
  STONEYDSP_REQUIRE ((a >> 1) == 2);  // Right shift: 0010
}

//==================================================================//comparison

STONEYDSP_TEST_CASE ("[core][types][char_t][comparison]",
                     "[core][types][char_t][comparison]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::char_t a = 5_char_t;
  ::stoneydsp::char_t b = 3_char_t;

  STONEYDSP_REQUIRE ((a == b) == false);
  STONEYDSP_REQUIRE ((a != b) == true);
  STONEYDSP_REQUIRE ((a > b) == true);
  STONEYDSP_REQUIRE ((a < b) == false);
  STONEYDSP_REQUIRE ((a >= b) == true);
  STONEYDSP_REQUIRE ((a <= b) == false);
}

//===============================================================//serialization

STONEYDSP_TEST_CASE ("[core][types][char_t][serialization]",
                     "[core][types][char_t][serialization]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::std::stringstream ss;

  ::stoneydsp::char_t originalValue = 42_char_t;
  ::stoneydsp::char_t deserializedValue;

  ss.write (reinterpret_cast<const char *> (&originalValue),
            sizeof (originalValue));
  ss.read (reinterpret_cast<char *> (&deserializedValue),
           sizeof (deserializedValue));

  STONEYDSP_REQUIRE (originalValue == deserializedValue);
}

//=======================================================//boundary_and_overflow

STONEYDSP_TEST_CASE ("[core][types][char_t][boundary][overflow]",
                     "[core][types][char_t][boundary][overflow]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::char_t a = 127_char_t;
  ::stoneydsp::char_t b = 1_char_t;

  STONEYDSP_REQUIRE (static_cast< ::stoneydsp::char_t> (a + b)
                     == -128); // Check overflow wrap-around behaviour
}

//======================================================//boundary_and_underflow

STONEYDSP_TEST_CASE ("[core][types][char_t][boundary][underflow]",
                     "[core][types][char_t][boundary][underflow]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::char_t a = -127_char_t;
  ::stoneydsp::char_t b = 2_char_t;

  STONEYDSP_REQUIRE (static_cast< ::stoneydsp::char_t> (a - b)
                     == 127); // Check underflow wrap-around behavior
}

//===============================================================//compatibility

STONEYDSP_TEST_CASE ("[core][types][char_t][compatibility]",
                     "[core][types][char_t][compatibility]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::std::vector< ::stoneydsp::char_t> vec
      = { 5_char_t, 3_char_t, 4_char_t, 1_char_t, 2_char_t };

  // Use std::sort to sort the vector
  ::std::sort (vec.begin (), vec.end ());

  // Verify the vector is sorted
  STONEYDSP_REQUIRE (vec
                     == ::std::vector< ::stoneydsp::char_t>{
                         1_char_t, 2_char_t, 3_char_t, 4_char_t, 5_char_t });

  // Use std::accumulate to sum the elements
  ::stoneydsp::char_t sum = ::std::accumulate (vec.begin (), vec.end (),
                                               ::stoneydsp::char_t (0_char_t));

  // Verify the sum is correct
  STONEYDSP_REQUIRE (sum == 15);
}

//===================================================================//benchmark

// Benchmark for addition
STONEYDSP_TEST_CASE ("[core][types][char_t][benchmark][addition]",
                     "[core][types][char_t][benchmark][addition]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::char_t a = 12_char_t;
  ::stoneydsp::char_t b = 34_char_t;

  STONEYDSP_BENCHMARK ("Addition") { return a + b; };
}

// Benchmark for subtraction
STONEYDSP_TEST_CASE ("[core][types][char_t][benchmark][subtraction]",
                     "[core][types][char_t][benchmark][subtraction]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::char_t a = 34_char_t;
  ::stoneydsp::char_t b = 12_char_t;

  STONEYDSP_BENCHMARK ("Subtraction") { return a - b; };
}

// Benchmark for multiplication
STONEYDSP_TEST_CASE ("[core][types][char_t][benchmark][multiplication]",
                     "[core][types][char_t][benchmark][multiplication]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::char_t a = 12_char_t;
  ::stoneydsp::char_t b = 2_char_t;

  STONEYDSP_BENCHMARK ("Multiplication") { return a * b; };
}

// Benchmark for division
STONEYDSP_TEST_CASE ("[core][types][char_t][benchmark][division]",
                     "[core][types][char_t][benchmark][division]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::char_t a = 12_char_t;
  ::stoneydsp::char_t b = 2_char_t;

  STONEYDSP_BENCHMARK ("Division") { return a / b; };
}

// Benchmark for type conversion to int
STONEYDSP_TEST_CASE ("[core][types][char_t][benchmark][conversion][int]",
                     "[core][types][char_t][benchmark][conversion][int]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::char_t a = 12_char_t;

  STONEYDSP_BENCHMARK ("Conversion to int") { return static_cast<int> (a); };
}

// Benchmark for type conversion to float
STONEYDSP_TEST_CASE ("[core][types][char_t][benchmark][conversion][float]",
                     "[core][types][char_t][benchmark][conversion][float]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::char_t a = 12_char_t;

  STONEYDSP_BENCHMARK ("Conversion to float")
  {
    return static_cast<float> (a);
  };
}

//============================================================================//

#endif // defined(STONEYDSP_BUILD_TEST)

//=========================================================================//EOF
