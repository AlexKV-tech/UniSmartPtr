#ifndef PLAYER_H
#define PLAYER_H
#include "hero.h"
#include "campaign.h"
#include <vector>

class Player
{
    std::string first_name;
    std::string last_name;
    std::map<unsigned, std::shared_ptr<Hero>> heroes;
    std::shared_ptr<Campaign> campaign;

public:
    Player(const std::string&, const std::string&);
    unsigned create_hero(const std::string &, Hero_Class, Hero_Species,
                         unsigned, const std::map<std::string, unsigned> &);
    void create_campaign(const std::string&, unsigned, unsigned);
    bool has_hero(unsigned) const; // help-method, checks whether a hero with id is in the player's list

    void join_friends_campaign(const Player &pfriend, unsigned hero_id);
    void join_campaign_with_hero(const std::shared_ptr<Campaign> &new_campaign, unsigned hero_id);

    void leave_all_heroes_from_campaign();

    void transfer_campaign(Player &);
    void assign_hero_to_campaign(unsigned) const;
    unsigned remove_dead();
    std::vector<unsigned> get_heroes_ids() const;
    void encounter_monster(unsigned, Monster &) const;
    void add_hero(unsigned) const;
    std::ostream &print_campaign(std::ostream &) const;

    std::ostream &print_heroes(std::ostream &) const;
    std::ostream &print_heroes_log(std::ostream &, unsigned) const;
    std::ostream &print(std::ostream &) const;
};
std::ostream &operator<<(std::ostream &, const Player &);
#endif