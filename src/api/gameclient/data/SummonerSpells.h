#ifndef GWENLY_SUMMONERSPELL_H
#define GWENLY_SUMMONERSPELL_H

#include <nlohmann/json.hpp>
#include <string>

struct SummonerSpell
{
    std::string displayName;
    std::string rawDescription;
    std::string rawDisplayName;

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(SummonerSpell, displayName, rawDescription, rawDisplayName)
};

struct SummonerSpells
{
    SummonerSpell summonerSpellOne;
    SummonerSpell summonerSpellTwo;

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(SummonerSpells, summonerSpellOne, summonerSpellTwo)
};



#endif //GWENLY_SUMMONERSPELL_H
