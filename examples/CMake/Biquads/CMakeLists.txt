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

cmake_minimum_required (VERSION 3.22...3.28 FATAL_ERROR)

project(STONEYDSP_AUDIO_PLUGIN_BIQUADS VERSION 0.0.0)

# find_package(JUCE CONFIG REQUIRED)

juce_add_plugin(Biquads
    # VERSION ...                               # Set this if the plugin version is different to the project version
    # ICON_BIG ...                              # ICON_* arguments specify a path to an image file to use as an icon for the Standalone
    # ICON_SMALL ...
    COMPANY_NAME StoneyDSP                      # Specify the name of the plugin's author
    IS_SYNTH FALSE                              # Is this a synth or an effect?
    NEEDS_MIDI_INPUT FALSE                      # Does the plugin need midi input?
    NEEDS_MIDI_OUTPUT FALSE                     # Does the plugin need midi output?
    IS_MIDI_EFFECT FALSE                        # Is this plugin a MIDI effect?
    EDITOR_WANTS_KEYBOARD_FOCUS TRUE            # Does the editor need keyboard focus?
    COPY_PLUGIN_AFTER_BUILD FALSE               # Should the plugin be installed to a default location after building?
    PLUGIN_MANUFACTURER_CODE Sdsp               # A four-character manufacturer id with at least one upper-case character
    PLUGIN_CODE Biq0                            # A unique four-character plugin id with exactly one upper-case character
                                                # GarageBand 10.3 requires the first letter to be upper-case, and the remaining letters to be lower-case
    FORMATS AU VST3 Standalone                  # The formats to build. Other valid formats are: AAX Unity VST AU AUv3
    PRODUCT_NAME "Biquads"                      # The name of the final executable, which can differ from the target name
)

set (STONEYDSP_BIQUADS_GUI_HEADERS "")
list (APPEND STONEYDSP_BIQUADS_GUI_HEADERS
    "AutoButton.h"
    "AutoComboBox.h"
    "AutoComponent.h"
    "AutoKnob.h"
    "Viewer.h"
)

set (STONEYDSP_BIQUADS_DSP_HEADERS "")
list (APPEND STONEYDSP_BIQUADS_DSP_HEADERS
    "Biquads.h"
    "Coefficient.hpp"
    "SecondOrderBiquads.h"
)

set (STONEYDSP_BIQUADS_VST_HEADERS "")
list (APPEND STONEYDSP_BIQUADS_VST_HEADERS
    "PluginEditor.h"
    "PluginParameters.h"
    "PluginProcessor.h"
    "PluginWrapper.h"
)

set (STONEYDSP_BIQUADS_HEADERS "")
list (APPEND STONEYDSP_BIQUADS_HEADERS
    ${STONEYDSP_BIQUADS_GUI_HEADERS}
    ${STONEYDSP_BIQUADS_DSP_HEADERS}
    ${STONEYDSP_BIQUADS_VST_HEADERS}
)

foreach(STONEYDSP_BIQUADS_HEADER IN LISTS STONEYDSP_BIQUADS_HEADERS)
    configure_file(
        "include/Biquads/${STONEYDSP_BIQUADS_HEADER}" # SRC_DIR
        "include/Biquads/${STONEYDSP_BIQUADS_HEADER}" # BIN_DIR
    )
endforeach()

# juce_generate_juce_header(AudioPluginExample)

