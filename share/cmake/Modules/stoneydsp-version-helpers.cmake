option(STONEYDSP_GENERATE_VERSIONS "" OFF)

set(_STONEYDSP_MANAGED_VERSION)

macro(stoneydsp_file_versions)
    file(READ "${CMAKE_CURRENT_SOURCE_DIR}/VERSION" _STONEYDSP_MANAGED_VERSION)
    string(STRIP "${_STONEYDSP_MANAGED_VERSION}" _STONEYDSP_MANAGED_VERSION)
endmacro(stoneydsp_file_versions)

macro(stoneydsp_git_versions)
    # https://softwareengineering.stackexchange.com/questions/141973/how-do-you-achieve-a-numeric-versioning-scheme-with-git
    # 'git rev-list HEAD | wc -l'
    find_package(Git REQUIRED)
    execute_process(
        COMMAND "${GIT_EXECUTABLE}" "rev-list" "HEAD"
        COMMAND "wc" "-l"
        WORKING_DIRECTORY "${STONEYDSP_SOURCE_DIR}"
        OUTPUT_VARIABLE _STONEYDSP_GIT_COMMIT_COUNT
        ERROR_VARIABLE _STONEYDSP_GIT_COMMIT_COUNT_ERROR
    )

    if(_STONEYDSP_GIT_COMMIT_COUNT_ERROR)
        message(SEND_ERROR "${_STONEYDSP_GIT_COMMIT_COUNT_ERROR}")
    endif()

    execute_process(
        COMMAND "${GIT_EXECUTABLE}" "rev-parse" "HEAD"
        WORKING_DIRECTORY "${STONEYDSP_SOURCE_DIR}"
        OUTPUT_VARIABLE _STONEYDSP_GIT_REF_HEAD
        ERROR_VARIABLE _STONEYDSP_GIT_REF_HEAD_ERROR
    )

    if(_STONEYDSP_GIT_REF_HEAD_ERROR)
        message(SEND_ERROR "${_STONEYDSP_GIT_REF_HEAD_ERROR}")
    endif()

    execute_process(
        COMMAND "${GIT_EXECUTABLE}" "rev-parse" "--short" "HEAD"
        WORKING_DIRECTORY "${STONEYDSP_SOURCE_DIR}"
        OUTPUT_VARIABLE _STONEYDSP_GIT_REF_HEAD_SHORT
        ERROR_VARIABLE _STONEYDSP_GIT_REF_HEAD_SHORT_ERROR
    )

    if(_STONEYDSP_GIT_REF_HEAD_SHORT_ERROR)
        message(SEND_ERROR "${_STONEYDSP_GIT_REF_HEAD_SHORT_ERROR}")
    endif()

    execute_process(
        COMMAND "${GIT_EXECUTABLE}" rev-parse --abbrev-ref --symbolic-full-name HEAD
        WORKING_DIRECTORY "${STONEYDSP_SOURCE_DIR}"
        OUTPUT_VARIABLE _STONEYDSP_GIT_BRANCH
        ERROR_VARIABLE _STONEYDSP_GIT_BRANCH_ERROR
    )

    if(_STONEYDSP_GIT_BRANCH_ERROR)
        message(SEND_ERROR "${_STONEYDSP_GIT_BRANCH_ERROR}")
    endif()

    string(STRIP "${_STONEYDSP_GIT_COMMIT_COUNT}" STONEYDSP_GIT_COMMIT_COUNT)
    string(STRIP "${_STONEYDSP_GIT_REF_HEAD}" _STONEYDSP_GIT_REF_HEAD)
    string(STRIP "${_STONEYDSP_GIT_REF_HEAD_SHORT}" _STONEYDSP_GIT_REF_HEAD_SHORT)
    string(STRIP "${_STONEYDSP_GIT_BRANCH}" STONEYDSP_GIT_BRANCH)

    string(HEX "${_STONEYDSP_GIT_REF_HEAD}" STONEYDSP_GIT_REF_HEAD)
    string(HEX "${_STONEYDSP_GIT_REF_HEAD_SHORT}" STONEYDSP_GIT_REF_HEAD_SHORT)

    set(_STONEYDSP_MANAGED_VERSION "0.0.${STONEYDSP_GIT_COMMIT_COUNT}.${STONEYDSP_GIT_REF_HEAD_SHORT}")
endmacro(stoneydsp_git_versions)

macro(stoneydsp_git_module_versions MODULE)
    set(${MODULE}_VERSION_MAJOR "${STONEYDSP_VERSION_MAJOR}")
    set(${MODULE}_VERSION_MINOR "${STONEYDSP_VERSION_MINOR}")
    execute_process(
        COMMAND "${GIT_EXECUTABLE}" rev-list origin/module/${MODULE}
        COMMAND wc -l
        OUTPUT_VARIABLE ${MODULE}_VERSION_PATCH
        ERROR_VARIABLE _${MODULE}_VERSION_PATCH
    )

    if(${_${MODULE}_VERSION_PATCH})
        message(WARNING "git: could not find a corresponding module/${MODULE} branch for module ${MODULE}")
    endif()

    string(STRIP "${${MODULE}_VERSION_PATCH}" ${MODULE}_VERSION_PATCH)
    set(${MODULE}_VERSION "${${MODULE}_VERSION_MAJOR}.${${MODULE}_VERSION_MINOR}.${${MODULE}_VERSION_PATCH}")
endmacro(stoneydsp_git_module_versions)
