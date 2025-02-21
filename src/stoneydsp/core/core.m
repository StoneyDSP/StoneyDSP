/**
 * @file stoneydsp.m
 * @author StoneyDSP (nathanjhood@googlemail.com)
 * @copyright Copyright (c) 2025
 *
 */

//==============================================================================

/// TODO: this seems like a loaded filename to try to include...
/// Perhaps this instance is ok, but it's a bad pattern - what if we have a
/// `file.cpp`? Too much room for clashes with things like system files...

#include "core.c" // only here and Mississipi

// project tree should probably be fully qualified with project namespace because
// we need to use file-based look up (double quotes) while *not* clashing
// with any files in the system, which the compiler *might* look up instead
// of our files with loaded filenames!

//=========================================================================//EOF
