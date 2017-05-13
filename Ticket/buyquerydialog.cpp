#include "buyquerydialog.h"
#include "buydialog.h"
#include "ui_buyquerydialog.h"

BuyQueryDialog::BuyQueryDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BuyQueryDialog)
{
    ui->setupUi(this);
    ui->dateEdit->setDate( QDate::currentDate() );
}

BuyQueryDialog::~BuyQueryDialog()
{
    delete ui;
}

void BuyQueryDialog::on_pushButton_clicked()
{
    QDate date = ui->dateEdit->date();
    QString from = ui->startLineEdit->text();
    QString to = ui->endLineEdit->text();
    BuyDialog buyDialog(this,date,from,to);
    this->hide();
    buyDialog.exec();
    accept();
}
