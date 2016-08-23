#ifndef PGOCLIENT_H
#define PGOCLIENT_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QUrl>

#include "proto/POGOProtos.Networking.Envelopes.pb.h"

class PGoClient : public QObject
{
    Q_OBJECT
public:
    explicit PGoClient(QObject *parent = 0);

signals:

public slots:
    void auth(const QString &provider, const QString &token);

private:
    QNetworkAccessManager _net;

    QUrl _apiUrl;
    POGOProtos::Networking::Envelopes::AuthTicket _authTicket;

    int64_t _requestId;
    double _latitude;
    double _longitude;
    double _altitude;

};

#endif // PGOCLIENT_H
