cmake_minimum_required(VERSION 3.21)
project(WaylibSharedMinimalConsumer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(WaylibShared REQUIRED COMPONENTS SharedServer)

add_executable(waylibshared_minimal_consumer main.cpp)
target_link_libraries(waylibshared_minimal_consumer PRIVATE WaylibShared::SharedServer)

add_executable(waylibshared_qml_consumer qml_test.cpp)
target_link_libraries(waylibshared_qml_consumer PRIVATE WaylibShared::SharedServer)

include(CTest)

# 推导 WaylibShared 的安装前缀（WaylibShared_DIR 通常位于 <prefix>/lib/cmake/WaylibShared）
get_filename_component(_waylibshared_prefix "${WaylibShared_DIR}/../../.." ABSOLUTE)

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
  add_test(NAME waylibshared_qml_import_test COMMAND waylibshared_qml_consumer)

  if(_waylibshared_ld_library_dir)
    set_tests_properties(waylibshared_link_test PROPERTIES
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
