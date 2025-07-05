#include "hero.h"
#include "campaign.h"
#include "monster.h"
#include "hero_info.h"
#include "player.h"
#include <algorithm>
#include <vector>
#include <cassert>

Player::Player(const std::string& first_name, const std::string& last_name) : first_name{first_name},
                                                                              last_name{last_name}, campaign{nullptr} {
    if (first_name.empty())
        throw std::runtime_error("First name of a player may not be empty");
    if (last_name.empty())
        throw std::runtime_error("Last name of a player may not be empty");
}

unsigned Player::create_hero(const std::string &name, const Hero_Class hero_class, const Hero_Species hero_species,
                             const unsigned max_hp, const std::map<std::string, unsigned> &abilities)
{
    const auto tied_hero = std::make_shared<Hero>(name, hero_class, hero_species, max_hp, abilities);
    heroes[tied_hero->get_id()] = tied_hero;
    return tied_hero->get_id();
}
void Player::create_campaign(const std::string& name, const unsigned min_level, const unsigned hero_id)
{
    join_campaign_with_hero(std::make_shared<Campaign>(name, min_level), hero_id);
}
bool Player::has_hero(const unsigned hero_id) const
{
    return heroes.count(hero_id);
}

void Player::join_friends_campaign(const Player &pfriend, const unsigned hero_id)
{
    join_campaign_with_hero(pfriend.campaign, hero_id);
}
void Player::assign_hero_to_campaign(const unsigned hero_id) const {
    if (!has_hero(hero_id))
        throw std::runtime_error("There is no player with id " + std::to_string(hero_id));
    if (!campaign)
        throw std::runtime_error("The player doesn't have any running sessions");
    campaign->add_hero(heroes.at(hero_id));
}
void Player::join_campaign_with_hero(const std::shared_ptr<Campaign> &new_campaign, const unsigned hero_id) {
    if (!new_campaign)
        throw std::runtime_error("A friend doesn't have any running sessions");
    campaign.reset();
    leave_all_heroes_from_campaign();
    campaign = new_campaign;
    assign_hero_to_campaign(hero_id);
}
void Player::leave_all_heroes_from_campaign() {
    for (const auto &[hero_id, hero_ptr] : heroes) {
        hero_ptr->leave_active_campaign();
    }
}

void Player::transfer_campaign(Player &pfriend) {
    if (!campaign)
        throw std::runtime_error("There is no running campaigns by the player");
    pfriend.campaign = std::move(campaign);
    leave_all_heroes_from_campaign();
    campaign.reset();
    assert(campaign.get() == nullptr);

}
unsigned Player::remove_dead()
{
    unsigned removed{0};
    for (auto it = heroes.begin(); it != heroes.end();)
    {
        if (const auto hero = it->second; hero->is_dead())
        {
            it = heroes.erase(it);
            removed++;
        }
        else
        {
            ++it;
        }
    }

    return removed;
}
std::vector<unsigned> Player::get_heroes_ids() const
{
    std::vector<unsigned> heroes_ids;
    std::transform(heroes.begin(), heroes.end(),
                   std::back_inserter(heroes_ids), [](const auto &p)
                   { return p.first; });
    return heroes_ids;
}

void Player::encounter_monster(const unsigned hero_id, Monster &m) const {
    campaign->encounter_monster(hero_id, m);
}
void Player::add_hero(const unsigned hero_id) const {
    if (!has_hero(hero_id))
        throw std::runtime_error("Hero with a such id is not in the list of heroes");
    campaign->add_hero(heroes.at(hero_id));
}
std::ostream &Player::print_heroes_log(std::ostream &o, const unsigned hero_id) const
{
    if (!has_hero(hero_id))
        throw std::runtime_error("Hero with a such id is not in the list of heroes");
    heroes.at(hero_id)->print_log(o);
    return o;
}
std::ostream &Player::print_campaign(std::ostream &o) const
{
    if (!campaign)
    {
        o << "[]";
        return o;
    }
    return campaign->print(o);
}

std::ostream &Player::print_heroes(std::ostream &o) const
{
    o << '{';
    bool first_print{true};
    for (const auto &[hero_id, hero_ptr] : heroes)
    {
        if (!hero_ptr)
            continue;
        if (first_print)
        {
            o << *hero_ptr;
            first_print = false;
        }
        else
        {
            o << ", " << *hero_ptr;
        }
    }
    o << '}';
    return o;
}

std::ostream &Player::print(std::ostream &o) const
{
    o << '[';
    o << first_name;
    o << ' ';
    o << last_name;
    o << ", ";
    print_heroes(o);
    o << ", ";
    print_campaign(o);

    o << ']';

    return o;
}

std::ostream &operator<<(std::ostream &o, const Player &p)
{
    return p.print(o);
}
