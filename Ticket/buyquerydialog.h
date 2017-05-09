#ifndef BUYQUERYDIALOG_H
#define BUYQUERYDIALOG_H

#include <QDialog>

namespace Ui {
class BuyQueryDialog;
}

class BuyQueryDialog : public QDialog
{
    Q_OBJECT

public:
    explicit BuyQueryDialog(QWidget *parent = 0);
    ~BuyQueryDialog();

private slots:
    void on_pushButton_clicked();

private:
    Ui::BuyQueryDialog *ui;
};

#endif // BUYQUERYDIALOG_H
