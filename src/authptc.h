#ifndef AUTHPTC_H
#define AUTHPTC_H

#include <QObject>
#include <QMap>
#include <QNetworkAccessManager>
#include <QUrlQuery>

#include "iauth.h"

class AuthPTC : public QObject, public IAuth
{
    Q_OBJECT
    Q_INTERFACES(IAuth)
public:
    explicit AuthPTC(QObject *parent = 0);

    // IAuth interface
public:
    virtual void login(const QString &username, const QString &password) override;
    virtual QString getToken(bool force = false) override;
    virtual QString provider() override;

private:
    QNetworkAccessManager net;
    QString username;
    QString password;
    QString ticket;
    QString token;
    int expires;

};

#endif // AUTHPTC_H
