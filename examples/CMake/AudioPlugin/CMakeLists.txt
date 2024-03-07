cmake_minimum_required(VERSION 3.22)

project(STONEYDSP_EXAMPLE_AUDIO_PLUGIN VERSION 0.0.1)

# find_package(JUCE CONFIG REQUIRED)        # If you've installed JUCE to your system
# or
# add_subdirectory(JUCE)                    # If you've put JUCE in a subdirectory called JUCE

# If you are building a VST2 or AAX plugin, CMake needs to be told where to find these SDKs on your
# system. This setup should be done before calling `juce_add_plugin`.

# juce_set_vst2_sdk_path(...)
# juce_set_aax_sdk_path(...)

juce_add_plugin(AudioPluginExample
    PRODUCT_NAME "Audio Plugin Example"         # The name of the final executable, which can differ from the target name
    FORMATS AU VST3 Standalone                  # The formats to build. Other valid formats are: AAX Unity VST AU AUv3
    # VERSION ...                               # Set this if the plugin version is different to the project version
    # BUILD_VERSION ...
    # ICON_BIG ...                              # ICON_* arguments specify a path to an image file to use as an icon for the Standalone
    # ICON_SMALL ...
    # DESCRIPTION

    COMPANY_NAME StoneyDSP                      # Specify the name of the plugin's author
    COMPANY_WEBSITE "https://stoneydsp.com"
    COMPANY_EMAIL "nathan@stoneydsp.com"
    # COMPANY_COPYRIGHT

    # NEEDS_CURL <TRUE|FALSE>
    # NEEDS_WEB_BROWSER <TRUE|FALSE>
    # NEEDS_STORE_KIT <TRUE|FALSE>

    VST3_AUTO_MANIFEST FALSE

    IS_SYNTH FALSE                              # Is this a synth or an effect?
    NEEDS_MIDI_INPUT FALSE                      # Does the plugin need midi input?
    NEEDS_MIDI_OUTPUT FALSE                     # Does the plugin need midi output?
    IS_MIDI_EFFECT FALSE                        # Is this plugin a MIDI effect?
    EDITOR_WANTS_KEYBOARD_FOCUS TRUE            # Does the editor need keyboard focus?
    # COPY_PLUGIN_AFTER_BUILD FALSE             # Should the plugin be installed to a default location after building?

    PLUGIN_NAME "AudioPluginExample"
    PLUGIN_MANUFACTURER_CODE Sdsp               # A four-character manufacturer id with at least one upper-case character
    PLUGIN_CODE Ape0                            # A unique four-character plugin id with exactly one upper-case character
                                                # GarageBand 10.3 requires the first letter to be upper-case, and the remaining letters to be lower-case
)

# juce_generate_juce_header(AudioPluginExample)

set(STONEYDSP_EXAMPLE_AUDIO_PLUGIN_GUI_HEADERS "")
list(APPEND STONEYDSP_EXAMPLE_AUDIO_PLUGIN_GUI_HEADERS
    "PluginEditor.h"
)

set(STONEYDSP_EXAMPLE_AUDIO_PLUGIN_VST_HEADERS "")
list(APPEND STONEYDSP_EXAMPLE_AUDIO_PLUGIN_VST_HEADERS
    "PluginProcessor.h"
)

set (STONEYDSP_EXAMPLE_AUDIO_PLUGIN_HEADERS "")
list (APPEND STONEYDSP_EXAMPLE_AUDIO_PLUGIN_HEADERS
    ${STONEYDSP_EXAMPLE_AUDIO_PLUGIN_GUI_HEADERS}
    ${STONEYDSP_EXAMPLE_AUDIO_PLUGIN_VST_HEADERS}
)

foreach(STONEYDSP_EXAMPLE_AUDIO_PLUGIN_HEADER IN LISTS STONEYDSP_EXAMPLE_AUDIO_PLUGIN_HEADERS)
    configure_file(
        "include/AudioPlugin/${STONEYDSP_EXAMPLE_AUDIO_PLUGIN_HEADER}" # SRC_DIR
        "include/AudioPlugin/${STONEYDSP_EXAMPLE_AUDIO_PLUGIN_HEADER}" # BIN_DIR
    )
    target_sources(AudioPluginExample
        PUBLIC
        FILE_SET stoneydsp_EXAMPLE_AUDIO_PLUGIN_HEADERS
        TYPE HEADERS
        BASE_DIRS
            $<BUILD_INTERFACE:${STONEYDSP_EXAMPLE_AUDIO_PLUGIN_BINARY_DIR}/include>
            $<INSTALL_INTERFACE:include>
        FILES
            $<BUILD_INTERFACE:${STONEYDSP_EXAMPLE_AUDIO_PLUGIN_BINARY_DIR}/include/AudioPlugin/${STONEYDSP_EXAMPLE_AUDIO_PLUGIN_HEADER}>
            $<INSTALL_INTERFACE:include/AudioPlugin/${STONEYDSP_EXAMPLE_AUDIO_PLUGIN_HEADER}>
    )
endforeach()

target_include_directories (AudioPluginExample
    PRIVATE
        $<BUILD_INTERFACE:${STONEYDSP_EXAMPLE_AUDIO_PLUGIN_BINARY_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

target_sources(AudioPluginExample
    PRIVATE
        "src/AudioPlugin/PluginEditor.cpp"
        "src/AudioPlugin/PluginProcessor.cpp"
)

target_compile_definitions(AudioPluginExample
    PUBLIC
        # JUCE_WEB_BROWSER and JUCE_USE_CURL would be on by default, but you might not need them.
        JUCE_WEB_BROWSER=0  # If you remove this, add `NEEDS_WEB_BROWSER TRUE` to the `juce_add_plugin` call
        JUCE_USE_CURL=0     # If you remove this, add `NEEDS_CURL TRUE` to the `juce_add_plugin` call
        JUCE_VST3_CAN_REPLACE_VST2=0
)

target_link_libraries(AudioPluginExample
    PRIVATE
        StoneyDSP::stoneydsp_audio
        juce::juce_audio_utils
    PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags
)

juce_enable_vst3_manifest_step(AudioPluginExample)

juce_enable_copy_plugin_step(AudioPluginExample)
