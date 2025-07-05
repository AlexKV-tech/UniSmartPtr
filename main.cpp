#include <iostream>
#include <vector>
#include <cstdlib>
#include "player.h"

constexpr unsigned ELITE_MONST_N = 10;
constexpr unsigned STD_MONST_N = 20;
constexpr unsigned MAX_N_HEROES = 4;
constexpr unsigned MIN_N_HEROES = 1;
constexpr unsigned PLAYERS_N = 4;


int main()
{
    /*Monsters initialization*/
    std::vector<std::shared_ptr<Standard_Monster>> std_monsters;
    for (unsigned i{1}; i <= STD_MONST_N; i++)
    {
        std_monsters.emplace_back(std::make_shared<Standard_Monster>("Standard Monster " + std::to_string(i),
                                                STD_MONST_MAX_HP,
                                                std::max(static_cast<unsigned>(rand()) % STD_MONST_MAX_ATTACK, MIN_LEVEL)));
    }
    std::vector<std::shared_ptr<Elite_Monster>> elite_monsters;
    for (unsigned i{1}; i <= ELITE_MONST_N; i++)
    {
        elite_monsters.emplace_back(std::make_shared<Elite_Monster>("Elite Monster " + std::to_string(i),
                                               ELITE_MONST_MAX_HP,
                                               std::max(static_cast<unsigned>(rand()) % ELITE_MONST_MAX_ATTACK, MIN_LEVEL),
                                               std::max(static_cast<unsigned>(rand()) % ELITE_MONST_MAX_DEFENSE, MIN_LEVEL)));
    }
    /*Players initialization*/
    std::vector<std::shared_ptr<Player>> players;
    for (unsigned i{1}; i <= PLAYERS_N; i++)
    {
        std::map<std::string, unsigned> test_abilities;
        for (const auto& str : KEY_ABILITIES)
        {
            test_abilities[str] = std::max(static_cast<unsigned>(rand()) % MAX_ABILITY_VAL, MIN_ABILITY_VAL);
        }
        auto p{std::make_shared<Player>("Player " + std::to_string(i), " Playerov " + std::to_string(i))};
        for (unsigned j{1}; j <= std::max(static_cast<unsigned>(rand()) % MAX_N_HEROES, MIN_N_HEROES); j++)
        {
            p->create_hero("Hero " + std::to_string(i),
                           static_cast<Hero_Class>(static_cast<unsigned>(rand()) % HERO_CLASS_NUM),
                           static_cast<Hero_Species>(static_cast<unsigned>(rand()) % HERO_SPECIES_NUM),
                           HERO_MAX_HP,
                           test_abilities);
        }
        auto heroes_ids = p->get_heroes_ids();
        const auto random_hero_idx = static_cast<unsigned>(rand()) % static_cast<unsigned>(heroes_ids.size());
        p->create_campaign("Campaign " + std::to_string(i),
                           MIN_LEVEL, heroes_ids.at(random_hero_idx));
        for (const unsigned hero_id : heroes_ids)
        {
            try
            {
                if (hero_id != heroes_ids.at(random_hero_idx))
                    p->add_hero(hero_id);
            }
            catch (std::runtime_error&)
            {
                std::cerr << "The hero with such an id was added";
            }
        }

        players.push_back(p);
    }
    /*Fighting with standard monsters*/

    while (!std_monsters.empty())
    {
        const auto rand_monster_idx = static_cast<unsigned>(rand()) % std_monsters.size();
        auto cur_monster = std_monsters.at(rand_monster_idx);
        std::cout << "Standard Monster " << *cur_monster << " was chosen for the fighting\n";
        const auto rand_player_idx = static_cast<unsigned>(rand()) % players.size();
        auto &cur_player = players.at(rand_player_idx);
        std::cout << "Player " << *cur_player << " was chosen for the fighting\n";
        auto heroes_ids = cur_player->get_heroes_ids();
        const auto rand_hero_idx = static_cast<unsigned>(rand()) % static_cast<unsigned>(heroes_ids.size());
        cur_player->encounter_monster(heroes_ids.at(rand_hero_idx), *cur_monster);
        std_monsters.erase(std_monsters.begin() + static_cast<std::ptrdiff_t>(rand_monster_idx));
    }
    std::cout << '\n';
    for (const auto& p : players)
    {
        std::cout << "Player " << *p << '\n';
        for (const unsigned h_id : p->get_heroes_ids())
        {
            std::cout << "Hero with id " + std::to_string(h_id) << '\n';
            p->print_heroes_log(std::cout, h_id);
            std::cout << "\n";
        }
        std::cout << '\n';
    }
    std::cout << '\n';
    /*Campaigns transfer*/
    for (unsigned i{0}; i < PLAYERS_N; i++) {
        const unsigned new_camp_from_idx = static_cast<unsigned>(rand()) % PLAYERS_N;
        const auto& p = players.at(new_camp_from_idx);
        players.at(new_camp_from_idx)->transfer_campaign(*p);
        auto heroes_ids = p->get_heroes_ids();
        const auto random_hero_idx = static_cast<unsigned>(rand()) % static_cast<unsigned>(heroes_ids.size());
        p->create_campaign("Campaign " + std::to_string((i + 1) * 2),
                           MIN_LEVEL, heroes_ids.at(random_hero_idx));
        for (const auto &hero_id: heroes_ids) {
            try
            {
                if (hero_id != heroes_ids.at(random_hero_idx))
                    p->add_hero(hero_id);
            }
            catch (std::runtime_error&)
            {
                std::cerr << "The hero with such an id was added";
            }
        }

    }
    /*Fighting with elite monsters*/
    while (!elite_monsters.empty())
    {
        const auto rand_monster_idx = static_cast<unsigned>(rand()) % elite_monsters.size();
        auto cur_monster = elite_monsters.at(rand_monster_idx);
        std::cout << "Elite Monster " << *cur_monster << " was chosen for the fighting\n";
        const auto rand_player_idx = static_cast<unsigned>(rand()) % players.size();
        auto &cur_player = players.at(rand_player_idx);
        std::cout << "Player " << *cur_player << " was chosen for the fighting\n";
        auto heroes_ids = cur_player->get_heroes_ids();
        const auto rand_hero_idx = static_cast<unsigned>(rand()) % static_cast<unsigned>(heroes_ids.size());
        cur_player->encounter_monster(heroes_ids.at(rand_hero_idx), *cur_monster);
        elite_monsters.erase(elite_monsters.begin() + static_cast<std::ptrdiff_t>(rand_monster_idx));
    }
    std::cout << '\n';
    for (const auto& p : players)
    {
        std::cout << "Player " << *p << '\n';
        for (const unsigned h_id : p->get_heroes_ids())
        {
            std::cout << "Hero with id " + std::to_string(h_id) << '\n';
            p->print_heroes_log(std::cout, h_id);
            std::cout << "\n";
        }
        std::cout << '\n';
    }
    return 0;
}