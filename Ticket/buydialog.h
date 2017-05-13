#ifndef BUYDIALOG_H
#define BUYDIALOG_H

#include "lib/lib.hpp"
#include "railway.hpp"
#include <QDialog>
#include <QDate>
#include <QTableWidget>

namespace Ui {
class BuyDialog;
}

class BuyDialog : public QDialog
{
    Q_OBJECT

public:
    explicit BuyDialog(QWidget *parent = 0);
    explicit BuyDialog(QWidget *parent, QDate date, QString from, QString to);
    ~BuyDialog();

private slots:
    void on_tableWidget_itemSelectionChanged();

    void on_buyPushButton_clicked();

private:
    void refresh();

private:
    Ui::BuyDialog *ui;

    QDate date;
    QString from, to;

    vector<pair<Ticket,int>> vec;
};

#endif // BUYDIALOG_H
