#include "ui_userdialog.h"
#include "userdialog.h"
#include "buydialog.h"
#include "myticketdialog.h"
#include "infodialog.h"
#include "buyquerydialog.h"
#include <QPainter>
#include <QTimer>

UserDialog::UserDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UserDialog)
{
    ui->setupUi(this);
    QTimer *timer = new QTimer(this);
    connect( timer, SIGNAL(timeout()), this, SLOT(update_time()) );
    timer->start( 1000 );
    update_time();
    ui->nameLabel->setText( QString("尊敬的 %1 ，您好！").arg(railway.users[railway.curUserid].name) );
}

void UserDialog::update_time() {
    ui->timeLabel->setText( QDateTime::currentDateTime().toString("当前时间：yyyy-MM-dd hh:mm:ss"));
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
