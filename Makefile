####################################################<<<-Initialization and Setup

## Default target executed when no arguments are given to make.
default_target: all
.PHONY : default_target

# ## Allow only one "make -f Makefile2" at a time, but pass parallelism.
# .NOTPARALLEL:

## Save temps without passing `-save-temps`
.SECONDARY:

## The shell in which to execute make rules.
SHELL := /bin/sh
ECHO := echo

## Compilers and tools
CC := cc
CXX := c++
CPP := $(CXX) -E
ASM := $(CXX) -S
AR := ar
LD ?= ld
GDB ?= gdb
OBJCOPY ?= objcopy

CMAKE := cmake
CTEST := ctest
CPACK := cpack

GIT := git
ZIP := zip
UNZIP := unzip
XXD := xxd
MD5SUM := md5sum
SHA1SUM := sha1sum
HASH_ALGORITHM ?= $(XXD)
PKG_CONFIG ?= pkg-config

CPP_LINT ?= clang-format
CPP_TIDY ?= clang-tidy

## Get the directory of the Makefile
MAKEFILE_DIR := $(patsubst %/,%,$(dir $(realpath $(firstword $(MAKEFILE_LIST)))))

SOURCES :=
OBJECTS :=
INCLUDES :=

## Verbosity control.
##
## example:
##     $(Q)mkdir build
##
VERBOSE ?=
ifeq ($(VERBOSE),1)
    Q :=
else
    Q := @
endif

ifdef CROSS_COMPILE
	MACHINE := $(CROSS_COMPILE)
else
	MACHINE ?= $(shell $(CC) -dumpmachine)
endif

ifneq (,$(findstring i686-,$(MACHINE)))
	ARCH_X86 := 1
	ARCH_CPU := x86
else ifneq (,$(findstring x86_64-,$(MACHINE)))
	ARCH_X64 := 1
	ARCH_CPU := x64
else ifneq (,$(findstring arm64-,$(MACHINE)))
	ARCH_ARM64 := 1
	ARCH_CPU := arm64
else ifneq (,$(findstring aarch64-,$(MACHINE)))
	ARCH_ARM64 := 1
	ARCH_CPU := arm64
else
$(error Could not determine CPU architecture of $(MACHINE))
endif

ifneq (,$(findstring -darwin,$(MACHINE)))
	ARCH_MAC := 1
	ARCH_OS := mac
else ifneq (,$(findstring -mingw32,$(MACHINE)))
	ARCH_WIN := 1
	ARCH_OS := win
else ifneq (,$(findstring -windows,$(MACHINE)))
	ARCH_WIN := 1
	ARCH_OS := win
else ifneq (,$(findstring -linux,$(MACHINE)))
	ARCH_LIN := 1
	ARCH_OS := lin
else
$(error Could not determine operating system of $(MACHINE))
endif

ARCH_NAME = $(ARCH_OS)-$(ARCH_CPU)

ifdef ARCH_X86
	TRIPLET_ARCH := x86
	PRESET_ARCH := x86
endif

ifdef ARCH_X64
	TRIPLET_ARCH := x64
	PRESET_ARCH := x64
endif

ifdef ARCH_ARM64
	TRIPLET_ARCH := arm64
	PRESET_ARCH := arm64
endif

ifdef ARCH_WIN
	TRIPLET_OS := mingw-dynamic
	PRESET_OS := windows
endif

ifdef ARCH_LIN
	TRIPLET_OS := linux
	PRESET_OS := linux
endif

ifdef ARCH_MAC
	TRIPLET_OS := osx
	PRESET_OS := osx
endif

## 1. Accepts a 'BUILD_TYPE=' argument when configuring (supports 'debug' or 'release')
## 2. Lookup the 'DEBUG' env var if no 'BUILD_TYPE=' was specified.
## 3. If 'DEBUG' was set, build in 'debug' mode; otherwise, defaults to 'release'.
## 4. Lookup the 'VERBOSE' env var; if set, append '-verbose' to the preset.
ifdef BUILD_TYPE
	PRESET_CONFIG := $(BUILD_TYPE)
else ifdef DEBUG
	PRESET_CONFIG := debug
else
	PRESET_CONFIG := release
endif

ifdef VERBOSE
	PRESET_VERBOSE := -verbose
endif

## The deduced CMake Preset name.
PRESET ?= $(PRESET_ARCH)-$(PRESET_OS)-$(PRESET_CONFIG)$(PRESET_VERBOSE)

## This target reports the automatically-selected CMake Preset to stdout.
preset:
	@echo $(PRESET)
.PHONY: preset

###########################################<<<-Standards, Flags, and Directories

## Standards
C_STANDARD ?= 11
CXX_STANDARD ?= 14

