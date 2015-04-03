#include "mainwindow.h"
#include <QApplication>

#include <QThread>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    qDebug() << QThread::currentThreadId() << "QApplication::exec()を実行するスレッド";

    MainWindow w;
    w.show();

    return a.exec();
}
