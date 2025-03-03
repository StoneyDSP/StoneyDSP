/**
 * @file ptrdiff_t.test.cpp
 * @brief Test suite for stoneydsp::ptrdiff_t
 * @copyright Copyright (c) 2025
 *
 */

//==============================================================================

#include "stoneydsp/core/system/types.h"

//==============================================================================

#if defined(STONEYDSP_BUILD_TEST) && defined(STONEYDSP_BUILD_CORE)

//==============================================================================

  #include "utils.test.hpp"

//================================================================//requirements

STONEYDSP_TEST_CASE ("[core][types][ptrdiff_t][requirements]",
                     "[core][types][ptrdiff_t][requirements]")
{
  STONEYDSP_SECTION ("[core][types][ptrdiff_t][requirements][min]")
  {
    bool result = false;
  #if defined(PTRDIFF_MIN)
    result = true;
  #endif
    STONEYDSP_REQUIRE (result == true);
  }
  STONEYDSP_SECTION ("[core][types][ptrdiff_t][requirements][max]")
  {
    bool result = false;
  #if defined(PTRDIFF_MAX)
    result = true;
  #endif
    STONEYDSP_REQUIRE (result == true);
  }
}

//=====================================================================//alignof

STONEYDSP_TEST_CASE ("[core][types][ptrdiff_t][alignof]",
                     "[core][types][ptrdiff_t][alignof]")
{
  STONEYDSP_REQUIRE (alignof (::stoneydsp::ptrdiff_t)
                     == alignof (std::ptrdiff_t));
}

//=================================================================//type_traits

STONEYDSP_TEST_CASE ("[core][types][ptrdiff_t][type_traits]",
                     "[core][types][ptrdiff_t][type_traits]")
{
  STONEYDSP_REQUIRE (::std::is_integral< ::stoneydsp::ptrdiff_t>::value);
  STONEYDSP_REQUIRE (::std::is_signed< ::stoneydsp::ptrdiff_t>::value);
  STONEYDSP_REQUIRE (
      ::std::is_standard_layout< ::stoneydsp::ptrdiff_t>::value);
  STONEYDSP_REQUIRE (
      ::std::is_trivially_copyable< ::stoneydsp::ptrdiff_t>::value);
}

//==============================================================//special_values

STONEYDSP_TEST_CASE ("[core][types][ptrdiff_t][special_values]",
                     "[core][types][ptrdiff_t][special_values]")
{
  STONEYDSP_REQUIRE (
      ::stoneydsp::numeric_limits<stoneydsp::ptrdiff_t>::min ()
      == std::numeric_limits<stoneydsp::ptrdiff_t>::min ()); // Minimum value
                                                             // for ptrdiff_t
  STONEYDSP_REQUIRE (
      ::stoneydsp::numeric_limits<std::ptrdiff_t>::max ()
      == std::numeric_limits<std::ptrdiff_t>::max ()); // Maximum value
                                                       // for ptrdiff_t
  STONEYDSP_REQUIRE (
      ::stoneydsp::numeric_limits<stoneydsp::ptrdiff_t>::lowest ()
      == std::numeric_limits<stoneydsp::ptrdiff_t>::lowest ()); // Lowest value
                                                                // for
                                                                // ptrdiff_t
}

//==================================================================//endianness

