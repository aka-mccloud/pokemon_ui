#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "testobject.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<TestObject>("TestModule", 1, 0, "TestObject");
    qmlRegisterType<Pokemon>("TestModule", 1, 0, "Pokemon");
    qmlRegisterType<PokemonData>("TestModule", 1, 0, "PokemonData");
    qmlRegisterType<EncounterData>("TestModule", 1, 0, "EncounterData");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
