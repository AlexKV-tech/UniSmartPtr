#include "hero.h"
#include <algorithm>

Hero::Hero(const std::string& name, const Hero_Class hero_class, const Hero_Species hero_species, const unsigned max_hp,
           const std::map<std::string, unsigned> &abilities) : name{name},
                                                               hero_class{hero_class},
                                                               hero_species{hero_species},
                                                               level{DEFAULT_LEVEL}, max_hp{max_hp},
                                                               current_hp{max_hp},
                                                               abilities{abilities.begin(), abilities.end()}
{
    if (name.empty())
        throw std::runtime_error("Empty names are forbidden");
    if (abilities.size() != KEY_ABILITIES_CNT)
        throw std::runtime_error("Incorrect number of abilities");
    unsigned val;

    for (size_t i{0}; i < KEY_ABILITIES_CNT; i++)
    {

        if (abilities.count(KEY_ABILITIES[i]))
            val = abilities.at(KEY_ABILITIES[i]);
        else
            throw std::runtime_error("Ability " + KEY_ABILITIES[i] + " was not found in the range");
        if (val > MAX_ABILITY_VAL || val < MIN_ABILITY_VAL)
            throw std::runtime_error("Ability " + KEY_ABILITIES[i] + " is not in permitted range");
    }
    id = next_id++;
}
void Hero::assign_active_campaign(const std::weak_ptr<Campaign>& new_campaign)
{
    if (new_campaign.expired())
        throw std::runtime_error("Invalid campaign was provided");
    leave_active_campaign();
    active_campaign = new_campaign;
    add_campaign_to_log(new_campaign.lock()->get_name());
}
void Hero::add_campaign_to_log(std::string &&campaign_title)
{
    if (!campaign_level_log.count(campaign_title))
        campaign_level_log.insert({campaign_title, 0});
}
void Hero::leave_active_campaign()
{
    if (!active_campaign.expired()) active_campaign.lock()->erase_hero(id);
    active_campaign.reset();
}
unsigned Hero::get_id() const
{
    return id;
}
std::string Hero::get_name() const
{
    return name;
}
unsigned Hero::get_lvl() const
{
    return level;
}
unsigned Hero::get_hp() const
{
    return current_hp;
}
unsigned Hero::level_up()
{
    if (active_campaign.expired())
        throw std::runtime_error("Level up was called not within an active campaign");
    if (level < MAX_LEVEL)
    {
        level++;
        log_campaign_level_up();
    }
    return level;
}
void Hero::log_campaign_level_up()
{
    campaign_level_log.at(active_campaign.lock()->get_name())++;
}
unsigned Hero::calculate_attack_val() const
{
    auto max_ability = std::max_element(
                           abilities.begin(), abilities.end(),
                           [](const auto &p1, const auto &p2)
                           { return p1.second < p2.second; })
                           ->second;

    return level * max_ability;
}
bool Hero::is_dead() const
{
    return !get_hp();
}
bool Hero::fight(Monster &m)
{

    while (!is_dead() && !m.is_dead())
    {
        m.take_damage(calculate_attack_val());
        if (!m.is_dead())
            take_damage(m.get_attack_val());
    }
    return !is_dead();
}
void Hero::take_damage(const unsigned dmg)
{
    if (dmg > get_hp())
        current_hp = 0;
    else
        current_hp -= dmg;
}
std::ostream &Hero::print_abilities(std::ostream &o) const
{
    o << '{';
    for (size_t i{0}; i < KEY_ABILITIES_CNT; i++)
    {
        o << abilities.at(KEY_ABILITIES[i]);
        if (i < KEY_ABILITIES_CNT - 1)
            o << ", ";
    }

    o << '}';
    return o;
}
std::ostream &Hero::print_hp(std::ostream &o) const
{
    o << '(';
    o << get_hp() << '/' << max_hp;
    o << ')';
    o << " HP";
    return o;
}
std::ostream &Hero::print_log(std::ostream &o) const
{
    if (campaign_level_log.empty())
        return o;

    o << "LOG: {";
    bool first{true};
    for (const auto &[camp_name, lvl_up] : campaign_level_log)
    {
        if (first)
        {
            o << camp_name << ": +" << lvl_up;
            first = false;
        }
        else
        {
            o << ", \n"
              << camp_name << ": +" << lvl_up;
        }
    }
    o << '}';
    return o;
}
std::ostream &Hero::print(std::ostream &o) const
{
    o << '[';
    o << id << ", ";
    o << name << ", ";
    o << '(';
    o << hero_class << ", ";
    o << hero_species << ", ";
    o << level << "), ";
    print_abilities(o);
    o << ", ";
    print_hp(o);
    o << ']';

    return o;
}

unsigned Hero::next_id{START_ID};
std::ostream &operator<<(std::ostream &o, const Hero &obj)
{
    return obj.print(o);
}