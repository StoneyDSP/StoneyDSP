#[=============================================================================[
This file is part of the StoneyDSP library.
Copyright (c) 2024 - StoneyDSP
Home: https://www.stoneydsp.com
Source: https://github.com/StoneyDSP/StoneyDSP

StoneyDSP is an open source library subject to open-source licensing.

By using StoneyDSP, you agree to the terms of the StoneyDSP End-User License
Agreement and also the StoneyDSP Privacy Policy.

End User License Agreement: www.stoneydsp.com/LICENSE
Privacy Policy: www.stoneydsp.com/privacy-policy

By using StoneyDSP, you must also agree to the terms of both the JUCE 7 End-User
License Agreement and JUCE Privacy Policy.

End User License Agreement: www.juce.com/juce-7-licence
Privacy Policy: www.juce.com/juce-privacy-policy

Or: You may also use this code under the terms of the GPL v3 (see
www.gnu.org/licenses).

STONEYDSP IS PROVIDED "AS IS" WITHOUT ANY WARRANTY, AND ALL WARRANTIES, WHETHER
EXPRESSED OR IMPLIED, INCLUDING MERCHANTABILITY AND FITNESS FOR PURPOSE, ARE
DISCLAIMED.
]=============================================================================]#

cmake_minimum_required(VERSION 3.22...3.28 FATAL_ERROR)

# list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/share/cmake/Modules")

project(STONEYDSP_EXAMPLE_CONSOLE_APPLICATION VERSION 0.0.1)

set_property(GLOBAL PROPERTY USE_FOLDERS YES)

if(NOT DEFINED JUCE_VERSION)
    find_package(JUCE CONFIG REQUIRED)
endif()

juce_add_console_app(ConsoleAppExample
    PRODUCT_NAME "Console App Example"
    _NO_RESOURCERC
)

configure_file(
    "include/ConsoleAppExample.h"
    "include/ConsoleAppExample.h"
)

# juce_generate_juce_header(ConsoleAppExample)

target_include_directories(ConsoleAppExample
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

target_sources(ConsoleAppExample
    PRIVATE
        "src/ConsoleAppExample.cpp"
)

target_compile_definitions(ConsoleAppExample
    PRIVATE
        # JUCE_WEB_BROWSER and JUCE_USE_CURL would be on by default, but you might not need them.
        JUCE_WEB_BROWSER=0  # OR `NEEDS_WEB_BROWSER TRUE` in `juce_add_console_app`
        JUCE_USE_CURL=0     # OR `NEEDS_CURL TRUE` in `juce_add_console_app` call
)

# juce_add_binary_data(ConsoleAppData SOURCES ...)

target_link_libraries(ConsoleAppExample
    PRIVATE
        # ConsoleAppData
        # juce::juce_core
        StoneyDSP::stoneydsp_core
    PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_warning_flags
)

include("${StoneyDSP_SOURCE_DIR}/extras/Build/CMake/StoneyDSPCPackIgnoreList.cmake")
set(CPACK_SOURCE_IGNORE_FILES ${STONEYDSP_CPACK_IGNORE_LIST})
include(CPack)
