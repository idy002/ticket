#include "logindialog.h"
#include "ui_logindialog.h"
#include "signupdialog.h"
#include "managerdialog.h"
#include "userdialog.h"
#include "railway.hpp"
#include <QMessageBox>

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
//    tic::load( "railway.data", railway );
    tic::load( "D:/TicketData/SmallSet/railway.data", railway );
}

LoginDialog::~LoginDialog()
{
//    tic::save( "railway.data", railway );
    tic::save( "D:/TicketData/SmallSet/railway.data", railway );
    delete ui;
}

void LoginDialog::on_loginPushButton_clicked()
{
    QString id, pwd;
    id = ui->idLE->text();
    pwd = ui->pwdLE->text();
    if( checkIdPwd(id,pwd) == true ) {
        railway.curUserid = id;
        ui->idLE->clear();
        ui->pwdLE->clear();
        ui->idLE->setFocus();
        if( railway.users[id].isManager ) {
            ManagerDialog managerDialog;
            this->hide();
            if( managerDialog.exec() == QDialog::Accepted ) {
                this->show();
            } else {
                accept();
            }
        } else {
            UserDialog userDialog;
            if( userDialog.exec() == QDialog::Accepted ) {
                this->show();
            } else {
                accept();
            }
        }
    } else {
        QMessageBox::warning( this, "对不起", "用户名或密码错误，请您重新输入" );
        ui->idLE->clear();
        ui->pwdLE->clear();
        ui->idLE->setFocus();
    }
}

bool LoginDialog::checkIdPwd(QString sid, QString spwd) {
    if( railway.users.count(sid) && railway.users[sid].password == spwd ) return true;
    return false;
}

void LoginDialog::on_forgetPwdPushButton_clicked()
{
    QMessageBox::information( this, "对不起", "请您重新注册一个账号，不是我懒，只是让你长记性-_-");
}

void LoginDialog::on_signupPushButton_clicked()
{
    SignupDialog signupDialog;
    signupDialog.exec();
}
