/**
 * @file platform.test.cpp
 * @author StoneyDSP (nathanjhood@googlemail.com)
 * @copyright Copyright (c) 2025
 *
 */

//==============================================================================

#include <stoneydsp/core/system/platform.h>

//==============================================================================

#if defined(STONEYDSP_BUILD_TEST) && defined(STONEYDSP_BUILD_CORE)

//==============================================================================

  #include "../../../utils.test.hpp"

//====================================================================//platform

STONEYDSP_TEST_CASE ("[core][system][platform]", "[core][system][platform]")
{
  bool result = false;

  #if defined(STONEYDSP_WINDOWS)
  result = true;
  #elif defined(STONEYDSP_LINUX)
  result = true;
  #elif defined(STONEYDSP_MAC)
  result = true;
  #endif

  STONEYDSP_REQUIRE (result == true);
}

//================================================================//architecture

STONEYDSP_TEST_CASE ("[core][system][architecture]",
                     "[core][system][architecture]")
{
  bool result = false;

  #if defined(STONEYDSP_32BIT)
  result = true;
  #elif defined(STONEYDSP_64BIT)
  result = true;
  #endif

  STONEYDSP_REQUIRE (result == true);
}

//=========================================================================//cpu

STONEYDSP_TEST_CASE ("[core][system][cpu]", "[core][system][cpu]")
{
  bool result = false;

  #if defined(STONEYDSP_INTEL)
  result = true;
  #elif defined(STONEYDSP_ARM)
  result = true;
  #endif

  STONEYDSP_REQUIRE (result == true);
}

//==================================================================//endianness

STONEYDSP_TEST_CASE ("[core][system][endianness]",
                     "[core][system][endianness]")
{
  bool result = false;

  #if defined(STONEYDSP_BIG_ENDIAN)
  result = true;
  #elif defined(STONEYDSP_LITTLE_ENDIAN)
  result = true;
  #endif

  STONEYDSP_REQUIRE (result == true);
}

//============================================================================//

#endif // defined(STONEYDSP_BUILD_TEST) && defined(STONEYDSP_BUILD_CORE)

//=========================================================================//EOF
