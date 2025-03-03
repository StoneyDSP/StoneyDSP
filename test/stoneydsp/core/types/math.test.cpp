/**
 * @file math.test.cpp
 * @author StoneyDSP (nathanjhood@googlemail.com)
 * @copyright Copyright (c) 2025
 *
 */

//==============================================================================

#include "stoneydsp/core/system/types.h"

//==============================================================================

#if defined(STONEYDSP_BUILD_TEST) && defined(STONEYDSP_BUILD_CORE)

//==============================================================================

  #include "utils.test.hpp"

//==============================================================================

// Test tags provided by this file:
//
// type tags:
//
// [float_t]
// [double_t]
//
// size and alignment:
//
// [sizeof]
// [alignof]
//
// type traits:
//
// [type_traits]
// [is_signed]
// [is_trivially_copyable]
// [is_standard_layout]
//
// behavioural
//
// [precision]
// [rounding]
// [special_values]
// [arithmetic]
// [conversion]
// [endianness]
// [serialization]
// [boundary]
// [underflow]
// [overflow]
// [compatibility]

//======================================================================//sizeof

// Ensure types have the expected size across different architectures.

STONEYDSP_TEST_CASE ("[core][types][double_t][sizeof]",
                     "[core][types][double_t][sizeof]")
{
  STONEYDSP_REQUIRE (sizeof (::stoneydsp::double_t) == (unsigned long)8UL);
}

STONEYDSP_TEST_CASE ("[core][types][float_t][sizeof]",
                     "[core][types][float_t][sizeof]")
{
  STONEYDSP_REQUIRE (sizeof (::stoneydsp::float_t) == (unsigned long)4UL);
}

//=====================================================================//alignof

// Ensure types have the expected alignment across different architectures.

STONEYDSP_TEST_CASE ("[core][types][double_t][alignof]",
                     "[core][types][double_t][alignof]")
{
  STONEYDSP_REQUIRE (alignof (::stoneydsp::double_t) == (unsigned long)8UL);
}

STONEYDSP_TEST_CASE ("[core][types][float_t][alignof]",
                     "[core][types][float_t][alignof]")
{
  STONEYDSP_REQUIRE (alignof (::stoneydsp::float_t) == (unsigned long)4UL);
}

//=================================================================//type_traits

// Ensure types have the expected signedness across different architectures.

STONEYDSP_TEST_CASE ("[core][types][double_t][type_traits][is_signed]",
                     "[core][types][double_t][type_traits][is_signed]")
{
  STONEYDSP_REQUIRE (::std::is_signed< ::stoneydsp::double_t>::value);
}

STONEYDSP_TEST_CASE ("[core][types][float_t][type_traits][is_signed]",
                     "[core][types][float_t][type_traits][is_signed]")
{
  STONEYDSP_REQUIRE (::std::is_signed< ::stoneydsp::float_t>::value);
}

//=======================================================//is_trivially_copyable

STONEYDSP_TEST_CASE (
    "[core][types][double_t][type_traits][is_trivially_copyable]",
    "[core][types][double_t][type_traits][is_trivially_copyable]")
{
  STONEYDSP_REQUIRE (
      ::std::is_trivially_copyable< ::stoneydsp::double_t>::value);
}

STONEYDSP_TEST_CASE (
    "[core][types][float_t][type_traits][is_trivially_copyable]",
    "[core][types][float_t][type_traits][is_trivially_copyable]")
{
  STONEYDSP_REQUIRE (
      ::std::is_trivially_copyable< ::stoneydsp::float_t>::value);
}

//==========================================================//is_standard_layout

STONEYDSP_TEST_CASE (
    "[core][types][double_t][type_traits][is_standard_layout]",
    "[core][types][double_t][type_traits][is_standard_layout]")
{
  STONEYDSP_REQUIRE (::std::is_standard_layout< ::stoneydsp::double_t>::value);
}

STONEYDSP_TEST_CASE ("[core][types][float_t][type_traits][is_standard_layout]",
                     "[core][types][float_t][type_traits][is_standard_layout]")
{
  STONEYDSP_REQUIRE (::std::is_standard_layout< ::stoneydsp::float_t>::value);
}

//==============================================================//numeric_limits

