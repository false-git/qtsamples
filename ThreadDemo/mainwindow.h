#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAbstractButton>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:
    void someSignal1();
    void someSignal2();

private slots:
    void button1Clicked();
    void button2Clicked();
    void button3Clicked();
    void someSlot1();
    void someSlot2();
    void someSlot3();

private:

};

#endif // MAINWINDOW_H
