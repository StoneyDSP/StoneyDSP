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

  #include "utils.test.hpp"

//======================================================================//sizeof

STONEYDSP_TEST_CASE ("[core][types][int_t][sizeof]",
                     "[core][types][int_t][sizeof]")
{
  STONEYDSP_REQUIRE (sizeof (::stoneydsp::int_t) == 4UL);
}

//=====================================================================//alignof

STONEYDSP_TEST_CASE ("[core][types][int_t][alignof]",
                     "[core][types][int_t][alignof]")
{
  STONEYDSP_REQUIRE (alignof (::stoneydsp::int_t) == 4UL);
}

//=================================================================//type_traits

STONEYDSP_TEST_CASE ("[core][types][int_t][type_traits][is_integral]",
	"[core][types][int_t][type_traits][is_integral]")
{
STONEYDSP_REQUIRE (::std::is_integral< ::stoneydsp::int_t>::value);
}

STONEYDSP_TEST_CASE ("[core][types][int_t][type_traits][is_unsigned]",
	"[core][types][int_t][type_traits][is_unsigned]")
{
STONEYDSP_REQUIRE (::std::is_unsigned< ::stoneydsp::int_t>::value);
}

STONEYDSP_TEST_CASE ("[core][types][int_t][type_traits][is_arithmetic]",
	"[core][types][int_t][type_traits][is_arithmetic]")
{
STONEYDSP_REQUIRE (::std::is_arithmetic< ::stoneydsp::int_t>::value);
}

STONEYDSP_TEST_CASE ("[core][types][int_t][type_traits][is_pointer]",
	"[core][types][int_t][type_traits][is_pointer]")
{
STONEYDSP_REQUIRE (!::std::is_pointer< ::stoneydsp::int_t>::value);
}

STONEYDSP_TEST_CASE ("[core][types][int_t][type_traits][is_const]",
	"[core][types][int_t][type_traits][is_const]")
{
STONEYDSP_REQUIRE (!::std::is_const< ::stoneydsp::int_t>::value);
}

STONEYDSP_TEST_CASE ("[core][types][int_t][type_traits][is_empty]",
	"[core][types][int_t][type_traits][is_empty]")
{
STONEYDSP_REQUIRE (!::std::is_empty< ::stoneydsp::int_t>::value);
}

STONEYDSP_TEST_CASE (
"[core][types][int_t][type_traits][is_trivially_copyable]",
"[core][types][int_t][type_traits][is_trivially_copyable]")
{
STONEYDSP_REQUIRE (
::std::is_trivially_copyable< ::stoneydsp::int_t>::value);
}

STONEYDSP_TEST_CASE ("[core][types][int_t][type_traits][is_standard_layout]",
	"[core][types][int_t][type_traits][is_standard_layout]")
{
STONEYDSP_REQUIRE (::std::is_standard_layout< ::stoneydsp::int_t>::value);
}

//==============================================================//numeric_limits

STONEYDSP_TEST_CASE ("[core][types][int_t][numeric_limits]",
                     "[core][types][int_t][numeric_limits]")
{
  // { -2147483648 }
  STONEYDSP_REQUIRE (::stoneydsp::numeric_limits< ::stoneydsp::int_t>::min ()
                     == ::std::numeric_limits< ::stoneydsp::int_t>::min ());
  // { 2147483647 }
  STONEYDSP_REQUIRE (::stoneydsp::numeric_limits< ::stoneydsp::int_t>::max ()
                     == ::std::numeric_limits< ::stoneydsp::int_t>::max ());
  // { -2147483648 }
  STONEYDSP_REQUIRE (
      ::stoneydsp::numeric_limits< ::stoneydsp::int_t>::lowest ()
      == ::std::numeric_limits< ::stoneydsp::int_t>::lowest ());
}

//==============================================================//special_values

STONEYDSP_TEST_CASE ("[core][types][int_t][special_values]",
                     "[core][types][int_t][special_values]")
{
  ::stoneydsp::int_t min_val
      = ::std::numeric_limits< ::stoneydsp::int_t>::min ();
  ::stoneydsp::int_t max_val
      = ::std::numeric_limits< ::stoneydsp::int_t>::max ();
  STONEYDSP_REQUIRE (min_val == -2147483648); // Minimum value for int_t
  STONEYDSP_REQUIRE (max_val == 2147483647);  // Maximum value for int_t
}

