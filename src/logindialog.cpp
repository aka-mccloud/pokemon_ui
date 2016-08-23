#include "logindialog.h"
#include "ui_logindialog.h"

LoginDialog::LoginDialog(AuthPTC *auth, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog),
    auth(auth)
{
    ui->setupUi(this);

    connect(auth, &AuthPTC::loginSuccessful, this, &QDialog::accept);
//    connect(auth, &AuthPTC::loginFailed, this, &QDialog::reject);
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::on_loginButton_clicked()
{
    ui->loginButton->setEnabled(false);
    auth->login(ui->usernameEdit->text(), ui->passwordEdit->text());
}
