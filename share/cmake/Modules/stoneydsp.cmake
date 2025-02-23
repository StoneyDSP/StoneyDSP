#[===============================[Include Guard]===============================]
include_guard(GLOBAL)

set(_version 0.0.0)

if(COMMAND stoneydsp_add_core)
    if(NOT DEFINED _stoneydsp_script_version OR NOT(_version STREQUAL _stoneydsp_script_version))
        message(WARNING "More than one 'stoneydsp.cmake' version has been included in this project.")
    endif()

    # 'stoneydsp.cmake' has already been included! Don't do anything
    return()
endif()

set(_stoneydsp_script_version "${_version}" CACHE INTERNAL "Current 'stoneydsp.cmake' version. Used for checking for conflicts")

set(_stoneydsp_script_file "${CMAKE_CURRENT_LIST_FILE}" CACHE INTERNAL "Path to current 'stoneydsp.cmake' script")

#[=============================================================================[
Internal helper
]=============================================================================] #
function(_stoneydsp_trim_newlines input)
    string(REGEX REPLACE "[\r\n\"]" "" input "${input}")
    set(input "${input}" PARENT_SCOPE)
endfunction()

#[=============================================================================[
Internal helper (borrowed from CMakeRC).
]=============================================================================]
function(_stoneydsp_normalize_path var)
    set(path "${${var}}")
    file(TO_CMAKE_PATH "${path}" path)

    while(path MATCHES "//")
        string(REPLACE "//" "/" path "${path}")
    endwhile()

    string(REGEX REPLACE "/+$" "" path "${path}")
    set("${var}" "${path}" PARENT_SCOPE)
endfunction()

#[=============================================================================[
Internal helper (borrowed from CMakeRC).
]=============================================================================]
macro(stoneydsp_add_directories)
    file(RELATIVE_PATH STONEYDSP_INCLUDE_DIR "${STONEYDSP_DIR}" "${STONEYDSP_DIR}/include")
    file(RELATIVE_PATH STONEYDSP_SRC_DIR "${STONEYDSP_DIR}" "${STONEYDSP_DIR}/src")
    file(RELATIVE_PATH STONEYDSP_TEST_DIR "${STONEYDSP_DIR}" "${STONEYDSP_DIR}/test")
    file(RELATIVE_PATH STONEYDSP_DATA_DIR "${STONEYDSP_DIR}" "${STONEYDSP_DIR}/share")
endmacro()

set(STONEYDSP_INCLUDE_DIR "${STONEYDSP_INCLUDE_DIR}")
set(STONEYDSP_SRC_DIR "${STONEYDSP_SRC_DIR}")
set(STONEYDSP_TEST_DIR "${STONEYDSP_TEST_DIR}")
set(STONEYDSP_DATA_DIR "${STONEYDSP_DATA_DIR}")

#[==========================[stoneydsp_add_stoneydsp]==========================]
option(STONEYDSP_TARGET_INSTALL "Notes" ON)
option(STONEYDSP_TARGET_EXPORT "Notes" ON)
option(STONEYDSP_BUILD_SHARED "Build shared library if truthy, else build static library. Default: OFF" OFF)
set(_STONEYDSP_BUILD_STATIC_OR_DYNAMIC)

if(STONEYDSP_BUILD_SHARED OR BUILD_SHARED_LIBS)
    set(_STONEYDSP_BUILD_STATIC_OR_DYNAMIC "SHARED")
else()
    set(_STONEYDSP_BUILD_STATIC_OR_DYNAMIC "STATIC")
endif(STONEYDSP_BUILD_SHARED OR BUILD_SHARED_LIBS)

if(APPLE)
    set(CMAKE_SKIP_BUILD_RPATH FALSE)
    set(CMAKE_BUILD_WITH_INSTALL_RPATH FALSE)
    set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

    # Add the RPATH to the build directory
    set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")
endif()

