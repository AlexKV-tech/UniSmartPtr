#include "campaign.h"

Campaign::Campaign(const std::string& name, const unsigned min_level) : name{name}, min_level{min_level}
{
    if (name.empty())
        throw std::runtime_error("Empty names are forbidden");
    if (min_level < MIN_LEVEL)
        throw std::runtime_error("Minimal level must be at least " + std::to_string(MIN_LEVEL));
};
std::string Campaign::get_name() const
{
    return name;
}
unsigned Campaign::get_min_lvl() const
{
    return min_level;
}
bool Campaign::has_hero(const unsigned id) const
{
    return heroes.count(id);
}
void Campaign::erase_hero(const unsigned id) {
    if (!has_hero(id)) throw std::runtime_error("There is no hero with ID " + std::to_string(id) + " in that session");
    heroes.erase(id);
}
void Campaign::add_hero(const std::shared_ptr<Hero>& h)
{
    if (!h)
        throw std::runtime_error("Attempt to add a null-hero");
    if (has_hero(h->get_id()))
        throw std::runtime_error("This hero is already in the session");
    if (h->get_lvl() < min_level)
        throw std::runtime_error(
            "A hero must have at least level " + std::to_string(min_level));
    heroes[h->get_id()] = h;
    h->assign_active_campaign(weak_from_this());
}
void Campaign::encounter_monster(const unsigned id, Monster &m) const {
    if (!has_hero(id))
        throw std::runtime_error("There is no hero with ID " + std::to_string(id) + " in that session");
    auto hero = heroes.at(id).lock();
    if (!hero)
        throw std::runtime_error("Hero with ID " + std::to_string(id) + " was recently removed from that session");
    if (hero->fight(m))
        hero->level_up();
}
unsigned Campaign::remove_dead_and_expired()
{
    unsigned removed{0};
    for (auto it = heroes.begin(); it != heroes.end();)
    {
        auto hero = it->second;
        if (hero.expired() || hero.lock()->is_dead())
        {
            it = heroes.erase(it);
            removed++;
            if (!hero.expired())
                hero.lock()->leave_active_campaign();
        }
        else
        {
            ++it;
        }
    }

    return removed;
}

std::ostream &Campaign::print_heroes(std::ostream &o) const
{
    o << '{';
    bool first_print{true};

    for (const auto &[id, hero_weak_ptr] : heroes)
    {
        auto hero_ptr = hero_weak_ptr.lock();
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
std::ostream &Campaign::print(std::ostream &o) const
{
    o << '[';
    o << get_name() << " Campaign";
    o << ", ";
    o << "Min_Level " << get_min_lvl();
    o << ", ";
    print_heroes(o);
    o << ']';
    return o;
}

std::ostream &operator<<(std::ostream &o, const Campaign &p)
{
    return p.print(o);
}
