#ifndef ENCOUNTERDATA_H
#define ENCOUNTERDATA_H

#include <QMap>
#include <QObject>

#include "pokemondata.h"

class EncounterData : public QObject
{

    Q_OBJECT
    Q_PROPERTY(QString status READ status WRITE setStatus NOTIFY statusChanged)
    Q_PROPERTY(QMap<qint32, qreal> capture_probability READ captureProbability WRITE setCaptureProbability NOTIFY captureProbabilityChanged)
    Q_PROPERTY(PokemonData* pokemon_data READ pokemonData WRITE setPokemonData NOTIFY pokemonDataChanged)

public:
    explicit EncounterData(QObject *parent = 0);

    QString status() const;
    QMap<qint32, qreal> captureProbability() const;
    PokemonData *pokemonData() const;

signals:
    void statusChanged(QString status);
    void captureProbabilityChanged(QMap<qint32, qreal> capture_probability);
    void pokemonDataChanged(PokemonData *pokemon_data);

public slots:
    void setStatus(QString status);
    void setCaptureProbability(QMap<qint32, qreal> capture_probability);
    void setPokemonData(PokemonData *pokemon_data);

private:
    QString m_status;
    QMap<qint32, qreal> m_capture_probability;
    PokemonData *m_pokemon_data;

};

#endif // ENCOUNTERDATA_H
