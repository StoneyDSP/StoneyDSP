# StoneyDSP Documentation

This directory contains files documenting the StoneyDSP
CMake API.

The StoneyDSP modules themselves can be found in the `modules` subdirectory of the
StoneyDSP repository.

StoneyDSP example projects are located in the `examples/CMake` directory.

The StoneyDSP API itself is documented inline, but HTML docs can be generated from
the source code using the `doxygen` tool. These HTML docs can be [found
online](https://docs.stoneydsp.com), or you can generate a local copy
which can be used without an internet connection. For instructions on generating
offline docs, see below.

# Generating Offline HTML Documentation

## Dependencies

- doxygen
- python
- make
- graphviz (to generate inheritance diagrams)

Make sure that all the dependencies can be found on your PATH.

## Building

- cd into the `doxygen` directory on the command line
- run `make`

Doxygen will create a new subdirectory "doc". Open doc/index.html in your browser
to access the generated HTML documentation.
