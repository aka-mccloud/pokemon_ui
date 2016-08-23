#ifndef AUTHPTC_H
#define AUTHPTC_H

#include <QObject>
#include <QNetworkAccessManager>

class AuthPTC : public QObject
{
    Q_OBJECT
public:
    explicit AuthPTC(QObject *parent = 0);

    void login(const QString &username, const QString &password);
    QString getToken(bool force = false);

signals:
    void loginSuccessful();
    void loginFailed();

public slots:

private slots:
    void phaseOne(QNetworkReply *reply);
    void phaseTwo(QNetworkReply *reply);

private:
    QNetworkAccessManager net;
    QString username;
    QString password;
    QString ticket;
    QString token;
    int expires;

};

#endif // AUTHPTC_H
