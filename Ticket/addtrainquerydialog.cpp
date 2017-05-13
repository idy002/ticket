#include "addtrainquerydialog.h"
#include "addtraindialog.h"
#include "railway.hpp"
#include "ui_addtrainquerydialog.h"
#include <QMessageBox>

AddTrainQueryDialog::AddTrainQueryDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddTrainQueryDialog)
{
    ui->setupUi(this);
}

AddTrainQueryDialog::~AddTrainQueryDialog()
{
    delete ui;
}

void AddTrainQueryDialog::on_finishPushButton_clicked()
{
    QString trainid = ui->idLineEdit->text();
    int stations_count = ui->stationCntLineEdit->text().toInt();
    int types_count = ui->typeCntLineEdit->text().toInt();
    if( railway.trains.count(trainid) ) {
        QMessageBox::warning( this, "出错了", "这列火车已经存在,请重新输入列车编号" );
        ui->idLineEdit->clear();
        ui->idLineEdit->setFocus();
        return;
    }
    if( stations_count <= 0 || stations_count > 1000 ) {
        QMessageBox::warning( this, "出错了", "列车经停车站数不合法，请重新输入" );
        ui->stationCntLineEdit->clear();
        ui->stationCntLineEdit->setFocus();
        return;
    }
    if( types_count <= 0 || types_count > 20 ) {
        QMessageBox::warning( this, "出错了", "列车座位种类数不合法，请重新输入" );
        ui->typeCntLineEdit->clear();
        ui->typeCntLineEdit->setFocus();
        return;
    }
    AddTrainDialog addTrainDialog( this, trainid, stations_count, types_count );
    addTrainDialog.exec();
    accept();
}
