#ifndef AUTHGOOGLE_H
#define AUTHGOOGLE_H

#include <QObject>
#include <QMap>
#include <QNetworkAccessManager>
#include <QUrlQuery>

class AuthGoogle : public QObject
{
    Q_OBJECT
public:
    explicit AuthGoogle(QObject *parent = 0);

    void login(const QString &email, const QString &password);
    QString getToken(bool force = false);

signals:
    void loginSuccessful();
    void loginFailed();

public slots:

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
