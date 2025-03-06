/**
 * @file size.test.cpp
 * @brief Test suite for stoneydsp::size_t
 * @copyright Copyright (c) 2025
 *
 */

//==============================================================================

#include "stoneydsp/core/types/size.h"

//==============================================================================

#if defined(STONEYDSP_BUILD_TEST) && defined(STONEYDSP_BUILD_CORE)

//==============================================================================

  #include "../../../utils.test.hpp"

//================================================================//requirements

STONEYDSP_TEST_CASE ("[core][types][size_t][requirements]",
                     "[core][types][size_t][requirements]")
{
  STONEYDSP_SECTION ("[core][types][size_t][requirements][max]")
  {
    bool result = false;
  #if defined(SIZE_MAX)
    result = true;
  #endif
    STONEYDSP_REQUIRE (result == true);
  }
}

//======================================================================//sizeof

STONEYDSP_TEST_CASE ("[core][types][size_t][sizeof]",
                     "[core][types][size_t][sizeof]")
{
  STONEYDSP_REQUIRE (sizeof (::stoneydsp::size_t) == sizeof (std::size_t));
}

//=====================================================================//alignof

STONEYDSP_TEST_CASE ("[core][types][size_t][alignof]",
                     "[core][types][size_t][alignof]")
{
  STONEYDSP_REQUIRE (alignof (::stoneydsp::size_t) == alignof (std::size_t));
}

//=================================================================//type_traits

STONEYDSP_TEST_CASE ("[core][types][size_t][type_traits][is_integral]",
                     "[core][types][size_t][type_traits][is_integral]")
{
  STONEYDSP_REQUIRE (::std::is_integral< ::stoneydsp::size_t>::value);
}

STONEYDSP_TEST_CASE ("[core][types][size_t][type_traits][is_unsigned]",
                     "[core][types][size_t][type_traits][is_unsigned]")
{
  STONEYDSP_REQUIRE (::std::is_unsigned< ::stoneydsp::size_t>::value);
}

STONEYDSP_TEST_CASE ("[core][types][size_t][type_traits][is_arithmetic]",
                     "[core][types][size_t][type_traits][is_arithmetic]")
{
  STONEYDSP_REQUIRE (::std::is_arithmetic< ::stoneydsp::size_t>::value);
}

STONEYDSP_TEST_CASE ("[core][types][size_t][type_traits][is_pointer]",
                     "[core][types][size_t][type_traits][is_pointer]")
{
  STONEYDSP_REQUIRE (!::std::is_pointer< ::stoneydsp::size_t>::value);
}

STONEYDSP_TEST_CASE ("[core][types][size_t][type_traits][is_const]",
                     "[core][types][size_t][type_traits][is_const]")
{
  STONEYDSP_REQUIRE (!::std::is_const< ::stoneydsp::size_t>::value);
}

STONEYDSP_TEST_CASE ("[core][types][size_t][type_traits][is_empty]",
                     "[core][types][size_t][type_traits][is_empty]")
{
  STONEYDSP_REQUIRE (!::std::is_empty< ::stoneydsp::size_t>::value);
}

STONEYDSP_TEST_CASE (
    "[core][types][size_t][type_traits][is_trivially_copyable]",
    "[core][types][size_t][type_traits][is_trivially_copyable]")
{
  STONEYDSP_REQUIRE (
      ::std::is_trivially_copyable< ::stoneydsp::size_t>::value);
}

STONEYDSP_TEST_CASE ("[core][types][size_t][type_traits][is_standard_layout]",
                     "[core][types][size_t][type_traits][is_standard_layout]")
{
  STONEYDSP_REQUIRE (::std::is_standard_layout< ::stoneydsp::size_t>::value);
}

// //==============================================================//numeric_limits

