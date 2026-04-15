#include "client.h"
<<<<<<< HEAD
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    Client w;
=======

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    client w;
>>>>>>> 94c10cb9d84c0b7ebc383fe1993bc808236789c8
    w.show();
    return a.exec();
}
