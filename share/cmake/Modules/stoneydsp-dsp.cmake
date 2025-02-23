#[===============================[Include Guard]===============================]
include_guard(GLOBAL)

set(_version 0.0.0)

if(COMMAND stoneydsp_add_dsp)
    if(NOT DEFINED _stoneydsp_dsp_script_version OR NOT(_version STREQUAL _stoneydsp_dsp_script_version))
        message(WARNING "More than one 'stoneydsp-dsp.cmake' version has been included in this project.")
    endif()

    # 'stoneydsp-dsp.cmake' has already been included! Don't do anything
    return()
endif()

set(_stoneydsp_dsp_script_version "${_version}" CACHE INTERNAL "Current 'stoneydsp-dsp.cmake' version. Used for checking for conflicts")

set(_stoneydsp_dsp_script_file "${CMAKE_CURRENT_LIST_FILE}" CACHE INTERNAL "Path to current 'stoneydsp-dsp.cmake' script")

#[============================[stoneydsp_add_dsp]============================]
cmake_dependent_option(STONEYDSP_DSP_TARGET_INSTALL "Notes" ON "STONEYDSP_BUILD_DSP" ON)
cmake_dependent_option(STONEYDSP_DSP_TARGET_EXPORT "Notes" ON "STONEYDSP_BUILD_DSP" ON)
include(CMakeDependentOption)

