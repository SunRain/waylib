#include <QApplication>
#include <QDebug>

#include "waylibserver/wglobal.h"
#include <waylibserver/wserver.h>

WAYLIB_SERVER_USE_NAMESPACE

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    WServer server;
    server.start();

    qDebug() << "Waylib package test successful!";
    qDebug() << "Waylib::SharedServer target found and linked.";

    return 0;
}
