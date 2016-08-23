#include <QByteArray>
#include <QDateTime>
#include <QEventLoop>
#include <QNetworkRequest>
#include <QNetworkReply>

#include <QFile>

#include "proto/POGOProtos.Networking.Envelopes.pb.h"
#include "proto/POGOProtos.Networking.Requests.pb.h"
#include "proto/POGOProtos.Networking.Requests.Messages.pb.h"
#include "proto/POGOProtos.Networking.Responses.pb.h"

#include "pgoclient.h"

using namespace POGOProtos;

PGoClient::PGoClient(QObject *parent) : QObject(parent), _apiUrl("https://pgorelease.nianticlabs.com/plfe/rpc")
{
    _requestId = 1;
    _latitude = 50.418709;
    _longitude = 30.5236256;
    _altitude = 8.0;


}

void PGoClient::auth(const QString &provider, const QString &token)
{
    Networking::Requests::Messages::GetPlayerMessage getPlayerMessage;
    Networking::Requests::Messages::GetHatchedEggsMessage getHatchedEggsMessage;
    Networking::Requests::Messages::GetInventoryMessage getInventoryMessage;
    getInventoryMessage.set_last_timestamp_ms(QDateTime::currentDateTimeUtc().toTime_t());
    Networking::Requests::Messages::CheckAwardedBadgesMessage checkAwardedBadgesMessage;
    Networking::Requests::Messages::DownloadSettingsMessage downloadSettingsMessage;
    downloadSettingsMessage.set_hash("05daf51635c82611d1aac95c0b051d3ec088a930");

    Networking::Envelopes::RequestEnvelope requestEnvelope;
    requestEnvelope.set_status_code(2);
    requestEnvelope.set_request_id(_requestId++);
    requestEnvelope.set_latitude(_latitude);
    requestEnvelope.set_longitude(_longitude);
    requestEnvelope.set_altitude(_altitude);
    requestEnvelope.mutable_auth_info()->set_provider(provider.toStdString());
    requestEnvelope.mutable_auth_info()->mutable_token()->set_contents(token.toStdString());
    requestEnvelope.mutable_auth_info()->mutable_token()->set_unknown2(59);
    requestEnvelope.set_unknown12(989);

    Networking::Requests::Request *req = requestEnvelope.mutable_requests()->Add();
    req->set_request_type(Networking::Requests::GET_PLAYER);
    req->set_request_message(getPlayerMessage.SerializeAsString());

    req = requestEnvelope.mutable_requests()->Add();
    req->set_request_type(Networking::Requests::GET_HATCHED_EGGS);
    req->set_request_message(getHatchedEggsMessage.SerializeAsString());

    req = requestEnvelope.mutable_requests()->Add();
    req->set_request_type(Networking::Requests::GET_INVENTORY);
    req->set_request_message(getInventoryMessage.SerializeAsString());

    req = requestEnvelope.mutable_requests()->Add();
    req->set_request_type(Networking::Requests::CHECK_AWARDED_BADGES);
    req->set_request_message(checkAwardedBadgesMessage.SerializeAsString());

    req = requestEnvelope.mutable_requests()->Add();
    req->set_request_type(Networking::Requests::DOWNLOAD_SETTINGS);
    req->set_request_message(downloadSettingsMessage.SerializeAsString());

    QNetworkRequest request;
    request.setUrl(_apiUrl);
    request.setHeader(QNetworkRequest::UserAgentHeader, "Niantic App");
    request.setRawHeader("Connection", "keep-alive");

    QByteArray body(requestEnvelope.ByteSize(), '\0');
    requestEnvelope.SerializeToArray(body.data(), body.size());

    QEventLoop loop;
    QNetworkReply *reply = _net.post(request, body);
    connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    QByteArray response = reply->readAll();

    Networking::Envelopes::ResponseEnvelope responseEnvelope;
    if (responseEnvelope.ParseFromArray(response.data(), response.size()))
    {
        _apiUrl = QUrl(responseEnvelope.api_url().c_str());
        _authTicket = responseEnvelope.auth_ticket();
    }
}
