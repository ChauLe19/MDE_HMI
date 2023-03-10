QT       += core gui
QT       += charts
QT       += widgets
QT       += network
QT       += mqtt
QT	 += charts
QT	 += qml
QT	 += quick

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    datasource.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    datasource.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /opt/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    ScopeView.qml \
    eglfs.json \
    main.qmodel

RESOURCES += \
    chart.qrc
