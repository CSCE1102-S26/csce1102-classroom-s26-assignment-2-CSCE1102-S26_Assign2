#ifndef CLIENT_H
#define CLIENT_H

#include <QMainWindow>
#include <qcorotask.h>
#include <QTcpSocket>

QT_BEGIN_NAMESPACE
namespace Ui { class client; }
QT_END_NAMESPACE

class client : public QMainWindow {
    Q_OBJECT

public:
    client(QWidget *parent = nullptr);
    ~client();

private slots:
    void on_sendButton_clicked();

private:
    Ui::client *ui;
    QCoro::Task<void> sendNetworkMessage(QString host, quint16 port, QString message);
};
#endif
