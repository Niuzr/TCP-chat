#include "logindlg.h"
#include "ui_logindlg.h"

loginDlg::loginDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::loginDlg)
{
    ui->setupUi(this);
}

loginDlg::~loginDlg()
{
    delete ui;
}

void loginDlg::on_loginBtn_clicked()
{
    accept();
}