#[==[
Adds target: `stoneydsp::dsp`
]==]
function(stoneydsp_add_dsp)
    # Generate target properties
    set(STONEYDSP_DSP_TARGET_NAME "dsp")
    set(STONEYDSP_DSP_VERSION_MAJOR "0")
    set(STONEYDSP_DSP_VERSION_MINOR "0")
    set(STONEYDSP_DSP_VERSION_BUILD "0")
    set(STONEYDSP_DSP_VERSION "${STONEYDSP_DSP_VERSION_MAJOR}.${STONEYDSP_DSP_VERSION_MINOR}.${STONEYDSP_DSP_VERSION_BUILD}")
    set(STONEYDSP_DSP_HEADERS_FILESET_NAME "stoneydsp_DSP_PUBLIC_HEADERS")

    # dsp.h|cpp
    set(STONEYDSP_DSP_H_FILE "${STONEYDSP_INCLUDE_DIR}/${STONEYDSP_SLUG}/${STONEYDSP_DSP_TARGET_NAME}/${STONEYDSP_DSP_TARGET_NAME}.h")
    set(STONEYDSP_DSP_CPP_FILE "${STONEYDSP_SRC_DIR}/${STONEYDSP_SLUG}/${STONEYDSP_DSP_TARGET_NAME}/${STONEYDSP_DSP_TARGET_NAME}.cpp")

    # List header files (public)
    set(STONEYDSP_DSP_HEADER_FILES)
    list(APPEND STONEYDSP_DSP_HEADER_FILES
        ${STONEYDSP_DSP_H_FILE}
    )

    # List source files (private)
    set(STONEYDSP_DSP_SOURCE_FILES)
    list(APPEND STONEYDSP_DSP_SOURCE_FILES
        ${STONEYDSP_DSP_CPP_FILE}
    )

    # List link libraries (public)
    set(STONEYDSP_DSP_LINK_LIBRARIES_PUBLIC)
    list(APPEND STONEYDSP_DSP_LINK_LIBRARIES_PUBLIC
        ${STONEYDSP_BRAND}::${STONEYDSP_SLUG}::${STONEYDSP_CORE_TARGET_NAME}
    )

    # List compile definitions (public)
    set(STONEYDSP_DSP_COMPILE_DEFINITIONS_PUBLIC)
    list(APPEND STONEYDSP_DSP_COMPILE_DEFINITIONS_PUBLIC
        "-DSTONEYDSP_BUILD_DSP=1"
        "-DSTONEYDSP_DSP_VERSION_MAJOR=${STONEYDSP_DSP_VERSION_MAJOR}"
        "-DSTONEYDSP_DSP_VERSION_MINOR=${STONEYDSP_DSP_VERSION_MINOR}"
        "-DSTONEYDSP_DSP_VERSION_BUILD=${STONEYDSP_DSP_VERSION_BUILD}"
        "-DSTONEYDSP_DSP_VERSION=${STONEYDSP_DSP_VERSION}"
    )

    add_library(${STONEYDSP_DSP_TARGET_NAME} OBJECT)
    add_library(${STONEYDSP_SLUG}::${STONEYDSP_DSP_TARGET_NAME} ALIAS ${STONEYDSP_DSP_TARGET_NAME})
    add_library(${STONEYDSP_BRAND}::${STONEYDSP_SLUG}::${STONEYDSP_DSP_TARGET_NAME} ALIAS ${STONEYDSP_DSP_TARGET_NAME})

    set_target_properties(${STONEYDSP_DSP_TARGET_NAME}
        PROPERTIES

        VERSION "${STONEYDSP_DSP_VERSION}"
        SOVERSION "${STONEYDSP_DSP_VERSION_MAJOR}"

        RUNTIME_OUTPUT_DIRECTORY "${STONEYDSP_BINARY_DIR}/bin"
        PDB_OUTPUT_DIRECTORY "${STONEYDSP_BINARY_DIR}/lib"
        LIBRARY_OUTPUT_DIRECTORY "${STONEYDSP_BINARY_DIR}/lib"
        ARCHIVE_OUTPUT_DIRECTORY "${STONEYDSP_BINARY_DIR}/lib"
    )

    foreach(STONEYDSP_DSP_HEADER_FILE IN LISTS STONEYDSP_DSP_HEADER_FILES)
        message(DEBUG "Target: ${STONEYDSP_DSP_TARGET_NAME} - adding header: ${STONEYDSP_DSP_HEADER_FILE}")
        configure_file("${STONEYDSP_DSP_HEADER_FILE}" "${STONEYDSP_DSP_HEADER_FILE}")
        target_sources(${STONEYDSP_DSP_TARGET_NAME}
            PUBLIC
            FILE_SET ${STONEYDSP_DSP_HEADERS_FILESET_NAME}
            TYPE HEADERS
            BASE_DIRS
            $<BUILD_INTERFACE:${STONEYDSP_DIR}/${STONEYDSP_INCLUDE_DIR}>
            $<INSTALL_INTERFACE:${STONEYDSP_INCLUDE_DIR}>
            FILES
            $<BUILD_INTERFACE:${STONEYDSP_DIR}/${STONEYDSP_DSP_HEADER_FILE}>
            $<INSTALL_INTERFACE:${STONEYDSP_DSP_HEADER_FILE}>
        )
        message(VERBOSE "Target: ${STONEYDSP_DSP_TARGET_NAME} - added header: ${STONEYDSP_DSP_HEADER_FILE}")
    endforeach(STONEYDSP_DSP_HEADER_FILE IN LISTS STONEYDSP_DSP_HEADER_FILES)

    foreach(STONEYDSP_DSP_SOURCE_FILE IN LISTS STONEYDSP_DSP_SOURCE_FILES)
        message(DEBUG "Target: ${STONEYDSP_DSP_TARGET_NAME} - adding source: ${STONEYDSP_DSP_SOURCE_FILE}")
        target_sources(${STONEYDSP_DSP_TARGET_NAME}
            PRIVATE
            "${STONEYDSP_DSP_SOURCE_FILE}"
        )
        message(VERBOSE "Target: ${STONEYDSP_DSP_TARGET_NAME} - added source: ${STONEYDSP_DSP_SOURCE_FILE}")
    endforeach(STONEYDSP_DSP_SOURCE_FILE IN LISTS STONEYDSP_DSP_SOURCE_FILES)

    foreach(STONEYDSP_DSP_LINK_LIBRARY IN LISTS STONEYDSP_DSP_LINK_LIBRARIES_PUBLIC)
        message(DEBUG "Target: ${STONEYDSP_DSP_TARGET_NAME} - linking library (public): ${STONEYDSP_DSP_LINK_LIBRARY}")
        target_link_libraries(${STONEYDSP_DSP_TARGET_NAME}
            PUBLIC
            ${STONEYDSP_DSP_LINK_LIBRARY}
        )
        message(VERBOSE "Target: ${STONEYDSP_DSP_TARGET_NAME} - linked library (public): ${STONEYDSP_DSP_LINK_LIBRARY}")
    endforeach(STONEYDSP_DSP_LINK_LIBRARY IN LISTS STONEYDSP_DSP_LINK_LIBRARIES_PUBLIC)

    if(STONEYDSP_DSP_TARGET_INSTALL)
        # Generate export set
        install(TARGETS ${STONEYDSP_DSP_TARGET_NAME}
            EXPORT ${STONEYDSP_DSP_TARGET_NAME}Install
            COMPONENT ${STONEYDSP_DSP_TARGET_NAME}
            LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
            RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
            ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
            INCLUDES DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
            FILE_SET ${STONEYDSP_DSP_HEADERS_FILESET_NAME} DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
        )

        # Install export set
        install(EXPORT ${STONEYDSP_DSP_TARGET_NAME}Install
            FILE "${STONEYDSP_SLUG}-${STONEYDSP_DSP_TARGET_NAME}-targets.cmake"
            NAMESPACE ${STONEYDSP_BRAND}::${STONEYDSP_SLUG}::
            DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/${STONEYDSP_BRAND}"
        )
    endif()

    if(STONEYDSP_DSP_TARGET_EXPORT)
        # Generate export set
        export(
            SETUP ${STONEYDSP_DSP_TARGET_NAME}Export
            TARGET ${STONEYDSP_DSP_TARGET_NAME}
        )

        # Install export set
        export(
            EXPORT ${STONEYDSP_DSP_TARGET_NAME}Export
            FILE "lib/cmake/${STONEYDSP_BRAND}/${STONEYDSP_SLUG}-${STONEYDSP_DSP_TARGET_NAME}-targets.cmake"
            NAMESPACE ${STONEYDSP_BRAND}::${STONEYDSP_SLUG}::
        )
    endif()

    set(STONEYDSP_DSP_TARGET_NAME ${STONEYDSP_DSP_TARGET_NAME} PARENT_SCOPE)
endfunction()
