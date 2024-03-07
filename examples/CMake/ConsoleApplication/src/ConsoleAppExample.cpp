#include <stoneydsp_core/stoneydsp_core.h>

int main (int argc, char* argv[])
{
    StoneyDSP::Application::ConsoleApplication consoleApplication;

    consoleApplication.print_help();

    // Your code goes here!
    StoneyDSP::ignoreUnused(argc, argv);

    return EXIT_SUCCESS;
}
