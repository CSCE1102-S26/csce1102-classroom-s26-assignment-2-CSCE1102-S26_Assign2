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
    // TODO: Create a QTcpSocket locally.
    QTcpSocket socket;

    // TODO: Print a qDebug() message stating you are attempting to connect.
    qDebug() << "Attempting to connect to" << host << "on port" << port;

    // TODO: Initiate the connection to the host using the socket.
    socket.connectToHost(host, port);

    // TODO: Asynchronously wait for the connection to establish using co_await and qCoro.
    // QCoro provides a waitForConnected() coroutine wrapper for QTcpSocket.
    bool connected = co_await qCoro(&socket).waitForConnected();

    // TODO: Write an if-statement. If NOT connected:
    if (!connected) {
        // 1. Show a QMessageBox::critical stating the connection failed.
        QMessageBox::critical(this, "Connection Failed",
                              "Could not connect to server: " + socket.errorString());
        // 2. co_return; to exit early.
        co_return;
    }

    // TODO: Print a qDebug() message confirming connection.
    qDebug() << "Connected successfully to" << host;

    // TODO: Write the 'message' variable to the socket.
    // We convert QString to a UTF-8 QByteArray for network transmission.
    socket.write(message.toUtf8());

    // TODO: Tell Qt to gracefully disconnect from the host.
    socket.disconnectFromHost();

    // TODO: Asynchronously wait for Qt to finish flushing and disconnecting.
    co_await qCoro(&socket).waitForDisconnected();

    // TODO: Show a QMessageBox::information stating the message was sent successfully.
    QMessageBox::information(this, "Success", "Message sent successfully!");
}