STONEYDSP_TEST_CASE ("[core][types][ptrdiff_t][endianness]",
                     "[core][types][ptrdiff_t][endianness]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::ptrdiff_t value = 0x12345678_ptrdiff_t;

  ::std::uint8_t *bytePtr = reinterpret_cast< ::std::uint8_t *> (&value);

  if (bytePtr[0] == 0x78)
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

STONEYDSP_TEST_CASE ("[core][types][ptrdiff_t][rounding]",
                     "[core][types][ptrdiff_t][rounding]")
{
  ::stoneydsp::float_t a = 1.5f;
  ::stoneydsp::ptrdiff_t b
      = static_cast< ::stoneydsp::ptrdiff_t> (::std::round (a));
  STONEYDSP_REQUIRE (
      b == 2); // 1.5 rounded to nearest integer and cast to ptrdiff_t
}

//==================================================================//arithmetic

STONEYDSP_TEST_CASE ("[core][types][ptrdiff_t][arithmetic]",
                     "[core][types][ptrdiff_t][arithmetic]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::ptrdiff_t a = 15_ptrdiff_t;
  ::stoneydsp::ptrdiff_t b = 20_ptrdiff_t;

  STONEYDSP_REQUIRE (a + b == 35);  // Addition
  STONEYDSP_REQUIRE (a - b == -5);  // Subtraction
  STONEYDSP_REQUIRE (a * b == 300); // Multiplication
  STONEYDSP_REQUIRE (b / a == 1);   // Division
  STONEYDSP_REQUIRE (b % a == 5);   // Modulo
}

//=====================================================================//bitwise

STONEYDSP_TEST_CASE ("[core][types][ptrdiff_t][bitwise][logic]",
                     "[core][types][ptrdiff_t][bitwise][logic]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::ptrdiff_t a = 5_ptrdiff_t; // 0101
  ::stoneydsp::ptrdiff_t b = 3_ptrdiff_t; // 0011

  STONEYDSP_REQUIRE ((a & b) == 1); // AND: 0001
  STONEYDSP_REQUIRE ((a | b) == 7); // OR:  0111
  STONEYDSP_REQUIRE ((a ^ b) == 6); // XOR: 0110
  STONEYDSP_REQUIRE (~a == -6); // NOT:  1111 1111 1111 1010 (two's complement)
}

STONEYDSP_TEST_CASE ("[core][types][ptrdiff_t][bitwise][arithmetic]",
                     "[core][types][ptrdiff_t][bitwise][arithmetic]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::ptrdiff_t a = 5_ptrdiff_t; // 0101
  STONEYDSP_REQUIRE ((a << 1) == 10);     // Left shift: 1010
  STONEYDSP_REQUIRE ((a >> 1) == 2);      // Right shift: 0010
}

//===============================================================//comparison

STONEYDSP_TEST_CASE ("[core][types][ptrdiff_t][comparison]",
                     "[core][types][ptrdiff_t][comparison]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::ptrdiff_t a = 5_ptrdiff_t;
  ::stoneydsp::ptrdiff_t b = 3_ptrdiff_t;
  STONEYDSP_REQUIRE ((a == b) == false);
  STONEYDSP_REQUIRE ((a != b) == true);
  STONEYDSP_REQUIRE ((a > b) == true);
  STONEYDSP_REQUIRE ((a < b) == false);
  STONEYDSP_REQUIRE ((a >= b) == true);
  STONEYDSP_REQUIRE ((a <= b) == false);
}

//===============================================================//serialization

STONEYDSP_TEST_CASE ("[core][types][ptrdiff_t][serialization]",
                     "[core][types][ptrdiff_t][serialization]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::std::stringstream ss;
  ::stoneydsp::ptrdiff_t originalValue = 42_ptrdiff_t;
  ::stoneydsp::ptrdiff_t deserializedValue;

  ss.write (reinterpret_cast<const char *> (&originalValue),
            sizeof (originalValue));
  ss.read (reinterpret_cast<char *> (&deserializedValue),
           sizeof (deserializedValue));

  STONEYDSP_REQUIRE (originalValue == deserializedValue);
}

//=======================================================//boundary_and_overflow

STONEYDSP_TEST_CASE ("[core][types][ptrdiff_t][boundary][overflow]",
                     "[core][types][ptrdiff_t][boundary][overflow]")
{
  ::stoneydsp::ptrdiff_t a
      = std::numeric_limits< ::stoneydsp::ptrdiff_t>::max ();
  ::stoneydsp::ptrdiff_t b = 1;
  STONEYDSP_REQUIRE (static_cast< ::stoneydsp::ptrdiff_t> (a + b)
                     == std::numeric_limits< ::stoneydsp::ptrdiff_t>::
                         min ()); // Check overflow wrap-around behaviour
}

//======================================================//boundary_and_underflow

STONEYDSP_TEST_CASE ("[core][types][ptrdiff_t][boundary][underflow]",
                     "[core][types][ptrdiff_t][boundary][underflow]")
{
  ::stoneydsp::ptrdiff_t a
      = std::numeric_limits< ::stoneydsp::ptrdiff_t>::min ();
  ::stoneydsp::ptrdiff_t b = 1;
  STONEYDSP_REQUIRE (static_cast< ::stoneydsp::ptrdiff_t> (a - b)
                     == std::numeric_limits< ::stoneydsp::ptrdiff_t>::
                         max ()); // Check underflow wrap-around behavior
}

//===============================================================//compatibility

STONEYDSP_TEST_CASE ("[core][types][ptrdiff_t][compatibility]",
                     "[core][types][ptrdiff_t][compatibility]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::std::vector< ::stoneydsp::ptrdiff_t> vec
      = { 5_ptrdiff_t, 3_ptrdiff_t, 4_ptrdiff_t, 1_ptrdiff_t, 2_ptrdiff_t };

  // Use std::sort to sort the vector
  ::std::sort (vec.begin (), vec.end ());

  // Verify the vector is sorted
  STONEYDSP_REQUIRE (
      vec
      == ::std::vector< ::stoneydsp::ptrdiff_t>{
          1_ptrdiff_t, 2_ptrdiff_t, 3_ptrdiff_t, 4_ptrdiff_t, 5_ptrdiff_t });

  // Use std::accumulate to sum the elements
  ::stoneydsp::ptrdiff_t sum = ::std::accumulate (
      vec.begin (), vec.end (), ::stoneydsp::ptrdiff_t (0_ptrdiff_t));

  // Verify the sum is correct
  STONEYDSP_REQUIRE (sum == 15);
}

//===================================================================//benchmark

// Benchmark for addition
STONEYDSP_TEST_CASE ("[core][types][ptrdiff_t][benchmark][addition]",
                     "[core][types][ptrdiff_t][benchmark][addition]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::ptrdiff_t a = 1200_ptrdiff_t;
  ::stoneydsp::ptrdiff_t b = 3400_ptrdiff_t;

  STONEYDSP_BENCHMARK ("Addition") { return a + b; };
}

// Benchmark for subtraction
STONEYDSP_TEST_CASE ("[core][types][ptrdiff_t][benchmark][subtraction]",
                     "[core][types][ptrdiff_t][benchmark][subtraction]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::ptrdiff_t a = 3400_ptrdiff_t;
  ::stoneydsp::ptrdiff_t b = 1200_ptrdiff_t;

  STONEYDSP_BENCHMARK ("Subtraction") { return a - b; };
}

// Benchmark for multiplication
STONEYDSP_TEST_CASE ("[core][types][ptrdiff_t][benchmark][multiplication]",
                     "[core][types][ptrdiff_t][benchmark][multiplication]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::ptrdiff_t a = 1200_ptrdiff_t;
  ::stoneydsp::ptrdiff_t b = 2_ptrdiff_t;

  STONEYDSP_BENCHMARK ("Multiplication") { return a * b; };
}

// Benchmark for division
STONEYDSP_TEST_CASE ("[core][types][ptrdiff_t][benchmark][division]",
                     "[core][types][ptrdiff_t][benchmark][division]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::ptrdiff_t a = 1200_ptrdiff_t;
  ::stoneydsp::ptrdiff_t b = 2_ptrdiff_t;

  STONEYDSP_BENCHMARK ("Division") { return a / b; };
}

// Benchmark for type conversion to int
STONEYDSP_TEST_CASE ("[core][types][ptrdiff_t][benchmark][conversion][int]",
                     "[core][types][ptrdiff_t][benchmark][conversion][int]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::ptrdiff_t a = 1200_ptrdiff_t;

  STONEYDSP_BENCHMARK ("Conversion to int") { return static_cast<int> (a); };
}

// Benchmark for type conversion to float
STONEYDSP_TEST_CASE ("[core][types][ptrdiff_t][benchmark][conversion][float]",
                     "[core][types][ptrdiff_t][benchmark][conversion][float]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::ptrdiff_t a = 1200_ptrdiff_t;

  STONEYDSP_BENCHMARK ("Conversion to float")
  {
    return static_cast<float> (a);
  };
}

//============================================================================//

#endif // defined(STONEYDSP_BUILD_TEST)

//=========================================================================//EOF
