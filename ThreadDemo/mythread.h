#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QThread>
#include <QDebug>

class MyThread: public QThread {
    Q_OBJECT
public:
    MyThread() {

    }
    ~MyThread() {
        qDebug() << QThread::currentThreadId() << "~MyThread";
    }

protected:
    void run() {
        qDebug() << QThread::currentThreadId() << "サブスレッド";
        emit finishCalculation();
        qDebug() << QThread::currentThreadId() << "emit完了!";
    }
signals:
    void finishCalculation();
};

#endif // MYTHREAD_H

