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

cmake_minimum_required(VERSION 3.22)

project(STONEYDSP_EXAMPLE_GUI_APP VERSION 0.0.0)

# find_package(JUCE CONFIG REQUIRED))                    # If you've put JUCE in a subdirectory called JUCE

juce_add_gui_app(GuiAppExample
    # VERSION ...                       # Set this if the app version is different to the project version
    # ICON_BIG ...                      # ICON_* arguments specify a path to an image file to use as an icon
    # ICON_SMALL ...
    # DOCUMENT_EXTENSIONS ...           # Specify file extensions that should be associated with this app
    # COMPANY_NAME ...                  # Specify the name of the app's author
    PRODUCT_NAME "Gui App Example"      # The name of the final executable, which can differ from the target name
)

# juce_generate_juce_header(GuiAppExample)
configure_file (
    "include/GUIApp/component.h"
    "include/GUIApp/component.h"
)
target_include_directories (GuiAppExample
    PUBLIC
        $<BUILD_INTERFACE:${STONEYDSP_EXAMPLE_GUI_APP_BINARY_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

target_sources(GuiAppExample
    PRIVATE
        src/main.cpp
        src/component.cpp
)

target_compile_definitions(GuiAppExample
    PRIVATE
        # JUCE_WEB_BROWSER and JUCE_USE_CURL would be on by default, but you might not need them.
        JUCE_WEB_BROWSER=0  # If you remove this, add `NEEDS_WEB_BROWSER TRUE` to the `juce_add_gui_app` call
        JUCE_USE_CURL=0     # If you remove this, add `NEEDS_CURL TRUE` to the `juce_add_gui_app` call
        JUCE_APPLICATION_NAME_STRING="$<TARGET_PROPERTY:GuiAppExample,JUCE_PRODUCT_NAME>"
        JUCE_APPLICATION_VERSION_STRING="$<TARGET_PROPERTY:GuiAppExample,JUCE_VERSION>"
)

target_link_libraries(GuiAppExample
    PRIVATE
        StoneyDSP::stoneydsp_graphics
        juce::juce_gui_extra
    PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags
)
