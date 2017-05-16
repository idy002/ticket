#ifndef MANAGERDIALOG_H
#define MANAGERDIALOG_H

#include <QDialog>
#include <QTimer>

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

    void on_myTiccketButton_clicked();

    void on_buyTicketButton_clicked();

    void on_modifyInfoButton_clicked();

    void on_showPushButton_2_clicked();

    void on_logPushButton_clicked();

    void update_time();

private:
    Ui::ManagerDialog *ui;
    QTimer *timer;

};

#endif // MANAGERDIALOG_H
