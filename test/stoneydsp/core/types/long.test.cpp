/**
 * @file long.test.cpp
 * @brief Test suite for stoneydsp::long_t
 * @copyright Copyright (c) 2025
 *
 */

//==============================================================================

#include "stoneydsp/core/types/long.h"

//==============================================================================

#if defined(STONEYDSP_BUILD_TEST) && defined(STONEYDSP_BUILD_CORE)

//==============================================================================

  #include "../../../utils.test.hpp"

//================================================================//requirements

STONEYDSP_TEST_CASE ("[core][types][long_t][requirements]",
                     "[core][types][long_t][requirements]")
{
  STONEYDSP_SECTION ("[core][types][long_t][requirements][min]")
  {
    bool result = false;
  #if defined(LONG_MIN)
    result = true;
  #endif
    STONEYDSP_REQUIRE (result == true);
  }
  STONEYDSP_SECTION ("[core][types][long_t][requirements][max]")
  {
    bool result = false;
  #if defined(LONG_MAX)
    result = true;
  #endif
    STONEYDSP_REQUIRE (result == true);
  }
}

//======================================================================//sizeof

STONEYDSP_TEST_CASE ("[core][types][long_t][sizeof]",
                     "[core][types][long_t][sizeof]")
{
  #ifdef STONEYDSP_WINDOWS
  STONEYDSP_REQUIRE (sizeof (::stoneydsp::long_t) == 4UL);
  #else
  STONEYDSP_REQUIRE (sizeof (::stoneydsp::long_t) == 8UL);
  #endif
}

//=====================================================================//alignof

STONEYDSP_TEST_CASE ("[core][types][long_t][alignof]",
                     "[core][types][long_t][alignof]")
{
  #ifdef STONEYDSP_WINDOWS
  STONEYDSP_REQUIRE (alignof (::stoneydsp::long_t) == 4UL);
  #else
  STONEYDSP_REQUIRE (alignof (::stoneydsp::long_t) == 8UL);
  #endif
}

//=================================================================//type_traits

STONEYDSP_TEST_CASE ("[core][types][long_t][type_traits][is_integral]",
                     "[core][types][long_t][type_traits][is_integral]")
{
  STONEYDSP_REQUIRE (::std::is_integral< ::stoneydsp::long_t>::value);
}

STONEYDSP_TEST_CASE ("[core][types][long_t][type_traits][is_unsigned]",
                     "[core][types][long_t][type_traits][is_unsigned]")
{
  STONEYDSP_REQUIRE (!::std::is_unsigned< ::stoneydsp::long_t>::value);
}

STONEYDSP_TEST_CASE ("[core][types][long_t][type_traits][is_arithmetic]",
                     "[core][types][long_t][type_traits][is_arithmetic]")
{
  STONEYDSP_REQUIRE (::std::is_arithmetic< ::stoneydsp::long_t>::value);
}

STONEYDSP_TEST_CASE ("[core][types][long_t][type_traits][is_pointer]",
                     "[core][types][long_t][type_traits][is_pointer]")
{
  STONEYDSP_REQUIRE (!::std::is_pointer< ::stoneydsp::long_t>::value);
}

STONEYDSP_TEST_CASE ("[core][types][long_t][type_traits][is_const]",
                     "[core][types][long_t][type_traits][is_const]")
{
  STONEYDSP_REQUIRE (!::std::is_const< ::stoneydsp::long_t>::value);
}

STONEYDSP_TEST_CASE ("[core][types][long_t][type_traits][is_empty]",
                     "[core][types][long_t][type_traits][is_empty]")
{
  STONEYDSP_REQUIRE (!::std::is_empty< ::stoneydsp::long_t>::value);
}

STONEYDSP_TEST_CASE (
    "[core][types][long_t][type_traits][is_trivially_copyable]",
    "[core][types][long_t][type_traits][is_trivially_copyable]")
{
  STONEYDSP_REQUIRE (
      ::std::is_trivially_copyable< ::stoneydsp::long_t>::value);
}

STONEYDSP_TEST_CASE ("[core][types][long_t][type_traits][is_standard_layout]",
                     "[core][types][long_t][type_traits][is_standard_layout]")
{
  STONEYDSP_REQUIRE (::std::is_standard_layout< ::stoneydsp::long_t>::value);
}

//==============================================================//numeric_limits

STONEYDSP_TEST_CASE ("[core][types][long_t][numeric_limits]",
                     "[core][types][long_t][numeric_limits]")
{
  // { -9223372036854775807L - 1 }
  STONEYDSP_REQUIRE (::stoneydsp::numeric_limits< ::stoneydsp::long_t>::min ()
                     == ::std::numeric_limits< ::stoneydsp::long_t>::min ());
  // { 9223372036854775807L }
  STONEYDSP_REQUIRE (::stoneydsp::numeric_limits< ::stoneydsp::long_t>::max ()
                     == ::std::numeric_limits< ::stoneydsp::long_t>::max ());
  // { -9223372036854775807L - 1 }
  STONEYDSP_REQUIRE (
      ::stoneydsp::numeric_limits< ::stoneydsp::long_t>::lowest ()
      == ::std::numeric_limits< ::stoneydsp::long_t>::lowest ());
}

