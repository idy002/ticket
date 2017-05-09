#include "myticketdialog.h"
#include "ui_myticketdialog.h"

MyTicketDialog::MyTicketDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MyTicketDialog)
{
    ui->setupUi(this);
}

MyTicketDialog::~MyTicketDialog()
{
    delete ui;
}
