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

vcpkg_from_github(
    OUT_SOURCE_PATH SOURCE_PATH
    REPO StoneyDSP/StoneyDSP
    #REF Link-3.0.6
    #SHA512 7dd811d3b7792722a8754cd0875777b8cf4902a0babff2822a6fd997137eb5feac576263169c71fca24358189e56b5106a32ae1313b33fb6148eb845691a6438
    HEAD_REF master
    #PATCHES
        #replace_local_asiostandalone_by_vcpkg_asio.patch
        #replace_asiosdk_download_by_vcpkg_asiosdk.patch
        #replace_local_catch_by_vcpkg_catch2.patch
        #no-werror.patch
)

vcpkg_cmake_configure(
    SOURCE_PATH "${SOURCE_PATH}"
    #OPTIONS
        #-DNEED_CATCH2=${NEED_CATCH2}
        #-DLINK_BUILD_ASIO=${NEED_ASIOSDK}
)

# We must not correct the CMake include path before build
vcpkg_apply_patches(
    SOURCE_PATH "${SOURCE_PATH}"
    PATCHES
        correct_cmake_include_directory.patch
)

file(INSTALL "${SOURCE_PATH}/StoneyDSPConfig.cmake" DESTINATION "${CURRENT_PACKAGES_DIR}/share/${PORT}/")
file(INSTALL "${SOURCE_PATH}/cmake_include/" DESTINATION "${CURRENT_PACKAGES_DIR}/share/${PORT}/cmake_include/")
file(INSTALL "${SOURCE_PATH}/include/" DESTINATION "${CURRENT_PACKAGES_DIR}/include" PATTERN "CMakeLists.txt" EXCLUDE)

# Handle copyright
file(INSTALL "${SOURCE_PATH}/LICENSE" DESTINATION "${CURRENT_PACKAGES_DIR}/share/${PORT}" RENAME copyright)
