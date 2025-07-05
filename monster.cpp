
#include "monster.h"

Monster::Monster(const std::string& name,
    const unsigned health, const unsigned attack) : name{name}, health{health}, attack{attack}
{
    if (name.empty())
        throw std::runtime_error("Name of a monster may not be empty");
    if (!health)
        throw std::runtime_error("New monsters should have health value greater than 0");
    if (!attack)
        throw std::runtime_error("Monsters should have attack value greater than 0");
}

void Monster::take_damage(const unsigned dmg)
{
    unsigned final_dmg = calculate_damage(dmg);
    if (final_dmg > get_hp())
        health = 0;
    else
        health -= final_dmg;
}
std::string Monster::get_name() const
{
    return name;
}
unsigned Monster::get_hp() const
{
    return health;
}
unsigned Monster::get_attack_val() const
{
    return attack;
}

bool Monster::is_dead() const
{
    return !get_hp();
}

std::ostream &Monster::print(std::ostream &o) const
{
    o << '[';
    o << get_name() << ", ";
    o << get_hp() << " HP, ";
    o << get_attack_val() << " ATK";
    o << additional_information();

    o << ']';
    return o;
}

Elite_Monster::Elite_Monster(const std::string& name, const unsigned health, const unsigned attack,
    const unsigned defense) :Monster(name, health, attack), defense{defense}
{
    if (!defense)
        throw std::runtime_error("Elite Monsters should have defense value greater than 0");
}
unsigned Elite_Monster::get_defense_val() const
{
    return defense;
}
unsigned Elite_Monster::calculate_damage(const unsigned dmg) const
{
    if (dmg < defense)
        return 0;
    return dmg - get_defense_val();
}
std::string Elite_Monster::additional_information() const
{
    return ", " + std::to_string(defense) + " DEF";
}

Standard_Monster::Standard_Monster(const std::string& name,
    const unsigned health, const unsigned attack) : Monster(name, health, attack) {}
unsigned Standard_Monster::calculate_damage(const unsigned dmg) const
{
    return dmg;
}
std::string Standard_Monster::additional_information() const
{
    return "";
}
std::ostream &operator<<(std::ostream &o, const Monster &m)
{
    return m.print(o);
}