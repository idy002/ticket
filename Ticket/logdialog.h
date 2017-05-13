#ifndef LOGDIALOG_H
#define LOGDIALOG_H

#include <QDialog>
#include "railway.hpp"

namespace Ui {
class LogDialog;
}

class LogDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LogDialog(QWidget *parent = 0);
    ~LogDialog();

private slots:
    void on_queryPushButton_clicked();

private:
    Ui::LogDialog *ui;

    tic::vector<tic::Log> logs;
};

#endif // LOGDIALOG_H
