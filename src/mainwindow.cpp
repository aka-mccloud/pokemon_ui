#include <QApplication>
#include <QQuickView>
#include <QTimer>

#include "authgoogle.h"
#include "pgoclient.h"
#include "logindialog.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    auth(new AuthPTC)
{
    ui->setupUi(this);

    QQuickView *view = new QQuickView();
    QWidget *container = QWidget::createWindowContainer(view, this);
    view->setSource(QUrl("qrc:/main.qml"));
    ui->centralwidget->layout()->addWidget(container);

//    AuthGoogle auth;
//    auth.login("test.mail.zx@gmail.com", "lM0Qxec3");
//    QString token = auth.getToken(true);

//    qWarning() << token;

//    PGoClient client;
//    client.auth("google", token);

    QTimer::singleShot(100, this, &MainWindow::showLoginDialog);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showLoginDialog()
{
    LoginDialog *dialog = new LoginDialog(auth, this);
    connect(dialog, &QDialog::accepted, this, &MainWindow::show);
    connect(dialog, &QDialog::rejected, qApp, &QApplication::quit);

    dialog->show();
}
