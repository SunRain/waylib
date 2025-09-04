// test_qml_module_loading.cpp - 测试QML模块加载
//
// 此测试验证QML模块是否能正确加载和使用

#include <QtTest/QtTest>
#include <QtQml/QQmlEngine>
#include <QtQml/QQmlComponent>
#include <QtCore/QDir>
#include <QtCore/QStandardPaths>

class TestQmlModuleLoading : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase()
    {
        // 设置QML导入路径
        QStringList importPaths = engine.importPathList();

        // 添加默认QML路径
        importPaths << "/usr/lib/qt6/qml";

        // 如果设置了QT6_INSTALL_QMLDIR环境变量，添加到导入路径
        const QString customQmlDir = qEnvironmentVariable("QT6_INSTALL_QMLDIR");
        if (!customQmlDir.isEmpty()) {
            importPaths << customQmlDir;
        }

        engine.setImportPathList(importPaths);
    }

    void testQmlModuleImport()
    {
        // 测试QML模块导入
        QString qmlCode = R"(
            import QtQuick 2.15
            import Waylib.Server 1.0

            Item {
                id: root
                property bool moduleLoaded: true

                // 测试基本的QML类型是否可用
                WEventJunkman {
                    id: junkman
                }

                Component.onCompleted: {
                    console.log("QML module Waylib.Server loaded successfully")
                }
            }
        )";

        QQmlComponent component(&engine);
        component.setData(qmlCode.toUtf8(), QUrl());

        QVERIFY2(component.isReady(), qPrintable(component.errorString()));

        QObject *object = component.create();
        QVERIFY(object != nullptr);

        // 验证模块加载成功
        QVariant moduleLoaded = object->property("moduleLoaded");
        QVERIFY(moduleLoaded.toBool());

        delete object;
    }

    void testQmlTypesAvailability()
    {
        // 测试QML类型是否可用
        QString qmlCode = R"(
            import QtQuick 2.15
            import Waylib.Server 1.0

            Item {
                // 测试各种QML类型
                WEventJunkman { id: junkman }
                WQuickCursor { id: cursor }
                WOutputItem { id: outputItem }
                WQuickOutputLayout { id: layout }

                property bool typesAvailable: true
            }
        )";

        QQmlComponent component(&engine);
        component.setData(qmlCode.toUtf8(), QUrl());

        QVERIFY2(component.isReady(), qPrintable(component.errorString()));

        QObject *object = component.create();
        QVERIFY(object != nullptr);

        // 验证类型可用性
        QVariant typesAvailable = object->property("typesAvailable");
        QVERIFY(typesAvailable.toBool());

        delete object;
    }

    void testQmlDirFile()
    {
        // 测试qmldir文件是否存在
        QStringList importPaths = engine.importPathList();

        bool qmldirFound = false;
        for (const QString &path : importPaths) {
            QString qmldirPath = path + "/Waylib/QuickSharedServer/qmldir";
            if (QFile::exists(qmldirPath)) {
                qmldirFound = true;
                qDebug() << "Found qmldir at:" << qmldirPath;
                break;
            }
        }

        QVERIFY2(qmldirFound, "qmldir file not found in any import path");
    }

    void testQmlTypesFile()
    {
        // 测试plugins.qmltypes文件是否存在
        QStringList importPaths = engine.importPathList();

        bool qmltypesFound = false;
        for (const QString &path : importPaths) {
            QString qmltypesPath = path + "/Waylib/QuickSharedServer/WaylibSharedServer.qmltypes";
            if (QFile::exists(qmltypesPath)) {
                qmltypesFound = true;
                qDebug() << "Found qmltypes at:" << qmltypesPath;
                break;
            }
        }

        QVERIFY2(qmltypesFound, "plugins.qmltypes file not found in any import path");
    }

private:
    QQmlEngine engine;
};

QTEST_MAIN(TestQmlModuleLoading)
#include "test_qml_module_loading.moc"
