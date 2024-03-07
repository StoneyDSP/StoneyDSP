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

if (NOT DEFINED CMakeRC_DIR)
    include(CMakeRC RESULT_VARIABLE CMakeRC_FOUND)
    if (NOT CMakeRC_FOUND)
        message (FATAL_ERROR "Cannot find CMakeRC?")
        return ()
    endif ()
else ()
    find_package (CMakeRC REQUIRED)
endif ()

file(COPY "${CMAKE_CURRENT_LIST_DIR}/images"
    DESTINATION "${StoneyDSP_BINARY_DIR}/public"
)

cmrc_add_resource_library (Icons
	ALIAS StoneyDSP::Icons
	NAMESPACE StoneyDSP::Icons
)

cmrc_add_resources (Icons

	WHENCE ${StoneyDSP_BINARY_DIR}/public/images
	PREFIX StoneyDSP/Icons

	${StoneyDSP_BINARY_DIR}/public/images/favicon.ico
)

set (STONEYDSP_ICONS_PNG_WIDE "")
list (APPEND STONEYDSP_ICONS_PNG_WIDE
	w_icon__196x128.png
    w_icon__320x160.png
	w_icon__384x256.png
    w_icon__640x320.png
	w_icon__768x512.png
    w_icon__960x480.png
    w_icon__1024x768.png
    w_icon__1280x640.png
)

foreach (STONEYDSP_ICON_PNG_WIDE IN LISTS STONEYDSP_ICONS_PNG_WIDE)
    cmrc_add_resources (Icons

        WHENCE ${StoneyDSP_BINARY_DIR}/public/images
        PREFIX StoneyDSP/Icons

        ${StoneyDSP_BINARY_DIR}/public/images/${STONEYDSP_ICON_PNG_WIDE}
    )
endforeach ()

set (STONEYDSP_ICONS_PNG "")
list (APPEND STONEYDSP_ICONS_PNG
	android-chrome-192x192.png
	android-chrome-512x512.png
	android-icon-144x144.png
	android-icon-192x192.png
	android-icon-36x36.png
	android-icon-48x48.png
	android-icon-72x72.png
	android-icon-96x96.png
	favicon-144x144.png
	favicon-168x168.png
	favicon-256x256.png
	favicon-32x32.png
	favicon-48x48.png
	favicon-512x512.png
	favicon-64x64.png
	favicon-96x96.png
	ms-icon-150x150.png
	ms-icon-310x310.png
	ms-icon-70x70.png
)
foreach (STONEYDSP_ICON_PNG IN LISTS STONEYDSP_ICONS_PNG)
    cmrc_add_resources (Icons

        WHENCE ${StoneyDSP_BINARY_DIR}/public/images
        PREFIX StoneyDSP/Icons

        ${StoneyDSP_BINARY_DIR}/public/images/favicon/${STONEYDSP_ICON_PNG}
    )
endforeach ()

set (STONEYDSP_ICONS_ICO "")
list (APPEND STONEYDSP_ICONS_ICO
	favicon__144x144.ico
	favicon__168x168.ico
	favicon__256x256.ico
	favicon__32x32.ico
	favicon__48x48.ico
	favicon__64x64.ico
	favicon__96x96.ico
)

foreach (STONEYDSP_ICON_ICO IN LISTS STONEYDSP_ICONS_ICO)
    cmrc_add_resources (Icons

        WHENCE ${StoneyDSP_BINARY_DIR}/public/images
        PREFIX StoneyDSP/Icons

        ${StoneyDSP_BINARY_DIR}/public/images/favicon/${STONEYDSP_ICON_ICO}
    )
endforeach ()

if (UNIX)
    set_target_properties (Icons
        PROPERTIES
        POSITION_INDEPENDENT_CODE ON
    )
endif()
