/**
 * @file uint64.test.cpp
 * @brief Test suite for stoneydsp::uint64_t
 * @copyright Copyright (c) 2025
 *
 */

//==============================================================================

#include <stoneydsp/core/system/types.h>

//==============================================================================

#if defined(STONEYDSP_BUILD_TEST) && defined(STONEYDSP_BUILD_CORE)

//==============================================================================

  #include "../../../utils.test.hpp"

  #if defined(STONEYDSP_WINDOWS) || defined(STONEYDSP_32BIT)

    #include <stoneydsp/core/types/ullong.h> // for numerical_limits<llong_t>

  #elif (defined(STONEYDSP_LINUX) || defined(STONEYDSP_MAC))                  \
      && (defined(STONEYDSP_64BIT) || defined(STONEYDSP_ARM))

    #include <stoneydsp/core/types/ulong.h> // for numerical_limits<long_t>

  #else

    #error unable to determine a suitable template for numerical_limits<uint64_t>

  #endif

//======================================================================//sizeof

STONEYDSP_TEST_CASE ("[core][types][uint64_t][sizeof]",
                     "[core][types][uint64_t][sizeof]")
{
  STONEYDSP_REQUIRE (sizeof (::stoneydsp::uint64_t) == 8UL);
}

//=====================================================================//alignof

STONEYDSP_TEST_CASE ("[core][types][uint64_t][alignof]",
                     "[core][types][uint64_t][alignof]")
{
  STONEYDSP_REQUIRE (alignof (::stoneydsp::uint64_t) == 8UL);
}

//=================================================================//type_traits

STONEYDSP_TEST_CASE ("[core][types][uint64_t][type_traits][is_integral]",
                     "[core][types][uint64_t][type_traits][is_integral]")
{
  STONEYDSP_REQUIRE (::std::is_integral< ::stoneydsp::uint64_t>::value);
}

STONEYDSP_TEST_CASE ("[core][types][uint64_t][type_traits][is_unsigned]",
                     "[core][types][uint64_t][type_traits][is_unsigned]")
{
  STONEYDSP_REQUIRE (::std::is_unsigned< ::stoneydsp::uint64_t>::value);
}

STONEYDSP_TEST_CASE ("[core][types][uint64_t][type_traits][is_arithmetic]",
                     "[core][types][uint64_t][type_traits][is_arithmetic]")
{
  STONEYDSP_REQUIRE (::std::is_arithmetic< ::stoneydsp::uint64_t>::value);
}

STONEYDSP_TEST_CASE ("[core][types][uint64_t][type_traits][is_pointer]",
                     "[core][types][uint64_t][type_traits][is_pointer]")
{
  STONEYDSP_REQUIRE (!::std::is_pointer< ::stoneydsp::uint64_t>::value);
}

STONEYDSP_TEST_CASE ("[core][types][uint64_t][type_traits][is_const]",
                     "[core][types][uint64_t][type_traits][is_const]")
{
  STONEYDSP_REQUIRE (!::std::is_const< ::stoneydsp::uint64_t>::value);
}

STONEYDSP_TEST_CASE ("[core][types][uint64_t][type_traits][is_empty]",
                     "[core][types][uint64_t][type_traits][is_empty]")
{
  STONEYDSP_REQUIRE (!::std::is_empty< ::stoneydsp::uint64_t>::value);
}

STONEYDSP_TEST_CASE (
    "[core][types][uint64_t][type_traits][is_trivially_copyable]",
    "[core][types][uint64_t][type_traits][is_trivially_copyable]")
{
  STONEYDSP_REQUIRE (
      ::std::is_trivially_copyable< ::stoneydsp::uint64_t>::value);
}

STONEYDSP_TEST_CASE (
    "[core][types][uint64_t][type_traits][is_standard_layout]",
    "[core][types][uint64_t][type_traits][is_standard_layout]")
{
  STONEYDSP_REQUIRE (::std::is_standard_layout< ::stoneydsp::uint64_t>::value);
}

//==============================================================//numeric_limits

STONEYDSP_TEST_CASE ("[core][types][uint64_t][numeric_limits]",
                     "[core][types][uint64_t][numeric_limits]")
{
  // { 0U }
  STONEYDSP_REQUIRE (
      ::stoneydsp::numeric_limits< ::stoneydsp::uint64_t>::min ()
      == ::std::numeric_limits< ::stoneydsp::uint64_t>::min ());

  // { 18446744073709551615ULL }
  STONEYDSP_REQUIRE (
      ::stoneydsp::numeric_limits< ::stoneydsp::uint64_t>::max ()
      == ::std::numeric_limits< ::stoneydsp::uint64_t>::max ());

  // { 0U }
  STONEYDSP_REQUIRE (
      ::stoneydsp::numeric_limits< ::stoneydsp::uint64_t>::lowest ()
      == ::std::numeric_limits< ::stoneydsp::uint64_t>::lowest ());
}

