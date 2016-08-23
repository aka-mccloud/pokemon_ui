#ifndef TESTOBJECT_H
#define TESTOBJECT_H

#include <QQuickItem>
#include <QNetworkAccessManager>
#include <QTimer>

#include "pokemon.h"

class TestObject : public QQuickItem
{
    Q_OBJECT
public:
    TestObject(QQuickItem *parent = 0);

signals:
    void itemAppeared(Pokemon *pokemon);

private slots:
    void changeState(const QString &str);
    void refreshData();

private:
    QNetworkAccessManager networkManager;
    QTimer refreshTimer;

};

#endif // TESTOBJECT_H
