#ifndef HERO_H
#define HERO_H
#include <string>
#include <map>
#include <memory>
#include "hero_info.h"
#include "monster.h"
#include "campaign.h"

class Monster;
class Campaign;
class Hero
{
    unsigned id;
    std::string name;
    Hero_Class hero_class;
    Hero_Species hero_species;
    unsigned level;
    unsigned max_hp;
    unsigned current_hp;
    std::map<std::string, unsigned> abilities;
    static unsigned next_id;
    std::weak_ptr<Campaign> active_campaign;
    std::map<std::string, unsigned> campaign_level_log;

public:
    Hero(const std::string&, Hero_Class, Hero_Species, unsigned,
         const std::map<std::string, unsigned> &);
    void assign_active_campaign(const std::weak_ptr<Campaign>&);
    void leave_active_campaign();
    void add_campaign_to_log(std::string &&);
    unsigned get_id() const;
    std::string get_name() const;
    unsigned get_lvl() const;
    unsigned get_hp() const;
    unsigned level_up();
    void log_campaign_level_up();
    unsigned calculate_attack_val() const; // help-method, calculates how much damage the hero will cause to a monster
    bool is_dead() const;                  // help-method, returns whether the hero is dead
    bool fight(Monster &);
    void take_damage(unsigned); // help-method, updates hp level of the hero in response to a monster's damage
    std::ostream &print_abilities(std::ostream &) const;
    std::ostream &print_hp(std::ostream &) const;
    std::ostream &print(std::ostream &) const;
    std::ostream &print_log(std::ostream &) const;
};
std::ostream &operator<<(std::ostream &, const Hero &);
#endif