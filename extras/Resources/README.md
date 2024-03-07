# StoneyDSP::Resources

This is primarily an internal project, designed to utilize a single set of binary resources as a CMake target, which can be shared around with the rest of the ```StoneyDSP``` library installation, providing a suite of metadata and other objects to all of the other targets in the ```StoneyDSP``` installation. This target will also likely be exported into the form of a Napi Addon for the NodeJS runtime, allowing us to consume this library elsewhere, such as our webpages and other external projects.

It might also serve as a useful example project for resource-compiler targets and their uses.

Currently, the ```Resources``` project codebase is essentially a placeholer or a dummy target. This codebase has been added to the build now because we need some targets to validate our library as early as possible, to ensure that no configuration issues shall arise later on. The functionality given shall be derived partially from the ```StoneyDSP``` library itself, providing a means of self-testing as well as consistent behaviour. Since ```Resources``` is a sub-project of ```StoneyDSP```, it will likely recieve it's own version number, and possibly be moved into a git submodule, in due course.
