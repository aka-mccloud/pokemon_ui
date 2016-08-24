#include <QCryptographicHash>
#include <QEventLoop>

#include <QNetworkReply>
#include <QNetworkRequest>

#include <QUrlQuery>

#include <openssl/rsa.h>
#include <openssl/engine.h>
#include <openssl/pem.h>

#include "authgoogle.h"

const char *b64_key_7_3_29 = "AAAAgMom/1a/v0lblO2Ubrt60J2gcuXSljGFQXgcyZWveWLEwo6prwgi3"
                             "iJIZdodyhKZQrNWp5nKJ3srRXcUW+F1BD3baEVGcmEgqaLZUNBjm057pK"
                             "RI16kB0YppeGx5qIQ5QjKzsR8ETQbKLNWgRY0QRNVz34kMJR3P/LgHax/"
                             "6rmf5AAAAAwEAAQ==";

const char *auth_url = "https://android.clients.google.com/auth";
const char *useragent = "gpsoauth/0.2.0";

const char *GOOGLE_LOGIN_ANDROID_ID = "9774d56d682e549c";
const char *GOOGLE_LOGIN_SERVICE= "audience:server:client_id:848232511240-7so421jotr2609rmqakceuu1luuq0ptb.apps.googleusercontent.com";
const char *GOOGLE_LOGIN_APP = "com.nianticlabs.pokemongo";
const char *GOOGLE_LOGIN_CLIENT_SIG = "321187995bc7cdc2b5fc91b11a96e2baa8602c62";


QString google_signature(const QString &email, const QString &password, const char *b64_key);

AuthGoogle::AuthGoogle(QObject *parent) : QObject(parent)
{

}

void AuthGoogle::login(const QString &email, const QString &password)
{
    this->email = email;
    this->password = password;

    QUrlQuery params;
    params.addQueryItem("accountType",      "HOSTED_OR_GOOGLE");
    params.addQueryItem("Email",            email);
    params.addQueryItem("has_permission",   "1");
    params.addQueryItem("add_account",      "1");
    params.addQueryItem("EncryptedPasswd",  google_signature(email, password, b64_key_7_3_29));
    params.addQueryItem("service",          "ac2dm");
    params.addQueryItem("source",           "android");
    params.addQueryItem("androidId",        "9774d56d682e549c");
    params.addQueryItem("device_country",   "us");
    params.addQueryItem("operatorCountry",  "us");
    params.addQueryItem("lang",             "en");
    params.addQueryItem("sdk_version",      "17");

    QMap<QString, QString> response = performRequest(params);
    masterToken = response["token"];
//    token = response["auth"];
}

QString AuthGoogle::getToken(bool force)
{
    if (!token.isEmpty() && !force)
        return token;

    // get access token

    QUrlQuery params;
    params.addQueryItem("accountType",      "HOSTED_OR_GOOGLE");
    params.addQueryItem("Email",            "");
    params.addQueryItem("has_permission",   "1");
    params.addQueryItem("EncryptedPasswd",  masterToken);
    params.addQueryItem("service",          GOOGLE_LOGIN_SERVICE);
    params.addQueryItem("source",           "android");
    params.addQueryItem("androidId",        GOOGLE_LOGIN_ANDROID_ID);
    params.addQueryItem("app",              GOOGLE_LOGIN_APP);
    params.addQueryItem("client_sig",       GOOGLE_LOGIN_CLIENT_SIG);
    params.addQueryItem("device_country",   "us");
    params.addQueryItem("operatorCountry",  "us");
    params.addQueryItem("lang",             "en");
    params.addQueryItem("sdk_version",      "17");

    QMap<QString, QString> response = performRequest(params);
    token = response["auth"];

    return token;
}

QString AuthGoogle::provider()
{
    return "google";
}

QMap<QString, QString> AuthGoogle::performRequest(const QUrlQuery &query)
{
    QMap<QString, QString> response;
    QNetworkRequest request;
    request.setUrl(QUrl(auth_url));
    request.setHeader(QNetworkRequest::UserAgentHeader, useragent);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    QNetworkReply *reply = net.post(request, query.toString(QUrl::FullyEncoded).toUtf8());

    QEventLoop loop;
    connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    QStringList lines = QString(reply->readAll()).split('\n', QString::SkipEmptyParts);
    foreach (QString line, lines) {
        QStringList parts = line.split('=');
        response.insert(parts[0].toLower(), parts[1]);
    }

    return response;
}

QString google_signature(const QString &email, const QString &password, const char *b64_key)
{
    QByteArray data = email.toUtf8() + '\0' + password.toUtf8();
    QByteArray binaryKey = QByteArray::fromBase64(b64_key);
    QCryptographicHash hash(QCryptographicHash::Sha1);
    hash.addData(binaryKey);

    QByteArray sig(1024, '\0');
    sig.replace(1, 4, hash.result());

    RSA *key = RSA_new();
    key->n = BN_bin2bn((const uchar *)binaryKey.data() + 4, 128, NULL);
    key->e = BN_bin2bn((const uchar *)binaryKey.data() + 136, 3, NULL);
    int len = RSA_public_encrypt(data.size(), (const uchar *)data.data(), (uchar *)sig.data() + 5, key, RSA_PKCS1_OAEP_PADDING);
    RSA_free(key);

    sig.resize(len + 5);
    return QString(sig.toBase64(QByteArray::Base64UrlEncoding));
}