ifdef USE_GNU_EXTENSIONS
	C_DIALECT := gnu
	CXX_DIALECT := gnu
else
	C_DIALECT := c
	CXX_DIALECT := c++
endif

C_STANDARD_FLAG += -std=$(C_DIALECT)$(C_STANDARD)
CXX_STANDARD_FLAG += -std=$(CXX_DIALECT)$(CXX_STANDARD)

## Optional debugger symbols
ifdef DEBUG
	ASMFLAGS += -g
endif

## -O0: No optimization. This is the default level. It aims for the fastest compilation time and the best debugging experience.
## -O1: Basic optimization. Enables optimizations that do not involve a space-speed tradeoff.
## -O2: Further optimization. More optimizations are enabled that improve performance without significantly increasing the compilation time.
## -O3: Aggressive optimization. It enables more aggressive optimizations that may increase the compilation time but aim to maximize the performance of the generated code.
## -Os: Optimize for size. Enables all -O2 optimizations that do not typically increase code size and enables further optimizations to reduce code size.
## -Ofast: Disregards strict standards compliance for the sake of optimization. Enables all -O3 optimizations along with other aggressive optimizations.
OPTIMIZATION ?= -O0
ASMFLAGS += $(OPTIMIZATION)

## Warnings and errors
FLAGS += -Wall
FLAGS += -Wextra
FLAGS += -Werror

ifdef VERBOSE
	FLAGS += -v
endif

ifdef DEBUG
	FLAGS += -Wno-unused-parameter
	FLAGS += -pedantic
else ifdef VERBOSE
	FLAGS += -Wno-unused-parameter
	FLAGS += -pedantic
endif

# In theory, we could leave -fPIC in place, since non-POSIX users are almost
# definitely MSVC users, who likely aren't using this Makefile anyway...
FLAGS += -fPIC
# FLAGS += -save-temps

# Generate dependency files alongside the object files
CPPFLAGS += -MMD
CPPFLAGS += -MP
# CPPFLAGS += -fmacro-prefix-map=$(BUILD_DIR)/include=include
# CPPFLAGS += -fmacro-prefix-map=$(BUILD_DIR)/src=src
# CPPFLAGS += -fmacro-prefix-map=$(BUILD_DIR)/test=test

#####################################################<<<-Source and Object Files

## Directories
BUILD_DIR := build
DOC_DIR := doc
SRC_DIR := src
TEST_DIR := test
INCLUDE_DIR := $(BUILD_DIR)/include

## Source files
CORE_SRCS := $(wildcard $(SRC_DIR)/stoneydsp/core/core.cpp)
DSP_SRCS := $(wildcard $(SRC_DIR)/stoneydsp/dsp/dsp.cpp)
SIMD_SRCS := $(wildcard $(SRC_DIR)/stoneydsp/simd/simd.cpp)
LIB_SRCS := $(wildcard $(SRC_DIR)/stoneydsp/stoneydsp.cpp)

## Object files
CORE_OBJS := $(CORE_SRCS:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/src/%.cpp.o)
DSP_OBJS := $(DSP_SRCS:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/src/%.cpp.o)
SIMD_OBJS := $(SIMD_SRCS:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/src/%.cpp.o)
LIB_OBJS := $(LIB_SRCS:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/src/%.cpp.o)

## Dep files
CORE_DEPS := $(CORE_OBJS:.o=.d)
DSP_DEPS := $(DSP_OBJS:.o=.d)
SIMD_DEPS := $(SIMD_OBJS:.o=.d)
LIB_DEPS := $(LIB_OBJS:.o=.d)

###################################################<<<-Feature Flags and Targets

## Library type
BUILD_SHARED ?= 1
ifeq ($(BUILD_SHARED),1)
	DEFINES += -DSTONEYDSP_BUILD_SHARED=$(BUILD_SHARED)
	ifdef ARCH_WIN
		LIB_EXT := dll
	else
		LIB_EXT := so
	endif
	BUILD_SHARED_FLAG := -shared
else
	LIB_EXT := a
	BUILD_SHARED_FLAG :=
endif

## TODO: The macro NDEBUG controls whether assert() statements are active or not.
ifdef DEBUG
	# DEFINES += -DDEBUG # consider Windows MSVC...
	DEFINES += -D_DEBUG
else
	DEFINES += -DNDEBUG
endif

## Feature flags
EXPERIMENTAL ?= 0
BUILD_CORE ?= 1
BUILD_DSP ?= 0
BUILD_SIMD ?= 0

ifeq ($(EXPERIMENTAL),1)
	DEFINES += -DSTONEYDSP_EXPERIMENTAL=$(EXPERIMENTAL)
