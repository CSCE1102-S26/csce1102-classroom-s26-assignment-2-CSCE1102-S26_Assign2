#include "client.h"
#include "ui_client.h"
#include <QTcpSocket>
#include <QCoro/QCoroNetwork> // Required to await QTcpSocket
#include <QMessageBox>        // Required for UI feedback
#include <QDebug>

client::client(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::client)
{
    ui->setupUi(this);
}

client::~client()
{
    delete ui;
}

QCoro::Task<void> client::sendNetworkMessage(QString host, quint16 port, QString message)
{
    QTcpSocket Socket;

    qDebug() << "Attempting to connect to" << host << "on port" << port;

    Socket.connectToHost(host, port);

    bool connected = co_wait qCoro(socket).waitForConnected();

    if(!connected)
    {
        QMessageBox::critical(this, "Error", "Connection failed: " + socket.errorString());
        co_return;
    }

    qDebug() << "Connected successfully to" << host;

    socket.write(message.toUtf8());

    socket.disconnectFromHost();

    co_wait qCoro(socket).waitForDisconnected();

    QMessageBox::information(this,"Success","Message sent successfully!");
    //chatgpt link:https://chatgpt.com/share/69dd27fe-52e4-8328-95a3-e18883a16312
    //Mazen Abudaif-900221772

}
