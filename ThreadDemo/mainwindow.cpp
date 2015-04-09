#include "mainwindow.h"

#include <QVBoxLayout>
#include <QPushButton>
#include <QThread>
#include <QDebug>

#include "mythread.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    // 画面部品を作る
    QWidget *widget = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout;
    QPushButton *button1 = new QPushButton("button 1");
    layout->addWidget(button1);
    QPushButton *button2 = new QPushButton("button 2");
    layout->addWidget(button2);
    QPushButton *button3 = new QPushButton("button 3");
    layout->addWidget(button3);
    widget->setLayout(layout);
    setCentralWidget(widget);

    // シグナルの引数を登録する
    qRegisterMetaType<MyObject>();
    qRegisterMetaType<QSharedPointer<MyObject>>();

    // シグナルとスロットを繋ぐ
    connect(button1, &QPushButton::clicked, this, &MainWindow::button1Clicked);
    connect(button2, &QPushButton::clicked, this, &MainWindow::button2Clicked);
    connect(button3, &QPushButton::clicked, this, &MainWindow::button3Clicked);
    connect(this, &MainWindow::someSignal1, this, &MainWindow::someSlot1); // Qt::AutoConnection
    connect(this, &MainWindow::someSignal2, this, &MainWindow::someSlot2, Qt::QueuedConnection);
}

MainWindow::~MainWindow()
{
    qDebug() << QThread::currentThreadId() << "~MainWindow";
}

void MainWindow::button1Clicked()
{
    qDebug() << QThread::currentThreadId() << "button 1が押されたときに呼ばれるslotのスレッド";
    emit someSignal1();
    qDebug() << QThread::currentThreadId() << "emit完了!";
}
void MainWindow::button2Clicked()
{
    qDebug() << QThread::currentThreadId() << "button 2が押されたときに呼ばれるslotのスレッド";
    emit someSignal2();
    qDebug() << QThread::currentThreadId() << "emit完了!";
}
void MainWindow::button3Clicked()
{
    qDebug() << QThread::currentThreadId() << "button 3が押されたときに呼ばれるslotのスレッド";
    MyThread *t = new MyThread;
    connect(t, &MyThread::intResult, this, [](int result) {
        qDebug() << QThread::currentThreadId() << "intResult:" << result;
    });
    connect(t, &MyThread::stringResult, this, [](const QString &result) {
        qDebug() << QThread::currentThreadId() << "stringResult:" << result;
    });
    connect(t, &MyThread::objectResult, this, [](MyObject result) {
        qDebug() << QThread::currentThreadId() << "objectResult:" << result.i;
    });
    connect(t, &MyThread::object_pResult, this, [](MyObject *result) {
        qDebug() << QThread::currentThreadId() << "object_pResult:" << result->i;
        // resultがリークする
    });
    connect(t, &MyThread::object_spResult, this, [](QSharedPointer<MyObject> result) {
        qDebug() << QThread::currentThreadId() << "object_spResult:" << result->i;
        result->i = 9;
    });
    connect(t, &MyThread::object_spResult, this, [](QSharedPointer<MyObject> result) {
        qDebug() << QThread::currentThreadId() << "object_spResult2:" << result->i;
    });
    connect(t, &MyThread::finishCalculation, this, &MainWindow::someSlot3); // Qt::AutoConnection
    connect(t, &MyThread::finished, t, &MyThread::deleteLater);
    t->start();
}

void MainWindow::someSlot1()
{
    qDebug() << QThread::currentThreadId() << "someSlot1が呼ばれたときのスレッド";
}

void MainWindow::someSlot2()
{
    qDebug() << QThread::currentThreadId() << "someSlot2が呼ばれたときのスレッド";
}

void MainWindow::someSlot3()
{
    qDebug() << QThread::currentThreadId() << "someSlot3が呼ばれたときのスレッド";
}

