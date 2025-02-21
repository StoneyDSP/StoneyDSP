vcpkg_from_github(
    OUT_SOURCE_PATH SOURCE_PATH
    REPO StoneyDSP/StoneyDSP
    REF 2f9abd0dc94a764923d6ec22ba57840660c57794
    SHA512 0
    HEAD_REF feat/simd
)
vcpkg_check_features(OUT_FEATURE_OPTIONS FEATURE_OPTIONS
    FEATURES
    core STONEYDSP_BUILD_CORE
    simd STONEYDSP_BUILD_SIMD
)
vcpkg_cmake_configure(
    SOURCE_PATH "${SOURCE_PATH}"
    OPTIONS
    "-DSTONEYDSP_GENERATE_VERSIONS:BOOL=OFF"
    ${FEATURE_OPTIONS}
)
vcpkg_cmake_install()
vcpkg_cmake_config_fixup(
    PACKAGE_NAME stoneydsp
    CONFIG_PATH "lib/cmake/stoneydsp"
)
vcpkg_fixup_pkgconfig()
file(REMOVE_RECURSE "${CURRENT_PACKAGES_DIR}/debug/include")
file(
    INSTALL "${SOURCE_PATH}/LICENSE"
    DESTINATION "${CURRENT_PACKAGES_DIR}/share/${PORT}"
    RENAME copyright
)
