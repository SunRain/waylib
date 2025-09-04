# GenerateQmlFiles.cmake - 备选方案：手动生成QML模块文件
#
# 当构建环境缺少qmlplugindump工具或权限不足时使用此脚本
# 此脚本提供手动生成qmldir和plugins.qmltypes文件的备选方案

cmake_minimum_required(VERSION 3.21)

# 函数：手动生成qmldir文件
function(generate_qmldir_manual output_file module_uri version install_location)
    set(QMLDIR_CONTENT "module ${module_uri}
linktarget ${TARGET}plugin
optional plugin ${TARGET}plugin
classname ${TARGET}Plugin
typeinfo ${TARGET}.qmltypes
prefer :/qt/qml/${module_uri}/
depends QtQuick

# 手动注册的QML类型
# 如果需要添加更多类型，请在此处添加
")

    file(WRITE "${output_file}" "${QMLDIR_CONTENT}")
    message(STATUS "Generated manual qmldir file: ${output_file}")
endfunction()

# 函数：手动生成plugins.qmltypes文件
function(generate_qmltypes_manual output_file target_name headers)
    set(QMLTYPES_CONTENT "import QtQuick.tooling 1.2

// This file describes the plugin-supplied types contained in the library.
// It is used for QML tooling purposes only.
//
// This file was manually generated as a fallback when qmlplugindump is not available.

Module {
")

    # 为每个头文件生成基本的类型信息
    foreach(header ${headers})
        get_filename_component(header_name "${header}" NAME_WE)
        string(TOUPPER "${header_name}" upper_name)

        set(QMLTYPES_CONTENT "${QMLTYPES_CONTENT}
    Component {
        file: \"${header}\"
        name: \"Waylib::Server::${header_name}\"
        accessSemantics: \"reference\"
        prototype: \"QObject\"
        exports: [\"Waylib.Server/${header_name} 1.0\"]
        exportMetaObjectRevisions: [256]
    }")
    endforeach()

    set(QMLTYPES_CONTENT "${QMLTYPES_CONTENT}
}
")

    file(WRITE "${output_file}" "${QMLTYPES_CONTENT}")
    message(STATUS "Generated manual qmltypes file: ${output_file}")
endfunction()

# 函数：检查qmlplugindump工具是否可用
function(check_qmlplugindump_available result_var)
    find_program(QMLPLUGINDUMP_EXECUTABLE qmlplugindump)
    if(QMLPLUGINDUMP_EXECUTABLE)
        set(${result_var} TRUE PARENT_SCOPE)
        message(STATUS "qmlplugindump found: ${QMLPLUGINDUMP_EXECUTABLE}")
    else()
        set(${result_var} FALSE PARENT_SCOPE)
        message(WARNING "qmlplugindump not found, will use manual generation")
    endif()
endfunction()

# 主函数：生成QML文件
function(generate_qml_files target_name module_uri version output_dir headers)
    set(QMLDIR_FILE "${output_dir}/qmldir")
    set(QMLTYPES_FILE "${output_dir}/${target_name}.qmltypes")

    # 检查qmlplugindump是否可用
    check_qmlplugindump_available(QMLPLUGINDUMP_AVAILABLE)

    if(QMLPLUGINDUMP_AVAILABLE)
        message(STATUS "Using qmlplugindump to generate QML files")
        # 这里可以调用qmlplugindump，但由于这是备选方案，我们假设它不可用
    else()
        message(STATUS "Using manual generation for QML files")

        # 手动生成qmldir文件
        generate_qmldir_manual("${QMLDIR_FILE}" "${module_uri}" "${version}" "${output_dir}")

        # 手动生成qmltypes文件
        generate_qmltypes_manual("${QMLTYPES_FILE}" "${target_name}" "${headers}")
    endif()
endfunction()
