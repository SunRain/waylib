cmake_minimum_required(VERSION 3.21)

project(
  Waylib
  VERSION 0.6.13
  LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(WITH_SUBMODULE_QWLROOTS "Use the QWlroots from git submodule" ON)
option(
  BUILD_WAYLIB_EXAMPLES
  "A minimum viable product Wayland compositor based on waylib and other examples"
  OFF)
option(BUILD_WAYLIB_TESTS "Build test demos" OFF)
option(DISABLE_XWAYLAND "Disable the xwayland support" OFF)
# Don't install tinywl by default, using for debug in local
option(INSTALL_TINYWL
       "A minimum viable product Wayland compositor based on waylib" OFF)
option(ADDRESS_SANITIZER "Enable address sanitize" OFF)
option(WAYLIB_USE_PERCOMPILE_HEADERS "Use precompile headers to build waylib"
       OFF)

find_package(Qt6 COMPONENTS Core Gui Quick REQUIRED)
if(Qt6_VERSION VERSION_GREATER_EQUAL 6.10)
  find_package(Qt6 REQUIRED COMPONENTS GuiPrivate QuickPrivate)
endif()

if(WITH_SUBMODULE_QWLROOTS)
  # Use qwlroots from project root directory
  # 传递BUILD_SHARED_LIBS选项给qwlroots子模块
 #   if(DEFINED BUILD_SHARED_LIBS_WAYLIB)
 #     set(BUILD_SHARED_LIBS ${BUILD_SHARED_LIBS_WAYLIB})
 #   endif()
	#始终静态编译qwlroots
	  set(BUILD_SHARED_QWLROOTS_LIBS OFF)
	  # 确保从父目录传递的构建选项生效
	  include(${CMAKE_CURRENT_SOURCE_DIR}/../qwlroots/cmake/WaylandScannerHelpers.cmake)
	  add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../qwlroots qwlroots)
	  message("Using QWlroots from submodule")
else()
  find_package(WaylibSharedQWlroots REQUIRED)
endif()

if(DISABLE_XWAYLAND)
  add_definitions(-DDISABLE_XWAYLAND)
endif()

if(ADDRESS_SANITIZER)
  add_compile_options(-fsanitize=address -fno-optimize-sibling-calls
                      -fno-omit-frame-pointer)
  add_link_options(-fsanitize=address)
endif()

# For Unix/Linux
include(GNUInstallDirs)
include(CMakePackageConfigHelpers)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/")
include(PackageVersionHelper)

add_subdirectory(src)
if(BUILD_WAYLIB_EXAMPLES)
  add_subdirectory(examples)
endif()
if(BUILD_WAYLIB_TESTS)
  enable_testing(true)
  add_subdirectory(tests)
endif()
