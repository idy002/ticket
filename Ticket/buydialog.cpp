#include "railway.hpp"
#include "buydialog.h"
#include "ui_buydialog.h"
#include <QTableWidget>
#include <QMessageBox>
#include <QHeaderView>

BuyDialog::BuyDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BuyDialog)
{
    ui->setupUi(this);
}
BuyDialog::BuyDialog(QWidget *parent, QDate date, QString from, QString to) :
    QDialog(parent),
    ui(new Ui::BuyDialog)
{
    ui->setupUi(this);
    this->date = date;
    this->from = from;
    this->to = to;
    railway.queryTicket( date, from, to, "", vec );
    QStringList header;
    header << "日期" << "车站编号" << "起始站" << "终点站" << "发车时间" << "到达时间" << "里程" << "座位类型" << "票价" << "余票";
    ui->tableWidget->setRowCount(vec.size());
    ui->tableWidget->setColumnCount(10);
    ui->tableWidget->setHorizontalHeaderLabels( header );
    ui->tableWidget->setEditTriggers( QAbstractItemView::NoEditTriggers );
    ui->tableWidget->setSelectionBehavior( QAbstractItemView::SelectRows );
    ui->tableWidget->setSelectionMode( QAbstractItemView::SingleSelection );
    ui->tableWidget->verticalHeader()->setSectionResizeMode( QHeaderView::Fixed );
    for( int t = 0; t < (int)vec.size(); t++ ) {
        QString row[10];
        tic::Ticket & tk = vec[t].first;
        row[0] = tk.date.toString();
        row[1] = tk.trainid;
        row[2] = tk.from;
        row[3] = tk.to;
        row[4] = tk.leave.toString();
        row[5] = tk.arrive.toString();
        row[6] = QString::number(tk.dist);
        row[7] = tk.type;
        row[8] = QString::number(tk.price,'f',1);
        row[9] = QString::number(vec[t].second);
        for( int tt = 0; tt < 10; tt++ ) {
            QTableWidgetItem *item = new QTableWidgetItem(row[tt]);
            item->setTextAlignment( Qt::AlignHCenter | Qt::AlignVCenter );
            ui->tableWidget->setItem( t, tt, item );
        }
    }

    Qt::WindowFlags flags = Qt::Dialog;
    flags |= Qt::WindowMaximizeButtonHint
           | Qt::WindowMinimizeButtonHint
           | Qt::WindowCloseButtonHint;
    setWindowFlags( flags );
}

BuyDialog::~BuyDialog()
{
    delete ui;
}

void BuyDialog::setQueryInfo(QDate date, QString from, QString to) {
    this->date = date;
    this->from = from;
    this->to = to;
}
