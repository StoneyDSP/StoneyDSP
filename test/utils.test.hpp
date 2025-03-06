#pragma once

#ifndef STONEYDSP_TEST_UTILS_H_INCLUDED
  #define STONEYDSP_TEST_UTILS_H_INCLUDED

//==============================================================================

  #if defined(STONEYDSP_BUILD_TEST)

  //==============================================================================

    #ifndef CATCH_CONFIG_PREFIX_ALL
      #define CATCH_CONFIG_PREFIX_ALL
    #endif

    #include <algorithm>                            // for `std::sort`
    #include <catch2/benchmark/catch_benchmark.hpp> //
    #include <catch2/catch_test_macros.hpp>         //
    #include <catch2/matchers/catch_matchers_floating_point.hpp> //
    #include <cmath>                                             //
    #include <cstring>                                           //
    #include <limits>                           // for `std::numeric_limits`
    #include <numeric>                          // for `std::accumulate`
    #include <sstream>                          // for serialization tests
    #include <stoneydsp/core/system/compiler.h> // for `STONEYDSP_PUBLIC_FUNCTION`
    #include <stoneydsp/core/system/platform.h> //
    #include <type_traits> // for `is_signed` and `is_unsigned`
    #include <vector>      // for compatibility tests

  //==============================================================================

    #define STONEYDSP_REQUIRE(...) CATCH_REQUIRE (__VA_ARGS__)
    #define STONEYDSP_REQUIRE_FALSE(...) CATCH_REQUIRE_FALSE (__VA_ARGS__)
    #define STONEYDSP_REQUIRE_THROWS(...) CATCH_REQUIRE_THROWS (__VA_ARGS__)
    #define STONEYDSP_REQUIRE_THROWS_AS(...)                                  \
      CATCH_REQUIRE_THROWS_AS (__VA_ARGS__)
    #define STONEYDSP_REQUIRE_NOTHROW(...) CATCH_REQUIRE_NOTHROW (__VA_ARGS__)
    #define STONEYDSP_REQUIRE_THAT(...) CATCH_REQUIRE_THAT (__VA_ARGS__)

    #define STONEYDSP_CHECK(...) CATCH_CHECK (__VA_ARGS__)
    #define STONEYDSP_CHECK_FALSE(...) CATCH_CHECK_FALSE (__VA_ARGS__)
    #define STONEYDSP_CHECK_IF(...) CATCH_CHECK_IF (__VA_ARGS__)
    #define STONEYDSP_CHECK_ELSE(...) CATCH_CHECK_ELSE (__VA_ARGS__)

    #define STONEYDSP_TEST_CASE(...) CATCH_TEST_CASE (__VA_ARGS__)

    #define STONEYDSP_SECTION(...) CATCH_SECTION (__VA_ARGS__)

    #define STONEYDSP_BENCHMARK(...) CATCH_BENCHMARK (__VA_ARGS__)

  //==============================================================================

  #endif // defined(STONEYDSP_BUILD_TEST)

//==============================================================================

#endif // STONEYDSP_TEST_UTILS_H_INCLUDED

//==============================================================================
