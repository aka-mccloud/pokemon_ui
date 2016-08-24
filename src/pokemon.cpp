#include "pokemon.h"

Pokemon::Pokemon(QObject *parent) : QObject(parent)
{

}

QString Pokemon::spawnPointId() const
{
    return _spawnPointId;
}

void Pokemon::setSpawnPointId(QString spawnPointId)
{
    _spawnPointId = spawnPointId;
    emit spawnPointIdChanged(_spawnPointId);
}

qint64 Pokemon::encounterId() const
{
    return _encounterId;
}

void Pokemon::setEncounterId(qint64 encounterId)
{
    _encounterId = encounterId;
    emit encounterIdChanged(_encounterId);
}

qint32 Pokemon::pokemonId() const
{
    return _pokemonId;
}

void Pokemon::setPokemonId(qint32 pokemonId)
{
    _pokemonId = pokemonId;
    emit pokemonIdChanged(_pokemonId);
}

qint64 Pokemon::expirationTimestampMs() const
{
    return _expirationTimestampMs;
}

void Pokemon::setExpirationTimestampMs(qint64 expirationTimestampMs)
{
    _expirationTimestampMs = expirationTimestampMs;
    emit expirationTimestampMsChanged(_expirationTimestampMs);
}

qreal Pokemon::latitude() const
{
    return _latitude;
}

void Pokemon::setLatitude(qreal latitude)
{
    _latitude = latitude;
    emit latitudeChanged(_latitude);
}

qreal Pokemon::longitude() const
{
    return _longitude;
}

void Pokemon::setLongitude(qreal longitude)
{
    _longitude = longitude;
    emit longitudeChanged(_longitude);
}
