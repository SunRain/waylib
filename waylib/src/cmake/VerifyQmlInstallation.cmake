# VerifyQmlInstallation.cmake - 验证QML安装路径和模块加载
#
# 此脚本用于验证QML模块是否正确安装并可以在运行时加载

cmake_minimum_required(VERSION 3.21)

# 函数：验证QML安装路径
function(verify_qml_install_path qml_dir result_var)
    set(${result_var} FALSE PARENT_SCOPE)

    # 检查路径是否存在
    if(NOT EXISTS "${qml_dir}")
        message(WARNING "QML install directory does not exist: ${qml_dir}")
        return()
    endif()

    # 检查是否可写（对于安装过程）
    if(CMAKE_INSTALL_PREFIX)
        # 在安装时检查目标目录
        set(target_dir "${CMAKE_INSTALL_PREFIX}/${qml_dir}")
        if(NOT EXISTS "${target_dir}")
            message(STATUS "QML target directory will be created: ${target_dir}")
        endif()
    endif()

    # 检查路径是否为绝对路径
    if(NOT IS_ABSOLUTE "${qml_dir}")
        message(WARNING "QML install path should be absolute: ${qml_dir}")
        return()
    endif()

    set(${result_var} TRUE PARENT_SCOPE)
    message(STATUS "QML install path verified: ${qml_dir}")
endfunction()

# 函数：验证QML模块文件
function(verify_qml_module_files module_dir result_var)
    set(${result_var} FALSE PARENT_SCOPE)

    # 检查qmldir文件
    set(qmldir_file "${module_dir}/qmldir")
    if(NOT EXISTS "${qmldir_file}")
        message(WARNING "qmldir file not found: ${qmldir_file}")
        return()
    endif()

    # 检查plugins.qmltypes文件
    set(qmltypes_file "${module_dir}/plugins.qmltypes")
    if(NOT EXISTS "${qmltypes_file}")
        message(WARNING "plugins.qmltypes file not found: ${qmltypes_file}")
        return()
    endif()

    # 读取并验证qmldir内容
    file(READ "${qmldir_file}" qmldir_content)
    if(NOT qmldir_content MATCHES "module")
        message(WARNING "Invalid qmldir file: missing module declaration")
        return()
    endif()

    set(${result_var} TRUE PARENT_SCOPE)
    message(STATUS "QML module files verified in: ${module_dir}")
endfunction()

# 函数：生成QML测试文件
function(generate_qml_test_file output_file module_uri)
    set(test_content "import QtQuick 2.15
import ${module_uri} 1.0

Item {
    // QML模块加载测试
    Component.onCompleted: {
        console.log(\"QML module ${module_uri} loaded successfully\")
    }
}
")

    file(WRITE "${output_file}" "${test_content}")
    message(STATUS "Generated QML test file: ${output_file}")
endfunction()

# 主验证函数
function(verify_qml_installation qml_dir module_uri)
    message(STATUS "Verifying QML installation...")

    # 验证安装路径
    verify_qml_install_path("${qml_dir}" path_valid)
    if(NOT path_valid)
        message(FATAL_ERROR "QML installation path verification failed")
    endif()

    # 验证模块文件（如果已生成）
    set(module_dir "${qml_dir}/${module_uri}")
    if(EXISTS "${module_dir}")
        verify_qml_module_files("${module_dir}" module_valid)
        if(NOT module_valid)
            message(WARNING "QML module files verification failed")
        endif()
    else()
        message(STATUS "QML module directory not yet created: ${module_dir}")
    endif()

    # 生成测试文件
    set(test_file "${CMAKE_CURRENT_BINARY_DIR}/qml_test.qml")
    generate_qml_test_file("${test_file}" "${module_uri}")

    message(STATUS "QML installation verification completed")
endfunction()
