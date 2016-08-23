#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

#include <QNetworkRequest>
#include <QNetworkReply>
#include <QTimer>
#include <QUrl>

#include "testobject.h"

TestObject::TestObject(QQuickItem *parent)
    : QQuickItem(parent)
    , refreshTimer(this)
{
    // update every 5 seconds
    refreshTimer.setInterval(5000);
    refreshTimer.stop();

    connect(&refreshTimer, &QTimer::timeout, this, &TestObject::refreshData);
    connect(this, &QQuickItem::stateChanged, this, &TestObject::changeState);
}

void TestObject::changeState(const QString &str)
{
    qDebug() << "Change state to:" << str;

    refreshTimer.start();
}

void TestObject::refreshData()
{
    QNetworkReply *reply = networkManager.get(QNetworkRequest(QUrl("http://192.168.0.100:5000/raw_data?pokemons=true&gyms=false")));

    QEventLoop loop;
    connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
    QJsonArray pokemonArray = doc.object().find("pokemons")->toArray();

    foreach (auto pokemonItem, pokemonArray)
    {
//        int pokemonId = pokemonItem.toObject().find("pokemon_id")->toInt();
        QJsonObject pokemonObj = pokemonItem.toObject();
        Pokemon *pokemon = new Pokemon();
        for (auto propertyIt = pokemonObj.begin(); propertyIt != pokemonObj.end(); ++propertyIt)
        {
            pokemon->setProperty(propertyIt.key().toStdString().c_str(), propertyIt.value().toVariant());
        }
//        pokemonItem.toObject().begin();

//        pokemon->setPokemonId(pokemonId);


        emit itemAppeared(pokemon);
    }
}
