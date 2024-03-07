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

# ==================================================================================================
# StoneyDSP Modules Support Helper Functions
#
# In this file, functions intended for use by end-users have the prefix `stoneydsp_`.
# Functions beginning with an underscore should be considered private and susceptible to
# change, so don't call them directly.
#
# See the readme at
# `https://github.com/juce-framework/JUCE/blob/master/docs/CMake API.md` for
# more information about CMake usage, including documentation of the public
# functions in this file.
# ==================================================================================================

include_guard(GLOBAL)
cmake_minimum_required(VERSION 3.22)

# ==================================================================================================

set(STONEYDSP_CMAKE_UTILS_DIR ${CMAKE_CURRENT_LIST_DIR} CACHE INTERNAL "The path to the folder holding this file and other resources")
