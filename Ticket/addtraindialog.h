#ifndef ADDTRAINDIALOG_H
#define ADDTRAINDIALOG_H

#include <QDialog>

namespace Ui {
class AddTrainDialog;
}

class AddTrainDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddTrainDialog(QWidget *parent = 0);
    ~AddTrainDialog();

private:
    Ui::AddTrainDialog *ui;
};

#endif // ADDTRAINDIALOG_H
