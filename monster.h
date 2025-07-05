#ifndef MONSTER_H
#define MONSTER_H
#include "hero.h"

constexpr unsigned STD_MONST_MAX_HP = 2;
constexpr unsigned STD_MONST_MAX_ATTACK = 1;
constexpr unsigned ELITE_MONST_MAX_HP = 3;
constexpr unsigned ELITE_MONST_MAX_ATTACK = 2;
constexpr unsigned ELITE_MONST_MAX_DEFENSE = 1;
class Monster
{

    std::string name;
    unsigned health;
    unsigned attack;

public:
    Monster(const std::string&, unsigned, unsigned);

    virtual ~Monster() = default;
    virtual unsigned calculate_damage(unsigned) const = 0;
    void take_damage(unsigned);
    std::string get_name() const;
    unsigned get_hp() const;
    unsigned get_attack_val() const;

    bool is_dead() const;
    virtual std::string additional_information() const = 0;
    std::ostream &print(std::ostream &) const;
};

class Elite_Monster : public Monster
{
    unsigned defense;

public:
    Elite_Monster(const std::string&, unsigned, unsigned, unsigned);
    unsigned get_defense_val() const;
    unsigned calculate_damage(unsigned) const override;
    std::string additional_information() const override;
};
class Standard_Monster : public Monster
{
public:
    Standard_Monster(const std::string&, unsigned, unsigned);
    unsigned calculate_damage(unsigned) const override;
    std::string additional_information() const override;
};
std::ostream &operator<<(std::ostream &, const Monster &);
#endif