STONEYDSP_TEST_CASE ("[core][types][double_t][numeric_limits]",
                     "[core][types][double_t][numeric_limits]")
{
  STONEYDSP_REQUIRE (::std::numeric_limits< ::stoneydsp::double_t>::min ()
                     == 2.2250738585072014e-308);
  STONEYDSP_REQUIRE (::std::numeric_limits< ::stoneydsp::double_t>::max ()
                     == 1.7976931348623158e+308);
  STONEYDSP_REQUIRE (::std::numeric_limits< ::stoneydsp::double_t>::epsilon ()
                     == 2.2204460492503131e-16);
  STONEYDSP_REQUIRE (::std::numeric_limits< ::stoneydsp::double_t>::lowest ()
                     == -1.7976931348623158e+308);
}

STONEYDSP_TEST_CASE ("[core][types][float_t][numeric_limits]",
                     "[core][types][float_t][numeric_limits]")
{
  STONEYDSP_REQUIRE (::std::numeric_limits< ::stoneydsp::float_t>::min ()
                     == 1.175494351e-38F);
  STONEYDSP_REQUIRE (::std::numeric_limits< ::stoneydsp::float_t>::max ()
                     == 3.402823466e+38F);
  STONEYDSP_REQUIRE (::std::numeric_limits< ::stoneydsp::float_t>::epsilon ()
                     == 1.192092896e-07F);
  STONEYDSP_REQUIRE (::std::numeric_limits< ::stoneydsp::float_t>::lowest ()
                     == -3.402823466e+38F);
}

//===================================================================//precision

STONEYDSP_TEST_CASE ("[core][types][double_t][precision]",
                     "[core][types][double_t][precision]")
{
  ::stoneydsp::double_t a = 0.1;
  ::stoneydsp::double_t b = 0.1;
  STONEYDSP_REQUIRE_THAT (a, ::Catch::Matchers::WithinRel (b, 1e-12));
}

STONEYDSP_TEST_CASE ("[core][types][float_t][precision]",
                     "[core][types][float_t][precision]")
{
  ::stoneydsp::float_t a = 0.1f;
  ::stoneydsp::float_t b = 0.1f;
  STONEYDSP_REQUIRE_THAT (a, ::Catch::Matchers::WithinRel (b, 1e-6f));
}

//====================================================================//rounding

STONEYDSP_TEST_CASE ("[core][types][double_t][rounding]",
                     "[core][types][double_t][rounding]")
{
  ::stoneydsp::double_t a = 1.5;
  ::stoneydsp::double_t b = ::std::round (a);
  STONEYDSP_REQUIRE_THAT (b, ::Catch::Matchers::WithinRel (2.0, 1e-12));
}

STONEYDSP_TEST_CASE ("[core][types][float_t][rounding]",
                     "[core][types][float_t][rounding]")
{
  ::stoneydsp::float_t a = 1.5f;
  ::stoneydsp::float_t b = ::std::round (a);
  STONEYDSP_REQUIRE_THAT (b, ::Catch::Matchers::WithinRel (2.0f, 1e-6f));
}

//==============================================================//special_values

STONEYDSP_TEST_CASE ("[core][types][double_t][special_values]",
                     "[core][types][double_t][special_values]")
{
  ::stoneydsp::double_t nan
      = ::std::numeric_limits< ::stoneydsp::double_t>::quiet_NaN ();
  ::stoneydsp::double_t inf
      = ::std::numeric_limits< ::stoneydsp::double_t>::infinity ();
  STONEYDSP_REQUIRE (::std::isnan (nan));
  STONEYDSP_REQUIRE (::std::isinf (inf));
}

STONEYDSP_TEST_CASE ("[core][types][float_t][special_values]",
                     "[core][types][float_t][special_values]")
{
  ::stoneydsp::float_t nan
      = ::std::numeric_limits< ::stoneydsp::float_t>::quiet_NaN ();
  ::stoneydsp::float_t inf
      = ::std::numeric_limits< ::stoneydsp::float_t>::infinity ();
  STONEYDSP_REQUIRE (::std::isnan (nan));
  STONEYDSP_REQUIRE (::std::isinf (inf));
}

//==================================================================//arithmetic

