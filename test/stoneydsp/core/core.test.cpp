/**
 * @file core.test.cpp
 * @author StoneyDSP (nathanjhood@googlemail.com)
 * @copyright Copyright (c) 2025
 *
 */

//==============================================================================

#include "stoneydsp/core/core.h"

//==============================================================================

#if defined(STONEYDSP_BUILD_TEST) && defined(STONEYDSP_BUILD_CORE)

//==============================================================================

  #include "../../utils.test.hpp"

//==============================================================================

STONEYDSP_TEST_CASE ("[core][files]", "[core][files]")
{
  bool result = false;
  #if defined(STONEYDSP_CORE_H_INCLUDED)
  result = true;
  #endif
  STONEYDSP_REQUIRE (result == true);
}

//============================================================================//

#endif // defined(STONEYDSP_BUILD_TEST) && defined(STONEYDSP_BUILD_CORE)

//=========================================================================//EOF