//==============================================================//special_values

STONEYDSP_TEST_CASE ("[core][types][uint64_t][special_values]",
                     "[core][types][uint64_t][special_values]")
{
  ::stoneydsp::uint64_t min_val
      = ::std::numeric_limits< ::stoneydsp::uint64_t>::min ();
  ::stoneydsp::uint64_t max_val
      = ::std::numeric_limits< ::stoneydsp::uint64_t>::max ();
  STONEYDSP_REQUIRE (min_val == 0UL); // Minimum value for uint64_t
  STONEYDSP_REQUIRE (max_val
                     == 18446744073709551615ULL); // Maximum value for uint64_t
}

//==================================================================//endianness

STONEYDSP_TEST_CASE ("[core][types][uint64_t][endianness]",
                     "[core][types][uint64_t][endianness]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::uint64_t value = 0x123456789ABCDEF0_uint64_t;
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

STONEYDSP_TEST_CASE ("[core][types][uint64_t][rounding]",
                     "[core][types][uint64_t][rounding]")
{
  float a = 1.5f;
  ::stoneydsp::uint64_t b
      = static_cast< ::stoneydsp::uint64_t> (::std::round (a));
  STONEYDSP_REQUIRE (
      b == 2); // 1.5 rounded to nearest integer and cast to uint64_t
}

//==================================================================//arithmetic

STONEYDSP_TEST_CASE ("[core][types][uint64_t][arithmetic]",
                     "[core][types][uint64_t][arithmetic]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::uint64_t a = 1500000000000000000_uint64_t;
  ::stoneydsp::uint64_t b = 2_uint64_t;
  STONEYDSP_REQUIRE (a + b == 1500000000000000002ULL); // Addition
  STONEYDSP_REQUIRE (a - b == 1499999999999999998ULL); // Subtraction
  STONEYDSP_REQUIRE (a * b == 3000000000000000000ULL); // Multiplication
  STONEYDSP_REQUIRE (b / a == 0);                      // Division
  STONEYDSP_REQUIRE (b % a == 2ULL);                   // Modulo
}

//=====================================================================//bitwise

STONEYDSP_TEST_CASE ("[core][types][uint64_t][bitwise][logic]",
                     "[core][types][uint64_t][bitwise][logic]")
{
  using namespace ::stoneydsp::core::types::literals;

  // clang-format off
  ::stoneydsp::uint64_t a = 5_uint64_t; // 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0101
  ::stoneydsp::uint64_t b = 3_uint64_t; // 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0011

  STONEYDSP_REQUIRE ((a & b) == 1); // AND: 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0001
  STONEYDSP_REQUIRE ((a | b) == 7); // OR:  0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0111
  STONEYDSP_REQUIRE ((a ^ b) == 6); // XOR: 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0110
  STONEYDSP_REQUIRE ((~a & 0xFFFFFFFFFFFFFFFFULL)
      == 18446744073709551610ULL); // NOT: 1111 1111 1111 1111 1111 1111 1111 1111 1111 1111 1111 1111 1111 1111 1111 1010 (considering uint64_t wrap-around)
  // clang-format on
}

STONEYDSP_TEST_CASE ("[core][types][uint64_t][bitwise][arithmetic]",
                     "[core][types][uint64_t][bitwise][arithmetic]")
{
  using namespace ::stoneydsp::core::types::literals;

  // clang-format off
  ::stoneydsp::uint64_t a = 5_uint64_t; // 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0101

	STONEYDSP_REQUIRE ((a << 1) == 10);  // Left shift: 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 1010
  STONEYDSP_REQUIRE ((a >> 1) == 2);   // Right shift: 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0010
  // clang-format on
}

//===============================================================//comparison

STONEYDSP_TEST_CASE ("[core][types][uint64_t][comparison]",
                     "[core][types][uint64_t][comparison]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::uint64_t a = 5_uint64_t;
  ::stoneydsp::uint64_t b = 3_uint64_t;

  STONEYDSP_REQUIRE ((a == b) == false);
  STONEYDSP_REQUIRE ((a != b) == true);
  STONEYDSP_REQUIRE ((a > b) == true);
  STONEYDSP_REQUIRE ((a < b) == false);
  STONEYDSP_REQUIRE ((a >= b) == true);
  STONEYDSP_REQUIRE ((a <= b) == false);
}

//===============================================================//serialization

STONEYDSP_TEST_CASE ("[core][types][uint64_t][serialization]",
                     "[core][types][uint64_t][serialization]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::std::stringstream ss;
  ::stoneydsp::uint64_t originalValue = 42_uint64_t;
  ::stoneydsp::uint64_t deserializedValue;

  ss.write (reinterpret_cast<const char *> (&originalValue),
            sizeof (originalValue));
  ss.read (reinterpret_cast<char *> (&deserializedValue),
           sizeof (deserializedValue));

  STONEYDSP_REQUIRE (originalValue == deserializedValue);
}

//=======================================================//boundary_and_overflow

STONEYDSP_TEST_CASE ("[core][types][uint64_t][boundary][overflow]",
                     "[core][types][uint64_t][boundary][overflow]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::uint64_t a = 18446744073709551615_uint64_t;
  ::stoneydsp::uint64_t b = 1_uint64_t;

  STONEYDSP_REQUIRE (static_cast< ::stoneydsp::uint64_t> (a + b)
                     == 0); // Check overflow wrap-around behaviour
}

//======================================================//boundary_and_underflow

STONEYDSP_TEST_CASE ("[core][types][uint64_t][boundary][underflow]",
                     "[core][types][uint64_t][boundary][underflow]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::uint64_t a = 0_uint64_t;
  ::stoneydsp::uint64_t b = 1_uint64_t;

  STONEYDSP_REQUIRE (
      static_cast< ::stoneydsp::uint64_t> (a - b)
      == 18446744073709551615ULL); // Check underflow wrap-around behavior
}

//===============================================================//compatibility

STONEYDSP_TEST_CASE ("[core][types][uint64_t][compatibility]",
                     "[core][types][uint64_t][compatibility]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::std::vector< ::stoneydsp::uint64_t> vec
      = { 5_uint64_t, 3_uint64_t, 4_uint64_t, 1_uint64_t, 2_uint64_t };

  // Use std::sort to sort the vector
  ::std::sort (vec.begin (), vec.end ());

  // Verify the vector is sorted
  STONEYDSP_REQUIRE (
      vec
      == ::std::vector< ::stoneydsp::uint64_t>{
          1_uint64_t, 2_uint64_t, 3_uint64_t, 4_uint64_t, 5_uint64_t });

  // Use std::accumulate to sum the elements
  ::stoneydsp::uint64_t sum = ::std::accumulate (
      vec.begin (), vec.end (), ::stoneydsp::uint64_t (0_uint64_t));

  // Verify the sum is correct
  STONEYDSP_REQUIRE (sum == 15);
}

//===================================================================//benchmark

// Benchmark for addition
STONEYDSP_TEST_CASE ("[core][types][uint64_t][benchmark][addition]",
                     "[core][types][uint64_t][benchmark][addition]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::uint64_t a = 1200_uint64_t;
  ::stoneydsp::uint64_t b = 3400_uint64_t;

  STONEYDSP_BENCHMARK ("Addition") { return a + b; };
}

// Benchmark for subtraction
STONEYDSP_TEST_CASE ("[core][types][uint64_t][benchmark][subtraction]",
                     "[core][types][uint64_t][benchmark][subtraction]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::uint64_t a = 3400_uint64_t;
  ::stoneydsp::uint64_t b = 1200_uint64_t;

  STONEYDSP_BENCHMARK ("Subtraction") { return a - b; };
}

// Benchmark for multiplication
STONEYDSP_TEST_CASE ("[core][types][uint64_t][benchmark][multiplication]",
                     "[core][types][uint64_t][benchmark][multiplication]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::uint64_t a = 1200_uint64_t;
  ::stoneydsp::uint64_t b = 2_uint64_t;

  STONEYDSP_BENCHMARK ("Multiplication") { return a * b; };
}

// Benchmark for division
STONEYDSP_TEST_CASE ("[core][types][uint64_t][benchmark][division]",
                     "[core][types][uint64_t][benchmark][division]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::uint64_t a = 1200_uint64_t;
  ::stoneydsp::uint64_t b = 2_uint64_t;

  STONEYDSP_BENCHMARK ("Division") { return a / b; };
}

// Benchmark for type conversion to int
STONEYDSP_TEST_CASE ("[core][types][uint64_t][benchmark][conversion][int]",
                     "[core][types][uint64_t][benchmark][conversion][int]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::uint64_t a = 1200_uint64_t;

  STONEYDSP_BENCHMARK ("Conversion to int") { return static_cast<int> (a); };
}

// Benchmark for type conversion to float
STONEYDSP_TEST_CASE ("[core][types][uint64_t][benchmark][conversion][float]",
                     "[core][types][uint64_t][benchmark][conversion][float]")
{
  using namespace ::stoneydsp::core::types::literals;

  ::stoneydsp::uint64_t a = 1200_uint64_t;

  STONEYDSP_BENCHMARK ("Conversion to float")
  {
    return static_cast<float> (a);
  };
}

//============================================================================//

#endif // defined(STONEYDSP_BUILD_TEST)

//=========================================================================//EOF