endif
ifeq ($(BUILD_CORE),1)
	SOURCES += $(CORE_SRCS)
	OBJECTS += $(CORE_OBJS)
	DEPS += $(CORE_DEPS)
	DEFINES += -DSTONEYDSP_BUILD_CORE=$(BUILD_CORE)
endif
ifeq ($(BUILD_DSP),1)
	SOURCES += $(DSP_SRCS)
	OBJECTS += $(DSP_OBJS)
	DEPS += $(DSP_DEPS)
	DEFINES += -DSTONEYDSP_BUILD_DSP=$(BUILD_DSP)
endif
ifeq ($(BUILD_SIMD),1)
	SOURCES += $(SIMD_SRCS)
	OBJECTS += $(SIMD_OBJS)
	DEPS += $(SIMD_DEPS)
	DEFINES += -DSTONEYDSP_BUILD_SIMD=$(BUILD_SIMD)
endif

## Optional test objects
ifeq ($(BUILD_TEST),1)
	TEST_SRCS :=
	ifeq ($(BUILD_CORE),1)
		# TEST_SRCS += $(wildcard $(TEST_DIR)/stoneydsp/core/*.test.cpp)
		TEST_SRCS += $(wildcard $(TEST_DIR)/stoneydsp/core/types/*.test.cpp)
		# TEST_SRCS += $(wildcard $(TEST_DIR)/stoneydsp/core/core.test.cpp)
	endif
	ifeq ($(BUILD_SIMD),1)
	endif
	ifeq ($(BUILD_DSP),1)
	endif
	TEST_TARGET := $(BUILD_DIR)/test/main
	TEST_SRCS += $(wildcard $(TEST_DIR)/catch2session.test.cpp)
	TEST_SRCS += $(wildcard $(TEST_DIR)/utils.test.cpp)
	TEST_SRCS += $(wildcard $(TEST_DIR)/main.test.cpp)
	TEST_OBJS := $(TEST_SRCS:$(TEST_DIR)/%.test.cpp=$(BUILD_DIR)/test/%.test.cpp.o)
	TEST_DEPS := $(TEST_OBJS:.o=.d)
	DEFINES += -DSTONEYDSP_BUILD_TEST=$(BUILD_TEST)
endif

## Always include the library source (and last, so translation units arte ordered)
SOURCES += $(LIB_SRCS)
OBJECTS += $(LIB_OBJS)
INCLUDES += -I$(INCLUDE_DIR)

##########################################<<<-Dependencies and submodule targets

GIT_REF ?= $(strip $(shell $(GIT) rev-parse --short HEAD))

STONEYDSP_VERSION_MAJOR ?= 0
STONEYDSP_VERSION_MINOR ?= 0
STONEYDSP_VERSION_PATCH ?= $(strip $(shell $(GIT) rev-list HEAD | wc -l))
STONEYDSP_VERSION_TWEAK ?= $(strip $(shell $(ECHO) -n $(GIT_REF) | $(HASH_ALGORITHM) -p))
STONEYDSP_VERSION_BUILD ?= $(strip $(shell $(GIT) rev-parse --short HEAD))
STONEYDSP_VERSION ?= $(STONEYDSP_VERSION_MAJOR).$(STONEYDSP_VERSION_MINOR).$(STONEYDSP_VERSION_PATCH).$(STONEYDSP_VERSION_TWEAK)

DEFINES += -DSTONEYDSP_VERSION_MAJOR="$(STONEYDSP_VERSION_MAJOR)"
DEFINES += -DSTONEYDSP_VERSION_MINOR="$(STONEYDSP_VERSION_MINOR)"
DEFINES += -DSTONEYDSP_VERSION_PATCH="$(STONEYDSP_VERSION_PATCH)"
DEFINES += -DSTONEYDSP_VERSION_TWEAK="$(STONEYDSP_VERSION_TWEAK)"
DEFINES += -DSTONEYDSP_VERSION="$(STONEYDSP_VERSION)"

version-major:
	@echo $(STONEYDSP_VERSION_MAJOR)
.PHONY: version-major

version-minor:
	@echo $(STONEYDSP_VERSION_MINOR)
.PHONY: version-minor

version-patch:
	@echo $(STONEYDSP_VERSION_PATCH)
.PHONY: version-patch

version-tweak:
	@echo $(STONEYDSP_VERSION_TWEAK)
.PHONY: version-tweak

version-build:
	@echo $(STONEYDSP_VERSION_BUILD)
.PHONY: version-build

version:
	@echo $(STONEYDSP_VERSION)
.PHONY: version

version-package:
	@echo $(STONEYDSP_VERSION_MAJOR).$(STONEYDSP_VERSION_MINOR).$(STONEYDSP_VERSION_PATCH)-r$(STONEYDSP_VERSION_BUILD)
.PHONY: version-package

version-all: version-major version-minor version-patch version-tweak
	@echo $(STONEYDSP_VERSION)
	@echo $(STONEYDSP_VERSION_MAJOR).$(STONEYDSP_VERSION_MINOR).$(STONEYDSP_VERSION_PATCH)-r$(STONEYDSP_VERSION_BUILD)
.PHONY: version-all

.git/modules:
	@$(GIT) submodule update --init --recursive

.git/modules/dep: .git/modules

## Fetch submodules
.git/modules/dep/vcpkg: .git/modules/dep

## Bootstrap vcpkg
dep/vcpkg/bootstrap-vcpkg.sh: .git/modules/dep/vcpkg
	@$(GIT) submodule update --init --recursive

## Use vcpkg
dep/vcpkg/vcpkg: dep/vcpkg/bootstrap-vcpkg.sh

VCPKG_ROOT ?= dep/vcpkg
VCPKG := $(VCPKG_ROOT)/vcpkg

ifdef DEBUG
	LIB_CATCH := Catch2d
	LIB_CATCH_PATH := $(BUILD_DIR)/vcpkg_installed/$(TRIPLET_ARCH)-$(TRIPLET_OS)/debug/lib
	# PKG_CONFIG_PATH +=$(BUILD_DIR)/vcpkg_installed/$(TRIPLET_ARCH)-$(TRIPLET_OS)/debug/lib/pkgconfig
else
	LIB_CATCH := Catch2
	LIB_CATCH_PATH := $(BUILD_DIR)/vcpkg_installed/$(TRIPLET_ARCH)-$(TRIPLET_OS)/lib
	# PKG_CONFIG_PATH +=$(BUILD_DIR)/vcpkg_installed/$(TRIPLET_ARCH)-$(TRIPLET_OS)/lib/pkgconfig
endif

ifeq ($(BUILD_TEST),1)
	LDFLAGS += -L$(LIB_CATCH_PATH)
	LDFLAGS += -l$(LIB_CATCH)
	INCLUDES += -I$(BUILD_DIR)/test
endif

INCLUDES += -I$(BUILD_DIR)/vcpkg_installed/$(TRIPLET_ARCH)-$(TRIPLET_OS)/include

##################################################<<<-CMake and workflow targets

CMAKE_ARGS ?=
CMAKE_ARGS += -DSTONEYDSP_BUILD_CORE:BOOL=$(BUILD_CORE)
CMAKE_ARGS += -DSTONEYDSP_BUILD_SIMD:BOOL=$(BUILD_SIMD)
CMAKE_ARGS += -DSTONEYDSP_BUILD_DSP:BOOL=$(BUILD_DSP)
CMAKE_ARGS += -DSTONEYDSP_BUILD_TEST:BOOL=$(BUILD_TEST)
CMAKE_ARGS += -DSTONEYDSP_BUILD_SHARED:BOOL=$(BUILD_SHARED)

reconfigure: dep/vcpkg/vcpkg
	@echo Reconfiguring with CMake...
	@VCPKG_ROOT=$(VCPKG_ROOT) $(CMAKE) \
	--preset $(PRESET) \
	--fresh $(CMAKE_ARGS)
	@echo Reconfigured with CMake.
.PHONY: reconfigure

configure: dep/vcpkg/vcpkg
	@echo Configuring with CMake...
	@VCPKG_ROOT=$(VCPKG_ROOT) $(CMAKE) \
	--preset $(PRESET) $(CMAKE_ARGS)
	@echo Configured with CMake.
.PHONY: configure

build: configure
	@echo Building with CMake...
	@$(CMAKE) \
	--build $(PWD)/build \
	--preset $(PRESET)
	@echo Built with CMake.
.PHONY: build

test: build
	@echo Testing with CTest...
	$(CTEST) \
	--test-dir $(PWD)/build \
	--preset $(PRESET)
	@echo Tested with CTest.
.PHONY: test

package: test
	@echo Packaging build tree with CPack...
	@$(CMAKE) \
	--build $(PWD)/build \
	--target $@
	@echo Packaged build tree with CPack.
.PHONY: package

package_source: test
	@echo Packaging source tree with CPack...
	@$(CMAKE) \
	--build $(PWD)/build \
	--target $@
	@echo Packaged source tree with CPack.
.PHONY: package_source

workflow: dep/vcpkg/vcpkg
	@echo Running workflow with CMake...
	@VCPKG_ROOT=$(VCPKG_ROOT) $(CMAKE) \
	--workflow \
	--preset $(PRESET) \
	--fresh
	@echo Ran workflow with CMake.
.PHONY: workflow

source: configure
	@$(CMAKE) \
	--install $(PWD)/build \
	--prefix $(PWD)/dist \
	--component $@
.PHONY: source

# package: test
# 	$(CMAKE) \
#   --install $(PWD)/build \
# 	--prefix $(PWD)/install

# # Dependencies
# dep: configure

# .PHONY: dep

CMAKE_CACHE := $(BUILD_DIR)/CMakeCache.txt

$(CMAKE_CACHE): configure

COMPILE_COMMANDS := $(BUILD_DIR)/compile_commands.json

$(COMPILE_COMMANDS): $(CMAKE_CACHE)

############################################<<<-Libraries and executable targets

CPPFLAGS += $(FLAGS) $(DEFINES) $(INCLUDES)
ASMFLAGS += $(FLAGS)
CFLAGS += $(FLAGS)
CXXFLAGS += $(FLAGS)
OBJCFLAGS += $(FLAGS)
OBJCXXFLAGS += $(FLAGS)
LDFLAGS += $(FLAGS)

# <CPP>
CPP_CC_COMPILER := $(CC)
CPP_CXX_COMPILER := $(CXX)
CPP_OBJC_COMPILER := $(OBJC)
CPP_OBJCXX_COMPILER := $(OBJCXX)

# <ASM>
ASM_CC_COMPILER := $(CC)
ASM_CXX_COMPILER := $(CXX)
ASM_OBJC_COMPILER := $(OBJC)
ASM_OBJCXX_COMPILER := $(OBJCXX)

# <C;CXX;OBJC;OBJCXX>
CC_COMPILER := $(CC)
CXX_COMPILER := $(CXX)
OBJC_COMPILER := $(OBJC) -ObjC
OBJCXX_COMPILER := $(OBJCXX) -ObjC++

# <CPP>
CPP_CC_COMPILER_LAUNCHER := $(CPP_CC_COMPILER) -E $(CPPFLAGS) $(C_STANDARD_FLAG)
CPP_CXX_COMPILER_LAUNCHER := $(CPP_CXX_COMPILER) -E $(CPPFLAGS) $(CXX_STANDARD_FLAG)
CPP_OBJC_COMPILER_LAUNCHER := $(CPP_OBJC_COMPILER) -E $(CPPFLAGS) $(C_STANDARD_FLAG)
CPP_OBJCXX_COMPILER_LAUNCHER := $(CPP_OBJCXX_COMPILER) -E $(CPPFLAGS) $(CXX_STANDARD_FLAG)

# <ASM>
ASM_CC_COMPILER_LAUNCHER := $(ASM_CC_COMPILER) -S $(ASMFLAGS) $(C_STANDARD_FLAG)
ASM_CXX_COMPILER_LAUNCHER := $(ASM_CXX_COMPILER) -S $(ASMFLAGS) $(CXX_STANDARD_FLAG)
ASM_OBJC_COMPILER_LAUNCHER := $(ASM_OBJC_COMPILER) -S $(ASMFLAGS)  $(C_STANDARD_FLAG)
ASM_OBJCXX_COMPILER_LAUNCHER := $(ASM_OBJCXX_COMPILER) -S $(ASMFLAGS) $(CXX_STANDARD_FLAG)

# <C;CXX;OBJC;OBJCXX>
CC_COMPILER_LAUNCHER := $(CC_COMPILER) -c $(CFLAGS) $(C_STANDARD_FLAG)
CXX_COMPILER_LAUNCHER := $(CXX_COMPILER) -c $(CXXFLAGS) $(CXX_STANDARD_FLAG)
OBJC_COMPILER_LAUNCHER := $(OBJC_COMPILER) -c $(OBJCFLAGS) $(C_STANDARD_FLAG)
OBJCXX_COMPILER_LAUNCHER := $(OBJCXX_COMPILER) -c $(OBJCXXFLAGS) $(CXX_STANDARD_FLAG)

##########################################################<<<-Patterns and rules

TARGET := $(BUILD_DIR)/lib/libstoneydsp.$(LIB_EXT)

## Distribution build
$(TARGET): $(OBJECTS)
	@echo
	@echo Building target: $@
	@mkdir -p $(dir $@)
	$(CXX) $(BUILD_SHARED_FLAG) $(LDFLAGS) $^ -o $@
	@echo Built target successfully: $@
	@echo

$(BUILD_DIR)/include: $(CMAKE_CACHE)
	@echo "Configured header files."

-include $(DEPS)

## <CC>

## '*.c' - Pre-Processor
$(BUILD_DIR)/src/%.c.i: $(SRC_DIR)/%.c
	@echo
	@echo Building target: $@
	@mkdir -p $(dir $@)
	$(CPP_CC_COMPILER_LAUNCHER) -x c $< -o $@
	@echo Built target successfully: $@
	@echo
## '*.c.s' - Assembler
$(BUILD_DIR)/src/%.c.s: $(BUILD_DIR)/src/%.c.i
	@echo
	@echo Building target: $@
	@mkdir -p $(dir $@)
	$(ASM_CC_COMPILER_LAUNCHER) -x c-cpp-output $< -o $@
	@echo Built target successfully: $@
	@echo
## '*.c.o' - Compiler
$(BUILD_DIR)/src/%.c.o: $(BUILD_DIR)/src/%.c.s
	@echo
	@echo Building target: $@
	@mkdir -p $(dir $@)
	$(CC_COMPILER_LAUNCHER) -x assembler $< -o $@
	@echo Built target successfully: $@
	@echo

# ## '*.c.d' - Dependency tracking
# $(BUILD_DIR)/src/%.c.d: $(SRC_DIR)/%.c
# 	@mkdir -p $(dir $@)
# 	@$(CC) $(CFLAGS) $(CPPFLAGS) $(FLAGS) $(DEFINES) $(INCLUDES) -x c -MM -MF $@ -MT $(@:.d=.o) $<
# -include $(DEPS)

## <CXX>

## '*.cpp.i' - Pre-Processor
$(BUILD_DIR)/src/%.cpp.ii: $(SRC_DIR)/%.cpp
	@echo
	@echo Building target: $@
	@mkdir -p $(dir $@)
	$(CPP_CXX_COMPILER_LAUNCHER) -x c++ $< -o $@
	@echo Built target successfully: $@
	@echo

## '*.cpp.s' - Assembler
$(BUILD_DIR)/src/%.cpp.s: $(BUILD_DIR)/src/%.cpp.ii
	@echo
	@echo Building target: $@
	@mkdir -p $(dir $@)
	$(ASM_CXX_COMPILER_LAUNCHER) -x c++-cpp-output $< -o $@
	@echo Built target successfully: $@
	@echo

## '*.cpp.o' - Compiler
$(BUILD_DIR)/src/%.cpp.o: $(BUILD_DIR)/src/%.cpp.s
	@echo
	@echo Building target: $@
	@mkdir -p $(dir $@)
	$(CXX_COMPILER_LAUNCHER) -x assembler $< -o $@
	@echo Built target successfully: $@
	@echo

# ## '*.cpp.d' - Dependency tracking
# $(BUILD_DIR)/src/%.cpp.d: $(SRC_DIR)/%.cpp
# 	@echo Building target: $@
# 	@mkdir -p $(dir $@)
# 	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -x c++ -MM -MF $@ -MT $(@:.d=.o) $<
# -include $(DEPS)

## <OBJC>

## '*.m.i' - Pre-Processor
$(BUILD_DIR)/src/%.m.mi: $(SRC_DIR)/%.m
	@echo
	@echo Building target: $@
	@mkdir -p $(dir $@)
	$(CPP_OBJC_COMPILER_LAUNCHER) -x objective-c $< -o $@
	@echo Built target successfully: $@
	@echo

## '*.m.s' - Assembler
$(BUILD_DIR)/src/%.m.s: $(BUILD_DIR)/src/%.m.mi
	@echo
	@echo Building target: $@
	@mkdir -p $(dir $@)
	$(ASM_OBJC_COMPILER_LAUNCHER) -x objective-c-cpp-output $< -o $@
	@echo Built target successfully: $@
	@echo

## '*.m.o' - Compiler
$(BUILD_DIR)/src/%.m.o: $(BUILD_DIR)/src/%.m.s
	@echo
	@echo Building target: $@
	@mkdir -p $(dir $@)
	$(OBJC_COMPILER_LAUNCHER) -x assembler $< -o $@
	@echo Built target successfully: $@
	@echo

## <OBJCXX>
## '*.mm.i' - Pre-Processor
$(BUILD_DIR)/src/%.mm.mii: $(SRC_DIR)/%.mm
	@echo
	@echo Building target: $@
	@mkdir -p $(dir $@)
	$(CPP_OBJCXX_COMPILER_LAUNCHER) -x objective-c++ $< -o $@
	@echo Built target successfully: $@
	@echo

## '*.mm.s' - Assembler
$(BUILD_DIR)/src/%.mm.s: $(BUILD_DIR)/src/%.mm.mii
	@echo
	@echo Building target: $@
	@mkdir -p $(dir $@)
	$(ASM_OBJCXX_COMPILER_LAUNCHER) -x objective-c++-cpp-output $< -o $@
	@echo Built target successfully: $@
	@echo

## '*.mm.o' - Compiler
$(BUILD_DIR)/src/%.mm.o: $(BUILD_DIR)/src/%.mm.s
	@echo
	@echo Building target: $@
	@mkdir -p $(dir $@)
	$(OBJCXX_COMPILER_LAUNCHER) -x assembler $< -o $@
	@echo Built target successfully: $@
	@echo

ifeq ($(BUILD_MAIN),1)
## '*.cpp.i' - Pre-Processor
$(BUILD_DIR)/bin/main.cpp.ii: bin/main.cpp $(TARGET)
	@echo
	@echo Building target: $@
	@mkdir -p $(dir $@)
	$(CPP_CXX_COMPILER_LAUNCHER) -DSTONEYDSP_BUILD_MAIN=1 -x c++ $< -o $@
	@echo Built target successfully: $@
	@echo

## '*.cpp.s' - Assembler
$(BUILD_DIR)/bin/main.cpp.s: $(BUILD_DIR)/bin/main.cpp.ii
	@echo
	@echo Building target: $@
	@mkdir -p $(dir $@)
	$(ASM_CXX_COMPILER_LAUNCHER) -x c++-cpp-output $< -o $@
	@echo Built target successfully: $@
	@echo

## '*.cpp.o' - Compiler
$(BUILD_DIR)/bin/main.cpp.o: $(BUILD_DIR)/bin/main.cpp.s
	@echo
	@echo Building target: $@
	@mkdir -p $(dir $@)
	$(CXX_COMPILER_LAUNCHER) -x assembler $< -o $@
	@echo Built target successfully: $@
	@echo

$(BUILD_DIR)/bin/main: $(BUILD_DIR)/bin/main.cpp.o
	@echo
	@echo Building target: $@
	@mkdir -p $(dir $@)
	$(CXX) $(BUILD_DIR)/bin/main.cpp.o -L$(BUILD_DIR)/lib -o $@ $(LDFLAGS) -lstoneydsp
	@echo Built target successfully: $@
	@echo

# build/%.bin.o: %
# 	@mkdir -p $(@D)
# ifdef ARCH_LIN
# 	$(OBJCOPY) -I binary -O elf64-x86-64 -B i386:x86-64 --rename-section .data=.rodata,alloc,load,readonly,data,contents $< $@
# endif
# ifdef ARCH_WIN
# 	$(OBJCOPY) -I binary -O pe-x86-64 -B i386:x86-64 --rename-section .data=.rodata,alloc,load,readonly,data,contents $< $@
# endif
# ifdef ARCH_MAC
# 	@# Apple makes this needlessly complicated, so just generate a C file with an array.
# 	xxd -i $< | $(CC) $(MAC_SDK_FLAGS) -c -o $@ -xc -
# endif

run: $(BUILD_DIR)/bin/main
	@$(BUILD_DIR)/bin/main $(RUN_ARGS)
.PHONY: run

endif

#######################################################################<<<-Tests

## Test executable
ifdef BUILD_TEST
$(LIB_CATCH_PATH)/lib$(LIB_CATCH).a: $(CMAKE_CACHE)

## Alias target to install Catch2 unit-testing library
catch2: $(LIB_CATCH_PATH)/lib$(LIB_CATCH).a
.PHONY: catch2

$(TEST_TARGET): $(TARGET) $(TEST_OBJS)
	@echo
	@echo Building target: $@
	@mkdir -p $(dir $@)
	$(CXX) $(TEST_OBJS) -L$(BUILD_DIR)/lib -o $@ $(LDFLAGS) -lstoneydsp
	@echo Built target successfully: $@
	@echo

check: catch2 $(TEST_TARGET)
	$(TEST_TARGET) $(TEST_ARGS)
.PHONY: check

## <CXX>

## '*.test.cpp.i' - Pre-Processor
$(BUILD_DIR)/test/%.test.cpp.ii: $(TEST_DIR)/%.test.cpp
	@echo
	@echo Building target: $@
	@mkdir -p $(dir $@)
	$(CPP_CXX_COMPILER_LAUNCHER) -x c++ $< -o $@
	@echo Built target successfully: $@
	@echo

## '*.test.cpp.s' - Assembler
$(BUILD_DIR)/test/%.test.cpp.s: $(BUILD_DIR)/test/%.test.cpp.ii
	@echo
	@echo Building target: $@
	@mkdir -p $(dir $@)
	$(ASM_CXX_COMPILER_LAUNCHER) -x c++-cpp-output $< -o $@
	@echo Built target successfully: $@
	@echo

## '*.test.cpp.o' - Compiler
$(BUILD_DIR)/test/%.test.cpp.o: $(BUILD_DIR)/test/%.test.cpp.s
	@echo
	@echo Building target: $@
	@mkdir -p $(dir $@)
	$(CXX_COMPILER_LAUNCHER) -x assembler $< -o $@
	@echo Built target successfully: $@
	@echo

# ## '*.cpp.d' - Dependency tracking
# $(BUILD_DIR)/src/%.cpp.d: $(SRC_DIR)/%.cpp
# 	@echo Building target: $@
# 	@mkdir -p $(dir $@)
# 	$(CXX) $(CXXFLAGS) $(CPPFLAGS) $(FLAGS) $(DEFINES) $(INCLUDES) -x c++ -MM -MF $@ -MT $(@:.d=.o) $<
# -include $(DEPS)

endif

##################################################<<<-Packaging and distribution

PREFIX ?= /usr/local

install: $(TARGET)
	@mkdir -p $(PREFIX)/lib
	@mkdir -p $(PREFIX)/include/stoneydsp
	@cp $(TARGET) $(PREFIX)/lib/
	@cp -r $(BUILD_DIR)/include/stoneydsp $(PREFIX)/include/
	@echo "StoneyDSP Library and headers installed to $(PREFIX)"

$(BUILD_DIR)/%.html: %.md
	@mkdir -p $(dir $@)
	@markdown $< > $@

## Include the doc target
$(BUILD_DIR)/doc/html: $(CMAKE_CACHE)
	@doxygen ./doc/Doxyfile

doc: $(BUILD_DIR)/doc/html
	@mkdir -p $(dir $@)
.PHONY: doc

#############################################<<<-Part 10: Clean, Help, and utils

## default target
all: $(TARGET) $(TEST_TARGET)
.PHONY: all

## Fetch submodules
submodules:
	@$(GIT) submodule update --init --recursive
.PHONY: submodules

DEBUG_FLAGS := -g -O0
RELEASE_FLAGS := -O2

## Debug build
debug: CFLAGS += $(DEBUG_FLAGS)
debug: $(TARGET)
.PHONY: debug

## Release build
release: CFLAGS += $(RELEASE_FLAGS)
release: $(TARGET)
.PHONY: release

## Lint source files files
format:
	@$(CPP_LINT) --style=file:.clang-format
.PHONY: format

## Analyze source files files
tidy: $(COMPILE_COMMANDS)
	@$(CPP_TIDY) --config-file=.clang-tidy -p $(BUILD_DIR)
.PHONY: tidy

## Clean up build files
clean:
	@rm -rvf $(BUILD_DIR)/doc
	@rm -rvf $(BUILD_DIR)/bin
	@rm -rvf $(BUILD_DIR)/lib
	@rm -rvf $(BUILD_DIR)/test
	@rm -rvf $(BUILD_DIR)/src
	@rm -rvf $(BUILD_DIR)/include
	@rm -rvf $(BUILD_DIR)/.ninja_deps
	@rm -rvf $(BUILD_DIR)/.ninja_log
	@rm -rvf $(BUILD_DIR)/build.ninja
	@rm -rvf $(BUILD_DIR)/cmake_install.cmake
	@rm -rvf $(BUILD_DIR)/install_manifest.txt
	@rm -rvf $(BUILD_DIR)/CPackConfig.cmake
	@rm -rvf $(BUILD_DIR)/CPackSourceConfig.cmake
	@rm -rvf $(BUILD_DIR)/CMakeFiles
	@rm -rvf $(BUILD_DIR)/MakeFiles
	@rm -rvf $(BUILD_DIR)/Testing
	@rm -rvf $(TARGET)
	@rm -rvf $(TEST_TARGET)
	@rm -rvf $(CMAKE_CACHE)
	@rm -rvf $(COMPILE_COMMANDS)
	@rm -rvf $(BUILD_DIR)/compile_commands_cmake.json
	@rm -rvf $(BUILD_DIR)/compile_commands_make.json
.PHONY: clean

wipe: clean
	@rm -rvf $(BUILD_DIR)
.PHONY: wipe

# Helper to debug Makefile variables, eg: "make echo ECHO_ARGS='STONEYDSP_SOURCES'"
echo:
	@echo $($(ECHO_ARGS))
.PHONY: echo

## Help Target
help:
	@echo "The directory of the Makefile is: $(MAKEFILE_DIR)"
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... dep"
	@echo "... catch2"
	@echo "... submodules"
	@echo "... doc"
	@echo "... configure"
	@echo "... build"
	@echo "... test"
	@echo "... run"
	@echo "... install"
	@echo "... package"
	@echo "... package_source"
	@echo "... workflow"
	@echo "... clean"
	@echo "... version"
	@echo "... help"
.PHONY: help

.PRECIOUS: $(CMAKE_CACHE) $(COMPILE_COMMANDS)

.DEFAULT_TARGET: all
