#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = 0);
    ~LoginDialog();

private slots:
    void on_loginPushButton_clicked();

private:
    Ui::LoginDialog *ui;
private:
    bool checkIdPwd( QString id, QString pwd );
};

#endif // LOGINDIALOG_H
