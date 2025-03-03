/**
 * @file uint.test.cpp
 * @brief Test suite for stoneydsp::uint_t
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

STONEYDSP_TEST_CASE ("[core][types][uint_t][requirements]",
                     "[core][types][uint_t][requirements]")
{
  STONEYDSP_SECTION ("[core][types][uint_t][requirements][max]")
  {
    bool result = false;
  #if defined(UINT_MAX)
    result = true;
  #endif
    STONEYDSP_REQUIRE (result == true);
  }
}

//======================================================================//sizeof

STONEYDSP_TEST_CASE ("[core][types][uint_t][sizeof]",
                     "[core][types][uint_t][sizeof]")
{
  STONEYDSP_REQUIRE (sizeof (::stoneydsp::uint_t) == 4UL);
}

//=====================================================================//alignof

STONEYDSP_TEST_CASE ("[core][types][uint_t][alignof]",
                     "[core][types][uint_t][alignof]")
{
  STONEYDSP_REQUIRE (alignof (::stoneydsp::uint_t) == 4UL);
}

//=================================================================//type_traits

STONEYDSP_TEST_CASE ("[core][types][uint_t][type_traits][is_integral]",
                     "[core][types][uint_t][type_traits][is_integral]")
{
  STONEYDSP_REQUIRE (::std::is_integral< ::stoneydsp::uint_t>::value);
}

STONEYDSP_TEST_CASE ("[core][types][uint_t][type_traits][is_unsigned]",
                     "[core][types][uint_t][type_traits][is_unsigned]")
{
  STONEYDSP_REQUIRE (::std::is_unsigned< ::stoneydsp::uint_t>::value);
}

STONEYDSP_TEST_CASE ("[core][types][uint_t][type_traits][is_arithmetic]",
                     "[core][types][uint_t][type_traits][is_arithmetic]")
{
  STONEYDSP_REQUIRE (::std::is_arithmetic< ::stoneydsp::uint_t>::value);
}

STONEYDSP_TEST_CASE ("[core][types][uint_t][type_traits][is_pointer]",
                     "[core][types][uint_t][type_traits][is_pointer]")
{
  STONEYDSP_REQUIRE (!::std::is_pointer< ::stoneydsp::uint_t>::value);
}

STONEYDSP_TEST_CASE ("[core][types][uint_t][type_traits][is_const]",
                     "[core][types][uint_t][type_traits][is_const]")
{
  STONEYDSP_REQUIRE (!::std::is_const< ::stoneydsp::uint_t>::value);
}

STONEYDSP_TEST_CASE ("[core][types][uint_t][type_traits][is_empty]",
                     "[core][types][uint_t][type_traits][is_empty]")
{
  STONEYDSP_REQUIRE (!::std::is_empty< ::stoneydsp::uint_t>::value);
}

STONEYDSP_TEST_CASE (
    "[core][types][uint_t][type_traits][is_trivially_copyable]",
    "[core][types][uint_t][type_traits][is_trivially_copyable]")
{
  STONEYDSP_REQUIRE (
      ::std::is_trivially_copyable< ::stoneydsp::uint_t>::value);
}

STONEYDSP_TEST_CASE ("[core][types][uint_t][type_traits][is_standard_layout]",
                     "[core][types][uint_t][type_traits][is_standard_layout]")
{
  STONEYDSP_REQUIRE (::std::is_standard_layout< ::stoneydsp::uint_t>::value);
}

//==============================================================//numeric_limits

STONEYDSP_TEST_CASE ("[core][types][uint_t][numeric_limits]",
                     "[core][types][uint_t][numeric_limits]")
{
  // { 0U }
  STONEYDSP_REQUIRE (::stoneydsp::numeric_limits< ::stoneydsp::uint_t>::min ()
                     == ::std::numeric_limits< ::stoneydsp::uint_t>::min ());
  // { 4294967295UL }
  STONEYDSP_REQUIRE (::stoneydsp::numeric_limits< ::stoneydsp::uint_t>::max ()
                     == ::std::numeric_limits< ::stoneydsp::uint_t>::max ());
  // { 0U }
  STONEYDSP_REQUIRE (
      ::stoneydsp::numeric_limits< ::stoneydsp::uint_t>::lowest ()
      == ::std::numeric_limits< ::stoneydsp::uint_t>::lowest ());
}

//==============================================================//special_values

STONEYDSP_TEST_CASE ("[core][types][uint_t][special_values]",
                     "[core][types][uint_t][special_values]")
{
  ::stoneydsp::uint_t min_val
      = ::std::numeric_limits< ::stoneydsp::uint_t>::min ();
  ::stoneydsp::uint_t max_val
      = ::std::numeric_limits< ::stoneydsp::uint_t>::max ();
  STONEYDSP_REQUIRE (min_val == 0U);           // Minimum value for uint_t
  STONEYDSP_REQUIRE (max_val == 4294967295UL); // Maximum value for uint_t
}

//==================================================================//endianness

STONEYDSP_TEST_CASE ("[core][types][uint_t][endianness]",
                     "[core][types][uint_t][endianness]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::uint_t value = 0x12345678_uint_t;
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

STONEYDSP_TEST_CASE ("[core][types][uint_t][rounding]",
                     "[core][types][uint_t][rounding]")
{
  ::stoneydsp::float_t a = 1.5f;
  ::stoneydsp::uint_t b = static_cast< ::stoneydsp::uint_t> (::std::round (a));
  STONEYDSP_REQUIRE (
      b == 2); // 1.5 rounded to nearest integer and cast to uint_t
}

//==================================================================//arithmetic

STONEYDSP_TEST_CASE ("[core][types][uint_t][arithmetic]",
                     "[core][types][uint_t][arithmetic]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::uint_t a = 1500000000_uint_t;
  ::stoneydsp::uint_t b = 2_uint_t;

  STONEYDSP_REQUIRE (a + b == 1500000002); // Addition
  STONEYDSP_REQUIRE (a - b == 1499999998); // Subtraction
  STONEYDSP_REQUIRE (a * b == 3000000000); // Multiplication
  STONEYDSP_REQUIRE (b / a == 0);          // Division
  STONEYDSP_REQUIRE (b % a == 2);          // Modulo
}

//=====================================================================//bitwise

STONEYDSP_TEST_CASE ("[core][types][uint_t][bitwise][logic]",
                     "[core][types][uint_t][bitwise][logic]")
{
  using namespace ::stoneydsp::core::types::literals;

  // clang-format off
  ::stoneydsp::uint_t a = 5_uint_t; // 0000 0000 0000 0000 0000 0000 0000 0101
  ::stoneydsp::uint_t b = 3_uint_t; // 0000 0000 0000 0000 0000 0000 0000 0011

  STONEYDSP_REQUIRE ((a & b) == 1); // AND: 0000 0000 0000 0000 0000 0000 0000 0001
  STONEYDSP_REQUIRE ((a | b) == 7); // OR:  0000 0000 0000 0000 0000 0000 0000 0111
  STONEYDSP_REQUIRE ((a ^ b) == 6); // XOR: 0000 0000 0000 0000 0000 0000 0000 0110
  STONEYDSP_REQUIRE ((~a & 0xFFFFFFFF) == 4294967290UL); // NOT: 1111 1111 1111 1111 1111 1111 1111 1010 (considering uint_t wrap-around)
  // clang-format on
}

STONEYDSP_TEST_CASE ("[core][types][uint_t][bitwise][arithmetic]",
                     "[core][types][uint_t][bitwise][arithmetic]")
{
  using namespace ::stoneydsp::core::types::literals;

  // clang-format off
  ::stoneydsp::uint_t a = 5_uint_t; // 0000 0000 0000 0000 0000 0000 0000 0101
  STONEYDSP_REQUIRE ((a << 1) == 10); // Left shift: 0000 0000 0000 0000 0000 0000 0000 1010
  STONEYDSP_REQUIRE ((a >> 1) == 2); // Right shift: 0000 0000 0000 0000 0000 0000 0000 0010
                  // clang-format on
}

//==================================================================//comparison

STONEYDSP_TEST_CASE ("[core][types][uint_t][comparison]",
                     "[core][types][uint_t][comparison]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::uint_t a = 5_uint_t;
  ::stoneydsp::uint_t b = 3_uint_t;

  STONEYDSP_REQUIRE ((a == b) == false);
  STONEYDSP_REQUIRE ((a != b) == true);
  STONEYDSP_REQUIRE ((a > b) == true);
  STONEYDSP_REQUIRE ((a < b) == false);
  STONEYDSP_REQUIRE ((a >= b) == true);
  STONEYDSP_REQUIRE ((a <= b) == false);
}

//===============================================================//serialization

STONEYDSP_TEST_CASE ("[core][types][uint_t][serialization]",
                     "[core][types][uint_t][serialization]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::std::stringstream ss;
  ::stoneydsp::uint_t originalValue = 42_uint_t;
  ::stoneydsp::uint_t deserializedValue;

  ss.write (reinterpret_cast<const char *> (&originalValue),
            sizeof (originalValue));
  ss.read (reinterpret_cast<char *> (&deserializedValue),
           sizeof (deserializedValue));

  STONEYDSP_REQUIRE (originalValue == deserializedValue);
}

//=======================================================//boundary_and_overflow

STONEYDSP_TEST_CASE ("[core][types][uint_t][boundary][overflow]",
                     "[core][types][uint_t][boundary][overflow]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::uint_t a = 4294967295_uint_t;
  ::stoneydsp::uint_t b = 1_uint_t;

  STONEYDSP_REQUIRE (static_cast< ::stoneydsp::uint_t> (a + b)
                     == 0); // Check overflow wrap-around behaviour
}

//======================================================//boundary_and_underflow

STONEYDSP_TEST_CASE ("[core][types][uint_t][boundary][underflow]",
                     "[core][types][uint_t][boundary][underflow]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::uint_t a = 0_uint_t;
  ::stoneydsp::uint_t b = 1_uint_t;

  STONEYDSP_REQUIRE (static_cast< ::stoneydsp::uint_t> (a - b)
                     == 4294967295UL); // Check underflow wrap-around behavior
}

//===============================================================//compatibility

STONEYDSP_TEST_CASE ("[core][types][uint_t][compatibility]",
                     "[core][types][uint_t][compatibility]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::std::vector< ::stoneydsp::uint_t> vec
      = { 5_uint_t, 3_uint_t, 4_uint_t, 1_uint_t, 2_uint_t };

  // Use std::sort to sort the vector
  ::std::sort (vec.begin (), vec.end ());

  // Verify the vector is sorted
  STONEYDSP_REQUIRE (vec
                     == ::std::vector< ::stoneydsp::uint_t>{
                         1_uint_t, 2_uint_t, 3_uint_t, 4_uint_t, 5_uint_t });

  // Use std::accumulate to sum the elements
  ::stoneydsp::uint_t sum = ::std::accumulate (vec.begin (), vec.end (),
                                               ::stoneydsp::uint_t (0_uint_t));

  // Verify the sum is correct
  STONEYDSP_REQUIRE (sum == 15);
}

//===================================================================//benchmark

// Benchmark for addition
STONEYDSP_TEST_CASE ("[core][types][uint_t][benchmark][addition]",
                     "[core][types][uint_t][benchmark][addition]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::uint_t a = 1200_uint_t;
  ::stoneydsp::uint_t b = 3400_uint_t;

  STONEYDSP_BENCHMARK ("Addition") { return a + b; };
}

// Benchmark for subtraction
STONEYDSP_TEST_CASE ("[core][types][uint_t][benchmark][subtraction]",
                     "[core][types][uint_t][benchmark][subtraction]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::uint_t a = 3400_uint_t;
  ::stoneydsp::uint_t b = 1200_uint_t;

  STONEYDSP_BENCHMARK ("Subtraction") { return a - b; };
}

// Benchmark for multiplication
STONEYDSP_TEST_CASE ("[core][types][uint_t][benchmark][multiplication]",
                     "[core][types][uint_t][benchmark][multiplication]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::uint_t a = 1200_uint_t;
  ::stoneydsp::uint_t b = 2_uint_t;

  STONEYDSP_BENCHMARK ("Multiplication") { return a * b; };
}

// Benchmark for division
STONEYDSP_TEST_CASE ("[core][types][uint_t][benchmark][division]",
                     "[core][types][uint_t][benchmark][division]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::uint_t a = 1200_uint_t;
  ::stoneydsp::uint_t b = 2_uint_t;

  STONEYDSP_BENCHMARK ("Division") { return a / b; };
}

// Benchmark for type conversion to int
STONEYDSP_TEST_CASE ("[core][types][uint_t][benchmark][conversion][int]",
                     "[core][types][uint_t][benchmark][conversion][int]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::uint_t a = 1200_uint_t;

  STONEYDSP_BENCHMARK ("Conversion to int") { return static_cast<int> (a); };
}

// Benchmark for type conversion to float
STONEYDSP_TEST_CASE ("[core][types][uint_t][benchmark][conversion][float]",
                     "[core][types][uint_t][benchmark][conversion][float]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::uint_t a = 1200_uint_t;

  STONEYDSP_BENCHMARK ("Conversion to float")
  {
    return static_cast<float> (a);
  };
}

//============================================================================//

#endif // defined(STONEYDSP_BUILD_TEST)

//=========================================================================//EOF
