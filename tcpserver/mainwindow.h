#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpServer>
#include <QTextCodec>//保证正常显示中文
#include <QTcpSocket>
#include <QDebug>
#include <QMessageBox>
#include <QByteArray>
#include <QImage>  //图片
#include <QTimer>
#include <QBuffer>
#include <mythread.h>  //线程实验
#include<ctime>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QImage *image;
    QTimer *timer;

    //线程实验
    myThread *thread;
    int pb;
private:
    Ui::MainWindow *ui;
    QTcpServer *tserver;
    QTcpSocket *tsocket;

private slots:
    void listenStartSlot();  //开始侦听槽
    void newConnectSlot();   //收到新连接
    void receiveTcpSlot();   //槽函数用于对接受的数据进行处理
    void sendTcpSlot();      //发送tcp信号槽（发送按钮触发）
    void tcpDisconnect();    //tcp连接中断

    //线程实验
    void closeThreadSlot();
};

#endif // MAINWINDOW_H
