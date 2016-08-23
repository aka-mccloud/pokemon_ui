#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "authptc.h"

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

private:
    Ui::MainWindow *ui;
    AuthPTC *auth;

};

#endif // MAINWINDOW_H
