#include "main.h"

constexpr auto _int_max = INT_MAX;
constexpr auto _argc_min = 1;
constexpr auto _argc_max = _int_max;

void STONEYDSP_PUBLIC_FUNCTION
stoneydsp::run ()
{
  return;
}

int
main (int argc, char *argv[])
{

  // #ifdef STONEYDSP_DEBUG
  //   // Perform any necessary initialization
  //   allocationMap.clear(); // Ensure the allocation map is initialized and
  //   empty

  //   // Now set the flag to use custom new and delete operators
  //   ::custom_new_initialized = true;
  // #endif // STONEYDSP_DEBUG

  if ((argc < _argc_min) || (argc > _argc_max))
    {
      std::cerr << "wrong number of args: " << argc << std::endl;
      return EXIT_FAILURE;
    }

  // Ensure argc is within valid range (though this check is usually
  // unnecessary)
  const int args = argc;

  // Loop using 'int' for consistency with argc
  for (int i = 0; i < args; ++i)
    {
      if (i > 0)
        { // skip arg0
          std::cout << "argv[" << i << "] = " << argv[i] << std::endl;
          // ::stoneydspArgs += " ";
          // ::stoneydspArgs += argv[i];
        }
    }

  ::stoneydsp::run ();

  return EXIT_SUCCESS;
}

#if defined(STONEYDSP_SUPPORTS_WIDECHARS) && defined(UNICODE)

/**
 * @brief UTF-16 to UTF-8 wrapper for Windows with unicode.
 *
 * @param argc
 * @param wargv
 * @return int
 */
int
wmain (int argc, wchar_t *wargv[])
{

  // Convert wchar_t* arguments to char* arguments
  ::std::vector< ::std::string> args;

  for (int i = 0; i < argc; ++i)
    {
      // push wargv to a wide string
      ::std::wstring ws (wargv[i]);
      // push the wide string to a regular string
      ::std::string s (ws.begin (), ws.end ());
      // use the regular string to call main
      args.push_back (s);
    }

  // Create a char* array for main()
  ::std::vector<char *> argv;

  for (auto &arg : args)
    {
      argv.push_back (&arg[0]);
    }
  argv.push_back (nullptr); // Null-terminate the array

  // Call main() with the converted arguments
  return main (argc, argv.data ());
}

#endif // defined (STONEYDSP_SUPPORTS_WIDECHARS) && defined (UNICODE)
