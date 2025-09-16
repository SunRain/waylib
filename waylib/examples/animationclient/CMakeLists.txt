find_package(Qt6 REQUIRED COMPONENTS Quick Widgets)

qt_standard_project_setup(REQUIRES 6.4)

if(QT_KNOWN_POLICY_QTP0001) # this policy was introduced in Qt 6.5
  qt_policy(SET QTP0001 NEW)
  # the RESOURCE_PREFIX argument for qt_add_qml_module() defaults to ":/qt/qml/"
endif()

qt_add_executable(animationclient
    main.cpp
)

qt_add_qml_module(animationclient
    URI AnimationClient
    VERSION 1.0
    QML_FILES
        Main.qml
)

target_link_libraries(animationclient
    PRIVATE Qt6::Quick Qt6::Widgets
)
