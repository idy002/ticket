#include "querytraindialog.h"
#include "railway.hpp"
#include "ui_querytraindialog.h"
#include <QMessageBox>
#include <QTableWidget>
#include <QTableWidgetItem>

QueryTrainDialog::QueryTrainDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QueryTrainDialog)
{
    ui->setupUi(this);

    for( auto it = railway.trains.begin(); it != railway.trains.end(); ++it )
        trainids.push_back( it->first );

    Qt::WindowFlags flags = Qt::Dialog;
    flags |= Qt::WindowMaximizeButtonHint
           | Qt::WindowMinimizeButtonHint
           | Qt::WindowCloseButtonHint;
    setWindowFlags( flags );
}

QueryTrainDialog::~QueryTrainDialog()
{
    delete ui;
}

void QueryTrainDialog::update_trainListWidget() {
    QString trainid = ui->trainidLineEdit->text();
    QStringList list;
    int total = 0, showed = 0;
    for( int t = 0; t < (int)trainids.size(); t++ )
        if( trainids[t].count( trainid ) ) {
            total++;
            if( showed < 100 ) {
                showed++;
                list << trainids[t];
            }
        }
    QMessageBox::information( this, "结果", QString("共找到 %1 列车，显示其中前 %2 个").arg(total).arg(showed) );
    ui->trainListWidget->clear();
    ui->trainListWidget->addItems( list );
}

void QueryTrainDialog::update_dateListWidget() {
    int oldx = ui->dateListWidget->currentRow();
    dates.clear();
    ui->dateListWidget->clear();
    if( railway.trains.count(curTrainid) == 0 )
        return;

    Train & train = railway.trains[curTrainid];
    QStringList list;
    QDate maxdate;
    for( auto it = train.seats.begin(); it != train.seats.end(); ++it ) {
        if( it->first == Date(1,1,1) ) continue;
        dates.push_back( it->first );
        maxdate = tic::max( maxdate, it->first );
        list << QString("[%1] %2").arg(it->second.first ? "正在销售" : "停止销售").arg(it->first.toString(DefaultDateFormat));
    }
    if( maxdate == QDate() ) {
        maxdate = QDate::currentDate();
    }
    ui->dateEdit->setDate( maxdate );
    ui->dateListWidget->addItems( list );
    if( 0 <= oldx && oldx < (int)train.seats.size() ) {
        ui->dateListWidget->setCurrentRow(oldx);
    }
}

void QueryTrainDialog::update_buttons() {
    bool del, restore, stop, start;
    if( curTrainid == "" ) {
        del = restore = stop = start = false;
    } else {
        start = true;
        int row = ui->dateListWidget->currentRow();
        if( row == -1 ) {
            del = restore = stop = false;
        } else {
            if( railway.trains[curTrainid].seats[dates[row]].first == false ) {
                del = true;
                restore = true;
                stop = false;
            } else {
                del = false;
                restore = false;
                stop = true;
            }
        }
    }
    ui->startPushButton->setEnabled( start );
    ui->delPushButton->setEnabled( del );
    ui->restroePushButton->setEnabled( restore );
    ui->stopPushButton->setEnabled( stop );
}

void QueryTrainDialog::update_tableWidget() {
    if( ui->dateListWidget->currentRow() == -1 ) return;
    QDate date = dates[ui->dateListWidget->currentRow()];

    ui->tableWidget->clear();
    if( railway.trains.count(curTrainid) == 0 ) {
        return;
    }
    Train & train = railway.trains[curTrainid];
    if( train.seats.count(date) == 0 ) {
        return;
    }
    pair<bool,map<string,tic::Seat>> &pr = train.seats[date];

    //	0     1    2      3       4    5        6    		7
    //  日期  站名 到达时间 停车时间 里程 1座位票价 1座位票数   .....
    int n = train.stations.size();
    QStringList list;
    list << "日期" << "站名" << "到达时间" << "停车时间" << "里程";
    for( auto it = pr.second.begin(); it != pr.second.end(); ++it ) {
        list << (it->second.type + "票价") << (it->second.type + "余票");
    }
    ui->tableWidget->setRowCount( train.stations.size() );
    ui->tableWidget->setColumnCount( 5 + pr.second.size() * 2 );
    ui->tableWidget->setHorizontalHeaderLabels( list );
    ui->tableWidget->setEditTriggers( QAbstractItemView::NoEditTriggers );
    ui->tableWidget->setSelectionBehavior( QAbstractItemView::SelectRows );
    for( int i = 0; i < n; i++ ) {
        ui->tableWidget->setItem( i, 0, new QTableWidgetItem( date.toString(DefaultDateFormat) ) );
        ui->tableWidget->setItem( i, 1, new QTableWidgetItem( train.stations[i] ) );
        ui->tableWidget->setItem( i, 2, new QTableWidgetItem( tic::transDateTime(date,train.arrive[i]).toString(DefaultDateTimeFormat)) );
        ui->tableWidget->setItem( i, 3, new QTableWidgetItem( tic::transDateTime(date,train.leave[i]).toString(DefaultDateTimeFormat)) );
        ui->tableWidget->setItem( i, 4, new QTableWidgetItem( QString("%1").arg(train.dists[i]) ));
        int j = 0;
        for( auto it = pr.second.begin(); it != pr.second.end(); ++it, j++ ) {
            ui->tableWidget->setItem( i, 5 + j * 2, new QTableWidgetItem( QString("%1").arg(it->second.prices[i]) ));
            ui->tableWidget->setItem( i, 5 + j * 2 + 1, new QTableWidgetItem( QString("%1").arg(it->second.remains[i]) ));
        }
    }
    ui->tableWidget->show();
}

