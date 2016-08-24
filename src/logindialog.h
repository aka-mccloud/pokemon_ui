#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>

#include "iauth.h"

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = 0);
    ~LoginDialog();

    IAuth *auth();

private slots:
    void on_loginButton_clicked();

private:
    Ui::LoginDialog *ui;
    IAuth *_auth;

};

#endif // LOGINDIALOG_H
