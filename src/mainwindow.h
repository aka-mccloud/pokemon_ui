#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "iauth.h"
#include "pgoclient.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void showLoginDialog();
    void loginSuccessful();

private:
    Ui::MainWindow *ui;

    IAuth *_auth;
    PGoClient *_client;

};

#endif // MAINWINDOW_H