void QueryTrainDialog::on_trainListWidget_itemDoubleClicked(QListWidgetItem *item)
{
    curTrainid = item->text();
}

void QueryTrainDialog::on_startPushButton_clicked()
{
    QDate date = ui->dateEdit->date();
    if( !date.isValid() ) {
        QMessageBox::warning( this, "出错了", "您输入的日期有误，请重新输入" );
        return;
    }
    if( railway.trains.count(curTrainid) == 0 )  return;
    Train &train = railway.trains[curTrainid];
    if( train.seats.count(date) == 0 ) {
        train.seats[date] = train.seats[Date(1,1,1)];
        train.seats[date].first = true;
        update_dateListWidget();
        QMessageBox::information( this, "恭喜您", "添加成功" );
    } else {
        QMessageBox::warning( this, "对不起", "您输入的日期正在售票或停止售票，请重新输入");
        return;
    }
}

void QueryTrainDialog::on_dateListWidget_itemClicked(QListWidgetItem *)
{
    update_buttons();
}

void QueryTrainDialog::on_dateListWidget_itemDoubleClicked(QListWidgetItem *)
{
    update_tableWidget();
    update_buttons();
}

void QueryTrainDialog::on_delPushButton_clicked()
{
    if( railway.trains.count(curTrainid) == 0 ) return;
    Train &train = railway.trains[curTrainid];
    QDate date = dates[ui->dateListWidget->currentRow()];
    if( train.seats.count(date) == 0 ) return;
    if( QMessageBox::Yes == QMessageBox::question( this, "询问",
           QString("请问您确定要删除 列车%1 %2 的记录，数据数据不可恢复！").arg(curTrainid).arg(date.toString(DefaultDateFormat)) ) ) {
        train.seats.erase( train.seats.find(date) );
        QMessageBox::question( this, "完成", "已删除");
        update_dateListWidget();
        update_tableWidget();
        update_buttons();
    } else {
        return;
    }
}

void QueryTrainDialog::on_stopPushButton_clicked()
{
    if( railway.trains.count(curTrainid) == 0 ) return;
    if( ui->dateListWidget->currentRow() == -1 ) return;
    QDate date = dates[ui->dateListWidget->currentRow()];
//    if( train.seats.count(date) == 0 ) return;
//    train.seats[date].first = false;
    railway.stopSell( curTrainid, date );
    update_dateListWidget();
    update_tableWidget();
    update_buttons();
}

void QueryTrainDialog::on_restroePushButton_clicked()
{
    if( railway.trains.count(curTrainid) == 0 ) return;
    QDate date = dates[ui->dateListWidget->currentRow()];
//    if( train.seats.count(date) == 0 ) return;
//    train.seats[date].first = true;
    railway.startSell( curTrainid, date );
    update_dateListWidget();
    update_tableWidget();
    update_buttons();
}


void QueryTrainDialog::on_pushButton_clicked()
{
    update_trainListWidget();
}

void QueryTrainDialog::on_pushButton_2_clicked()
{
    if( ui->trainListWidget->currentRow() == -1 ) {
        QMessageBox::warning( this, "出错了", "请选择要查看的列车" );
        return;
    }
    curTrainid = ui->trainListWidget->currentItem()->text();
    update_dateListWidget();
    update_buttons();
    update_tableWidget();
}
