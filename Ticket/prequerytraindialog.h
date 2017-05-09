#ifndef PREQUERYTRAINDIALOG_H
#define PREQUERYTRAINDIALOG_H

#include <QDialog>

namespace Ui {
class PreQueryTrainDialog;
}

class PreQueryTrainDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PreQueryTrainDialog(QWidget *parent = 0);
    ~PreQueryTrainDialog();

private slots:
    void on_pushButton_clicked();

private:
    Ui::PreQueryTrainDialog *ui;
};

#endif // PREQUERYTRAINDIALOG_H
