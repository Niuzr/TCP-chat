#include "mainwindow.h"
#include <QApplication>
#include<logindlg.h>

int main(int argc, char *argv[])
{
    //QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF8"));  //中文编码
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF8"));
    //QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF8"));

    QApplication a(argc, argv);
    MainWindow w;
    loginDlg dlg;
    if(dlg.exec()==QDialog::Accepted)
    {
        w.show();
        return a.exec();
    }
    else

    {
        return 0;
    }
}
