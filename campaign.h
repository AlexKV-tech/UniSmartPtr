#ifndef CAMPAIGN_H
#define CAMPAIGN_H
#include <string>
#include <map>
#include <memory>
#include "hero.h"

constexpr unsigned MIN_LEVEL = 1;
class Hero;
class Monster;
class Campaign : public std::enable_shared_from_this<Campaign>
{
    std::string name;
    std::map<unsigned, std::weak_ptr<Hero>> heroes;
    unsigned min_level;

public:
    Campaign(const std::string&, unsigned);
    std::string get_name() const;
    unsigned get_min_lvl() const;
    bool has_hero(unsigned) const; // help-method, checks whether a hero with given id already exists in the campaign
    void erase_hero(unsigned id);

    void add_hero(const std::shared_ptr<Hero>&);
    void encounter_monster(unsigned, Monster &) const;
    unsigned remove_dead_and_expired();

    std::ostream &print_heroes(std::ostream &) const;
    std::ostream &print(std::ostream &) const;
};

std::ostream &operator<<(std::ostream &, const Campaign &);

#endif