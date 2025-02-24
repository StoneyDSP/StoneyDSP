#include "main.h"

static const int _int_max = INT_MAX;
static const int _argc_min = 1;
static const int _argc_max = _int_max;

void STONEYDSP_PUBLIC_FUNCTION
stoneydsp_run ()
{
  stoneydsp_int8_t t;

  printf ("%s", stoneydsp_version);

  return;
}

int
main (int argc, char *argv[])
{
  if ((argc < _argc_min) || (argc > _argc_max))
    {
      printf ("%s: %i", "wrong number of args", argc);
      return EXIT_FAILURE;
    }

  // Ensure argc is within valid range (though this check is usually
  // unnecessary)
  const stoneydsp_int_t args = (stoneydsp_int_t)argc;

  // Loop using 'int' for consistency with argc
  for (stoneydsp_int_t i = 0; i < args; ++i)
    {
      if (i > 0)
        { // skip arg0
          printf ("argv[%i] = %s", i, argv[i]);
          // ::stoneydspArgs += " ";
          // ::stoneydspArgs += argv[i];
        }
    }

  stoneydsp_run ();

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

  // // Convert wchar_t* arguments to char* arguments
  // ::std::vector< ::std::string> args;

  // for (int i = 0; i < argc; ++i)
  //   {
  //     // push wargv to a wide string
  //     ::std::wstring ws (wargv[i]);
  //     // push the wide string to a regular string
  //     ::std::string s (ws.begin (), ws.end ());
  //     // use the regular string to call main
  //     args.push_back (s);
  //   }

  // // Create a char* array for main()
  // ::std::vector<char *> argv;

  // for (auto &arg : args)
  //   {
  //     argv.push_back (&arg[0]);
  //   }
  // argv.push_back (nullptr); // Null-terminate the array

  // // Call main() with the converted arguments
  // return main (argc, argv.data ());
}

#endif // defined (STONEYDSP_SUPPORTS_WIDECHARS) && defined (UNICODE)
