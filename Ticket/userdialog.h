#ifndef USERDIALOG_H
#define USERDIALOG_H

#include <QDialog>

namespace Ui {
class UserDialog;
}

class UserDialog : public QDialog
{
    Q_OBJECT

public:
    explicit UserDialog(QWidget *parent = 0);
    ~UserDialog();

private slots:
    void on_myTiccketButton_clicked();

    void on_buyTicketButton_clicked();

    void on_modifyInfoButton_clicked();

private:
    Ui::UserDialog *ui;
};

#endif // USERDIALOG_H
