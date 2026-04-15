#ifndef CLIENT_H
#define CLIENT_H

<<<<<<< HEAD
#include <QWidget>
#include <QTcpSocket>
#include <QString>

QT_BEGIN_NAMESPACE
namespace Ui { class Client; }
QT_END_NAMESPACE

class Client : public QWidget {
    Q_OBJECT
public:
    explicit Client(QWidget *parent = nullptr);
    ~Client();

private slots:
    void on_sendButton_clicked();
    void onReadyRead();

private:
    Ui::Client *ui;
    QTcpSocket *socket;

    // Added this line to declare the function that was missing
    void sendNetworkMessage(const QString& host, int port, const QString& message);
};
=======
#include <QMainWindow>
#include <qcorotask.h> // Include QCoro core

QT_BEGIN_NAMESPACE
namespace Ui { class client; }
QT_END_NAMESPACE

class client : public QMainWindow {
    Q_OBJECT

public:
    client(QWidget *parent = nullptr);
    ~client();

private:
    Ui::client *ui;

    // The coroutine that will handle the network operation without blocking the UI
    QCoro::Task<void> sendNetworkMessage(QString host, quint16 port, QString message);
};

>>>>>>> 94c10cb9d84c0b7ebc383fe1993bc808236789c8
#endif // CLIENT_H
