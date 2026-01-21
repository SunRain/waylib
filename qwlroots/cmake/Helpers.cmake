function(add_cmake_module name library include_dir)
    set(_cmake_install_dir "${CMAKE_INSTALL_LIBDIR}/cmake/${name}")
    include(CMakePackageConfigHelpers)
    configure_package_config_file(${PROJECT_SOURCE_DIR}/src/cmake/CMakeConfig.cmake.in
        ${CMAKE_CURRENT_BINARY_DIR}/${name}Config.cmake
        INSTALL_DESTINATION ${_cmake_install_dir}
    )
    write_basic_package_version_file(
      ${CMAKE_CURRENT_BINARY_DIR}/${name}ConfigVersion.cmake
      VERSION ${PROJECT_VERSION}
      COMPATIBILITY AnyNewerVersion
    )

    # 导出构建目录中的配置文件，以便子模块使用
    export(EXPORT ${name}Targets
        FILE "${CMAKE_CURRENT_BINARY_DIR}/${name}Targets.cmake"
        NAMESPACE ${name}::
    )

    install(FILES
        ${CMAKE_CURRENT_BINARY_DIR}/${name}Config.cmake
        ${CMAKE_CURRENT_BINARY_DIR}/${name}ConfigVersion.cmake
        DESTINATION ${_cmake_install_dir}
    )

    install(EXPORT ${name}Targets
        FILE ${name}Targets.cmake
        NAMESPACE ${name}::
        DESTINATION ${_cmake_install_dir}
    )
endfunction()

function(add_pkgconfig_module name library include_dir depends)
    # For cmake
    include(CMakePackageConfigHelpers)
    configure_file(${PROJECT_SOURCE_DIR}/src/cmake/pkgconfig.pc.in
        ${CMAKE_CURRENT_BINARY_DIR}/${name}.pc
    )
    install(FILES
        ${CMAKE_CURRENT_BINARY_DIR}/${name}.pc
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/pkgconfig
    )
endfunction()
