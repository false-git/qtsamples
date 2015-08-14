#include "mainwindow.h"
#include <QApplication>

#include <QThread>
#include <QDateTime>
#include <QDebug>

void debug(const QString &message)
{
    QDateTime now = QDateTime::currentDateTime();
    QString tid = QString("%1").arg(reinterpret_cast<ulong>(QThread::currentThreadId()), sizeof(ulong) * 2, 16, QChar('0'));
    qDebug() << qPrintable(now.toString("HH:mm:ss.zzz")) << qPrintable(tid) << qPrintable(message);
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    debug("QApplication::exec()を実行するスレッド");

    MainWindow w;
    w.show();

    return a.exec();
}
