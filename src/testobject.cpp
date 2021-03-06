#include <google/protobuf/text_format.h>

#include "proto/POGOProtos.Networking.Responses.pb.h"

#include "testobject.h"

using namespace POGOProtos;
using namespace POGOProtos::Networking::Responses;

TestObject::TestObject(QQuickItem *parent)
    : QQuickItem(parent)
    , _refreshTimer(this)
    , _client(nullptr)
{
    // update every 5 seconds
    _refreshTimer.setInterval(5000);

    connect(&_refreshTimer, &QTimer::timeout, this, &TestObject::refreshData);
    connect(this, &QQuickItem::stateChanged, this, &TestObject::changeState);
}

void TestObject::login(const QString &provider, const QString &login, const QString &password)
{
    qDebug() << "Invoked from QML with args: " << provider << login << password;

    IAuth *auth = AuthFactory::createAuthProvider(provider == "google" ? IAuth::Google : IAuth::PTC);
    auth->login(login, password);

    _client = new PGoClient(auth, this);
    _client->init();

    emit ready();
}

EncounterData *TestObject::encounter(Pokemon *pokemon)
{
    Networking::Requests::Messages::EncounterMessage message;
    message.set_spawn_point_id(pokemon->spawnPointId().toStdString());
    message.set_encounter_id(pokemon->encounterId());
    message.set_player_latitude(pokemon->latitude());
    message.set_player_longitude(pokemon->longitude());

    Networking::Requests::Request encounterRequest;
    encounterRequest.set_request_type(Networking::Requests::ENCOUNTER);
    encounterRequest.set_request_message(message.SerializeAsString());
    EncounterResponse *encounterResponse = _client->post<EncounterResponse>(encounterRequest);

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

void TestObject::changeState(const QString &str)
{
    qDebug() << "Change state to:" << str;

    if (str == "active")
        _refreshTimer.start();
    else
        _refreshTimer.stop();
}

bool contains(const std::list<Pokemon*> &list, qint64 encounterId)
{
    foreach (Pokemon* pokemon, list) {
        if (pokemon->encounterId() == encounterId)
            return true;
    }

    return false;
}

void TestObject::refreshData()
{
#if 1
    if (_client == nullptr)
        return;

    GetMapObjectsResponse *response = _client->getMapObjects();

    foreach (Map::MapCell cell, response->map_cells()) {
        foreach (Map::Pokemon::MapPokemon pokemon, cell.catchable_pokemons()) {
            if (::contains(_pokemons, pokemon.encounter_id()))
                continue;

            Pokemon *p = new Pokemon();
            p->setSpawnPointId(QString::fromStdString(pokemon.spawn_point_id()));
            p->setEncounterId(pokemon.encounter_id());
            p->setPokemonId(pokemon.pokemon_id());
            p->setExpirationTimestampMs(pokemon.expiration_timestamp_ms());
            p->setLatitude(pokemon.latitude());
            p->setLongitude(pokemon.longitude());
            _pokemons.push_back(p);

            emit itemAppeared(p);
        }
    }
#else
    if (_pokemons.size() == 0)
    {
        Pokemon *p = new Pokemon();
        p->setSpawnPointId("spawn_point_id");
        p->setEncounterId(123);
        p->setPokemonId(10);
        p->setExpirationTimestampMs(123);
        p->setLatitude(50.424420);
        p->setLongitude(30.506768);
        _pokemons.push_back(p);

        emit itemAppeared(p);
    }
#endif
}

double TestObject::latitude() const
{
    return _client ? _client->_latitude : 0.0;
}

void TestObject::setLatitude(double latitude)
{
    if (_client)
    {
        _client->_latitude = latitude;
        emit latitudeChanged(latitude);
    }
}

double TestObject::longitude() const
{
    return _client ? _client->_longitude : 0.0;
}

void TestObject::setLongitude(double longitude)
{
    if (_client)
    {
        _client->_longitude = longitude;
        emit longitudeChanged(longitude);
    }
}
