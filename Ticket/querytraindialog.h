#ifndef QUERYTRAINDIALOG_H
#define QUERYTRAINDIALOG_H

#include <QDialog>
#include <QDate>
#include <QListWidget>
#include <QListWidgetItem>
#include "railway.hpp"

namespace Ui {
class QueryTrainDialog;
}

class QueryTrainDialog : public QDialog
{
    Q_OBJECT

public:
    explicit QueryTrainDialog(QWidget *parent = 0);
    ~QueryTrainDialog();


private slots:
    void on_trainListWidget_itemDoubleClicked(QListWidgetItem *item);

    void on_startPushButton_clicked();

    void on_dateListWidget_itemClicked(QListWidgetItem *item);

    void on_dateListWidget_itemDoubleClicked(QListWidgetItem *item);

    void on_delPushButton_clicked();

    void on_stopPushButton_clicked();

    void on_restroePushButton_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    void update_trainListWidget();
    void update_dateListWidget();
    void update_tableWidget();
    void update_buttons();

private:
    Ui::QueryTrainDialog *ui;

    tic::vector<QString> trainids;	//	total
    tic::vector<Date> dates;	//	showed in date listWidget
    QString curTrainid;
};

#endif // QUERYTRAINDIALOG_H
