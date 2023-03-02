#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMqttClient>
#include <QQmlApplicationEngine>
#include <QQuickView>
#include "datasource.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void goToSetCurrentVoltagePage();
    void cancelSetCurrentVoltage();
    void saveSetCurrentVoltage();
    void updateTime();
    void updateOnMessageReceived(const QByteArray &message, const QMqttTopicName &topic);
    void changeFault(const QString &text);
    void changeState(const QString &text);
    void turnOff();
private:
    void setDCCurrentLabel(double currentValue);
    void setDCVoltageLabel(double voltageLabel);
    void updateSetOutputStatus();
    Ui::MainWindow *ui;
    QMqttClient *m_client;
    int setOutputVoltage;
    int setOutputCurrent;
    QQuickView *scopeView;
    DataSource *dataSource;
};
#endif // MAINWINDOW_H
