#include <QByteArray>
#include <QDateTime>
#include <QEventLoop>
#include <QNetworkRequest>
#include <QNetworkReply>

#include <google/protobuf/text_format.h>
#include <third_party/xxHash/xxhash.h>
#include <s2/s2cellid.h>
#include <s2/s2latlng.h>

#include "proto/POGOProtos.Networking.Envelopes.pb.h"
#include "proto/POGOProtos.Networking.Requests.pb.h"
#include "proto/POGOProtos.Networking.Requests.Messages.pb.h"
#include "proto/POGOProtos.Networking.Responses.pb.h"

#include "pgoclient.h"

using namespace POGOProtos;
using namespace POGOProtos::Networking::Responses;

PGoClient::PGoClient(IAuth *auth, QObject *parent) : QObject(parent), _auth(auth), _apiUrl("https://pgorelease.nianticlabs.com/plfe/rpc")
{
    _requestId = 1;
    _latitude = 50.418417;
    _longitude = 30.523445;
    _altitude = 8.0;

    _timer.start();
}

void PGoClient::init()
{
    QString token = _auth->getToken();
    if (token.isEmpty())
        return;

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
    requestEnvelope.mutable_auth_info()->set_provider(_auth->provider().toStdString());
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
        _apiUrl = QUrl(QString("https://") + responseEnvelope.api_url().c_str() + "/rpc");
        _authTicket = responseEnvelope.auth_ticket();
    }

    std::string out;
    google::protobuf::TextFormat::PrintToString(responseEnvelope, &out);

    qInfo() << out.c_str();
}

Networking::Responses::GetInventoryResponse * PGoClient::getInventory()
{
    Networking::Requests::Request getInventoryRequest;
    getInventoryRequest.set_request_type(Networking::Requests::GET_INVENTORY);
    getInventoryRequest.set_request_message(Networking::Requests::Messages::GetInventoryMessage().SerializeAsString());
    auto getInventoryResponse = performRequest<Networking::Responses::GetInventoryResponse>(getInventoryRequest);

    std::string out;
    google::protobuf::TextFormat::PrintToString(*getInventoryResponse, &out);

    qInfo() << out.c_str();

    return getInventoryResponse;
}

Networking::Responses::GetMapObjectsResponse *PGoClient::getMapObjects()
{
    S2CellId cell = S2CellId::FromLatLng(S2LatLng::FromDegrees(_latitude, _longitude)).parent(15);
    std::vector<S2CellId> nearbyCells;
    nearbyCells.push_back(cell);
    cell.AppendAllNeighbors(15, &nearbyCells);

    Networking::Requests::Messages::GetMapObjectsMessage message;
    message.set_latitude(_latitude);
    message.set_longitude(_longitude);
    foreach (S2CellId cell, nearbyCells)
    {
        message.add_cell_id(cell.id());
        message.add_since_timestamp_ms(0);
    }

    Networking::Requests::Request request;
    request.set_request_type(Networking::Requests::GET_MAP_OBJECTS);
    request.set_request_message(message.SerializeAsString());

    auto response = performRequest<Networking::Responses::GetMapObjectsResponse>(request);

    std::string out;
    google::protobuf::TextFormat::PrintToString(*response, &out);

    std::cout << out.c_str() << std::endl;

    return response;
}

EncounterData *PGoClient::encounter(const Pokemon *pokemon)
{
    Networking::Requests::Messages::EncounterMessage message;
    message.set_spawn_point_id(pokemon->spawnPointId().toStdString());
    message.set_encounter_id(pokemon->encounterId());
    message.set_player_latitude(pokemon->latitude());
    message.set_player_longitude(pokemon->longitude());

    Networking::Requests::Request encounterRequest;
    encounterRequest.set_request_type(Networking::Requests::ENCOUNTER);
    encounterRequest.set_request_message(message.SerializeAsString());
    EncounterResponse *encounterResponse = performRequest<EncounterResponse>(encounterRequest);

    std::string out;
    google::protobuf::TextFormat::PrintToString(*encounterResponse, &out);

    qInfo() << out.c_str();

    PokemonData *pokemonData = new PokemonData();
    pokemonData->setPokemonId(encounterResponse->wild_pokemon().pokemon_data().pokemon_id());
    pokemonData->setIndividualAttack(encounterResponse->wild_pokemon().pokemon_data().individual_attack());
    pokemonData->setIndividualDefence(encounterResponse->wild_pokemon().pokemon_data().individual_defense());
    pokemonData->setIndividualStamina(encounterResponse->wild_pokemon().pokemon_data().individual_stamina());
    pokemonData->setCp(encounterResponse->wild_pokemon().pokemon_data().cp());

    EncounterData *encounterData = new EncounterData();
    encounterData->setStatus(QString::fromStdString(Networking::Responses::EncounterResponse_Status_Name(encounterResponse->status())));
    encounterData->setPokemonData(pokemonData);

    return encounterData;
}

