#ifndef QUERYTRAINDIALOG_H
#define QUERYTRAINDIALOG_H

#include <QDialog>
#include <QDate>

namespace Ui {
class QueryTrainDialog;
}

class QueryTrainDialog : public QDialog
{
    Q_OBJECT

public:
    explicit QueryTrainDialog(QWidget *parent = 0);
    ~QueryTrainDialog();


private:
    Ui::QueryTrainDialog *ui;

};

#endif // QUERYTRAINDIALOG_H
