#ifndef ADDTRAINQUERYDIALOG_H
#define ADDTRAINQUERYDIALOG_H

#include <QDialog>

namespace Ui {
class AddTrainQueryDialog;
}

class AddTrainQueryDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddTrainQueryDialog(QWidget *parent = 0);
    ~AddTrainQueryDialog();

private slots:
    void on_finishPushButton_clicked();

private:
    Ui::AddTrainQueryDialog *ui;
};

#endif // ADDTRAINQUERYDIALOG_H
