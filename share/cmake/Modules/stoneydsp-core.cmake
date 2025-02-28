#[===============================[Include Guard]===============================]
include_guard(GLOBAL)

set(_version 0.0.0)

if(COMMAND stoneydsp_add_core)
    if(NOT DEFINED _stoneydsp_core_script_version OR NOT(_version STREQUAL _stoneydsp_core_script_version))
        message(WARNING "More than one 'stoneydsp-core.cmake' version has been included in this project.")
    endif()

    # 'stoneydsp-core.cmake' has already been included! Don't do anything
    return()
endif()

set(_stoneydsp_core_script_version "${_version}" CACHE INTERNAL "Current 'stoneydsp-core.cmake' version. Used for checking for conflicts")

set(_stoneydsp_core_script_file "${CMAKE_CURRENT_LIST_FILE}" CACHE INTERNAL "Path to current 'stoneydsp-core.cmake' script")

if(NOT DEFINED STONEYDSP_BINARY_DIR)
    set(STONEYDSP_BINARY_DIR "${CMAKE_BINARY_DIR}")
endif(NOT DEFINED STONEYDSP_BINARY_DIR)

#[============================[stoneydsp_add_core]============================]
option(STONEYDSP_EXPORTS "" ON)
cmake_dependent_option(STONEYDSP_CORE_TARGET_INSTALL "Notes" ON "STONEYDSP_BUILD_CORE" ON)
cmake_dependent_option(STONEYDSP_CORE_TARGET_EXPORT "Notes" ON "STONEYDSP_BUILD_CORE" ON)
include(CMakeDependentOption)

