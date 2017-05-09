#ifndef DELTRAINDIALOG_H
#define DELTRAINDIALOG_H

#include <QDialog>

namespace Ui {
class DelTrainDialog;
}

class DelTrainDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DelTrainDialog(QWidget *parent = 0);
    ~DelTrainDialog();

private:
    Ui::DelTrainDialog *ui;
};

#endif // DELTRAINDIALOG_H
