#include "queryuserdialog.h"
#include "ui_queryuserdialog.h"
#include "railway.hpp"
#include <QMessageBox>

QueryUserDialog::QueryUserDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QueryUserDialog)
{
    ui->setupUi(this);

    for( auto it = railway.users.begin(); it != railway.users.end(); ++it )
        userids.push_back( it->first );
    curUserid = "";
    ui->modifyLineEdit->setEnabled(false);

    Qt::WindowFlags flags = Qt::Dialog;
    flags |= Qt::WindowMaximizeButtonHint
           | Qt::WindowMinimizeButtonHint
           | Qt::WindowCloseButtonHint;
    setWindowFlags( flags );

}

void QueryUserDialog::update_userListWidget() {
    ui->userListWidget->clear();
    QString userid = ui->useridLineEdit->text();
    int total = 0, showed = 0;
    for( int t = 0; t < (int)userids.size(); t++ ) {
        if( userids[t].count(userid) ) {
            total++;
            if( showed < 100 ) {
                showed++;
                ui->userListWidget->addItem( new QListWidgetItem( userids[t] ) );
            }
        }
    }
    QMessageBox::information( this, "查询结果", QString("共找到 %1 位用户的用户名包含给串，显示其中 %2 位").arg(total).arg(showed) );
}

void QueryUserDialog::update_userInfo() {
    tic::User &user = railway.users[curUserid];
    QString pwd = user.password;
    QString name = user.name;
    ui->nameLineEdit->setText(name);
    ui->pwdLineEdit->setText(pwd);

    vector<pair<Ticket,int>> bought = railway.queryUserBoughtTicket( curUserid );
    vector<pair<Ticket,int>> refunded = railway.queryUserRefundedTicket( curUserid );
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
            row[0] = tk.date.toString(DefaultDateFormat);
            row[1] = tk.trainid;
            row[2] = tk.from;
            row[3] = tk.to;
            row[4] = tk.leave.toString(DefaultDateTimeFormat);
            row[5] = tk.arrive.toString(DefaultDateTimeFormat);
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
}

QueryUserDialog::~QueryUserDialog()
{
    delete ui;
}

void QueryUserDialog::on_lookPushButton_clicked()
{
    int row = ui->userListWidget->currentRow();
    if( row == -1 ) {
        QMessageBox::warning( this, "出错了", "请选择用户");
        return;
    } else {
        curUserid = ui->userListWidget->currentItem()->text();
        ui->modifyLineEdit->setEnabled(true);
        update_userInfo();
    }
}

void QueryUserDialog::on_modifyLineEdit_clicked()
{
    QString newname = ui->nameLineEdit->text();
    QString newpwd = ui->pwdLineEdit->text();
    if( newname.isEmpty() ) {
        QMessageBox::warning( this, "出错了", "姓名不能为空，重请新输入" );
        ui->nameLineEdit->setFocus();
        return;
    }
    if( newpwd.length() < 6 ) {
        QMessageBox::warning( this, "出错了", "密码长度过，短密码长度至少为6个字符，请重新输入" );
        ui->pwdLineEdit->setFocus();
        return;
    }
    if( railway.users.count(curUserid) == 0 ) {
        QMessageBox::warning( this, "出错了", "发生了不可能的事" );
        return;
    }
    tic::User &user = railway.users[curUserid];
    user.name = newname;
    user.password = newpwd;
    QMessageBox::information( this, "提示", "修改成功" );
}

void QueryUserDialog::on_showPushButton_clicked()
{
    update_userListWidget();
}