STONEYDSP_TEST_CASE ("[core][types][double_t][arithmetic]",
                     "[core][types][double_t][arithmetic]")
{
  ::stoneydsp::double_t a = 1.5;
  ::stoneydsp::double_t b = 2.0;
  STONEYDSP_REQUIRE_THAT (a + b, ::Catch::Matchers::WithinRel (3.5, 1e-12));
  STONEYDSP_REQUIRE_THAT (a - b, ::Catch::Matchers::WithinRel (-0.5, 1e-12));
  STONEYDSP_REQUIRE_THAT (a * b, ::Catch::Matchers::WithinRel (3.0, 1e-12));
  STONEYDSP_REQUIRE_THAT (a / b, ::Catch::Matchers::WithinRel (0.75, 1e-12));
}

STONEYDSP_TEST_CASE ("[core][types][float_t][arithmetic]",
                     "[core][types][float_t][arithmetic]")
{
  ::stoneydsp::float_t a = 1.5f;
  ::stoneydsp::float_t b = 2.0f;
  STONEYDSP_REQUIRE_THAT (a + b, ::Catch::Matchers::WithinRel (3.5f, 1e-6f));
  STONEYDSP_REQUIRE_THAT (a - b, ::Catch::Matchers::WithinRel (-0.5f, 1e-6f));
  STONEYDSP_REQUIRE_THAT (a * b, ::Catch::Matchers::WithinRel (3.0f, 1e-6f));
  STONEYDSP_REQUIRE_THAT (a / b, ::Catch::Matchers::WithinRel (0.75f, 1e-6f));
}

//==================================================================//conversion

STONEYDSP_TEST_CASE ("[core][types][double_t][conversion][float]",
                     "[core][types][double_t][conversion][float]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::double_t a = 0.1_double_t;
  float b = static_cast<float> (a);
  STONEYDSP_REQUIRE_THAT (b, ::Catch::Matchers::WithinRel (0.1f, 1e-6f));
}

STONEYDSP_TEST_CASE ("[core][types][float_t][conversion][double]",
                     "[core][types][float_t][conversion][double]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::float_t a = 0.1_float_t;
  double b = static_cast<double> (a);
  STONEYDSP_REQUIRE_THAT (b, ::Catch::Matchers::WithinRel (0.1, 1e-6));
}

//===============================================================//serialization

STONEYDSP_TEST_CASE ("[core][types][float_t][serialization]",
                     "[core][types][float_t][serialization]")
{
  ::std::stringstream ss;
  ::stoneydsp::float_t originalValue = 123.456f;
  ::stoneydsp::float_t deserializedValue;

  ss.write (reinterpret_cast<const char *> (&originalValue),
            sizeof (originalValue));
  ss.read (reinterpret_cast<char *> (&deserializedValue),
           sizeof (deserializedValue));

  STONEYDSP_REQUIRE_THAT (
      originalValue, ::Catch::Matchers::WithinRel (deserializedValue, 1e-6f));
}

STONEYDSP_TEST_CASE ("[core][types][double_t][serialization]",
                     "[core][types][double_t][serialization]")
{
  ::std::stringstream ss;
  ::stoneydsp::double_t originalValue = 123.456789;
  ::stoneydsp::double_t deserializedValue;

  ss.write (reinterpret_cast<const char *> (&originalValue),
            sizeof (originalValue));
  ss.read (reinterpret_cast<char *> (&deserializedValue),
           sizeof (deserializedValue));

  STONEYDSP_REQUIRE_THAT (
      originalValue, ::Catch::Matchers::WithinRel (deserializedValue, 1e-12));
}

//==================================================================//endianness

STONEYDSP_TEST_CASE ("[core][types][double_t][endianness][arbitrary_value]",
                     "[core][types][double_t][endianness][arbitrary_value]")
{
  ::stoneydsp::double_t value = 123.456;
  ::std::uint8_t *bytePtr = reinterpret_cast< ::std::uint8_t *> (&value);

  if (bytePtr[0]
      == reinterpret_cast< ::std::uint8_t *> (
          &value)[sizeof (::stoneydsp::double_t) - 1])
    {
      STONEYDSP_REQUIRE (true); // Little-endian
    }
  else if (bytePtr[0] == reinterpret_cast< ::std::uint8_t *> (&value)[0])
    {
      STONEYDSP_REQUIRE (true); // Big-endian
    }
  else
    {
      STONEYDSP_REQUIRE (false); // Unknown endianness
    }
}

