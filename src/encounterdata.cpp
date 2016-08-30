#include "encounterdata.h"

EncounterData::EncounterData(QObject *parent) : QObject(parent)
{

}

QString EncounterData::status() const
{
    return m_status;
}

QMap<qint32, qreal> EncounterData::captureProbability() const
{
    return m_capture_probability;
}

PokemonData *EncounterData::pokemonData() const
{
    return m_pokemon_data;
}

void EncounterData::setStatus(QString status)
{
    if (m_status == status)
        return;

    m_status = status;
    emit statusChanged(status);
}

void EncounterData::setCaptureProbability(QMap<qint32, qreal> capture_probability)
{
    if (m_capture_probability == capture_probability)
        return;

    m_capture_probability = capture_probability;
    emit captureProbabilityChanged(capture_probability);
}

void EncounterData::setPokemonData(PokemonData *pokemon_data)
{
    if (m_pokemon_data == pokemon_data)
        return;

    m_pokemon_data = pokemon_data;
    emit pokemonDataChanged(pokemon_data);
}
