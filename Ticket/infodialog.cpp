#include "infodialog.h"
#include "ui_infodialog.h"
#include "railway.hpp"
#include <QMessageBox>

InfoDialog::InfoDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InfoDialog)
{
    ui->setupUi(this);

    tic::User &user = railway.users[railway.curUserid];
    ui->userIDLineEdit->setText( user.id );
    ui->userNameLineEdit->setText( user.name );
}

InfoDialog::~InfoDialog()
{
    delete ui;
}

void InfoDialog::on_pushButton_clicked()
{
    QString newname = ui->userNameLineEdit->text();
    QString newpwd = ui->pwdLineEdit->text();
    QString repwd = ui->repwdLineEdit->text();
    tic::User &user = railway.users[railway.curUserid];
    if( newpwd.isEmpty() && repwd.isEmpty() ) {
        newpwd = repwd = user.password;
    }
    if( newname.isEmpty() ) {
        QMessageBox::warning( this, "出错了", "姓名不能为空，重请新输入" );
        ui->userNameLineEdit->setFocus();
        return;
    }
    if( newpwd != repwd ) {
        QMessageBox::warning( this, "出错了", "两次密码输入不一致，请重新输入" );
        ui->pwdLineEdit->clear();
        ui->repwdLineEdit->clear();
        ui->pwdLineEdit->setFocus();
        return;
    }
    if( newpwd.length() < 6 ) {
        QMessageBox::warning( this, "出错了", "密码长度过，短密码长度至少为6个字符，请重新输入" );
        ui->pwdLineEdit->clear();
        ui->repwdLineEdit->clear();
        ui->pwdLineEdit->setFocus();
        return;
    }
    user.name = newname;
    user.password = newpwd;
    QMessageBox::information( this, "完成", "信息修改成功" );
    accept();
}