target_include_directories (Biquads
    PRIVATE
        $<BUILD_INTERFACE:${STONEYDSP_AUDIO_PLUGIN_BIQUADS_BINARY_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

target_sources (Biquads
    PUBLIC
        FILE_SET biquads_HEADERS
        TYPE HEADERS
        BASE_DIRS
            $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include/${PROJECT_NAME}>
            $<INSTALL_INTERFACE:include/${PROJECT_NAME}>
        FILES
            # # include/${PROJECT_NAME}/Components/AutoButton.h
            # $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include/${PROJECT_NAME}/Components/AutoButton.h>
            # $<INSTALL_INTERFACE:include/${PROJECT_NAME}/Components/AutoButton.h>

            # # include/${PROJECT_NAME}/Components/AutoComboBox.h
            # $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include/${PROJECT_NAME}/Components/AutoComboBox.h>
            # $<INSTALL_INTERFACE:include/${PROJECT_NAME}/Components/AutoComboBox.h>

            # include/${PROJECT_NAME}/Components/AutoComponent.h
            $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include/${PROJECT_NAME}/Components/AutoComponent.h>
            $<INSTALL_INTERFACE:include/${PROJECT_NAME}/Components/AutoComponent.h>

            # # include/${PROJECT_NAME}/Components/AutoKnob.h
            # $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include/${PROJECT_NAME}/Components/AutoKnob.h>
            # $<INSTALL_INTERFACE:include/${PROJECT_NAME}/Components/AutoKnob.h>

            # include/${PROJECT_NAME}/Components/Viewer.h
            $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include/${PROJECT_NAME}/Components/Viewer.h>
            $<INSTALL_INTERFACE:include/${PROJECT_NAME}/Components/Viewer.h>

            # include/${PROJECT_NAME}/Modules/Biquads.h
            $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include/${PROJECT_NAME}/Modules/Biquads.h>
            $<INSTALL_INTERFACE:include/${PROJECT_NAME}/Modules/Biquads.h>

            # include/${PROJECT_NAME}/Modules/Coefficient.hpp
            $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include/${PROJECT_NAME}/Modules/Coefficient.hpp>
            $<INSTALL_INTERFACE:include/${PROJECT_NAME}/Modules/Coefficient.hpp>

            # include/${PROJECT_NAME}/Modules/SecondOrderBiquads.h
            $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include/${PROJECT_NAME}/Modules/SecondOrderBiquads.h>
            $<INSTALL_INTERFACE:include/${PROJECT_NAME}/Modules/SecondOrderBiquads.h>

            # include/${PROJECT_NAME}/PluginEditor.h
            $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include/${PROJECT_NAME}/PluginEditor.h>
            $<INSTALL_INTERFACE:include/${PROJECT_NAME}/PluginEditor.h>

            # include/${PROJECT_NAME}/PluginParameters.h
            $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include/${PROJECT_NAME}/PluginParameters.h>
            $<INSTALL_INTERFACE:include/${PROJECT_NAME}/PluginParameters.h>

            # include/${PROJECT_NAME}/PluginProcessor.h
            $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include/${PROJECT_NAME}/PluginProcessor.h>
            $<INSTALL_INTERFACE:include/${PROJECT_NAME}/PluginProcessor.h>

            # include/${PROJECT_NAME}/PluginWrapper.h
            $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include/${PROJECT_NAME}/PluginWrapper.h>
            $<INSTALL_INTERFACE:include/${PROJECT_NAME}/PluginWrapper.h>

)

target_sources (Biquads
    PRIVATE
        include/Biquads/PluginEditor.cpp
        include/Biquads/PluginParameters.cpp
        include/Biquads/PluginProcessor.cpp
        include/Biquads/PluginWrapper.cpp

        include/Biquads/Modules/Biquads.cpp
        include/Biquads/Modules/Coefficient.cpp
        include/Biquads/Modules/SecondOrderBiquads.cpp

        # include/Biquads/Components/AutoButton.cpp
        # include/Biquads/Components/AutoComboBox.cpp
        include/Biquads/Components/AutoComponent.cpp
        # include/Biquads/Components/AutoKnob.cpp
        include/Biquads/Components/Viewer.cpp
)

target_compile_definitions (Biquads
    PUBLIC
        JUCE_WEB_BROWSER=0
        JUCE_USE_CURL=0
        JUCE_VST3_CAN_REPLACE_VST2=0
)

target_link_libraries (Biquads
    PRIVATE
        StoneyDSP::stoneydsp_core
        juce::juce_audio_basics
        juce::juce_audio_devices
        juce::juce_audio_formats
        juce::juce_audio_plugin_client
        juce::juce_audio_processors
        juce::juce_audio_utils
        juce::juce_core
        juce::juce_data_structures
        juce::juce_dsp
        juce::juce_events
        juce::juce_graphics
        juce::juce_gui_basics
        juce::juce_gui_extra
    PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags
)
