#ifndef POKEMON_H
#define POKEMON_H

#include <QObject>

class Pokemon : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int pokemon_id READ pokemonId WRITE setPokemonId NOTIFY pokemonIdChanged)
    Q_PROPERTY(double latitude READ latitude WRITE setLatitude NOTIFY latitudeChanged)
    Q_PROPERTY(double longitude READ longitude WRITE setLongitude NOTIFY longitudeChanged)

public:
    explicit Pokemon(QObject *parent = 0);

    int pokemonId() const;
    void setPokemonId(int pokemonId);

    double latitude() const;
    void setLatitude(double latitude);

    double longitude() const;
    void setLongitude(double longitude);

signals:
    void pokemonIdChanged(int);
    void latitudeChanged(double);
    void longitudeChanged(double);

private:
    int _pokemonId;
    double _latitude;
    double _longitude;
};

#endif // POKEMON_H
