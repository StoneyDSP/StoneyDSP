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

if(STONEYDSP_BUILD_EXAMPLES)

    # Console application tests
    set(_consoleapp_fail "if %ERRORLEVEL% neq 0 exit /b 1")
    if(UNIX)
        set(_consoleapp_fail "|| exit 1")
    endif()
    if(APPLE)
        set(_consoleapp_fail "|| exit 1")
    endif()

    macro(_stoneydsp_test_consoleappexample_command_help)
        add_test(
            NAME test_consoleappexample_command_help
            COMMAND "${StoneyDSP_BINARY_DIR}/examples/CMake/ConsoleApplication/ConsoleAppExample_artefacts/${CMAKE_BUILD_TYPE}/ConsoleAppExample" "--help" "${_consoleapp_fail}"
            WORKING_DIRECTORY "${StoneyDSP_SOURCE_DIR}"
        )
        # set_tests_properties(test_consoleappexample_command_help
        #     PROPERTIES PASS_REGULAR_EXPRESSION " passed."
        # )
    endmacro()

    macro(_stoneydsp_test_consoleappexample_command_version)
        add_test(
            NAME test_consoleappexample_command_version
            COMMAND "${StoneyDSP_BINARY_DIR}/examples/CMake/ConsoleApplication/ConsoleAppExample_artefacts/${CMAKE_BUILD_TYPE}/ConsoleAppExample" "--versoin" "${_consoleapp_fail}"
            WORKING_DIRECTORY "${StoneyDSP_SOURCE_DIR}"
        )
        # set_tests_properties(test_consoleappexample_command_help
        #     PROPERTIES PASS_REGULAR_EXPRESSION " passed."
        # )
    endmacro()

    _stoneydsp_test_consoleappexample_command_help()
    _stoneydsp_test_consoleappexample_command_version()

    unset(_consoleapp_fail)

    # VST3 tests with pluginval
    set(_pluginval_platform "Windows")
    set(_pluginval_binary "pluginval.exe")
    set(_pluginval_fail "if %ERRORLEVEL% neq 0 exit /b 1")
    if(UNIX)
        set(_pluginval_platform "Linux")
        set(_pluginval_binary "pluginval")
        set(_pluginval_fail "|| exit 1")
    endif()
    if(APPLE)
        set(_pluginval_platform "macOS")
        set(_pluginval_binary "pluginval.app/Contents/MacOS/pluginval")
        set(_pluginval_fail "|| exit 1")
    endif()

    message(STATUS "Checking for binary 'pluginval'")

    if(EXISTS "${StoneyDSP_BINARY_DIR}/${_pluginval_binary}")
        message(STATUS "  Found ${_pluginval_binary} for ${_pluginval_platform} in binary dir")
    else()

        if(EXISTS "${StoneyDSP_BINARY_DIR}/pluginval_${_pluginval_platform}.zip")
            message(STATUS "  Found pluginval_${_pluginval_platform}.zip: ${StoneyDSP_BINARY_DIR}/pluginval_${_pluginval_platform}.zip")
        else()

            if(NOT CURL_FETCH_PLUGINVAL_BINARY)
                message(STATUS "Fetching pluginval_${_pluginval_platform}.zip (Because STONEYDSP_BUILD_TESTS = TRUE)...")
                execute_process(
                    RESULT_VARIABLE CURL_FETCH_PLUGINVAL_BINARY
                    COMMAND curl "-LO" "https://github.com/Tracktion/pluginval/releases/download/v1.0.3/pluginval_${_pluginval_platform}.zip"
                    WORKING_DIRECTORY "${StoneyDSP_BINARY_DIR}"
                )
                message(STATUS "  Fetched pluginval_${_pluginval_platform}.zip: ${StoneyDSP_BINARY_DIR}/pluginval_${_pluginval_platform}.zip")
            endif()

        endif()

        if(NOT 7ZIP_UNPACK_PLUGINVAL_BINARY)
            message(STATUS "Unpacking pluginval_${_pluginval_platform}.zip: ${StoneyDSP_BINARY_DIR}/${_pluginval_binary}...")
            execute_process(
                RESULT_VARIABLE 7ZIP_UNPACK_PLUGINVAL_BINARY
                COMMAND 7z "x" "-y" "pluginval_${_pluginval_platform}.zip"
                WORKING_DIRECTORY "${StoneyDSP_BINARY_DIR}"
            )
            message(STATUS "  Unpacked pluginval_${_pluginval_platform}.zip: ${StoneyDSP_BINARY_DIR}/${_pluginval_binary}")
        endif()

    endif()

    macro(_stoneydsp_test_audiopluginexample_pluginval_vst3_validation)
        add_test(
        NAME test_pluginval_vst3_validation
        COMMAND "${StoneyDSP_BINARY_DIR}/${_pluginval_binary}" "--output-dir ${StoneyDSP_BINARY_DIR}" "--strictness-level 10" "--verbose" "--validate" "${StoneyDSP_BINARY_DIR}/examples/CMake/AudioPlugin/AudioPluginExample_artefacts/${CMAKE_BUILD_TYPE}/VST3/Audio Plugin Example.vst3/" "${_pluginval_fail}"
        WORKING_DIRECTORY "${StoneyDSP_BINARY_DIR}"
        )
    endmacro()

    macro(_stoneydsp_test_audiopluginexample_pluginval_vst3_unit_tests)
        add_test(
            NAME test_pluginval_vst3_unit_tests
            COMMAND "${StoneyDSP_BINARY_DIR}/${_pluginval_binary}" "--output-dir ${StoneyDSP_BINARY_DIR}" "--strictness-level 10" "--verbose" "--run-tests" "${StoneyDSP_BINARY_DIR}/examples/CMake/AudioPlugin/AudioPluginExample_artefacts/${CMAKE_BUILD_TYPE}/VST3/Audio Plugin Example.vst3/" "${_pluginval_fail}"
            WORKING_DIRECTORY "${StoneyDSP_BINARY_DIR}"
        )
    endmacro()

    _stoneydsp_test_audiopluginexample_pluginval_vst3_validation()
    # _stoneydsp_test_audiopluginexample_pluginval_vst3_unit_tests()

    unset(_pluginval_platform)
    unset(_pluginval_binary)
    unset(_pluginval_fail)

endif()
