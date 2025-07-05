#include "hero_info.h"

std::ostream &operator<<(std::ostream &o, Hero_Class m)
{
    o << HERO_CLASS_REPR_MAP.at(m);
    return o;
}
std::ostream &operator<<(std::ostream &o, Hero_Species m)
{
    o << HERO_SPECIES_REPR_MAP.at(m);
    return o;
}