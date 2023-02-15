#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtMqtt/QMqttClient>
#include <QTime>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->MainPages->setCurrentIndex(0);
    QTimer *timer = new QTimer(); // for starting the clock
    connect(timer, &QTimer::timeout, this, &MainWindow::updateTime);
    timer->start(1000); // clock update frequency (1 update/s)
    setOutputCurrent = ui->currentSpinBox->text().toInt();
    setOutputVoltage = ui->voltageSpinBox->text().toInt();
    updateSetOutputStatus();

    m_client = new QMqttClient();
    m_client->setHostname("127.0.0.1"); // localhost
    m_client->setPort(1883);
//    m_client->setHostname("137.184.70.171"); // test mde signal
//    m_client->setPort(1883);

//    m_client->setUsername("mde_test");
//    m_client->setPassword("mde_test");

    connect(m_client, &QMqttClient::messageReceived, this, [this](const QByteArray &message, const QMqttTopicName &topic){
        qDebug() << "hi";
        setDCVoltageLabel(message.toDouble());
    });

    connect(m_client, &QMqttClient::disconnected, this, [this](){
        // update the icon here
        qDebug() << "disconnected\n";
    });

    connect(m_client, &QMqttClient::connected, this, [this](){
        // update the icon here
        qDebug() << "connected\n";
        auto subscription = m_client->subscribe(QString("/pebb/voltage"), 0);
        if (!subscription) {
            qDebug() << QLatin1String("Error:") << QLatin1String("Could not subscribe. Is there a valid connection?");
        }
    });

//    connect(this, &QMqttClient::disconnected, this, [this](){
//        // update the icon here
//        qDebug() << "disconnected\n";
//    });

    // UI interaction signals/slots
    connect(ui->SetOutputButton, &QPushButton::clicked, this, &MainWindow::goToSetCurrentVoltagePage);
    connect(ui->CancelButton, &QPushButton::clicked, this, &MainWindow::cancelSetCurrentVoltage);
    connect(ui->SaveButton, &QPushButton::clicked, this, &MainWindow::saveSetCurrentVoltage);

    m_client->connectToHost();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::goToSetCurrentVoltagePage()
{
    ui->MainPages->setCurrentIndex(1);
}

void MainWindow::cancelSetCurrentVoltage()
{
    updateSetOutputStatus();
    ui->MainPages->setCurrentIndex(0);
    ui->currentSpinBox->setValue(setOutputCurrent);
    ui->voltageSpinBox->setValue(setOutputVoltage);
}

void MainWindow::saveSetCurrentVoltage()
{
    // set(save) values
    // send mqtt messages
    setOutputCurrent = ui->currentSpinBox->text().toInt();
    setOutputVoltage = ui->voltageSpinBox->text().toInt();
    m_client->publish(QMqttTopicName("/pebb/setVoltage"), QString::number(setOutputVoltage).toUtf8());
    m_client->publish(QMqttTopicName("/pebb/setCurrent"), QString::number(setOutputCurrent).toUtf8());
    updateSetOutputStatus();
    ui->MainPages->setCurrentIndex(0);
}

void MainWindow::setDCCurrentLabel(double currentValue)
{
    ui->DCCurrentLabel->setText(QString("DC Current: %1A").arg(currentValue, 0, 'f', 1));
}

void MainWindow::setDCVoltageLabel(double voltageValue)
{
    ui->DCVoltageLabel->setText(QString("DC Voltage: %1V").arg(voltageValue, 0, 'f', 1));
}

void MainWindow::updateTime()
{
    QTime time = QTime::currentTime();
    ui->TimeLabel->setText(time.toString("h:mmAP"));
}

void MainWindow::updateSetOutputStatus()
{
    qDebug() << "update";
    ui->outputStatusLabel->setText(QString("Set DC Current: %1A\nSet DC Voltage: %2V").arg(QString::number(setOutputCurrent), QString::number(setOutputVoltage)));
}
