#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtMqtt/QMqttClient>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_client = new QMqttClient(	);
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

    m_client->connectToHost();
}

void MainWindow::setDCCurrentLabel(double currentValue)
{
    ui->DCCurrentLabel->setText(QString("DC Current: %1A").arg(currentValue, 0, 'f', 1));
}

void MainWindow::setDCVoltageLabel(double voltageValue)
{
    ui->DCVoltageLabel->setText(QString("DC Voltage: %1V").arg(voltageValue, 0, 'f', 1));
}

MainWindow::~MainWindow()
{
    delete ui;
}

