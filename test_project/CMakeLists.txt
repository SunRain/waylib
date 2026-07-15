cmake_minimum_required(VERSION 3.21)
project(WaylibSharedMinimalConsumer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# The core package must remain consumable without Qt Quick Controls 2.
set(CMAKE_DISABLE_FIND_PACKAGE_Qt6QuickControls2 TRUE)
find_package(WaylibShared REQUIRED COMPONENTS SharedServer)

get_target_property(
  _waylibshared_interface_links
  WaylibShared::SharedServer
  INTERFACE_LINK_LIBRARIES
)
if(NOT "PkgConfig::XCB" IN_LIST _waylibshared_interface_links)
  message(FATAL_ERROR
    "WaylibShared::SharedServer must propagate its public XCB dependency")
endif()
unset(_waylibshared_interface_links)

# Derive the installation prefix from the installed CMake package.
get_filename_component(_waylibshared_prefix "${WaylibShared_DIR}/../../.." ABSOLUTE)

set(_waylibshared_original_pkg_config_path "$ENV{PKG_CONFIG_PATH}")
set(ENV{PKG_CONFIG_PATH}
  "${_waylibshared_prefix}/lib/pkgconfig:$ENV{PKG_CONFIG_PATH}")
find_package(PkgConfig REQUIRED)
pkg_check_modules(
  WAYLIBSHARED_PC
  REQUIRED
  IMPORTED_TARGET
  WaylibSharedServer
)
set(ENV{PKG_CONFIG_PATH} "${_waylibshared_original_pkg_config_path}")
unset(_waylibshared_original_pkg_config_path)

file(STRINGS
  "${_waylibshared_prefix}/lib/pkgconfig/WaylibSharedServer.pc"
  _waylibshared_pkgconfig_requires
  REGEX "^Requires:"
)
if(NOT _waylibshared_pkgconfig_requires MATCHES "(^|[, ])xcb([, ]|$)")
  message(FATAL_ERROR
    "WaylibSharedServer.pc must declare its public XCB dependency")
endif()
unset(_waylibshared_pkgconfig_requires)

foreach(_waylibshared_pkgconfig_name
        WaylibSharedServer
        waylibshared-qwlroots)
  file(STRINGS
    "${_waylibshared_prefix}/lib/pkgconfig/${_waylibshared_pkgconfig_name}.pc"
    _waylibshared_pkgconfig_libs
    REGEX "^Libs:"
  )
  string(FIND
    "${_waylibshared_pkgconfig_libs}"
    "-L${_waylibshared_prefix}/lib"
    _waylibshared_pkgconfig_libdir_index
  )
  if(_waylibshared_pkgconfig_libdir_index EQUAL -1)
    message(FATAL_ERROR
      "${_waylibshared_pkgconfig_name}.pc must expose its non-system library directory")
  endif()
endforeach()
unset(_waylibshared_pkgconfig_libdir_index)
unset(_waylibshared_pkgconfig_libs)
unset(_waylibshared_pkgconfig_name)

add_executable(waylibshared_minimal_consumer main.cpp)
target_link_libraries(waylibshared_minimal_consumer PRIVATE WaylibShared::SharedServer)

add_executable(waylibshared_pkgconfig_consumer main.cpp)
target_link_libraries(
  waylibshared_pkgconfig_consumer
  PRIVATE
    PkgConfig::WAYLIBSHARED_PC
)

add_executable(waylibshared_qml_consumer qml_test.cpp)
target_link_libraries(waylibshared_qml_consumer PRIVATE WaylibShared::SharedServer)

include(CTest)

# 推导 QML import path（优先 KDE 路径 lib/qml，其次 Qt 习惯路径 lib/qt6/qml）
set(_waylibshared_qml_import_dir "")
foreach(_candidate
        "${_waylibshared_prefix}/lib/qml"
        "${_waylibshared_prefix}/lib/qt6/qml")
  if(EXISTS "${_candidate}")
    set(_waylibshared_qml_import_dir "${_candidate}")
    break()
  endif()
endforeach()

# 推导运行时动态库路径（避免测试运行时找不到 /lib 下的依赖）
set(_waylibshared_ld_library_dir "")
foreach(_candidate
        "${_waylibshared_prefix}/lib"
        "${_waylibshared_prefix}/lib64")
  if(EXISTS "${_candidate}")
    set(_waylibshared_ld_library_dir "${_candidate}")
    break()
  endif()
endforeach()

target_compile_definitions(waylibshared_qml_consumer
  PRIVATE
    WAYLIBSHARED_TEST_DEFAULT_QML_IMPORT_PATH="${_waylibshared_qml_import_dir}"
)

if(BUILD_TESTING)
  add_test(NAME waylibshared_link_test COMMAND waylibshared_minimal_consumer)
  add_test(NAME waylibshared_pkgconfig_link_test
           COMMAND waylibshared_pkgconfig_consumer)
  add_test(NAME waylibshared_qml_import_test COMMAND waylibshared_qml_consumer)

  if(_waylibshared_ld_library_dir)
    set_tests_properties(
      waylibshared_link_test
      waylibshared_pkgconfig_link_test
      PROPERTIES
      ENVIRONMENT "LD_LIBRARY_PATH=${_waylibshared_ld_library_dir}"
    )
  endif()

  set_tests_properties(waylibshared_qml_import_test PROPERTIES
    ENVIRONMENT
      "QT_QPA_PLATFORM=offscreen;QML_IMPORT_PATH=${_waylibshared_qml_import_dir};LD_LIBRARY_PATH=${_waylibshared_ld_library_dir}"
  )
endif()

unset(_waylibshared_prefix)
unset(_waylibshared_qml_import_dir)
unset(_waylibshared_ld_library_dir)
