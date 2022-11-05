#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{

    //QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF8"));  //保证正常显示中文
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF8"));
    //QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF8"));

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    //多线程实验
    return a.exec();
}
