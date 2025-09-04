cmake_minimum_required(VERSION 3.16)
project(TestWaylibPackage)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Standard installation paths
include(GNUInstallDirs)
# Macros
include(FeatureSummary)

# Set CMAKE_PREFIX_PATH to find the installed Waylib package
set(CMAKE_PREFIX_PATH "/tmp/waylib-install" CACHE PATH "Path to installed Waylib package")

find_package(Qt6 REQUIRED COMPONENTS Core Widgets Quick)
find_package(Waylib REQUIRED COMPONENTS SharedServer)

add_executable(test_app main.cpp)
target_link_libraries(test_app PRIVATE Qt6::Core Qt6::Widgets Qt6::Quick
                                        Waylib::SharedServer)
