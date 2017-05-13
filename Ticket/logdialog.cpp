#include "logdialog.h"
#include "ui_logdialog.h"
#include "railway.hpp"

LogDialog::LogDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LogDialog)
{
    ui->setupUi(this);
    QDate mindate, maxdate;
    if( railway.logs.size() == 0 ) {
        mindate = maxdate = QDate::currentDate();
    } else {
        mindate = railway.logs.begin()->date;
        maxdate = (--railway.logs.end())->date;
    }
    ui->startDateEdit->setDate( mindate );
    ui->endDateEdit->setDate( maxdate );
    Qt::WindowFlags flags = Qt::Dialog;
    flags |= Qt::WindowMaximizeButtonHint
           | Qt::WindowMinimizeButtonHint
           | Qt::WindowCloseButtonHint;
    setWindowFlags( flags );
}

LogDialog::~LogDialog()
{
    delete ui;
}

void LogDialog::on_queryPushButton_clicked()
{
    QString userid = ui->userLineEdit->text();
    QDate start = ui->startDateEdit->date();
    QDate end = ui->endDateEdit->date();
    tic::set<tic::Log> &logs = railway.logs;
    tic::vector<tic::Log> vc;
    int total = 0, showed = 0;
    for( auto it = logs.begin(); it != logs.end(); ++it ) {
        if( start <= it->date && it->date <= end && it->userid.count(userid) ) {
            total++;
            if( showed <= 1000 ) {
                showed++;
                vc.push_back( *it );
            }
        }
    }

    QStringList header;
    header << "日期" << "时间" << "操作用户" << "事件";
    ui->tableWidget->setRowCount(vc.size());
    ui->tableWidget->setColumnCount(4);
    ui->tableWidget->setHorizontalHeaderLabels( header );
    ui->tableWidget->setEditTriggers( QAbstractItemView::NoEditTriggers );
    ui->tableWidget->setSelectionBehavior( QAbstractItemView::SelectRows );
    ui->tableWidget->verticalHeader()->setSectionResizeMode( QHeaderView::Fixed );
    ui->tableWidget->horizontalHeader()->setSectionResizeMode( QHeaderView::Stretch );
    for( int i = 0; i < showed; i++ ) {
        ui->tableWidget->setItem( i, 0, new QTableWidgetItem( vc[i].date.toString() ));
        ui->tableWidget->setItem( i, 1, new QTableWidgetItem( vc[i].time.toString() ));
        ui->tableWidget->setItem( i, 2, new QTableWidgetItem( vc[i].userid ));
        ui->tableWidget->setItem( i, 3, new QTableWidgetItem( vc[i].message ));
    }
}