#[==[
Adds target: `stoneydsp::core`
]==]
function(stoneydsp_add_core)
    # Generate target properties
    set(STONEYDSP_CORE_TARGET_NAME "core")
    set(STONEYDSP_CORE_VERSION_MAJOR "0")
    set(STONEYDSP_CORE_VERSION_MINOR "0")
    set(STONEYDSP_CORE_VERSION_BUILD "0")
    set(STONEYDSP_CORE_VERSION "${STONEYDSP_CORE_VERSION_MAJOR}.${STONEYDSP_CORE_VERSION_MINOR}.${STONEYDSP_CORE_VERSION_BUILD}")
    set(STONEYDSP_CORE_HEADERS_FILESET_NAME "stoneydsp_CORE_PUBLIC_HEADERS")

    # system/platform.h
    set(STONEYDSP_CORE_SYSTEM_PLATFORM_H_FILE "${STONEYDSP_INCLUDE_DIR}/${STONEYDSP_SLUG}/${STONEYDSP_CORE_TARGET_NAME}/system/platform.h")

    # system/compiler.h
    set(STONEYDSP_CORE_SYSTEM_COMPILER_H_FILE "${STONEYDSP_INCLUDE_DIR}/${STONEYDSP_SLUG}/${STONEYDSP_CORE_TARGET_NAME}/system/compiler.h")

    # system/languages.h
    set(STONEYDSP_CORE_SYSTEM_LANGUAGES_H_FILE "${STONEYDSP_INCLUDE_DIR}/${STONEYDSP_SLUG}/${STONEYDSP_CORE_TARGET_NAME}/system/languages.h")

    # system/cxx.h
    set(STONEYDSP_CORE_SYSTEM_CXX_H_FILE "${STONEYDSP_INCLUDE_DIR}/${STONEYDSP_SLUG}/${STONEYDSP_CORE_TARGET_NAME}/system/cxx.h")

    # system/types.h
    set(STONEYDSP_CORE_SYSTEM_TYPES_H_FILE "${STONEYDSP_INCLUDE_DIR}/${STONEYDSP_SLUG}/${STONEYDSP_CORE_TARGET_NAME}/system/types.h")

    # core.h|cpp
    set(STONEYDSP_CORE_H_FILE "${STONEYDSP_INCLUDE_DIR}/${STONEYDSP_SLUG}/${STONEYDSP_CORE_TARGET_NAME}/${STONEYDSP_CORE_TARGET_NAME}.h")
    set(STONEYDSP_CORE_CPP_FILE "${STONEYDSP_SRC_DIR}/${STONEYDSP_SLUG}/${STONEYDSP_CORE_TARGET_NAME}/${STONEYDSP_CORE_TARGET_NAME}.cpp")

    # List header files (public)
    set(STONEYDSP_CORE_HEADER_FILES)
    list(APPEND STONEYDSP_CORE_HEADER_FILES
        "${STONEYDSP_CORE_SYSTEM_PLATFORM_H_FILE}"
        "${STONEYDSP_CORE_SYSTEM_COMPILER_H_FILE}"
        "${STONEYDSP_CORE_SYSTEM_LANGUAGES_H_FILE}"
        "${STONEYDSP_CORE_SYSTEM_CXX_H_FILE}"
        "${STONEYDSP_CORE_SYSTEM_TYPES_H_FILE}"
        "${STONEYDSP_CORE_H_FILE}"
    )

    # List source files (private)
    set(STONEYDSP_CORE_SOURCE_FILES)
    list(APPEND STONEYDSP_CORE_SOURCE_FILES
        "${STONEYDSP_CORE_CPP_FILE}"
    )

    # List link libraries (private)
    set(STONEYDSP_CORE_LINK_LIBRARIES_PRIVATE)
    list(APPEND STONEYDSP_CORE_LINK_LIBRARIES_PRIVATE)

    # List link libraries (public)
    set(STONEYDSP_CORE_LINK_LIBRARIES_PUBLIC)
    list(APPEND STONEYDSP_CORE_LINK_LIBRARIES_PUBLIC)

    # List link libraries (interface)
    set(STONEYDSP_CORE_LINK_LIBRARIES_INTERFACE)
    list(APPEND STONEYDSP_CORE_LINK_LIBRARIES_INTERFACE)

    # List compile definitions (private)
    set(STONEYDSP_CORE_COMPILE_DEFINITIONS_PRIVATE)
    list(APPEND STONEYDSP_CORE_COMPILE_DEFINITIONS_PRIVATE)

    # List compile definitions (public)
    set(STONEYDSP_CORE_COMPILE_DEFINITIONS_PUBLIC)
    list(APPEND STONEYDSP_CORE_COMPILE_DEFINITIONS_PUBLIC
        "-DSTONEYDSP_BUILD_CORE=1"
        "-DSTONEYDSP_CORE_VERSION_MAJOR=${STONEYDSP_CORE_VERSION_MAJOR}"
        "-DSTONEYDSP_CORE_VERSION_MINOR=${STONEYDSP_CORE_VERSION_MINOR}"
        "-DSTONEYDSP_CORE_VERSION_BUILD=${STONEYDSP_CORE_VERSION_BUILD}"
        "-DSTONEYDSP_CORE_VERSION=${STONEYDSP_CORE_VERSION}"
    )

    if(STONEYDSP_EXPORTS)
        list(APPEND STONEYDSP_CORE_COMPILE_DEFINITIONS_PUBLIC
            "-DSTONEYDSP_EXPORTS=1"
        )
    endif(STONEYDSP_EXPORTS)

    # List compile definitions (interface)
    set(STONEYDSP_CORE_COMPILE_DEFINITIONS_INTERFACE)
    list(APPEND STONEYDSP_CORE_COMPILE_DEFINITIONS_INTERFACE)

    # List compile options (interface)
    set(STONEYDSP_CORE_COMPILE_OPTIONS_INTERFACE)
    list(APPEND STONEYDSP_CORE_COMPILE_OPTIONS_INTERFACE)

    # List compile options (private)
    set(STONEYDSP_CORE_COMPILE_OPTIONS_PRIVATE)
    list(APPEND STONEYDSP_CORE_COMPILE_OPTIONS_PRIVATE)

    # List compile options (public)
    set(STONEYDSP_CORE_COMPILE_OPTIONS_PUBLIC)
    list(APPEND STONEYDSP_CORE_COMPILE_OPTIONS_PUBLIC)

    # List compile features (interface)
    set(STONEYDSP_CORE_COMPILE_FEATURES_INTERFACE)
    list(APPEND STONEYDSP_CORE_COMPILE_FEATURES_INTERFACE)

    # List compile features (private)
    set(STONEYDSP_CORE_COMPILE_FEATURES_PRIVATE)
    list(APPEND STONEYDSP_CORE_COMPILE_FEATURES_PRIVATE)

    # List compile features (public)
    set(STONEYDSP_CORE_COMPILE_FEATURES_PUBLIC)
    list(APPEND STONEYDSP_CORE_COMPILE_FEATURES_PUBLIC
        cxx_std_11
        cxx_rvalue_references
        cxx_range_for
        cxx_nullptr
        cxx_override
        cxx_noexcept
        cxx_long_long_type
        cxx_lambdas
        cxx_deleted_functions
        cxx_decltype
        cxx_constexpr
        cxx_auto_type
        cxx_alignof
        cxx_alignas
        cxx_attributes
        cxx_alias_templates
        cxx_enum_forward_declarations
        cxx_explicit_conversions
        cxx_extern_templates
        cxx_static_assert

        # # 98
        cxx_template_template_parameters

        # # <CC>
        # # 11
        c_std_11
        c_static_assert
        c_variadic_macros
    )

    add_library(${STONEYDSP_CORE_TARGET_NAME} OBJECT)
    add_library(${STONEYDSP_SLUG}::${STONEYDSP_CORE_TARGET_NAME} ALIAS ${STONEYDSP_CORE_TARGET_NAME})
    add_library(${STONEYDSP_BRAND}::${STONEYDSP_SLUG}::${STONEYDSP_CORE_TARGET_NAME} ALIAS ${STONEYDSP_CORE_TARGET_NAME})

    set_target_properties(${STONEYDSP_CORE_TARGET_NAME}
        PROPERTIES

        VERSION "${STONEYDSP_CORE_VERSION}"
        SOVERSION "${STONEYDSP_CORE_VERSION_MAJOR}"

        RUNTIME_OUTPUT_DIRECTORY "${STONEYDSP_BINARY_DIR}/bin"
        PDB_OUTPUT_DIRECTORY "${STONEYDSP_BINARY_DIR}/lib"
        LIBRARY_OUTPUT_DIRECTORY "${STONEYDSP_BINARY_DIR}/lib"
        ARCHIVE_OUTPUT_DIRECTORY "${STONEYDSP_BINARY_DIR}/lib"
    )

    foreach(STONEYDSP_CORE_HEADER_FILE IN LISTS STONEYDSP_CORE_HEADER_FILES)
        message(DEBUG "Target: ${STONEYDSP_CORE_TARGET_NAME} - adding header: ${STONEYDSP_CORE_HEADER_FILE}")
        configure_file("${STONEYDSP_CORE_HEADER_FILE}" "${STONEYDSP_CORE_HEADER_FILE}")
        target_sources(${STONEYDSP_CORE_TARGET_NAME}
            PUBLIC
            FILE_SET ${STONEYDSP_CORE_HEADERS_FILESET_NAME}
            TYPE HEADERS
            BASE_DIRS
            $<BUILD_INTERFACE:${STONEYDSP_DIR}/${STONEYDSP_INCLUDE_DIR}>
            $<INSTALL_INTERFACE:${STONEYDSP_INCLUDE_DIR}>
            FILES
            $<BUILD_INTERFACE:${STONEYDSP_DIR}/${STONEYDSP_CORE_HEADER_FILE}>
            $<INSTALL_INTERFACE:${STONEYDSP_CORE_HEADER_FILE}>
        )
        message(VERBOSE "Target: ${STONEYDSP_CORE_TARGET_NAME} - added header: ${STONEYDSP_CORE_HEADER_FILE}")
    endforeach(STONEYDSP_CORE_HEADER_FILE IN LISTS STONEYDSP_CORE_HEADER_FILES)

    foreach(STONEYDSP_CORE_SOURCE_FILE IN LISTS STONEYDSP_CORE_SOURCE_FILES)
        message(DEBUG "Target: ${STONEYDSP_CORE_TARGET_NAME} - adding source: ${STONEYDSP_CORE_SOURCE_FILE}")
        target_sources(${STONEYDSP_CORE_TARGET_NAME}
            PRIVATE
            "${STONEYDSP_CORE_SOURCE_FILE}"
        )
        message(VERBOSE "Target: ${STONEYDSP_CORE_TARGET_NAME} - added source: ${STONEYDSP_CORE_SOURCE_FILE}")
    endforeach(STONEYDSP_CORE_SOURCE_FILE IN LISTS STONEYDSP_CORE_SOURCE_FILES)

    foreach(STONEYDSP_CORE_LINK_LIBRARY IN LISTS STONEYDSP_CORE_LINK_LIBRARIES_PRIVATE)
        message(DEBUG "Target: ${STONEYDSP_CORE_TARGET_NAME} - linking library (private): ${STONEYDSP_CORE_LINK_LIBRARY}")
        target_link_libraries(${STONEYDSP_CORE_TARGET_NAME}
            PRIVATE
            ${STONEYDSP_CORE_LINK_LIBRARY}
        )
        message(VERBOSE "Target: ${STONEYDSP_CORE_TARGET_NAME} - linked library (private): ${STONEYDSP_CORE_LINK_LIBRARY}")
    endforeach(STONEYDSP_CORE_LINK_LIBRARY IN LISTS STONEYDSP_CORE_LINK_LIBRARIES_PRIVATE)

    foreach(STONEYDSP_CORE_LINK_LIBRARY IN LISTS STONEYDSP_CORE_LINK_LIBRARIES_PUBLIC)
        message(DEBUG "Target: ${STONEYDSP_CORE_TARGET_NAME} - linking library (public): ${STONEYDSP_CORE_LINK_LIBRARY}")
        target_link_libraries(${STONEYDSP_CORE_TARGET_NAME}
            PUBLIC
            ${STONEYDSP_CORE_LINK_LIBRARY}
        )
        message(VERBOSE "Target: ${STONEYDSP_CORE_TARGET_NAME} - linked library (public): ${STONEYDSP_CORE_LINK_LIBRARY}")
    endforeach(STONEYDSP_CORE_LINK_LIBRARY IN LISTS STONEYDSP_CORE_LINK_LIBRARIES_PUBLIC)

    foreach(STONEYDSP_CORE_LINK_LIBRARY IN LISTS STONEYDSP_CORE_LINK_LIBRARIES_INTERFACE)
        message(DEBUG "Target: ${STONEYDSP_CORE_TARGET_NAME} - linking library (interface): ${STONEYDSP_CORE_LINK_LIBRARY}")
        target_link_libraries(${STONEYDSP_CORE_TARGET_NAME}
            INTERFACE
            ${STONEYDSP_CORE_LINK_LIBRARY}
        )
        message(VERBOSE "Target: ${STONEYDSP_CORE_TARGET_NAME} - linked library (interface): ${STONEYDSP_CORE_LINK_LIBRARY}")
    endforeach(STONEYDSP_CORE_LINK_LIBRARY IN LISTS STONEYDSP_CORE_LINK_LIBRARIES_INTERFACE)

    foreach(STONEYDSP_CORE_COMPILE_DEFINITION IN LISTS STONEYDSP_CORE_COMPILE_DEFINITIONS_PRIVATE)
        message(DEBUG "Target: ${STONEYDSP_CORE_TARGET_NAME} - adding compile definiton (private): ${STONEYDSP_CORE_COMPILE_DEFINITION}")
        target_compile_definitions(${STONEYDSP_CORE_TARGET_NAME}
            PRIVATE
            ${STONEYDSP_CORE_COMPILE_DEFINITION}
        )
        message(VERBOSE "Target: ${STONEYDSP_CORE_TARGET_NAME} - added compile definiton (private): ${STONEYDSP_CORE_COMPILE_DEFINITION}")
    endforeach(STONEYDSP_CORE_COMPILE_DEFINITION IN LISTS STONEYDSP_CORE_COMPILE_DEFINITIONS_PRIVATE)

    foreach(STONEYDSP_CORE_COMPILE_DEFINITION IN LISTS STONEYDSP_CORE_COMPILE_DEFINITIONS_PUBLIC)
        message(DEBUG "Target: ${STONEYDSP_CORE_TARGET_NAME} - adding compile definiton (public): ${STONEYDSP_CORE_COMPILE_DEFINITION}")
        target_compile_definitions(${STONEYDSP_CORE_TARGET_NAME}
            PUBLIC
            ${STONEYDSP_CORE_COMPILE_DEFINITION}
        )
        message(VERBOSE "Target: ${STONEYDSP_CORE_TARGET_NAME} - added compile definiton (public): ${STONEYDSP_CORE_COMPILE_DEFINITION}")
    endforeach(STONEYDSP_CORE_COMPILE_DEFINITION IN LISTS STONEYDSP_CORE_COMPILE_DEFINITIONS_PUBLIC)

    foreach(STONEYDSP_CORE_COMPILE_DEFINITION IN LISTS STONEYDSP_CORE_COMPILE_DEFINITIONS_INTERFACE)
        message(DEBUG "Target: ${STONEYDSP_CORE_TARGET_NAME} - adding compile definiton (interface): ${STONEYDSP_CORE_COMPILE_DEFINITION}")
        target_compile_definitions(${STONEYDSP_CORE_TARGET_NAME}
            INTERFACE
            ${STONEYDSP_CORE_COMPILE_DEFINITION}
        )
        message(VERBOSE "Target: ${STONEYDSP_CORE_TARGET_NAME} - added compile definiton (interface): ${STONEYDSP_CORE_COMPILE_DEFINITION}")
    endforeach(STONEYDSP_CORE_COMPILE_DEFINITION IN LISTS STONEYDSP_CORE_COMPILE_DEFINITIONS_INTERFACE)

    foreach(STONEYDSP_CORE_COMPILE_OPTION IN LISTS STONEYDSP_CORE_COMPILE_OPTIONS_PRIVATE)
        message(DEBUG "Target: ${STONEYDSP_CORE_TARGET_NAME} - adding compile option (private): ${STONEYDSP_CORE_COMPILE_OPTION}")
        target_compile_options(${STONEYDSP_CORE_TARGET_NAME}
            PRIVATE
            ${STONEYDSP_CORE_COMPILE_OPTION}
        )
        message(VERBOSE "Target: ${STONEYDSP_CORE_TARGET_NAME} - added compile option (private): ${STONEYDSP_CORE_COMPILE_OPTION}")
    endforeach(STONEYDSP_CORE_COMPILE_OPTION IN LISTS STONEYDSP_CORE_COMPILE_OPTIONS_PRIVATE)

    foreach(STONEYDSP_CORE_COMPILE_OPTION IN LISTS STONEYDSP_CORE_COMPILE_OPTIONS_PUBLIC)
        message(DEBUG "Target: ${STONEYDSP_CORE_TARGET_NAME} - adding compile option (public): ${STONEYDSP_CORE_COMPILE_OPTION}")
        target_compile_options(${STONEYDSP_CORE_TARGET_NAME}
            PUBLIC
            ${STONEYDSP_CORE_COMPILE_OPTION}
        )
        message(VERBOSE "Target: ${STONEYDSP_CORE_TARGET_NAME} - added compile option (public): ${STONEYDSP_CORE_COMPILE_OPTION}")
    endforeach(STONEYDSP_CORE_COMPILE_OPTION IN LISTS STONEYDSP_CORE_COMPILE_OPTIONS_PUBLIC)

    foreach(STONEYDSP_CORE_COMPILE_OPTION IN LISTS STONEYDSP_CORE_COMPILE_OPTIONS_INTERFACE)
        message(DEBUG "Target: ${STONEYDSP_CORE_TARGET_NAME} - adding compile option (interface): ${STONEYDSP_CORE_COMPILE_OPTION}")
        target_compile_options(${STONEYDSP_CORE_TARGET_NAME}
            INTERFACE
            ${STONEYDSP_CORE_COMPILE_OPTION}
        )
        message(VERBOSE "Target: ${STONEYDSP_CORE_TARGET_NAME} - added compile option (interface): ${STONEYDSP_CORE_COMPILE_OPTION}")
    endforeach(STONEYDSP_CORE_COMPILE_OPTION IN LISTS STONEYDSP_CORE_COMPILE_OPTIONS_INTERFACE)

    foreach(STONEYDSP_CORE_COMPILE_FEATURE IN LISTS STONEYDSP_CORE_COMPILE_FEATURES_PRIVATE)
        message(DEBUG "Target: ${STONEYDSP_CORE_TARGET_NAME} - adding compile feature (private): ${STONEYDSP_CORE_COMPILE_FEATURE}")
        target_compile_features(${STONEYDSP_CORE_TARGET_NAME}
            PRIVATE
            ${STONEYDSP_CORE_COMPILE_FEATURE}
        )
        message(VERBOSE "Target: ${STONEYDSP_CORE_TARGET_NAME} - added compile feature (private): ${STONEYDSP_CORE_COMPILE_FEATURE}")
    endforeach(STONEYDSP_CORE_COMPILE_FEATURE IN LISTS STONEYDSP_CORE_COMPILE_FEATURES_PRIVATE)

    foreach(STONEYDSP_CORE_COMPILE_FEATURE IN LISTS STONEYDSP_CORE_COMPILE_FEATURES_PUBLIC)
        message(DEBUG "Target: ${STONEYDSP_CORE_TARGET_NAME} - adding compile feature (public): ${STONEYDSP_CORE_COMPILE_FEATURE}")
        target_compile_features(${STONEYDSP_CORE_TARGET_NAME}
            PUBLIC
            ${STONEYDSP_CORE_COMPILE_FEATURE}
        )
        message(VERBOSE "Target: ${STONEYDSP_CORE_TARGET_NAME} - added compile feature (public): ${STONEYDSP_CORE_COMPILE_FEATURE}")
    endforeach(STONEYDSP_CORE_COMPILE_FEATURE IN LISTS STONEYDSP_CORE_COMPILE_FEATURES_PUBLIC)

    foreach(STONEYDSP_CORE_COMPILE_FEATURE IN LISTS STONEYDSP_CORE_COMPILE_FEATURES_INTERFACE)
        message(DEBUG "Target: ${STONEYDSP_CORE_TARGET_NAME} - adding compile feature (interface): ${STONEYDSP_CORE_COMPILE_FEATURE}")
        target_compile_features(${STONEYDSP_CORE_TARGET_NAME}
            INTERFACE
            ${STONEYDSP_CORE_COMPILE_FEATURE}
        )
        message(VERBOSE "Target: ${STONEYDSP_CORE_TARGET_NAME} - added compile feature (interface): ${STONEYDSP_CORE_COMPILE_FEATURE}")
    endforeach(STONEYDSP_CORE_COMPILE_FEATURE IN LISTS STONEYDSP_CORE_COMPILE_FEATURES_INTERFACE)

    if(STONEYDSP_CORE_TARGET_INSTALL)
        # Generate export set
        install(TARGETS ${STONEYDSP_CORE_TARGET_NAME}
            EXPORT ${STONEYDSP_CORE_TARGET_NAME}Install
            COMPONENT ${STONEYDSP_CORE_TARGET_NAME}
            LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
            RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
            ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
            INCLUDES DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
            FILE_SET ${STONEYDSP_CORE_HEADERS_FILESET_NAME} DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
        )

        # Install export set
        install(EXPORT ${STONEYDSP_CORE_TARGET_NAME}Install
            FILE "${STONEYDSP_SLUG}-${STONEYDSP_CORE_TARGET_NAME}-targets.cmake"
            NAMESPACE ${STONEYDSP_BRAND}::${STONEYDSP_SLUG}::
            DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/${STONEYDSP_BRAND}"
        )
    endif()

    if(STONEYDSP_CORE_TARGET_EXPORT)
        # Generate export set
        export(
            SETUP ${STONEYDSP_CORE_TARGET_NAME}Export
            TARGET ${STONEYDSP_CORE_TARGET_NAME}
        )

        # Install export set
        export(
            EXPORT ${STONEYDSP_CORE_TARGET_NAME}Export
            FILE "lib/cmake/${STONEYDSP_BRAND}/${STONEYDSP_SLUG}-${STONEYDSP_CORE_TARGET_NAME}-targets.cmake"
            NAMESPACE ${STONEYDSP_BRAND}::${STONEYDSP_SLUG}::
        )
    endif()

    # Pass target properties to parent scope
    set(STONEYDSP_CORE_TARGET_NAME "${STONEYDSP_CORE_TARGET_NAME}" PARENT_SCOPE)
    set(STONEYDSP_CORE_VERSION_MAJOR "${STONEYDSP_CORE_VERSION_MAJOR}" PARENT_SCOPE)
    set(STONEYDSP_CORE_VERSION_MINOR "${STONEYDSP_CORE_VERSION_MINOR}" PARENT_SCOPE)
    set(STONEYDSP_CORE_VERSION_BUILD "${STONEYDSP_CORE_VERSION_BUILD}" PARENT_SCOPE)
    set(STONEYDSP_CORE_VERSION "${STONEYDSP_CORE_VERSION_MAJOR}.${STONEYDSP_CORE_VERSION_MINOR}.${STONEYDSP_CORE_VERSION_BUILD}")
    set(STONEYDSP_CORE_HEADER_FILES "${STONEYDSP_CORE_HEADER_FILES}" PARENT_SCOPE)
    set(STONEYDSP_CORE_SOURCE_FILES "${STONEYDSP_CORE_SOURCE_FILES}" PARENT_SCOPE)
    set(STONEYDSP_CORE_LINK_LIBRARIES_PRIVATE "${STONEYDSP_CORE_LINK_LIBRARIES_PRIVATE}" PARENT_SCOPE)
endfunction(stoneydsp_add_core)

#[==================================[Cleanup]==================================]
unset(_version)