// STONEYDSP_TEST_CASE ("[core][types][size_t][numeric_limits]",
//                      "[core][types][size_t][numeric_limits]")
// {
//   // { 0UL }
//   STONEYDSP_REQUIRE (::stoneydsp::numeric_limits< ::stoneydsp::size_t>::min
//   ()
//                      == ::std::numeric_limits< ::std::size_t>::min ());
//   // { 18446744073709551615UL }
//   STONEYDSP_REQUIRE (::stoneydsp::numeric_limits< ::stoneydsp::size_t>::max
//   ()
//                      == ::std::numeric_limits< ::std::size_t>::max ());
//   STONEYDSP_REQUIRE (
//       ::stoneydsp::numeric_limits< ::stoneydsp::size_t>::lowest ()
//       == ::std::numeric_limits< ::std::size_t>::lowest ());
// }

//==================================================================//endianness

STONEYDSP_TEST_CASE ("[core][types][size_t][endianness]",
                     "[core][types][size_t][endianness]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::size_t value = 0x12345678_size_t;
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

STONEYDSP_TEST_CASE ("[core][types][size_t][rounding]",
                     "[core][types][size_t][rounding]")
{
  float a = 1.5f;
  ::stoneydsp::size_t b = static_cast< ::stoneydsp::size_t> (::std::round (a));
  STONEYDSP_REQUIRE (
      b == 2); // 1.5 rounded to nearest integer and cast to size_t
}

//==================================================================//arithmetic

STONEYDSP_TEST_CASE ("[core][types][size_t][arithmetic]",
                     "[core][types][size_t][arithmetic]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::size_t a = 15_size_t;
  ::stoneydsp::size_t b = 20_size_t;

  STONEYDSP_REQUIRE (a + b == 35); // Addition
  STONEYDSP_REQUIRE (
      a - b
      == static_cast< ::stoneydsp::size_t> (-5)); // Subtraction (wrap-around)
  STONEYDSP_REQUIRE (a * b == 300);               // Multiplication
  STONEYDSP_REQUIRE (b / a == 1);                 // Division
  STONEYDSP_REQUIRE (b % a == 5);                 // Modulo
}

//===============================================================//bitwise

STONEYDSP_TEST_CASE ("[core][types][size_t][bitwise][logic]",
                     "[core][types][size_t][bitwise][logic]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::size_t a = 5_size_t; // 0101
  ::stoneydsp::size_t b = 3_size_t; // 0011

  STONEYDSP_REQUIRE ((a & b) == 1); // AND: 0001
  STONEYDSP_REQUIRE ((a | b) == 7); // OR:  0111
  STONEYDSP_REQUIRE ((a ^ b) == 6); // XOR: 0110
  STONEYDSP_REQUIRE ((~a & std::numeric_limits< ::stoneydsp::size_t>::max ())
                     == ~static_cast< ::stoneydsp::size_t> (5)); // NOT
}

STONEYDSP_TEST_CASE ("[core][types][size_t][bitwise][arithmetic]",
                     "[core][types][size_t][bitwise][arithmetic]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::size_t a = 5_size_t; // 0101

  STONEYDSP_REQUIRE ((a << 1) == 10); // Left shift: 1010
  STONEYDSP_REQUIRE ((a >> 1) == 2);  // Right shift: 0010
}

//===============================================================//comparison

STONEYDSP_TEST_CASE ("[core][types][size_t][comparison]",
                     "[core][types][size_t][comparison]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::size_t a = 5_size_t;
  ::stoneydsp::size_t b = 3_size_t;

  STONEYDSP_REQUIRE ((a == b) == false);
  STONEYDSP_REQUIRE ((a != b) == true);
  STONEYDSP_REQUIRE ((a > b) == true);
  STONEYDSP_REQUIRE ((a < b) == false);
  STONEYDSP_REQUIRE ((a >= b) == true);
  STONEYDSP_REQUIRE ((a <= b) == false);
}

//===============================================================//serialization

STONEYDSP_TEST_CASE ("[core][types][size_t][serialization]",
                     "[core][types][size_t][serialization]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::std::stringstream ss;
  ::stoneydsp::size_t originalValue = 42_size_t;
  ::stoneydsp::size_t deserializedValue;

  ss.write (reinterpret_cast<const char *> (&originalValue),
            sizeof (originalValue));
  ss.read (reinterpret_cast<char *> (&deserializedValue),
           sizeof (deserializedValue));

  STONEYDSP_REQUIRE (originalValue == deserializedValue);
}

//=======================================================//boundary_and_overflow

STONEYDSP_TEST_CASE ("[core][types][size_t][boundary][overflow]",
                     "[core][types][size_t][boundary][overflow]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::size_t a = std::numeric_limits< ::stoneydsp::size_t>::max ();
  ::stoneydsp::size_t b = 1_size_t;

  STONEYDSP_REQUIRE (static_cast< ::stoneydsp::size_t> (a + b)
                     == 0); // Check overflow wrap-around behaviour
}

//======================================================//boundary_and_underflow

STONEYDSP_TEST_CASE ("[core][types][size_t][boundary][underflow]",
                     "[core][types][size_t][boundary][underflow]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::size_t a = 0_size_t;
  ::stoneydsp::size_t b = 1_size_t;

  STONEYDSP_REQUIRE (static_cast< ::stoneydsp::size_t> (a - b)
                     == std::numeric_limits< ::stoneydsp::size_t>::
                         max ()); // Check underflow wrap-around behavior
}

//===============================================================//compatibility

STONEYDSP_TEST_CASE ("[core][types][size_t][compatibility]",
                     "[core][types][size_t][compatibility]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::std::vector< ::stoneydsp::size_t> vec
      = { 5_size_t, 3_size_t, 4_size_t, 1_size_t, 2_size_t };

  // Use std::sort to sort the vector
  ::std::sort (vec.begin (), vec.end ());

  // Verify the vector is sorted
  STONEYDSP_REQUIRE (vec
                     == ::std::vector< ::stoneydsp::size_t>{
                         1_size_t, 2_size_t, 3_size_t, 4_size_t, 5_size_t });

  // Use std::accumulate to sum the elements
  ::stoneydsp::size_t sum = ::std::accumulate (vec.begin (), vec.end (),
                                               ::stoneydsp::size_t (0_size_t));

  // Verify the sum is correct
  STONEYDSP_REQUIRE (sum == 15);
}

//===================================================================//benchmark

// Benchmark for addition
STONEYDSP_TEST_CASE ("[core][types][size_t][benchmark][addition]",
                     "[core][types][size_t][benchmark][addition]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::size_t a = 1200_size_t;
  ::stoneydsp::size_t b = 3400_size_t;

  STONEYDSP_BENCHMARK ("Addition") { return a + b; };
}

// Benchmark for subtraction
STONEYDSP_TEST_CASE ("[core][types][size_t][benchmark][subtraction]",
                     "[core][types][size_t][benchmark][subtraction]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::size_t a = 3400_size_t;
  ::stoneydsp::size_t b = 1200_size_t;

  STONEYDSP_BENCHMARK ("Subtraction") { return a - b; };
}

// Benchmark for multiplication
STONEYDSP_TEST_CASE ("[core][types][size_t][benchmark][multiplication]",
                     "[core][types][size_t][benchmark][multiplication]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::size_t a = 1200_size_t;
  ::stoneydsp::size_t b = 2_size_t;

  STONEYDSP_BENCHMARK ("Multiplication") { return a * b; };
}

// Benchmark for division
STONEYDSP_TEST_CASE ("[core][types][size_t][benchmark][division]",
                     "[core][types][size_t][benchmark][division]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::size_t a = 1200_size_t;
  ::stoneydsp::size_t b = 2_size_t;

  STONEYDSP_BENCHMARK ("Division") { return a / b; };
}

// Benchmark for type conversion to int
STONEYDSP_TEST_CASE ("[core][types][size_t][benchmark][conversion][int]",
                     "[core][types][size_t][benchmark][conversion][int]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::size_t a = 1200_size_t;

  STONEYDSP_BENCHMARK ("Conversion to int") { return static_cast<int> (a); };
}

// Benchmark for type conversion to float
STONEYDSP_TEST_CASE ("[core][types][size_t][benchmark][conversion][float]",
                     "[core][types][size_t][benchmark][conversion][float]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::size_t a = 1200_size_t;

  STONEYDSP_BENCHMARK ("Conversion to float")
  {
    return static_cast<float> (a);
  };
}

//============================================================================//

#endif // defined(STONEYDSP_BUILD_TEST)

//=========================================================================//EOF
