#include "userdialog.h"
#include "buydialog.h"
#include "myticketdialog.h"
#include "infodialog.h"
#include "buyquerydialog.h"
#include "managerdialog.h"
#include "deltraindialog.h"
#include "ui_managerdialog.h"
#include "addtraindialog.h"
#include "querytraindialog.h"
#include "addtrainquerydialog.h"
#include "queryuserdialog.h"
#include "logdialog.h"

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
    AddTrainQueryDialog addTrainQueryDialog;
    addTrainQueryDialog.exec();
}

void ManagerDialog::on_delPushButton_clicked()
{
    DelTrainDialog delTrainDialog;
    delTrainDialog.exec();
}

void ManagerDialog::on_showPushButton_clicked()
{
    QueryTrainDialog queryTrainDialog;
    queryTrainDialog.exec();
}

void ManagerDialog::on_myTiccketButton_clicked()
{
    MyTicketDialog myTicketDialog;
    myTicketDialog.exec();
}

void ManagerDialog::on_buyTicketButton_clicked()
{
    BuyQueryDialog buyQueryDialog;
    buyQueryDialog.exec();
}

void ManagerDialog::on_modifyInfoButton_clicked()
{
    InfoDialog infoDialog;
    infoDialog.exec();
}

void ManagerDialog::on_showPushButton_2_clicked()
{
    QueryUserDialog queryTrainDialog;
    queryTrainDialog.exec();
}

void ManagerDialog::on_logPushButton_clicked()
{
    LogDialog logDialog;
    logDialog.exec();
}
