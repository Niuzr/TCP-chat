#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{


    ui->setupUi(this);

    tsocket =new QTcpSocket;  //新建一个TCP套接字


    QObject::connect(ui->connectButton,SIGNAL(clicked(bool)),this,SLOT(connectHostSlot()));  //连接主机
    QObject::connect(ui->sendButton,SIGNAL(clicked(bool)),this,SLOT(sendTcpSlot()));  //发送数据
    QObject::connect(tsocket,SIGNAL(readyRead()),this,SLOT(receiveTcpSlot()));  //接收数据
    QObject::connect(tsocket,SIGNAL(disconnected()),this,SLOT(tcpDisconnect()));  //tcp连接中断

}

MainWindow::~MainWindow()
{
    delete ui;
    delete this->tsocket;  //清理内存
}
void MainWindow::connectHostSlot()  //请求建立连接
{
    if(ui->connectButton->text()=="连接")
    {
        QString hostip=ui->hostIpLineEdit->text();  //获取主机ip
        quint16 hostport=quint16(ui->hostPortLineEdit->text().toUInt());  //获取主机端口
        tsocket->abort(); //取消已有连接
        tsocket->connectToHost(hostip,hostport);  //请求与服务器建立连接

        if(!tsocket->waitForConnected(30000))  //等待30s
        {
            QMessageBox::information(this,"提示","连接失败");
            return;
        }
        else
        {
            QMessageBox::information(this,"提示","连接成功");

            ui->connectButton->setText("断开连接");
        }
    }
    else
    {
        tsocket->disconnectFromHost();  //断开连接
        ui->connectButton->setText("连接");
    }
}
void MainWindow::receiveTcpSlot()   //槽函数用于对接受的数据进行处理
{



//         QByteArray array;
//         while(tsocket->waitForReadyRead(1)){           //连续接收 ，知道接收完毕
//             qDebug()<<"bytesAvailable"<<endl;
//             array.append((QByteArray)tsocket->readAll());
//         }
//
//         QBuffer buffer(&array);
//         buffer.open(QIODevice::ReadOnly);
//
//         QImageReader reader(&buffer,"JPG");
//         QImage img = reader.read();
//
//         if(!img.isNull()){
//             qDebug()<<"right"<<endl;
//             ui->imageLabel->setPixmap(QPixmap::fromImage(img).scaled(ui->imageLabel->size()));//按比例缩放
//         } else {
//             qDebug()<<"error"<<endl;
//         }

    QByteArray receiveData; //因为传来的数据类型是未知的，用bytearray类型
    receiveData=tsocket->readAll();
    ui->receiveContextTextEdit->append(QString::fromUtf8(receiveData));   //转换成char *

}
void MainWindow::sendTcpSlot()      //发送tcp信号槽（发送按钮触发）
{
    //添加判断连接
    QString sendContext=ui->sendContextTextEdit->document()->toPlainText();//////////////////////
//    tsocket->write(sendContext.toLatin1());
    tsocket->write(sendContext.toUtf8());  //将QString转换成QByteArray类型发送
    tsocket->flush();
}
void MainWindow::tcpDisconnect()    //tcp连接中断
{
    ui->connectButton->setText("连接");
    QMessageBox::information(this,"提示","TCP连接中断");
}
