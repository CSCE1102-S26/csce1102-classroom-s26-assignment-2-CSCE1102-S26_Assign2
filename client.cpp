#include "client.h"
#include "ui_client.h"
#include <QMessageBox>
#include <QTcpSocket>

Client::Client(QWidget *parent) : QWidget(parent), ui(new Ui::Client) {
    ui->setupUi(this);
    
    socket = new QTcpSocket(this);
    

    connect(ui->sendButton, &QPushButton::clicked, this, &Client::on_sendButton_clicked);
    connect(socket, &QTcpSocket::readyRead, this, &Client::onReadyRead);
}

Client::~Client()
{
    delete ui;
}

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
}
