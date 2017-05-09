#include "refunddialog.h"
#include "ui_refunddialog.h"

RefundDialog::RefundDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RefundDialog)
{
    ui->setupUi(this);
}

RefundDialog::~RefundDialog()
{
    delete ui;
}