STONEYDSP_TEST_CASE ("[core][types][double_t][endianness][specific_value]",
                     "[core][types][double_t][endianness][specific_value]")
{
  ::stoneydsp::double_t value = 1.0;
  unsigned char bytes[sizeof (::stoneydsp::double_t)];
  std::memcpy (bytes, &value, sizeof (value));

  if (bytes[0] == 0x3f && bytes[1] == 0xf0 && bytes[2] == 0x00
      && bytes[3] == 0x00 && bytes[4] == 0x00 && bytes[5] == 0x00
      && bytes[6] == 0x00 && bytes[7] == 0x00)
    {
      // Little-endian representation of 1.0
      STONEYDSP_REQUIRE (true);
    }
  else if (bytes[0] == 0x00 && bytes[1] == 0x00 && bytes[2] == 0x00
           && bytes[3] == 0x00 && bytes[4] == 0x00 && bytes[5] == 0x00
           && bytes[6] == 0xf0 && bytes[7] == 0x3f)
    {
      // Big-endian representation of 1.0
      STONEYDSP_REQUIRE (true);
    }
  else
    {
      STONEYDSP_REQUIRE (false); // Unexpected endianness
    }
}

//==================================================================//endianness

STONEYDSP_TEST_CASE ("[core][types][float_t][endianness][arbitrary_value]",
                     "[core][types][float_t][endianness][arbitrary_value]")
{
  ::stoneydsp::float_t value = 123.456f;
  ::std::uint8_t *bytePtr = reinterpret_cast< ::std::uint8_t *> (&value);

  if (bytePtr[0]
      == reinterpret_cast< ::std::uint8_t *> (
          &value)[sizeof (::stoneydsp::float_t) - 1])
    {
      STONEYDSP_REQUIRE (true); // Little-endian
    }
  else if (bytePtr[0] == reinterpret_cast< ::std::uint8_t *> (&value)[0])
    {
      STONEYDSP_REQUIRE (true); // Big-endian
    }
  else
    {
      STONEYDSP_REQUIRE (false); // Unknown endianness
    }
}

//==================================================================//endianness

STONEYDSP_TEST_CASE ("[core][types][float_t][endianness][specific_value]",
                     "[core][types][float_t][endianness][specific_value]")
{
  ::stoneydsp::float_t value = 1.0f;
  unsigned char bytes[sizeof (::stoneydsp::float_t)];
  std::memcpy (bytes, &value, sizeof (value));

  if (bytes[0] == 0x3f && bytes[1] == 0x80 && bytes[2] == 0x00
      && bytes[3] == 0x00)
    {
      // Little-endian representation of 1.0f
      STONEYDSP_REQUIRE (true);
    }
  else if (bytes[0] == 0x00 && bytes[1] == 0x00 && bytes[2] == 0x80
           && bytes[3] == 0x3f)
    {
      // Big-endian representation of 1.0f
      STONEYDSP_REQUIRE (true);
    }
  else
    {
      STONEYDSP_REQUIRE (false); // Unexpected endianness
    }
}

//====================================================================//boundary

STONEYDSP_TEST_CASE ("[core][types][double_t][boundary]",
                     "[core][types][double_t][boundary]")
{
  ::stoneydsp::double_t max_val
      = std::numeric_limits< ::stoneydsp::double_t>::max ();
  ::stoneydsp::double_t min_val
      = std::numeric_limits< ::stoneydsp::double_t>::min ();
  STONEYDSP_REQUIRE (std::isfinite (max_val));
  STONEYDSP_REQUIRE (std::isfinite (min_val));
}

STONEYDSP_TEST_CASE ("[core][types][float_t][boundary]",
                     "[core][types][float_t][boundary]")
{
  ::stoneydsp::float_t max_val
      = std::numeric_limits< ::stoneydsp::float_t>::max ();
  ::stoneydsp::float_t min_val
      = std::numeric_limits< ::stoneydsp::float_t>::min ();
  STONEYDSP_REQUIRE (std::isfinite (max_val));
  STONEYDSP_REQUIRE (std::isfinite (min_val));
}

//====================================================================//overflow

