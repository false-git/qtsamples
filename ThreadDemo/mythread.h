#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QThread>
#include <QDebug>
#include <QSharedPointer>

class MyObject {
public:
    int i;
    ~MyObject() {
        qDebug() << "~MyObject" << i;
    }
};

Q_DECLARE_METATYPE(MyObject)
Q_DECLARE_METATYPE(QSharedPointer<MyObject>)

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
        emit intResult(1);
        QString r("abc");
        emit stringResult(r);
        MyObject o;
        o.i = 3;
        emit objectResult(o);
        MyObject *p = new MyObject;
        p->i = 5;
        emit object_pResult(p);
        QSharedPointer<MyObject> sp(new MyObject);
        sp->i = 7;
        emit object_spResult(sp);
        emit finishCalculation();
        qDebug() << QThread::currentThreadId() << "emit完了!";
    }
signals:
    void intResult(int result);
    void stringResult(const QString &result);
    void objectResult(MyObject result);
    void object_pResult(MyObject* result);
    void object_spResult(QSharedPointer<MyObject> result);
    void finishCalculation();
};

#endif // MYTHREAD_H

