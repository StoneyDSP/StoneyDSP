/**
 * @file catch2session.cpp
 * @author StoneyDSP (nathanjhood@googlemail.com)
 * @copyright Copyright (c) 2025
 *
 */

//==============================================================================

#include "catch2session.hpp"

//==============================================================================

#if defined(STONEYDSP_BUILD_TEST)

//==============================================================================

  #include <catch2/catch_session.hpp>

//==============================================================================

  #include "stoneydsp/stoneydsp.h"

//==============================================================================

  #include <iostream>
  #include <sstream>
  #include <string>
  #include <vector>

//==============================================================================

STONEYDSP_EXTERN_C_BEGIN
stoneydsp_test_args stoneydspTestArgs = "";
STONEYDSP_EXTERN_C_END

//==============================================================================

int STONEYDSP_PUBLIC_FUNCTION
STONEYDSP_NAMESPACE_QUAL (stoneydsp::test) run ()
{

  // Create Catch2 session
  Catch::Session session;

  // Parse stoneydspTestArgs
  ::std::istringstream iss (stoneydspTestArgs);

  // Parse stoneydspTestArgs into args
  ::std::vector< ::std::string> args;
  for (::std::string s; iss >> s;)
    args.push_back (s);

  // Parse stoneydspTestArgs into argv
  ::std::vector<const char *> argv;

  // name of entry point (plus a buffer)
  argv.push_back (::std::string ("main").data ());

  // Arg stream
  for (const auto &arg : args)
    argv.push_back (arg.c_str ());
  argv.push_back (nullptr);

  // Apply command line
  int returnCode = session.applyCommandLine (args.size () + 1, argv.data ());
  if (returnCode != 0)
    {
      // WARN("Catch2 command line error %d", returnCode);
      return returnCode;
    }

  // Run Catch2 tests
  int numFailed = session.run ();
  return numFailed;
}

//==============================================================================

#endif // defined (STONEYDSP_BUILD_TEST)

//=========================================================================//EOF