STONEYDSP_TEST_CASE ("[core][types][double_t][overflow]",
                     "[core][types][double_t][overflow]")
{
  ::stoneydsp::double_t max_val
      = std::numeric_limits< ::stoneydsp::double_t>::max ();
  ::stoneydsp::double_t overflow_val = max_val * 2.0;
  STONEYDSP_REQUIRE (std::isinf (overflow_val)); // Check for positive overflow
}

STONEYDSP_TEST_CASE ("[core][types][float_t][overflow]",
                     "[core][types][float_t][overflow]")
{
  ::stoneydsp::float_t max_val
      = std::numeric_limits< ::stoneydsp::float_t>::max ();
  ::stoneydsp::float_t overflow_val = max_val * 2.0f;
  STONEYDSP_REQUIRE (std::isinf (overflow_val)); // Check for positive overflow
}

// //===================================================================//underflow

// STONEYDSP_TEST_CASE ("Underflow behavior for stoneydsp::double_t",
//            "[underflow][boundary][double_t]")
// {
//   ::stoneydsp::double_t min_val
//       = std::numeric_limits< ::stoneydsp::double_t>::min ();
//   ::stoneydsp::double_t underflow_val = min_val / 2.0;
//   STONEYDSP_REQUIRE_THAT (underflow_val, ::Catch::Matchers::WithinAbs (
//                                    0.0, 0.0)); // Check for underflow to
//                                    zero
// }

// STONEYDSP_TEST_CASE ("Underflow behavior for stoneydsp::float_t",
//            "[underflow][boundary][float_t]")
// {
//   ::stoneydsp::float_t min_val
//       = std::numeric_limits< ::stoneydsp::float_t>::min ();
//   ::stoneydsp::float_t underflow_val = min_val / 2.0f;
//   STONEYDSP_REQUIRE_THAT (underflow_val, ::Catch::Matchers::WithinAbs (
//                                    0.0f, 0.0f)); // Check for underflow to
//                                    zero
// }

//===============================================================//compatibility

STONEYDSP_TEST_CASE ("[core][types][float_t][compatibility]",
                     "[core][types][float_t][compatibility]")
{
  ::std::vector< ::stoneydsp::float_t> vec = { 5.1f, 3.2f, 4.3f, 1.4f, 2.5f };

  // Use std::sort to sort the vector
  ::std::sort (vec.begin (), vec.end ());

  // Verify the vector is sorted
  STONEYDSP_REQUIRE (
      vec
      == ::std::vector< ::stoneydsp::float_t>{ 1.4f, 2.5f, 3.2f, 4.3f, 5.1f });

  // Use std::accumulate to sum the elements
  ::stoneydsp::float_t sum = ::std::accumulate (vec.begin (), vec.end (),
                                                ::stoneydsp::float_t (0.0f));

  // Verify the sum is correct
  STONEYDSP_REQUIRE_THAT (sum, ::Catch::Matchers::WithinRel (16.5f, 0.001f));
}

STONEYDSP_TEST_CASE ("[core][types][double_t][compatibility]",
                     "[core][types][double_t][compatibility]")
{
  ::std::vector< ::stoneydsp::double_t> vec = { 5.1, 3.2, 4.3, 1.4, 2.5 };

  // Use std::sort to sort the vector
  ::std::sort (vec.begin (), vec.end ());

  // Verify the vector is sorted
  STONEYDSP_REQUIRE (
      vec == std::vector< ::stoneydsp::double_t>{ 1.4, 2.5, 3.2, 4.3, 5.1 });

  // Use std::accumulate to sum the elements
  ::stoneydsp::double_t sum = std::accumulate (vec.begin (), vec.end (),
                                               ::stoneydsp::double_t (0.0));

  // Verify the sum is correct
  STONEYDSP_REQUIRE_THAT (sum, ::Catch::Matchers::WithinRel (16.5, 0.001));
}

//===================================================================//benchmark

// Benchmark for addition
STONEYDSP_TEST_CASE ("[core][types][float_t][benchmark][addition]",
                     "[core][types][float_t][benchmark][addition]")
{
  ::stoneydsp::float_t a = 123.456f;
  ::stoneydsp::float_t b = 987.654f;

  STONEYDSP_BENCHMARK ("Addition") { return a + b; };
}