//==================================================================//endianness

STONEYDSP_TEST_CASE ("[core][types][int_t][endianness]",
                     "[core][types][int_t][endianness]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::int_t value = 0x12345678_int_t;
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

STONEYDSP_TEST_CASE ("[core][types][int_t][rounding]",
                     "[core][types][int_t][rounding]")
{
  ::stoneydsp::float_t a = 1.5f;
  ::stoneydsp::int_t b = static_cast< ::stoneydsp::int_t> (::std::round (a));
  STONEYDSP_REQUIRE (b
                     == 2); // 1.5 rounded to nearest integer and cast to int_t
}

//==================================================================//arithmetic

STONEYDSP_TEST_CASE ("[core][types][int_t][arithmetic]",
                     "[core][types][int_t][arithmetic]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::int_t a = 15000_int_t;
  ::stoneydsp::int_t b = 20000_int_t;

  STONEYDSP_REQUIRE (a + b == 35000_int_t);     // Addition
  STONEYDSP_REQUIRE (a - b == -5000_int_t);     // Subtraction
  STONEYDSP_REQUIRE (a * b == 300000000_int_t); // Multiplication
  STONEYDSP_REQUIRE (b / a == 1_int_t);         // Division
  STONEYDSP_REQUIRE (b % a == 5000_int_t);      // Modulo
}

//=====================================================================//bitwise

STONEYDSP_TEST_CASE ("[core][types][int_t][bitwise][logic]",
                     "[core][types][int_t][bitwise][logic]")
{
  using namespace ::stoneydsp::core::types::literals;

  // clang-format off
  ::stoneydsp::int_t a = 5_int_t; // 0000 0000 0000 0000 0000 0000 0000 0101
  ::stoneydsp::int_t b = 3_int_t; // 0000 0000 0000 0000 0000 0000 0000 0011

  STONEYDSP_REQUIRE ((a & b) == 1); // AND: 0000 0000 0000 0000 0000 0000 0000 0001
  STONEYDSP_REQUIRE ((a | b) == 7); // OR:  0000 0000 0000 0000 0000 0000 0000 0111
  STONEYDSP_REQUIRE ((a ^ b) == 6); // XOR: 0000 0000 0000 0000 0000 0000 0000 0110
  STONEYDSP_REQUIRE (~a == -6);     // NOT: considering wrap-around for int_t
                             // clang-format on
}

STONEYDSP_TEST_CASE ("[core][types][int_t][bitwise][arithmetic]",
                     "[core][types][int_t][bitwise][arithmetic]")
{
  using namespace ::stoneydsp::core::types::literals;

  // clang-format off
  ::stoneydsp::int_t a = 5_int_t; // 0000 0000 0000 0000 0000 0000 0000 0101

  STONEYDSP_REQUIRE ((a << 1) == 10); // Left shift: 0000 0000 0000 0000 0000 0000 0000 1010
	STONEYDSP_REQUIRE ((a >> 1) == 2); // Right shift: 0000 0000 0000 0000 0000 0000 0000 0010
  // clang-format on
}

//==================================================================//comparison

STONEYDSP_TEST_CASE ("[core][types][int_t][comparison]",
                     "[core][types][int_t][comparison]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::int_t a = 5_int_t;
  ::stoneydsp::int_t b = 3_int_t;

  STONEYDSP_REQUIRE ((a == b) == false);
  STONEYDSP_REQUIRE ((a != b) == true);
  STONEYDSP_REQUIRE ((a > b) == true);
  STONEYDSP_REQUIRE ((a < b) == false);
  STONEYDSP_REQUIRE ((a >= b) == true);
  STONEYDSP_REQUIRE ((a <= b) == false);
}

//===============================================================//serialization

STONEYDSP_TEST_CASE ("[core][types][int_t][serialization]",
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

  STONEYDSP_REQUIRE (originalValue == deserializedValue);
}

//=======================================================//boundary_and_overflow

STONEYDSP_TEST_CASE ("[core][types][int_t][boundary][overflow]",
                     "[core][types][int_t][boundary][overflow]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::int_t a = 2147483647_int_t;
  ::stoneydsp::int_t b = 1_int_t;

  STONEYDSP_REQUIRE (static_cast< ::stoneydsp::int_t> (a + b)
                     == -2147483648); // Check overflow wrap-around behaviour
}

//======================================================//boundary_and_underflow

STONEYDSP_TEST_CASE ("[core][types][int_t][boundary][underflow]",
                     "[core][types][int_t][boundary][underflow]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::int_t a = -2147483647_int_t - 1_int_t; // _int;
  ::stoneydsp::int_t b = 1_int_t;

  STONEYDSP_REQUIRE (static_cast< ::stoneydsp::int_t> (a - b)
                     == 2147483647); // Check underflow wrap-around behavior
}

//===============================================================//compatibility

STONEYDSP_TEST_CASE ("[core][types][int_t][compatibility]",
                     "[core][types][int_t][compatibility]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::std::vector< ::stoneydsp::int_t> vec
      = { 5_int_t, 3_int_t, 4_int_t, 1_int_t, 2_int_t };

  // Use std::sort to sort the vector
  ::std::sort (vec.begin (), vec.end ());

  // Verify the vector is sorted
  STONEYDSP_REQUIRE (vec
                     == ::std::vector< ::stoneydsp::int_t>{
                         1_int_t, 2_int_t, 3_int_t, 4_int_t, 5_int_t });

  // Use std::accumulate to sum the elements
  ::stoneydsp::int_t sum = ::std::accumulate (vec.begin (), vec.end (),
                                              ::stoneydsp::int_t (0_int_t));

  // Verify the sum is correct
  STONEYDSP_REQUIRE (sum == 15);
}

//===================================================================//benchmark

// Benchmark for addition
STONEYDSP_TEST_CASE ("[core][types][int_t][benchmark][addition]",
                     "[core][types][int_t][benchmark][addition]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::int_t a = 1200_int_t;
  ::stoneydsp::int_t b = 3400_int_t;

  STONEYDSP_BENCHMARK ("Addition") { return a + b; };
}

// Benchmark for subtraction
STONEYDSP_TEST_CASE ("[core][types][int_t][benchmark][subtraction]",
                     "[core][types][int_t][benchmark][subtraction]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::int_t a = 3400_int_t;
  ::stoneydsp::int_t b = 1200_int_t;

  STONEYDSP_BENCHMARK ("Subtraction") { return a - b; };
}

// Benchmark for multiplication
STONEYDSP_TEST_CASE ("[core][types][int_t][benchmark][multiplication]",
                     "[core][types][int_t][benchmark][multiplication]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::int_t a = 1200_int_t;
  ::stoneydsp::int_t b = 2_int_t;

  STONEYDSP_BENCHMARK ("Multiplication") { return a * b; };
}

// Benchmark for division
STONEYDSP_TEST_CASE ("[core][types][int_t][benchmark][division]",
                     "[core][types][int_t][benchmark][division]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::int_t a = 1200_int_t;
  ::stoneydsp::int_t b = 2_int_t;

  STONEYDSP_BENCHMARK ("Division") { return a / b; };
}

// Benchmark for type conversion to int
STONEYDSP_TEST_CASE (
    "[core][types][int_t][benchmark][division][conversion][int]",
    "[core][types][int_t][benchmark][division][conversion][int]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::int_t a = 1200_int_t;

  STONEYDSP_BENCHMARK ("Conversion to int") { return static_cast<int> (a); };
}

// Benchmark for type conversion to float
STONEYDSP_TEST_CASE (
    "[core][types][int_t][benchmark][division][conversion][float]",
    "[core][types][int_t][benchmark][division][conversion][float]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::int_t a = 1200_int_t;

  STONEYDSP_BENCHMARK ("Conversion to float")
  {
    return static_cast<float> (a);
  };
}

//============================================================================//

#endif // defined(STONEYDSP_BUILD_TEST)

//=========================================================================//EOF
