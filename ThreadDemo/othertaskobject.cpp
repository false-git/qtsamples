#include <QDebug>
#include <QThread>
#include "othertaskobject.h"

OtherTaskObject::OtherTaskObject(QObject *parent) : QObject(parent), timer2(this)
{
    timer1.setInterval(3000);
    timer1.setSingleShot(true);
    connect(&timer1, &QTimer::timeout, this, &OtherTaskObject::timeout);
    timer2.setInterval(3000);
    timer2.setSingleShot(true);
    connect(&timer2, &QTimer::timeout, this, &OtherTaskObject::timeout);
}

OtherTaskObject::~OtherTaskObject()
{
    timer1.stop(); // 動作中の場合はエラーになる
    timer2.stop();
}

void OtherTaskObject::startJob1()
{
    qDebug() << QThread::currentThreadId() << "OtherTaskObject::startJob1 called";
    QMetaObject::invokeMethod(this, "startJobInternal1", Qt::QueuedConnection);
}

void OtherTaskObject::startJobInternal1()
{
    qDebug() << QThread::currentThreadId() << "OtherTaskObject::startJobInternal1 called";
    timer1.start();
}

void OtherTaskObject::startJob2()
{
    qDebug() << QThread::currentThreadId() << "OtherTaskObject::startJob2 called";
    QMetaObject::invokeMethod(this, "startJobInternal2", Qt::QueuedConnection);
}

void OtherTaskObject::startJobInternal2()
{
    qDebug() << QThread::currentThreadId() << "OtherTaskObject::startJobInternal2 called";
    timer2.start();
}

void OtherTaskObject::timeout()
{
    qDebug() << QThread::currentThreadId() << "OtherTaskObject::timeout called";
    emit finishJob();
}

void OtherTaskObject::startLongJob()
{
    qDebug() << QThread::currentThreadId() << "OtherTaskObject::startLongJob called";
    QMetaObject::invokeMethod(this, "longJob", Qt::QueuedConnection);
}

void OtherTaskObject::longJob()
{
    qDebug() << QThread::currentThreadId() << "OtherTaskObject::longJob called";
    QThread::sleep(5);
    qDebug() << QThread::currentThreadId() << "OtherTaskObject::longJob finished";
}
