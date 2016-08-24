#include "authfactory.h"
#include "logindialog.h"
#include "ui_logindialog.h"

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

IAuth *LoginDialog::auth()
{
    return _auth;
}

void LoginDialog::on_loginButton_clicked()
{
    ui->loginButton->setEnabled(false);

    _auth = AuthFactory::createAuthProvider(ui->googleRadioButton->isChecked() ? IAuth::Google : IAuth::PTC);
    _auth->login(ui->usernameEdit->text(), ui->passwordEdit->text());

    QDialog::accept();
}
