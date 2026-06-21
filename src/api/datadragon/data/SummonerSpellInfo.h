#ifndef GWENLY_SUMMONERSPELLINFO_H
#define GWENLY_SUMMONERSPELLINFO_H

#include <nlohmann/json.hpp>

struct SummonerSpellInfo
{
    std::string id;
    std::string name;
    std::string cooldownBurn;

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(SummonerSpellInfo, id, name, cooldownBurn)
};

#endif //GWENLY_SUMMONERSPELLINFO_H
