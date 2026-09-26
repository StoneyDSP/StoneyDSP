/**
 * @file catch2session.hpp
 * @author StoneyDSP (nathanjhood@googlemail.com)
 * @brief
 * @version @STONEYDSP_TEST_CATCH2_SESSION_VERSION@
 * @date 2025-01-29
 *
 * @copyright Copyright (c) 2025
 *
 */

#pragma once

#ifndef STONEYDSP_TEST_CATCH2_SESSION_HPP_INCLUDED
  #define STONEYDSP_TEST_CATCH2_SESSION_HPP_INCLUDED

  #if defined(STONEYDSP_BUILD_TEST)

    #include <catch2/catch_session.hpp>

    #include "stoneydsp/stoneydsp.h"

    #include <sstream>
    #include <string>
    #include <vector>

STONEYDSP_NAMESPACE_BEGIN (stoneydsp)
STONEYDSP_NAMESPACE_BEGIN (test)
using args_t = ::std::string;
int STONEYDSP_PUBLIC_FUNCTION run ();
STONEYDSP_NAMESPACE_END
STONEYDSP_NAMESPACE_END

STONEYDSP_EXTERN_C_BEGIN
typedef STONEYDSP_NAMESPACE_QUAL (stoneydsp::test) args_t
    stoneydsp_test_args_t;
typedef stoneydsp_test_args_t stoneydsp_test_args;
extern stoneydsp_test_args stoneydspTestArgs;
STONEYDSP_EXTERN_C_END

  #endif // defined (STONEYDSP_BUILD_TEST)

#endif // STONEYDSP_TEST_CATCH2_SESSION_HPP_INCLUDED
