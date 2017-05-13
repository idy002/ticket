#ifndef MYTICKETDIALOG_H
#define MYTICKETDIALOG_H

#include <QDialog>
#include "railway.hpp"

namespace Ui {
class MyTicketDialog;
}

class MyTicketDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MyTicketDialog(QWidget *parent = 0);
    ~MyTicketDialog();

private slots:
    void on_refundPushButton_clicked();
    void on_tableWidget_itemSelectionChanged();

private:
    vector<pair<Ticket,int>> bought, refunded;
    void refresh();

private:
    Ui::MyTicketDialog *ui;
};

#endif // MYTICKETDIALOG_H
