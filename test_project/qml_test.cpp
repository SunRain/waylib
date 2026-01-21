#include <QGuiApplication>
#include <QQmlComponent>
#include <QQmlEngine>

#include <QCoreApplication>
#include <QDeadlineTimer>
#include <QDebug>
#include <QStringList>

#ifndef WAYLIBSHARED_TEST_DEFAULT_QML_IMPORT_PATH
#  define WAYLIBSHARED_TEST_DEFAULT_QML_IMPORT_PATH ""
#endif

static QStringList splitQmlImportPath(const QString &value)
{
    if (value.isEmpty()) {
        return {};
    }

#if defined(Q_OS_WIN)
    const QChar sep(';');
#else
    const QChar sep(':');
#endif

    return value.split(sep, Qt::SkipEmptyParts);
}

int main(int argc, char **argv)
{
    // 允许 headless 环境运行（CI/容器）
    if (qEnvironmentVariableIsEmpty("QT_QPA_PLATFORM")) {
        qputenv("QT_QPA_PLATFORM", "offscreen");
    }

    QGuiApplication app(argc, argv);

    QQmlEngine engine;

    const auto envImportPath = qEnvironmentVariable("QML_IMPORT_PATH");
    for (const auto &p : splitQmlImportPath(envImportPath)) {
        engine.addImportPath(p);
    }

    const auto defaultImportPath =
        QStringLiteral(WAYLIBSHARED_TEST_DEFAULT_QML_IMPORT_PATH);
    if (!defaultImportPath.isEmpty()) {
        engine.addImportPath(defaultImportPath);
    }

    QQmlComponent component(&engine);
    component.setData(
        R"QML(
import QtQuick
import WaylibShared.QuickSharedServer

Item {
    DynamicCreator { }
}
)QML",
        QUrl(QStringLiteral("waylibshared-test://qml-import-test.qml")));

    QDeadlineTimer deadline(5000);
    while (component.status() == QQmlComponent::Loading && !deadline.hasExpired()) {
        QCoreApplication::processEvents(QEventLoop::AllEvents, 50);
    }

    if (component.status() == QQmlComponent::Error) {
        for (const auto &e : component.errors()) {
            qCritical().noquote() << e.toString();
        }
        return 1;
    }

    QObject *obj = component.create();
    if (!obj) {
        for (const auto &e : component.errors()) {
            qCritical().noquote() << e.toString();
        }
        return 1;
    }

    delete obj;
    return 0;
}
