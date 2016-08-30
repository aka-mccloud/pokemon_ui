#ifndef POKEMONDATA_H
#define POKEMONDATA_H

#include <QObject>

class PokemonData : public QObject
{
    Q_OBJECT
    Q_PROPERTY(qint32 pokemon_id READ pokemonId WRITE setPokemonId NOTIFY pokemonIdChanged)
    Q_PROPERTY(qint32 cp READ cp WRITE setCp NOTIFY cpChanged)
    Q_PROPERTY(qint32 individual_attack READ individualAttack WRITE setIndividualAttack NOTIFY individualAttackChanged)
    Q_PROPERTY(qint32 individual_defence READ individualDefence WRITE setIndividualDefence NOTIFY individualDefenceChanged)
    Q_PROPERTY(qint32 individual_stamina READ individualStamina WRITE setIndividualStamina NOTIFY individualStaminaChanged)
    Q_PROPERTY(QString nickname READ nickname WRITE setNickname NOTIFY nicknameChanged)

public:
    explicit PokemonData(QObject *parent = 0);

    qint32 pokemonId() const;
    qint32 cp() const;
    qint32 individualAttack() const;
    qint32 individualDefence() const;
    qint32 individualStamina() const;
    QString nickname() const;

signals:
    void pokemonIdChanged(qint32 pokemon_id);
    void cpChanged(qint32 cp);
    void individualAttackChanged(qint32 individual_attack);
    void individualDefenceChanged(qint32 individual_defence);
    void individualStaminaChanged(qint32 individual_stamina);
    void nicknameChanged(QString nickname);

public slots:
    void setPokemonId(qint32 pokemon_id);
    void setCp(qint32 cp);
    void setIndividualAttack(qint32 individual_attack);
    void setIndividualDefence(qint32 individual_defence);
    void setIndividualStamina(qint32 individual_stamina);
    void setNickname(QString nickname);

private:
    qint32 m_pokemon_id;
    qint32 m_cp;
    qint32 m_individual_attack;
    qint32 m_individual_defence;
    qint32 m_individual_stamina;
    QString m_nickname;

};

#endif // POKEMONDATA_H
