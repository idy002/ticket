#include "prequerytraindialog.h"
#include "ui_prequerytraindialog.h"
#include "querytraindialog.h"

PreQueryTrainDialog::PreQueryTrainDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PreQueryTrainDialog)
{
    ui->setupUi(this);
}

PreQueryTrainDialog::~PreQueryTrainDialog()
{
    delete ui;
}

void PreQueryTrainDialog::on_pushButton_clicked()
{
    QueryTrainDialog queryTrainDialog;
    queryTrainDialog.exec();
}
