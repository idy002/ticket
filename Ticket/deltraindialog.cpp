#include "deltraindialog.h"
#include "ui_deltraindialog.h"

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
