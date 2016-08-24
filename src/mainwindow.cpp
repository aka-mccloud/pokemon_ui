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
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QQuickView *view = new QQuickView();
    QWidget *container = QWidget::createWindowContainer(view, this);
    view->setSource(QUrl("qrc:/main.qml"));
    ui->centralwidget->layout()->addWidget(container);

    QTimer::singleShot(100, this, &MainWindow::showLoginDialog);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showLoginDialog()
{
    LoginDialog *dialog = new LoginDialog(this);
    connect(dialog, &QDialog::accepted, this, &MainWindow::loginSuccessful);
    connect(dialog, &QDialog::rejected, qApp, &QApplication::quit);

    dialog->show();
}

void MainWindow::loginSuccessful()
{
    LoginDialog *dialog = qobject_cast<LoginDialog*>(QObject::sender());
    if (dialog != nullptr)
    {
        _auth = dialog->auth();
        _client = new PGoClient(_auth, this);
        _client->init();
        _client->getInventory();
        _client->getMapObjects();
    }
}
