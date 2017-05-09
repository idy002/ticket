#ifndef MYTICKETDIALOG_H
#define MYTICKETDIALOG_H

#include <QDialog>

namespace Ui {
class MyTicketDialog;
}

class MyTicketDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MyTicketDialog(QWidget *parent = 0);
    ~MyTicketDialog();

private:
    Ui::MyTicketDialog *ui;
};

#endif // MYTICKETDIALOG_H
