# https://github.com/microsoft/vcpkg-tool/blob/main/cmake/Findfmt.cmake

option(VCPKG_DEPENDENCY_EXTERNAL_FMT "Use an external version of the fmt library" OFF)

# This option exists to allow the URI to be replaced with a Microsoft-internal URI in official
# builds which have restricted internet access; see azure-pipelines/signing.yml
# Note that the SHA512 is the same, so vcpkg-tool contributors need not be concerned that we built
# with different content.
# A cache variable cannot be used it here because it will break contributors' builds on fmt update.
if("$CACHE{VCPKG_FMT_URL}" MATCHES "^https://github.com/fmtlib/fmt/archive/refs/tags")
    unset(VCPKG_FMT_URL CACHE) # Fix upgrade
endif()
if(NOT VCPKG_FMT_URL)
    set(VCPKG_FMT_URL "https://github.com/fmtlib/fmt/archive/refs/tags/10.1.0.tar.gz")
endif()

if(POLICY CMP0135)
    cmake_policy(SET CMP0135 NEW)
endif()

set(OLD_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
set(SKIP_WARNINGS OFF)
if(MSVC AND VCPKG_DEVELOPMENT_WARNINGS AND NOT (CMAKE_CXX_COMPILER_ID MATCHES "AppleClang") AND NOT (CMAKE_CXX_COMPILER_ID MATCHES "[Cc]lang"))
    set(SKIP_WARNINGS ON)
    # fmt\core.h(418): warning C6239: (<non-zero constant> && <expression>) always evaluates to the result of <expression>:  Did you intend to use the bitwise-and (&) operator? If not, consider removing the redundant '<non-zero constant>' and the && operator.
    string(APPEND CMAKE_CXX_FLAGS " /wd6239")
    # This one is guarded by an assert
    # fmt\format-inl.h(327): warning C6385: Reading invalid data from 'pow10_significands'.: Lines: 298, 300, 327
    string(APPEND CMAKE_CXX_FLAGS " /wd6385")
    # fmt\os.h(377): warning C6326: Potential comparison of a constant with another constant.
    string(APPEND CMAKE_CXX_FLAGS " /wd6326")
endif()

include(FetchContent)
FetchContent_Declare(
    fmt
    URL "${VCPKG_FMT_URL}"
    URL_HASH "SHA512=69a7b8584f828528e3bb4b87153449e96df29bd740adcd42a2e3d50ae4a270c80a5eb2c3057337048be5b978094d8bb73bec3378e3b6370748de2b063dd0aa4b"
)

if(NOT fmt_FIND_REQUIRED)
    message(FATAL_ERROR "fmt must be REQUIRED")
endif()

if(VCPKG_DEPENDENCY_EXTERNAL_FMT)
    find_package(fmt CONFIG REQUIRED)
else()
    FetchContent_MakeAvailable(fmt)
endif()

if(SKIP_WARNINGS)
    set(CMAKE_CXX_FLAGS "${OLD_CXX_FLAGS}")
endif()
