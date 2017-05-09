#include "addtraindialog.h"
#include "ui_addtraindialog.h"

AddTrainDialog::AddTrainDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddTrainDialog)
{
    ui->setupUi(this);
}

AddTrainDialog::~AddTrainDialog()
{
    delete ui;
}
