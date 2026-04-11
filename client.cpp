#include "client.h"
#include "ui_client.h"
#include <QTcpSocket>
#include <QCoro/QCoroNetwork>
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

QCoro::Task<void> client::sendNetworkMessage(QString host, quint16 port,QString message)
{
    QTcpSocket socket;

    co_await qCoro(socket).connectToHost(host, port);

    if(socket.state() != QAbstractSocket::ConnectedState) {
        QMessageBox::critical(this, "Error", "Connection failed!") ;
        co_return;
    }

        socket.write(message.toUtf8());
    //socket.flush();

    co_await qCoro(socket).waitForBytesWritten(3000);

    socket.disconnectFromHost();

    QMessageBox::information(this, "Success", "Message Sent");

}


void client::on_sendButton_clicked()
{
    QString host = "127.0.0.1" ;
    quint16 port = 54321;
    QString message = ui->messagelineEdit->text();

    sendNetworkMessage(host, port, message);
}