// Benchmark for subtraction
STONEYDSP_TEST_CASE ("[core][types][float_t][benchmark][subtraction]",
                     "[core][types][float_t][benchmark][subtraction]")
{
  ::stoneydsp::float_t a = 987.654f;
  ::stoneydsp::float_t b = 123.456f;

  STONEYDSP_BENCHMARK ("Subtraction") { return a - b; };
}

// Benchmark for multiplication
STONEYDSP_TEST_CASE ("[core][types][float_t][benchmark][multiplication]",
                     "[core][types][float_t][benchmark][multiplication]")
{
  ::stoneydsp::float_t a = 123.456f;
  ::stoneydsp::float_t b = 2.0f;

  STONEYDSP_BENCHMARK ("Multiplication") { return a * b; };
}

// Benchmark for division
STONEYDSP_TEST_CASE ("[core][types][float_t][benchmark][division]",
                     "[core][types][float_t][benchmark][division]")
{
  ::stoneydsp::float_t a = 123.456f;
  ::stoneydsp::float_t b = 2.0f;

  STONEYDSP_BENCHMARK ("Division") { return a / b; };
}

// Benchmark for type conversion to int
STONEYDSP_TEST_CASE ("[core][types][float_t][benchmark][conversion][int]",
                     "[core][types][float_t][benchmark][conversion][int]")
{
  ::stoneydsp::float_t a = 123.456f;

  STONEYDSP_BENCHMARK ("Conversion to int") { return static_cast<int> (a); };
}

// Benchmark for type conversion to double
STONEYDSP_TEST_CASE ("[core][types][float_t][benchmark][conversion][double]",
                     "[core][types][float_t][benchmark][conversion][double]")
{
  ::stoneydsp::float_t a = 123.456f;

  STONEYDSP_BENCHMARK ("Conversion to double")
  {
    return static_cast<double> (a);
  };
}

// Benchmark for addition
STONEYDSP_TEST_CASE ("[core][types][double_t][benchmark][addition]",
                     "[core][types][double_t][benchmark][addition]")
{
  ::stoneydsp::double_t a = 123.456;
  ::stoneydsp::double_t b = 987.654;

  STONEYDSP_BENCHMARK ("Addition") { return a + b; };
}

// Benchmark for subtraction
STONEYDSP_TEST_CASE ("[core][types][double_t][benchmark][subtraction]",
                     "[core][types][double_t][benchmark][subtraction]")
{
  ::stoneydsp::double_t a = 987.654;
  ::stoneydsp::double_t b = 123.456;

  STONEYDSP_BENCHMARK ("Subtraction") { return a - b; };
}

// Benchmark for multiplication
STONEYDSP_TEST_CASE ("[core][types][double_t][benchmark][multiplication]",
                     "[core][types][double_t][benchmark][multiplication]")
{
  ::stoneydsp::double_t a = 123.456;
  ::stoneydsp::double_t b = 2.0;

  STONEYDSP_BENCHMARK ("Multiplication") { return a * b; };
}

// Benchmark for division
STONEYDSP_TEST_CASE ("[core][types][double_t][benchmark][division]",
                     "[core][types][double_t][benchmark][division]")
{
  ::stoneydsp::double_t a = 123.456;
  ::stoneydsp::double_t b = 2.0;

  STONEYDSP_BENCHMARK ("Division") { return a / b; };
}

// Benchmark for type conversion to int
STONEYDSP_TEST_CASE ("[core][types][double_t][benchmark][conversion][int]",
                     "[core][types][double_t][benchmark][conversion][int]")
{
  ::stoneydsp::double_t a = 123.456;

  STONEYDSP_BENCHMARK ("Conversion to int") { return static_cast<int> (a); };
}

// Benchmark for type conversion to float
STONEYDSP_TEST_CASE ("[core][types][double_t][benchmark][conversion][float]",
                     "[core][types][double_t][benchmark][conversion][float]")
{
  ::stoneydsp::double_t a = 123.456;

  STONEYDSP_BENCHMARK ("Conversion to float")
  {
    return static_cast<float> (a);
  };
}

//============================================================================//

#endif // defined(STONEYDSP_BUILD_TEST)

//=========================================================================//EOF
