/**
 * @file compiler.test.cpp
 * @author StoneyDSP (nathanjhood@googlemail.com)
 * @copyright Copyright (c) 2025
 *
 */

//==============================================================================

#include <stoneydsp/core/system/compiler.h>

//==============================================================================

#if defined(STONEYDSP_BUILD_TEST) && defined(STONEYDSP_BUILD_CORE)

//==============================================================================

  #include "../../../utils.test.hpp"

//====================================================================//compiler

STONEYDSP_TEST_CASE ("[core][system][compiler]", "[core][system][compiler]")
{
  bool result = false;

  #if defined(STONEYDSP_MSVC)
  result = true;
  #elif defined(STONEYDSP_CLANG)
  result = true;
  #elif defined(STONEYDSP_GCC)
  result = true;
  #endif

  STONEYDSP_REQUIRE (result == true);
}

//============================================================================//

#endif // defined(STONEYDSP_BUILD_TEST) && defined(STONEYDSP_BUILD_CORE)

//=========================================================================//EOF
