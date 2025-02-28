# StoneyDSP

The StoneyDSP audio Library.

---
[![windows](https://github.com/StoneyDSP/StoneyDSP/actions/workflows/windows-latest.yml/badge.svg)](https://github.com/StoneyDSP/StoneyDSP/actions/workflows/windows-latest.yml)
[![macos](https://github.com/StoneyDSP/StoneyDSP/actions/workflows/macos-latest.yml/badge.svg)](https://github.com/StoneyDSP/StoneyDSP/actions/workflows/macos-latest.yml)
[![ubuntu](https://github.com/StoneyDSP/StoneyDSP/actions/workflows/ubuntu-latest.yml/badge.svg)](https://github.com/StoneyDSP/StoneyDSP/actions/workflows/ubuntu-latest.yml)

---

StoneyDSP is an audio Digital Signal Processing (DSP) library with isometric support for C, C++, and other C-like languages, across a wide range of target platforms, architectures, and toolchains; additional features include interfaces for popular audio programming targets including VST, AU, and even VCV Rack, as well as as extensions and utilities such as a CMake API, JUCE module support, vcpkg integration, and NodeJS Binary Addon bindings to Javascript/Typescript.*

_*please note that we are under construction; some of these features are planned, experimental, or only partially implemented as of writing._

## Contents

- [Quickstart]
- [Requirements]
- [Building]
  - [Make]
  - [CMake]
  - [Presets](#presets)
  - [Workflows](#workflows)
- [Features](#features)
  - [core](#core)
  - [simd](#simd)
  - [dsp](#dsp)
  - [test](#test)
  - [doc](#doc)
- [FAQ](#faq)
- [License](#license)
- [Acknowledgements]

## Quickstart

Clone StoneyDSP:

```sh
$ git clone git@github.com:StoneyDSP/StoeyDSP:git && cd StoneyDSP
```

Build with GNU Make:

```sh
$ make
```

Or build with CMake:

```sh
$ cmake -S . -B ./build
```

## Requirements

TODO

## Building

TODO

- ### Make

  TODO

- ### CMake

  TODO

- ### Presets

  When building StoneyDSP from source, we provide an extensive set of curated CMake Presets for a simplified, streamlined workflow.

  CMake presets provide multiple possible actions - configure, build, test, package, and so forth - and also the ability to chain these actions together into a "workflow".

  For example, configuring the CMake project for 64-bit Linux platforms in "Release" mode with extra logging enabled is as easy as:

  ```sh
  $ cmake --preset x64-linux-release-verbose
  ```

  Our CMake Presets are specified as: `<arch>-<platform>-<mode>[-<option>]`

  Where `<arch>` may be any of:

  - `x86` (32-bit machines)
  - `x64` (64-bit machines)
  - `arm64` (ARM machines)

  Where `<platform>` may be any of:

  - `windows`
  - `osx`
  - `linux`

  Where `<mode>` may be any of:

  - `release`
  - `debug`

  Where `[-option]` may be unspecified, or any of:

  - `verbose`

  CMake, CTest, and CPack all respond appropriately to the various preset combinations available. The entire set of actions, demonstrated with the example preset as before, is as follows:

  CMake configure with a preset:

  ```sh
  $ cmake --preset x64-linux-release-verbose
  ```

  CMake re-configure with a preset:

  ```sh
  $ cmake --preset x64-linux-release-verbose --fresh
  ```

  CMake build with a prest:

  ```sh
  $ cmake --build ./build --preset x64-linux-release-verbose
  ```

  CTest test with a preset:

  ```sh
  $ ctest --test-dir ./build --preset x64-linux-release-verbose
  ```

  CMake package the build tree with a preset (calls CPack underneath):

  ```sh
  $ cmake --build ./build --preset x64-linux-release-verbose --target package
  ```

  CMake package the source tree with a preset (calls CPack underneath):

  ```sh
  $ cmake --build ./build --preset x64-linux-release-verbose --target package_source
  ```

  *NOTE:* Our presets all use Ninja as a generator to ensure cross-compatibility and reduce complexity.

  Not all platform and architecture combinations are currently supported; here is a summary of what we guarantee as of writing:

  ```txt
  // windows
  "x86-windows-debug"
  "x86-windows-release"
  "x86-windows-debug-verbose"
  "x86-windows-release-verbose"

  "x64-windows-debug"
  "x64-windows-release"
  "x64-windows-debug-verbose"
  "x64-windows-release-verbose"

  // osx
  "x86-osx-debug"
  "x86-osx-release"
  "x86-osx-debug-verbose"
  "x86-osx-release-verbose"

  "x64-osx-debug"
  "x64-osx-release"
  "x64-osx-debug-verbose"
  "x64-osx-release-verbose"

  "arm64-osx-debug"
  "arm64-osx-release"
  "arm64-osx-debug-verbose"
  "arm64-osx-release-verbose"

  // Linux
  "x86-linux-debug"
  "x86-linux-release"
  "x86-linux-debug-verbose"
  "x86-linux-release-verbose"

  "x64-linux-debug"
  "x64-linux-release"
  "x64-linux-debug-verbose"
  "x64-linux-release-verbose"
  ```

- ### Workflows

  StoneyDSP also provides workflows for all possible presets:

  ```sh
  $ cmake --preset x64-linux-release-verbose --workflow
  ```

  The workflows run the following steps in order:

  - configure
  - build
  - test
  - package build
  - package source

  To streamline this even further, we have implemented a platform look-up method in our Makefile, which automatically selects an appropriate preset for your host machine's platform and architecture, with additional options set as environment variables on the command line.

  In other words, if you are on a 64-bit Windows platform and just run:

  ```sh
  $ make workflow

  // x64-windows-release workflow is running...
  ```

  Our look-up mechanism will automatically select the `x64-windows-release` preset for you. This applies to all possible preset combinations on all platforms (not only 64-bit Windows).

  Additionally, if you wish to run the workflow - or any preset - in `Debug` mode - with the compiler generating debugger symbols, some helpful additional logging, and other expected "debugging" behaviours, just prepend `DEBUG=1` to the same command:

  ```sh
  $ DEBUG=1 make workflow

  // x64-windows-debug workflow is running...
  ```

  In addition to the standard `DEBUG` environment workflows and our presets respond similarly to `VERBOSE=1` for enabling gratuituous logging to the console by selecting a `-verbose` option from the presets list:

  ```sh
  $ VERBOSE=1 make workflow

  // x64-windows-release-verbose workflow is running...
  ```

  Of course, both flags can be combined to access the final variant:

  ```sh
  $ DEBUG=1 VERBOSE=1 make workflow

  // x64-windows-debug-verbose workflow is running...
  ```

## Features

- ### core

  The core features and functionalities of StoneyDSP.

  This feature is `ON` by default.

- ### simd

  SIMD data types for optimized performance.

- ### dsp

  The DSP (digital signal processing) features and functionalities of StoneyDSP.

- ### test

	Unit-tests with Catch2.

  This feature is only available when building StoneyDSP from source (it is not part of our distribution build), and is `OFF` by default.

- ### doc

	Documentation with Doxygen.

  This feature is only available when building StoneyDSP from source (it is not part of our distribution build), and is `OFF` by default.

## FAQ

TODO

## License

Copyright (C) 2024 Nathan J. Hood <nathanjhood@googlemail.com> MIT License.

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

1. The origin of this source code must not be misrepresented; you must not
  claim that you wrote the original source code. If you use this source code
  in a product, an acknowledgment in the product documentation would be
  appreciated but is not required.

2. Altered source versions must be plainly marked as such, and must not be
  misrepresented as being the original source code.

3. This notice may not be removed or altered from any source distribution.

For more information, visit the website:
[www.stoneydsp.com](https://www.stoneydsp.com)

FULL STONEYDSP TERMS:
- [STONEYDSP END-USER LICENSE AGREEMENT](https://www.stoneydsp.com/licence)
- [STONEYDSP PRIVACY POLICY](https://www.stoneydsp.com/privacy-policy)

## Acknowledgements

TODO
