# Build requirements

StoneyDSP's canonical build/package definition is CMake and its checked-in
presets. The Makefile is a useful command facade and fallback, but not the
authority for install/export claims.

## Required for the supported CMake path

- a C11-capable C compiler;
- a C++11-capable C++ compiler;
- CMake 3.23 or newer;
- Ninja, as selected by the checked-in presets;
- Git and the repository submodules, including vcpkg.

The active CI covers Clang/GCC environments where available and MSVC x86/x64
on Windows. A named preset being present is not equivalent to a continuously
tested production target; consult the workflows and current CI before making a
support claim.

## Optional tools

- GNU Make for the convenience command surface and legacy native test path;
- vcpkg, normally supplied by the repository submodule or a deliberately
  configured external installation;
- Doxygen for `make doc`;
- platform symbol tools when validating shared-library visibility.

`make version-check` requires Node.js because the version protocol synchronises
the CMake/vcpkg/package manifests with a checked-in script.
