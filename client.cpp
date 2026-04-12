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
    // TODO: Create a QTcpSocket locally. (It will be destroyed automatically when this function ends).
	QTcpSocket socket1;
	
    // TODO: Print a qDebug() message stating you are attempting to connect to the host and port.
	qDebug() << "Attempting to connect to the" << host <<" and "<<port;

    // TODO: Initiate the connection to the host using the socket.
	socket1.connectToHost(host, port);

    // TODO: Asynchronously wait for the connection to establish using co_await and qCoro.
    // Save the result into a boolean variable (e.g., 'connected').
	
	bool ok = co_await qCoro(&socket1)
		.waitForConnected();

    // TODO: Write an if-statement. If NOT connected:
	if(!ok) {
		QMessageBox::critical(this,"Error", socket1.errorString());
		co_return;
	} 
   // 1. Show a QMessageBox::critical stating the connection failed, using socket.errorString().
    // 2. co_return; to exit early.


    // TODO: Print a qDebug() message confirming connection.

	qDebug()<<"Connection Confirmed";
    // TODO: Write the 'message' variable to the socket (remember to convert it to Utf8).
	
	socket1.write(message.toUtf8());

    // TODO: Tell Qt to gracefully disconnect from the host.
	
	socket1.disconnectFromHost();
    // TODO: Asynchronously wait for Qt to finish flushing the buffer and disconnecting using co_await and qCoro.

	co_await qCoro(&socket1)
		.waitForDisconnected();
    // TODO: Show a QMessageBox::information stating the message was sent successfully.
	QMessageBox::information(this,"Success","Message was sent successfully");
}
