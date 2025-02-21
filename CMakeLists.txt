cmake_minimum_required(VERSION 3.23...3.31 FATAL_ERROR)

# Constants - write to cache!
set(STONEYDSP_SLUG "stoneydsp" CACHE STRING "" FORCE)
set(STONEYDSP_BRAND "stoneydsp" CACHE STRING "" FORCE)

# Temporary - no cache!
set(STONEYDSP_DIR "${CMAKE_CURRENT_LIST_DIR}")

# Include StoneyDSP CMake Modules
list(APPEND CMAKE_MODULE_PATH "${STONEYDSP_DIR}/share/cmake/Modules")
message(STATUS "CMake Module Path: ${CMAKE_MODULE_PATH}")

# Add directory structure
include(GNUInstallDirs)
include(stoneydsp)
stoneydsp_add_directories()
include(stoneydsp-version-helpers)

if(STONEYDSP_GENERATE_VERSIONS)
    stoneydsp_git_versions()
else()
    stoneydsp_file_versions()
endif()

# Begin project
project(STONEYDSP
    VERSION "${_STONEYDSP_MANAGED_VERSION}"
    DESCRIPTION "The StoneyDSP Audio Library."
    HOMEPAGE_URL "https://github.com/StoneyDSP/StoneyDSP"
    LANGUAGES C CXX
)
set(PROJECT_NAME "StoneyDSP")

set(STONEYDSP_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}" CACHE STRING "" FORCE)
set(STONEYDSP_VERSION_MINOR "${PROJECT_VERSION_MINOR}" CACHE STRING "" FORCE)
set(STONEYDSP_VERSION_PATCH "${PROJECT_VERSION_PATCH}" CACHE STRING "" FORCE)
set(STONEYDSP_VERSION_TWEAK "${PROJECT_VERSION_TWEAK}" CACHE STRING "" FORCE)
set(STONEYDSP_VERSION "${PROJECT_VERSION}" CACHE STRING "" FORCE)
stoneydsp_update_version_file()

option(STONEYDSP_EXPERIMENTAL "Use '-DSTONEYDSP_EXPERIMENTAL=ON|OFF' when configuring to toggle this option." OFF)
option(STONEYDSP_BUILD_DOCS "Use '-DSTONEYDSP_BUILD_DOCS=ON|OFF' when configuring to toggle this option." OFF)
option(STONEYDSP_BUILD_CORE "Use '-DSTONEYDSP_BUILD_CORE=ON|OFF' when configuring to toggle this option." ON)
cmake_dependent_option(STONEYDSP_BUILD_SIMD "Use '-DSTONEYDSP_BUILD_SIMD=ON|OFF' when configuring to toggle this option." OFF "STONEYDSP_BUILD_CORE" OFF)
cmake_dependent_option(STONEYDSP_BUILD_TEST "Use '-DSTONEYDSP_BUILD_TEST=ON|OFF' when configuring to toggle this option." OFF "STONEYDSP_IS_TOP_LEVEL;STONEYDSP_BUILD_CORE" OFF)

include(CMakeDependentOption)

set(STONEYDSP_TARGETS)

#[==============================[stoneydsp::core]==============================]
if(STONEYDSP_BUILD_CORE)
    include(stoneydsp-core)
    stoneydsp_add_core()
    list(APPEND STONEYDSP_TARGETS "${STONEYDSP_CORE_TARGET_NAME}")
endif()

#[==============================[stoneydsp::simd]==============================]
if(STONEYDSP_BUILD_SIMD)
    include(stoneydsp-simd)
    stoneydsp_add_simd()
    list(APPEND STONEYDSP_TARGETS "${STONEYDSP_SIMD_TARGET_NAME}")
endif()

#[===========================[stoneydsp::stoneydsp]===========================]
# 'always-on' target: libstoneydsp
stoneydsp_add_stoneydsp()
include(CMakePackageConfigHelpers)

