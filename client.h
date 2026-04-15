#ifndef CLIENT_H
#define CLIENT_H

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
#endif // CLIENT_H
