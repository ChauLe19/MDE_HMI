#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMqttClient>

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

private:
    void setDCCurrentLabel(double currentValue);
    void setDCVoltageLabel(double voltageLabel);
    void updateSetOutputStatus();
    Ui::MainWindow *ui;
    QMqttClient *m_client;
    int setOutputVoltage;
    int setOutputCurrent;
};
#endif // MAINWINDOW_H
