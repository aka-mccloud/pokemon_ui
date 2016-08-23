#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>

#include "authptc.h"

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(AuthPTC* auth, QWidget *parent = 0);
    ~LoginDialog();

private slots:
    void on_loginButton_clicked();

private:
    Ui::LoginDialog *ui;
    AuthPTC *auth;

};

#endif // LOGINDIALOG_H
