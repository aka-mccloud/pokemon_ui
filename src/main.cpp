#include <QApplication>
#include <QQmlApplicationEngine>

#include "testobject.h"
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    qmlRegisterType<TestObject>("TestModule", 1, 0, "TestObject");
    qmlRegisterType<Pokemon>("TestModule", 1, 0, "Pokemon");

    MainWindow window;
    window.show();

    return app.exec();
}