Networking::Envelopes::Unknown6 *PGoClient::generateSignature(Networking::Requests::Request &request)
{
    std::string input = _authTicket.SerializeAsString();
    QByteArray location =
            QByteArray::fromRawData(reinterpret_cast<char *>(&_altitude), sizeof(_altitude)) +
            QByteArray::fromRawData(reinterpret_cast<char *>(&_longitude), sizeof(_longitude)) +
            QByteArray::fromRawData(reinterpret_cast<char *>(&_latitude), sizeof(_latitude));

    std::reverse(location.begin(), location.end());
    XXH32_hash_t seed32 = XXH32(input.c_str(), input.size(), 0x1B845238);
    XXH32_hash_t hash1 = XXH32(location.data(), location.size(), seed32);
    XXH32_hash_t hash2 = XXH32(location.data(), location.size(), 0x1B845238);

    std::string req = request.SerializeAsString();
    XXH64_hash_t seed64 = XXH64(input.c_str(), input.size(), 0x1B845238);
    XXH64_hash_t hash = XXH64(req.c_str(), req.size(), seed64);

    uchar session_hash[] = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F };

    Networking::Envelopes::Signature sig;
    sig.set_timestamp_since_start(_timer.elapsed());
    sig.set_timestamp(QDateTime::currentMSecsSinceEpoch());
    sig.set_location_hash1(hash1);
    sig.set_location_hash2(hash2);
    sig.set_session_hash(session_hash, sizeof(session_hash));
    sig.mutable_request_hash()->Add(hash);

    Networking::Envelopes::Unknown6 *unk6 = new Networking::Envelopes::Unknown6();
    unk6->set_request_type(6);
    unk6->mutable_unknown2()->set_encrypted_signature(encrypt(sig.SerializeAsString()));

    return unk6;
}


extern "C" int encrypt(char*, size_t, char*, size_t, uchar*, size_t*);

std::string PGoClient::encrypt(const std::string &data)
{
    char session_hash[32] = { 0x00 };
    size_t outSize = 32 + data.size() + (256 - (data.size() % 256));
    uchar *out = new uchar[outSize];
    ::encrypt((char*) data.c_str(), data.size(), session_hash, sizeof(session_hash), out, &outSize);

    return std::string((char*)out, outSize);
}

template<typename ResponseType>
ResponseType * PGoClient::performRequest(Networking::Requests::Request &request)
{
    generateSignature(request);

    Networking::Envelopes::RequestEnvelope requestEnvelope;
    requestEnvelope.set_status_code(2);
    requestEnvelope.set_request_id(_requestId++);
    requestEnvelope.set_latitude(_latitude);
    requestEnvelope.set_longitude(_longitude);
    requestEnvelope.set_altitude(_altitude);
    requestEnvelope.mutable_auth_ticket()->CopyFrom(_authTicket);
    requestEnvelope.set_unknown12(989);

    requestEnvelope.mutable_requests()->Add()->MergeFrom(request);
    requestEnvelope.set_allocated_unknown6(generateSignature(request));

    QNetworkRequest req;
    req.setUrl(_apiUrl);
    req.setHeader(QNetworkRequest::UserAgentHeader, "Niantic App");
    req.setRawHeader("Connection", "keep-alive");

    QByteArray body(requestEnvelope.ByteSize(), '\0');
    requestEnvelope.SerializeToArray(body.data(), body.size());

    QEventLoop loop;
    QNetworkReply *reply = _net.post(req, body);
    connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    QByteArray response = reply->readAll();

    Networking::Envelopes::ResponseEnvelope responseEnvelope;
    if (responseEnvelope.ParseFromArray(response.data(), response.size()))
    {
        ResponseType *response = new ResponseType();
        response->ParseFromString(responseEnvelope.returns(0));

        return response;
    }

    return nullptr;
}
