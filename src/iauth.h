#ifndef IAUTH_H
#define IAUTH_H

#include <QObject>
#include <QString>

class IAuth
{

public:
    enum AuthProviders
    {
        Google,
        PTC
    };

public:
    virtual void login(const QString &username, const QString &password) = 0;
    virtual QString getToken(bool force = false) = 0;
    virtual QString provider() = 0;

};

Q_DECLARE_INTERFACE(IAuth, "pokemon_ui.iauth/1.0")

#endif // IAUTH_H
