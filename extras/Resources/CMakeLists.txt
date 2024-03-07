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

# Create a CMakeRC library
# See https://github.com/vector-of-bool/cmrc/blob/master/README.md#usage

if (NOT DEFINED CMakeRC_DIR)
    include(CMakeRC RESULT_VARIABLE CMakeRC_FOUND)
    if (NOT CMakeRC_FOUND)
        message (FATAL_ERROR "Cannot find CMakeRC?")
        return ()
    endif ()
else ()
    find_package (CMakeRC REQUIRED)
endif ()

file(COPY
    "${StoneyDSP_SOURCE_DIR}/AUTHORS"
    "${StoneyDSP_SOURCE_DIR}/LICENSE"
    "${StoneyDSP_SOURCE_DIR}/VERSION"
    "${StoneyDSP_SOURCE_DIR}/README.md"
    DESTINATION "${StoneyDSP_BINARY_DIR}/public"
)

cmrc_add_resource_library (Resources
	ALIAS StoneyDSP::Resources
	NAMESPACE StoneyDSP::Resources
)

cmrc_add_resources (Resources
    WHENCE ${StoneyDSP_BINARY_DIR}/public
	PREFIX StoneyDSP/Resources
    # Resources to compile...
    ${StoneyDSP_BINARY_DIR}/public/AUTHORS
    ${StoneyDSP_BINARY_DIR}/public/LICENSE
    ${StoneyDSP_BINARY_DIR}/public/VERSION
    ${StoneyDSP_BINARY_DIR}/public/README.md
)

if (UNIX)
    set_target_properties (Resources
        PROPERTIES
        POSITION_INDEPENDENT_CODE ON
    )
endif ()
