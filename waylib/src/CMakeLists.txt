set(CMAKE_INCLUDE_CURRENT_DIR ON)

include(CMakePackageConfigHelpers)

# 配置主包配置文件
configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/WaylibConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/WaylibConfig.cmake"
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/Waylib
)

# 创建版本文件
write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/WaylibConfigVersion.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMinorVersion
)

# 注意：WaylibTargets将在server子目录中定义

# 安装配置文件
install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/WaylibConfig.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/WaylibConfigVersion.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/Waylib
)

# 注意：WaylibTargets将在server子目录中定义

add_subdirectory(server)
