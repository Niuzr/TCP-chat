#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextCodec>//保证正常显示中文
#include <QTcpSocket>
#include <QDebug>
#include <QMessageBox>
#include <QByteArray>
#include <QIODevice>
#include <QBuffer>
#include <QImageReader>
#include <QDataStream>    //数据流
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

private:
    Ui::MainWindow *ui;
    QTcpSocket *tsocket;

private slots:
    void connectHostSlot();  //请求建立连接
    void receiveTcpSlot();   //槽函数用于对接受的数据进行处理

    void sendTcpSlot();      //发送tcp信号槽（发送按钮触发）
    void tcpDisconnect();    //tcp连接中断
};

#endif // MAINWINDOW_H
