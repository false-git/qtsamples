#ifndef OTHERTASKOBJECT_H
#define OTHERTASKOBJECT_H

#include <QObject>
#include <QTimer>

class OtherTaskObject : public QObject
{
    Q_OBJECT
public:
    explicit OtherTaskObject(QObject *parent = 0);
    ~OtherTaskObject();

signals:
    void finishJob();
public slots:
    void startJob1();
    void startJobInternal1();
    void startJob2();
    void startJobInternal2();
    void timeout();
    void startLongJob();
private slots:
    void longJob();
private:
    QTimer timer1;
    QTimer timer2;
};

#endif // OTHERTASKOBJECT_H
