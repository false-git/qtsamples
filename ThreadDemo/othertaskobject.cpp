#include <QThread>
#include "othertaskobject.h"

void debug(const QString &message);

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
    debug("OtherTaskObject::startJob1 called");
    QMetaObject::invokeMethod(this, "startJobInternal1", Qt::QueuedConnection);
}

void OtherTaskObject::startJobInternal1()
{
    debug("OtherTaskObject::startJobInternal1 called");
    timer1.start();
}

void OtherTaskObject::startJob2()
{
    debug("OtherTaskObject::startJob2 called");
    QMetaObject::invokeMethod(this, "startJobInternal2", Qt::QueuedConnection);
}

void OtherTaskObject::startJobInternal2()
{
    debug("OtherTaskObject::startJobInternal2 called");
    timer2.start();
}

void OtherTaskObject::timeout()
{
    debug("OtherTaskObject::timeout called");
    emit finishJob();
}

void OtherTaskObject::startLongJob()
{
    debug("OtherTaskObject::startLongJob called");
    QMetaObject::invokeMethod(this, "longJob", Qt::QueuedConnection);
}

void OtherTaskObject::longJob()
{
    debug("OtherTaskObject::longJob called");
    QThread::sleep(5);
    emit finishJob();
    debug("OtherTaskObject::longJob finished");
}
