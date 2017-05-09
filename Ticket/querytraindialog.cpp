#include "querytraindialog.h"
#include "ui_querytraindialog.h"

QueryTrainDialog::QueryTrainDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QueryTrainDialog)
{
    ui->setupUi(this);
}

QueryTrainDialog::~QueryTrainDialog()
{
    delete ui;
}

