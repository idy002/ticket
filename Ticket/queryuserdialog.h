#ifndef QUERYUSERDIALOG_H
#define QUERYUSERDIALOG_H

#include <QDialog>
#include "railway.hpp"

namespace Ui {
class QueryUserDialog;
}

class QueryUserDialog : public QDialog
{
    Q_OBJECT

public:
    explicit QueryUserDialog(QWidget *parent = 0);
    ~QueryUserDialog();

private slots:
    void on_lookPushButton_clicked();

    void on_modifyLineEdit_clicked();

    void on_showPushButton_clicked();

private:
    void update_userListWidget();
    void update_userInfo();

private:
    Ui::QueryUserDialog *ui;

    tic::vector<QString> userids;
    QString curUserid;
};

#endif // QUERYUSERDIALOG_H
