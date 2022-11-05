#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    tserver =new QTcpServer;  //创建新TCP服务器

    QObject::connect(ui->listenButton,SIGNAL(clicked(bool)),this,SLOT(listenStartSlot()));  //开始侦听
    QObject::connect(this->tserver,SIGNAL(newConnection()),this,SLOT(newConnectSlot()));  //侦听到新连接
    QObject::connect(ui->sendButton,SIGNAL(clicked(bool)),this,SLOT(sendTcpSlot()));  //发送数据

    //线程实验
    QObject::connect(ui->closeThreadButton,SIGNAL(clicked(bool)),this,SLOT(closeThreadSlot()));
    //线程实验
    pb=0;
    thread=new myThread(pb);
    thread->start();
}

MainWindow::~MainWindow()
{
    tserver->close();
    tserver->deleteLater();

    delete thread;  //线程实验
    delete ui;
}
void MainWindow::listenStartSlot()  //开始侦听槽
{
    if(ui->listenButton->text()=="侦听")
    {
        quint16 port=quint16(ui->listenPortLineEdit->text().toUInt());//获取监听端口
        qDebug()<<"port:"<<port;
        if(!tserver->listen(QHostAddress::Any,port))
        {
            QMessageBox::information(this,"提示","侦听设置出错");
            return;
        }
        else
        {
            QMessageBox::information(this,"提示","开始侦听");
            ui->listenButton->setText("取消侦听");
        }

    }
    else
    {
        if(tsocket->state()==QAbstractSocket::ConnectedState)
        {
            tsocket->disconnectFromHost();  //关闭连接

        }
        tserver->close();  //取消侦听
        ui->listenButton->setText("侦听");
    }

}

void MainWindow::newConnectSlot()   //收到新连接
{
    tsocket=tserver->nextPendingConnection();  //server让自己的socket与client的socket相连
    QObject::connect(this->tsocket,SIGNAL(disconnected()),this,SLOT(tcpDisconnect()));  //套接字断开连接
    QObject::connect(this->tsocket,SIGNAL(readyRead()),this,SLOT(receiveTcpSlot()));  //收到数据
    QMessageBox::information(this,"提示","侦听到新连接");

}

void MainWindow::receiveTcpSlot()   //槽函数用于对接受的数据进行处理
{
    QByteArray receiveData; //因为传来的数据类型是未知的，用bytearray类型
    receiveData=tsocket->readAll();
    //QTime time=QTime::currentTime();
   // ui->receiveContextTextEdit->append(QString::fromUtf8(ctime));
    ui->receiveContextTextEdit->append(QString::fromUtf8(receiveData));   //////////////

}
void MainWindow::sendTcpSlot()      //发送tcp信号槽（发送按钮触发）
{

    //发送图片
  //      qDebug()<<"sendPicture clicked"<<endl;

   //     QPixmap pixmap(tr("th.jpg"));
   //     QBuffer buffer;
   //    buffer.open(QIODevice::ReadWrite);
   //     pixmap.save(&buffer,"jpg");
   //     quint32 pixmap_len = (quint32)buffer.data().size();
   //     qDebug("image size:%d",pixmap_len);

  //      QByteArray dataArray;
   //     dataArray.append(buffer.data());

    //    quint32 write_len = tsocket->write(dataArray);
   //     qDebug("write len:%d",write_len);


    //添加判断连接
    QString sendContext=ui->sendContextTextEdit->document()->toPlainText();//////////////////////
    tsocket->write(sendContext.toUtf8());  //以Utf8形式的bytearray发送
    tsocket->flush();

}
void MainWindow::tcpDisconnect()    //tcp连接中断
{
    ui->listenButton->setText("侦听");
    QMessageBox::information(this,"提示","TCP连接中断");

}
void MainWindow::closeThreadSlot()
{
    delete thread;

}
































