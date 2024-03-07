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

# add_executable (Main "src/main.cpp")
# target_link_libraries (Main PRIVATE StoneyDSP::StoneyDSP)
# set_target_properties (Main
#     PROPERTIES
#     ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/lib"
#     LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/lib"
#     RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/bin"
#     PDB_OUTPUT_DIRECTORY     "${CMAKE_CURRENT_BINARY_DIR}/bin"
#     # POSITION_INDEPENDENT_CODE ON
# )

if (NOT DEFINED JUCE_VERSION)
    find_package (JUCE 7.0.10 CONFIG REQUIRED)
endif ()

# The juceaide program generates intermediate build files including BinaryData sources, icons, and
# plists. To ensure that we always build it for the host system, and not for, say, a device or
# simulator if we're targeting iOS or Android, we reinvoke cmake here and build juceaide during the
# configuration stage of the outer project.

if(STONEYDSP_BUILD_HELPER_TOOLS)

    configure_file(
        "include/stoneyhelper/cli.hpp" # SOURCE_DIR
        "include/stoneyhelper/cli.hpp" # BINARY_DIR
    )

    configure_file(
        "include/stoneyhelper/main.hpp" # SOURCE_DIR
        "include/stoneyhelper/main.hpp" # BINARY_DIR
    )

    # Build the tool for the current system
    juce_add_console_app(stoneyhelper _NO_RESOURCERC)

    target_include_directories(stoneyhelper
        PUBLIC
            $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>
            $<INSTALL_INTERFACE:include>
    )

    target_sources(stoneyhelper
        PRIVATE
        "src/stoneyhelper/cli.cpp"
        "src/stoneyhelper/main.cpp"
    )

    target_compile_definitions(stoneyhelper PRIVATE
        JUCE_DISABLE_JUCE_VERSION_PRINTING=1
        JUCE_USE_CURL=0
        # This is a temporary workaround to allow builds to complete on Xcode 15.
        # Add -Wl,-ld_classic to the OTHER_LDFLAGS build setting if you need to
        # deploy to older versions of macOS.
        JUCE_SILENCE_XCODE_15_LINKER_WARNING=1
    )

    target_link_libraries(stoneyhelper PRIVATE
        # juce::juce_build_tools
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags
    )

    set_target_properties(stoneyhelper PROPERTIES
        MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

    export(TARGETS stoneyhelper
           NAMESPACE stoneydsp_tools::
           FILE "${StoneyDSP_BINARY_DIR}/StoneyDSPToolsExport.cmake")
else()
    message(STATUS "Configuring stoneyhelper...")

    if(CMAKE_CROSSCOMPILING)
        unset(ENV{ADDR2LINE})
        unset(ENV{AR})
        unset(ENV{ASM})
        unset(ENV{AS})
        unset(ENV{CC})
        unset(ENV{CPP})
        unset(ENV{CXXFILT})
        unset(ENV{CXX})
        unset(ENV{DLLTOOL})
        unset(ENV{DLLWRAP})
        unset(ENV{ELFEDIT})
        unset(ENV{GCC})
        unset(ENV{GCOV_DUMP})
        unset(ENV{GCOV_TOOL})
        unset(ENV{GCOV})
        unset(ENV{GPROF})
        unset(ENV{GXX})
        unset(ENV{LDFLAGS})
        unset(ENV{LD_BFD})
        unset(ENV{LD})
        unset(ENV{LTO_DUMP})
        unset(ENV{NM})
        unset(ENV{OBJCOPY})
        unset(ENV{OBJDUMP})
        unset(ENV{PKG_CONFIG_LIBDIR})
        unset(ENV{PKG_CONFIG})
        unset(ENV{RANLIB})
        unset(ENV{RC})
        unset(ENV{READELF})
        unset(ENV{SIZE})
        unset(ENV{STRINGS})
        unset(ENV{STRIP})
        unset(ENV{WIDL})
        unset(ENV{WINDMC})
        unset(ENV{WINDRES})

        if(DEFINED ENV{PATH_ORIG})
            set(ENV{PATH} "$ENV{PATH_ORIG}")
        endif()
    endif()

    # Generator platform is only supported on specific generators
    if(CMAKE_GENERATOR MATCHES "^Visual Studio.*$")
        set(ENV{CMAKE_GENERATOR_PLATFORM} "${CMAKE_HOST_SYSTEM_PROCESSOR}")
    endif()


    if(DEFINED CMAKE_TOOLCHAIN_FILE)
        set(_maybe_toolchain "-DCMAKE_TOOLCHAIN_FILE=${CMAKE_TOOLCHAIN_FILE}")
    endif()

    # Looks like we're bootstrapping, reinvoke CMake
    execute_process(COMMAND "${CMAKE_COMMAND}"
            "."
            "-B${StoneyDSP_BINARY_DIR}/tools"
            "-G${CMAKE_GENERATOR}"
            "-DCMAKE_MAKE_PROGRAM=${CMAKE_MAKE_PROGRAM}"
            "-DCMAKE_BUILD_TYPE=Debug"
            "-DSTONEYDSP_BUILD_HELPER_TOOLS=ON"
            "-DCMAKE_INSTALL_PREFIX=${CMAKE_INSTALL_PREFIX}"
            "-DVCPKG_MANIFEST_MODE=FALSE"
            ${_maybe_toolchain}
            ${extra_compiler_flag_arguments}
            "--no-warn-unused-cli"
        WORKING_DIRECTORY "${StoneyDSP_SOURCE_DIR}"
        OUTPUT_VARIABLE command_output
        ERROR_VARIABLE command_output
        RESULT_VARIABLE result_variable
    )
    unset(_maybe_toolchain)

    if(result_variable)
        message(FATAL_ERROR "Failed to configure stoneyhelper\n${command_output}")
    endif()

    message(STATUS "Building stoneyhelper")

    execute_process(COMMAND "${CMAKE_COMMAND}"
            --build "${StoneyDSP_BINARY_DIR}/tools"
            --config Debug
        OUTPUT_VARIABLE command_output
        ERROR_VARIABLE command_output
        RESULT_VARIABLE result_variable
    )

    if(result_variable)
        message(FATAL_ERROR "Failed to build stoneyhelper\n${command_output}")
    endif()

    message(STATUS "Exporting stoneyhelper")

    # This will be generated by the recursive invocation of CMake (above)
    include("${StoneyDSP_BINARY_DIR}/tools/StoneyDSPToolsExport.cmake")

    add_executable(stoneyhelper IMPORTED GLOBAL)
    get_target_property(imported_location stoneydsp_tools::stoneyhelper IMPORTED_LOCATION_DEBUG)
    set_target_properties(stoneyhelper PROPERTIES IMPORTED_LOCATION "${imported_location}")

    add_executable(stoneydsp_tools::stoneyhelper ALIAS stoneyhelper)

    set(STONEYDSP_TOOL_INSTALL_DIR "bin/StoneyDSP-v${StoneyDSP_VERSION}" CACHE STRING
        "The location, relative to the install prefix, where stoneyhelper will be installed")

    install(PROGRAMS "${imported_location}" DESTINATION "${STONEYDSP_TOOL_INSTALL_DIR}")

    get_filename_component(binary_name "${imported_location}" NAME)
    set(STONEYDSP_STONEYHELPER_NAME "${binary_name}" CACHE INTERNAL "The name of the stoneyhelper program")
endif()
