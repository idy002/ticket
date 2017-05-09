#include "managerdialog.h"
#include "deltraindialog.h"
#include "ui_managerdialog.h"
#include "addtraindialog.h"
#include "prequerytraindialog.h"

ManagerDialog::ManagerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ManagerDialog)
{
    ui->setupUi(this);
}

ManagerDialog::~ManagerDialog()
{
    delete ui;
}

void ManagerDialog::on_addPushButton_clicked()
{
    AddTrainDialog addTrainDialog;
    addTrainDialog.exec();
}

void ManagerDialog::on_delPushButton_clicked()
{
    DelTrainDialog delTrainDialog;
    delTrainDialog.exec();
}

void ManagerDialog::on_showPushButton_clicked()
{
    PreQueryTrainDialog preQueryTrainDialog;
    preQueryTrainDialog.exec();
}
