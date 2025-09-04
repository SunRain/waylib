if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_subdirectory(manual)
endif()
add_subdirectory(unit_tests)

# QML模块加载测试
find_package(Qt6 COMPONENTS Test REQUIRED)
if(Qt6Test_FOUND)
    qt_standard_project_setup()

    qt_add_executable(test_qml_module_loading
        test_qml_module_loading.cpp
    )

    target_link_libraries(test_qml_module_loading
        PRIVATE
        Qt6::Test
        Qt6::Qml
        Qt6::Quick
        Waylib::SharedServer
    )

    add_test(NAME QmlModuleLoadingTest COMMAND test_qml_module_loading)
endif()
