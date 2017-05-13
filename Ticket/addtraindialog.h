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
    explicit AddTrainDialog(QWidget *parent, QString trainid, int stations_count, int types_count );
    ~AddTrainDialog();

private slots:
    void on_finishPushButton_clicked();

private:
    QString trainid;
    int stations_count;
    int types_count;

private:
    Ui::AddTrainDialog *ui;
};

#endif // ADDTRAINDIALOG_H