#[==[
Adds target: `stoneydsp::stoneydsp`
]==]
function(stoneydsp_add_stoneydsp)
    # Generate target properties
    set(STONEYDSP_TARGET_NAME "stoneydsp")
    set(STONEYDSP_HEADERS_FILESET_NAME "stoneydsp_PUBLIC_HEADERS")

    # stoneydsp/stoneydsp.h|cpp
    set(STONEYDSP_H_FILE "${STONEYDSP_INCLUDE_DIR}/${STONEYDSP_SLUG}/${STONEYDSP_SLUG}.h")
    set(STONEYDSP_CPP_FILE "${STONEYDSP_SRC_DIR}/${STONEYDSP_SLUG}/${STONEYDSP_SLUG}.cpp")

    # List header files (public)
    set(STONEYDSP_HEADER_FILES)
    list(APPEND STONEYDSP_HEADER_FILES
        "${STONEYDSP_H_FILE}"
    )

    # List source files (private)
    set(STONEYDSP_SOURCE_FILES)
    list(APPEND STONEYDSP_SOURCE_FILES
        "${STONEYDSP_CPP_FILE}"
    )

    # List link libraries (private)
    set(STONEYDSP_LINK_LIBRARIES_PRIVATE)
    list(APPEND STONEYDSP_LINK_LIBRARIES_PRIVATE)

    # List link libraries (public)
    set(STONEYDSP_LINK_LIBRARIES_PUBLIC)
    list(APPEND STONEYDSP_LINK_LIBRARIES_PUBLIC)

    if(STONEYDSP_BUILD_CORE)
        list(APPEND STONEYDSP_LINK_LIBRARIES_PUBLIC
            ${STONEYDSP_BRAND}::${STONEYDSP_SLUG}::${STONEYDSP_CORE_TARGET_NAME}
        )
    endif()

    if(STONEYDSP_BUILD_SIMD)
        list(APPEND STONEYDSP_LINK_LIBRARIES_PUBLIC
            ${STONEYDSP_BRAND}::${STONEYDSP_SLUG}::${STONEYDSP_SIMD_TARGET_NAME}
        )
    endif()

    if(STONEYDSP_BUILD_DSP)
        list(APPEND STONEYDSP_LINK_LIBRARIES_PUBLIC
            ${STONEYDSP_BRAND}::${STONEYDSP_SLUG}::${STONEYDSP_DSP_TARGET_NAME}
        )
    endif()

    # List link libraries (interface)
    set(STONEYDSP_LINK_LIBRARIES_INTERFACE)
    list(APPEND STONEYDSP_LINK_LIBRARIES_INTERFACE)

    # List compile definitions (private)
    set(STONEYDSP_COMPILE_DEFINITIONS_PRIVATE)
    list(APPEND STONEYDSP_COMPILE_DEFINITIONS_PRIVATE)

    # List compile definitions (public)
    set(STONEYDSP_COMPILE_DEFINITIONS_PUBLIC)
    list(APPEND STONEYDSP_COMPILE_DEFINITIONS_PUBLIC
        "-DSTONEYDSP_VERSION_MAJOR=${STONEYDSP_VERSION_MAJOR}"
        "-DSTONEYDSP_VERSION_MINOR=${STONEYDSP_VERSION_MINOR}"
        "-DSTONEYDSP_VERSION_BUILD=${STONEYDSP_VERSION_BUILD}"
        "-DSTONEYDSP_VERSION=${STONEYDSP_VERSION}"
    )

    # List compile definitions (interface)
    set(STONEYDSP_COMPILE_DEFINITIONS_INTERFACE)
    list(APPEND STONEYDSP_COMPILE_DEFINITIONS_INTERFACE)

    # List compile options (interface)
    set(STONEYDSP_COMPILE_OPTIONS_INTERFACE)
    list(APPEND STONEYDSP_COMPILE_OPTIONS_INTERFACE)

    # List compile options (private)
    set(STONEYDSP_COMPILE_OPTIONS_PRIVATE)
    list(APPEND STONEYDSP_COMPILE_OPTIONS_PRIVATE)

    # List compile options (public)
    set(STONEYDSP_COMPILE_OPTIONS_PUBLIC)
    list(APPEND STONEYDSP_COMPILE_OPTIONS_PUBLIC)

    # List compile features (interface)
    set(STONEYDSP_COMPILE_FEATURES_INTERFACE)
    list(APPEND STONEYDSP_COMPILE_FEATURES_INTERFACE)

    # List compile features (private)
    set(STONEYDSP_COMPILE_FEATURES_PRIVATE)
    list(APPEND STONEYDSP_COMPILE_FEATURES_PRIVATE)

    # List compile features (public)
    set(STONEYDSP_COMPILE_FEATURES_PUBLIC)
    list(APPEND STONEYDSP_COMPILE_FEATURES_PUBLIC

        # <CXX>
        cxx_std_11

        # <CC>
        #
        c_std_11
    )

    add_library(${STONEYDSP_TARGET_NAME} ${_STONEYDSP_BUILD_STATIC_OR_DYNAMIC})
    add_library(${STONEYDSP_SLUG}::${STONEYDSP_TARGET_NAME} ALIAS ${STONEYDSP_TARGET_NAME})
    add_library(${STONEYDSP_BRAND}::${STONEYDSP_SLUG}::${STONEYDSP_TARGET_NAME} ALIAS ${STONEYDSP_TARGET_NAME})

    set_target_properties(${STONEYDSP_TARGET_NAME}
        PROPERTIES

        VERSION "${STONEYDSP_VERSION}"
        SOVERSION "${STONEYDSP_VERSION_MAJOR}"

        RUNTIME_OUTPUT_DIRECTORY "${STONEYDSP_BINARY_DIR}/bin"
        PDB_OUTPUT_DIRECTORY "${STONEYDSP_BINARY_DIR}/lib"
        LIBRARY_OUTPUT_DIRECTORY "${STONEYDSP_BINARY_DIR}/lib"
        ARCHIVE_OUTPUT_DIRECTORY "${STONEYDSP_BINARY_DIR}/lib"
    )

    foreach(STONEYDSP_HEADER_FILE IN LISTS STONEYDSP_HEADER_FILES)
        message(DEBUG "Target: ${STONEYDSP_TARGET_NAME} - adding header: ${STONEYDSP_HEADER_FILE}")
        configure_file("${STONEYDSP_HEADER_FILE}" "${STONEYDSP_HEADER_FILE}")
        target_sources(${STONEYDSP_TARGET_NAME}
            PUBLIC
            FILE_SET ${STONEYDSP_HEADERS_FILESET_NAME}
            TYPE HEADERS
            BASE_DIRS
            $<BUILD_INTERFACE:${STONEYDSP_DIR}/${STONEYDSP_INCLUDE_DIR}>
            $<INSTALL_INTERFACE:${STONEYDSP_INCLUDE_DIR}>
            FILES
            $<BUILD_INTERFACE:${STONEYDSP_DIR}/${STONEYDSP_HEADER_FILE}>
            $<INSTALL_INTERFACE:${STONEYDSP_HEADER_FILE}>
        )
        message(VERBOSE "Target: ${STONEYDSP_TARGET_NAME} - added header: ${STONEYDSP_HEADER_FILE}")
    endforeach(STONEYDSP_HEADER_FILE IN LISTS STONEYDSP_HEADER_FILES)

    foreach(STONEYDSP_SOURCE_FILE IN LISTS STONEYDSP_SOURCE_FILES)
        message(DEBUG "Target: ${STONEYDSP_TARGET_NAME} - adding source: ${STONEYDSP_SOURCE_FILE}")
        target_sources(${STONEYDSP_TARGET_NAME}
            PRIVATE
            "${STONEYDSP_SOURCE_FILE}"
        )
        message(VERBOSE "Target: ${STONEYDSP_TARGET_NAME} - added source: ${STONEYDSP_SOURCE_FILE}")
    endforeach(STONEYDSP_SOURCE_FILE IN LISTS STONEYDSP_SOURCE_FILES)

    foreach(STONEYDSP_LINK_LIBRARY IN LISTS STONEYDSP_LINK_LIBRARIES_PRIVATE)
        message(DEBUG "Target: ${STONEYDSP_TARGET_NAME} - linking library (private): ${STONEYDSP_LINK_LIBRARY}")
        target_link_libraries(${STONEYDSP_TARGET_NAME}
            PRIVATE
            ${STONEYDSP_LINK_LIBRARY}
        )
        message(VERBOSE "Target: ${STONEYDSP_TARGET_NAME} - linked library (private): ${STONEYDSP_LINK_LIBRARY}")
    endforeach(STONEYDSP_LINK_LIBRARY IN LISTS STONEYDSP_LINK_LIBRARIES_PRIVATE)

    foreach(STONEYDSP_LINK_LIBRARY IN LISTS STONEYDSP_LINK_LIBRARIES_PUBLIC)
        message(DEBUG "Target: ${STONEYDSP_TARGET_NAME} - linking library (public): ${STONEYDSP_LINK_LIBRARY}")
        target_link_libraries(${STONEYDSP_TARGET_NAME}
            PUBLIC
            ${STONEYDSP_LINK_LIBRARY}
        )
        message(VERBOSE "Target: ${STONEYDSP_TARGET_NAME} - linked library (public): ${STONEYDSP_LINK_LIBRARY}")
    endforeach(STONEYDSP_LINK_LIBRARY IN LISTS STONEYDSP_LINK_LIBRARIES_PUBLIC)

    foreach(STONEYDSP_LINK_LIBRARY IN LISTS STONEYDSP_LINK_LIBRARIES_INTERFACE)
        message(DEBUG "Target: ${STONEYDSP_TARGET_NAME} - linking library (interface): ${STONEYDSP_LINK_LIBRARY}")
        target_link_libraries(${STONEYDSP_TARGET_NAME}
            INTERFACE
            ${STONEYDSP_LINK_LIBRARY}
        )
        message(VERBOSE "Target: ${STONEYDSP_TARGET_NAME} - linked library (interface): ${STONEYDSP_LINK_LIBRARY}")
    endforeach(STONEYDSP_LINK_LIBRARY IN LISTS STONEYDSP_LINK_LIBRARIES_INTERFACE)

    foreach(STONEYDSP_COMPILE_DEFINITION IN LISTS STONEYDSP_COMPILE_DEFINITIONS_PRIVATE)
        message(DEBUG "Target: ${STONEYDSP_TARGET_NAME} - adding compile definiton (private): ${STONEYDSP_COMPILE_DEFINITION}")
        target_compile_definitions(${STONEYDSP_TARGET_NAME}
            PRIVATE
            ${STONEYDSP_COMPILE_DEFINITION}
        )
        message(VERBOSE "Target: ${STONEYDSP_TARGET_NAME} - added compile definiton (private): ${STONEYDSP_COMPILE_DEFINITION}")
    endforeach(STONEYDSP_COMPILE_DEFINITION IN LISTS STONEYDSP_COMPILE_DEFINITIONS_PRIVATE)

    foreach(STONEYDSP_COMPILE_DEFINITION IN LISTS STONEYDSP_COMPILE_DEFINITIONS_PUBLIC)
        message(DEBUG "Target: ${STONEYDSP_TARGET_NAME} - adding compile definiton (public): ${STONEYDSP_COMPILE_DEFINITION}")
        target_compile_definitions(${STONEYDSP_TARGET_NAME}
            PUBLIC
            ${STONEYDSP_COMPILE_DEFINITION}
        )
        message(VERBOSE "Target: ${STONEYDSP_TARGET_NAME} - added compile definiton (public): ${STONEYDSP_COMPILE_DEFINITION}")
    endforeach(STONEYDSP_COMPILE_DEFINITION IN LISTS STONEYDSP_COMPILE_DEFINITIONS_PUBLIC)

    foreach(STONEYDSP_COMPILE_DEFINITION IN LISTS STONEYDSP_COMPILE_DEFINITIONS_INTERFACE)
        message(DEBUG "Target: ${STONEYDSP_TARGET_NAME} - adding compile definiton (interface): ${STONEYDSP_COMPILE_DEFINITION}")
        target_compile_definitions(${STONEYDSP_TARGET_NAME}
            INTERFACE
            ${STONEYDSP_COMPILE_DEFINITION}
        )
        message(VERBOSE "Target: ${STONEYDSP_TARGET_NAME} - added compile definiton (interface): ${STONEYDSP_COMPILE_DEFINITION}")
    endforeach(STONEYDSP_COMPILE_DEFINITION IN LISTS STONEYDSP_COMPILE_DEFINITIONS_INTERFACE)

    foreach(STONEYDSP_COMPILE_OPTION IN LISTS STONEYDSP_COMPILE_OPTIONS_PRIVATE)
        message(DEBUG "Target: ${STONEYDSP_TARGET_NAME} - adding compile option (private): ${STONEYDSP_COMPILE_OPTION}")
        target_compile_options(${STONEYDSP_TARGET_NAME}
            PRIVATE
            ${STONEYDSP_COMPILE_OPTION}
        )
        message(VERBOSE "Target: ${STONEYDSP_TARGET_NAME} - added compile option (private): ${STONEYDSP_COMPILE_OPTION}")
    endforeach(STONEYDSP_COMPILE_OPTION IN LISTS STONEYDSP_COMPILE_OPTIONS_PRIVATE)

    foreach(STONEYDSP_COMPILE_OPTION IN LISTS STONEYDSP_COMPILE_OPTIONS_PUBLIC)
        message(DEBUG "Target: ${STONEYDSP_TARGET_NAME} - adding compile option (public): ${STONEYDSP_COMPILE_OPTION}")
        target_compile_options(${STONEYDSP_TARGET_NAME}
            PUBLIC
            ${STONEYDSP_COMPILE_OPTION}
        )
        message(VERBOSE "Target: ${STONEYDSP_TARGET_NAME} - added compile option (public): ${STONEYDSP_COMPILE_OPTION}")
    endforeach(STONEYDSP_COMPILE_OPTION IN LISTS STONEYDSP_COMPILE_OPTIONS_PUBLIC)

    foreach(STONEYDSP_COMPILE_OPTION IN LISTS STONEYDSP_COMPILE_OPTIONS_INTERFACE)
        message(DEBUG "Target: ${STONEYDSP_TARGET_NAME} - adding compile option (interface): ${STONEYDSP_COMPILE_OPTION}")
        target_compile_options(${STONEYDSP_TARGET_NAME}
            INTERFACE
            ${STONEYDSP_COMPILE_OPTION}
        )
        message(VERBOSE "Target: ${STONEYDSP_TARGET_NAME} - added compile option (interface): ${STONEYDSP_COMPILE_OPTION}")
    endforeach(STONEYDSP_COMPILE_OPTION IN LISTS STONEYDSP_COMPILE_OPTIONS_INTERFACE)

    foreach(STONEYDSP_COMPILE_FEATURE IN LISTS STONEYDSP_COMPILE_FEATURES_PRIVATE)
        message(DEBUG "Target: ${STONEYDSP_TARGET_NAME} - adding compile feature (private): ${STONEYDSP_COMPILE_FEATURE}")
        target_compile_features(${STONEYDSP_TARGET_NAME}
            PRIVATE
            ${STONEYDSP_COMPILE_FEATURE}
        )
        message(VERBOSE "Target: ${STONEYDSP_TARGET_NAME} - added compile feature (private): ${STONEYDSP_COMPILE_FEATURE}")
    endforeach(STONEYDSP_COMPILE_FEATURE IN LISTS STONEYDSP_COMPILE_FEATURES_PRIVATE)

    foreach(STONEYDSP_COMPILE_FEATURE IN LISTS STONEYDSP_COMPILE_FEATURES_PUBLIC)
        message(DEBUG "Target: ${STONEYDSP_TARGET_NAME} - adding compile feature (public): ${STONEYDSP_COMPILE_FEATURE}")
        target_compile_features(${STONEYDSP_TARGET_NAME}
            PUBLIC
            ${STONEYDSP_COMPILE_FEATURE}
        )
        message(VERBOSE "Target: ${STONEYDSP_TARGET_NAME} - added compile feature (public): ${STONEYDSP_COMPILE_FEATURE}")
    endforeach(STONEYDSP_COMPILE_FEATURE IN LISTS STONEYDSP_COMPILE_FEATURES_PUBLIC)

    foreach(STONEYDSP_COMPILE_FEATURE IN LISTS STONEYDSP_COMPILE_FEATURES_INTERFACE)
        message(DEBUG "Target: ${STONEYDSP_TARGET_NAME} - adding compile feature (interface): ${STONEYDSP_COMPILE_FEATURE}")
        target_compile_features(${STONEYDSP_TARGET_NAME}
            INTERFACE
            ${STONEYDSP_COMPILE_FEATURE}
        )
        message(VERBOSE "Target: ${STONEYDSP_TARGET_NAME} - added compile feature (interface): ${STONEYDSP_COMPILE_FEATURE}")
    endforeach(STONEYDSP_COMPILE_FEATURE IN LISTS STONEYDSP_COMPILE_FEATURES_INTERFACE)

    if(STONEYDSP_TARGET_INSTALL)
        # Generate export set
        install(TARGETS ${STONEYDSP_TARGET_NAME}
            EXPORT ${STONEYDSP_TARGET_NAME}Install
            COMPONENT ${STONEYDSP_TARGET_NAME}
            LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
            RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
            ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
            INCLUDES DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
            FILE_SET ${STONEYDSP_HEADERS_FILESET_NAME} DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
        )

        # Install export set
        install(EXPORT ${STONEYDSP_TARGET_NAME}Install
            FILE "${STONEYDSP_TARGET_NAME}-targets.cmake"
            NAMESPACE ${STONEYDSP_BRAND}::${STONEYDSP_SLUG}::
            DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/${STONEYDSP_BRAND}"
        )
    endif()

    if(STONEYDSP_TARGET_EXPORT)
        # Generate export set
        export(
            SETUP ${STONEYDSP_TARGET_NAME}Export
            TARGET ${STONEYDSP_TARGET_NAME}
        )

        # Install export set
        export(
            EXPORT ${STONEYDSP_TARGET_NAME}Export
            FILE "lib/cmake/${STONEYDSP_BRAND}/${STONEYDSP_TARGET_NAME}-targets.cmake"
            NAMESPACE ${STONEYDSP_BRAND}::${STONEYDSP_SLUG}::
        )
    endif()

    set(STONEYDSP_TARGET_NAME "${STONEYDSP_TARGET_NAME}" PARENT_SCOPE)
endfunction(stoneydsp_add_stoneydsp)

#[==================================[Cleanup]==================================]
unset(${_STONEYDSP_BUILD_STATIC_OR_DYNAMIC})
unset(_version)
