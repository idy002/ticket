#ifndef REFUNDDIALOG_H
#define REFUNDDIALOG_H

#include <QDialog>

namespace Ui {
class RefundDialog;
}

class RefundDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RefundDialog(QWidget *parent = 0);
    ~RefundDialog();

private:
    Ui::RefundDialog *ui;
};

#endif // REFUNDDIALOG_H
