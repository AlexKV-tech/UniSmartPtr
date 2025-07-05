#ifndef HERO_INFO_H
#define HERO_INFO_H
#include <iostream>
#include <map>
#include <array>

constexpr unsigned DEFAULT_LEVEL = 1;
constexpr unsigned MAX_LEVEL = 20;
constexpr unsigned MAX_ABILITY_VAL = 20;
constexpr unsigned MIN_ABILITY_VAL = 1;
constexpr unsigned DEATH_HP = 0;
constexpr unsigned START_ID = 0;
constexpr unsigned HERO_CLASS_NUM = 12;
constexpr unsigned HERO_SPECIES_NUM = 10;
constexpr unsigned HERO_MAX_HP = 300;
enum class Hero_Class
{
    BARBARIAN,
    BARD,
    CLERIC,
    DRUID,
    FIGHTER,
    MONK,
    PALADIN,
    RANGER,
    ROGUE,
    SORCERER,
    WARLOCK,
    WIZARD
};
enum class Hero_Species
{
    DRAGONBORN,
    DWARF,
    ELF,
    GNOME,
    AASIMAR,
    HALFLING,
    ORC,
    GOLIATH,
    HUMAN,
    TIEFLING
};
const std::map<Hero_Class, std::string> HERO_CLASS_REPR_MAP = {
    {Hero_Class::BARBARIAN, "Barbarian"},
    {Hero_Class::BARD, "Bard"},
    {Hero_Class::CLERIC, "Cleric"},
    {Hero_Class::DRUID, "Druid"},
    {Hero_Class::FIGHTER, "Fighter"},
    {Hero_Class::MONK, "Monk"},
    {Hero_Class::PALADIN, "Paladin"},
    {Hero_Class::RANGER, "Ranger"},
    {Hero_Class::ROGUE, "Rogue"},
    {Hero_Class::SORCERER, "Sorcerer"},
    {Hero_Class::WARLOCK, "Warlock"},
    {Hero_Class::WIZARD, "Wizard"}};
const std::map<Hero_Species, std::string> HERO_SPECIES_REPR_MAP = {
    {Hero_Species::DRAGONBORN, "Dragonborn"},
    {Hero_Species::DWARF, "Dwarf"},
    {Hero_Species::ELF, "Elf"},
    {Hero_Species::GNOME, "Gnome"},
    {Hero_Species::AASIMAR, "Aasimar"},
    {Hero_Species::HALFLING, "Halfling"},
    {Hero_Species::ORC, "Orc"},
    {Hero_Species::GOLIATH, "Goliath"},
    {Hero_Species::HUMAN, "Human"},
    {Hero_Species::TIEFLING, "Tiefling"}};
constexpr size_t KEY_ABILITIES_CNT = 6;
const std::array<std::string, KEY_ABILITIES_CNT> KEY_ABILITIES = {
    "Charisma",
    "Constitution",
    "Dexterity",
    "Intelligence",
    "Strength",
    "Wisdom"};
std::ostream &operator<<(std::ostream &, Hero_Class);
std::ostream &operator<<(std::ostream &, Hero_Species);

#endif