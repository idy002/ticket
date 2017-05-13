#include "signupdialog.h"
#include "ui_signupdialog.h"
#include <QMessageBox>
#include "railway.hpp"

SignupDialog::SignupDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SignupDialog)
{
    ui->setupUi(this);
}

SignupDialog::~SignupDialog()
{
    delete ui;
}

void SignupDialog::on_signPushButton_clicked()
{
    QString id, name, pwd, repwd;
    id = ui->idLineEdit->text();
    name = ui->nameLineEdit->text();
    pwd = ui->pwdLineEdit->text();
    repwd = ui->pwdLineEdit->text();
    if( id.length() < 6 ) {
        QMessageBox::warning( this, "出错了", "至少为6位字符，请重新输入" );
        return;
    }
    if( railway.users.count(id) ) {
        QMessageBox::warning( this, "出错了", "此用户名已经被注册过了，请换一个" );
        ui->idLineEdit->clear();
        ui->idLineEdit->setFocus();
        return;
    }
    if( name.isEmpty() ) {
        QMessageBox::warning( this, "出错了", "姓名不能为空" );
        return;
    }
    if( pwd != repwd ) {
        QMessageBox::warning( this, "出错了", "两次密码输入不一致，请重新输入" );
        ui->pwdLineEdit->clear();
        ui->repwdLineEdit->clear();
        ui->pwdLineEdit->setFocus();
        return;
    }
    if( pwd.length() < 6 ) {
        QMessageBox::warning( this, "出错了", "密码长度至少为6位，请重新输入" );
        ui->pwdLineEdit->clear();
        ui->repwdLineEdit->clear();
        ui->pwdLineEdit->setFocus();
        return;
    }
    bool applyManager = ui->managerCheckBox->isChecked();
    railway.addUser( id, name, pwd, applyManager );
//    railway.users[id] = tic::User(id,name,pwd,applyManager);
    QMessageBox::information( this, "恭喜你", "注册成功了");
    accept();
}
