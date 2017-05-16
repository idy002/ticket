#include "deltraindialog.h"
#include "ui_deltraindialog.h"
#include "railway.hpp"
#include <QMessageBox>

DelTrainDialog::DelTrainDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DelTrainDialog)
{
    ui->setupUi(this);
}

DelTrainDialog::~DelTrainDialog()
{
    delete ui;
}

void DelTrainDialog::on_pushButton_clicked()
{
    QString trainid = ui->lineEdit->text();
    if( railway.trains.count(trainid) == false ) {
        QMessageBox::warning( this, "出错了", "列车不存在" );
        return;
    }
    Train &train = railway.trains[trainid];
    if( train.seats.size() > 1 ) {
        QMessageBox::warning( this, "出错了", "您只能删除没有计划的列车" );
        return;
    }
    railway.deleteTrain( trainid );
    QMessageBox::warning( this, "操作成功", "列车已删除" );
}
