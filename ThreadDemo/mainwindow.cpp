#include "mainwindow.h"

#include <QVBoxLayout>
#include <QPushButton>
#include <QThread>

void debug(const QString &message);

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), otherTaskThread(this)
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
    QPushButton *button4 = new QPushButton("button 4");
    layout->addWidget(button4);
    QPushButton *button5 = new QPushButton("button 5");
    layout->addWidget(button5);
    widget->setLayout(layout);
    setCentralWidget(widget);

    // otherTaskObjectを生成し、別スレッドに移す
    otherTaskObject = new OtherTaskObject;
    otherTaskObject->moveToThread(&otherTaskThread);
    otherTaskThread.start();

    // シグナルとスロットを繋ぐ
    connect(button1, &QPushButton::clicked, this, &MainWindow::button1Clicked);
    connect(button2, &QPushButton::clicked, this, &MainWindow::button2Clicked);
    connect(button3, &QPushButton::clicked, this, &MainWindow::button3Clicked);
    connect(button4, &QPushButton::clicked, this, &MainWindow::button4Clicked);
    connect(button5, &QPushButton::clicked, this, &MainWindow::button5Clicked);
    connect(otherTaskObject, &OtherTaskObject::finishJob, this, &MainWindow::someSlot1);
}

MainWindow::~MainWindow()
{
    debug("~MainWindow");
    otherTaskThread.quit();
    otherTaskThread.wait();
}

void MainWindow::button1Clicked()
{
    debug("call otherTaskObject->startJob1()");
    otherTaskObject->startJob1();
}
void MainWindow::button2Clicked()
{
    debug("call otherTaskObject->startJobInternal1()");
    otherTaskObject->startJobInternal1();
}
void MainWindow::button3Clicked()
{
    debug("call otherTaskObject->startJob2()");
    otherTaskObject->startJob2();
}
void MainWindow::button4Clicked()
{
    debug("call otherTaskObject->startJobInternal2()");
    otherTaskObject->startJobInternal2();
}
void MainWindow::button5Clicked()
{
    debug("call otherTaskObject->startLongJob()");
    otherTaskObject->startLongJob();
}

void MainWindow::someSlot1()
{
    debug("receive finished signal");
}

