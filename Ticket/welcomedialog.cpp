#include "welcomedialog.h"
#include "ui_welcomedialog.h"
#include <QTimer>

WelcomeDialog::WelcomeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WelcomeDialog)
{
    ui->setupUi(this);

    /*
    QTimer *timer = new QTimer(this);
    connect( timer, SIGNAL(timeout()), this, SLOT(update()) );
    timer->start( 80 );
    ui->progressBar->setValue(0);
    */

    Qt::WindowFlags flags = 0;
    flags |= Qt::FramelessWindowHint;
    this->setWindowFlags(flags);
}

void WelcomeDialog::update() {
    int curValue = ui->progressBar->value();
    curValue = curValue % 100 + 1;
    ui->progressBar->setValue( curValue );
}

WelcomeDialog::~WelcomeDialog()
{
    delete ui;
}
