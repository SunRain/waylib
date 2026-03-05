cmake_minimum_required(VERSION 3.25.0)

project(
  QuickWaylibServer
  VERSION 0.7.0
  LANGUAGES CXX C)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Standard installation paths
include(GNUInstallDirs)
# Macros
include(FeatureSummary)

option(WITH_SUBMODULE_WAYLIB "Use the waylib from git submodule" ON)
add_feature_info(submodule_waylib WITH_SUBMODULE_WAYLIB
                 "Use waylib from submodule")

option(ADDRESS_SANITIZER "Enable address sanitizer" OFF)
add_feature_info(ASanSupport ADDRESS_SANITIZER
                 "https://github.com/google/sanitizers/wiki/AddressSanitizer")

option(BUILD_SHARED_LIBS "Build shared libraries" ON)
add_feature_info(BuildSharedLibs BUILD_SHARED_LIBS
                 "Build shared libraries instead of static")

if(ADDRESS_SANITIZER)
  add_compile_options(-fsanitize=address -fno-optimize-sibling-calls
                      -fno-omit-frame-pointer)
  add_link_options(-fsanitize=address)
endif()
# NOTE: Qt keywords conflict with wlroots. but dtksystemsettings still uses it.
# add_definitions("-DQT_NO_KEYWORDS")

set(LOCAL_QML_IMPORT_PATH "${PROJECT_BINARY_DIR}/qt/qml")

if(WITH_SUBMODULE_WAYLIB)
  set(WITH_SUBMODULE_QWLROOTS ON)
  # 传递BUILD_SHARED_LIBS选项给waylib子模块
  set(BUILD_SHARED_LIBS_WAYLIB ${BUILD_SHARED_LIBS})
  set(BUILD_SHARED_QWLROOTS_LIBS OFF)
  add_subdirectory(waylib)
  list(APPEND LOCAL_QML_IMPORT_PATH "${PROJECT_BINARY_DIR}/waylib/src/server")

  # 设置 WaylibShared_DIR 以便父项目可以找到 WaylibShared
  set(WaylibShared_DIR
      "${CMAKE_CURRENT_BINARY_DIR}/waylib/src"
      CACHE PATH "WaylibShared CMake config directory" FORCE)
else()
  find_package(WaylibShared REQUIRED COMPONENTS SharedServer)
endif()

set(QML_IMPORT_PATH
    "${LOCAL_QML_IMPORT_PATH}"
    CACHE STRING "For LSP" FORCE)

# Display feature summary
feature_summary(WHAT ALL)
