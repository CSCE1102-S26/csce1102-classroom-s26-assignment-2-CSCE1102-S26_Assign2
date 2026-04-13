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
    QTcpSocket socket;

    socket.connectToHost(host, port);
    co_await socket.waitForConnected();

    socket.write(message.toUtf8());
    co_await socket.waitForBytesWritten();

    socket.disconnectFromHost();

    co_return;
}


void client::on_pushButton_clicked()
{
    void client::on_sendButton_clicked()
    {
        QString host = "127.0.0.1";
        quint16 port = 54321;
        QString message = ui->messagelineEdit->text();

        sendNetworkMessage(host, port, message);
    }
}
