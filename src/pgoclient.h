#ifndef PGOCLIENT_H
#define PGOCLIENT_H

#include <QElapsedTimer>
#include <QObject>
#include <QNetworkAccessManager>
#include <QUrl>

#include "proto/POGOProtos.Networking.Envelopes.pb.h"
#include "proto/POGOProtos.Networking.Responses.pb.h"

#include "iauth.h"

class PGoClient : public QObject
{
    Q_OBJECT
public:
    explicit PGoClient(IAuth *auth, QObject *parent = 0);

signals:

public slots:
    void init();

    POGOProtos::Networking::Responses::GetInventoryResponse *getInventory();
    POGOProtos::Networking::Responses::GetMapObjectsResponse *getMapObjects();

private:
    template<typename ResponseType>
    ResponseType * performRequest(POGOProtos::Networking::Requests::Request &request);

    POGOProtos::Networking::Envelopes::Unknown6 * generateSignature(POGOProtos::Networking::Requests::Request &request);
    std::string encrypt(const std::string &data);

private:
    QNetworkAccessManager _net;
    IAuth *_auth;
    QElapsedTimer _timer;

    QUrl _apiUrl;
    POGOProtos::Networking::Envelopes::AuthTicket _authTicket;

    int64_t _requestId;
    double _latitude;
    double _longitude;
    double _altitude;

};

#endif // PGOCLIENT_H