//==============================================================//special_values

STONEYDSP_TEST_CASE ("[core][types][long_t][special_values]",
                     "[core][types][long_t][special_values]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::long_t min_val
      = ::std::numeric_limits< ::stoneydsp::long_t>::min ();
  ::stoneydsp::long_t max_val
      = ::std::numeric_limits< ::stoneydsp::long_t>::max ();
  #ifdef STONEYDSP_WINDOWS
  STONEYDSP_REQUIRE (
      min_val
      == ((-2147483647_long_t) - 1_long_t)); // Minimum value for 32-bit long_t
  STONEYDSP_REQUIRE (max_val
                     == 2147483647_long_t); // Maximum value for 32-bit long_t
  #else
  STONEYDSP_REQUIRE (min_val
                     == ((-9223372036854775807_long_t)
                         - 1_long_t)); // Minimum value for 64-bit long_t
  STONEYDSP_REQUIRE (
      max_val
      == 9223372036854775807_long_t); // Maximum value for 64-bit long_t
  #endif
}

//==================================================================//endianness

STONEYDSP_TEST_CASE ("[core][types][long_t][endianness]",
                     "[core][types][long_t][endianness]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::long_t value = 0x123456789ABCDEF0_long_t;
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

STONEYDSP_TEST_CASE ("[core][types][long_t][rounding]",
                     "[core][types][long_t][rounding]")
{
  float a = 1.5f;
  ::stoneydsp::long_t b = static_cast< ::stoneydsp::long_t> (::std::round (a));
  STONEYDSP_REQUIRE (
      b == 2); // 1.5 rounded to nearest integer and cast to long_t
}

//==================================================================//arithmetic

STONEYDSP_TEST_CASE ("[core][types][long_t][arithmetic]",
                     "[core][types][long_t][arithmetic]")
{
  using namespace ::stoneydsp::core::types::literals;

  // Using values within the 32-bit range
  // Maximum positive 32-bit long is 2147483647
  ::stoneydsp::long_t a = 15000_long_t;
  // Ensure no overflow during addition
  ::stoneydsp::long_t b = 200_long_t;

  STONEYDSP_REQUIRE (a + b == 15200L);   // Addition
  STONEYDSP_REQUIRE (a - b == 14800L);   // Subtraction
  STONEYDSP_REQUIRE (a * b == 3000000L); // Multiplication
  STONEYDSP_REQUIRE (b / a == 0L);       // Division (integer division)
  STONEYDSP_REQUIRE (b % a == 200L);     // Modulo
}

//=====================================================================//bitwise

STONEYDSP_TEST_CASE ("[core][types][long_t][bitwise][logic]",
                     "[core][types][long_t][bitwise][logic]")
{
  using namespace ::stoneydsp::core::types::literals;

  // clang-format off
	// 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0101
  ::stoneydsp::long_t a = 5_long_t;
	// 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0011
  ::stoneydsp::long_t b = 3_long_t;

	// AND: 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0001
  STONEYDSP_REQUIRE ((a & b) == 1);
	// OR:  0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0111
  STONEYDSP_REQUIRE ((a | b) == 7);
	// XOR: 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0110
  STONEYDSP_REQUIRE ((a ^ b) == 6);
	// NOT: considering wrap-around for long_t
  STONEYDSP_REQUIRE (~a == -6);
  // clang-format on
}

STONEYDSP_TEST_CASE ("[core][types][long_t][bitwise][arithmetic]",
                     "[core][types][long_t][bitwise][arithmetic]")
{
  using namespace ::stoneydsp::core::types::literals;

  // clang-format off
  ::stoneydsp::long_t a = 5_long_t; // 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0101

  STONEYDSP_REQUIRE ((a << 1) == 10); // Left shift: 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 1010
  STONEYDSP_REQUIRE ((a >> 1) == 2); // Right shift: 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0010
  // clang-format on
}

//==================================================================//comparison

STONEYDSP_TEST_CASE ("[core][types][long_t][comparison]",
                     "[core][types][long_t][comparison]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::long_t a = 5_long_t;
  ::stoneydsp::long_t b = 3_long_t;

  STONEYDSP_REQUIRE ((a == b) == false);
  STONEYDSP_REQUIRE ((a != b) == true);
  STONEYDSP_REQUIRE ((a > b) == true);
  STONEYDSP_REQUIRE ((a < b) == false);
  STONEYDSP_REQUIRE ((a >= b) == true);
  STONEYDSP_REQUIRE ((a <= b) == false);
}

//===============================================================//serialization

STONEYDSP_TEST_CASE ("[core][types][long_t][serialization]",
                     "[core][types][long_t][serialization]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::std::stringstream ss;
  ::stoneydsp::long_t originalValue = 42_long_t;
  ::stoneydsp::long_t deserializedValue;

  ss.write (reinterpret_cast<const char *> (&originalValue),
            sizeof (originalValue));
  ss.read (reinterpret_cast<char *> (&deserializedValue),
           sizeof (deserializedValue));

  STONEYDSP_REQUIRE (originalValue == deserializedValue);
}

//=======================================================//boundary_and_overflow

STONEYDSP_TEST_CASE ("[core][types][long_t][boundary][overflow]",
                     "[core][types][long_t][boundary][overflow]")
{
  using namespace ::stoneydsp::core::types::literals;

  #ifdef STONEYDSP_WINDOWS
  // Max value for 32-bit long
  ::stoneydsp::long_t a = 2147483647_long_t;
  #else
  // Max value for 64-bit long
  ::stoneydsp::long_t a = 9223372036854775807_long_t;
  #endif

  ::stoneydsp::long_t b = 1_long_t;

  STONEYDSP_REQUIRE (static_cast< ::stoneydsp::long_t> (a + b)
                     == ::std::numeric_limits< ::stoneydsp::long_t>::
                         min ()); // Check overflow wrap-around behaviour
}

//======================================================//boundary_and_underflow

STONEYDSP_TEST_CASE ("[core][types][long_t][boundary][underflow]",
                     "[core][types][long_t][boundary][underflow]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::long_t a = -9223372036854775807_long_t - 1_long_t;
  ::stoneydsp::long_t b = 1_long_t;
  STONEYDSP_REQUIRE (
      static_cast< ::stoneydsp::long_t> (a - b)
      == 9223372036854775807_long_t); // Check underflow wrap-around behavior
}

//===============================================================//compatibility

STONEYDSP_TEST_CASE ("[core][types][long_t][compatibility]",
                     "[core][types][long_t][compatibility]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::std::vector< ::stoneydsp::long_t> vec
      = { 5_long_t, 3_long_t, 4_long_t, 1_long_t, 2_long_t };

  // Use std::sort to sort the vector
  ::std::sort (vec.begin (), vec.end ());

  // Verify the vector is sorted
  STONEYDSP_REQUIRE (vec
                     == ::std::vector< ::stoneydsp::long_t>{
                         1_long_t, 2_long_t, 3_long_t, 4_long_t, 5_long_t });

  // Use std::accumulate to sum the elements
  ::stoneydsp::long_t sum = ::std::accumulate (vec.begin (), vec.end (),
                                               ::stoneydsp::long_t (0_long_t));

  // Verify the sum is correct
  STONEYDSP_REQUIRE (sum == 15);
}

//===================================================================//STONEYDSP_benchmark

// STONEYDSP_Benchmark for addition
STONEYDSP_TEST_CASE ("[core][types][long_t][benchmark][addition]",
                     "[core][types][long_t][benchmark][addition]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::long_t a = 1200_long_t;
  ::stoneydsp::long_t b = 3400_long_t;

  STONEYDSP_BENCHMARK ("Addition") { return a + b; };
}

// STONEYDSP_Benchmark for subtraction
STONEYDSP_TEST_CASE ("[core][types][long_t][benchmark][subtraction]",
                     "[core][types][long_t][benchmark][subtraction]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::long_t a = 3400_long_t;
  ::stoneydsp::long_t b = 1200_long_t;

  STONEYDSP_BENCHMARK ("Subtraction") { return a - b; };
}

// STONEYDSP_Benchmark for multiplication
STONEYDSP_TEST_CASE ("[core][types][long_t][benchmark][multiplication]",
                     "[core][types][long_t][benchmark][multiplication]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::long_t a = 1200_long_t;
  ::stoneydsp::long_t b = 2_long_t;

  STONEYDSP_BENCHMARK ("Multiplication") { return a * b; };
}

// STONEYDSP_Benchmark for division
STONEYDSP_TEST_CASE ("[core][types][long_t][benchmark][division]",
                     "[core][types][long_t][benchmark][division]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::long_t a = 1200_long_t;
  ::stoneydsp::long_t b = 2_long_t;

  STONEYDSP_BENCHMARK ("Division") { return a / b; };
}

// STONEYDSP_Benchmark for type conversion to int
STONEYDSP_TEST_CASE ("[core][types][long_t][benchmark][conversion][int]",
                     "[core][types][long_t][benchmark][conversion][int]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::long_t a = 1200_long_t;

  STONEYDSP_BENCHMARK ("Conversion to int") { return static_cast<int> (a); };
}

// STONEYDSP_Benchmark for type conversion to float
STONEYDSP_TEST_CASE ("[core][types][long_t][benchmark][conversion][float]",
                     "[core][types][long_t][benchmark][conversion][float]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::long_t a = 1200_long_t;

  STONEYDSP_BENCHMARK ("Conversion to float")
  {
    return static_cast<float> (a);
  };
}

//============================================================================//

#endif // defined(STONEYDSP_BUILD_TEST)

//=========================================================================//EOF
