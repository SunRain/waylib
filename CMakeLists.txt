cmake_minimum_required(VERSION 3.21)

project(Waylib
    VERSION 0.1.1
    LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(ECM_VERSION 6.0.0)

option(WITH_SUBMODULE_QWLROOTS "Use the QWlroots from git submodule" OFF)
option(BUILD_EXAMPLES "A minimum viable product Wayland compositor based on waylib and other examples" ON)
option(BUILD_TESTS "Build test demos" ON)
option(DISABLE_XWAYLAND "Disable the xwayland support" OFF)
# Don't install tinywl by default, using for debug in local
option(INSTALL_TINYWL "A minimum viable product Wayland compositor based on waylib" OFF)
option(ADDRESS_SANITIZER "Enable address sanitize" OFF)
option(WAYLIB_USE_PERCOMPILE_HEADERS "Use precompile headers to build waylib" ON)

# set up extra-cmake-modules before trying anything else
include(FeatureSummary)

find_package(ECM ${ECM_VERSION} REQUIRED NO_MODULE)
set_package_properties(ECM
    PROPERTIES
        TYPE REQUIRED
        DESCRIPTION "Extra CMake Modules"
        URL "https://commits.kde.org/extra-cmake-modules"
)
feature_summary(WHAT REQUIRED_PACKAGES_NOT_FOUND FATAL_ON_MISSING_REQUIRED_PACKAGES)

# we found extra-cmake-modules, so use it now
set(CMAKE_MODULE_PATH
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake" ${ECM_MODULE_PATH}
)

## Installation directories:
include(KDEInstallDirs6)

## CMake settings:
include(KDECMakeSettings)

set(QT_COMPONENTS Core Gui Quick)
find_package(Qt6 COMPONENTS ${QT_COMPONENTS} REQUIRED)
if(WITH_SUBMODULE_QWLROOTS)
    include(${CMAKE_CURRENT_SOURCE_DIR}/qwlroots/cmake/WaylandScannerHelpers.cmake)
    add_subdirectory(qwlroots)
    message("Using QWlroots from submodule")
else()
    find_package(QWlroots REQUIRED)
    message("Using QWlroots from shared library")
endif()

if(DISABLE_XWAYLAND)
    add_definitions(-DDISABLE_XWAYLAND)
endif()

if (ADDRESS_SANITIZER)
    add_compile_options(-fsanitize=address -fno-optimize-sibling-calls -fno-omit-frame-pointer)
    add_link_options(-fsanitize=address)
endif()

# For Unix/Linux
include(GNUInstallDirs)
include(CMakePackageConfigHelpers)
# list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/")
include(PackageVersionHelper)

add_subdirectory(src)
if(BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()
if(BUILD_TESTS)
    add_subdirectory(tests)
endif()

# and we're done
include(ECMFeatureSummary)
ecm_feature_summary(WHAT ALL INCLUDE_QUIET_PACKAGES FATAL_ON_MISSING_REQUIRED_PACKAGES)
