find_package(Qt6 COMPONENTS Quick QuickControls2 REQUIRED)
qt_standard_project_setup(REQUIRES 6.4)

if(QT_KNOWN_POLICY_QTP0001) # this policy was introduced in Qt 6.5
    qt_policy(SET QTP0001 NEW)
    # the RESOURCE_PREFIX argument for qt_add_qml_module() defaults to ":/qt/qml/"
endif()
if(POLICY CMP0071)
    # https://cmake.org/cmake/help/latest/policy/CMP0071.html
    cmake_policy(SET CMP0071 NEW)
endif()

set(QML_IMPORT_PATH "${PROJECT_BINARY_DIR}/src/server;${QML_IMPORT_PATH}" CACHE STRING "For LSP" FORCE)

find_package(PkgConfig REQUIRED)
pkg_search_module(PIXMAN REQUIRED IMPORTED_TARGET pixman-1)
pkg_search_module(WAYLAND REQUIRED IMPORTED_TARGET wayland-server)

qt_add_executable(live
    main.cpp
)

qt_add_qml_module(live
    URI Live
    VERSION "1.0"
    QML_FILES
        Main.qml
    SOURCES
        helper.h
)

target_compile_definitions(live
    PRIVATE
    PROJECT_BINARY_DIR="${PROJECT_BINARY_DIR}"
    WLR_USE_UNSTABLE
)

target_link_libraries(live
    PRIVATE
    Qt6::Quick
    Qt6::QuickControls2
    quickwaylibpulgin
    PkgConfig::PIXMAN
    PkgConfig::WAYLAND
)
