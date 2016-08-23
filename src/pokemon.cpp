#include "pokemon.h"

Pokemon::Pokemon(QObject *parent) : QObject(parent)
{
    setPokemonId(10);
}

int Pokemon::pokemonId() const
{
    return _pokemonId;
}

void Pokemon::setPokemonId(int pokemonId)
{
    _pokemonId = pokemonId;
    emit pokemonIdChanged(_pokemonId);
}

double Pokemon::latitude() const
{
    return _latitude;
}

void Pokemon::setLatitude(double latitude)
{
    _latitude = latitude;
    emit latitudeChanged(_latitude);
}

double Pokemon::longitude() const
{
    return _longitude;
}

void Pokemon::setLongitude(double longitude)
{
    _longitude = longitude;
    emit longitudeChanged(_longitude);
}
