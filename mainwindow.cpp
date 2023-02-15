#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtMqtt/QMqttClient>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_client = new QMqttClient(	);
    m_client->setHostname("127.0.0.1");
//    m_client->setHostname("broker.mqttdashboard.com");
    m_client->setPort(1883);
//    m_client->setUsername("mde_test");
//    m_client->setPassword("mde_test");

    connect(m_client, &QMqttClient::messageReceived, this, [this](const QByteArray &message, const QMqttTopicName &topic){
        ui->DCCurrentLabel->setText(message);
        qDebug() << "hi\n";
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

MainWindow::~MainWindow()
{
    delete ui;
}

