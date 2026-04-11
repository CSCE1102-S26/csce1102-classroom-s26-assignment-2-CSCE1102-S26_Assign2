#include "client.h"
#include "ui_client.h"
#include <QTcpSocket>
#include <qcoronetwork.h>
#include <QMessageBox>
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
QTcpSocket socket;
qDebug() << "Connecting to" << host << ":" << port;
socket.connectToHost(host, port);
bool connected = co_await qCoro(socket).waitForConnected(3000);
if (!connected) {
    QMessageBox::critical(this, "Error", "Connection failed: " + socket.errorString());
    co_return;
    }
qDebug() << "Connected successfully";
socket.write(message.toUtf8());
co_await qCoro(socket).waitForBytesWritten(3000);
socket.disconnectFromHost();
co_await qCoro(socket).waitForDisconnected(3000);
QMessageBox::information(this, "Success", "Message sent succesfully! ");
}
void client::on_sendButton_clicked()
{
    QString host = "127.0.0.1";
    quint16 port = 54321;
    QString message = ui->messagelineEdit->text();
    sendNetworkMessage(host, port, message);
}
