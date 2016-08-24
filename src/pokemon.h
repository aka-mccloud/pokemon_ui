#ifndef POKEMON_H
#define POKEMON_H

#include <QObject>

class Pokemon : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString spawn_pint_id READ spawnPointId WRITE setSpawnPointId NOTIFY spawnPointIdChanged)
    Q_PROPERTY(qint64 encounter_id READ encounterId WRITE setEncounterId NOTIFY encounterIdChanged)
    Q_PROPERTY(qint32 pokemon_id READ pokemonId WRITE setPokemonId NOTIFY pokemonIdChanged)
    Q_PROPERTY(qint64 expiration_timestamp_ms READ expirationTimestampMs WRITE setExpirationTimestampMs NOTIFY expirationTimestampMsChanged)
    Q_PROPERTY(qreal latitude READ latitude WRITE setLatitude NOTIFY latitudeChanged)
    Q_PROPERTY(qreal longitude READ longitude WRITE setLongitude NOTIFY longitudeChanged)

public:
    explicit Pokemon(QObject *parent = 0);

    QString spawnPointId() const;
    void setSpawnPointId(QString spawnPointId);

    qint64 encounterId() const;
    void setEncounterId(qint64 encounterId);

    qint32 pokemonId() const;
    void setPokemonId(qint32 pokemonId);

    qint64 expirationTimestampMs() const;
    void setExpirationTimestampMs(qint64 expirationTimestampMs);

    qreal latitude() const;
    void setLatitude(qreal latitude);

    qreal longitude() const;
    void setLongitude(qreal longitude);

signals:
    void spawnPointIdChanged(QString);
    void encounterIdChanged(qint64);
    void pokemonIdChanged(qint32);
    void expirationTimestampMsChanged(qint64);
    void latitudeChanged(qreal);
    void longitudeChanged(qreal);

private:
    QString _spawnPointId;
    qint64 _encounterId;
    qint32 _pokemonId;
    qint64 _expirationTimestampMs;
    qreal _latitude;
    qreal _longitude;
};

#endif // POKEMON_H
