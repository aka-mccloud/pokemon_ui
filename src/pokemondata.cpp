#include "pokemondata.h"

PokemonData::PokemonData(QObject *parent) : QObject(parent)
{

}

qint32 PokemonData::pokemonId() const
{
    return m_pokemon_id;
}

qint32 PokemonData::cp() const
{
    return m_cp;
}

qint32 PokemonData::individualAttack() const
{
    return m_individual_attack;
}

qint32 PokemonData::individualDefence() const
{
    return m_individual_defence;
}

qint32 PokemonData::individualStamina() const
{
    return m_individual_stamina;
}

QString PokemonData::nickname() const
{
    return m_nickname;
}

void PokemonData::setPokemonId(qint32 pokemon_id)
{
    if (m_pokemon_id == pokemon_id)
        return;

    m_pokemon_id = pokemon_id;
    emit pokemonIdChanged(pokemon_id);
}

void PokemonData::setCp(qint32 cp)
{
    if (m_cp == cp)
        return;

    m_cp = cp;
    emit cpChanged(cp);
}

void PokemonData::setIndividualAttack(qint32 individual_attack)
{
    if (m_individual_attack == individual_attack)
        return;

    m_individual_attack = individual_attack;
    emit individualAttackChanged(individual_attack);
}

void PokemonData::setIndividualDefence(qint32 individual_defence)
{
    if (m_individual_defence == individual_defence)
        return;

    m_individual_defence = individual_defence;
    emit individualDefenceChanged(individual_defence);
}

void PokemonData::setIndividualStamina(qint32 individual_stamina)
{
    if (m_individual_stamina == individual_stamina)
        return;

    m_individual_stamina = individual_stamina;
    emit individualStaminaChanged(individual_stamina);
}

void PokemonData::setNickname(QString nickname)
{
    if (m_nickname == nickname)
        return;

    m_nickname = nickname;
    emit nicknameChanged(nickname);
}
