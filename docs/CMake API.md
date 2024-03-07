# The StoneyDSP CMake API

Adapted directly from the [JUCE CMake API](https://raw.githubusercontent.com/juce-framework/JUCE/master/docs/CMake%20API.md) until further developed. Please refer to the JUCE CMake API for general queries; we simply provide a few of the same options within our own namespsace, allowing you to customize your configuration to best suit your usage requirements, using an identical interace while not interfering with your project's JUCE configuration.

## System Requirements

- All project types require CMake 3.22 or higher.
- See JUCE for platform-specific requirements (we adhere to those)

Most system package managers have packages for CMake, but we recommend using the most recent release
from https://cmake.org/download. You should always use a CMake that's newer than your build
toolchain, so that CMake can identify your build tools and understand how to invoke them.

In addition to CMake you'll need a build toolchain for your platform, such as Xcode, MSVC, or GNU with either a Makefile generator or Ninja.

## Getting Started

### Using `add_subdirectory`

The simplest way to include StoneyDSP in your project is to add StoneyDSP as a
subdirectory of your project, and to include the line `add_subdirectory(StoneyDSP)`
in your project CMakeLists.txt. This will make the StoneyDSP targets and helper
functions available for use by your custom targets.

### Using `find_package`

To install StoneyDSP globally on your system, you'll need to tell CMake where to
place the installed files.

    # Go to StoneyDSP directory
    cd /path/to/clone/StoneyDSP
    # Configure build with library components only
    cmake -B cmake-build-install -DCMAKE_INSTALL_PREFIX=/path/to/StoneyDSP/install
    # Run the installation
    cmake --build cmake-build-install --target install

In your project which consumes StoneyDSP, make sure the project CMakeLists.txt contains the line
`find_package(StoneyDSP CONFIG REQUIRED)`. This will make the StoneyDSP modules and CMake helper functions
available for use in the rest of your build. Then, run the build like so:

    # Go to project directory
    cd /path/to/my/project
    # Configure build, passing the StoneyDSP install path you used earlier
    cmake -B cmake-build -DCMAKE_PREFIX_PATH=/path/to/StoneyDSP/install
    # Build the project
    cmake --build cmake-build

### Example projects

In the StoneyDSP/examples/CMake directory, you'll find example projects for a GUI app, a console app,
and an audio plugin. You can simply copy one of these subdirectories out of the StoneyDSP repo, add StoneyDSP
as a submodule, and uncomment the call to `add_subdirectory` where indicated in the CMakeLists.txt.
Alternatively, if you've installed StoneyDSP using a package manager or the CMake install target, you can
uncomment the call to `find_package`.

Once your project is set up, you can generate a build tree for it in the normal way. To get started,
you might invoke CMake like this, from the new directory you created.

    cmake -Bbuild (-GgeneratorName) (-DSTONEYDSP_BUILD_EXTRAS=ON) (-DSTONEYDSP_BUILD_EXAMPLES=ON)

This will create a build tree in a directory named 'build', using the CMakeLists in the current
working directory, using the default generator (makefiles on mac/linux, and the most recent Visual
Studio on Windows). You can choose a specific generator to use with the `-G` flag (call `cmake -G`
to see a full list of generators on your platform). If you included StoneyDSP as a subdirectory, you can
enable the Extras and Examples targets by including the last two arguments (they're off by default).
There's currently not a lot of example projects, so generating project files might not take a much longer when
these options are on, but you probably won't want to include them most of the time.

Then, to build the project:

    cmake --build build (--target targetNameFromCMakeLists) (--config Release/Debug/...)

This tells cmake to build the target named `targetNameFromCMakeLists`, in the specified
configuration, using the appropriate tool. Of course, if you generated makefiles or ninja files, you
could call `make` or `ninja` in the build directory. If you generated an IDE project, like an Xcode
or Visual Studio project, then you could open the generated project in your IDE.

## API Reference

### Options

These flags can be enabled or disabled to change the behaviour of parts of the StoneyDSP build.

These options would normally be configured by either:
- Supplying an option in the form `-DNAME_OF_OPTION=ON/OFF` to the initial CMake configuration call,
  or
- Calling `set(NAME_OF_OPTION ON/OFF)` before including StoneyDSP in your project via `add_subdirectory`
  or `find_package`.

#### `STONEYDSP_BUILD_EXTRAS`

This controls whether targets are added for the projects in the 'extras' folder, such as the
Icons and Resources targets. This is off by default, because you probably won't need these targets (these are mostly for internal use, but you can see how and what they each do).

#### `STONEYDSP_BUILD_EXAMPLES`

This controls whether targets are added for the projects in the 'examples' folder, such as the
Biquads Audio Plugin and the Curl Console App. This is off by default, because you probably won't need these targets if you've
included StoneyDSP in your own project.

#### `STONEYDSP_MODULES_ONLY`

Only brings in targets for the built-in STONEYDSP modules, and the `stoneydsp_*` CMake functions.
This is meant for highly custom use-cases where the `juce_add_gui_app` and `juce_add_plugin`
functions are not required. Most importantly, the 'stoneyhelper' helper tool is not built when this
option is enabled, which may improve build times for established products that use other methods to
handle plugin bundle structures, icons, plists, and so on.
