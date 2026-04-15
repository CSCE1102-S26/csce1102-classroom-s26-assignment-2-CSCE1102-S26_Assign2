#include "client.h"
#include "ui_client.h"
<<<<<<< HEAD
#include <QMessageBox>
#include <QTcpSocket>

Client::Client(QWidget *parent) : QWidget(parent), ui(new Ui::Client) {
    ui->setupUi(this);
    
    socket = new QTcpSocket(this);
    

    connect(ui->sendButton, &QPushButton::clicked, this, &Client::on_sendButton_clicked);
    connect(socket, &QTcpSocket::readyRead, this, &Client::onReadyRead);
}

Client::~Client()
=======
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
>>>>>>> 94c10cb9d84c0b7ebc383fe1993bc808236789c8
{
    delete ui;
}

<<<<<<< HEAD
void Client::on_sendButton_clicked()
{
    QString host = "127.0.0.1";
    quint16 port = 54321;
    
    QString message = ui->messagelineEdit->text();
    
    
    sendNetworkMessage(host, port, message);
    
    QMessageBox::information(this, "Success", "Message sent successfully!");
}


void Client::sendNetworkMessage(const QString& host, int port, const QString& message) {
    
    if (socket->state() != QAbstractSocket::ConnectedState) {
        socket->connectToHost(host, port);
    }
    
   
    if (socket->waitForConnected(3000)) {
      
        socket->write(message.toUtf8());
        socket->flush();
    }
}

void Client::onReadyRead()
{
    QByteArray data = socket->readAll();
    ui->chatDisplay->append(QString::fromUtf8(data));
=======
QCoro::Task<void> client::sendNetworkMessage(QString host, quint16 port, QString message)
{
    // TODO: Create a QTcpSocket locally. (It will be destroyed automatically when this function ends).

    // TODO: Print a qDebug() message stating you are attempting to connect to the host and port.

    // TODO: Initiate the connection to the host using the socket.

    // TODO: Asynchronously wait for the connection to establish using co_await and qCoro.
    // Save the result into a boolean variable (e.g., 'connected').

    // TODO: Write an if-statement. If NOT connected:
    // 1. Show a QMessageBox::critical stating the connection failed, using socket.errorString().
    // 2. co_return; to exit early.

    // TODO: Print a qDebug() message confirming connection.

    // TODO: Write the 'message' variable to the socket (remember to convert it to Utf8).

    // TODO: Tell Qt to gracefully disconnect from the host.

    // TODO: Asynchronously wait for Qt to finish flushing the buffer and disconnecting using co_await and qCoro.

    // TODO: Show a QMessageBox::information stating the message was sent successfully.

>>>>>>> 94c10cb9d84c0b7ebc383fe1993bc808236789c8
}
