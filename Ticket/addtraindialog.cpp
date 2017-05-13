#include "addtraindialog.h"
#include "ui_addtraindialog.h"
#include "railway.hpp"
#include <QDateTimeEdit>
#include <QMessageBox>
#include <QTableWidget>

AddTrainDialog::AddTrainDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddTrainDialog)
{
    ui->setupUi(this);
}
AddTrainDialog::AddTrainDialog(QWidget *parent, QString trainid, int stations_count, int types_count ) :
    QDialog(parent),
    ui(new Ui::AddTrainDialog)
{
    ui->setupUi(this);
    //			0    1      2       3     4     5    		6
    //		   站名 到达时间 停车时间 里程 1座位票价	1座位票数   .....
    this->trainid = trainid;
    this->stations_count = stations_count;
    this->types_count = types_count;
    QStringList header;
    ui->tableWidget->setRowCount( stations_count + 1 );
    ui->tableWidget->setColumnCount( 4 + types_count * 2 );
    header << "站名" << "到达时间" << "停车时间" << "里程";
    ui->tableWidget->setSpan( 0, 0, 1, 4 );
    for( int t = 0; t < types_count; t++ ) {
        header << QString("%1座位票价").arg(t+1) << QString("%1座位票数").arg(t+1);
        ui->tableWidget->setSpan( 0, 4 + t * 2, 1, 2 );
    }
    ui->tableWidget->setHorizontalHeaderLabels( header );
    for( int i = 0; i <= stations_count; i++ ) {
        for( int j = 0; j < 4 + types_count * 2; j++ ) {
            if( i == 0 ) {
                if( j <= 3 ) {
                    ui->tableWidget->setItem( i, j, new QTableWidgetItem() );
                    ui->tableWidget->item( i, j )->setFlags( Qt::NoItemFlags );
                } else {
                    ui->tableWidget->setItem( i, j, new QTableWidgetItem( "类型名" ) );
                }
            } else {
                if( j == 1 || j == 2 ) {
                    ui->tableWidget->setCellWidget( i, j, new QDateTimeEdit );
                }
            }
        }
    }

    Qt::WindowFlags flags = Qt::Dialog;
    flags |= Qt::WindowMaximizeButtonHint
           | Qt::WindowMinimizeButtonHint
           | Qt::WindowCloseButtonHint;
    setWindowFlags( flags );
}

AddTrainDialog::~AddTrainDialog()
{
    delete ui;
}

void AddTrainDialog::on_finishPushButton_clicked()
{
    //			0    1      2       3     4     5    6
    //		   站名 到达时间 停车时间 里程 座位1	  座位2 .....
    tic::Train train;
    train.id = trainid;
    vector<QString> type_names;
    map<string,tic::Seat> & mseat = train.seats[Date(1,1,1)].second;

    for( int j = 0; j < types_count; j++ ) {
        QString type_name = ui->tableWidget->item( 0, 4 + j * 2 )->text();
        if( type_name.isEmpty() || type_name == "类型名" ) {
            QMessageBox::warning( this, "出错了", "请正确输入座位类型名" );
            ui->tableWidget->setCurrentCell( 0, 4 + j * 2 );
            return;
        } else {
            type_names.push_back( type_name );
            mseat[type_name].type = type_name;
        }
    }
    for( int i = 1; i <= stations_count; i++ ) {
        QString station;
        QTime arrive, leave;
        int dist;
        station = ui->tableWidget->item(i,0)->text();
        arrive = ((QDateTimeEdit*)ui->tableWidget->cellWidget(i,1))->time();
        leave = ((QDateTimeEdit*)ui->tableWidget->cellWidget(i,2))->time();
        dist = ui->tableWidget->item(i,3)->text().toInt();
        if( station.isEmpty() ) {
            QMessageBox::warning( this, "出错了", QString("第 %1 站站名为空，请重新输入").arg(i) );
            ui->tableWidget->setCurrentCell( i, 0 );
            return;
        }
        if( !arrive.isValid() ) {
            QMessageBox::warning( this, "出错了", QString("第 %1 站到达时间无效，请重新输入").arg(i) );
            ui->tableWidget->setCurrentCell( i, 1 );
            return;
        }
        if( !leave.isValid() ) {
            QMessageBox::warning( this, "出错了", QString("第 %1 站离开时间无效，请重新输入").arg(i) );
            ui->tableWidget->setCurrentCell( i, 2 );
            return;
        }
        if( (i == 1 && dist != 0) || (i > 1 && dist < train.dists.back()) ) {
            QMessageBox::warning( this, "出错了", QString("第 %1 站距离不合法，请重新输入").arg(i) );
            ui->tableWidget->setCurrentCell( i, 3 );
            return;
        }
        train.stations.push_back( station );
        train.arrive.push_back( arrive );
        train.leave.push_back( leave );
        train.dists.push_back( dist );
        for( int j = 0; j < types_count; j++ ) {
            double price = ui->tableWidget->item(i,4 + j * 2)->text().toDouble();
            int remain = ui->tableWidget->item(i, 4 + j * 2 + 1)->text().toInt();
            if( remain <= 0 ) {
                QMessageBox::warning( this, "出错了", QString("第 %1 站 %2 类型座位余票不合法，请重新输入").arg(i).arg(type_names[j]) );
                ui->tableWidget->setCurrentCell( i, 4 + j * 2 + 1 );
                return;
            }
            if( price < -1e-8 ) {
                QMessageBox::warning( this, "出错了", QString("第 %1 站 %2 类型座位票价为负，请重新输入").arg(i).arg(type_names[j]) );
                ui->tableWidget->setCurrentCell( i, 4 + j * 2  );
                return;
            }
            if( (i == 1 && price > 1e-8) || (i > 1 && price > 1e-8 && price < mseat[type_names[j]].prices.back()) ) {
                QMessageBox::warning( this, "出错了", QString("第 %1 站 %2 类型座位票价不合法，请重新输入").arg(i).arg(type_names[j]) );
                ui->tableWidget->setCurrentCell( i, 4 + j * 2 );
                return;
            }
            mseat[type_names[j]].prices.push_back( price );
            mseat[type_names[j]].remains.push_back( remain );
        }
    }
//    railway.trains[trainid] = train;
    railway.addTrain( train );
    QMessageBox::information( this, "提示", QString("列车 %1 已成功添加").arg(trainid) );
    accept();
}
