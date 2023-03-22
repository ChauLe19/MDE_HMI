#include "mainwindow.h"


#include <QApplication>
#include <QFile>

int main(int argc, char *argv[])
{
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
