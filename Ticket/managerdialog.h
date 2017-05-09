#ifndef MANAGERDIALOG_H
#define MANAGERDIALOG_H

#include <QDialog>

namespace Ui {
class ManagerDialog;
}

class ManagerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ManagerDialog(QWidget *parent = 0);
    ~ManagerDialog();

private slots:
    void on_addPushButton_clicked();

    void on_delPushButton_clicked();

    void on_showPushButton_clicked();

private:
    Ui::ManagerDialog *ui;
};

#endif // MANAGERDIALOG_H
