#include "myticketdialog.h"
#include "ui_myticketdialog.h"
#include "railway.hpp"

MyTicketDialog::MyTicketDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MyTicketDialog)
{
    ui->setupUi(this);

    refresh();
    on_tableWidget_itemSelectionChanged();

    Qt::WindowFlags flags = Qt::Dialog;
    flags |= Qt::WindowMaximizeButtonHint
           | Qt::WindowMinimizeButtonHint
           | Qt::WindowCloseButtonHint;
    setWindowFlags( flags );
}

MyTicketDialog::~MyTicketDialog()
{
    delete ui;
}

void MyTicketDialog::refresh() {
    int oldx = ui->tableWidget->currentRow();
    int oldy = ui->tableWidget->currentColumn();

    bought = railway.queryUserBoughtTicket( railway.curUserid );
    refunded = railway.queryUserRefundedTicket( railway.curUserid );
    QStringList header;
    header << "日期" << "车站编号" << "起始站" << "终点站" << "发车时间" << "到达时间" << "里程" << "座位类型" << "票价" << "数量" << "状态";
    ui->tableWidget->setRowCount(bought.size() + refunded.size());
    ui->tableWidget->setColumnCount(11);
    ui->tableWidget->setHorizontalHeaderLabels( header );
    ui->tableWidget->setEditTriggers( QAbstractItemView::NoEditTriggers );
    ui->tableWidget->setSelectionBehavior( QAbstractItemView::SelectRows );
    ui->tableWidget->setSelectionMode( QAbstractItemView::SingleSelection );
    ui->tableWidget->verticalHeader()->setSectionResizeMode( QHeaderView::Fixed );
    for( int c = 0; c < 2; c++ ) {
        vector<pair<Ticket,int>> &vec = ( c == 0 ? bought : refunded );
        for( int t = 0; t < (int)vec.size(); t++ ) {
            QString row[11];
            tic::Ticket & tk = vec[t].first;
            row[0] = tk.date.toString(tic::DefaultDateFormat);
            row[1] = tk.trainid;
            row[2] = tk.from;
            row[3] = tk.to;
            row[4] = tk.leave.toString(tic::DefaultDateFormat);
            row[5] = tk.arrive.toString(tic::DefaultDateFormat);
            row[6] = QString::number(tk.dist);
            row[7] = tk.type;
            row[8] = QString::number(tk.price,'f',1);
            row[9] = QString::number(vec[t].second);
            row[10] = (c == 0 ? "已购票" : "已退票");
            for( int tt = 0; tt < 11; tt++ ) {
                QTableWidgetItem *item = new QTableWidgetItem(row[tt]);
                item->setTextAlignment( Qt::AlignHCenter | Qt::AlignVCenter );
                ui->tableWidget->setItem( (c == 1 ? bought.size() : 0) + t, tt, item );
            }
        }
    }
    ui->tableWidget->setCurrentCell( oldx, oldy );
}

void MyTicketDialog::on_refundPushButton_clicked()
{
    int row = ui->tableWidget->currentRow();
    railway.refundTicket( railway.curUserid, bought[row].first, 1);
    refresh();
    qDebug() << "refund button clicked";
}

void MyTicketDialog::on_tableWidget_itemSelectionChanged()
{
    int row = ui->tableWidget->currentRow();
    if( row < (int)bought.size() ) {
        ui->refundPushButton->setEnabled( true );
    } else {
        ui->refundPushButton->setEnabled( false );
    }
}
