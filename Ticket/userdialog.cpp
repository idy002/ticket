#include "ui_userdialog.h"
#include "userdialog.h"
#include "buydialog.h"
#include "myticketdialog.h"
#include "infodialog.h"
#include "buyquerydialog.h"
#include <QPainter>

UserDialog::UserDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UserDialog)
{
    ui->setupUi(this);
}

UserDialog::~UserDialog()
{
    delete ui;
}

void UserDialog::on_myTiccketButton_clicked()
{
    MyTicketDialog myTicketDialog;
    myTicketDialog.exec();
}

void UserDialog::on_buyTicketButton_clicked()
{
    BuyQueryDialog buyQueryDialog;
    buyQueryDialog.exec();
}

void UserDialog::on_modifyInfoButton_clicked()
{
    InfoDialog infoDialog;
    infoDialog.exec();
}
