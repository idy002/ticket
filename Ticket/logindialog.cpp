#include "logindialog.h"
#include "ui_logindialog.h"
#include "railway.hpp"
#include <QMessageBox>

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::on_loginPushButton_clicked()
{
    QString id, pwd;
    id = ui->idLE->text();
    pwd = ui->pwdLE->text();
    if( checkIdPwd(id,pwd) == true ) {
        curUserid = id;
        ui->idLE->clear();
        ui->pwdLE->clear();
        ui->idLE->setFocus();
        accept();
    } else {
        QMessageBox::warning( this, "对不起", "用户名或密码错误，请您重新输入" );
        ui->idLE->clear();
        ui->pwdLE->clear();
        ui->idLE->setFocus();
    }
}

bool LoginDialog::checkIdPwd(QString sid, QString spwd) {
    if( railway.users.count(sid) && railway.users[sid].password == spwd ) return true;
    if( railway.managers.count(sid) && railway.managers[sid].password == spwd ) return true;
    return false;
}
