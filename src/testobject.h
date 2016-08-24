#ifndef TESTOBJECT_H
#define TESTOBJECT_H

#include <QQuickItem>
#include <QTimer>

#include "authfactory.h"
#include "pokemon.h"
#include "pgoclient.h"

class TestObject : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(double latitude READ latitude WRITE setLatitude NOTIFY latitudeChanged)
    Q_PROPERTY(double longitude READ longitude WRITE setLongitude NOTIFY longitudeChanged)

public:
    TestObject(QQuickItem *parent = 0);

    double latitude() const;
    void setLatitude(double latitude);

    double longitude() const;
    void setLongitude(double longitude);

public:
    Q_INVOKABLE void login(const QString &provider, const QString &login, const QString &password);


signals:
    void latitudeChanged(double);
    void longitudeChanged(double);
    void ready();
    void itemAppeared(Pokemon *pokemon);

private slots:
    void changeState(const QString &str);
    void refreshData();

private:
    std::list<Pokemon*> _pokemons;
    QTimer _refreshTimer;
    PGoClient *_client;

};

#endif // TESTOBJECT_H