file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/${STONEYDSP_SLUG}-config.cmake.in" [==[
# Begin package init
@PACKAGE_INIT@
# End package init

include("${CMAKE_CURRENT_LIST_DIR}/@STONEYDSP_SLUG@-config-version.cmake")

set(_@STONEYDSP_SLUG@_supported_components)
list(APPEND _@STONEYDSP_SLUG@_supported_components
    @STONEYDSP_TARGETS@
)

## Custom 'check_required_components' macro
foreach(_requested_component ${@STONEYDSP_SLUG@_FIND_COMPONENTS})
    if (NOT _requested_component IN_LIST _@STONEYDSP_SLUG@_supported_components)
        message(FATAL_ERROR "Unsupported component: ${_requested_component}")
        set(@STONEYDSP_SLUG@_FOUND False)
        set(@STONEYDSP_SLUG@_NOT_FOUND_MESSAGE "Unsupported component: ${_requested_component}")
    endif()
    include("${CMAKE_CURRENT_LIST_DIR}/@STONEYDSP_SLUG@-${_requested_component}-targets.cmake")
    # Tell the user what is happening
    message(STATUS "Imported target: @STONEYDSP_SLUG@::${_requested_component}")
endforeach()

unset(_@STONEYDSP_SLUG@_supported_components)
# 'always-on' library target
include("${CMAKE_CURRENT_LIST_DIR}/@STONEYDSP_TARGET_NAME@-targets.cmake")
# Tell the user what is happening
message(STATUS "Imported target: @STONEYDSP_SLUG@::@STONEYDSP_TARGET_NAME@")
]==])

# create cmake config file
configure_package_config_file(
    "${CMAKE_CURRENT_BINARY_DIR}/${STONEYDSP_SLUG}-config.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/lib/cmake/${STONEYDSP_BRAND}/${STONEYDSP_SLUG}-config.cmake"
    INSTALL_DESTINATION
    "${CMAKE_INSTALL_LIBDIR}/cmake/${STONEYDSP_BRAND}"

    # Use custom 'check_required_components' macro
    NO_CHECK_REQUIRED_COMPONENTS_MACRO
)

# generate the version file for the cmake config file
write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/lib/cmake/${STONEYDSP_BRAND}/${STONEYDSP_SLUG}-config-version.cmake"
    VERSION ${STONEYDSP_VERSION_MAJOR}.${STONEYDSP_VERSION_MINOR}.${STONEYDSP_VERSION_PATCH}
    COMPATIBILITY AnyNewerVersion
)

install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/lib/cmake/${STONEYDSP_BRAND}/${STONEYDSP_SLUG}-config.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/lib/cmake/${STONEYDSP_BRAND}/${STONEYDSP_SLUG}-config-version.cmake"
    DESTINATION
    "${CMAKE_INSTALL_LIBDIR}/cmake/${STONEYDSP_BRAND}"
)

#[==============================[stoneydsp::test]==============================]
if(STONEYDSP_BUILD_TEST)
    find_package(Catch2 REQUIRED 3.7.1)
    include(stoneydsp-test)
    stoneydsp_add_test()
endif()

#[===================================[CTest]===================================]
if(STONEYDSP_BUILD_TEST)
    enable_testing()
    include(CTest)
    include(Catch)

    set(CMAKE_CATCH_DISCOVER_TESTS_DISCOVERY_MODE PRE_TEST)
    catch_discover_tests("${STONEYDSP_TEST_TARGET_NAME}")
endif()

#[===================================[CPack]===================================]
set(CPACK_PACKAGE_VENDOR "StoneyDSP")
set(CPACK_PACKAGE_VERSION_MAJOR "${STONEYDSP_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${STONEYDSP_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${STONEYDSP_VERSION_PATCH}")
set(CPACK_GENERATOR "ZIP")
set(CPACK_SOURCE_GENERATOR "ZIP")
include(CPack)
