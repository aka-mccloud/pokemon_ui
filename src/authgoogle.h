#ifndef AUTHGOOGLE_H
#define AUTHGOOGLE_H

#include <QObject>
#include <QMap>
#include <QNetworkAccessManager>
#include <QUrlQuery>

#include "iauth.h"

class AuthGoogle : public QObject, public IAuth
{
    Q_OBJECT
    Q_INTERFACES(IAuth)
public:
    explicit AuthGoogle(QObject *parent = 0);

    // IAuth interface
public:
    virtual void login(const QString &email, const QString &password) override;
    virtual QString getToken(bool force = false) override;
    virtual QString provider() override;

private:
    QMap<QString, QString> performRequest(const QUrlQuery &query);

private:
    QNetworkAccessManager net;
    QString email;
    QString password;
    QString masterToken;
    QString token;

};

#endif // AUTHGOOGLE_H
