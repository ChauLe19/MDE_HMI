#include "mainwindow.h"


#include <QApplication>
#include <QFile>
#include <QNetworkProxy>

int main(int argc, char *argv[])
{
    // for my phone's Access Point
//    QNetworkProxy proxy;
//    proxy.setType(QNetworkProxy::HttpProxy);
//    proxy.setHostName("192.168.49.1");
//    proxy.setPort(8282);

//    QNetworkProxy::setApplicationProxy(proxy);

    QApplication a(argc, argv);

    // Set app style sheet
    QFile styleSheetFile(":/styles/SpyBot.qss");
    styleSheetFile.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(styleSheetFile.readAll());
    a.setStyleSheet(styleSheet);

    MainWindow w;
//    w.show();
    w.showFullScreen();
    return a.exec();
}
