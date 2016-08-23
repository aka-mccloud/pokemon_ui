#include <functional>

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

#include <QEventLoop>

#include <QNetworkReply>
#include <QNetworkRequest>

#include <QUrlQuery>

#include "authptc.h"

const char *PTC_LOGIN_URL = "https://sso.pokemon.com/sso/login?service=https%3A%2F%2Fsso.pokemon.com%2Fsso%2Foauth2.0%2FcallbackAuthorize";
const char *PTC_LOGIN_OAUTH = "https://sso.pokemon.com/sso/oauth2.0/accessToken";
const char *PTC_LOGIN_CLIENT_SECRET = "w8ScCUXJQc6kXKw8FiOhd8Fixzht18Dq3PEVkUCP5ZPxtgyWsbTvWHFLm2wNY0JR";

AuthPTC::AuthPTC(QObject *parent) : QObject(parent)
{

}

void AuthPTC::login(const QString &username, const QString &password)
{
    this->username = username;
    this->password = password;

    QNetworkRequest request;
    request.setUrl(QUrl(PTC_LOGIN_URL));
    request.setHeader(QNetworkRequest::UserAgentHeader, "niantic");

    QNetworkReply *reply = net.get(request);

    connect(reply, &QNetworkReply::finished, std::bind(&AuthPTC::phaseOne, this, reply));
}

QString AuthPTC::getToken(bool force)
{
    if (!token.isEmpty() && !force)
        return token;

    // get access token
    QUrlQuery params;
    params.addQueryItem("client_id", "mobile-app_pokemon-go");
    params.addQueryItem("redirect_uri", "https://www.nianticlabs.com/pokemongo/error");
    params.addQueryItem("client_secret", PTC_LOGIN_CLIENT_SECRET);
    params.addQueryItem("grant_type", "refresh_token");
    params.addQueryItem("code", ticket);

    QNetworkRequest request;
    request.setUrl(QUrl(PTC_LOGIN_OAUTH));
    request.setHeader(QNetworkRequest::UserAgentHeader, "niantic");
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    QNetworkReply *reply = net.post(request, params.toString(QUrl::FullyEncoded).toUtf8());

    QEventLoop loop;
    connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    QByteArray data = reply->readAll();
    qInfo() << data;

    QUrlQuery query(data);
    if (query.hasQueryItem("access_token"))
    {
        token = query.queryItemValue("access_token");
        expires = query.queryItemValue("expires").toInt();
    }

    return token;
}

void AuthPTC::phaseOne(QNetworkReply *reply)
{
    QByteArray data = reply->readAll();

    QJsonDocument doc = QJsonDocument::fromJson(data);
    QString lt = doc.object().find("lt")->toString();
    QString execution = doc.object().find("execution")->toString();

    QUrlQuery params;
    params.addQueryItem("lt", lt);
    params.addQueryItem("execution", execution);
    params.addQueryItem("_eventId", "submit");
    params.addQueryItem("username", username);
    params.addQueryItem("password", password);

    QNetworkRequest request;
    request.setUrl(QUrl(PTC_LOGIN_URL));
    request.setHeader(QNetworkRequest::UserAgentHeader, "niantic");
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    reply->deleteLater();
    reply = net.post(request, params.toString(QUrl::FullyEncoded).toUtf8());

    connect(reply, &QNetworkReply::finished, std::bind(&AuthPTC::phaseTwo, this, reply));
}

void AuthPTC::phaseTwo(QNetworkReply *reply)
{
    QString location = reply->header(QNetworkRequest::LocationHeader).toString();

    if (location.isEmpty())
    {
        QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
        QJsonArray errors = doc.object().find("errors")->toArray();
        QJsonArray::const_iterator it = errors.begin();
        for (; it != errors.end(); ++it)
            qWarning() << it->toString();

        emit loginFailed();

        return;
    }

    QUrlQuery query(QUrl(location).query());
    ticket = query.queryItemValue("ticket");

    emit loginSuccessful();
}
